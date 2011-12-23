//******************************************************************************
//   MSP430x26x Demo - DMA2, Rpt'd single transfer to DAC1, 8-Bit Sine, TBCCR2, DCO
//
//   Description: DMA2 is used to transfer a sine look-up table byte-by-byte
//   as a repeating block to DAC12_1. The effect is a sine wave output. Timer_B
//   operates in upmode with TBCCR2 loading DAC12_1 on the rising edge, CCR2_CCIFG
//   triggering the next DMA2 transfer. Use external reference on VeRef+.
//   ACLK = 32kHz, MCLK = SMCLK = TBCLK = default DCO 1.045MHz
//
//                MSP430F261x
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//   Ext Ref->|VeRef+  DAC1/P6.7|--> ~ 1kHz sine wave output
//
//
//   B. Nisarga
//   Texas Instruments Inc.
//   September 2007
//   Built with IAR Embedded Workbench Version: 3.42A
//******************************************************************************
#include "msp430x26x.h"

//------------------------------------------------------------------------------
// 8-bit Sine Lookup table with 32 steps
//------------------------------------------------------------------------------
const char Sin_tab[32] = { 128, 152, 176, 198, 218, 234, 245, 253,
                           255, 253, 245, 234, 218, 198, 176, 152,
                           128, 103,  79,  57,  37,  21,  10,   2,
                             0,   2,  10,  21,  37,  57,  79, 103
                         };

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  DMA2SA = (int)Sin_tab;                    // Source block address
  DMA2DA = DAC12_1DAT_;                     // Destination single address
  DMA2SZ = 0x020;                           // Block size
  DMACTL0 = DMA2TSEL_2;                     // TBCCR2 trigger
  DMA2CTL = DMASBDB + DMADT_4 + DMASRCINCR_3 + DMAEN; // Rpt, inc src, byte-byte
  DAC12_1CTL = DAC12SREF_2 + DAC12RES + DAC12LSEL_3 + DAC12IR + DAC12AMP_5 + DAC12ENC;
  TBCCTL2 = OUTMOD_7;                       // Reset/set
  TBCCR2 = 01;                              // PWM Duty Cycle
  TBCCR0 = 032 - 1;                         // Clock period of TBCCR0
  TBCTL = TBSSEL_2 + MC_1;                  // SMCLK, up mode
  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0
}
