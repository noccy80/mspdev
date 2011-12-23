//******************************************************************************
//  MSP430F552x Demo - ADC12, Using an External Reference
//
//  Description: This example shows how to use an external positive reference for
//  the ADC12.The external reference is applied to the VeREF+ pin. AVss is used
//  for the negative reference. A single conversion is performed on channel A0.
//  The conversion results are stored in ADC12MEM0 and Test by applying a voltage
//  to channel A0, then setting and running to a break point at the "_NOP()"
//  instruction. To view the conversion results, open an SFR window in debugger
//  and view the contents of ADC12MEM0.
//  NOTE: VeREF+ range: 1.4V (min) to AVCC (max)
//        VeREF- range: 0V (min) to 1.2V (max)
//        Differential ref voltage range: 1.4V(min) to AVCC(max)
//			(see datasheet for device specific information)
//
//
//                MSP430F552x
//             -------------------
//         /|\|                   |
//          | |                   |
//          --|RST                |
//            |                   |
//     Vin -->|P6.0/CB0/A0        |
//            |                   |
//     REF -->|P5.0/VREF+/VeREF+  |
//            |                   |
//
//   Bhargavi Nisarga
//   Texas Instruments Inc.
//   April 2009
//   Built with CCSv4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************

#include <msp430f5529.h>

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop watchdog timer
  P6SEL |= 0x01;                            // Enable A/D channel A0
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
