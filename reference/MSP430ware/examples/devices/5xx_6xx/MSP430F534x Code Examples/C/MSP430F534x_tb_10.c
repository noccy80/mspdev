//******************************************************************************
//   MSP430F534x Demo - Timer_B, PWM TB1-6, Up Mode, DCO SMCLK
//
//   Description: This program generates six PWM outputs on P4/P5 using
//   Timer_B configured for up mode. The value in CCR0, 512-1, defines the PWM
//   period and the values in CCR1-6 the PWM duty cycles. Using ~1048kHz SMCLK
//   as TBCLK, the timer period is ~488us.
//   ACLK = REF0, SMCLK = MCLK = TBCLK = default DCO ~1048kHz.
//
//                MSP430F534x 
//             -----------------
//         /|\|              XIN|-
//          | |                 |  
//          --|RST          XOUT|-
//            |                 |
//            |         P5.7/TB1|--> CCR1 - 75% PWM
//            |         P4.1/TB2|--> CCR2 - 25% PWM
//            |         P4.2/TB3|--> CCR3 - 12.5% PWM
//            |         P4.3/TB4|--> CCR4 - 6.26% PWM
//            |         P4.4/TB5|--> CCR5 - 3.13% PWM
//            |         P4.5/TB6|--> CCR6 - 1.566% PWM
//
//   Bhargavi Nisarga
//   Texas Instruments Inc.
//   Jun 2011
//   Built with CCSv4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************

#include <msp430f5342.h>

void Port_Mapping(void);

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  Port_Mapping();
  
  // Setup Port Pins              
  P4DIR |= 0x3E;                            // P4.1 - P4.5 output
  P4SEL |= 0x3E;                            // P4.1 - P4.5 Port Map functions  

  P5SEL |= BIT7;                            // P5.7 option select
  P5DIR |= BIT7;                            // P5.7 outputs

  TBCCR0 = 512-1;                           // PWM Period
  TBCCTL1 = OUTMOD_7;                       // CCR1 reset/set
  TBCCR1 = 383;                             // CCR1 PWM Duty Cycle	
  TBCCTL2 = OUTMOD_7;                       // CCR2 reset/set
  TBCCR2 = 128;                             // CCR2 PWM duty cycle	
  TBCCTL3 = OUTMOD_7;                       // CCR3 reset/set
  TBCCR3 = 64;                              // CCR3 PWM duty cycle	
  TBCCTL4 = OUTMOD_7;                       // CCR4 reset/set
  TBCCR4 = 32;                              // CCR4 PWM duty cycle	
  TBCCTL5 = OUTMOD_7;                       // CCR5 reset/set
  TBCCR5 = 16;                              // CCR5 PWM duty cycle	
  TBCCTL6 = OUTMOD_7;                       // CCR6 reset/set
  TBCCR6 = 8;                               // CCR6 PWM duty cycle	
  TBCTL = TBSSEL_2+MC_1;                    // SMCLK, upmode

  __bis_SR_register(LPM0_bits);             // CPU off
}

void Port_Mapping(void)
{
  __disable_interrupt();                    // Disable Interrupts before altering Port Mapping registers
  PMAPPWD = 0x02D52;                        // Enable Write-access to modify port mapping registers
  
  #ifdef PORT_MAP_RECFG                     
  PMAPCTL = PMAPRECFG;                      // Allow reconfiguration during runtime
  #endif  
  
  P4MAP1 = PM_TB0CCR2A;
  P4MAP2 = PM_TB0CCR3A;
  P4MAP3 = PM_TB0CCR4A;
  P4MAP4 = PM_TB0CCR5A;
  P4MAP5 = PM_TB0CCR6A;
  
  PMAPPWD = 0;                              // Disable Write-Access to modify port mapping registers
  #ifdef PORT_MAP_EINT
  __enable_interrupt();                     // Re-enable all interrupts
  #endif  
}