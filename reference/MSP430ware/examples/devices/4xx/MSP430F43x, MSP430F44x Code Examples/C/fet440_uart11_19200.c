//******************************************************************************
//  MSP-FET430P440 Demo - USART1, 19200 UART Echo ISR, DCO SMCLK
//
//  Description: Echo a received character, RX ISR used. Normal mode is LPM0.
//  USART1 RX interrupt triggers TX Echo.
//  Baud rate divider with 1048576hz = 1048576Hz/19200 = ~54.61 (036h|6Bh)
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//	
//
//                MSP430F449
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |             P4.0|------------>
//            |                 | 19200 - 8N1
//            |             P4.1|<------------
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
  P4SEL |= 0x03;                            // P4.0,1 = USART1 TXD/RXD
  ME2 |= UTXE1 + URXE1;                     // Enable USART1 TXD/RXD
  UCTL1 |= CHAR;                            // 8-bit character
  UTCTL1 |= SSEL1;                          // UCLK = SMCLK
  UBR01 = 0x36;                             // 1MHz 19200
  UBR11 = 0x00;                             // 1MHz 19200
  UMCTL1 = 0x6B;                            // Modulation
  UCTL1 &= ~SWRST;                          // Initalize USART state machine
  IE2 |= URXIE1;                            // Enable USART1 RX interrupt

  _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0 w/ interrupt
}

#pragma vector=USART1RX_VECTOR
__interrupt void usart1_rx(void)
{
  while (!(IFG2 & UTXIFG1));                // USART1 TX buffer ready?
  TXBUF1 = RXBUF1;                          // RXBUF1 to TXBUF0
}
