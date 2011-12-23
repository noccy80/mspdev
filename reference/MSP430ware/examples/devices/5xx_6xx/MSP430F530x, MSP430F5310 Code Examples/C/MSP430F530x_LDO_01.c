//******************************************************************************
//   MSP430F530x Demo - Internal LDO powering device VCC and PortU
//
//   Description: This example code shows the device can be automatically 
//   powered up by the internal LDO when sufficicnt is present at the LDOI pin 
//   and how the external connection between LDOO and VCC can be used to power 
//   the device VCC.
//    
//   Note: 
//    1.To power the MSP430 device VCC via the internal LDO, connect  LDOO to  
//      VCC externally. If using TI target board (MSP-TS430RGC64B), jumper pin 
//      header JP4 
//    2.Ensure current drawn by device VCC is < ILDOO spec
//
//   ACLK = 32.768kHz, MCLK = SMCLK = default DCO~1MHz
//
//                MSP430F530x
//             -----------------
//        /|\|              VCC|<-
//         | |                 |  |(jumper JP4 on MSP-TS430RGC64B)
//         --|RST          LDOO|--
//           |                 |
//           |             LDOI|<-- LDO Input Voltage (3.76V to 5.5V - refer to the d/s specs for actual range)
//           |                 |                              
//           |             PU.0|--> Toggle
//           |             PU.1|--> Toggle (complementary to PU.0)
//
//   B. Nisarga
//   Texas Instruments Inc.
//   Dec 2010
//   Built with CCSv4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include <msp430f5310.h>    // To include F530x and F5310 header file v1.1, refer
                            // to the "ReadMe - Header" file in the code ex zip file

void main(void)
{
  volatile unsigned int i;

  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  
  // Configure PU.0 as output pins
  LDOKEYPID = 0x9628;                       // Enable access to config registers 
  PUCTL |= PUOPE + PUOUT1;                  // PortU input enable
                                            // PU.0 = low and PU.1 = high  
  LDOPWRCTL |= LDOOVLIE;                    // Enable LDO overload indication interrupt
  LDOKEYPID = 0x0;                          // Disbale access to config registers

  while(1)                                  // continuous loop
  {
    for(i=50000;i>0;i--);                   // Delay
    LDOKEYPID = 0x9628;                     // Enable access to config registers
    PUCTL ^= (PUOUT0 + PUOUT1);             // XOR PU.0/1    
    LDOKEYPID = 0x0;                        // Disbale access to config registers    
  }
}

#pragma vector=LDO_PWR_VECTOR
__interrupt void LDOInterruptHandler(void)
{
  if(LDOPWRCTL & VUOVLIFG)
  {
      LDOKEYPID = 0x9628;                   // Enable access to config registers
      LDOPWRCTL &= ~VUOVLIFG;               // Software clear IFG
      LDOKEYPID = 0x0;                      // Disbale access to config registers        
      while(1);                             // Over load indication; take necessary
                                            // steps in application firmware
  }
}
