//******************************************************************************
//  MSP430x41x2 Demo - ADC10, Sample A0, Signed, Set P5.1 if A0 > 0.5*AVcc
//
//  Description: A single sample is made on A0 with SIGNED reference to AVcc.
//  Software sets ADC10SC to start sample and conversion - ADC10SC
//  automatically cleared at EOC. ADC10 internal oscillator times sample (16x)
//  and conversion. In Mainloop MSP430 waits in LPM0 to save power until ADC10
//  conversion complete, ADC10_ISR will force exit from LPM0 in Mainloop on
//  reti. If A0 > 0.5*AVcc, P5.1 set, else reset.
//
//                MSP430x41x2
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//        >---|P7.4/A0      P5.1|--> LED
//
//  P. Thanigai
//  Texas Instruments Inc.
//  January 2009
//  Built with CCE Version: 3.1 and IAR Embedded Workbench Version: 4.11
//******************************************************************************
#include "msp430x41x2.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  ADC10CTL1 = ADC10DF;                      // Conversion code singed format
  ADC10CTL0 = ADC10SHT_2 + ADC10ON + ADC10IE; // ADC10ON, interrupt enabled
  ADC10AE0 |= 0x01;                         // P7.4 ADC option select
  P5DIR |= 0x02;                            // Set P5.1 to output direction

  for (;;)
  {
    ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
    __bis_SR_register(CPUOFF + GIE);        // LPM0, ADC10_ISR will force exit
    if ((int)ADC10MEM  < 0)
      P5OUT &= ~0x02;                       // Clear P5.1 LED off
    else
      P5OUT |= 0x02;                        // Set P5.1 LED on
  }
}

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
  __bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)
}
