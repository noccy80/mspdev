//******************************************************************************
//  MSP430F552x Demo - ADC12, Repeated Sequence of Conversions
//
//  Description: This example shows how to perform a repeated sequence of
//  conversions using "repeat sequence-of-channels" mode.  AVcc is used for the
//  reference and repeated sequence of conversions is performed on Channels A0,
//  A1, A2, and A3. Each conversion result is stored in ADC12MEM0, ADC12MEM1,
//  ADC12MEM2, and ADC12MEM3 respectively. After each sequence, the 4 conversion
//  results are moved to A0results[], A1results[], A2results[], and A3results[].
//  Test by applying voltages to channels A0 - A3. Open a watch window in
//  debugger and view the results. Set Breakpoint1 in the index increment line
//  to see the array values change sequentially and Breakpoint2 to see the entire
//  array of conversion results in A0results[], A1results[], A2results[], and
//  A3results[]for the specified Num_of_Results.
//
//  Note that a sequence has no restrictions on which channels are converted.
//  For example, a valid sequence could be A0, A3, A2, A4, A2, A1, A0, and A7.
//  See the MSP430x5xx User's Guide for instructions on using the ADC12.
//
//               MSP430F552x
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//    Vin0 -->|P6.0/CB0/A0      |
//    Vin1 -->|P6.1/CB1/A1      |
//    Vin2 -->|P6.2/CB2/A2      |
//    Vin3 -->|P6.3/CB3/A3      |
//            |                 |
//
//   Bhargavi Nisarga
//   Texas Instruments Inc.
//   April 2009
//   Built with CCSv4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************

#include <msp430f5529.h>

#define   Num_of_Results   8

volatile unsigned int A0results[Num_of_Results];
volatile unsigned int A1results[Num_of_Results];
volatile unsigned int A2results[Num_of_Results];
volatile unsigned int A3results[Num_of_Results];

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop watchdog timer
  P6SEL = 0x0F;                             // Enable A/D channel inputs
  ADC12CTL0 = ADC12ON+ADC12MSC+ADC12SHT0_8; // Turn on ADC12, extend sampling time
                                            // to avoid overflow of results
  ADC12CTL1 = ADC12SHP+ADC12CONSEQ_3;       // Use sampling timer, repeated sequence
  ADC12MCTL0 = ADC12INCH_0;                 // ref+=AVcc, channel = A0
  ADC12MCTL1 = ADC12INCH_1;                 // ref+=AVcc, channel = A1
  ADC12MCTL2 = ADC12INCH_2;                 // ref+=AVcc, channel = A2
  ADC12MCTL3 = ADC12INCH_3+ADC12EOS;        // ref+=AVcc, channel = A3, end seq.
  ADC12IE = 0x08;                           // Enable ADC12IFG.3
  ADC12CTL0 |= ADC12ENC;                    // Enable conversions
  ADC12CTL0 |= ADC12SC;                     // Start convn - software trigger
  
  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0, Enable interrupts
  __no_operation();                         // For debugger
  
}

#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR (void)
{
  static unsigned int index = 0;

  switch(__even_in_range(ADC12IV,34))
  {
  case  0: break;                           // Vector  0:  No interrupt
  case  2: break;                           // Vector  2:  ADC overflow
  case  4: break;                           // Vector  4:  ADC timing overflow
  case  6: break;                           // Vector  6:  ADC12IFG0
  case  8: break;                           // Vector  8:  ADC12IFG1
  case 10: break;                           // Vector 10:  ADC12IFG2
  case 12:                                  // Vector 12:  ADC12IFG3
    A0results[index] = ADC12MEM0;           // Move A0 results, IFG is cleared
    A1results[index] = ADC12MEM1;           // Move A1 results, IFG is cleared
    A2results[index] = ADC12MEM2;           // Move A2 results, IFG is cleared
    A3results[index] = ADC12MEM3;           // Move A3 results, IFG is cleared
    index++;                                // Increment results index, modulo; Set Breakpoint1 here
    
    if (index == 8)
    {
      (index = 0);
    }
  case 14: break;                           // Vector 14:  ADC12IFG4
  case 16: break;                           // Vector 16:  ADC12IFG5
  case 18: break;                           // Vector 18:  ADC12IFG6
  case 20: break;                           // Vector 20:  ADC12IFG7
  case 22: break;                           // Vector 22:  ADC12IFG8
  case 24: break;                           // Vector 24:  ADC12IFG9
  case 26: break;                           // Vector 26:  ADC12IFG10
  case 28: break;                           // Vector 28:  ADC12IFG11
  case 30: break;                           // Vector 30:  ADC12IFG12
  case 32: break;                           // Vector 32:  ADC12IFG13
  case 34: break;                           // Vector 34:  ADC12IFG14
  default: break; 
  }  
}
