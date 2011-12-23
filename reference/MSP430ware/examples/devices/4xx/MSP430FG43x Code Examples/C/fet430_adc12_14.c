//******************************************************************************
//  MSP-FET430P430 Demo - ADC12, Single Conversion on Channel A15
//
//  This example shows how to perform a single ADC12 conversion on a single
//  channel. It uses AVcc for the reference and performs a single conversion on
//  channel A15. The conversion results are stored in ADC12MEM0. Test by
//  applying a voltage to channel A15, then setting and running to a break point
//  at the "_NOP()" instruction. To view the conversion results, open a
//  register window with the debugger and view the contents of ADC12MEM0.
//  ACLK = n/a, MCLK = SMCLK = default DCO, ADC12CLK = ADC12OSC
//
//               MSP430FG439
//             ---------------
//            |               |
//     Vin -->|P4.6/A15       |
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
  WDTCTL = WDTPW+WDTHOLD;                   // Stop watchdog timer
  P4SEL |= 0x40;                            // Enable A/D channel A0
  ADC12CTL0 = ADC12ON+SHT0_2;               // Turn on ADC12, set sampling time
  ADC12CTL1 = SHP;                          // Use sampling timer
  ADC12MCTL0 = INCH_15;                     // Input channel A15
  ADC12CTL0 |= ENC;                         // Enable conversions

  while (1)
  {
    ADC12CTL0 |= ADC12SC;                   // Start conversion
    while ((ADC12IFG & BIT0)==0);
    _NOP();                                 // SET BREAKPOINT HERE
  }
}
