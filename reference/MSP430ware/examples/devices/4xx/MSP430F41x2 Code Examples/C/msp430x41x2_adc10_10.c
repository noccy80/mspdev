//******************************************************************************
//  MSP430F41x2 Demo - ADC10, DTC Sample A2-0, AVcc, Single Sequence, DCO
//
//  Description: Sample A2/A1/A0 as single sequence with reference to AVcc.
//  Software sets ADC10SC to trigger sample sequence. In Mainloop MSP430 waits
//  in LPM0 to save power until ADC10 conversion complete, ADC10_ISR(DTC) will
//  force exit from any LPMx in Mainloop on reti. 
//  ADC10 internal oscillator times sample period (16x) and conversion
//  (13x). DTC transfers conversion code to RAM 200h - 206h. P5.1 set at start
//  of conversion burst, reset on completion.
//
//               MSP430F41x2
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//       >---|P6.0/A2      P5.1|-->LED
//       >---|P7.5/A1          |
//       >---|P7.4/A0          |
//
//  P. Thanigai
//  Texas Instruments Inc.
//  January 2009
//  Built with CCE Version: 3.1 and IAR Embedded Workbench Version: 4.11
//******************************************************************************
#include "msp430x41x2.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  ADC10CTL1 = INCH_2 + CONSEQ_1;            // A2/A1/A0, single sequence
  ADC10CTL0 = ADC10SHT_2 + MSC + ADC10ON + ADC10IE;
  ADC10DTC1 = 0x03;                         // 3 conversions
  ADC10AE0 |= 0x07;                         // P7.4,7.5,6.0 ADC10 option select
  P5DIR |= 0x02;                            // Set P5.1 output

  for (;;)
  {
    ADC10CTL0 &= ~ENC;
    while (ADC10CTL1 & BUSY);               // Wait if ADC10 core is active
    ADC10SA = 0x200;                        // Data buffer start
    P5OUT |= 0x02;                          // P5.1 set
    ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
    __bis_SR_register(CPUOFF + GIE);        // LPM0, ADC10_ISR will force exit
    P5OUT &= ~0x02;                         // P5.1 reset
  }
}

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
  __bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)
}
