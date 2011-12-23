//******************************************************************************
//   MSP430xG461x Demo - DMA0, Repeated Block to P5OUT, TACCR2 Trigger
//
//   Description: DMA0 is used to transfer a string byte-by-byte as a repeating
//   block to P5OUT. Timer_A operates continuously with CCR2IFG
//   triggering DMA0. The effect is P5.0/5.1 toggling at different frequencies.
//   ACLK = 32kHz, MCLK = SMCLK = TACLK = default DCO 1048576Hz
//
//               MSP430xG461x
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |             P5.0|-->
//            |             P5.1|--> LED
//
//   A. Dannenberg/ M. Mitchell
//   Texas Instruments Inc.
//   October 2006
//   Built with CCE Version: 3.2.0
//******************************************************************************
#include "msp430xG46x.h"

const char testconst[6] = { 0x0, 0x3, 0x2, 0x3, 0x0, 0x1 };

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P5DIR |= 0x003;                           // P5.0/5.1 output
  DMACTL0 = DMA0TSEL_1;                     // CCR2 trigger
  DMA0SA = (void (*)())testconst;                  // Source block address
  DMA0DA = (void (*)())&P5OUT;                     // Destination single address
  DMA0SZ = 0x06;                            // Block size
  DMA0CTL = DMADT_4 + DMASRCINCR_3 + DMASBDB + DMAEN; // Rpt, inc src
  TACTL = TASSEL_2 + MC_2;                  // SMCLK/4, contmode
  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0
}
