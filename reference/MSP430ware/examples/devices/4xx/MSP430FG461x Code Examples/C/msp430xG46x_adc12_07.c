//******************************************************************************
//  MSP430xG461x Demo - ADC12, Repeated Single Channel Conversions
//
//  This example shows how to perform repeated conversions on a single channel
//  using "repeat-single-channel" mode.  AVcc is used for the reference and
//  repeated conversions are performed on Channel A0. Each conversion result
//  is moved to an 8-element array called Results[].  Test by applying a
//  voltage to channel A0, then running. To view the conversion results, open a
//  watch window with the debugger and view Results[].
//  ACLK = 32kHz, MCLK = SMCLK = default DCO 1048576Hz, ADC12CLK = ADC12OSC
//
//                MSP430xG461x
//              ---------------
//             |            XIN|-
//      Vin -->|P6.0/A0        | 32kHz
//             |           XOUT|-
//
//  A. Dannenberg/ M. Mitchell
//  Texas Instruments Inc.
//  October 2006
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430xG46x.h"

volatile unsigned int Results[8];
unsigned int Index;

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P6SEL |= 0x01;                            // Enable A/D channel A0
  ADC12CTL0 = ADC12ON + SHT0_8 + MSC;       // Turn on ADC12, set sampling time
  ADC12CTL1 = SHP + CONSEQ_2;               // Use sampling timer, set mode
  ADC12IE = 0x01;                           // Enable ADC12IFG.0
  ADC12CTL0 |= ENC;                         // Enable conversions
  __enable_interrupt();                     // Enable interrupts
  ADC12CTL0 |= ADC12SC;                     // Start conversion
  __bis_SR_register(LPM0_bits);             // LPM0
}

#pragma vector = ADC12_VECTOR
__interrupt void ADC12_ISR(void)
{
  Results[Index++] = ADC12MEM0;             // Move result, IFG is cleared
  Index &= 0x07;                            // Modulo pointer
  __no_operation();                         // SET BREAKPOINT HERE
}
