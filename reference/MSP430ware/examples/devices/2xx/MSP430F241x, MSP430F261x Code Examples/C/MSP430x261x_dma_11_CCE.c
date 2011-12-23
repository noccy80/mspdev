//*******************************************************************************
//  MSP430x26x Demo - DMA0/1, ADC12 A10 rpt single transfer to MPY/RAM, TBCCR1, DCO
//
//  Description: A 0x20 word block of data is sampled and recorded into RAM
//  from the ADC12 channel 10 the integrated temperature sensor using the
//  Record() function. Timer_B CCR1 begins the ADC12 sample period, CCR0 the hold
//  and conversion start. Timer_B operates in the up mode with CCR0 defining the
//  sample period.
//  DMA0 will automatically transfer each ADC12 conversion code to the HW MPY
//  which will preform MPY x 0x1000 - this will rotate the operand 12-bits to
//  the left. DMA1 uses the multiplier ready trigger to move the lower byte of
//  the upper operand of the multiplier result to a RAM block. At the end of the
//  transfer block, DMA1 issues an interrupt.
//  The purpose of this example is to show how multiple DMA triggers can be
//  combined.
//  P1.0 is toggled during DMA transfer only for demonstration purposes.
//  ACLK = n/a, MCLK = SMCLK = default DCO ~ 1.045MHz
//  //* Final Production MSP430F16x(x) Device Required *//
//
//               MSP430F261x
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//           |A10          P1.0|-->LED
//
//   B. Nisarga
//   Texas Instruments Inc.
//   September 2007
//   Built with CCE Version: 3.2.0
//******************************************************************************
#include "msp430x26x.h"

void Record(void);

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog
  P1DIR |= 0x01;                            // Set P1.0 to output direction

  while (1)                                 // Repeat forever
  {
    Record();
    _NOP();                                 // << SET BREAKPOINT HERE
  }
}

// Record ADC12 A10 channel data and store in RAM using DMA0
void Record(void)
{
  // setup modules
  volatile unsigned int i;
  ADC12MCTL0 = 0x01A;                       // Vref+, Channel A10
  ADC12IFG = 0x00;
  ADC12CTL1 = SHS_3 + CONSEQ_2;             // S&H TB.OUT1, rep. single chan
  ADC12CTL0 = REF2_5V + REFON + ADC12ON + ENC;    // VRef ADC12 on, enabled
  for (i = 0xFFF; i > 0; i--);              // Time VRef to settle

  TBCCR0 = 100;                             // Init TBCCR0 w/ sample prd
  TBCCR1 = 100 - 30;                        // Trigger for ADC12 SC
  TBCCTL1 = OUTMOD_7;                       // Reset OUT1 on EQU1, set on EQU0

  DMACTL0 = DMA1TSEL_11 + DMA0TSEL_6;       // DMA1=MPY Ready, DMA0=ADC12IFGx

  DMA0SA = (void (*)())&ADC12MEM0;          // Src address = ADC12 module
  DMA0DA = (void (*)())&OP2;                // Dst address = multiplier
  DMA0SZ = 1;                               // Size in words
  DMA0CTL = DMADT_4 + DMAEN;                // Sng rpt, config

  DMA1SA = (void (*)())&RESHI;              // Src address = multiplier
  DMA1DA = (void (*)())0x220;               // Dst address = RAM memory
  DMA1SZ = 0x20;                            // Size in bytes
  DMA1CTL = DMADSTINCR_3 + DMASBDB + DMAIE + DMAEN;   // Sng, config

  MPY = 0x1000;                             // MPY first operand

  // start recording and enter LPM0
  P1OUT |= 0x01;                            // Set P1.0 (LED On)
  TBCTL = TBSSEL_2 + MC_1 + TBCLR;          // SMCLK, clear TBR, up mode
  
  _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0 w/ interrups

  // power-down MSP430 modules
  ADC12CTL1 &= ~CONSEQ_2;                   // Stop conversion immediately
  ADC12CTL0 &= ~ENC;                        // Disable ADC12 conversion
  ADC12CTL0 = 0;                            // Switch off ADC12 & ref voltage
  TBCTL = 0;                                // Disable Timer_B
  P1OUT &= ~0x01;                           // Clear P1.0 (LED Off)
}

// DMA interrupt service routine
#pragma vector = DMA_VECTOR
__interrupt void DMA_ISR(void)
{
  DMA1CTL &= ~DMAIFG;                       // Clear DMA1 interrupt flag
  _BIC_SR_IRQ(LPM0_bits);                   // Exit LPM0 on reti
}
