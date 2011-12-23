//******************************************************************************
//   MSP430F22x4 Demo - USCI_A0, UART 19200 Echo ISR, HF XTAL SMCLK
//
//   Description: This program will echo a received character, RX interrupt
//   service used. XT1 oscillator used in this example.
//   ACLK = MCLK = SMCLK = BRCLK = LFXT1CLK = 8MHz
//   Baud rate divider with 8MHz XTAL @19200 = 8MHz/19200 = ~416.6
//   //* An external 8MHz XTAL on XIN XOUT is required for LFXT1CLK *//
//
//                MSP430F22x4
//             -----------------
//         /|\|              XIN|-
//          | |                 | 8MHz
//          --|RST          XOUT|-
//            |                 |
//            |     P3.4/UCA0TXD|------------>
//            |                 | 19200 - 8N1
//            |     P3.5/UCA0RXD|<------------
//
//   A. Dannenberg
//   Texas Instruments Inc.
//   January 2007
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include  "msp430x22x4.h"

volatile unsigned int i;

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

  BCSCTL1 |= XTS;                           // ACLK = LFXT1 = HF XTAL
  BCSCTL3 |= LFXT1S1;                       // 3 – 16MHz crystal or resonator
  do
  {
    IFG1 &= ~OFIFG;                         // Clear OSCFault flag
    for (i = 0xFF; i > 0; i--);             // Time for flag to set
  }
  while (IFG1 & OFIFG);                     // OSCFault flag still set?
  BCSCTL2 |= SELM_3 + SELS;                 // MCLK = SMCLK = LFXT1 (safe)

  P3SEL = 0x30;                             // P3.4,5 = USCI_A0 TXD/RXD
  UCA0CTL1 |= UCSSEL_2;                     // SMCLK
  UCA0BR0 = 160;                            // 8MHz/19200 = ~416.6
  UCA0BR1 = 1;                              //
  UCA0MCTL = UCBRS2 + UCBRS1;               // Modulation UCBRSx = 6
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  IE2 |= UCA0RXIE;                          // Enable USCI_A0 RX interrupt

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0, interrupts enabled
}

//  Echo back RXed character, confirm TX buffer is ready first
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
  while (!(IFG2 & UCA0TXIFG));              // USCI_A0 TX buffer ready?
  UCA0TXBUF = UCA0RXBUF;                    // TX -> RXed character
}
