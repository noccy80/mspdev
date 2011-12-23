//******************************************************************************
//   MSP430F530x Demo - Software Toggle PU.0/1
//
//   Description: Toggle PU.0/1 by xor'ing PU.0/1 inside of a software loop. In 
//   the example code, initial configuration is PU.0 = low and PU.1 = high. 
//    
//   Note: Since the LDO is not enabled in this case, an external connection 
//    between the device VCC and LDOO pin is required for the PortU operation
//
//   ACLK = 32.768kHz, MCLK = SMCLK = default DCO~1MHz
//
//                MSP430F530x
//             -----------------
//         /|\|              VCC|--
//          | |                 |  |
//          --|RST          LDOO|<-
//            |                 |
//            |             PU.0|--> Toggle
//            |             PU.1|--> Toggle (complementary to PU.0)
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
  volatile unsigned int i;

  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  
  // Configure PU.0 as output pins
  LDOKEYPID = 0x9628;                       // Enable access to config registers 
  PUCTL |= PUOPE + PUOUT1;                  // PortU input enable
                                            // PU.0 = low and PU.1 = high
  LDOKEYPID = 0x0;                          // Disbale access to config registers  

  while(1)                                  // continuous loop
  {
    for(i=50000;i>0;i--);                   // Delay
    LDOKEYPID = 0x9628;                     // Enable access to config registers 
    PUCTL ^= (PUOUT0 + PUOUT1);             // XOR PU.0/1    
    LDOKEYPID = 0x0;                        // Disbale access to config registers      
  }
}
