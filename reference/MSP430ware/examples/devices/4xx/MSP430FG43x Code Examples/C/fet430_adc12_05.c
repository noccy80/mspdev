//******************************************************************************
//  MSP-FET430P430 Demo - ADC12, Using the Internal Reference
//
//  This example shows how to use the internal reference of the ADC12.
//  It uses the internal 2.5V reference and performs a single conversion
//  on channel A0. The conversion results are stored in ADC12MEM0. Test by
//  applying a voltage to channel A0, then setting and running to a break point
//  at the "_NOP()" instruction. To view the conversion results, open a
//  register window with the debugger and view the contents of ADC12MEM0.
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

void main(void)
{
  volatile unsigned int i;
  WDTCTL = WDTPW+WDTHOLD;                   // Stop watchdog timer
  P6SEL |= 0x01;                            // Enable A/D channel A0
  ADC12CTL0 = ADC12ON+SHT0_2+REFON+REF2_5V; // Turn on and set up ADC12
  ADC12CTL1 = SHP;                          // Use sampling timer
  ADC12MCTL0 = SREF_1;                      // Vr+=Vref+

  for ( i=0; i<0x3600; i++)                 // Delay for reference start-up
  {
  }

  ADC12CTL0 |= ENC;                         // Enable conversions

  while (1)
  {
    ADC12CTL0 |= ADC12SC;                   // Start conversion
    while ((ADC12IFG & BIT0)==0);
    _NOP();                                 // SET BREAKPOINT HERE
  }
}
