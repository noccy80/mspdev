//******************************************************************************
//   MSP430F22x4 Demo - ADC10, DTC Sample A0 -> TA1, AVcc, DCO
//
//   Description: Use DTC to sample A0 with reference to AVcc and directly
//   transfer code to TACCR1. Timer_A has been configured for 10-bit PWM mode.
//   TACCR1 duty cycle is automatically proportional to ADC10 A0. WDT_ISR used
//   as a period wakeup timer approximately 27ms based on default ~1.2MHz
//   DCO/SMCLK clock source used in this example for the WDT clock source.
//   Timer_A also uses default DCO.
//
//                MSP430F22x4
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//        >---|P2.0/A0      P1.2|--> TACCR1 - 0-1024 PWM
//
//   A. Dannenberg
//   Texas Instruments Inc.
//   October 2006
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x22x4.h"

void main(void)
{
  WDTCTL = WDT_MDLY_32;                     // WDT ~27ms interval timer
  IE1 |= WDTIE;                             // Enable WDT interrupt
  ADC10CTL0 = ADC10SHT_2 + ADC10ON;
  ADC10AE0 |= 0x01;                         // P2.0 ADC option select
  ADC10DTC1 = 0x01;                         // 1 conversion
  P1DIR |= 0x04;                            // P1.2 = output
  P1SEL |= 0x04;                            // P1.2 = TA1 output
  TACCR0 = 1024 - 1;                        // PWM Period
  TACCTL1 = OUTMOD_7;                       // TACCR1 reset/set
  TACCR1 = 512;                             // TACCR1 PWM Duty Cycle
  TACTL = TASSEL_2 + MC_1;                  // SMCLK, upmode

  while(1)
  {
    __bis_SR_register(LPM0_bits + GIE);     // LPM0, WDT_ISR will force exit
    ADC10SA = (unsigned int)&TACCR1;        // Data transfer location
    ADC10CTL0 |= ENC + ADC10SC;             // Start sampling
  }
}

#pragma vector = WDT_VECTOR
__interrupt void WDT_ISR(void)
{
  __bic_SR_register_on_exit(LPM0_bits);     // Exit LPM0
}

