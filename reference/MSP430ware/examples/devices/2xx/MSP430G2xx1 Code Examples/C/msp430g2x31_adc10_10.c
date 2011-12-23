//******************************************************************************
//  MSP430G2x31 Demo - ADC10, DTC Sample A2-0, AVcc, Single Sequence, DCO
//
//  Description: Sample A3/A2/A1 as single sequence with reference to AVcc.
//  Software sets ADC10SC to trigger sample sequence. In Mainloop MSP430 waits
//  in LPM0 to save power until ADC10 conversion complete, ADC10_ISR(DTC) will
//  force exit from any LPMx in Mainloop on reti. ADC10_ISR will force any LPMx
//  exit. ADC10 internal oscillator times sample period (16x) and conversion
//  (13x). DTC transfers conversion code to RAM 200h - 206h. P1.0 set at start
//  of conversion burst, reset on completion.
//
//               MSP430G2x31
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//       >---|P1.3/A3      P1.0|-->LED
//       >---|P1.2/A2          |
//       >---|P1.1/A1          |
//
//  D. Dang
//  Texas Instruments Inc.
//  October 2010
//  Built with CCS Version 4.2.0 and IAR Embedded Workbench Version: 5.10
//******************************************************************************
#include  "msp430g2231.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  ADC10CTL1 = INCH_3 + CONSEQ_1;            // A3/A2/A1, single sequence
  ADC10CTL0 = ADC10SHT_2 + MSC + ADC10ON + ADC10IE;
  ADC10DTC1 = 0x03;                         // 3 conversions
  ADC10AE0 |= 0x0E;                         // P1.3,2,1 ADC10 option select
  P1DIR |= 0x01;                            // Set P1.0 output

  for (;;)
  {
    ADC10CTL0 &= ~ENC;
    while (ADC10CTL1 & BUSY);               // Wait if ADC10 core is active
    ADC10SA = 0x200;                        // Data buffer start
    P1OUT |= 0x01;                          // P1.0 = 1
    ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
    __bis_SR_register(CPUOFF + GIE);        // LPM0, ADC10_ISR will force exit
    P1OUT &= ~0x01;                         // P1.0 = 0
  }
}

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
  __bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)
}
