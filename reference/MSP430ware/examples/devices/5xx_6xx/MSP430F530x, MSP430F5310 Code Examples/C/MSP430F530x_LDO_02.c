//******************************************************************************
//   MSP430F530x Demo - Internal LDO enabled after device power-up
//
//  Description: This demo code shows example case where device is powered from 
//  an external supply and the LDO input coming on is detected to enable 
//  external system circuitry. When sufficient voltage at LDOI is present, P1.0 
//  is set, else reset; thus reflecting the status of the LDO being enabled or not
//    
//   Note: 
//    1.External supply is used to power the device VCC. If using TI target board 
//      (MSP-TS430RGC64B), remove jumper on JP4
//
//   ACLK = 32.768kHz, MCLK = SMCLK = default DCO~1MHz
//
//                MSP430F530x
//             -----------------
//        /|\|              VCC|<- External Supply
//         | |                 |
//         --|RST              |  
//           |             LDOO|--> 3.3V LDO Output
//           |             LDOI|<-- LDO Input Voltage (3.76V to 5.5V - refer to the d/s specs for actual range)
//           |                 |          
//           |             P1.0|--> LED - Reflects LDO status
//           |                 |          
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
  
  // Configure P1.0 as output 
  P1DIR |= BIT0;                            // Set P1.0 to output direction
  
  // Detect if sufficient voltage at LDOI is present
  if (LDOPWRCTL & LDOBGVBV)
    P1OUT |= BIT0;                          // Valid LDOI, LED on
  else
    P1OUT &= ~BIT0;
  
  // Enable interrupts
  LDOKEYPID = 0x9628;                       // Enable access to config registers
  LDOPWRCTL &= ~(LDOOVLIFG + LDOONIFG + LDOOFFIFG); 
                                            // Clear LDO-PWR IFGs before enabled IE bits 
  LDOPWRCTL |= LDOONIE + LDOOFFIE + LDOOVLIE;  
                                            // Enable LDO-PWR interrupts
  LDOKEYPID = 0x0;                          // Disbale access to config registers
  
  __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3 w/ interrupts
  __no_operation();                         // For debugger
}

#pragma vector=LDO_PWR_VECTOR
__interrupt void LDOInterruptHandler(void)
{
  if(LDOPWRCTL & VBONIFG)
  {
      LDOKEYPID = 0x9628;                   // Enable access to config registers
      LDOPWRCTL &= ~(LDOOVLIFG + LDOONIFG); // Software clear IFG    
                                            // Its possible that current peaks due to charging cap 
                                            // at LDOO might cause the LDOOVLIFG to trigger
      LDOKEYPID = 0x0;                      // Disbale access to config registers       
      P1OUT |= BIT0;                        // Valid LDOI, LED on
  }
  else if(LDOPWRCTL & VUOVLIFG)
  {
      LDOKEYPID = 0x9628;                   // Enable access to config registers
      LDOPWRCTL &= ~VUOVLIFG;               // Software clear IFG
      LDOKEYPID = 0x0;                      // Disbale access to config registers   
      while(1);                             // Over load indication; take necessary steps in application firmware
  }
  else if(LDOPWRCTL & VBOFFIFG)
  {
      LDOKEYPID = 0x9628;                   // Enable access to config registers
      LDOPWRCTL &= ~VBOFFIFG;               // Software clear IFG
      LDOKEYPID = 0x0;                      // Disbale access to config registers       
      P1OUT &= ~BIT0;                       // Voltage LDOI < launch voltage, LED off
  }
}
