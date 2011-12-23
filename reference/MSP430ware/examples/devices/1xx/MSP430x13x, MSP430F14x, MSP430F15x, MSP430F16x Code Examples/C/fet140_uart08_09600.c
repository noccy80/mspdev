//******************************************************************************
//   MSP-FET430P140 Demo - USART0, UART 9600 Full-Duplex Transceiver, 32K ACLK
//
//  Description: UART0 communicates continously as fast as possible full-duplex
//  with another device. Normal mode is LPM3, with activity only during RX and
//  TX ISR's. The TX ISR indicates the UART is ready to send another character.
//  The RX ISR indicates the UART has received a character. At 9600 baud, a full
//  character is tranceived ~1ms.
//  The levels on P1.4/5 are TX'ed. RX'ed value is displayed on P1.0/1.1
//  ACLK = UCLK1 = LFXT1 = 32768, MCLK = SMCLK = DCO~ 800k
//  Baud rate divider with 32768hz XTAL @9600 = 32768Hz/9600 = 3.41 (000Dh 4Ah )
//  //* An external watch crystal is required on XIN XOUT for ACLK *//	
//
//                MSP430F149                   MSP430F149
//             -----------------            -----------------
//            |              XIN|-      /|\|              XIN|-
//            |                 | 32KHz  | |                 | 32KHz
//            |             XOUT|-       --|RST          XOUT|-
//            |                 | /|\      |                 |
//            |              RST|---       |                 |
//            |                 |          |                 |
//          ->|P1.4             |          |             P1.0|-> LED
//          ->|P1.5             |          |             P1.1|-> LED
//      LED <-|P1.0             |          |             P1.4|<-
//      LED <-|P1.1             |          |             P1.5|<-
//            |        UTXD/P3.4|--------->|P3.5             |
//            |                 | 9600 8N1 |                 |
//            |        URXD/P3.5|<---------|P3.4             |
//
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************

#include  <msp430x14x.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1OUT = 0x00;                             // P1.0/1 setup for LED output
  P1DIR = 0x03;
  P3SEL |= 0x30;                            // P3.4,5 = USART0 TXD/RXD
  ME1 |= UTXE0 + URXE0;                     // Enable USART0 TXD/RXD
  UCTL0 |= CHAR;                            // 8-bit character
  UTCTL0 |= SSEL0;                          // UCLK = ACLK
  UBR00 = 0x03;                             // 32k/9600 - 3.41
  UBR10 = 0x00;                             //
  UMCTL0 = 0x4a;                            // Modulation
  UCTL0 &= ~SWRST;                          // Initialize USART state machine
  IE1 |= URXIE0 +  UTXIE0;                  // Enable USART0 RX/TX interrupt

  _BIS_SR(LPM3_bits + GIE);                 // Enter LPM3 w/ interrupt
}

#pragma vector=USART0RX_VECTOR
__interrupt void usart0_rx (void)
{
  P1OUT = RXBUF0;                           // RXBUF0 to TXBUF0
}

#pragma vector=USART0TX_VECTOR
__interrupt void usart0_Tx (void)
{
  unsigned int i;

  i = P1IN;
  i = i >> 4;
  TXBUF0 = i;                               // Transmit character
}
