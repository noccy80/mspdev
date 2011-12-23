//******************************************************************************
// MSP430F51x2 Demo - Port Map single function to multiple pins;
//		Multiple runtime configurations
//
// Description: The port mapping of TimerD0/1 is changed with each WDT interrupt.
//              TimerD0 and D1 provides 2 PWMs each with 4 different duty cycles.
//              TimerD0/1 is sourced from ACLK.  ACLK is REFO, 32kHz
//                                                       
//                 MSP430x631x
//             ------------------------                        
//         /|\|                        |                       
//          | |                        |                       
//          --|RST                     |                                   
//            |   P4.0(TD0_1,2,TD1_1,2)|--> 25,50,75,87.5%                 
//            |   P4.1(TD0_1,2,TD1_1,2)|--> 25,50,75,87.5%                
//            |   P4.2(TD0_1,2,TD1_1,2)|--> 25,50,75,87.5%                
//            |   P4.3(TD0_1,2,TD1_1,2)|--> 25,50,75,87.5%                  
//            |   P4.4(TD0_1,2,TD1_1,2)|--> 25,50,75,87.5%                  
//            |   P4.5(TD0_1,2,TD1_1,2)|--> 25,50,75,87.5%                 
//            |   P4.6(TD0_1,2,TD1_1,2)|--> 25,50,75,87.5%                  
//            |   P4.7(TD0_1,2,TD1_1,2)|--> 25,50,75,87.5%    
//            |                        |
//                 
//  B.Nisarga
//  Texas Instruments Inc.
//  Dec 2009
//  Built with CCS v4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include "msp430f5172.h"

#define PORT_MAP_RECFG                      // Multiple runtime Port Map configurations

const unsigned char PortSequence[4] = {   PM_TD0_1,             
                                          PM_TD0_2,
                                          PM_TD1_1,             
                                          PM_TD1_2,};

unsigned char count=0;
void Port_Mapping(void);

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  Port_Mapping();
  // Setup Port Pins              
  P1DIR |= 0x0F;                            // P4.0 - P4.3 output
  P1SEL |= 0x0F;                            // P4.0 - P4.3 Port Map functions
  
  // Setup TD0 
  TD0CCR0 = 256;                            // TD0 Period
  TD0CCTL1 = OUTMOD_6;                      // TD0CCR1 toggle/set
  TD0CCR1 = 192;                            // TD0CCR1 PWM duty cycle
  TD0CCTL2 = OUTMOD_6;                      // TD0CCR2 toggle/set
  TD0CCR2 = 128;                            // TD0CCR2 PWM duty cycle
  
  // Setup TD1
  TD1CCR0 = 256;                            // TD1 PWM Period/2
  TD1CCTL1 = OUTMOD_6;                      // TD1CCR1 toggle/set
  TD1CCR1 = 64;                             // TD1CCR1 PWM duty cycle
  TD1CCTL2 = OUTMOD_6;                      // TD1CCR2 toggle/set
  TD1CCR2 = 32;                             // TD1CCR2 PWM duty cycle  

  TD0CTL0 = TDSSEL_1 + MC_3;                // ACLK, up-down mode
  TD1CTL0 = TDSSEL_1 + MC_3;                // ACLK, up-down mode
  
// Setup WDT in interval mode                                                 
  WDTCTL = WDT_ADLY_1000;                   // WDT 1s, ACLK, interval timer
  SFRIE1 |= WDTIE;                          // Enable WDT interrupt

  while(1)
  {
    __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3 w/interrupt
    __no_operation();                         // For debugger
    
    Port_Mapping();
    count++;
    if(count==4)
      count = 0; 
  }
}

// Watchdog Timer interrupt service routine
#pragma vector = WDT_VECTOR
__interrupt void watchdog_timer(void)
{
  __bic_SR_register_on_exit(LPM3_bits);   // Exit LPM3

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
    *ptr = PortSequence[count];
    ptr++;
  }
 
  PMAPPWD = 0;                              // Disable Write-Access to modify port mapping registers
  #ifdef PORT_MAP_EINT
  __enable_interrupt();                     // Re-enable all interrupts
  #endif  
  
}

