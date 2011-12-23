//*******************************************************************************
//  MSP430xG46x Demo - Timer_A, PWM TA1-2, Up Mode, 32kHz ACLK
//
//  Description: This program outputs two PWM signals on P1.2 and P2.0 using
//  Timer_A configured for up mode. The value in TACCR0 defines the PWM period
//  and the values in TACCR1 and TACCR2 the PWM duty cycles. Using 32kHz ACLK as
//  TACLK, the timer period is 15.6ms with a 75% duty cycle on P1.2 and 25%
//  on P2.0. Normal operating mode is LPM3.
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//	
//
//               MSP430xG461x
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32kHz
//         --|RST          XOUT|-
//           |                 |
//           |             P1.2|--> TACCR1 - 75% PWM
//           |             P2.0|--> TACCR2 - 25% PWM
//
//  K. Quiring/ M. Mitchell
//  Texas Instruments Inc.
//  October 2006
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include <msp430xG46x.h>

void main(void)
{
  volatile unsigned int i;

  WDTCTL = WDTPW +WDTHOLD;                  // Stop WDT
  FLL_CTL0 |= XCAP14PF;                     // Configure load caps

  // Wait for xtal to stabilize
  do
  {
  IFG1 &= ~OFIFG;                           // Clear OSCFault flag
  for (i = 0x47FF; i > 0; i--);             // Time for flag to set
  }
  while ((IFG1 & OFIFG));                   // OSCFault flag still set?

  P1DIR |= 0x04;                            // P1.2 output
  P1SEL |= 0x04;                            // P1.2 TA1 option
  P2DIR |= 0x01;                            // P2.0 output
  P2SEL |= 0x01;                            // P2.0 TA2 option
  TACCR0 = 512-1;                           // PWM Period
  TACCTL1 = OUTMOD_7;                       // TACCR1 reset/set
  TACCR1 = 384;                             // TACCR1 PWM duty cycle
  TACCTL2 = OUTMOD_7;                       // TACCR2 reset/set
  TACCR2 = 128;                             // TACCR2 PWM duty cycle
  TACTL = TASSEL_1 + MC_1;                  // ACLK, up mode

  _BIS_SR(LPM3_bits);                       // Enter LPM3
}

