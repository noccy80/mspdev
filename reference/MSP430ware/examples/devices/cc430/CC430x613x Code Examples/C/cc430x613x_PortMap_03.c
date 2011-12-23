//******************************************************************************
// CC430x613x Demo - Port Map single function to multiple pins; 
//                   Multiple runtime configurations
//
// Description:  The port mapping of TIMERA0 is changed with each WDT interrupt.
//               TimerA0 provides 4 PWMs with 4 different duty cycles.
//               TimerA0 is sourced from ACLK.  ACLK is REFO, 32kHz
//                                                       
//                 MSP430x631x
//             ------------------------                        
//         /|\|                        |                       
//          | |                        |                       
//          --|RST                     |                                   
//            |     P2.0(TA0CCR1,2,3,4)|--> 25,50,75,87.5%                 
//            |     P2.1(TA0CCR1,2,3,4)|--> 25,50,75,87.5%                
//            |     P2.2(TA0CCR1,2,3,4)|--> 25,50,75,87.5%                
//            |     P2.3(TA0CCR1,2,3,4)|--> 25,50,75,87.5%                  
//            |     P2.4(TA0CCR1,2,3,4)|--> 25,50,75,87.5%                  
//            |     P2.5(TA0CCR1,2,3,4)|--> 25,50,75,87.5%                 
//            |     P2.6(TA0CCR1,2,3,4)|--> 25,50,75,87.5%                  
//            |     P2.7(TA0CCR1,2,3,4)|--> 25,50,75,87.5%                  
//                 
//   M Morales  
//   Texas Instruments Inc.
//   April 2009
//   Built with CCE Version: 3.2.2 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************
#include "cc430x613x.h"

#define PORT_MAP_RECFG                      // Multiple runtime Port Map configurations

void Port_Mapping(void);

const unsigned char PortSequence[4] = {   
    PM_TA0CCR1A,
    PM_TA0CCR2A,
    PM_TA0CCR3A,  
    PM_TA0CCR4A, 
};
unsigned char count=0;

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  
  Port_Mapping();
  
  // Setup Port Pins              
  P2DIR |= 0xFF;                            // P2.0 - P2.7 output
  P2SEL |= 0xFF;                            // P2.0 - P2.6 Port Map functions
  
  // Setup TB0 
  TA0CCR0 = 256;                            // PWM Period/2
  TA0CCTL1 = OUTMOD_6;                      // CCR1 toggle/set
  TA0CCR1 = 192;                            // CCR1 PWM duty cycle
  TA0CCTL2 = OUTMOD_6;                      // CCR2 toggle/set
  TA0CCR2 = 128;                            // CCR2 PWM duty cycle
  TA0CCTL3 = OUTMOD_6;                      // CCR3 toggle/set
  TA0CCR3 = 64;                             // CCR3 PWM duty cycle
  TA0CCTL4 = OUTMOD_6;                      // CCR4 toggle/set
  TA0CCR4 = 32;                             // CCR4 PWM duty cycle  
  TA0CTL = TASSEL__ACLK + MC_3;             // ACLK, up-down mode
  
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
    PMAPCTL = PMAPRECFG;                    // Allow reconfiguration during runtime
  #endif  
  
  ptr = &P2MAP0;
  for(i=0;i<8;i++)
  {
    *ptr = PortSequence[count];
    ptr++;
  }
 
  PMAPPWD = 0;                              // Disable Write-Access to modify port mapping registers
  
  #ifdef PORT_MAP_EINT
    __enable_interrupt();                   // Re-enable all interrupts
  #endif  
}

