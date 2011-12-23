//******************************************************************************
//  MSP-FET430P120 Demo - USART0, UART 9600 Echo ISR, No XTAL, Rosc DCO Only
//
//  Description: Echo a received character, USART0 RX ISR at high-speed using
//  no XTAL and external resistor for DCO stabilized. DCO used for UART baud
//  generation. On a valid RX character, character echoed back. Using a 100k
//  resistor on ROSC, with default DCO setting, set DCOCLK ~ 2MHz.
//  Baud rate divider with 2Mhz = 2MHz/9600 ~ 208 (00D0h)
//  ACLK = n/a  MCLK = SMCLK = UCLK0 = DCOCLK  ~ 2MHz
//  //* Use of external resistor reduces temperature sensitivity of DCOCLK *//
//
//               MSP430F123(2)
//            -----------------
//  /|\   /|\|              XIN|-
//   |     | |                 |
//  100k   --|RST          XOUT|-
//   |       |                 |
//   +-------|P2.5/ROSC    P3.4|------------>
//           |                 |  9600 - 8N1
//           |             P3.5|<------------
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
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P3SEL |= 0x30;                            // P3.4,5 = USART0 TXD/RXD
  BCSCTL2 |= DCOR;                          // Rosc
  _BIS_SR(OSCOFF);                          // XTAL not used
  ME2 |= UTXE0 + URXE0;                     // Enabled USART0 TXD/RXD
  UCTL0 |= CHAR;                            // 8-bit character
  UTCTL0 |= SSEL1;                          // UCLK = SMCLK
  UBR00 = 0xD0;                             // 2MHz 9600
  UBR10 = 0x00;                             //
  UMCTL0 = 0x00;                            // no modulation
  UCTL0 &= ~SWRST;                          // Initialize USART state machine
  IE2 |= URXIE0;                            // Enable USART0 RX interrupt

  _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0 w/ interrupt
}

#pragma vector=USART0RX_VECTOR
__interrupt void usart0_rx (void)
{
  while (!(IFG2 & UTXIFG0));                // USART0 TX buffer ready?
  TXBUF0 = RXBUF0;                          // RXBUF0 to TXBUF0
}


