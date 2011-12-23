//******************************************************************************
//  MSP-FET430P430 Demo - DMA0, Repeated Block To P5OUT, TACCR2, DCO
//
//  Description: DMA0 is used to transfer a string byte-by-byte as a repeating
//  block to P5OUT. Timer_A operates continuously with CCR2IFG
//  triggering DMA0. The effect is P5.1/5.2 toggling at different frequencies.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//               MSP430FG439
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//           |             P5.1|--> LED
//           |             P5.2|-->
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************
#include  <msp430xG43x.h>

const unsigned char testconst[] = { 0x00, 0x06, 0x04, 0x06, 0x00, 0x02 };

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog
  P5DIR |= 0x06;                            // P5.1/5.2 output
  DMACTL0 = DMA0TSEL_1;                     // CCR2IFG trigger
  DMA0SA = (unsigned int)testconst;         // Source block address
  DMA0DA = (unsigned int)&P5OUT;            // Dest single address
  DMA0SZ = sizeof testconst;                // Block size
  DMA0CTL = DMADT_4 + DMASRCINCR_3 + DMASBDB + DMAEN; // Rpt, inc src, enable
  TACTL = TASSEL_2 + MC_2;                  // SMCLK, cont-mode

  _BIS_SR(LPM0_bits);                       // Enter LPM0
}


