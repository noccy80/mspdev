//******************************************************************************
//  MSP430xG461x Demo - ADC12, Using 10 External Channels for Conversion
//
//  This example shows how to perform A/D conversion on up to 10 external
//  channels by showing that channels A8 and A9 can be used for conversion
//  of external signals. A single sequence of conversions is performed - one
//  conversion on A8 and then one conversion on A9. Each conversion uses AVcc
//  and AVss for the references. The conversion results are stored in ADC12MEM0
//  and ADC12MEM1 respectively and are moved to Results[] upon completion of
//  the sequence. Test by applying voltages to pins VeREF+ for A8 and
//  VREF/VeREF- for A9, then setting and running to a break point at the
//  "__no_operation()" instruction in the ISR. To view the conversion results,
//  open a watch window with the debugger and view Results[] or view ADC12MEM0
//  and ADC12MEM1 in a register window.
//  *NOTE*  When using channels A8 and A9 for external signals, internal
//  references must be used for the conversions (see MSP430x4xx Family
//  User's Guide).
//  ACLK = 32kHz, MCLK = SMCLK = default DCO 1048576Hz, ADC12CLK = ADC12OSC
//
//
//               MSP430xG461x
//            -------------------
//           |                XIN|-
//   Vin1 -->|VeREF+             | 32kHz
//   Vin2 -->|VREF-/VeREF-   XOUT|-
//
//
//   A. Dannenberg/ M. Mitchell
//   Texas Instruments Inc.
//   October 2006
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430xG46x.h"

volatile unsigned int Results[2];

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  ADC12CTL0 = ADC12ON + MSC + SHT0_15;      // Turn on ADC12, set sampling time
  ADC12CTL1 = SHP + CONSEQ_1;               // Use sampling timer, single seq
  ADC12MCTL0 = INCH_8;                      // ref+=AVcc, chan = A8
  ADC12MCTL1 = INCH_9 + EOS;                // ref+=AVcc, chan = A9, end seq
  ADC12IE = 0x02;                           // Enable ADC12IFG.1
  ADC12CTL0 |= ENC;                         // Enable conversions
  __enable_interrupt();                     // Enable interrupts

  while(1)
  {
    ADC12CTL0 |= ADC12SC;                   // Start conversion
    __bis_SR_register(LPM0_bits);           // Enter LPM0
  }
}

#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR (void)
{
  Results[0] = ADC12MEM0;                   // Move results, IFG is cleared
  Results[1] = ADC12MEM1;                   // Move results, IFG is cleared
  __no_operation();                         // SET BREAKPOINT HERE
  __bic_SR_register_on_exit(LPM0_bits);     // Exit LPM0
}
