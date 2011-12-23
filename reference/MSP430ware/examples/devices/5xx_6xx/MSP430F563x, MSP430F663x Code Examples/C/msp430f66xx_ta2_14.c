//******************************************************************************
//  MSP430F66x Demo - Timer2_A3, Toggle P3.5/TA2.0, Up/Down Mode, 32kHz ACLK
//
//  Description: Toggle P3.5 using hardware TA2.0 output. Timer2_A is configured
//  for up/down mode with CCR0 defining period, TA2.0 also output on P3.5. In
//  this example, CCR0 is loaded with 5 and TA2.0 will toggle P3.5 at TACLK/2*5.
//  Thus the output frequency on P3.5 will be the TACLK/20. No CPU or software
//  resources required. Normal operating mode is LPM3.
//  As coded with TACLK = ACLK, P3.5 output frequency = 32768/20 = 1.6384kHz
//  ACLK = TACLK = 32kHz, MCLK = default DCO ~1.045MHz
//
//                MSP430F66x
//            -------------------
//        /|\|                   |
//         | |                   |
//         --|RST                |
//           |                   |
//           |         P3.5/TA2.0|-->ACLK/20
//
//   Priya Thanigai
//   Texas Instruments Inc.
//   Nov 2009
//   Built with IAR Embedded Workbench Version: 4.20 & Code Composer Studio V4.0
//******************************************************************************
#include <msp430f6638.h>


void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  while(BAKCTL & LOCKIO)                    // Unlock XT1 pins for operation
     BAKCTL &= ~(LOCKIO); 
  UCSCTL6 &= ~(XT1OFF);                     // XT1 On
  UCSCTL6 |= XCAP_3;                        // Internal load cap 
  // Loop until XT1 fault flag is cleared
  do
  {
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);
                                            // Clear XT2,XT1,DCO fault flags
    SFRIFG1 &= ~OFIFG;                      // Clear fault flags
  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag
  
  P3DIR |= BIT5;                            // P3.5 output
  P3SEL |= BIT5;                            // P3.5 option select
  TA2CCTL0 = OUTMOD_4;                      // CCR0 toggle mode
  TA2CCR0 = 5;
  TA2CTL = TASSEL_1 + MC_3 + TACLR;         // ACLK, up-downmode, clear TAR

  __bis_SR_register(LPM3_bits);             // Enter LPM3
  __no_operation();                         // For debugger
}
