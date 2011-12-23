//******************************************************************************
//  MSP430F54x Demo - ADC12, Using the Internal Reference
//
//  Description: This example shows how to use the internal reference of ADC12.
//  It uses the internal 2.5V reference and performs a single conversion
//  on channel A0. The conversion results are stored in ADC12MEM0. Test by
//  applying a voltage to channel A0, then setting and running to a break point
//  at the "__no_operation()" instruction. To view the conversion results,
//  open an ADC12 register window in debugger and view the contents of ADC12MEM0
//
//                MSP430F5438
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//     Vin -->|P6.0/A0          |
//            |                 |

//
//   M Smertneck / W. Goh
//   Texas Instruments Inc.
//   September 2008
//   Built with CCE Version: 3.2.2 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************

#include "msp430x54x.h"

void main(void)
{
  volatile unsigned int i;
  WDTCTL = WDTPW+WDTHOLD;                   // Stop watchdog timer
  P6SEL |= 0x01;                            // Enable A/D channel A0
  ADC12CTL0 = ADC12ON+ADC12SHT02+ADC12REFON+ADC12REF2_5V;
                                            // Turn on ADC12, Sampling time
                                            // On Reference Generator and set to
                                            // 2.5V
  ADC12CTL1 = ADC12SHP;                     // Use sampling timer
  ADC12MCTL0 = ADC12SREF_1;                 // Vr+=Vref+ and Vr-=AVss

  for ( i=0; i<0x30; i++);                  // Delay for reference start-up

  ADC12CTL0 |= ADC12ENC;                    // Enable conversions

  while (1)
  {
    ADC12CTL0 |= ADC12SC;                   // Start conversion
    while (!(ADC12IFG & BIT0));
    __no_operation();                       // SET BREAKPOINT HERE
  }
}

