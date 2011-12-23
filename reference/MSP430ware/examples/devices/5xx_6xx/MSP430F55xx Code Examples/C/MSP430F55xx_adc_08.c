//******************************************************************************
//  MSP430F552x Demo - ADC12, Using A8 and A9 Ext Channels for Conversion
//
//  Description: This example shows how to perform A/D conversion on up to 10
//  external channels by showing that channels A8 and A9 can be used for
//  conversion of external signals when not using these channels as external
//  reference inputs. A single sequence of conversions is performed - one
//  conversion on A8 and then one conversion on A9. Each conversion uses AVcc
//  and AVss for the references. The conversion results are stored in ADC12MEM0
//  and ADC12MEM1 respectively and are moved to 'results[]' upon completion of
//  the sequence.
//  Test by applying voltages to pins VeREF+ for A8 and VREF-/VeREF- for A9,
//  then setting and running to a break point at the "_BIC..." instruction in
//  the ISR. To view the conversion results, open a watch window in debugger and
//  view 'results' or view ADC12MEM0 and ADC12MEM1 in an ADC12 SFR window.
//  This can run even in LPM4 mode as ADC has its own clock
//  *NOTE*  When using channels A8 and A9 for external signals, internal
//  references must be used for the conversions. Refer to figure 18-1 in the
//  MSP430x5xx Family User's Guide.
//
//                MSP430F552x
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//    Vin1 -->|VeREF+           |
//    Vin2 -->|VREF-/VeREF-     |
//
//
//   Bhargavi Nisarga
//   Texas Instruments Inc.
//   April 2009
//   Built with CCSv4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************

#include <msp430f5529.h>

volatile unsigned int results[2];           // Needs to be global in this example
                                            // Otherwise, the compiler removes it
                                            // because it is not used for anything.

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop watchdog timer
  ADC12CTL0 = ADC12ON+ADC12MSC+ADC12SHT0_15;// Turn on ADC12, set sampling time
  ADC12CTL1 = ADC12SHP+ADC12CONSEQ_1;       // Use sampling timer, single sequence
  ADC12MCTL0 = ADC12INCH_8;                 // ref+=AVcc, channel = A8
  ADC12MCTL1 = ADC12INCH_9+ADC12EOS;        // ref+=AVcc, channel = A9, end seq.
  ADC12IE = 0x02;                           // Enable ADC12IFG.1, end channel
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
  case  8:                                  // Vector  8:  ADC12IFG1
    results[0] = ADC12MEM0;                 // Move results, IFG is cleared
    results[1] = ADC12MEM1;                 // Move results, IFG is cleared
    __bic_SR_register_on_exit(LPM4_bits);   // Exit active CPU, SET BREAKPOINT HERE
  case 10: break;                           // Vector 10:  ADC12IFG2
  case 12: break;                           // Vector 12:  ADC12IFG3
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
