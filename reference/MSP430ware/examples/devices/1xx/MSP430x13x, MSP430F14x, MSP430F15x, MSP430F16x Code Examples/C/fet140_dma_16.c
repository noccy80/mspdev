//******************************************************************************
//  MSP-FET430P140 Demo - DMA0/1/2, USART1 SPI 3-Wire Master P1.x Exchange
//
//  Description: SPI Master communicates at fast as possible, full-duplex with
//  SPI Slave using 3-wire mode. The level on P1.4/5 is TX'ed and RX'ed to P1.0
//  and P1.1. Master will pulse slave Reset on init to insure synch start.
//  With data transfer driven directly by DMA - no CPU resources used.
//  DMA0 trigger from TX read, which uses MPY to shift read P1 left
//  DMA1 trigger from MPY moves shifted P1 data to the USART1 TX buffer
//  DMA2 trigger from USART1 RX buffer moves received data to P1
//  Master mode is LPM0.
//  ACLK = n/a, MCLK = SMCLK = DCO ~ 800kHz, ULCK = external
//  //* Final Production MSP430F16x(x) Device Required *//
//
//             fet140_dma_15              fet140_dma_16
//             MSP430F169 Slave           MSP430F169 Master
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
//            |        UCLK/P3.3|<-------|P5.3/UCLK1       |
//
//  M. Buccini / A. Dannenberg
//  Texas Instruments Inc.
//  November 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.30A
//******************************************************************************

#include  <msp430x16x.h>
// Definition necessary to compile with CCEv3.2
// Workaround for &P1OUT
#define _P1OUT_ 0x0021						// Physical address of P1OUT
void main(void)
{
  volatile unsigned int i;

  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog
  P1OUT = 0x00;                             // P1.0 setup for LED output
  P1DIR |= 0x03;
  P5SEL |= 0x0E;                            // P5.1,2,3 SPI option select
  P5OUT &= ~0x01;
  P5DIR |= 0x01;                            // Reset Slave
  P5DIR &= ~0x01;
  U1CTL = CHAR + SYNC + MM + SWRST;         // 8-bit, SPI, Master
  U1TCTL = CKPL + SSEL1 + STC;              // Polarity, SMCLK, 3-wire
  U1BR0 = 0x02;                             // SPICLK = SMCLK/2
  U1BR1 = 0x00;
  U1MCTL = 0x00;
  ME2 |= USPIE1;                            // Module enable
  U1CTL &= ~SWRST;                          // SPI enable

  for (i = 0xFFF; i > 0; i--);              // Time for slave to ready

  MPY = 0x1000;                             // MPY first operand

// Setup triggers first
  DMACTL0 = DMA2TSEL_9 + DMA1TSEL_11 + DMA0TSEL_10;  // URXIFG1, MPY, UTXIFG1

// RX Store
  DMA2SA = (unsigned int)&U1RXBUF;          // Src address = UART RX Buffer
  DMA2DA = (unsigned int)&P1OUT;            // Dst address = P1
  DMA2SZ = 1;                               // Size in bytes
  DMA2CTL = DMADT_4 + DMASBDB + DMAEN;      // Sng, config

// TX load
  DMA1SA = (unsigned int)&RESHI;            // Src address = multiplier
  DMA1DA = (unsigned int)&U1TXBUF;          // Dst address
  DMA1SZ = 1;                               // Size in bytes
  DMA1CTL = DMADT_4 + DMASBDB + DMAEN;      // Sng, config

// TX Init
  DMA0SA = (unsigned int)&P1IN;             // Src address
  DMA0DA = (unsigned int)&OP2;              // Dst address = multiplier
  DMA0SZ = 1;                               // Size in words
  DMA0CTL = DMADT_4 + DMASBDB + DMALEVEL + DMAEN;  // Sng rpt, config

  _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0 w/ interrupt
}
