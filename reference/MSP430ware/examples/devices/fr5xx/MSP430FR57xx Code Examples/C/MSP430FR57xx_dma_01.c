//******************************************************************************
//  MSP430FR57xx Demo - DMA0, Repeated Block to-from RAM, Software Trigger
//
//  Description: A 16 word block from 1C20-1C2Fh is transfered to 1C40h-1C4fh
//  using DMA0 in a burst block using software DMAREQ trigger.
//  After each transfer, source, destination and DMA size are
//  reset to inital software setting because DMA transfer mode 5 is used.
//  P1.0 is toggled durring DMA transfer only for demonstration purposes.
//  ** RAM location 0x1C00 - 0x1C3F used - make sure no compiler conflict **
//   MCLK = SMCLK = default DCO 
// 
//
//                 MSP430FR5739
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|-->LED
//
//   Priya Thanigai
//   Texas Instruments Inc.
//   August 2010
//   Built with IAR Embedded Workbench Version: 5.10 & Code Composer Studio V4.0
//******************************************************************************
#include "msp430fr5739.h"

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  P1DIR |= 0x01;                            // P1.0 output
  __data16_write_addr((unsigned short) &DMA0SA,(unsigned long) 0x1C20);
                                            // Source block address
  __data16_write_addr((unsigned short) &DMA0DA,(unsigned long) 0x1C40);
                                            // Destination single address
  DMA0SZ = 16;                              // Block size
  DMA0CTL = DMADT_5+DMASRCINCR_3+DMADSTINCR_3; // Rpt, inc
  DMA0CTL |= DMAEN;                         // Enable DMA0

  while(1)
  {
    P1OUT |= 0x01;                          // P1.0 = 1, LED on
    DMA0CTL |= DMAREQ;                      // Trigger block transfer
    P1OUT &= ~0x01;                         // P1.0 = 0, LED off
  }
}
