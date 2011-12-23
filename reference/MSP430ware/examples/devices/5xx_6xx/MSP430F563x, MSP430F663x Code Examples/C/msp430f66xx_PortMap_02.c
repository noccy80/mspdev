//******************************************************************************
// MSP430F66x Demo - Port Mapping single function to multiple pins; Single 
//                    runtime configuration. 
// Description:  Port 2 is port mapped to output TimerB digital signals.  
// TBCCR1-3 generate different DutyCycles and have been output on multiple pins. 
// ACLK = REFO~32kHz; MCLK = SMCLK = default DCO;                           
//                                                       
//                 MSP430x66x
//             ------------------                        
//         /|\|                  |                       
//          | |                  |                       
//          --|RST               |                                   
//            |     P2.0(TB0CCR1)|--> 25%   
//            |     P2.1(TB0CCR1)|--> 25% 
//            |     P2.2(TB0CCR2)|--> 50%                 
//            |     P2.3(TB0CCR2)|--> 50%                 
//            |     P2.4(TB0CCR3)|--> 75%                 
//            |     P2.5(TB0CCR3)|--> 75%   
//            |     P2.6(default)|--> DVSS                
//            |     P2.7(default)|--> DVSS  
//                 
//   Priya Thanigai
//   Texas Instruments Inc.
//   Nov 2009
//   Built with IAR Embedded Workbench Version: 4.20 & Code Composer Studio V4.0
//******************************************************************************
#include <msp430f6638.h>

void Port_Mapping(void);

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  Port_Mapping();
  
  // Setup Port Pins              
  P2DIR |= 0xFF;                            // P2.0 - P2.7 output
  P2SEL |= 0xFF;                            // P2.0 - P2.6 Port Map functions
  
  // Setup TB0 
  TB0CCR0 = 128;                            // PWM Period/2
  TB0CCTL1 = OUTMOD_6;                      // CCR1 toggle/set
  TB0CCR1 = 96;                             // CCR1 PWM duty cycle
  TB0CCTL2 = OUTMOD_6;                      // CCR2 toggle/set
  TB0CCR2 = 64;                             // CCR2 PWM duty cycle
  TB0CCTL3 = OUTMOD_6;                      // CCR1 toggle/set
  TB0CCR3 = 32;                             // CCR1 PWM duty cycle
  TB0CTL = TBSSEL_1 + MC_3;                 // ACLK/2, up-down mode

  __bis_SR_register(LPM3_bits);		    // Enter LPM3
  __no_operation();                         // For debugger
}

void Port_Mapping(void)
{
  // Disable Interrupts before altering Port Mapping registers
  __disable_interrupt();     
  // Enable Write-access to modify port mapping registers
  PMAPPWD = 0x02D52;                        
  
  #ifdef PORT_MAP_RECFG                    
  // Allow reconfiguration during runtime
  PMAPCTL = PMAPRECFG;                     
  #endif  
  
  P2MAP0 = PM_TB0CCR1B;
  P2MAP1 = PM_TB0CCR1B;
  P2MAP2 = PM_TB0CCR2B;
  P2MAP3 = PM_TB0CCR2B;
  P2MAP4 = PM_TB0CCR3B;
  P2MAP5 = PM_TB0CCR3B;
  // Disable Write-Access to modify port mapping registers
  PMAPPWD = 0;                              
  #ifdef PORT_MAP_EINT
  __enable_interrupt();                     // Re-enable all interrupts
  #endif  
}

