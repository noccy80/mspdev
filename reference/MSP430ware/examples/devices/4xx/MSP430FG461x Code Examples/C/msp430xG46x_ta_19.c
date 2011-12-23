//*******************************************************************************
//  MSP430xG46x Demo - Timer_A, PWM TA1-2, Up/Down Mode, DCO SMCLK
//
//  Description: This program generates two PWM outputs on P1.2,P2.0 using
//  Timer_A configured for up/down mode. The value in TACCR0, 128, defines the
//  PWM period/2 and the values in TACCR1 and TACCR2 the PWM duty cycles. Using
//  ~1048kHz SMCLK as TACLK, the timer period is ~244us with a 75% duty cycle
//  on P1.2 and 25% on P2.0.
//  SMCLK = MCLK = TACLK = default DCO ~1048kHz.
//
//               MSP430FG4619
//            -----------------
//        /|\|              XIN|-
//         | |                 |  32kHz
//         --|RST          XOUT|-
//           |                 |
//           |         P1.2/TA1|--> TACCR1 - 75% PWM
//           |         P2.0/TA2|--> TACCR2 - 25% PWM
//
//  K. Quiring/ M. Mitchell
//  Texas Instruments Inc.
//  October 2006
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************

#include  <msp430xG46x.h>

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
  TACCR0 = 128;                             // PWM Period/2
  TACCTL1 = OUTMOD_6;                       // TACCR1 toggle/set
  TACCR1 = 32;                              // TACCR1 PWM duty cycle
  TACCTL2 = OUTMOD_6;                       // TACCR2 toggle/set
  TACCR2 = 96;                              // TACCR2 PWM duty cycle
  TACTL = TASSEL_2 + MC_3;                  // SMCLK, up-down mode

  _BIS_SR(CPUOFF);                          // Enter LPM0
}

