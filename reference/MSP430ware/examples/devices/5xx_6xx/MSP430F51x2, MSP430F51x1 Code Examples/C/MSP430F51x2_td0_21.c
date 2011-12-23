//******************************************************************************
//  MSP430F51x2 Demo - TimerD0, Hi-Res Calibrated mode, PWM TD0.0-2, DCO SMCLK
//
//  Description: This code example shows how to configure TimerD in Hi-Res 
//  calibrated mode. The reference input clock freq (in this e.g. SMCLK=12MHz)
//  is multiplied by a factor of 16 to generate a hi-res freq of InputClk x 16 
//  (in this e.g. 12MHz x 16 = 192Mhz. With TD0CCR0=128-1, TD0.0 outputs a 
//  square wave of freq 746kHz and TD0.1 and TD0.2 output PWM waveforms with
//  dutycycles of 25% and 75% respectively. 
//
//  NOTE: For using multiply factor 16x in hi-res calibration mode, make sure  
//  input ref clock is in the following freq range: 8Mhz to 16MHz. 
//  
//  ACLK=LFXT1=32kHz; SMCLK=MCLK=12MHz; TDCLK(Hi-Res)= SMCLK x 16 = 192MHz
//
//                 MSP430F51x2
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |       P1.6/TD0.0|--> CCR0 - 50% dutycycle; PWM period = (2 x 128)/(12MHz x 16)~ 1.34us = 746kHz
//            |       P1.7/TD0.1|--> CCR1 - 25% dutycycle; ON period ~ 32/(12MHz x 16)~ 167ns
//            |       P2.0/TD0.2|--> CCR2 - 75% dutycycle; ON period ~ 96/(12MHz x 16)~ 500ns
//
//  B. Nisarga
//  Texas Instruments Inc.
//  Dec 2009
//  Built with CCS v4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include "msp430f5172.h"

void SetVcoreUp (unsigned int level);

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  
  // Configure XT1
  PJSEL |= BIT4+BIT5;                       // Port select XT1  
  UCSCTL6 &= ~(XT1OFF);                     // XT1 On
  UCSCTL6 |= XCAP_3;                        // Internal load cap  
  // Loop until XT1 fault flag is cleared
  do
  {
    UCSCTL7 &= ~XT1LFOFFG;                  // Clear XT1 fault flags
  }while (UCSCTL7&XT1LFOFFG);               // Test XT1 fault flag

  // Increase Vcore setting to level1 to support fsystem=12MHz
  // NOTE: Change core voltage one level at a time..
  SetVcoreUp (0x01); 
        
  // Initialize DCO to 12MHz
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

  // Loop until XT1 & DCO fault flag is cleared
  do
  {
    UCSCTL7 &= ~(XT1LFOFFG + XT1HFOFFG + DCOFFG);
                                            // Clear XT1,DCO fault flags
    SFRIFG1 &= ~OFIFG;                      // Clear fault flags
  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag
  
  // Configure TimerD in Hi-Res Calibrated Mode
  TD0CTL0 = TDSSEL_2;                       // TDCLK=SMCLK=12MHz=Hi-Res input clk select
  
  TD0CTL1 |= TDCLKM_1;                      // Select Hi-res local clock
  TD0HCTL0 = TDHM_1 + TDHCALEN + TDHEN;     // Hi-res clock 16x TDCLK, 
                                            // Calibration and Hi-res mode enable
  TD0HINT |= TDHLKIE;                       // Enable TDH Lock IFG
  
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
  
// Timer0_D1 Interrupt Vector (TDIV) handler
#pragma vector=TIMER0_D1_VECTOR
__interrupt void TIMER0_D1_ISR(void)
{
  switch(__even_in_range(TD0IV,30))
  {
    case  0: break;                          // No interrupt
    case  2: break;                          // CCR1 not used
    case  4: break;                          // CCR2 not used
    case  6: break;                          // reserved
    case  8: break;                          // reserved
    case 10: break;                          // reserved
    case 12: break;                          // reserved
    case 14: break;
    case 16: break;
    case 18:                                 // Clock fail low
      while(1);                              // Input ref clock freq too low; trap here                          
    case 20:                                 // Clock fail high
      while(1);                              // Input ref clock freq too high; trap here                          
    case 22:                                 // Hi-res freq locked
      // Hi-Res freq locked; now configure ports to output PWMs at TD0.0/1/2
      P1SEL |= BIT6 + BIT7;                  // P1.6,7 option select
      P1DIR |= BIT6 + BIT7;                  // P1.6,7 output
      P2SEL |= BIT0;                         // P2.0 options select
      P2DIR |= BIT0;                         // P2.0 output 
      break;
    case 24: break;                          // Hi-res freq unlocked
    case 26: break;                          // reserved
    case 28: break;                          // reserved
    case 30: break;                          // reserved       
    default: break; 
  }   
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
  