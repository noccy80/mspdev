//******************************************************************************
//  CC430F513x Demo - ADC12_A, Using an External Reference
//
//  Description: This example shows how to use an external positive reference for
//  the ADC12.The external reference is applied to the VeREF+ pin. AVss is used
//  for the negative reference. A single conversion is performed on channel A0.
//  The conversion results are stored in ADC12MEM0 and Test by applying a voltage
//  to channel A0, then setting and running to a break point at the "_NOP()"
//  instruction. To view the conversion results, open the register window in 
//  the debugger and view the contents of ADC12MEM0.
//
//
//                CC430F5137
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//     Vin -->|P2.0/A0          |
//            |                 |
//     REF -->|P2.5/VeREF+      |
//            |                 |
//
//   M. Morales
//   Texas Instruments Inc.
//   April 2009
//   Built with CCE Version: 3.2.2 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************

#include "cc430x513x.h"

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop watchdog timer
  
  P2SEL |= BIT5 + BIT0;                     // Enable VeREF+ & A/D channel A0 
  
  /* Initialize ADC12 */
  ADC12CTL0 = ADC12ON+ADC12SHT0_2;          // Turn on ADC12, set sampling time
  ADC12CTL1 = ADC12SHP;                     // Use sampling timer
  ADC12MCTL0 = ADC12SREF_2;                 // Vr+ = VeREF+ (ext) and Vr-=AVss
  ADC12CTL0 |= ADC12ENC;                    // Enable conversions

  while (1)
  {
    ADC12CTL0 |= ADC12SC;                   // Start conversion-software trigger
    while (!(ADC12IFG & BIT0));
    __no_operation();                       // SET BREAKPOINT HERE
  }
}
