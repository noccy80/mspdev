//******************************************************************************
//   MSP-FET430P140 Demo - USART0, SPI Full-Duplex 3-Wire Master P1.x Exchange
//
//   Description: SPI Master communicates at fast as possible, full-duplex with
//   SPI Slave using 3-wire mode. The level on P1.4/5 is TX'ed and RX'ed to P1.0
//   and P1.1. Master will pulse slave Reset on init to insure synch start.
//   Master normal mode is LPM0.
//   ACLK = n/a, MCLK = SMCLK = UCLK = DCO ~ 800kHz
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
//            |       SIMO0/P3.1|<-------|P3.1/SIMO0       |
//            |       SOMI0/P3.2|------->|P3.2/SOMI0       |
//            |        UCLK/P3.3|<-------|P3.3/UCLK0       |
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************

#include  <msp430x14x.h>

void main(void)
{
  volatile unsigned int i;

  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog
  P1OUT = 0x00;                             // P1.0 setup for LED output
  P1DIR |= 0x03;
  P3SEL |= 0x0E;                            // P3.1,2,3 SPI option select
  P3OUT &= ~0x01;
  P3DIR |= 0x01;                            // Reset Slave
  P3DIR &= ~0x01;
  U0CTL = CHAR + SYNC + MM + SWRST;         // 8-bit, SPI, Master
  U0TCTL = CKPL + SSEL1 + STC;              // Polarity, SMCLK, 3-wire
  U0BR0 = 0x02;                             // SPICLK = SMCLK/2
  U0BR1 = 0x00;
  U0MCTL = 0x00;
  ME1 |= USPIE0;                            // Module enable
  U0CTL &= ~SWRST;                          // SPI enable
  IE1 |= URXIE0 + UTXIE0;                   // RX and TX interrupt enable

  for (i = 0xFFF; i > 0; i--);              // Time for slave to ready
  _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0 w/ interrupt
}

#pragma vector=USART0RX_VECTOR
__interrupt void SPI0_rx (void)
{
  P1OUT = RXBUF0;                           // RXBUF0 to TXBUF0
}

#pragma vector=USART0TX_VECTOR
__interrupt void SPI0_tx (void)
{
  unsigned int i;

  i = P1IN;
  i = i >> 4;
  TXBUF0 = i;                               // Transmit character
}
