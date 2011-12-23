//******************************************************************************
//   MSP430F532x Demo - Internal LDO powering device VCC and PortU
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
//                MSP430F532x
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
//   Oct 2011
//   Built with CCSv4 and IAR Embedded Workbench Version: 5.3
//******************************************************************************
#include <msp430f5328.h>    
                            

void main(void)
{
  volatile unsigned int i;

  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  
  // Configure PU.0 as output pins
  LDOKEYID = 0x9628;                        // Enable access to config registers 
  PUCTL |= PUOPE + PUOUT1;                  // PortU input enable
                                            // PU.0 = low and PU.1 = high  
  LDOPWRCTL |= LDOOVLIE;                    // Enable LDO overload indication interrupt
  LDOKEYID = 0x0;                           // Disbale access to config registers

  while(1)                                  // continuous loop
  {
    for(i=50000;i>0;i--);                   // Delay
    LDOKEYID = 0x9628;                      // Enable access to config registers
    PUCTL ^= (PUOUT0 + PUOUT1);             // XOR PU.0/1    
    LDOKEYID = 0x0;                         // Disbale access to config registers    
  }
}

#pragma vector=LDO_PWR_VECTOR
__interrupt void LDOInterruptHandler(void)
{
  if(LDOPWRCTL & VUOVLIFG)
  {
      LDOKEYID = 0x9628;                    // Enable access to config registers
      LDOPWRCTL &= ~VUOVLIFG;               // Software clear IFG
      LDOKEYID = 0x0;                       // Disbale access to config registers        
      while(1);                             // Over load indication; take necessary
                                            // steps in application firmware
  }
}
