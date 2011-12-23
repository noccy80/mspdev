//******************************************************************************
// MSP430F51x2 Demo - Port Mapping single function to multiple pins; Single 
//                    runtime configuration. 
// Description:  Port1 is port mapped to output TimerA0 digital signals.  
// TACCR1-2 generate different DutyCycles and have been output on multiple pins. 
// ACLK = REFO~32kHz; MCLK = SMCLK = default DCO;                           
//                                                       
//                 MSP430F51x2
//             ------------------                        
//         /|\|                  |                       
//          | |                  |                       
//          --|RST               |                                   
//            |     P1.0(TA0CCR0)|--> 50%   
//            |     P1.1(TA0CCR0)|--> 50% 
//            |     P1.2(TA0CCR1)|--> 25%                 
//            |     P1.3(TA0CCR1)|--> 25%                 
//            |     P1.4(TA0CCR2)|--> 75%                 
//            |     P1.5(TA0CCR2)|--> 75%   
//            |     P1.6(default)|--> DVSS                
//            |     P1.7(default)|--> DVSS  
//                 
//  B.Nisarga
//  Texas Instruments Inc.
//  Dec 2009
//  Built with CCS v4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include "msp430f5172.h"

void Port_Mapping(void);

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  Port_Mapping();
  
  // Setup Port Pins              
  P1DIR |= 0x3F;                            // P1.0 - P1.5 output
  P1SEL |= 0x3F;                            // P1.0 - P1.6 Port Map functions
  
  // Setup TA0 
  TA0CCTL0 = OUTMOD_4;                      // TA3CCR0 toggle
  TA0CCR0 = 128;                            // TA3CCR0 PWM Period/2
  TA0CCTL1 = OUTMOD_6;                      // TA3CCR1 toggle/set
  TA0CCR1 = 96;                             // TA3CCR1 PWM duty cycle
  TA0CCTL2 = OUTMOD_6;                      // TA3CCR2 toggle/set
  TA0CCR2 = 32;                             // TA3CCR2 PWM duty cycle
  TA0CTL = TASSEL_1 + MC_3;                 // ACLK/2, up-down mode

  __bis_SR_register(LPM3_bits);		        // Enter LPM3
  __no_operation();                         // For debugger
}

void Port_Mapping(void)
{
  __disable_interrupt();                    // Disable Interrupts before altering Port Mapping registers
  PMAPPWD = 0x02D52;                        // Enable Write-access to modify port mapping registers
  
  #ifdef PORT_MAP_RECFG                     
  PMAPCTL = PMAPRECFG;                      // Allow reconfiguration during runtime
  #endif  
  
  P1MAP0 = PM_TA3_0;
  P1MAP1 = PM_TA3_0;
  P1MAP2 = PM_TA3_1;
  P1MAP3 = PM_TA3_1;
  P1MAP4 = PM_TA3_2;
  P1MAP5 = PM_TA3_2;
  
  PMAPPWD = 0;                              // Disable Write-Access to modify port mapping registers
  #ifdef PORT_MAP_EINT
  __enable_interrupt();                     // Re-enable all interrupts
  #endif  
}

