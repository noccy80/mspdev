//******************************************************************************
//   MSP430F22x4 Demo - Timer_B, PWM TB1-2, Up Mode, HF XTAL ACLK
//
//   Description: This program generates two PWM outputs on P4.1,2 using
//   Timer_B configured for up mode. The value in TBCCR0, 512-1, defines the PWM
//   period and the values in TBCCR1-2 the PWM duty cycles. Using HF XTAL ACLK
//   as TBCLK, the timer period is HF XTAL/512 with a 75% duty cycle on P4.1
//   and 25% on P4.2.
//   ACLK = MCLK = TBCLK = HF XTAL
//   //* HF XTAL REQUIRED AND NOT INSTALLED ON FET *//
//   //* Min Vcc required varies with MCLK frequency - refer to datasheet *//
//
//                MSP430F22x4
//             -----------------
//         /|\|              XIN|-
//          | |                 | HF XTAL (3 – 16MHz crystal or resonator)
//          --|RST          XOUT|-
//            |                 |
//            |         P4.1/TB1|--> TBCCR1 - 75% PWM
//            |         P4.2/TB2|--> TBCCR2 - 25% PWM
//
//   A. Dannenberg
//   Texas Instruments Inc.
//   April 2006
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x22x4.h"

void main(void)
{
  volatile unsigned int i;

  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P4DIR |= 0x06;                            // P4.1 and P4.2 output
  P4SEL |= 0x06;                            // P4.1 and P4.2 TB1/2 otions

  BCSCTL1 |= XTS;                           // LFXT1 = HF XTAL
  BCSCTL3 = LFXT1S1;                        // LFXT1S1 = 3-16MHz
  do
  {
    IFG1 &= ~OFIFG;                         // Clear OSC fault flag
    i = 0xFF;                               // i = Delay
    while (i--);                            // Additional delay to ensure start
  }
  while (OFIFG & IFG1);                     // OSC fault flag set?
  BCSCTL2 |= SELM_3;                        // MCLK = LFXT1

  TBCCR0 = 512 - 1;                         // PWM Period
  TBCCTL1 = OUTMOD_7;                       // TBCCR1 reset/set
  TBCCR1 = 384;                             // TBCCR1 PWM Duty Cycle
  TBCCTL2 = OUTMOD_7;                       // TBCCR2 reset/set
  TBCCR2 = 128;                             // TBCCR2 PWM duty cycle
  TBCTL = TBSSEL_1 + MC_1;                  // ACLK, upmode

  __bis_SR_register(LPM0_bits);             // CPU off
}


