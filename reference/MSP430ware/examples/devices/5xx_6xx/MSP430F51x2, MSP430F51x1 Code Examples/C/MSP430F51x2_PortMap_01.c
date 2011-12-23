//******************************************************************************
//  MSP430F51x2 Demo - Port Mapping Port4; Single runtime configuration
//
//  Description:  Port4 is port mapped to output TimerD0/1 digital signals.
//  TTDxCCR0-2 generate different PWM DutyCycles and have been output on Port1 
//  pins. TD0CCR0 and TD1CCR0 generates a square wave of freq ACLK/2^10 ~32Hz. 
//  MCLK = SMCLK = default DCO; ACLK = REFO~32kHz;                           
//                                                       
//                 MSP430F51x2
//             ------------------                        
//         /|\|                  |                       
//          | |                  |                       
//          --|RST               |                                   
//            |       P1.0(TD0_0)|--> ACLK/2^10 ~ 32Hz                
//            |       P1.1(TD0_1)|--> 25%   
//            |       P1.2(TD0_2)|--> 50% 
//            |       P1.3(TD1_0)|--> ACLK/2^10 ~ 32Hz                
//            |       P1.4(TD1_1)|--> 75%                
//            |       P1.5(TD1_2)|--> 87.5%                 
//            |     P1.6(PM_None)|--> DVSS
//            |     P1.7(PM_None)|--> DVSS
//                 
//  B.Nisarga
//  Texas Instruments Inc.
//  Dec 2009
//  Built with CCS v4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include "msp430f5172.h"

// Port1 Port Mapping definitions
const unsigned char P1mapping[8] = {
                                      PM_TD0_0,
                                      PM_TD0_1,             
                                      PM_TD0_2,             
                                      PM_TD1_0,             
                                      PM_TD1_1,             
                                      PM_TD1_2,             
                                      PM_NONE,
                                      PM_NONE  };
// Function Definition
void Port_Mapping(void);

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  Port_Mapping();
  
  // Setup Port Pins              
  P1DIR |= 0xFF;                            // P1.0 - P1.7 output
  P1SEL |= 0xFF;                            // P1.0 - P1.6 Port Map functions
  
  // Setup TD0/TD1
  TD0CCTL0 = OUTMOD_4;                      // TD0CCR0 toggle
  TD0CCR0 = 256;                            // TD0CCR0 PWM Period/2
  TD0CCTL1 = OUTMOD_6;                      // TD0CCR1 toggle/set
  TD0CCR1 = 192;                            // TD0CCR1 PWM duty cycle
  TD0CCTL2 = OUTMOD_6;                      // TD0CCR2 toggle/set
  TD0CCR2 = 128;                            // TD0CCR2 PWM duty cycle
  
  TD1CCTL0 = OUTMOD_4;                      // TD1CCR0 toggle
  TD1CCR0 = 256;                            // TD1CCR0 PWM Period/2
  TD1CCTL1 = OUTMOD_6;                      // TD1CCR1 toggle/set
  TD1CCR1 = 64;                             // TD1CCR1 PWM duty cycle
  TD1CCTL2 = OUTMOD_6;                      // TD1CCR2 toggle/set
  TD1CCR2 = 32;                             // TD1CCR2 PWM duty cycle
  TD0CTL0 = TDSSEL_1 + MC_3;                // ACLK, up-down mode
  TD1CTL0 = TDSSEL_1 + MC_3;                // ACLK, up-down mode

  __bis_SR_register(LPM3_bits);             // Enter LPM3
  __no_operation();                         // For debugger
}

void Port_Mapping(void)
{
  unsigned char i;
  volatile unsigned char *ptr;
  __disable_interrupt();                    // Disable Interrupts before altering Port Mapping registers
  PMAPPWD = 0x02D52;                        // Enable Write-access to modify port mapping registers
  
  #ifdef PORT_MAP_RECFG                     
  PMAPCTL = PMAPRECFG;                      // Allow reconfiguration during runtime
  #endif  
  
  ptr = &P1MAP0;
  for(i=0;i<8;i++)
  {
    *ptr = P1mapping[i];
    ptr++;
  } 
  
  PMAPPWD = 0;                              // Disable Write-Access to modify port mapping registers
  #ifdef PORT_MAP_EINT
  __enable_interrupt();                     // Re-enable all interrupts
  #endif  
  
}

  
