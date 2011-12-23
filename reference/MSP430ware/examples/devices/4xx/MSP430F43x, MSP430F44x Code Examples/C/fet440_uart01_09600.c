//******************************************************************************
//  MSP-FET430P440 Demo - USART0, 9600 UART Echo ISR, DCO SMCLK
//
//  Description: Echo a received character, RX ISR used. Normal mode is LPM0.
//  USART0 RX interrupt triggers TX Echo.
//  Baud rate divider with 1048576hz = 1048576Hz/9600 = ~109.23 (06Dh|03h)
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//	
//
//                MSP430F449
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |             P2.4|----------->
//            |                 | 9600 - 8N1
//            |             P2.5|<-----------
//
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//*****************************************************************************
#include <msp430x44x.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  FLL_CTL0 |= XCAP18PF;                     // Configure load caps
  P2SEL |= 0x30;                            // P2.4,5 = USART0 TXD/RXD
  ME1 |= UTXE0 + URXE0;                     // Enable USART0 TXD/RXD
  UCTL0 |= CHAR;                            // 8-bit character
  UTCTL0 |= SSEL1;                          // UCLK = SMCLK
  UBR00 = 0x6D;                             // 1MHz 9600
  UBR10 = 0x00;                             // 1MHz 9600
  UMCTL0 = 0x03;                            // modulation
  UCTL0 &= ~SWRST;                          // Initialize USART state machine
  IE1 |= URXIE0;                            // Enable USART0 RX interrupt
  P2DIR |= 0x10;                            // P2.4 output direction

  _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0 w/ interrupt
}

#pragma vector=USART0RX_VECTOR
__interrupt void usart0_rx (void)
{
  while (!(IFG1 & UTXIFG0));                // USART0 TX buffer ready?
  TXBUF0 = RXBUF0;                          // RXBUF0 to TXBUF0
}
