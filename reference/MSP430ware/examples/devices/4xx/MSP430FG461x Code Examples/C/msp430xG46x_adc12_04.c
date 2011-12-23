//******************************************************************************
//   MSP430xG461x Demo - ADC12, Extend Sampling Period with SHT Bits
//
//   This example shows how to extend the sampling time using the sampling
//   timer. In this example, the ADC12OSC is used to provide the sampling period
//   and the SHT0 bits are set to extend the sampling period to 4xADC12CLKx256.
//   A single conversion is performed on channel A0. The A/D conversion results
//   are stored in ADC12MEM0 and are moved to R5 upon completion of the
//   conversion. Test by setting and running to a break point at
//   "__no_operation()". Use the debugger to inspect 'ADCResult'.
//   ACLK = 32kHz, MCLK = SMCLK = default DCO 1048576Hz, ADC12CLK = ADC12OSC
//
//
//               MSP430xG461x
//              ---------------
//             |            XIN|-
//      Vin -->|P6.0/A0        | 32kHz
//             |           XOUT|-
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
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog
  ADC12CTL0 = ADC12ON + SHT0_15;            // Turn on ADC12, set SHT0
                                            // for longer sampling
  ADC12CTL1 = SHP;                          // Use sampling timer
  ADC12IE |= 0x01;                          // Enable ADC12IFG.0 for ADC12MEM0
  ADC12CTL0 |= ENC;                         // Enable conversions

  while (1)
  {
    ADC12CTL0 |= ADC12SC;                   // Start conversions
    __bis_SR_register(LPM0_bits + GIE);     // Wait for conversion completion
                                            // Enable interrupts
    __no_operation();                       // SET BREAKPOINT HERE
  }
}

#pragma vector = ADC12_VECTOR
__interrupt void ADC12_ISR(void)
{
  ADCResult = ADC12MEM0;
  __bic_SR_register_on_exit(LPM0_bits);     // Exit LPM0
}
