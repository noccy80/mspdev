//*****************************************************************************
//  MSP-FET430P140 Demo - DMA0, Rpt'd Blk to DAC0, Sine Output, TACCR1, DCO
//
//  Description: DMA0 is used to transfer a sine look-up table word-by-word
//  as a repeating block to DAC12_0. The effect is sine wave output. Timer_A
//  operates in upmode with CCR1 loading DAC12_0 on rising edge and DAC12_OIFG
//  triggering next DMA0 transfer. DAC12_0 uses internal Vref.
//  ACLK= n/a, MCLK= SMCLK= TACLK= default DCO ~ 800kHz
//  //* MSP430F169 Device Required *//
//
//               MSP430F169
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//           |        DAC0/P6.6|--> ~ 1kHz sine wave output
//
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//*****************************************************************************

#include  <msp430x16x.h>

// Definition necessary to compile with CCEv3.2
// Workaround for &DAC12_0DAT
#define _DAC12_0DAT_ 0x01C8                 // Physical address of DAC12_0DAT

//-----------------------------------------------------------------------------
// RAM - 12-bit Sine Lookup table with 32 steps
//-----------------------------------------------------------------------------
static int Sin_tab[32] = {
        2048,
        2447,
        2831,
        3185,
        3495,
        3750,
        3939,
        4056,
        4095,
        4056,
        3939,
        3750,
        3495,
        3185,
        2831,
        2447,
        2048,
        1648,
        1264,
        910,
        600,
        345,
        156,
        39,
        0,
        39,
        156,
        345,
        600,
        910,
        1264,
        1648
};

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog
  ADC12CTL0 = REFON;                        // Internal ref
  DMA0SA = (int) Sin_tab;                   // Source block address
  DMA0DA = (unsigned int)&DAC12_0DAT;        // Destination single address
  DMA0SZ = 0x20;                            // Block size
  DMACTL0 = DMA0TSEL_5;                     // DAC12IFG trigger
  DMA0CTL = DMADT_4 + DMASRCINCR_3 + DMAEN; // Rpt, inc src, word-word
  DAC12_0CTL = DAC12LSEL_2 + DAC12IR + DAC12AMP_5 + DAC12IFG + DAC12ENC; // Config
                                            // **force first interrupt**
  CCTL1 = OUTMOD_3;                         // Set/reset
  CCR1 = 1;                                 // PWM Duty Cycle	
  CCR0 = 25-1;                              // ~1kHz Clock period
  TACTL = TASSEL_2 + MC_1;                  // SMCLK, up-mode

  _BIS_SR(LPM0_bits);                       // Enter LPM0
}
