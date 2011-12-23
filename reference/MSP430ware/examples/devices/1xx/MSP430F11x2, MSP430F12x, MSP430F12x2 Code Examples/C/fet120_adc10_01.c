//******************************************************************************
//  MSP-FET430P120 Demo - ADC10, Sample A0, AVcc Ref, Set P1.0 if > 0.5*AVcc
//
//  Description: A single sample is made on A0 with reference to AVcc.
//  Software sets ADC10SC to start sample and conversion - ADC10SC
//  automatically cleared at EOC. ADC10 internal oscillator times sample (16x)
//  and conversion. In Mainloop MSP430 waits in LPM0 to save power until ADC10
//  conversion complete, ADC10_ISR will force exit from LPM0 in Mainloop on
//  reti. If A0 > 0.5*AVcc, P1.0 set, else reset.
//  //* MSP430F1232 or MSP430F1132 Device Required *//
//
//                MSP430F1232
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//        >---|A0           P1.0|-->LED
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************

#include  <msp430x12x2.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  ADC10CTL0 = ADC10SHT_2 + ADC10ON + ADC10IE; // ADC10ON, interrupt enabled
  ADC10AE |= 0x01;                          // P2.0 ADC option select
  P1DIR |= 0x01;                            // Set P1.0 to output direction

  for (;;)
  {
    ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
    _BIS_SR(CPUOFF + GIE);                  // LPM0, ADC10_ISR will force exit
    if (ADC10MEM < 0x1FF)
    P1OUT &= ~0x01;                         // Clear P1.0 LED off
    else
    P1OUT |= 0x01;                          // Set P1.0 LED on
  }
}

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR (void)
{
    _BIC_SR_IRQ(CPUOFF);                    // Clear CPUOFF bit from 0(SR)
}
