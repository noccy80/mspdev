//******************************************************************************
//   MSP430xG461x Demo - DMA0, Repeated Burst to-from RAM, Software Trigger
//
//   Description: A 16 word block from 1400-141fh is transfered to 1420h-143fh
//   using DMA0 in a burst block using software DMAREQ trigger.
//   After each transfer, source, destination and DMA size are
//   reset to inital software setting because DMA transfer mode 5 is used.
//   P5.1 is toggled durring DMA transfer only for demonstration purposes.
//   ** RAM location 0x1400 - 0x143f used - make sure no compiler conflict **
//   ACLK = 32kHz, MCLK = SMCLK = default DCO 1048576Hz
//
//                MSP430xG461x
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |             P5.1|-->LED
//
//   A. Dannenberg/ M. Mitchell
//   Texas Instruments Inc.
//   October 2006
//   Built with CCE Version: 3.2.0
//******************************************************************************
#include "msp430xG46x.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P5DIR |= 0x002;                           // P1.0  output
  DMA0SA = (void (*)( )) 0x1400;           	// Start block address
  DMA0DA = (void (*)( )) 0x1420;            // Destination block address
  DMA0SZ = 0x0010;                          // Block size
  DMA0CTL = DMADT_5 + DMASRCINCR_3 + DMADSTINCR_3 + DMAEN; // Rpt, inc
  DMA0CTL |= DMAEN;                         // Enable DMA0

  while(1)
  {
    P5OUT |= 0x02;                          // P5.1 = 1, LED on
    DMA0CTL |= DMAREQ;                      // Trigger block transfer
    P5OUT &= ~0x02;                         // P5.1 = 0, LED off
  }
}

