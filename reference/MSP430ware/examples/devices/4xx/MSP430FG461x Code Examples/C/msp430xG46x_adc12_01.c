//******************************************************************************
//   MSP430xG461x Demo - ADC12, Sample A0, Set P5.1 if A0 > 0.5*AVcc
//
//   Description: A single sample is made on A0 with reference to AVcc.
//   Software sets ADC12SC to start sample and conversion - ADC12SC
//   automatically cleared at EOC. ADC12 internal oscillator times sample (16x)
//   and conversion. In Mainloop MSP430 waits in LPM0 to save power until ADC12
//   conversion complete, ADC12_ISR will force exit from LPM0 in Mainloop on
//   reti. If A0 > 0.5*AVcc, P5.1 set, else reset.
//   ACLK = 32kHz, MCLK = SMCLK = default DCO 1048576Hz, ADC12CLK = ADC12OSC
//
//                MSP430xG461x
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//     Vin -->|P6.0/A0      P5.1|--> LED
//
//   A. Dannenberg/ M. Mitchell
//   Texas Instruments Inc.
//   October 2006
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430xG46x.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  ADC12CTL0 = SHT0_2 + ADC12ON;             // Sampling time, ADC12 on
  ADC12CTL1 = SHP;                          // Use sampling timer
  ADC12IE = 0x01;                           // Enable interrupt
  ADC12CTL0 |= ENC;
  P6SEL |= 0x01;                            // P6.0 ADC option select
  P5DIR |= 0x02;                            // P5.1 output

  while (1)
  {
    ADC12CTL0 |= ADC12SC;                   // Start sampling/conversion
    __bis_SR_register(LPM0_bits + GIE);     // LPM0, ADC12_ISR will force exit
  }
}

#pragma vector = ADC12_VECTOR
__interrupt void ADC12_ISR(void)
{
  if (ADC12MEM0 >= 0x7ff)                   // ADC12MEM = A0 > 0.5AVcc?
    P5OUT |= 0x02;                          // P5.1 = 1
  else
    P5OUT &= ~0x02;                         // P5.1 = 0

  __bic_SR_register_on_exit(LPM0_bits);     // Exit LPM0
}
