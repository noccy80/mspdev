//******************************************************************************
//  MSP-FET430P140 Demo - USART0, SPI Full-Duplex 3-Wire Slave P1.x Exchange
//
//  Description: SPI Master communicates at fast as possible, full-duplex with
//  SPI Slave using 3-wire mode. The level on P1.4/5 is TX'ed and RX'ed to P1.0
//  and P1.1. Master will pulse slave Reset on init to insure synch start.
//  Slave normal mode is LPM4.
//  ACLK = n/a, MCLK = SMCLK = DCO ~ 800kHz, ULCK = external
//
//             fet140_slav0               fet140_mstr0
//             MSP430F169 Slave           MSP430F169 Master
//             -----------------          -----------------
//            |              XIN|-    /|\|              XIN|-
//            |                 |      | |                 |
//            |             XOUT|-     --|RST          XOUT|-
//            |                 | /|\    |                 |
//            |              RST|--+<----|P3.0             |
//      LED <-|P1.0             |        |             P1.4|<-
//      LED <-|P1.1             |        |             P1.5|<-
//          ->|P1.4             |        |             P1.0|-> LED
//          ->|P1.5             |        |             P1.1|-> LED
//            |       SIMO0/P3.1|<-------|P3.1             |
//            |       SOMI0/P3.2|------->|P3.2             |
//            |        UCLK/P3.3|<-------|P3.3             |
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************

#include  <msp430x14x.h>

void main(void)
{

  WDTCTL = WDTPW + WDTHOLD;                     // Stop watchdog
  P1OUT = 0x00;                                 // P1.0 setup for LED output
  P1DIR |= 0x03;
  P3SEL |= 0x0E;                                // P3.1,2,3 SPI option select
  U0CTL = CHAR + SYNC + SWRST;                  // 8-bit, SPI
  U0TCTL = CKPL + STC;                          // Polarity, 3-wire
  U0BR0 = 0x02;                                 // SPICLK = SMCLK/2
  U0BR1 = 0x00;
  U0MCTL = 0x00;
  ME1 |= USPIE0;                                // Module enable
  U0CTL &= ~SWRST;                              // SPI enable
  IE1 |= URXIE0 + UTXIE0;                       // RX and TX interrupt enable

  _BIS_SR(LPM4_bits + GIE);                     // Enter LPM4 w/ interrupt
}

#pragma vector=USART0RX_VECTOR
__interrupt void SPI0_rx (void)
{
  P1OUT = RXBUF0;                               // RXBUF0 to TXBUF0
}

#pragma vector=USART0TX_VECTOR
__interrupt void SPI0_tx (void)
{
  unsigned int i;

  i = P1IN;
  i = i >> 4;
  TXBUF0 = i;                                   // Transmit character
}
