//******************************************************************************
// MSP430x530x Demo - Port Mapping single function to multiple pins; Single 
//                    runtime configuration. 
// Description:  Port 4 is port mapped to output TimerB digital signals.  
// TBCCR1-TBCCR3 generate different DutyCycles and have been output on multiple pins. 
// ACLK = REFO~32kHz; MCLK = SMCLK = default DCO;                           
//                                                       
//                 MSP430x530x
//             ------------------                        
//         /|\|                  |                       
//          | |                  |                       
//          --|RST               |                                   
//            |     P4.0(TB0CCR1)|--> 25%   
//            |     P4.1(TB0CCR1)|--> 25% 
//            |     P4.2(TB0CCR2)|--> 50%                 
//            |     P4.3(TB0CCR2)|--> 50%                 
//            |     P4.4(TB0CCR3)|--> 75%                 
//            |     P4.5(TB0CCR3)|--> 75%   
//            |     P4.6(default)|--> DVSS                
//            |     P4.7(default)|--> DVSS  
//                 
//   B. Nisarga
//   Texas Instruments Inc.
//   Dec 2010
//   Built with CCSv4.2 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include <msp430f5310.h>

void Port_Mapping(void);

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  Port_Mapping();
  
  // Setup Port Pins              
  P4DIR |= 0xFF;                            // P4.0 - P4.7 output
  P4SEL |= 0xFF;                            // P4.0 - P4.6 Port Map functions
  
  // Setup TB0 
  TB0CCR0 = 128;                            // PWM Period/2
  TB0CCTL1 = OUTMOD_6;                      // CCR1 toggle/set
  TB0CCR1 = 96;                             // CCR1 PWM duty cycle
  TB0CCTL2 = OUTMOD_6;                      // CCR2 toggle/set
  TB0CCR2 = 64;                             // CCR2 PWM duty cycle
  TB0CCTL3 = OUTMOD_6;                      // CCR1 toggle/set
  TB0CCR3 = 32;                             // CCR1 PWM duty cycle
  TB0CTL = TBSSEL_1 + MC_3;                 // ACLK/2, up-down mode

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
  
  P4MAP0 = PM_TB0CCR1A;
  P4MAP1 = PM_TB0CCR1A;
  P4MAP2 = PM_TB0CCR2A;
  P4MAP3 = PM_TB0CCR2A;
  P4MAP4 = PM_TB0CCR3A;
  P4MAP5 = PM_TB0CCR3A;
  
  PMAPPWD = 0;                              // Disable Write-Access to modify port mapping registers
  #ifdef PORT_MAP_EINT
  __enable_interrupt();                     // Re-enable all interrupts
  #endif  
}

