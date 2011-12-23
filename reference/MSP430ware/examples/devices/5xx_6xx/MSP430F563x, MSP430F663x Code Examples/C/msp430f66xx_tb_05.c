//*****************************************************************************
//  MSP430F66x Demo - Timer_B, Toggle P1.0, CCR0 Up Mode ISR, 32kHz ACLK
//
//  Description: Toggle P1.0 using software and the TB_0 ISR. Timer_B is
//  configured for up mode, thus the timer overflows when TBR counts
//  to CCR0. In this example, CCR0 is loaded with 1000-1.
//  Toggle rate = 32768Hz/(2*1000) = 16.384Hz
//  ACLK = TBCLK = 32kHz, MCLK = SMCLK = default DCO ~1.045MHz
//
//           MSP430F66x
//         ---------------
//     /|\|               |
//      | |               |
//      --|RST            |
//        |               |
//        |           P1.0|-->LED
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
  
  P1DIR |= 0x01;                            // Set P1.0 to output direction
  TBCCTL0 = CCIE;                           // TRCCR0 interrupt enabled
  TBCCR0 = 1000-1;
  TBCTL = TBSSEL_1 + MC_1 + TBCLR;          // ACLK, upmode, clear TBR

  __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3, enable interrupts
  __no_operation();                         // For debugger  
}

// Timer B0 interrupt service routine
#pragma vector=TIMERB0_VECTOR
__interrupt void TIMERB1_ISR(void)
{
    P1OUT ^= 0x01;                          // Toggle P1.0 using exclusive-OR
}

