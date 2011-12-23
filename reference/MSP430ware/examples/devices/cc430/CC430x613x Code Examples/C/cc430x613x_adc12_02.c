//******************************************************************************
//  CC430F613x Demo - ADC12_A, Using the Internal Reference
//
//  Description: This example shows how to use the shared reference for ADC12
//  sampling and performs a single conversion on channel A0. The conversion 
//  results are stored in ADC12MEM0. Test by applying a voltage to channel A0, 
//  then setting and running to a break point at the "__no_operation()" 
//  instruction. To view the conversion results, open an ADC12 register window 
//  in debugger and view the contents of ADC12MEM0
//
//                CC430F613x
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//     Vin -->|P2.0/A0          |
//            |                 |

//
//   M. Morales
//   Texas Instruments Inc.
//   April 2009
//   Built with CCE Version: 3.2.2 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************

#include "cc430x613x.h"

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop watchdog timer
  
  P2SEL |= BIT0;                            // Enable A/D channel A0
  
  /* Initialize REF module */
  // Enable 2.5V shared reference, disable temperature sensor to save power
  REFCTL0 |= REFMSTR+REFVSEL_2+REFON+REFTCOFF; 
  
  /* Initialize ADC12 */  
  ADC12CTL0 = ADC12ON+ADC12SHT02;           // Turn on ADC12, set sampling time
  ADC12CTL1 = ADC12SHP;                     // Use sampling timer
  ADC12MCTL0 = ADC12SREF_1;                 // Vr+=Vref+ and Vr-=AVss

  __delay_cycles(75);                       // 75 us delay @ ~1MHz

  ADC12CTL0 |= ADC12ENC;                    // Enable conversions

  while (1)
  {
    ADC12CTL0 |= ADC12SC;                   // Start conversion
    while (!(ADC12IFG & BIT0));
    __no_operation();                       // SET BREAKPOINT HERE
  }
}

