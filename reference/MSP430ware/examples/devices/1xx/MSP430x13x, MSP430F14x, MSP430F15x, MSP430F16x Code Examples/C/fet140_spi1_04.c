//******************************************************************************
//   MSP-FET430P140 Demo - USART1, SPI Full-Duplex 3-Wire Master P1.x Exchange
//
//   Description: SPI1 Master communicates at fast as possible, full-duplex with
//   SPI Slave using 3-wire mode. The level on P1.4/5 is TX'ed and RX'ed to P1.0
//   and P1.1. Master will pulse slave Reset on init to insure synch start.
//   Master normal mode is LPM0.
//   ACLK = n/a, MCLK = SMCLK = UCLK = DCO ~ 800kHz
//
//             fet140_slav0               fet140_mstr1
//             MSP430F149 Slave           MSP430F149 Master
//             -----------------          -----------------
//            |              XIN|-    /|\|              XIN|-
//            |                 |      | |                 |
//            |             XOUT|-     --|RST          XOUT|-
//            |                 | /|\    |                 |
//            |              RST|--+<----|P5.0             |
//      LED <-|P1.0             |        |             P1.4|<-
//      LED <-|P1.1             |        |             P1.5|<-
//          ->|P1.4             |        |             P1.0|-> LED
//          ->|P1.5             |        |             P1.1|-> LED
//            |       SIMO0/P3.1|<-------|P5.1/SIMO1       |
//            |       SOMI0/P3.2|------->|P5.2/SOMI1       |
//            |        UCLK/P3.3|<-------|P5.3/UCLK        |
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
  P5SEL |= 0x0E;                            // P5.1,2,3 SPI option select
  P5OUT &= ~0x01;
  P5DIR |= 0x01;                            //Reset Slave
  P5DIR &= ~0x01;
  U1CTL = CHAR + SYNC + MM + SWRST;         // 8-bit, SPI, Master
  U1TCTL = CKPL + SSEL1 + STC;              // Polarity, SMCLK, 3-wire
  U1BR0 = 0x02;                             // SPICLK = SMCLK/2
  U1BR1 = 0x00;
  U1MCTL = 0x00;
  ME2 |= USPIE1;                            // Module enable
  U1CTL &= ~SWRST;                          // SPI enable
  IE2 |= URXIE1 + UTXIE1;                   // RX and TX interrupt enable

  for (i = 0xFFF; i > 0; i--);              // Time for slave to ready
  _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0 w/ interrupt
}

#pragma vector=USART1RX_VECTOR
__interrupt void SPI1_rx (void)
{
  P1OUT = RXBUF1;                           // RXBUF1 to TXBUF1
}

#pragma vector=USART1TX_VECTOR
__interrupt void SPI1_tx (void)
{
  unsigned int i;

  i = P1IN;
  i = i >> 4;
  TXBUF1 = i;                               // Transmit character
}
