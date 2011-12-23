//******************************************************************************
//   MSP430x26x Demo - USCI_A1, Ultra-Low Pwr UART 2400 Echo ISR, 32kHz ACLK
//
//   Description: Echo a received character, RX ISR used. Normal mode is LPM3,
//   USCI_A1 RX interrupt triggers TX Echo.
//   ACLK = BRCLK = LFXT1 = 32768Hz, MCLK = SMCLK = DCO ~1.045MHz
//   Baud rate divider with 32768Hz XTAL @2400 -- from User's Guide
//   //* An external watch crystal is required on XIN XOUT for ACLK *//
//
//                MSP430F261x/241x
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |     P3.6/UCA1TXD|------------>
//            |                 | 2400 - 8N1
//            |     P3.7/UCA1RXD|<------------
//
//   B. Nisarga
//   Texas Instruments Inc.
//   September 2007
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//******************************************************************************
#include  "msp430x26x.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P3SEL = 0xC0;                             // P3.6,7 = USCI_A1 TXD/RXD
  UCA1CTL1 |= UCSSEL_1;                     // CLK = ACLK
  UCA1BR0 = 0x0D;                           // 2400 (see User's Guide)
  UCA1BR1 = 0x00;                           //
  UCA1MCTL = UCBRS_6;                       // Modulation UCBRSx = 3
  UCA1CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  UC1IE |= UCA1RXIE;                        // Enable USCI_A1 RX interrupt

  __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3, interrupts enabled
}

// Echo back RXed character, confirm TX buffer is ready first
#pragma vector=USCIAB1RX_VECTOR
__interrupt void USCI1RX_ISR(void)
{
  while (!(UC1IFG&UCA1TXIFG));               // USCI_A1 TX buffer ready?
  UCA1TXBUF = UCA1RXBUF;                     // TX -> RXed character
}
