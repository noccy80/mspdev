//******************************************************************************
//   MSP430xG461x Demo - ADC12, Using the Internal Reference
//
//   This example shows how to use the internal reference of the ADC12.
//   It uses the internal 2.5V reference and performs a single conversion
//   on channel A0. The conversion results are stored in ADC12MEM0. Test by
//   applying a voltage to channel A0, then setting and running to a breakpoint
//   at "__no_operation()".
//   To view the conversion results, open a register window in Debugger and
//   view the contents of ADC12MEM0.
//   ACLK = 32kHz, MCLK = SMCLK = default DCO 1048576Hz, ADC12CLK = ADC12OSC
//
//
//                MSP430xG461x
//              ---------------
//             |            XIN|-
//             |               | 32kHz
//      Vin -->|P6.0/A0    XOUT|-
//             |               |
//
//
//   A. Dannenberg/ M. Mitchell
//   Texas Instruments Inc.
//   October 2006
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430xG46x.h"

volatile unsigned int i;

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog
  P6SEL |= 0x01;                            // Enable A/D channel A0
  ADC12CTL0 = REFON + REF2_5V + ADC12ON + SHT0_2;
                                            // turn on 2.5V ref, set samp time
  ADC12CTL1 = SHP;                          // Use sampling timer
  ADC12MCTL0 = SREF_1;                      // Vr+=Vref+

  for (i = 0x3600; i; i--);                 // Delay for needed ref start-up.
                                            // See datasheet for details.
  ADC12CTL0 |= ENC;                         // Enable conversions


  while (1)
  {
    ADC12CTL0 |= ADC12SC;                   // Start conversions
    while (!(ADC12IFG & 0x0001));           // Conversion done?
    ADC12MEM0;                              // Access result
    __no_operation();                       // SET BREAKPOINT HERE
  }
}
