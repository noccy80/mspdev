//******************************************************************************
//  MSP430x26x Demo - ADC12, Using A8 and A9 Ext Channels for Conversion
//
//  Description: This example shows how to perform A/D conversion on up to 10
//  external channels by showing that channels A8 and A9 can be used for
//  conversion of external signals when not using these channels as external 
//  reference inputs. A single sequence of conversions is performed - one 
//  conversion on A8 and then one conversion on A9. Each conversion uses AVcc
//  and AVss for the references. The conversion results are stored in ADC12MEM0
//  and ADC12MEM1 respectively and are moved to 'results[]' upon completion of
//  the sequence. 
//  Test by applying voltages to pins VeREF+ for A8 and VREF-/VeREF- for A9, 
//  then setting and running to a break point at the "_BIC..." instruction in  
//  the ISR. To view the conversion results, open a watch window in debugger and
//  view 'results' or view ADC12MEM0 and ADC12MEM1 in an ADC12 SFR window.
//  This can run even in LPM4 mode as ADC has its own clock
//  *NOTE*  When using channels A8 and A9 for external signals, internal
//  references must be used for the conversions. Refer to figure 17-1 in the
//  MSP430x1xx Family User's Guide.
//
//             MSP430F261x/241x
//            -----------------
//           |                 |
//   Vin1 -->|VeREF+           |
//   Vin2 -->|VREF-/VeREF-     |
//
//
//  B. Nisarga
//  Texas Instruments Inc.
//  September 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//******************************************************************************

#include  <msp430x26x.h>

volatile unsigned int results[2];             // Needs to be global in this example
                                            // Otherwise, the compiler removes it
                                            // because it is not used for anything.

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop watchdog timer
  ADC12CTL0 = ADC12ON+MSC+SHT0_15;          // Turn on ADC12, set sampling time
  ADC12CTL1 = SHP+CONSEQ_1;                 // Use sampling timer, single sequence
  ADC12MCTL0 = INCH_8;                      // ref+=AVcc, channel = A8
  ADC12MCTL1 = INCH_9+EOS;                  // ref+=AVcc, channel = A9, end seq.
  ADC12IE = 0x02;                           // Enable ADC12IFG.1
  ADC12CTL0 |= ENC;                         // Enable conversions

  while(1)
  {
  ADC12CTL0 |= ADC12SC;                     // Start convn - software trigger
  _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0, Enable interrupts
  }
}

#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR (void)
{
  results[0] = ADC12MEM0;                   // Move results, IFG is cleared
  results[1] = ADC12MEM1;                   // Move results, IFG is cleared
  _BIC_SR_IRQ(LPM0_bits);                   // Clear LPM0, SET BREAKPOINT HERE
}
