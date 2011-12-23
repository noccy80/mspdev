//******************************************************************************
//  MSP430G2xx1 Demo - Timer_A, PWM TA1, Up/Down Mode, 32kHz ACLK
//
//  Description: This program generates one PWM output on P1.2 using
//  Timer_A configured for up/down mode. The value in CCR0, 128, defines the
//  PWM period/2 and the value in CCR1 the PWM duty cycle. Using
//  32kHz ACLK as TACLK, the timer period is 7.8ms with a 75% duty cycle on
//  P1.2. Normal operating mode is LPM3.
//  ACLK = TACLK = LFXT1 = 32768Hz, MCLK = default DCO
//  //* External watch crystal installed on XIN XOUT is required for ACLK *//	
//
//               MSP430G2xx1
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32kHz
//         --|RST          XOUT|-
//           |                 |
//           |         P1.2/TA1|--> CCR1 - 75% PWM
//
//  D. Dang
//  Texas Instruments, Inc
//  October 2010
//  Built with CCS Version 4.2.0 and IAR Embedded Workbench Version: 5.10
//******************************************************************************

#include  <msp430g2231.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= 0x0C;                            // P1.2 and P1.3 output
  P1SEL |= 0x0C;                            // P1.2 and P1.3 TA1/2 otions
  CCR0 = 128;                               // PWM Period/2
  CCTL1 = OUTMOD_6;                         // CCR1 toggle/set
  CCR1 = 32;                                // CCR1 PWM duty cycle
  TACTL = TASSEL_1 + MC_3;                  // ACLK, up-down mode

  _BIS_SR(LPM3_bits);                       // Enter LPM3
}

