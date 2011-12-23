//******************************************************************************
//  MSP-FET430P430 Demo - DMA0, Rpt'd Blk to DAC1 8-bit Sine Output, TBCCR2, DCO
//
//  Description: DMA0 is used to transfer a sine look-up table byte-by-byte
//  as a repeating block to DAC12_1. The effect is sine wave output. Timer_B
//  operates in upmode with CCR2 loading DAC12_1 on rising edge, CCR2_CCIFG
//  triggering next DMA0 transfer. Use external reference on VeRef+.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//               MSP430FG439
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//  Ext Ref->|VeRef+  P6.7/DAC1|--> ~ 1kHz sine wave output
//
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************
#include  <msp430xG43x.h>

//------------------------------------------------------------------------------
// Flash - 8-bit Sine Lookup table with 32 steps
//------------------------------------------------------------------------------
const char Sin_tab[32] = { 128, 152, 176, 198, 218, 234, 245, 253, 255, 253,
245, 234, 218, 198, 176, 152, 128, 103, 79, 57, 37, 21, 10, 2, 0, 2, 10, 21,
37, 57, 79, 103 };

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog
  DMA0SA = (int) Sin_tab;                   // Source block address
  DMA0DA = (unsigned int)&DAC12_1DAT;       // Destination single address
  DMA0SZ = 0x20;                            // Block size
  DMACTL0 = DMA0TSEL_2;                     // Timer_B.CCIFG2 trigger
  DMA0CTL = DMASBDB + DMADT_4 + DMASRCINCR_3 + DMAEN;
  DAC12_1CTL = DAC12SREF_2+DAC12RES+DAC12LSEL_3+DAC12IR+DAC12AMP_5+DAC12ENC;

  TBCCTL2 = OUTMOD_7;                       // Reset/set
  TBCCR2 = 1;                               // PWM Duty Cycle	
  TBCCR0 = 32-1;                            // ~1kHz Clock period
  TBCTL = TBSSEL_2 + MC_1;                  // SMCLK, up mode

  _BIS_SR(LPM0_bits);                       // Enter LPM0
}

