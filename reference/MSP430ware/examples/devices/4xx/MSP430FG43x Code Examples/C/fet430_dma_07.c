//******************************************************************************
//  MSP-FET430P430 Demo - DMA0, ADC12 A10 Block Xfer to Flash, Timer_B, SMCLK
//
//  Description: A 0x20 word block of data is sampled and recorded into Flash
//  from ADC12 channel 10, the integrated temperature sensor, using the
//  Record() function. Timer_B CCR1 begins the ADC12 sample period, CCR0 the
//  hold and conversion start. Timer_B operates in the up mode with CCR0
//  defining the sample period. DMA0 will automatically transfer each
//  ADC12 conversion code to memory when complete. At the end of the recording
//  block, DMA0 will issue an interrupt exiting the function.
//  In this example the ADC12 sample period is 120 SMCLK cycles, and Flash
//  programming requires 105 cycles.
//  In the example the Flash block used to record ADC12 data begins at 0x1080.
//  P5.1 is toggled during DMA transfer only for demonstration purposes.
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//	
//
//  IMPORTANT - set breakpoint to avoid stressing Flash
//
//               MSP430FG439
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32kHz
//         --|RST          XOUT|-
//           |                 |
//           |A10          P5.1|-->LED
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//*******************************************************************************
#include  <msp430xG43x.h>

void Record(void);

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog
  FCTL2 = FWKEY + FSSEL_2 + FN1;            // Clk src = SMCLK / 3 (~350KHz)
  P5DIR |= 0x02;                            // Set P5.1 to output direction

  while (1)                                 // Repeat forever
  {
    Record();
    _NOP();                                 // SET BREAKPOINT HERE
  }
}

// Record ADC12 A10 channel data and store in RAM using DMA0
void Record(void)
{
  volatile unsigned int i;

  // Unlock and erase Flash memory
  FCTL1 = FWKEY + ERASE;                    // Set Erase bit
  FCTL3 = FWKEY;                            // Clear Lock bit
  *(unsigned int *)0x1080 = 0;              // Dummy write to erase Flash segment

  // Setup modules
  ADC12MCTL0 = 0x01A;
  ADC12IFG = 0x00;
  ADC12CTL1 = SHS_3 + CONSEQ_2;             // S&H TB.OUT1, rep. single chan
  ADC12CTL0 = REF2_5V + REFON + ADC12ON + ENC;      // VRef ADC12 on, enabled
  for (i = 0xFFF; i > 0; i--);              // Time VRef to settle

  TBCCR0 = 120-1;                           // Init TBCCR0 w/ sample prd
  TBCCR1 = 120 - 30;                        // Trigger for ADC12 SC
  TBCCTL1 = OUTMOD_7;                       // Reset OUT1 on EQU1, set on EQU0

  DMA0SA = (unsigned int)&ADC12MEM0;        // Src address = ADC12 module
  DMA0DA = 0x1080;                          // Dst address = Flash memory
  DMA0SZ = 0x20;                            // Size in words
  DMACTL0 = DMA0TSEL_6;                     // ADC12IFGx triggers DMA0
  DMACTL1 = DMAONFETCH;                     // Required for proper Flash Write
  DMA0CTL = DMADSTINCR_3 + DMAIE + DMAEN;   // Config

  // Start recording and enter LPM0
  P5OUT |= 0x02;                            // Set P5.1 (LED On)
  TBCTL = TBSSEL_2+ MC_1 + TBCLR;           // SMCLK, clear TBR, up mode
  FCTL1 = FWKEY + WRT;                      // Enable Flash write for recording
  _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0 w/ interrupts

  // Deactivate Flash memory write access
  FCTL1 = FWKEY;                            // Disable Flash write
  FCTL3 = FWKEY + LOCK;                     // Lock Flash memory

  // Power-down MSP430 modules
  ADC12CTL1 &= ~CONSEQ_2;                   // Stop conversion immediately
  ADC12CTL0 &= ~ENC;                        // Disable ADC12 conversion
  ADC12CTL0 = 0;                            // Switch off ADC12 & ref voltage
  TBCTL = 0;                                // Disable Timer_B
  P5OUT &= ~0x02;                           // Clear P5.1 (LED Off)
}

// DMA Interrupt Service Routine
#pragma vector=DAC12_DMA_VECTOR
__interrupt void DACDMA_ISR (void)
{
  DMA0CTL &= ~DMAIFG;                       // Clear DMA0 interrupt flag
  _BIC_SR_IRQ(LPM0_bits);                   // Exit LPM0 on reti
}
