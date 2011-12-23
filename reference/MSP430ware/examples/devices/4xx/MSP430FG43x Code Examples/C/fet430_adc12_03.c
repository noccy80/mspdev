//******************************************************************************
//  MSP-FET430P430 Demo - ADC12, Using an External Reference
//
//  This example shows how to use an external positive reference for the ADC12.
//  The external reference is applied to the VeREF+ pin. AVss is used for the
//  negative reference. A single conversion is performed on channel A0. The
//  conversion results are stored in ADC12MEM0. Test by applying a voltage to
//  channel A0, then setting and running to a break point at the "_NOP()"
//  instruction. To view the conversion results, open a register window
//  with the debugger and view the contents of ADC12MEM0.
//  ACLK = n/a, MCLK = SMCLK = default DCO, ADC12CLK = ADC12OSC
//
//
//                  MSP430FG439
//                ---------------
//               |               |
//        Vin -->|P6.0/A0        |
//               |               |
//        REF -->|VeREF+         |
//               |               |
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
  ADC12MCTL0 = SREF_2;                      // Vr+ = VeREF+ (external)
  ADC12CTL0 |= ENC;                         // Enable conversions

  while (1)
  {
    ADC12CTL0 |= ADC12SC;                   // Start conversion
    while ((ADC12IFG & ADC12BUSY)==0);
    _NOP();                                 // SET BREAKPOINT HERE
  }
}
