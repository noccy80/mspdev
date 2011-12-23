//******************************************************************************
//   CC430F513x Demo - Software Toggle P1.0 with 8MHz DCO
//
//   Description: Toggle P1.0 by xor'ing P1.0 inside of a software loop.
//   ACLK is brought out on pin P2.0, SMCLK is brought out on P2.4, and MCLK
//   is brought out on pin P2.2.
//   ACLK = REFO = 32kHz, MCLK = SMCLK = 8MHz
//
//                 CC430F5137
//             -----------------
//         /|\|                 |
//          | |            P2.0 |-->ACLK
//          --|RST         P2.2 |-->MCLK
//            |            P2.4 |-->SMCLK
//            |                 |
//			  |             P1.6|-->GND
//            |             P1.0|-->LED
//
//  M. Morales
//  Texas Instruments Inc.
//  April 2009
//  Built with CCE v3.1 Build 3.2.3.6.4 & IAR Embedded Workbench Version: 4.11B
//******************************************************************************
#include  "cc430x513x.h"

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  
  /* Initialize Ports */
  P1DIR |= BIT0 + BIT6;                     // P1.0 output, P1.6 GND reference 
  P1OUT = 0; 
  
  PMAPPWD = 0x02D52;                        // Get write-access to port mapping regs  
  P2MAP0 = PM_ACLK;                         // Map ACLK output to P2.0 
  P2MAP2 = PM_MCLK;                         // Map MCLK output to P2.2 
  P2MAP4 = PM_SMCLK;                        // Map SMCLK output to P2.4 
  PMAPPWD = 0;                              // Lock port mapping registers  
   
  P2DIR |= BIT0 + BIT2 + BIT4;              // ACLK, MCLK, SMCLK set out to pins
  P2SEL |= BIT0 + BIT2 + BIT4;              // P2.0,2,4 for debugging purposes

  UCSCTL3 |= SELREF_2;                      // Set DCO FLL reference = REFO
  UCSCTL4 |= SELA_2;                        // Set ACLK = REFO

  __bis_SR_register(SCG0);                  // Disable the FLL control loop
  UCSCTL0 = 0x0000;                         // Set lowest possible DCOx, MODx
  UCSCTL1 = DCORSEL_5;                      // Select DCO range 16MHz operation
  UCSCTL2 = FLLD_1 + 249;                   // Set DCO Multiplier for 8MHz
                                            // (N + 1) * FLLRef = Fdco
                                            // (249 + 1) * 32768 = 8MHz
                                            // Set FLL Div = fDCOCLK/2
  __bic_SR_register(SCG0);                  // Enable the FLL control loop

  // Worst-case settling time for the DCO when the DCO range bits have been
  // changed is n x 32 x 32 x f_MCLK / f_FLL_reference. See UCS chapter in 5xx
  // UG for optimization.
  // 32 x 32 x 8 MHz / 32,768 Hz = 250000 = MCLK cycles for DCO to settle
  __delay_cycles(250000);

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
