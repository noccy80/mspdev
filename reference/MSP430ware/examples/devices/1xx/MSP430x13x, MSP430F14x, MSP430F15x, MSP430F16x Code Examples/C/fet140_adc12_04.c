//******************************************************************************
//  MSP-FET430P140 Demo - ADC12, Extend Sampling Period with SHT Bits
//
//  Description: This example shows how to extend the sampling time using the
//  sampling timer. In this example, the ADC12OSC is used to provide the sampling
//  period and the SHT0 bits are set to extend the sampling period to
//  4xADC12CLKx256. A single conversion is performed on channel A0. The A/D
//  conversion results are stored in ADC12MEM0 and are moved to 'results' upon
//  completion of the conversion. Test by setting and running to a break point
//  at the "_BIC..." instruction in the ISR. To view the conversion results,
//  open a watch window in debugger and view 'results.'
//
//
//                MSP430F149
//             ---------------
//            |               |
//     Vin -->|P6.0/A0        |
//            |               |
//
//  M.Mitchell
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************

#include  <msp430x14x.h>

static unsigned int results;                // Needs to be global in this example
                                            // Otherwise, the compiler removes it
                                            // because it is not used for anything.

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop watchdog timer
  P6SEL |= 0x01;                            // Enable A/D channel A0
  ADC12CTL0 = ADC12ON+SHT0_15;              // Turn on ADC12, set sampling time
  ADC12CTL1 = SHP;                          // Use sampling timer, set mode
  ADC12IE = 0x01;                           // Enable ADC12IFG.0
  ADC12CTL0 |= ENC;                         // Enable conversions

  while(1)
  {
  ADC12CTL0 |= ADC12SC;                     // Start conversion
  _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0, Enable interrupts
   }
}

#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR (void)
{
  results = ADC12MEM0;                      // Move results, IFG is cleared
  _BIC_SR_IRQ(LPM0_bits);                   // Clear LPM0, SET BREAKPOINT HERE
}
