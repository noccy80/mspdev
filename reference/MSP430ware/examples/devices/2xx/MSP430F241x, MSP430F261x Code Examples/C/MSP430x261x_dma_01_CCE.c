//******************************************************************************
//   MSP430x26x Demo - DMA0, Repeated Burst to-from RAM, Software Trigger
//
//   Description: A 16 word block from 1400-141fh is transfered to 1420h-143fh
//   using DMA0 in a burst block using software DMAREQ trigger.
//   After each transfer, source, destination and DMA size are
//   reset to inital software setting because DMA transfer mode 5 is used.
//   P1.0 is toggled during DMA transfer only for demonstration purposes.
//   ** RAM location 0x1400 - 0x143f used - make sure no compiler conflict **
//   ACLK = 32kHz, MCLK = SMCLK = default DCO 1.045MHz
//
//                MSP430F261x
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|-->LED
//
//   B. Nisarga
//   Texas Instruments Inc.
//   September 2007
//   Built with CCE Version: 3.2.0
//******************************************************************************
#include "msp430x26x.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= 0x001;                           // P1.0  output
  DMA0SA = (void (*)())0x1400;              // Start block address
  DMA0DA = (void (*)())0x1420;              // Destination block address
  DMA0SZ = 0x0010;                          // Block size
  DMA0CTL = DMADT_5 + DMASRCINCR_3 + DMADSTINCR_3; // Rpt, inc
  DMA0CTL |= DMAEN;                         // Enable DMA0

  while(1)
  {
    P1OUT |= 0x01;                          // P1.0 = 1, LED on
    DMA0CTL |= DMAREQ;                      // Trigger block transfer
    P1OUT &= ~0x01;                         // P1.0 = 0, LED off
  }
}

