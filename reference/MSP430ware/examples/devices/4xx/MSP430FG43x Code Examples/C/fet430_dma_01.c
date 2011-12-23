//******************************************************************************
//  MSP430P430 Demo - DMA0, Repeated Burst to-from RAM, Software Trigger
//
//  Description: A 16 word block from 220h-240h is transferred to 240h-260h
//  using DMA0 in a burst block using software DMAREQ trigger.
//  After each transfer, source, destination and DMA size are
//  reset to inital software setting because DMA transfer mode 5 is used.
//  P5.1 is toggled during DMA transfer only for demonstration purposes.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//  ** RAM location 0x220 - 0x260 used - always make sure no compiler conflict **
//
//               MSP430FG439
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//           |             P5.1|-->LED
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************
#include  <msp430xG43x.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog
  P5DIR |= 0x02;                            // P5.1  output
  DMA0SA = 0x0220;                          // Start block address
  DMA0DA = 0x0240;                          // Destination block address
  DMA0SZ = 0x010;                           // Block size
  DMA0CTL = DMADT_5 + DMASRCINCR_3 + DMADSTINCR_3 + DMAEN; // Rpt, inc SRC, DST

  // Repeat
  for (;;)
  {
    P5OUT |= 0x02;                          // Set P5.1 (LED on)
    DMA0CTL |= DMAREQ;                      // Trigger block transfer
    P5OUT &= ~0x02;                         // Clear P5.1 (LED off)
    _NOP();                                 // SET BREAKPOINT HERE
  }
}
