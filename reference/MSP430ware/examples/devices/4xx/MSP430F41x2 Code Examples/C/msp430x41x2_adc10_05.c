//******************************************************************************
//  MSP430x41x2 Demo - ADC10, Sample A11, Lo_Batt, Set P5.1 if AVcc < 2.3V
//
//  Description: A single sample is made on A11 (AVcc/2) with reference to
//  internal 1.5V Vref. Software sets ADC10SC to start sample and conversion
//  - ADC10SC automatically cleared at EOC. ADC10 internal oscillator times
//  sample (16x) and conversion. ADC10BUSY flag is polled for EOC. If A11
//  (AVcc/2) < 0311h (1.15V) indicating AVcc is less 2.3V, P5.1 set indicating
//  a lo_Batt condition, else reset.
//
//                MSP430x41x2
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |A11 (AVcc/2) P5.1|-->LED
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
  ADC10CTL1 = INCH_11;                      // AVcc/2
  ADC10CTL0 = SREF_1 + ADC10SHT_2 + REFON + ADC10ON;
  TACCR0 = 30;                              // Delay to allow Ref to settle
  TACCTL0 |= CCIE;                          // Compare-mode interrupt
  TACTL = TASSEL_2 + MC_1;                  // TACLK = SMCLK, Up mode
  __bis_SR_register(CPUOFF + GIE);          // LPM0, TA0_ISR will force exit
  TACCTL0 &= ~CCIE;                         // Disable timer Interrupt
  P5DIR |= 0x02;                            // Set P5.1 to output direction

  for (;;)
  {
    ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
     while (!(ADC10IFG & ADC10CTL0));       // ADC10 Conversion Complete?
    if (ADC10MEM < 0x311)                   // ADC10MEM = A11 > 1.15V?
      P5OUT |= 0x02;                        // Set P5.1 LED on
    else
      P5OUT &= ~0x02;                       // Clear P5.1 LED off
  }
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void TA0_ISR(void)
{
  TACTL = 0;                                // Clear Timer_A control registers
  LPM0_EXIT;                                // Exit LPM0 on return
}
