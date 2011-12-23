//******************************************************************************
//   MSP430F530x Demo - Software Toggle P1.1 with 8MHz DCO
//
//   Description: Toggle P1.1 by xor'ing P1.1 inside of a software loop.
//   ACLK is rought out on pin P1.0, SMCLK is brought out on P2.2, and MCLK
//   is brought out on pin P4.7.
//   ACLK = REFO = 32kHz, MCLK = SMCLK = 8MHz
//
//                MSP430F530x
//             -----------------
//         /|\|                 |
//          | |             P1.0|-->ACLK
//          --|RST          P4.7|-->MCLK
//            |             P2.2|-->SMCLK
//            |                 |
//            |             P1.1|-->Port Pin
//
//   B. Nisarga
//   Texas Instruments Inc.
//   Dec 2010
//   Built with CCSv4.2 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include <msp430f5310.h>

void main(void)
{
  volatile unsigned int i;

  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT

  PMAPPWD = 0x02D52;                        // Enable Write-access to modify port mapping registers
  P4MAP7 = PM_MCLK;
  PMAPPWD = 0;                              // Disable Write-Access to modify port mapping registers


  P1DIR |= BIT1;                            // P1.1 output

  P1DIR |= BIT0;                            // ACLK set out to pins
  P1SEL |= BIT0;                            
  P2DIR |= BIT2;                            // SMCLK set out to pins
  P2SEL |= BIT2;                            
  
  P4SEL |= BIT7;  
  P4DIR |= BIT7;                            // MCLK set out to pins         

  UCSCTL3 = SELREF_2;                       // Set DCO FLL reference = REFO
  UCSCTL4 |= SELA_2;                        // Set ACLK = REFO
  UCSCTL0 = 0x0000;                         // Set lowest possible DCOx, MODx

  // Loop until XT1,XT2 & DCO stabilizes - In this case only DCO has to stabilize
  do
  {
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);
                                            // Clear XT2,XT1,DCO fault flags
    SFRIFG1 &= ~OFIFG;                      // Clear fault flags
  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag
	
  __bis_SR_register(SCG0);                  // Disable the FLL control loop
  UCSCTL1 = DCORSEL_5;                      // Select DCO range 16MHz operation
  UCSCTL2 |= 249;                           // Set DCO Multiplier for 8MHz
                                            // (N + 1) * FLLRef = Fdco
                                            // (249 + 1) * 32768 = 8MHz
  __bic_SR_register(SCG0);                  // Enable the FLL control loop

  // Worst-case settling time for the DCO when the DCO range bits have been
  // changed is n x 32 x 32 x f_MCLK / f_FLL_reference. See UCS chapter in 5xx
  // UG for optimization.
  // 32 x 32 x 8 MHz / 32,768 Hz = 250000 = MCLK cycles for DCO to settle
  __delay_cycles(250000);
	
  while(1)
  {
    P1OUT ^= BIT0;                          // Toggle P1.0
    __delay_cycles(600000);                 // Delay
  }
}

