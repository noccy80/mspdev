//******************************************************************************
//  MSP430F51x2 Demo - TimerD0/1-TEC, Synchronizing timers, hi-res timer mode 
//
//  Description: This code example shows how to configure the TEC module for
//  synchronizing two timer instances (TD0 and TD1) operated in Hi-res mode. In 
//  this example code, TD0 is the master timer instance and TD1 the slave 
//  instance. The Hi-res clock configuration of the master is applied to the 
//  slave. The counter length, high res enable and timer mode settings of the 
//  master are applied to the slave as well. 
//
//  Note: TDxCCR0 registers of both master and slave timer instance (TD0 and 
//      TD1 in this case) should be the same value
//
//  ACLK=REFO=32kHz; SMCLK=MCLK=DCO_Clk=25MHz; TDCLK(Hi-Res)Master/Slave = SMCLK x 8 = 200MHz
//
//                 MSP430F51x2
//             -----------------
//         /|\|              XIN|-
//          | |                 | 
//          --|RST          XOUT|-
//            |                 |
//            |                 |
//            |       P1.6/TD0.0|--> CCR0 - 50% dutycycle, PWM period = (2 x 200)/(25MHz x 8)~ 8us = 500kHz
//            |       P2.1/TD1.0|--> CCR0 - 50% dutycycle, PWM period = (2 x 200)/(25MHz x 8)~ 8us = 500kHz
//            |                 |
//            |       P1.7/TD0.1|--> CCR1 - 20% dutycycle, ON period ~ 40/(25MHz x 8)~ 200ns
//            |       P2.2/TD1.1|--> CCR1 - 40% dutycycle, ON period ~ 80/(25MHz x 8)~ 400ns
//            |                 |
//            |       P2.0/TD0.2|--> CCR2 - 60% dutycycle, ON period ~ 120/(25MHz x 8)~ 600ns
//            |       P2.3/TD1.2|--> CCR2 - 80% dutycycle, ON period ~ 160/(25MHz x 8)~ 800ns
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
  
  // Increase Vcore setting to level3 to support fsystem=25MHz
  // NOTE: Change core voltage one level at a time..
  SetVcoreUp (0x01);
  SetVcoreUp (0x02);  
  SetVcoreUp (0x03);   
  
  // Configure DCO = 25Mhz
  UCSCTL3 = SELREF_2;                       // Set DCO FLL reference = REFO
  UCSCTL4 |= SELA_2;                        // Set ACLK = REFO

  __bis_SR_register(SCG0);                  // Disable the FLL control loop
  UCSCTL0 = 0x0000;                         // Set lowest possible DCOx, MODx
  UCSCTL1 = DCORSEL_7;                      // Select DCO range 50MHz operation
  UCSCTL2 = FLLD_1 + 762;                   // Set DCO Multiplier for 25MHz
                                            // (N + 1) * FLLRef = Fdco
                                            // (762 + 1) * 32768 = 25MHz
                                            // Set FLL Div = fDCOCLK/2
  __bic_SR_register(SCG0);                  // Enable the FLL control loop

  // Worst-case settling time for the DCO when the DCO range bits have been
  // changed is n x 32 x 32 x f_MCLK / f_FLL_reference. See UCS chapter in 5xx
  // UG for optimization.
  // 32 x 32 x 25 MHz / 32,768 Hz ~ 780k MCLK cycles for DCO to settle
  __delay_cycles(782000);

  // Loop until XT1 & DCO stabilizes - In this case only DCO has to stabilize
  do
  {
    UCSCTL7 &= ~(XT1LFOFFG + XT1HFOFFG + DCOFFG);
                                            // Clear XT1,DCO fault flags
    SFRIFG1 &= ~OFIFG;                      // Clear fault flags
  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag
 
  // Configure Master Timer Instance - TimerD0, Hi-Res Calibrated Mode
  TD0CTL0 = TDSSEL_2;                       // TDCLK = SMCLK = 25MHz = Hi-Res input clk select  
  TD0CTL1 |= TDCLKM_1;                      // TD0 clock = Hi-res local clock
  TD0HCTL0 = TDHM_0 + TDHCALEN + TDHEN;     // Hi-res clock 8x TDCLK, 
                                            // Calibration and Hi-res mode enable
  TD0HINT |= TDHLKIE;                       // Enable TDH Lock IFG

  // Configure TD0 PWM outputs
  // Freq = 1Mhz, TD0.1/TD0.2 PWM Period = 1us
  TD0CCR0 = 200;                            // TD0CCR0, PWM freq/2
  TD0CCTL0 |= OUTMOD_4;                     // TD0CCR0, Toggle, 50% dutycycle
  TD0CCR1 = 40;                             // 20% dutycycle
  TD0CCTL1 |= OUTMOD_7;                     // TD0CCR1, Reset/Set    
  TD0CCR2 = 80;                             // 40% dutycycle
  TD0CCTL2 |= OUTMOD_7;                     // TD0CCR2, Reset/Set

  TD0CTL0 |= MC_1 + TDCLR;                  // up-mode, clear TDR, Start timer
  
  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0, enable interrupts
  __no_operation();                         // For debugger  
  
  // On LPM0 exit - Configure Slave Timer Instance - TimerD1 PWM outputs 
  TD1CCR0 = 200;                            // TD1CCR0, PWM freq/2
  TD1CCTL0 |= OUTMOD_4;                     // TD1CCR0, Toggle, 50% dutycycle
  TD1CCR1 = 120;                            // 60% dutycycle
  TD1CCTL1 |= OUTMOD_7;                     // TD1CCR1, Reset/Set    
  TD1CCR2 = 160;                            // 80% dutycycle
  TD1CCTL2 |= OUTMOD_7;                     // TD1CCR2, Reset/Set
  TD1CTL1 = TDCLKM_2;                       // TD1 clock = Auxiliary clock source from master timer instance
  
  // Syncronize master (TD0) and slave (TD1) timer instances
  TEC1XCTL2 |= TECAXCLREN;		    // Enable synchronized clear by enabling Aux clear of slave timer 
  TD0CTL0 |= TDCLR;                         // Clear timer counter
  
  __bis_SR_register(LPM0_bits);             // Enter LPM0
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
      // Hi-Res freq locked; now configure ports to output PWMs at TD0/TD1
      P1SEL |= BIT6 + BIT7;                  // P1.6/TD0.0, P1.7,TD0.1, options select
      P1DIR |= BIT6 + BIT7;                  // Output direction
      P2SEL |= BIT0 + BIT1 + BIT2 + BIT3;    // P2.0/TD0.2, P2.1/TD1.0, P2.2/TD1.1, P2.3/TD1.2, options select
      P2DIR |= BIT0 + BIT1 + BIT2 + BIT3;    // Output direction
      
      __bic_SR_register_on_exit(LPM0_bits + GIE);  // Exit LPM0 on return to main
      
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
