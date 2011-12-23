//******************************************************************************
//   MSP430F530x Demo  - Software Poll PU.0, Set P1.0 if PU.0 = 1
//
//  Description: Poll PU.0 in a loop, if hi P1.0 is set, if low, P1.0 reset.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//              MSP430F530x
//            -----------------
//        /|\|              VCC|--
//         | |                 |  |
//         --|RST          LDOO|<-
//     /|\   |                 |
//      --o--|PU.0         P1.0|-->LED
//     \|/
//
//  Note: 
//    1. PortU pins can only be configured together as either both inputs or both outputs
//    2. PortU is supplied by LDOO rail. Ensure 3.3V is available at LDOO, either by 
//       enabling the LDO OR by an external connection connecting device VCC to LDOO pin
//    3. In this example code, since the LDO is not enabled, an external connection between
//       the device VCC and LDOO pin is required for the PortU operation
//
//   B. Nisarga
//   Texas Instruments Inc.
//   Dec 2010
//   Built with CCSv4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include <msp430f5310.h>    // To include latest F530x and F5310 header file v1.1, refer
                            // to the "ReadMe - Header" file in the code ex zip file

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  
  // Configure PU.0 as input pin
  LDOKEYPID = 0x9628;                       // Enable access to config registers 
  PUCTL |= PUIPE;                           // PortU input enable
  LDOKEYPID = 0x0;                          // Disbale access to config registers

  // Configure P1.0 as output 
  P1DIR |= BIT0;                            // Set P1.0 to output direction
  
  while (1)                                 // Test P1.4
  {
    if (PUCTL & PUIN0)
      P1OUT |= BIT0;                        // if P1.4 set, set P1.0
    else
      P1OUT &= ~BIT0;                       // else reset
  }
}


