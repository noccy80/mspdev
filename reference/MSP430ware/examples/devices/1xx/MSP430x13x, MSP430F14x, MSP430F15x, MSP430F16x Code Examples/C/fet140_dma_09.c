//*******************************************************************************
//  MSP-FET430P140 Demo - DMA0, ADC12 A10 Block Xfer to RAM, TBCCR1, DCO
//
//  Description: A 0x20 word block of data is sampled and recorded into RAM
//  from the ADC12 channel 10 the integrated temperature sensor using the
//  Record() function. Timer_B CCR1 begins the ADC12 sample period, CCR0 the hold
//  and conversion start. Timer_B operates in the up mode with CCR0 defining the
//  sample period. DMA0 will automatically transfer each ADC12 conversion code
//  to memory when complete. At the end of the recording block, DMA0 will issue
//  an interrupt existing the function.
//  In the example the RAM block use to record the ADC12 data begins at 0x220.
//  P1.0 is toggled during DMA transfer only for demonstration purposes.
//  ACLK = n/a, MCLK = SMCLK = default DCO ~ 800k
//  //* MSP430F169 Device Required *//
//
//               MSP430F169
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//           |A10          P1.0|-->LED
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************

#include  <msp430x16x.h>

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
  ADC12MCTL0 = 0x01A;
  ADC12IFG = 0x00;
  ADC12CTL1 = SHS_3 + CONSEQ_2;             // S&H TB.OUT1, rep. single chan
  ADC12CTL0 = REF2_5V + REFON + ADC12ON + ENC;      // VRef ADC12 on, enabled
  for (i = 0xFFF; i > 0; i--);              // Time VRef to settle

  TBCCR0 = 100;                             // Init TBCCR0 w/ sample prd
  TBCCR1 = 100 - 30;                        // Trigger for ADC12 SC
  TBCCTL1 = OUTMOD_7;                       // Reset OUT1 on EQU1, set on EQU0

  DMA0SA = (unsigned int)&ADC12MEM0;				// Src address = ADC12 module
  DMA0DA = 0x220;                           // Dst address = RAM memory
  DMA0SZ = 0x20;                            // Size in words
  DMACTL0 = DMA0TSEL_6;                     // ADC12IFGx triggers DMA0
  DMA0CTL = DMADSTINCR_3 + DMAIE + DMAEN;   // Config

  // start recording and enter LPM0
  P1OUT |= 0x01;                            // Set P1.0 (LED On)
  TBCTL = TBSSEL_2+ MC_1 + TBCLR;           // SMCLK, clear TBR, up mode
  _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0 w/ interrups

  // power-down MSP430 modules
  ADC12CTL1 &= ~CONSEQ_2;                   // Stop conversion immediately
  ADC12CTL0 &= ~ENC;                        // Disable ADC12 conversion
  ADC12CTL0 = 0;                            // Switch off ADC12 & ref voltage
  TBCTL = 0;                                // Disable Timer_B
  P1OUT &= ~0x01;                           // Clear P1.0 (LED Off)
}

// DMA interrupt service routine
#pragma vector=DACDMA_VECTOR
__interrupt void DACDMA_ISR (void)
{
  DMA0CTL &= ~DMAIFG;                       // Clear DMA0 interrupt flag
  _BIC_SR_IRQ(LPM0_bits);                   // Exit LPM0 on reti
}
