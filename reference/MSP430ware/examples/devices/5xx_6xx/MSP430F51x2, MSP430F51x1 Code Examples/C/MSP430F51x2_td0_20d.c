//******************************************************************************
//  MSP430F51x2 Demo - TimerD0, Hi-Res Free Running mode, PWM TD0.0-2, TDCLK = 256Mhz
//
//  Description: This code example shows how to configure TimerD in Hi-Res 
//  Free Running mode. The TD0HCTL1 register with the TDHCLKTRIMx, TDHCLKSRx and 
//  TDHCLKRx bit settings are configured with the calibration data in the TLV 
//  table. 
//
//  ACLK=REFO; SMCLK=MCLK=DCOclock=16MHz; TDCLK(TLV Cal Data)= 256Mhz
//  Note: 1. DCO should be set to 16Mhz and TDHMx=01(16x) to use the 256Mhz TimerD TLV data
//        2. Use code example with hal_tlv.c and hal_tlv.h files to read the TimerD TLV data 
//
//                 MSP430F51x2
//             -----------------
//         /|\|              XIN|-
//          | |                 | 
//          --|RST          XOUT|-
//            |                 |
//            |       P1.6/TD0.0|--> CCR0 - 50% dutycycle; PWM period = (2 x 128)/256MHz~ 1us = 1MHz
//            |       P1.7/TD0.1|--> CCR1 - 25% dutycycle; ON period ~ 32/256MHz~ 125ns
//            |       P2.0/TD0.2|--> CCR2 - 75% dutycycle; ON period ~ 96/256MHz~ 375ns
//
//  B. Nisarga
//  Texas Instruments Inc.
//  Jan 2010
//  Built with CCS v4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include "msp430f5172.h"
#include "hal_tlv.h"

// Function Definitions
void SetVcoreUp (unsigned int level);

void main(void)
{
  struct s_TLV_Timer_D_Cal_Data * pTD0CAL;  // Structure initialized in tlv.h
  unsigned char bTD0CAL_bytes;                  
  
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

  // Increase Vcore setting to level3 to support fsystem=16MHz
  // NOTE: Change core voltage one level at a time..
  SetVcoreUp (0x01);
  SetVcoreUp (0x02);  
  
  UCSCTL3 = SELREF_2;                       // Set DCO FLL reference = REFO
  UCSCTL4 |= SELA_2;                        // Set ACLK = REFO

  __bis_SR_register(SCG0);                  // Disable the FLL control loop
  UCSCTL0 = 0x0000;                         // Set lowest possible DCOx, MODx
  UCSCTL1 = DCORSEL_6;                      // Select DCO range 50MHz operation
  UCSCTL2 = FLLD_1 + 487;                   // Set DCO Multiplier for 16MHz
                                            // (N + 1) * FLLRef = Fdco
                                            // (487 + 1) * 32768 = 16MHz
                                            // Set FLL Div = fDCOCLK/2
  __bic_SR_register(SCG0);                  // Enable the FLL control loop

  // Worst-case settling time for the DCO when the DCO range bits have been
  // changed is n x 32 x 32 x f_MCLK / f_FLL_reference. See UCS chapter in 5xx
  // UG for optimization.
  // 32 x 32 x 16 MHz / 32,768 Hz ~ 500k MCLK cycles for DCO to settle
  __delay_cycles(500000);

  // Loop until XT1,XT2 & DCO stabilizes - In this case only DCO has to stabilize
  do
  {
    UCSCTL7 &= ~(XT1LFOFFG + XT1HFOFFG + DCOFFG);
                                            // Clear XT2,XT1,DCO fault flags
    SFRIFG1 &= ~OFIFG;                      // Clear fault flags
  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag
  
  // Configure TimerD in Hi-Res Free Running Mode

  Get_TLV_Info(TLV_TIMER_D_CAL, 0, &bTD0CAL_bytes, (unsigned int **) &pTD0CAL); 
                                            //Get TimerD0 Cal Values (instance 0)
  if(bTD0CAL_bytes == 0x0)
  {
      // No TimerD free running cal data found
      while(1);                             // Loop here
  }  
  TD0HCTL1 = pTD0CAL->TDH0CTL1_256;         // Read the 256Mhz TimerD TLV Data     

  TD0CTL1 |= TDCLKM_1;                      // Select Hi-res local clock
  TD0HCTL0 = TDHEN + TDHM_1;                // CALEN=0 => free running mode; enable Hi-res mode 
                                            // THDMx = 01 => 16x
  // Configure TD0.x GPIO pins
  P1SEL |= BIT6 + BIT7;                     // P1.6,7 option select
  P1DIR |= BIT6 + BIT7;                     // P1.6,7 output
  P2SEL |= BIT0;                            // P2.0 options select
  P2DIR |= BIT0;                            // P2.0 output   
  
  // Configure the CCRx blocks
  TD0CCTL0 = OUTMOD_4;                      // CCR0 toggle
  TD0CCR0 = 128-1;                          // PWM Period/2
  TD0CCTL1 = OUTMOD_6;                      // CCR1 toggle/set
  TD0CCR1 = 32;                             // CCR1 PWM duty cycle
  TD0CCTL2 = OUTMOD_6;                      // CCR2 toggle/set
  TD0CCR2 = 96;                             // CCR2 PWM duty cycle
  TD0CTL0 |= MC_1 + TDCLR;                  // up-mode, clear TDR, Start timer
  
  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0
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

