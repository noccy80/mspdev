//******************************************************************************
//  MSP-FET430P430 Demo - ADC12, Sample A0, Set P5.1 if A0 > 0.5*AVcc
//
//  Description: A single sample is made on A0 with reference to AVcc.
//  Software sets ADC12SC to start sample and conversion - ADC12SC
//  automatically cleared at EOC. ADC12 internal oscillator times sample (16x)
//  and conversion. In Mainloop MSP430 waits in LPM0 to save power until ADC12
//  conversion is complete. ADC12_ISR forces exit from LPM0 in Mainloop on
//  reti. If A0 > 0.5*AVcc P5.1 is set, else it's reset.
//  ACLK = n/a, MCLK = SMCLK = default DCO, ADC12CLK = ADC12OSC
//  //* For acurate conversion, bias ADC12 references per device datasheet *//
//
//                MSP430FG439
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//     Vin -->|P6.0/A0      P5.1|--> LED
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//*****************************************************************************
#include  <msp430xG43x.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  ADC12CTL0 = SHT0_2 + ADC12ON;             // Set sampling time, turn on ADC12
  ADC12CTL1 = SHP;                          // Use sampling timer
  ADC12IE = 0x01;                           // Enable interrupt
  ADC12CTL0 |= ENC;                         // Conversion enabled
  P6SEL |= 0x01;                            // P6.0 ADC option select
  P5DIR |= 0x02;                            // P5.1 output

  for (;;)
  {
    ADC12CTL0 |= ADC12SC;                   // Sampling open
    _BIS_SR(CPUOFF + GIE);                  // LPM0, ADC12_ISR will force exit
  }
}

// ADC12 interrupt service routine
#pragma vector=ADC12_VECTOR
__interrupt void ADC12_ISR (void)
{
    if (ADC12MEM0 < 0x7FF)
      P5OUT &= ~0x02;                       // Clear P5.1 LED off
    else
      P5OUT |= 0x02;                        // Set P5.1 LED on
    _BIC_SR_IRQ(CPUOFF);                    // Clear CPUOFF bit from 0(SR)
}
