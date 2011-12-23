//******************************************************************************
//  MSP430xG461x Demo - ADC12, Repeated Sequence of Conversions
//
//  This example shows how to perform a repeated sequence of conversions using
//  "repeat sequence-of-channels" mode.  AVcc is used for the reference and
//  repeated sequence of conversions is performed on Channels A0, A1, A2, and
//  A3. Each conversion result is stored in ADC12MEM0, ADC12MEM1, ADC12MEM2,
//  and ADC12MEM3 respectively. After each sequence, the 4 conversion results
//  are moved to A0results[], A1results[], A2results[], and A3results[]. Test
//  by applying voltages to channels A0 - A3. Open a watch window with the
//  debugger and view the results.
//
//  Note that a sequence has no restrictions on which channels are converted.
//  For example, a valid sequence could be A0, A3, A2, A4, A2, A1, A0, and A7.
//  See the MSP430x4xx User's Guide for instructions on using the ADC12.
//  ACLK = 32kHz, MCLK = SMCLK = default DCO 1048576Hz, ADC12CLK = ADC12OSC
//
//              MSP430xG461x
//            -----------------
//           |              XIN|-
//   Vin0 -->|P6.0/A0          | 32kHz
//   Vin1 -->|P6.1/A1      XOUT|-
//   Vin2 -->|P6.2/A2          |
//   Vin3 -->|P6.3/A3          |
//           |                 |
//
//  A. Dannenberg/ M. Mitchell
//  Texas Instruments Inc.
//  October 2006
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430xG46x.h"

volatile unsigned int A0results[8];
volatile unsigned int A1results[8];
volatile unsigned int A2results[8];
volatile unsigned int A3results[8];
unsigned int Index;

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog
  P6SEL |= 0x0f;                            // Enable A/D inputs
  ADC12CTL0 = SHT0_8 + MSC + ADC12ON;       // Turn on ADC12, use int. osc.
                                            // extend sampling time so won't
                                            // get overflow
                                            // Set MSC so conversions triggered
                                            // automatically
  ADC12CTL1 = SHP + CONSEQ_3;               // Use sampling timer, set mode
  ADC12IE = 0x08;                           // Enable ADC12IFG.3 for ADC12MEM3
  ADC12MCTL0 = INCH_0;                      // A0 goes to MEM0
  ADC12MCTL1 = INCH_1;                      // A1 goes to MEM1
  ADC12MCTL2 = INCH_2;                      // A2 goes to MEM2
  ADC12MCTL3 = EOS + INCH_3;                // A3 goes to MEM3, end of sequence

  while (1)
  {
    ADC12CTL0 |= ENC;                       // Enable conversions
    ADC12CTL0 |= ADC12SC;                   // Start conversions
    __bis_SR_register(LPM0_bits + GIE);     // LPM0
  }
}

#pragma vector = ADC12_VECTOR
__interrupt void ADC12_ISR(void)
{
  A0results[Index] = ADC12MEM0;             // Move A0 results, IFG is cleared
  A1results[Index] = ADC12MEM1;             // Move A1 results, IFG is cleared
  A2results[Index] = ADC12MEM2;             // Move A2 results, IFG is cleared
  A3results[Index] = ADC12MEM3;             // Move A3 results, IFG is cleared
  Index = (Index + 1) & 0x7;                // Increment results index, modulo
  __no_operation();                         // SET BREAKPOINT HERE
  __bic_SR_register_on_exit(LPM0_bits);     // Exit LPM0
}
