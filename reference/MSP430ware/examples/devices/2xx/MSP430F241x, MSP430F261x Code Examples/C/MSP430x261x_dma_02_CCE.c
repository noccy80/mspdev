//******************************************************************************
//   MSP430x26x Demo - DMA0, Repeated single transfer to P1OUT, TACCR2 Trigger
//
//   Description: DMA0 is used to transfer a string byte-by-byte as a repeating
//   block to P1OUT. Timer_A operates continuously with CCR2IFG
//   triggering DMA0. The effect is P1.0/1.1 toggling at different frequencies.
//   ACLK = 32kHz, MCLK = SMCLK = TACLK = default DCO 1.045MHz
//
//               MSP430F261x
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|--> LED
//            |             P1.1|--> 
//
//   B. Nisarga
//   Texas Instruments Inc.
//   September 2007
//   Built with CCE Version: 3.2.0
//******************************************************************************
#include "msp430x26x.h"

const char testconst[6] = { 0x0, 0x3, 0x2, 0x3, 0x0, 0x1 };

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= 0x003;                           // P1.0/1.1 output
  DMACTL0 = DMA0TSEL_1;                     // CCR2 trigger
  DMA0SA = (void (*)())testconst;           // Source block address
  DMA0DA = (void (*)())&P1OUT;              // Destination single address
  DMA0SZ = 0x06;                            // Block size
  DMA0CTL = DMADT_4 + DMASRCINCR_3 + DMASBDB + DMAEN; // Rpt, inc src
  TACTL = TASSEL_2 + MC_2;                  // SMCLK/4, contmode
  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0
}
