//******************************************************************************
//   MSP430F543xA Demo - Software Toggle P1.0 with 12MHz DCO
//
//   Description: Toggle P1.0 by xor'ing P1.0 inside of a software loop.
//   ACLK is rought out on pin P11.0, SMCLK is brought out on P11.2, and MCLK
//   is brought out on pin P11.1.
//   ACLK = REFO = 32kHz, MCLK = SMCLK = 12MHz
//   PMMCOREV = 1 to support up to 12MHz clock
//
//                 MSP430F5438A
//             -----------------
//         /|\|                 |
//          | |            P11.0|-->ACLK
//          --|RST         P11.1|-->MCLK
//            |            P11.2|-->SMCLK
//            |                 |
//            |             P1.0|-->LED
//
//   Note: 
//   In order to run the system at up to 12MHz, VCore must be set at 1.6V 
//   or higher. This is done by invoking function SetVCore(), which requires 
//   2 files, hal_pmm.c and hal_pmm.h, to be included in the project.
//   hal_pmm.c and hal_pmm.h are located in the same folder as the code 
//   example. 
//
//   D. Dang
//   Texas Instruments Inc.
//   December 2009
//   Built with CCS Version: 4.0.2 and IAR Embedded Workbench Version: 4.21.8
//******************************************************************************
#include  "msp430x54xA.h"
#include  "hal_pmm.h"
void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  SetVCore(PMMCOREV_1);                     // Set VCore = 1.6V for 12MHz clock
  P1DIR |= BIT0;                            // P1.0 output
  P11DIR |= 0x07;                           // ACLK, MCLK, SMCLK set out to pins
  P11SEL |= 0x07;                           // P11.0,1,2 for debugging purposes.

  UCSCTL3 |= SELREF_2;                      // Set DCO FLL reference = REFO
  UCSCTL4 |= SELA_2;                        // Set ACLK = REFO

  __bis_SR_register(SCG0);                  // Disable the FLL control loop
  UCSCTL0 = 0x0000;                         // Set lowest possible DCOx, MODx
  UCSCTL1 = DCORSEL_5;                      // Select DCO range 24MHz operation
  UCSCTL2 = FLLD_1 + 374;                   // Set DCO Multiplier for 12MHz
                                            // (N + 1) * FLLRef = Fdco
                                            // (374 + 1) * 32768 = 12MHz
                                            // Set FLL Div = fDCOCLK/2
  __bic_SR_register(SCG0);                  // Enable the FLL control loop

  // Worst-case settling time for the DCO when the DCO range bits have been
  // changed is n x 32 x 32 x f_MCLK / f_FLL_reference. See UCS chapter in 5xx
  // UG for optimization.
  // 32 x 32 x 12 MHz / 32,768 Hz = 375000 = MCLK cycles for DCO to settle
  __delay_cycles(375000);
	
  // Loop until XT1,XT2 & DCO fault flag is cleared
  do
  {
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG);
                                            // Clear XT2,XT1,DCO fault flags
    SFRIFG1 &= ~OFIFG;                      // Clear fault flags
  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag
	
  while(1)
  {
    P1OUT ^= BIT0;                          // Toggle P1.0
    __delay_cycles(600000);                 // Delay
  }
}
