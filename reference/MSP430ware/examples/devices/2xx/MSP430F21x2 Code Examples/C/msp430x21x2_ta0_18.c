//******************************************************************************
//  MSP430F21x2 Demo - Timer0_A3, PWM TA0_1 - TA0_2, Up Mode, HF XTAL ACLK
//
//  Description: This program generates two PWM outputs on P1.2,3 using
//  Timer0_A3 configured for up mode. The value in TA0CCR0, 512-1, defines the
//  period and the values in TA0CCR1 and TA0CCR2 the PWM duty cycles. Using
//  HF XTAL ACLK as TA0CLK, the timer period is HF XTAL/512 with a 75% duty
//  cycle on P1.2 and 25% on P1.3.
//  ACLK = MCLK = TA0CLK = HF XTAL
//  //* HF XTAL REQUIRED AND NOT INSTALLED ON FET *//
//  //* Min Vcc required varies with MCLK frequency - refer to datasheet *//
//
//               MSP430F21x2
//            -----------------
//        /|\|              XIN|-
//         | |                 | HF XTAL (3 – 16MHz crystal or resonator)
//         --|RST          XOUT|-
//           |                 |
//           |       P1.2/TA0_1|--> TA0CCR1 - 75% PWM
//           |       P1.3/TA0_2|--> TA0CCR2 - 25% PWM
//
//  A. Dannenberg
//  Texas Instruments Inc.
//  January 2008
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x21x2.h"

void main(void)
{
  volatile unsigned int i;
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  BCSCTL1 |= XTS;                           // ACLK = LFXT1 = HF XTAL
  BCSCTL3 |= LFXT1S1;                       // LFXT1S1 = 3-16Mhz

  do
  {
    IFG1 &= ~OFIFG;                         // Clear OSCFault flag
    for (i = 0xFF; i > 0; i--);             // Time for flag to set
  }
  while (IFG1 & OFIFG);                     // OSCFault flag still set?
  BCSCTL2 |= SELM_3;                        // MCLK= LFXT1 (safe)

  P1DIR |= 0x0C;                            // P1.2 and P1.3 output
  P1SEL |= 0x0C;                            // P1.2 and P1.3 TA1/2 otions
  TA0CCR0 = 512 - 1;                         // PWM Period
  TA0CCTL1 = OUTMOD_7;                       // TA0CCR1 reset/set
  TA0CCR1 = 384;                             // TA0CCR1 PWM duty cycle
  TA0CCTL2 = OUTMOD_7;                       // TA0CCR2 reset/set
  TA0CCR2 = 128;                             // TA0CCR2 PWM duty cycle
  TA0CTL = TASSEL_1 + MC_1;                  // ACLK, up mode

  __bis_SR_register(LPM0_bits);             // Enter LPM0
}

