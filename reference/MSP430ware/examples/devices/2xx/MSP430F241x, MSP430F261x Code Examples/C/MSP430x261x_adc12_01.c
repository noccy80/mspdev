//******************************************************************************
//  MSP430x26x Demo - ADC12, Sample A0, Set P1.0 if A0 > 0.5*AVcc
//
//  Description: A single sample is made on A0 with reference to AVcc.
//  Software sets ADC10SC to start sample and conversion - ADC12SC
//  automatically cleared at EOC. ADC12 internal oscillator times sample (16x)
//  and conversion. In Mainloop MSP430 waits in LPM0 to save power until ADC12
//  conversion complete, ADC12_ISR will force exit from LPM0 in Mainloop on
//  reti. If A0 > 0.5*AVcc, P1.0 set, else reset.
//
//              MSP430F261x/241x
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//      Vin-->|P6.0/A0      P1.0|--> LED
//
//  B. Nisarga
//  Texas Instruments Inc.
//  September 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//******************************************************************************

#include  <msp430x26x.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  ADC12CTL0 = SHT0_2 + ADC12ON;             // Set sampling time, turn on ADC12
  ADC12CTL1 = SHP;                          // Use sampling timer
  ADC12IE = 0x01;                           // Enable interrupt
  ADC12CTL0 |= ENC;                         // Conversion enabled
  P6DIR &= 0x01;                            // P6.0, i/p 
  P6SEL |= 0x01;                            // P6.0-ADC option select 
  P1DIR |= 0x01;                            // P1.0 output-LED

  for (;;)
  {
    ADC12CTL0 |= ADC12SC;                   // Start convn, software controlled
    _BIS_SR(CPUOFF + GIE);                  // LPM0, ADC12_ISR will force exit
  }
}

// ADC12 interrupt service routine
#pragma vector=ADC12_VECTOR
__interrupt void ADC12_ISR (void)
{
    if (ADC12MEM0 < 0x7FF)
      P1OUT &= ~0x01;                       // Clear P1.0 LED off
    else
      P1OUT |= 0x01;                        // Set P1.0 LED on
    _BIC_SR_IRQ(CPUOFF);                    // Clear CPUOFF bit from 0(SR)
}
