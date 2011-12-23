//******************************************************************************
//  MSP-FET430P430 Demo - ADC12, Repeated Single Channel Conversions
//
//  This example shows how to perform repeated conversions on a single channel
//  using "repeat-single-channel" mode.  AVcc is used for the reference and
//  repeated conversions are performed on Channel A0. Each conversion result
//  is moved to an 8-element array called results[].  Test by applying a
//  voltage to channel A0, then running. To view the conversion results, open a
//  watch window with the debugger and view 'results.'
//  ACLK = n/a, MCLK = SMCLK = default DCO, ADC12CLK = ADC12OSC
//
//
//               MSP430FG439
//             ---------------
//            |               |
//     Vin -->|P6.0/A0        |
//            |               |
//
//
//  M. Mitchell
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************
#include  <msp430xG43x.h>

#define   Num_of_Results   8

// Needs to be global in this example. Otherwise, the
// compiler removes it because it is not used
static unsigned int results[Num_of_Results];

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop watchdog timer
  P6SEL |= 0x01;                            // Enable A/D channel A0
  ADC12CTL0 = ADC12ON+SHT0_8+MSC;           // Turn on ADC12, set sampling time
  ADC12CTL1 = SHP+CONSEQ_2;                 // Use sampling timer, set mode
  ADC12IE = 0x01;                           // Enable ADC12IFG.0
  ADC12CTL0 |= ENC;                         // Enable conversions
  _EINT();                                  // Enable interrupts
  ADC12CTL0 |= ADC12SC;                     // Start conversion
  _BIS_SR(LPM0_bits);                       // Enter LPM0
}


#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR (void)
{
  static unsigned int index = 0;

  results[index] = ADC12MEM0;               // Move results
  index = (index+1)%Num_of_Results;         // Increment results index, modulo
}
