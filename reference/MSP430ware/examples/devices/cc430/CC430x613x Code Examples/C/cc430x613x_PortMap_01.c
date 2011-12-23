//******************************************************************************
// CC430x613x Demo - Port Mapping Port2; Single runtime configuration
//
// Description:  Port2 is port mapped to output TimerA digital signals. TACCR1-3 
// generate different PWM DutyCycles. TACCR0 generates a square wave of 
// freq ACLK/2^10 ~32Hz. 
// MCLK = SMCLK = default DCO; ACLK = REFO~32kHz;                           
//                                                       
//                 CC430x613x
//             ------------------                        
//         /|\|                  |                       
//          | |                  |                       
//          --|RST               |                                   
//            |     P2.0(TA0CCR0)|--> ACLK/2^10 ~ 32Hz                
//            |     P2.2(TA0CCR1)|--> 25%   
//            |     P2.4(TA0CCR2)|--> 50% 
//            |     P2.6(TA0CCR3)|--> 75%                
//            |     P2.7(PM_None)|--> DVSS
//                 
//   M Morales
//   Texas Instruments Inc.
//   April 2009
//   Built with CCE Version: 3.2.2 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************
#include "cc430x613x.h"

// Function Definition
void Port_Mapping(void);

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  
  PMAPPWD = 0x02D52;                        // Get write-access to port mapping regs  
  P2MAP0 = PM_TA0CCR0A;                       // Map CBOUT output to P1.6 
  P2MAP2 = PM_TA0CCR1A;
  P2MAP4 = PM_TA0CCR2A;
  P2MAP6 = PM_TA0CCR3A;
  P2MAP7 = PM_NONE;   
  PMAPPWD = 0;                              // Lock port mapping registers 
  
  // Setup Port Pins              
  P2DIR |= BIT0+BIT2+BIT4+BIT6+BIT7;        // P2.0,2,4,6,7 output
  P2SEL |= BIT0+BIT2+BIT4+BIT6+BIT7;        // P2.0,2,4,6,7 Port Map functions
  
  // Setup TB0 
  TA0CCTL0 = OUTMOD_4;                      // CCR1 toggle/set
  TA0CCR0 = 256;                            // PWM Period/2
  TA0CCTL1 = OUTMOD_6;                      // CCR1 toggle/set
  TA0CCR1 = 192;                            // CCR1 PWM duty cycle
  TA0CCTL2 = OUTMOD_6;                      // CCR2 toggle/set
  TA0CCR2 = 128;                            // CCR2 PWM duty cycle
  TA0CCTL3 = OUTMOD_6;                      // CCR3 toggle/set
  TA0CCR3 = 64;                             // CCR3 PWM duty cycle
  TA0CTL = TASSEL__ACLK + MC_3;             // ACLK, up-down mode

  __bis_SR_register(LPM3_bits);       		// Enter LPM3
  __no_operation();                         // For debugger
}

