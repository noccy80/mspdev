//******************************************************************************
//  MSP-FET430P430 Demo - ADC12, Sequence of Conversions (non-repeated)
//
//  This example shows how to perform A/D conversions on a sequence of channels.
//  A single sequence of conversions is performed - one conversion each on
//  channels A0, A1, A2, and A3. Each conversion uses AVcc and AVss for the
//  references. The conversion results are stored in ADC12MEM0, ADC12MEM1,
//  ADC12MEM2, and ADC12MEM3 respectively and are moved to 'results[]' upon
//  completion of the sequence. Test by applying voltages to pins A0, A1, A2,
//  and A3, then setting and running to a break point at the "_BIC..."
//  instruction in the ISR. To view the conversion results, open a watch window
//  with the debugger and view 'results' or view ADC12MEM0, ADC12MEM1,
//  ADC12MEM2, and ADC12MEM3 in a register window.
//  ACLK = n/a, MCLK = SMCLK = default DCO, ADC12CLK = ADC12OSC
//
//  Note that a sequence has no restrictions on which channels are converted.
//  For example, a valid sequence could be A0, A3, A2, A4, A2, A1, A0, and A7.
//  See the MSP430x4xx User's Guide for instructions on using the ADC12.
//
//
//               MSP430FG439
//            -----------------
//           |                 |
//   Vin0 -->|P6.0/A0          |
//   Vin1 -->|P6.1/A1          |
//   Vin2 -->|P6.2/A2          |
//   Vin3 -->|P6.3/A3          |
//           |                 |
//
//
//  M. Mitchell
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************
#include  <msp430xG43x.h>

// Needs to be global in this example. Otherwise, the
// compiler removes it because it is not used
static unsigned int results[4];

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop watchdog timer
  P6SEL = 0x0F;                             // Enable A/D channel inputs
  ADC12CTL0 = ADC12ON+MSC+SHT0_2;           // Turn on ADC12, set sampling time
  ADC12CTL1 = SHP+CONSEQ_1;                 // Use sampling timer, single sequ
  ADC12MCTL0 = INCH_0;                      // ref+=AVcc, channel = A0
  ADC12MCTL1 = INCH_1;                      // ref+=AVcc, channel = A1
  ADC12MCTL2 = INCH_2;                      // ref+=AVcc, channel = A2
  ADC12MCTL3 = INCH_3+EOS;                  // ref+=AVcc, channel = A3, end seq
  ADC12IE = 0x08;                           // Enable ADC12IFG.3
  ADC12CTL0 |= ENC;                         // Enable conversions
  _EINT();                                  // Enable interrupts

  while(1)
  {
    ADC12CTL0 |= ADC12SC;                   // Start conversion
    _BIS_SR(LPM0_bits);                     // Enter LPM0
  }
}

#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR (void)
{
  results[0] = ADC12MEM0;                   // Move results, IFG is cleared
  results[1] = ADC12MEM1;                   // Move results, IFG is cleared
  results[2] = ADC12MEM2;                   // Move results, IFG is cleared
  results[3] = ADC12MEM3;                   // Move results, IFG is cleared
  _BIC_SR_IRQ(LPM0_bits);                   // Clear LPM0, SET BREAKPOINT HERE
}
