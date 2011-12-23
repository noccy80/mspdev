//******************************************************************************
//  MSP430F51x2 Demo - TimerD0/1-TEC, Synchronizing timers, Master Capture/Slave Compare
//
//  Description: This code example shows how to configure the TEC module for
//  synchronizing two timer instances (TD0 and TD1) to do both capture and  
//  compare on master and slave instances respectively. In this example code, 
//  TD0 is the master timer instance and TD1 is the slave instance. TD0/master 
//  is configured in capture mode and TD1/slave in compare mode. The TD1.x PWM 
//  outputs (40% and 80% PWM signals) are connected to the TD0.x capture inputs.
//  The PWM outputs (that are input to TD1.x) are generated in cont mode and so 
//  the period of the PWM input signal is 0xffff/Master clock. TD0.0 captures 
//  the rising edge and TD0.1 and TD0.2 capture the falling edges of the input 
//  PWM signal. Captured timer values are used to compute the dutycycle of 
//  respective PWM signals. If the measured dutycycle values of TD0.1 and TD0.2
//  are not 40% and 80% respectively, LED on P1.0 is turned ON. 
//
//  Note: The Slave timer starts only after the master timer starts
//
//  ACLK = REFO = 32kHz; SMCLK = MCLK = DCO Clock = TD0/1 Clock = 12MHz; 
//
//                 MSP430F51x2
//             -----------------
//         /|\|              XIN|-
//          | |                 | 
//          --|RST          XOUT|-
//            |                 |
//            |       P1.6/TD0.0|<-- CCI0A <-|  
//            |       P2.1/TD1.0|--> CCR0 -->|
//            |                 |
//            |       P1.7/TD0.1|<-- CCI1A <-|
//            |       P2.2/TD1.1|--> CCR1 -->| 
//            |                 |
//            |       P2.0/TD0.2|<-- CCI2A <-|
//            |       P2.3/TD1.2|--> CCR2 -->|
//            |                 |
//            |             P1.0|--> LED "ON" when measured TD0.1 dutycycle != 40% or
//            |                 |           TD0.2 dutycycle != 80%
//
//  B. Nisarga
//  Texas Instruments Inc.
//  Nov 2010
//  Built with CCS v4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************

#include "msp430f5172.h"

unsigned int REdge1, FEdge2, FEdge_IN1, FEdge_IN2;    // Variables to hold timer capture values

void SetVcoreUp (unsigned int level);

