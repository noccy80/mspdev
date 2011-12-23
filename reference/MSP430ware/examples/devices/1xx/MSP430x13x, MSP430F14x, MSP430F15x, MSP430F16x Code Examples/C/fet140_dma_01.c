//******************************************************************************
//  MSP-FET430P140 Demo - DMA0, Repeated Burst to-from RAM, Software Trigger
//
//  Description: A 16 word block from 220h-240h is transfered to 240h-260h
//  using DMA0 in a burst block using software DMAREQ trigger.
//  After each transfer, source, destination and DMA size are
//  reset to inital software setting because DMA transfer mode 5 is used.
//  P1.0 is toggled durring DMA transfer only for demonstration purposes.
//  * RAM location 0x220 - 0x260 used - always make sure no compiler conflict *
//  ACLK = n/a, MCLK = SMCLK = default DCO ~ 800k
//  //* MSP430F169 Device Required *//
//
//               MSP430F169
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//           |             P1.0|-->LED
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************

#include  <msp430x16x.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog
  P1DIR |= 0x01;                            // P1.0  output
  DMA0SA = 0x0220;                          // Start block address
  DMA0DA = 0x0240;                          // Destination block address
  DMA0SZ = 0x010;                           // Block size
  DMA0CTL = DMADT_5 + DMASRCINCR_3 + DMADSTINCR_3 + DMAEN; // Rpt, inc SRC, DST

  for (;;)                                  // Repeat
  {
    P1OUT |= 0x01;                          // Set P1.0 (LED on)
    DMA0CTL |= DMAREQ;                      // Trigger block transfer
    P1OUT &= ~0x01;                         // Clear P1.0 (LED off)
  }
}
