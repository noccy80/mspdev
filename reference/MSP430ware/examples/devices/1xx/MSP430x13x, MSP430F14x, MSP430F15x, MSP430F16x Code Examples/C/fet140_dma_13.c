//******************************************************************************
//  MSP-FET430P140 Demo - DMA0/1/2, USART0 UART 9600 Full-Duplex Transcvr, ACLK
//
//  Description: UART0 communicates continously as fast as possible full-duplex
//  with another device. With data transfer driven directly by DMA - no CPU
//  resources used.
//  DMA0 trigger from TX ready, which uses MPY to shift read P1 left
//  DMA1 trigger from MPY moves shifted P1 data to the USART0 TX buffer
//  DMA2 trigger from USART RX0 buffer moves received data to P1
//  The levels on P1.4/5 are TX'ed. RX'ed value is displayed on P1.0/1.
//  ACLK = UCLK1 = LFXT1 = 32768, MCLK = SMCLK = DCO~ 800k
//  Baud rate divider with 32768hz XTAL @9600 = 32768Hz/9600 = 3.41 (000Dh 4Ah )
//  //* An external watch crystal is required on XIN XOUT for ACLK *//	
//  //* Final Production MSP430F16x(x) Device Required *//
//
//                MSP430F169                   MSP430F169
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
//            |        UTXD/P3.4|--------->|P3.5/URXD        |
//            |                 | 9600 8N1 |                 |
//            |        URXD/P3.5|<---------|P3.4/UTXD        |
//
//
//  M. Buccini / A. Dannenberg
//  Texas Instruments Inc.
//  November 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.30A
//******************************************************************************

#include  <msp430x16x.h>

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

  MPY = 0x1000;                             // MPY first operand

  DMACTL0 = DMA2TSEL_3 + DMA1TSEL_11 + DMA0TSEL_4;  // URXIFG0, MPY, UTXIFG0

// TX load
  DMA1SA = (unsigned int)&RESHI;            // Src address = multiplier
  DMA1DA = (unsigned int)&U0TXBUF;          // Dst address = UART TX Buffer
  DMA1SZ = 1;                               // Size in bytes
  DMA1CTL = DMADT_4 + DMASBDB + DMAEN;      // Sng, config

// TX Init
  DMA0SA = (unsigned int)&P1IN;             // Src address
  DMA0DA = (unsigned int)&OP2;              // Dst address = multiplier
  DMA0SZ = 1;                               // Size in bytes
  DMA0CTL = DMADT_4 + DMASBDB + DMALEVEL + DMAEN;  // Sng rpt, config

// RX Store
  DMA2SA = (unsigned int)&U0RXBUF;          // Src address = UART RX Buffer
  DMA2DA = (unsigned int)&P1OUT;            // Dst address = P1
  DMA2SZ = 1;                               // Size in bytes
  DMA2CTL = DMADT_4 + DMASBDB + DMAEN;      // Sng, config

  _BIS_SR(LPM3_bits + GIE);                 // Enter LPM3 w/ interrupt
}