void main(void)
{
  unsigned char DutyCycle_IN1, DutyCycle_IN2 ;        // Dutycycle Variables 
  unsigned int Period, ON_Period_IN1, ON_Period_IN2;  // ON_Period Variables
  
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  
  P1DIR |= BIT0;                            // P1.0 Output direction
  P1OUT &= ~BIT0;                           // LED off
  
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
  P1SEL |= BIT6 + BIT7;                     // P1.6/TD0.CCI0A, P1.7,TD0.CCI1A, options select
  P1DIR &= ~(BIT6 + BIT7);                  // Input direction
  P2SEL |= BIT0 + BIT1 + BIT2 + BIT3;       // P2.0/TD0.CCI2A, P2.1/TD1.0, P2.2/TD1.1, P2.3/TD1.2, options select
  P2DIR |= BIT1 + BIT2 + BIT3;              // Output direction
  P2DIR &= ~BIT0;                           // P2.0/TD0.CCI2A, Input direction
  
  // Configure Master Timer Instance - TimerD0,  
  // TD0 clock = SMCLK = 12MHz
  TD0CTL0 = TDSSEL_2;                       // TD0, SMCLK
  TD0CTL1 = TDCLKM_0;                       // TD0 clock = external clock source = SMCLK 
  
  TD0CCTL0 = CM_1 | CAP | CCIE;             // Capture mode, rising edge, enable capture interrupt 
  TD0CCTL1 = CM_2 + CAP + CCIE;             // Capture mode, falling edge, enable capture interrupt
  TD0CCTL2 = CM_2 + CAP + CCIE;             // Capture mode, falling edge, enable capture interrupt

  // Configure Slave Timer Instance - TimerD1 PWM outputs 
  // PWM freq (0xFFFF/SMCLK) = 5.46ms 
  TD1CCR0 = 0xAAAA;                         // PWM Period/2 
  TD1CCTL0 |= OUTMOD_4;                     // TD1CCR0, Toggle, 50% dutycycle
  TD1CCR1 = 0x1111;                         // 40% dutycycle
  TD1CCTL1 |= OUTMOD_7;                     // TD1CCR1, Reset/Set    
  TD1CCR2 = 0x7777;                         // 80% dutycycle
  TD1CCTL2 |= OUTMOD_7;                     // TD1CCR2, Reset/Set
  TD1CTL1 = TDCLKM_2;                       // TD1 clock = Auxiliary clock source from master timer instance 
    
  // Syncronizing master (TD0) and slave (TD1) timer instances
  TEC1XCTL2 |= TECAXCLREN;		    // Enable synchronized clear by enabling Aux clear of slave timer 
  TD0CTL0 |= MC_2 + TDCLR;                  // Clear timer counter, Cont mode, Start timers   

  while(1)
  {
      __bis_SR_register(LPM0_bits + GIE);    // Enter LPM0, enable global interrupt
      __no_operation();                      // For debugger   
      
      // On LPM0 exit
      if ((TD0CCTL0 & COV) || (TD0CCTL1 & COV) || (TD0CCTL2 & COV))
        while(1);                           // Loop forever, is case of capture overflow 

      Period = 0xFFFF;                       // Period = FFFF as input signal (from TD0.x) is in Cont mode
      ON_Period_IN1 = FEdge_IN1 - REdge1;    // Compute On-Periods
      ON_Period_IN2 = FEdge_IN2 - REdge1;
      
      DutyCycle_IN1 = ((unsigned long)ON_Period_IN1*100/Period);  // Compute Dutycycle
      DutyCycle_IN2 = ((unsigned long)ON_Period_IN2*100/Period);

      __no_operation();                      // BREAKPOINT HERE to check measured dutycycles        
      if((DutyCycle_IN1 != 40)|| (DutyCycle_IN2 != 80))
      {
          P1OUT |= BIT0;
      }
  }
  
}

// Timer0_D0 Interrupt Vector
#pragma vector=TIMER0_D0_VECTOR
__interrupt void TIMER0_D0_ISR (void)
{
  REdge1 = TD0CCR0;                          // Rising edge on TD0.0 capture value
  __bic_SR_register_on_exit(LPM0_bits);      // Exit LPM0 
}

// TD0_D1 Interrupt vector
#pragma vector = TIMER0_D1_VECTOR
__interrupt void TIMER0_D1_ISR (void)
{
  switch(__even_in_range(TD0IV,0x1E))
  {
      case  0x0: break;                     // Vector  0:  No interrupt
      case  0x2:                            // Vector  2:  TDCCR1 CCIFG
        FEdge_IN1 = TD0CCR1;                // Falling edge on TD0.1 capture value
        break;                            
      case  0x4:                            // Vector  4:  TDCCR2 CCIFG        
        FEdge_IN2 = TD0CCR2;                // Falling edge on TD0.2 capture value  
        break;                            
      case 0x6: break;                      // Vector  6:  TDCCR3 CCIFG
      case 0x8: break;                      // Vector  8:  TDCCR4 CCIFG
      case 0xA: break;                      // Vector 10:  TDCCR5 CCIFG
      case 0xC: break;                      // Vector 12:  TDCCR5 CCIFG
      case 0xE: break;                      // Vector 14:  -
      case 0x10:break;                      // Vector 16:  TDIFG 
      case 0x12:break;                      // Vector 18:  TDHINT TDHFLIFG 
      case 0x14:break;                      // Vector 20:  TDHINT TDHFHIFG 
      case 0x16:break;                      // Vector 22:  TDHINT TDHLKIFG 
      case 0x18:break;                      // Vector 24:  TDHINT TDHUNLKIFG
      case 0x1A:break;                      // Vector 26:  -
      case 0x1C:break;                      // Vector 28:  - 
      case 0x1E:break;                      // Vector 28:  - 
      default: 	break;
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