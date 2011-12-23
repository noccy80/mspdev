//*******************************************************************************
//  MSP430x26x Demo - Timer_A, PWM TA1-2, Up/Down Mode, 32kHz ACLK
//
//  Description: This program generates two PWM outputs on P1.2,3 using
//  Timer_A configured for up/down mode. The value in CCR0, 128, defines the
//  PWM period/2 and the values in CCR1 and CCR2 the PWM duty cycles. Using
//  32kHz ACLK as TACLK, the timer period is 7.8ms with a 75% duty cycle
//  on P1.2 and 25% on P1.3. Normal operating mode is LPM3
//  ACLK = TACLK = LFXT1 = 32768Hz, MCLK = default DCO ~1.045MHz.
//  //* External watch crystal on XIN XOUT is required for ACLK *//	
//
//               MSP430F261x/241x
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32kHz
//         --|RST          XOUT|-
//           |                 |
//           |         P1.2/TA1|--> CCR1 - 75% PWM
//           |         P1.3/TA2|--> CCR2 - 25% PWM
//
//  B. Nisarga
//  Texas Instruments Inc.
//  September 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//******************************************************************************

#include  <msp430x26x.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= 0x0C;                            // P1.2 and P1.3 output
  P1SEL |= 0x0C;                            // P1.2 and P1.3 TA1/2 otions
  CCR0 = 128;                               // PWM Period/2
  CCTL1 = OUTMOD_6;                         // CCR1 toggle/set
  CCR1 = 32;                                // CCR1 PWM duty cycle
  CCTL2 = OUTMOD_6;                         // CCR2 toggle/set
  CCR2 = 96;                                // CCR2 PWM duty cycle
  TACTL = TASSEL_1 + MC_3;                  // ACLK, up-down mode

  _BIS_SR(LPM3_bits);                       // Enter LPM3
}

