//*******************************************************************************
//  MSP430F51x2 Demo - Timer0_A3, PWM TA0.1-2, Up Mode, 32kHz ACLK
//
//  Description: This program generates two PWM outputs on P3.6,P3.7 using
//  Timer0_A configured for up mode. The value in CCR0, 512-1, defines the PWM
//  period and the values in CCR1 and CCR2 the PWM duty cycles. Using 32kHz
//  ACLK as TACLK, the timer period is ~ (512/32k) ~ 15.6ms with a 75% duty
//  cycle on P3.6 and 25% on P3.5. Normal operating mode is LPM3.
//  ACLK = TACLK = 32768Hz, MCLK = default DCO ~1.045MHz.
//
//                MSP430F51x2
//            -------------------
//        /|\ |              XIN|-
//         |  |                 | 32kHz
//         ---|RST          XOUT|-
//           |                   |
//           |      P3.6/PM_TA0.1|--> CCR1 - 75% PWM
//           |      P3.5/PM_TA0.2|--> CCR2 - 25% PWM
//
//  B. Nisarga
//  Texas Instruments Inc.
//  Dec 2009
//  Built with CCS v4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include "msp430f5172.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  // Configure ports
  P3DIR |= BIT6+BIT5;                       // P3.6 and P3.5 output
  P3SEL |= BIT6+BIT5;                       // P3.6 and P3.5 options select
  PJSEL |= BIT4+BIT5;                       // Port select XT1

  UCSCTL6 &= ~(XT1OFF);                     // XT1 On
  UCSCTL6 |= XCAP_3;                        // Internal load cap
  UCSCTL3 = 0;                              // FLL Reference Clock = XT1

  // Loop until XT2 & DCO stabilizes - In this case loop until XT1 and DCo settle
  do
  {
    UCSCTL7 &= ~(XT1LFOFFG + XT1HFOFFG + DCOFFG);
                                            // Clear XT1,DCO fault flags
    SFRIFG1 &= ~OFIFG;                      // Clear fault flags
  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag  
  UCSCTL6 &= ~(XT1DRIVE_3);                 // Xtal is now stable, reduce drive strength
  UCSCTL4 |= SELA_0;                        // ACLK = LFTX1 (by default)
  
  // configure TA0
  TA0CCR0 = 512-1;                          // PWM Period
  TA0CCTL1 = OUTMOD_7;                      // CCR1 reset/set
  TA0CCR1 = 384;                            // CCR1 PWM duty cycle
  TA0CCTL2 = OUTMOD_7;                      // CCR2 reset/set
  TA0CCR2 = 128;                            // CCR2 PWM duty cycle
  TA0CTL = TASSEL_1 + MC_1 + TACLR;         // ACLK, up mode, clear TAR

  __bis_SR_register(LPM3_bits);             // Enter LPM3
  __no_operation();                         // For debugger
}

