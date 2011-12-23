//******************************************************************************
//  MSP430F543xA Demo - ADC12_A, Repeated Single Channel Conversions
//
//  Description: This example shows how to perform repeated conversions on a
//  single channel using "repeat-single-channel" mode.  AVcc is used for the
//  reference and repeated conversions are performed on Channel A0. Each
//  conversion result is moved to an 8-element array called results[].  Test by
//  applying a voltage to channel A0, then running. Open a watch window in
//  debugger and view the results. Set Breakpoint1 in the index increment line
//  to see the array value change sequentially and Breakpoint to see the entire
//  array of conversion results in "results[]" for the specified Num_of_Results.
//  This can run even in LPM4 mode as ADC has its own clock (MODOSC)
//
//                MSP430F5438A
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//     Vin -->|P6.0/A0          |
//            |                 |
//
//
//   M Morales
//   Texas Instruments Inc.
//   June 2009
//   Built with CCE Version: 3.2.2 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************

#include "msp430x54xA.h"

#define   Num_of_Results   8
  
volatile unsigned int results[Num_of_Results];
                                            // Needs to be global in this
                                            // example. Otherwise, the
                                            // compiler removes it because it
                                            // is not used for anything.

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop watchdog timer
  
  P6SEL |= 0x01;                            // Enable A/D channel A0
  
  /* Initialize ADC12_A */ 
  ADC12CTL0 = ADC12ON+ADC12SHT0_8+ADC12MSC; // Turn on ADC12, set sampling time
                                            // set multiple sample conversion
  ADC12CTL1 = ADC12SHP+ADC12CONSEQ_2;       // Use sampling timer, set mode
  ADC12IE = 0x01;                           // Enable ADC12IFG.0
  ADC12CTL0 |= ADC12ENC;                    // Enable conversions
  ADC12CTL0 |= ADC12SC;                     // Start conversion
  
  __bis_SR_register(LPM4_bits + GIE);       // Enter LPM4, Enable interrupts
  __no_operation();                         // For debugger  
}

#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR (void)
{
  static unsigned char index = 0;

  switch(__even_in_range(ADC12IV,34))
  {
  case  0: break;                           // Vector  0:  No interrupt
  case  2: break;                           // Vector  2:  ADC overflow
  case  4: break;                           // Vector  4:  ADC timing overflow
  case  6:                                  // Vector  6:  ADC12IFG0
    results[index] = ADC12MEM0;             // Move results
    index++;                                // Increment results index, modulo; Set Breakpoint1 here
   
    if (index == 8)
      index = 0;                            // Reset the index; Set Breakpoint here 
      
  case  8: break;                           // Vector  8:  ADC12IFG1
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
