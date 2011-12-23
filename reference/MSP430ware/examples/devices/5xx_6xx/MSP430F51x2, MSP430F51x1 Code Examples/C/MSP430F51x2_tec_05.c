//******************************************************************************
//  MSP430F51x2 Demo - TimerD0/1-TEC, Synchronizing timers, Normal timer mode
//
//  Description: This code example shows how to configure the TEC module for
//  synchronizing two timer instances (TD0 and TD1). In this example code, TD0 is 
//  the master timer and TD1 is the slave instance. The clock configuration of 
//  the master is applied to the slave. The counter length, high res enable
//  and timer mode settings of the master are applied to the slave as well. 
//
//  Note: TDxCCR0 registers of both master and slave timer instance (TD0 and 
//      TD1 in this case) should be the same value
//
//  ACLK = REFO = 32kHz; SMCLK = MCLK = DCO Clock = 12MHz; TD0 = TD1 = 10kHz
//
//                 MSP430F51x2
//             -----------------
//         /|\|              XIN|-
//          | |                 | 
//          --|RST          XOUT|-
//            |                 |
//            |       P1.6/TD0.0|--> CCR0 - 50% dutycycle 
//            |       P2.1/TD1.0|--> CCR0 - 50% dutycycle
//            |                 |
//            |       P1.7/TD0.1|--> CCR1 - 20% dutycycle
//            |       P2.2/TD1.1|--> CCR1 - 40% dutycycle
//            |                 |
//            |       P2.0/TD0.2|--> CCR2 - 60% dutycycle
//            |       P2.3/TD1.2|--> CCR2 - 80% dutycycle
//
//  B. Nisarga
//  Texas Instruments Inc.
//  Nov 2010
//  Built with CCS v4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************

#include "msp430f5172.h"

void SetVcoreUp (unsigned int level);

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  
  // Increase Vcore setting to level1 to support fsystem=12MHz
  // NOTE: Change core voltage one level at a time..
  SetVcoreUp (0x01);    
  
  // Configure DCO = 12Mhz
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
    UCSCTL7 &= ~(XT1LFOFFG + XT1HFOFFG + DCOFFG);
                                            // Clear XT2,XT1,DCO fault flags
    SFRIFG1 &= ~OFIFG;                      // Clear fault flags
  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag
  
  // Configure TD0, TD1 port pins
  P1SEL |= BIT6 + BIT7;                     // P1.6/TD0.0, P1.7,TD0.1, options select
  P1DIR |= BIT6 + BIT7;                     // Output direction
  P2SEL |= BIT0 + BIT1 + BIT2 + BIT3;       // P2.0/TD0.2, P2.1/TD1.0, P2.2/TD1.1, P2.3/TD1.2, options select
  P2DIR |= BIT0 + BIT1 + BIT2 + BIT3;       // Output direction
  
  // Configure Master Timer Instance - TimerD0
  // Freq = 100kHz, TD0.1/TD0.2 PWM Period = 10us
  TD0CCR0 = 120;                            // TD0CCR0 PWM period = 2*10us = 20us
  TD0CCTL0 |= OUTMOD_4;                     // TD0CCR0, Toggle, 50% dutycycle
  TD0CCR1 = 24;                             // 20% dutycycle
  TD0CCTL1 |= OUTMOD_7;                     // TD0CCR1, Reset/Set    
  TD0CCR2 = 48;                             // 40% dutycycle
  TD0CCTL2 |= OUTMOD_7;                     // TD0CCR2, Reset/Set
  TD0CTL0 = TDSSEL_2;                       // TD0, SMCLK
  TD0CTL1 = TDCLKM_0;                       // TD0 clock = external clock source = SMCLK  

  // Configure Slave Timer Instance - TimerD1 PWM outputs 
  TD1CCR0 = 120;                            // TD1CCR0 PWM period = 2*10us = 20us
  TD1CCTL0 |= OUTMOD_4;                     // TD1CCR0, Toggle, 50% dutycycle
  TD1CCR1 = 72;                             // 60% dutycycle
  TD1CCTL1 |= OUTMOD_7;                     // TD1CCR1, Reset/Set    
  TD1CCR2 = 96;                             // 80% dutycycle
  TD1CCTL2 |= OUTMOD_7;                     // TD1CCR2, Reset/Set
  TD1CTL1 = TDCLKM_2;                       // TD1 clock = Auxiliary clock source from master timer instance
  
  // Syncronizing master (TD0) and slave (TD1) timer instances
  TEC1XCTL2 |= TECAXCLREN;		    // Enable synchronized clear by enabling Aux clear of slave timer 
  TD0CTL0 |= MC_1 + TDCLR;                  // Clear timer counter, Up mode, Start timers  

  __bis_SR_register(LPM0_bits);             // Enter LPM0
  __no_operation();                         // For debugger  
  
}


void SetVcoreUp (unsigned int level)
{
  // Open PMM registers for write
  PMMCTL0_H = PMMPW_H;              
  // Set SVS/SVM high side new level
  SVSMHCTL = SVSHE + SVSHRVL0 * level + SVMHE + SVSMHRRL0 * level;
  // Set SVM low side to new level
  SVSMLCTL = SVSLE + SVMLE + SVSMLRRL0 * level;
  // Wait till SVM is settled
  while ((PMMIFG & SVSMLDLYIFG) == 0);
  // Clear already set flags
  PMMIFG &= ~(SVMLVLRIFG + SVMLIFG);
  // Set VCore to new level
  PMMCTL0_L = PMMCOREV0 * level;
  // Wait till new level reached
  if ((PMMIFG & SVMLIFG))
    while ((PMMIFG & SVMLVLRIFG) == 0);
  // Set SVS/SVM low side to new level
  SVSMLCTL = SVSLE + SVSLRVL0 * level + SVMLE + SVSMLRRL0 * level;
  // Lock PMM registers for write access
  PMMCTL0_H = 0x00;
}