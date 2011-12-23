//******************************************************************************
//  MSP430F41x2 Demo - ADC10, DTC Sample A0 64x, AVcc, Repeat Single, DCO
//
//  Description: Use DTC to sample A0 64 times with reference to AVcc. Software
//  writes to ADC10SC to trigger sample burst. In Mainloop MSP430 waits in LPM0
//  to save power until ADC10 conversion burst complete, ADC10_ISR(DTC) will
//  force exit from LPM0 in Mainloop on reti. ADC10 internal oscillator
//  times sample period (16x) and conversion (13x). DTC transfers conversion
//  code to RAM 200h - 280h. P5.1 set at start of conversion burst, reset on
//  completion.
//
//                MSP430F41x2
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//        >---|P7.4/A0      P5.1|-->LED
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
  ADC10CTL1 = CONSEQ_2;                     // Repeat single channel
  ADC10CTL0 = ADC10SHT_2 + MSC + ADC10ON + ADC10IE; // ADC10ON, interrupt enabl
  ADC10DTC1 = 0x40;                         // 64 conversions
  ADC10AE0 |= 0x01;                         // P7.4 ADC option select
  P5DIR |= 0x02;                            // Set P5.1 to output direction

  for (;;)
  {
    ADC10CTL0 &= ~ENC;
    while (ADC10CTL1 & BUSY);               // Wait if ADC10 core is active
    ADC10SA = 0x200;                        // Data buffer start
    P5OUT |= 0x02;                          // Set P5.1 LED on
    ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
    __bis_SR_register(CPUOFF + GIE);        // LPM0, ADC10_ISR will force exit
    P5OUT &= ~0x02;                         // Clear P5.1 LED off
  }
}

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
  __bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)
}
