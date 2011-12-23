//******************************************************************************
//  MSP430F5438 Demo - ADC12, Sequence of Conversions (non-repeated)
//
//  Description: This example shows how to perform A/D conversions on a sequence
//  of channels. A single sequence of conversions is performed - one conversion
//  each on channels A0, A1, A2, and A3. Each conversion uses AVcc and AVss for
//  the references. The conversion results are stored in ADC12MEM0, ADC12MEM1,
//  ADC12MEM2, and ADC12MEM3 respectively and are moved to 'results[]' upon
//  completion of the sequence. Test by applying voltages to pins A0, A1, A2,
//  and A3, then setting and running to a break point at the "_BIC..."
//  instruction in the ISR. To view the conversion results, open a watch window
//  in debugger and view 'results' or view ADC12MEM0, ADC12MEM1, ADC12MEM2, and
//  ADC12MEM3 in an ADC12 SFR window.
//  This can run even in LPM4 mode as ADC has its own clock
//  Note that a sequence has no restrictions on which channels are converted.
//  For example, a valid sequence could be A0, A3, A2, A4, A2, A1, A0, and A7.
//  See the MSP430x5xx User's Guide for instructions on using the ADC12.
//
//                MSP430F5438
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//    Vin0 -->|P6.0/A0          |
//    Vin1 -->|P6.1/A1          |
//    Vin2 -->|P6.2/A2          |
//    Vin3 -->|P6.3/A3          |
//            |                 |
//
//   M Smertneck / W. Goh
//   Texas Instruments Inc.
//   September 2008
//   Built with CCE Version: 3.2.2 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************

#include "msp430x54x.h"

volatile unsigned int results[4];           // Needs to be global in this example
                                            // Otherwise, the compiler removes it
                                            // because it is not used for anything.

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop watchdog timer
  P6SEL = 0x0F;                             // Enable A/D channel inputs
  ADC12CTL0 = ADC12ON+ADC12MSC+ADC12SHT0_2; // Turn on ADC12, set sampling time
  ADC12CTL1 = ADC12SHP+ADC12CONSEQ_1;       // Use sampling timer, single sequence
  ADC12MCTL0 = ADC12INCH_0;                 // ref+=AVcc, channel = A0
  ADC12MCTL1 = ADC12INCH_1;                 // ref+=AVcc, channel = A1
  ADC12MCTL2 = ADC12INCH_2;                 // ref+=AVcc, channel = A2
  ADC12MCTL3 = ADC12INCH_3+ADC12EOS;        // ref+=AVcc, channel = A3, end seq.
  ADC12IE = 0x08;                           // Enable ADC12IFG.3
  ADC12CTL0 |= ADC12ENC;                    // Enable conversions

  while(1)
  {
    ADC12CTL0 |= ADC12SC;                   // Start convn - software trigger
    
    __bis_SR_register(LPM4_bits + GIE);     // Enter LPM4, Enable interrupts
    __no_operation();                       // For debugger    
  }
}

#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR (void)
{
    switch(__even_in_range(ADC12IV,34))
  {
  case  0: break;                           // Vector  0:  No interrupt
  case  2: break;                           // Vector  2:  ADC overflow
  case  4: break;                           // Vector  4:  ADC timing overflow
  case  6: break;                           // Vector  6:  ADC12IFG0
  case  8: break;                           // Vector  8:  ADC12IFG1
  case 10: break;                           // Vector 10:  ADC12IFG2
  case 12:                                  // Vector 12:  ADC12IFG3
    results[0] = ADC12MEM0;                 // Move results, IFG is cleared
    results[1] = ADC12MEM1;                 // Move results, IFG is cleared
    results[2] = ADC12MEM2;                 // Move results, IFG is cleared
    results[3] = ADC12MEM3;                 // Move results, IFG is cleared
    __bic_SR_register_on_exit(LPM4_bits);   // Exit active CPU, SET BREAKPOINT HERE  
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

