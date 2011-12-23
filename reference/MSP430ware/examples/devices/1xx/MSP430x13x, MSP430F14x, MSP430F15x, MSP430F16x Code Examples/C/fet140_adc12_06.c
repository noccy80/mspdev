//******************************************************************************
//  MSP-FET430P140 Demo - ADC12, Repeated Sequence of Conversions
//
//  Description: This example shows how to perform a repeated sequence of
//  conversions using "repeat sequence-of-channels" mode.  AVcc is used for the
//  reference and repeated sequence of conversions is performed on Channels A0,
//  A1, A2, and A3. Each conversion result is stored in ADC12MEM0, ADC12MEM1,
//  ADC12MEM2, and ADC12MEM3 respectively. After each sequence, the 4 conversion
//  results are moved to A0results[], A1results[], A2results[], and A3results[].
//  Test by applying voltages to channels A0 - A3. Open a watch window in 
//  debugger and view the results. Set a breakpoint in the last line to see the 
//  array values change sequentially.
//
//  Note that a sequence has no restrictions on which channels are converted.
//  For example, a valid sequence could be A0, A3, A2, A4, A2, A1, A0, and A7.
//  See the MSP430x1xx User's Guide for instructions on using the ADC12.
//
//
//                 MSP430F149
//            -----------------
//           |                 |
//   Vin0 -->|P6.0/A0          |
//   Vin1 -->|P6.1/A1          |
//   Vin2 -->|P6.2/A2          |
//   Vin3 -->|P6.3/A3          |
//           |                 |
//
//
//  M. Mitchell
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************

#include  <msp430x14x.h>

#define   Num_of_Results   8

static unsigned int A0results[Num_of_Results];  // These need to be global in
static unsigned int A1results[Num_of_Results];  // this example. Otherwise, the
static unsigned int A2results[Num_of_Results];  // compiler removes them because
static unsigned int A3results[Num_of_Results];  // they are not used

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop watchdog timer
  P6SEL = 0x0F;                             // Enable A/D channel inputs
  ADC12CTL0 = ADC12ON+MSC+SHT0_8;           // Turn on ADC12, extend sampling time
                                            // to avoid overflow of results
  ADC12CTL1 = SHP+CONSEQ_3;                 // Use sampling timer, repeated sequence
  ADC12MCTL0 = INCH_0;                      // ref+=AVcc, channel = A0
  ADC12MCTL1 = INCH_1;                      // ref+=AVcc, channel = A1
  ADC12MCTL2 = INCH_2;                      // ref+=AVcc, channel = A2
  ADC12MCTL3 = INCH_3+EOS;                  // ref+=AVcc, channel = A3, end seq.
  ADC12IE = 0x08;                           // Enable ADC12IFG.3
  ADC12CTL0 |= ENC;                         // Enable conversions
  ADC12CTL0 |= ADC12SC;                     // Start conversion
  _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0, Enable interrupts
}

#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR (void)
{
  static unsigned int index = 0;

  A0results[index] = ADC12MEM0;             // Move A0 results, IFG is cleared
  A1results[index] = ADC12MEM1;             // Move A1 results, IFG is cleared
  A2results[index] = ADC12MEM2;             // Move A2 results, IFG is cleared
  A3results[index] = ADC12MEM3;             // Move A3 results, IFG is cleared
  index = (index+1)%Num_of_Results;         // Increment results index, modulo; Set Breakpoint here
}
