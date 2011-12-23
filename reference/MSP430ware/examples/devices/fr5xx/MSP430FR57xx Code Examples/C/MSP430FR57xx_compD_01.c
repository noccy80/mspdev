//******************************************************************************
// MSP430FR57xx Demo - COMPD output Toggle in LPM4; Vcompare is compared against  
//                    the internal 2.0V reference
//
// Description: Use CompD and internal reference to determine if input'Vcompare'
//    is high or low.  When Vcompare exceeds 2.0V CDOUT goes high and when 
//    Vcompare is less than 2.0V then CDOUT goes low. 
//    Connect P3.5/CDOUT to P1.0 externally to see the LED toggle accordingly.
//                                                   
//                 MSP430FR5739
//             ------------------                        
//         /|\|                  |                       
//          | |                  |                       
//          --|RST       P1.1/CD1|<--Vcompare            
//            |                  |                                         
//            |        P3.5/CDOUT|----> 'high'(Vcompare>2.0V); 'low'(Vcompare<2.0V)
//            |                  |  |
//            |            P1.0  |__| LED 'ON'(Vcompare>2.0V); 'OFF'(Vcompare<2.0V)
//            |                  | 
//
//   Priya Thanigai
//   Texas Instruments Inc.
//   August 2010
//   Built with IAR Embedded Workbench Version: 5.10 & Code Composer Studio V4.0
//******************************************************************************
#include "msp430fr5739.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;     // Stop WDT
// compare input
  P1SEL0 |= BIT1;               // P1.1/CD1
  P1SEL1 |= BIT1; 
// Compare output
  P3DIR |= BIT5; 
  P3SEL1 |= BIT5;
  P3SEL0 |= BIT5;
  
// Setup ComparatorD                           
  CDCTL0 |= CDIPEN + CDIPSEL_1; // Enable V+, input channel CD0
  CDCTL2 |= CDRSEL;             // VREF is applied to -terminal 
  CDCTL2 |= CDRS_3+CDREFL_2;    // R-ladder off; bandgap ref voltage (1.2V)
                                // supplied ref amplifier to get Vcref=2.0V (CDREFL_2)           
  CDCTL3 |= BIT1;               // Input Buffer Disable @P1.1/CD0    
  CDCTL1 |= CDON;               // Turn On ComparatorB           

  __delay_cycles(400);           // delay for the reference to settle
  
  __bis_SR_register(LPM4_bits);          // Enter LPM4
  __no_operation();                      // For debug 
}
