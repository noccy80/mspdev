//******************************************************************************
//  MSP430xG461x Demo - DMA0, ADC12 A10 Block Xfer to RAM, TBCCR1, DCO
//
//  Description: A 0x20 word block of data is sampled and recorded into RAM
//  starting at address 01500h from the ADC12 channel 10 (temp sensor) using the
//  Record() function. Timer_B CCR1 begins the ADC12 sample period, CCR0 the hold
//  and conversion start. Timer_B operates in the up mode with CCR0 defining the
//  sample period. DMA0 will automatically transfer each ADC12 conversion code
//  to memory when complete. At the end of the recording block, DMA0 will issue
//  an interrupt existing the function.
//  In the example the RAM block use to record the ADC12 data begins at 0x1500.
//  P5.1 is toggled during DMA transfer only for demonstration purposes.
//  ACLK = 32kHz, MCLK = SMCLK = default DCO 1048576Hz
//
//              MSP430xG461x
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32kHz
//         --|RST          XOUT|-
//           |                 |
//           |             P5.1|-->LED
//
//
//   A. Dannenberg/ M. Mitchell
//   Texas Instruments Inc.
//   October 2006
//   Built with IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430xG46x.h"

void Record(void);

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P5DIR |= 0x02;                            // Set P5.1 to output direction
  while(1)
    Record();
}

void Record(void)
{
  volatile int i;
  ADC12MCTL0 = SREF_1 + INCH_10;            // Channel A10, Vref+
  ADC12IFG = 0;
  ADC12CTL1 = SHS_3 + CONSEQ_2;             // S&H TB.OUT1, rep. single chan
  ADC12CTL0 = REF2_5V + REFON + ADC12ON + ENC;    // VRef ADC12 on, enabled
  i = 0x03600;                              // Delay for needed ref start-up.
  while(i--);                               // See datasheet for details.
  TBCCR0 = 100;                             // Init TBCCR0 w/ sample prd
  TBCCR1 = 70;                              // Trigger for ADC12 SC
  TBCCTL1 = OUTMOD_7;                       // Reset OUT1 on EQU1, set on EQU0
  DMA0SA = ADC12MEM0_;                      // Src address = ADC12 module
  DMA0DA = 0x01500;                         // Dst address = RAM memory
  DMA0SZ = 0x020;                           // Size in words
  DMACTL0 = DMA0TSEL_6;                     // ADC12IFGx triggers DMA0
  DMA0CTL = DMADSTINCR_3 + DMAIE + DMAEN;   // Config
  P5OUT |= 0x02;                            // Start recording and enter LPM0
  TBCTL = TBSSEL_2 + MC_1 + TBCLR;          // SMCLK, clear TBR, up mode
  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0, enable interrupts
  ADC12CTL1 &= ~CONSEQ_2;                   // Stop conversion immediately
  ADC12CTL0 &= ~ENC;                        // Disable ADC12 conversion
  ADC12CTL0 = 0;                            // Switch off ADC12 & ref voltage
  TBCTL = 0;                                // Disable Timer_B
  P5OUT &= ~0x02;                           // Clear P5.1 (LED Off)
}

#pragma vector = DMA_VECTOR
__interrupt void DMA_ISR(void)
{
  DMA0CTL &= ~DMAIFG;                       // Clear DMA0 interrupt flag
  __bic_SR_register_on_exit(LPM0_bits);     // Exit LPMx, interrupts enabled
}

