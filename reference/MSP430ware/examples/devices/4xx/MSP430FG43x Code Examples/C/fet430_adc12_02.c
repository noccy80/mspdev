//******************************************************************************
//  MSP-FET430P430 Demo - ADC12, Single Conversion on Single Channel
//
//  This example shows how to perform a single ADC12 conversion on a single
//  channel. It uses AVcc for the reference and performs a single conversion on
//  channel A0. The conversion results are stored in ADC12MEM0. Test by applying
//  a voltage to channel A0, then setting and running to a break point at the
//  "_NOP()" instruction. To view the conversion results, open a register window
//  ACLK = n/a, MCLK = SMCLK = default DCO, ADC12CLK = ADC12OSC
//  with the debugger and view the contents of ADC12MEM0.
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
  WDTCTL = WDTPW+WDTHOLD;                   // Stop watchdog timer
  P6SEL |= 0x01;                            // Enable A/D channel A0
  ADC12CTL0 = ADC12ON+SHT0_2;               // Turn on ADC12, set sampling time
  ADC12CTL1 = SHP;                          // Use sampling timer
  ADC12CTL0 |= ENC;                         // Enable conversions

  while (1)
  {
    ADC12CTL0 |= ADC12SC;                   // Start conversion
    while ((ADC12IFG & BIT0)==0);
    _NOP();                                 // SET BREAKPOINT HERE
  }
}
