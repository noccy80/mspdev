//******************************************************************************
//  MSP430G2x31 Demo - ADC10, DTC Sample A1 32x, AVcc, Repeat Single, DCO
//
//  Description: Use DTC to sample A1 32 times with reference to AVcc. Software
//  writes to ADC10SC to trigger sample burst. In Mainloop MSP430 waits in LPM0
//  to save power until ADC10 conversion burst complete, ADC10_ISR(DTC) will
//  force exit from any LPMx in Mainloop on reti. ADC10 internal oscillator
//  times sample period (16x) and conversion (13x). DTC transfers conversion
//  code to RAM 200h - 240h. P1.0 set at start of conversion burst, reset on
//  completion.
//
//                MSP430G2x31
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//        >---|P1.1/A1      P1.0|-->LED
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
  ADC10CTL1 = CONSEQ_2 + INCH_1;            // Repeat single channel, A1
  ADC10CTL0 = ADC10SHT_2 + MSC + ADC10ON + ADC10IE; // ADC10ON, interrupt enabl
  ADC10DTC1 = 0x20;                         // 32 conversions
  ADC10AE0 |= 0x02;                         // P1.1 ADC option select
  P1DIR |= 0x01;                            // Set P1.0 to output direction

  for (;;)
  {
    ADC10CTL0 &= ~ENC;
    while (ADC10CTL1 & BUSY);               // Wait if ADC10 core is active
    ADC10SA = 0x200;                        // Data buffer start
    P1OUT |= 0x01;                          // Set P1.0 LED on
    ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
    __bis_SR_register(CPUOFF + GIE);        // LPM0, ADC10_ISR will force exit
    P1OUT &= ~0x01;                         // Clear P1.0 LED off
  }
}

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
  __bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)
}
