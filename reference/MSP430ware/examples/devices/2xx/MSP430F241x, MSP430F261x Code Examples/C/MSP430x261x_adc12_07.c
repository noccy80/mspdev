//******************************************************************************
//  MSP430x26x Demo - ADC12, Repeated Single Channel Conversions
//
//  Description: This example shows how to perform repeated conversions on a
//  single channel using "repeat-single-channel" mode.  AVcc is used for the
//  reference and repeated conversions are performed on Channel A0. Each
//  conversion result is moved to an 8-element array called results[].  Test by
//  applying a voltage to channel A0, then running. Open a watch window in 
//  debugger and view the results. Set Breakpoint1 in the index increment line  
//  to see the array value change sequentially and Breakpoint2 to see the entire
//  array of conversion results in "results[]" for the specified Num_of_Results.
//  This can run even in LPM4 mode as ADC has its own clock
//
//           MSP430F261x/241x
//             ---------------
//            |               |
//     Vin -->|P6.0/A0        |
//            |               |
//
//
//  B. Nisarga
//  Texas Instruments Inc.
//  September 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//******************************************************************************

#include  <msp430x26x.h>

#define   Num_of_Results   8

volatile unsigned int results[Num_of_Results];  // Needs to be global in this
                                              // example. Otherwise, the
                                              // compiler removes it because it
                                              // is not used for anything.

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop watchdog timer
  P6SEL |= 0x01;                            // Enable A/D channel A0
  ADC12CTL0 = ADC12ON+SHT0_8+MSC;           // Turn on ADC12, set sampling time
  ADC12CTL1 = SHP+CONSEQ_2;                 // Use sampling timer, set mode
  ADC12IE = 0x01;                           // Enable ADC12IFG.0
  ADC12CTL0 |= ENC;                         // Enable conversions
  ADC12CTL0 |= ADC12SC;                     // Start conversion
  _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0,Enable interrupts
}


#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR (void)
{
  static unsigned int index = 0;

  results[index] = ADC12MEM0;               // Move results
  index = (index+1)%Num_of_Results;         // Increment results index, modulo; Set Breakpoint1 here
  if (index == 0)
    _NOP();                                 // Set Breakpoint2 here
  
}
