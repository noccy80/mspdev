//*******************************************************************************
//   MSP430x26x Demo - DMA0, ADC12 A10 Block Xfer to Flash, TBCCR1, DCO
//
//  Description: A 0x20 word block of data is sampled and recorded into Flash
//  from the ADC12 channel 10 the integrated temperature sensor using the
//  Record() function. Timer_B CCR1 begins the ADC12 sample period, CCR0 the hold
//  and conversion start. Timer_B operates in the up mode with CCR0 defining the
//  sample period. DMA0 will automatically transfer each ADC12 conversion code
//  to memory when complete. At the end of the recording block, DMA0 will issue
//  an interrupt existing the function.
//  In this example the ADC12 sample period is 100 SMCLK cycle, and Flash
//  programming requires 70 cycles.
//  In the example the Flash block use to record the ADC12 data begins at 0x2000.
//  P1.0 is toggled during DMA transfer only for demonstration purposes.
//  ACLK = n/a, MCLK = SMCLK = default DCO ~ 1.045MHz
//  //* Set Breakpoint on NOP in the Mainloop to avoid Stressing Flash *//
//  //* MSP430F169 Device Required *//
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
  FCTL2 = FWKEY + FSSEL_2 + FN0;            // Clk src = SMCLK / 2 (~400KHz)
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
  unsigned int i;

  // unlock and erase Flash memory
  FCTL1 = FWKEY + ERASE;                    // Set Erase bit
  FCTL3 = FWKEY;                            // Clear Lock bit
  *(unsigned int *)0x1080 = 0;              // Dummy write to erase Flash segment

  // setup modules
  ADC12MCTL0 = 0x01A;                       // Vref+, Channel A10
  ADC12IFG = 0x00;
  ADC12CTL1 = SHS_3 + CONSEQ_2;             // S&H TB.OUT1, rep. single chan
  ADC12CTL0 = REF2_5V + REFON + ADC12ON + ENC; // VRef ADC12 on, enabled
  for (i = 0xFFF; i > 0; i--);              // Time VRef to settle

  TBCCR0 = 100;                             // Init TBCCR0 w/ sample prd
  TBCCR1 = 100 - 30;                        // Trigger for ADC12 SC
  TBCCTL1 = OUTMOD_7;                       // Reset OUT1 on EQU1, set on EQU0

  DMA0SA = (void (*)())&ADC12MEM0;          // Src address = ADC12 module
  DMA0DA = (void (*)())0x2000;              // Dst address = Flash memory
  DMA0SZ = 0x20;                            // Size in words
  DMACTL0 = DMA0TSEL_6;                     // ADC12IFGx triggers DMA0
  DMACTL1 = DMAONFETCH;                     // Required for proper Flash Write
  DMA0CTL = DMADSTINCR_3 + DMAIE + DMAEN;   // Config

  // start recording and enter LPM0
  P1OUT |= 0x01;                            // Set P1.0 (LED On)
  TBCTL = TBSSEL_2+ MC_1 + TBCLR;           // SMCLK, clear TBR, up mode
  FCTL1 = FWKEY + WRT;                      // Enable Flash write for recording
  
  _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0 w/ interrups

  // deactivate Flash memory write access
  FCTL1 = FWKEY;                            // Disable Flash write
  FCTL3 = FWKEY + LOCK;                     // Lock Flash memory

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
  DMA0CTL &= ~DMAIFG;                       // Clear DMA0 interrupt flag
  _BIC_SR_IRQ(LPM0_bits);                   // Exit LPM0 on reti
}
