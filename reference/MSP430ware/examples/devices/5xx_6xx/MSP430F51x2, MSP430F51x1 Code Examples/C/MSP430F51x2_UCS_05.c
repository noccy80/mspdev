//******************************************************************************
//  MSP430F51x2 Demo - VLO sources ACLK
//
//  Description: This program demonstrates using VLO to source ACLK
//  ACLK = VLO = 9.4kHz (typical)
//
//                 MSP430F51x2
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//            |             P3.0|-->ACLK = ~10kHz
//            |                 |
//
//   Bhargavi Nisarga
//   Texas Instruments Inc.
//   Dec 2009
//   Built with CCS v4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include  "msp430f5172.h"

void Port_Mapping(void);

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  Port_Mapping();
  
  UCSCTL4 |= SELA_1;                        // VLO Clock Sources ACLK

  P3DIR |= BIT0;                            // P3.0=ACLK set out to pins
  P3SEL |= BIT0;                            

  __bis_SR_register(LPM3_bits);             // Enter LPM3
  __no_operation();                         // For debugger  
}

void Port_Mapping(void)
{
  __disable_interrupt();                    // Disable Interrupts before altering Port Mapping registers
  PMAPPWD = 0x02D52;                        // Enable Write-access to modify port mapping registers
  
  #ifdef PORT_MAP_RECFG                     
  PMAPCTL = PMAPRECFG;                      // Allow reconfiguration during runtime
  #endif  
  
  P3MAP0 = PM_TD1OUTH;
  
  PMAPPWD = 0;                              // Disable Write-Access to modify port mapping registers
  #ifdef PORT_MAP_EINT
  __enable_interrupt();                     // Re-enable all interrupts
  #endif  
}