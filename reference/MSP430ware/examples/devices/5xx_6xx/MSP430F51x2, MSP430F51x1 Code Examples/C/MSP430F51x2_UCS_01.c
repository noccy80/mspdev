//******************************************************************************
//   MSP430F51x2 Demo - Software Toggle P1.0 at Default DCO
//
//   Description: Toggle P1.0 by xor'ing P1.0 inside of a software loop.
//   ACLK is rought out on pin P3.0, SMCLK is brought out on P3.1, and MCLK
//   is brought out on pin P3.2 by using the port mapping controller
//   ACLK = REFO = 32.768kHz, MCLK = SMCLK = Default DCO
//
//                 MSP430F51x2
//             -----------------
//         /|\|                 |
//          | |             P3.0|--> MCLK
//          --|RST          P3.1|--> SMCLK
//            |             P3.2|--> ACLK
//            |                 |
//            |             P1.0|-->LED
//
//   Bhargavi Nisarga
//   Texas Instruments Inc.
//   Dec 2009
//   Built with CCS v4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include  "msp430f5172.h"

// Function Definition
void Port_Mapping(void);

void main(void)
{
  volatile unsigned int i;

  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  Port_Mapping();                           // Port Map port3
    
  P1DIR |= BIT0;                            // P1.0 output
  
  // Setup Port Pins 
  P3DIR |= 0x07;                            // P3.0 - P3.2 output
  P3SEL |= 0x07;                            // Port map P3.0 - P3.2                             

  while(1)
  {
    P1OUT ^= BIT0;                          // Toggle P1.0
    __delay_cycles(60000);                  // Delay
  }
}

void Port_Mapping(void)
{
  __disable_interrupt();                    // Disable Interrupts before altering Port Mapping registers
  PMAPPWD = 0x02D52;                        // Enable Write-access to modify port mapping registers
  
  #ifdef PORT_MAP_RECFG                     
  PMAPCTL = PMAPRECFG;                      // Allow reconfiguration during runtime
  #endif  
  
  P3MAP0 = PM_TD0CLKMCLK;
  P3MAP1 = PM_TD0_0SMCLK;
  P3MAP2 = PM_TD1OUTH;
  
  PMAPPWD = 0;                              // Disable Write-Access to modify port mapping registers
  #ifdef PORT_MAP_EINT
  __enable_interrupt();                     // Re-enable all interrupts
  #endif  
}