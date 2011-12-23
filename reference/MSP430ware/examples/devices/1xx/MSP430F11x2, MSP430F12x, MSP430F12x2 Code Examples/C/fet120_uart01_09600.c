//******************************************************************************
//  MSP-FET430P120 Demo - USART0, UART 9600 Echo ISR, HF XTAL ACLK
//
//  Description: Echo a received character, RX ISR used. Normal mode is LPM0,
//  USART0 RX interrupt triggers TX Echo. Though not required, MCLK = LFXT1.
//  Baud rate divider with 3.58Mhz XTAL @9600 = 3.58MHz/9600 = 372 (0174h)
//  ACLK = MCLK = UCLK0 = LFXT1 = 3.58MHz
//  //* USART0 interrupt flags are in different SFR's from other MSP430's *//
//  //* An external 3.58Mhz XTAL on XIN XOUT is required for ACLK *//
//
//
//               MSP430F123(2)
//             -----------------
//         /|\|              XIN|-
//          | |                 | 3.58MHz
//          --|RST          XOUT|-
//            |                 |
//            |             P3.4|------------>
//            |                 | 9600 - 8N1
//            |             P3.5|<------------
//
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************

#include  <msp430x12x2.h>

void main(void)
{
  volatile unsigned int i;

  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P3SEL |= 0x30;                            // P3.4,5 = USART0 TXD/RXD
  BCSCTL1 |= XTS;                           // ACLK = LFXT1 = HF XTAL

  do
  {
  IFG1 &= ~OFIFG;                           // Clear OSCFault flag
  for (i = 0xFF; i > 0; i--);               // Time for flag to set
  }
  while ((IFG1 & OFIFG) != 0);              // OSCFault flag still set?

  BCSCTL2 |= SELM_3;                        // MCLK = LFXT1 (safe)
  ME2 |= UTXE0 + URXE0;                     // Enabled USART0 TXD/RXD
  UCTL0 |= CHAR;                            // 8-bit character
  UTCTL0 |= SSEL0;                          // UCLK = ACLK
  UBR00 = 0x74;                             // 3.58Mhz/9600 - 372
  UBR10 = 0x01;                             //
  UMCTL0 = 0x00;                            // no modulation
  UCTL0 &= ~SWRST;                          // Initalize USART state machine
  IE2 |= URXIE0;                            // Enabled USART0 RX interrupt

   _BIS_SR(LPM0_bits + GIE);                // Enter LPM0 w/ interrupt
}

#pragma vector=USART0RX_VECTOR
__interrupt void usart0_rx (void)
{
  while (!(IFG2 & UTXIFG0));                // USART0 TX buffer ready?
  TXBUF0 = RXBUF0;                          // RXBUF0 to TXBUF0
}
