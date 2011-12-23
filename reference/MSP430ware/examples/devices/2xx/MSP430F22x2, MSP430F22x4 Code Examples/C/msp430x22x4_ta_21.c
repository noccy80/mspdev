//******************************************************************************
//  MSP430F22x4 Demo - Timer_A, PWM TA1-2, Up/Down Mode, HF XTAL ACLK
//
//  Description: This program generates two PWM outputs on P1.2/1.3 using
//  Timer_A configured for up/down mode. The value in TACCR0, 128, defines the
//  PWM period/2 and the values in TACCR1 and TACCR2 the PWM duty cycles.
//  Using HF XTAL ACLK as TACLK, the timer period is HF XTAL/256 with a 75%
//  duty cycle on P1.2 and 25% on P1.3.
//  ACLK = MCLK = TACLK = HF XTAL
//  //* HF XTAL REQUIRED AND NOT INSTALLED ON FET *//
//  //* Min Vcc required varies with MCLK frequency - refer to datasheet *//
//
//               MSP430F22x4
//            -----------------
//        /|\|              XIN|-
//         | |                 | HF XTAL (3 – 16MHz crystal or resonator)
//         --|RST          XOUT|-
//           |                 |
//           |         P1.2/TA1|--> TACCR1 - 75% PWM
//           |         P1.3/TA2|--> TACCR2 - 25% PWM
//
//  A. Dannenberg
//  Texas Instruments Inc.
//  April 2006
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x22x4.h"

void main(void)
{
  volatile unsigned int i;
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  BCSCTL1 |= XTS;                           // ACLK= LFXT1= HF XTAL
  BCSCTL3 |= LFXT1S1;                       // LFXT1S1 = 3-16MHz

  do
  {
    IFG1 &= ~OFIFG;                         // Clear OSCFault flag
    for (i = 0xFF; i > 0; i--);             // Time for flag to set
  }
  while (IFG1 & OFIFG);                     // OSCFault flag still set?

  BCSCTL2 |= SELM_3;                        // MCLK= LFXT1 (safe)
  P1DIR |= 0x0C;                            // P1.2 and P1.3 output
  P1SEL |= 0x0C;                            // P1.2 and P1.3 TA1/2 otions
  TACCR0 = 128;                             // PWM Period/2
  TACCTL1 = OUTMOD_6;                       // TACCR1 toggle/set
  TACCR1 = 32;                              // TACCR1 PWM duty cycle
  TACCTL2 = OUTMOD_6;                       // TACCR2 toggle/set
  TACCR2 = 96;                              // TACCR2 PWM duty cycle
  TACTL = TASSEL_1 + MC_3;                  // ACLK, up-down mode

  __bis_SR_register(LPM0_bits);             // Enter LPM0
}

