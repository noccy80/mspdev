//******************************************************************************
// CC430x513x Demo - COMPB Hysteresis, CBOUT Toggle in LPM4; High speed mode
//
// Description: Use CompB and shared reference to determine if input 'Vcompare'
//    is high of low.  Shared reference is configured to generate hysteresis.
//	  When Vcompare exceeds Vcc*3/4 CBOUT goes high and when Vcompare is less 
//    than Vcc*1/4 then CBOUT goes low.
//    Connect P1.6/CBOUT to P1.0 externally to see the LED toggle accordingly.
//
//                 CC430x513x
//             ------------------                        
//         /|\|                  |                       
//          | |                  |                       
//          --|RST      P2.0/CB0 |<--Vcompare            
//            |                  |                       
//            |        P1.6/CBOUT|----> 'high'(Vcompare>Vcc*3/4); 'low'(Vcompare<Vcc*1/4)
//            |                  |  |
//            |            P1.0  |__| LED 'ON'(Vcompare>Vcc*3/4); 'OFF'(Vcompare<Vcc*1/4)
//            |                  | 
//                                                       
// 	 M Morales 
//   Texas Instruments Inc.
//   April 2009
//   Built with CCE Version: 3.2.2 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************
#include "cc430x513x.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;     // Stop WDT                     
 
  P1DIR |= BIT6;                            // P1.6 output direction  
  P1SEL |= BIT6;                            // Select CBOUT function on P1.6/CBOUT
 
  PMAPPWD = 0x02D52;                        // Get write-access to port mapping regs  
  P1MAP6 = PM_CBOUT0;                       // Map CBOUT output to P1.6 
  PMAPPWD = 0;                              // Lock port mapping registers 
  
  P2SEL |= BIT0;                            // Select CB0 input for P2.0 

  // Setup ComparatorB                                                                                           
  CBCTL0 |= CBIPEN + CBIPSEL_0; // Enable V+, input channel CB0              
  CBCTL1 |= CBPWRMD_0;          // CBMRVS=0 => select VREF1 as ref when CBOUT 
                                // is high and VREF0 when CBOUT is low  
                                // High-Speed Power mode        
  CBCTL2 |= CBRSEL;             // VRef is applied to -terminal  
  CBCTL2 |= CBRS_1+CBREF13;     // VREF1 is Vcc*1/4             
  CBCTL2 |= CBREF04+CBREF03;    // VREF0 is Vcc*3/4             
  CBCTL3 |= BIT0;               // Input Buffer Disable @P6.0/CB0    
  CBCTL1 |= CBON;               // Turn On ComparatorB           

  __bis_SR_register(LPM4_bits); // Enter LPM4
  __no_operation();             // For debug 
} 


