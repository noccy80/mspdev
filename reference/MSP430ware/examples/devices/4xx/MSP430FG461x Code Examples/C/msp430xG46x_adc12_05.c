//******************************************************************************
//   MSP430xG461x Demo - ADC12, Using an External Reference
//
//   This example shows how to use an external positive reference for the ADC12.
//   The external reference is applied to the VeREF+ pin. Avss is used for the
//   negative reference. A single conversion is performed on channel A0. The
//   conversion results are stored in ADC12MEM0 and are moved to R5 after the
//   conversion is complete. Test by applying a voltage to channel A0, then
//   setting and running to a break point at "__no_operation()". To view the
//   conversion results, use the debugger to inspect 'ADCResult'.
//   ACLK = 32kHz, MCLK = SMCLK = default DCO 1048576Hz, ADC12CLK = ADC12OSC
//
//
//                  MSP430xG461x
//                ---------------
//               |            XIN|-
//        Vin -->|P6.0/A0        | 32kHz
//               |           XOUT|-
//        REF -->|VeREF+         |
//               |               |
//
//   A. Dannenberg/ M. Mitchell
//   Texas Instruments Inc.
//   October 2006
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430xG46x.h"

volatile unsigned int ADCResult;

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop watchdog
  P6SEL |= 0x01;                            // Enable A/D channel A0
  ADC12CTL0 = ADC12ON + SHT0_2;             // turn on ADC12, set samp time
  ADC12CTL1 = SHP;                          // Use sampling timer
  ADC12MCTL0 = SREF_2;                      // Vr+=VeREF+ (external)
  ADC12CTL0 |= ENC;                         // Enable conversions

  while (1)
  {
    ADC12CTL0 |= ADC12SC;                   // Start conversions
    while (!(ADC12IFG & 0x0001));           // Conversion done?
    ADCResult = ADC12MEM0;                  // Move result
    __no_operation();                       // SET BREAKPOINT HERE
  }
}
