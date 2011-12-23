//******************************************************************************
//   MSP430x26x Demo - DMA0/1, Rpt'd single transfer to DAC12_0/1, Sin/Cos, TACCR1, XT2
//
//   Description: DMA0 and DMA1 are used to transfer a sine and cos look-up
//   table word-by-word as a repeating block to DAC12_0 and DAC12_1. The effect
//   is sine and cos wave outputs. Timer_A operates in upmode with TACCR1
//   loading DAC12_0 amd DAC12_1 on rising edge and DAC12_OIFG triggering next
//   DMA transfers. DAC12_0 and DAC12_1 are grouped for jitter-free operation.
//   ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//   //* An external watch crystal between XIN & XOUT is required for ACLK *//
//
//                MSP430F261x
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |        DAC0/P6.6|--> ~ 10kHz sine wave
//            |        DAC1/P6.7|--> ~ 10kHz cos wave
//
//   B. Nisarga
//   Texas Instruments Inc.
//   September 2007
//   Built with CCE Version: 3.2.0
//******************************************************************************
#include "msp430x26x.h"

//------------------------------------------------------------------------------
// 12-bit Sine Lookup table with 32 steps
//------------------------------------------------------------------------------
const int Sin_tab[32] = { 2048, 2447, 2831, 3185, 3495, 3750, 3939, 4056,
                          4095, 4056, 3939, 3750, 3495, 3185, 2831, 2447,
                          2048, 1648, 1264,  910,  600,  345,  156,   39,
                             0,   39,  156,  345,  600,  910, 1264, 1648
                        };
//------------------------------------------------------------------------------
// 12-bit Cosine Lookup table with 32 steps
//------------------------------------------------------------------------------
const int Cos_tab[32] = { 1648, 1264,  910,  600,  345,  156,   39,    0,
                            39,   56,  345,  600,  910, 1264, 1648, 2048,
                          2447, 2831, 3185, 3495, 3750, 3939, 4056, 4095,
                           4056, 3939, 3750, 3495, 3185, 2831, 2447, 2048
                        };

void main(void)
{
  volatile unsigned int i;
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer

  ADC12CTL0 = REF2_5V + REFON;              // Internal 2.5V ref
  TACCR0 = 13600;                           // Delay to allow Ref to settle
  TACCTL0 |= CCIE;                          // Compare-mode interrupt.
  TACTL = TACLR + MC_1 + TASSEL_2;          // Up mode, SMCLK
  
  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0, enable interrupts
  TACCTL0 &= ~CCIE;                         // Disable timer interrupt
  __disable_interrupt();                    // Disable Interrupts
  DMACTL0 = DMA0TSEL_5 + DMA1TSEL_5;        // DAC12IFG triggers
  DMA0SA = (void (*)())Sin_tab;             // Source block address
  DMA0DA = (void (*)())&DAC12_0DAT;          // Destination single address
  DMA0SZ = 0x020;                           // Block size
  DMA0CTL = DMADT_4 + DMASRCINCR_3 + DMAEN; // Rpt, inc src, word-word
  DMA1SA = (void (*)())Cos_tab;             // Source block address
  DMA1DA = (void (*)())&DAC12_1DAT;         // Destination single address
  DMA1SZ = 0x020;                           // Block size
  DMA1CTL = DMADT_4 + DMASRCINCR_3 + DMAEN; // Rpt, inc src, word-word
  DAC12_0CTL = DAC12LSEL_2 + DAC12IR + DAC12AMP_5 + DAC12IFG + DAC12ENC + DAC12GRP;
  DAC12_1CTL = DAC12LSEL_2 + DAC12IR + DAC12AMP_5 + DAC12IFG + DAC12ENC;
  TACCTL1 = OUTMOD_3;                       // TACCR1 set/reset
  TACCR1 = 01;                              // TACCR1 PWM Duty Cycle
  TACCR0 = 025-1;                           // Clock period of TACCR0
  TACTL = TASSEL_2 + MC_1;                  // SMCLK, contmode

  while(1)
  {
    __bis_SR_register(LPM0_bits + GIE);     // Enter LPM0
  }
}

// Delay for Ref to settle
#pragma vector = TIMERA0_VECTOR
__interrupt void TA0_ISR(void)
{
  TACTL = 0;                                // Clear Timer_A control registers
  __bic_SR_register_on_exit(LPM0_bits);     // Exit LPMx, interrupts enabled
}
