//******************************************************************************
//   MSP430x24x Demo - USCI_A1, Ultra-Low Pwr UART 9600 Echo ISR, 32kHz ACLK
//
//   Description: Echo a received character, RX ISR used. Normal mode is LPM3,
//   USCI_A1 RX interrupt triggers TX Echo.
//   ACLK = BRCLK = LFXT1 = 32768Hz, MCLK = SMCLK = DCO ~1.045Mhz
//   Baud rate divider with 32768Hz XTAL @9600 = 32768Hz/9600 = 3.41 
//   => UCBRx = 0x03; In UCA1MCTL: UCBRSx = round(0.41*8) = 0x03
//   //* An external watch crystal is required on XIN XOUT for ACLK *//
//
//                MSP430F249
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |     P3.6/UCA1TXD|------------>
//            |                 | 9600 - 8N1
//            |     P3.7/UCA1RXD|<------------
//
//  B. Nisarga
//  Texas Instruments Inc.
//  September 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//******************************************************************************
#include "msp430x24x.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR = 0xFF;                             // All P1.x outputs
  P1OUT = 0;                                // All P1.x reset
  P2DIR = 0xFF;                             // All P2.x outputs
  P2OUT = 0;                                // All P2.x reset
  P3SEL = 0x0C0;                            // P3.6,7 = USCI_A1 TXD/RXD
  P3DIR = 0xFF;                             // All P3.x outputs
  P3OUT = 0;                                // All P3.x reset
  P4DIR = 0xFF;                             // All P4.x outputs
  P4OUT = 0;                                // All P4.x reset
  P5DIR = 0xFF;                             // All P5.x outputs
  P5OUT = 0;                                // All P5.x reset
  P6DIR = 0xFF;                             // All P6.x outputs
  P6OUT = 0;                                // All P6.x reset  
  
  UCA1CTL1 |= UCSSEL_1;                     // CLK = ACLK
  UCA1BR0 = 0x03;                           // 32kHz/9600 = 3.41
  UCA1BR1 = 0x00;                           //
  UCA1MCTL = UCBRS1 + UCBRS0;               // Modulation UCBRSx = 3
  UCA1CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  UC1IE |= UCA1RXIE;                          // Enable USCI_A1 RX interrupt

  __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3, interrupts enabled
}

// Echo back RXed character, confirm TX buffer is ready first
#pragma vector=USCIAB1RX_VECTOR
__interrupt void USCI1RX_ISR(void)
{
  while (!(UC1IFG&UCA1TXIFG));               // USCI_A1 TX buffer ready?
  UCA1TXBUF = UCA1RXBUF;                     // TX -> RXed character
}
