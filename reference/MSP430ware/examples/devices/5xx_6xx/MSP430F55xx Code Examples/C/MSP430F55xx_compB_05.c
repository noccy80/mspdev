//******************************************************************************
//  MSP430x552x Demo - COMPB Hysteresis, CBOUT Toggle in LPM4; High speed mode
//
//  Description: Use CompB and shared reference to determine if input 'Vcompare'
//  is high of low.  Shared reference is configured to generate hysteresis.
//  When Vcompare exceeds Vcc*3/4 CBOUT goes high and when Vcompare is less 
//  than Vcc*1/4 then CBOUT goes low.
//  Connect P1.6/CBOUT to P1.0 externally to see the LED toggle accordingly.
//
//                 MSP430x552x
//             ------------------                        
//         /|\|                  |                       
//          | |                  |                       
//          --|RST      P6.0/CB0 |<--Vcompare            
//            |                  |                       
//            |        P1.6/CBOUT|----> 'high'(Vcompare>Vcc*3/4); 'low'(Vcompare<Vcc*1/4)
//            |                  |  |
//            |            P1.0  |__| LED 'ON'(Vcompare>Vcc*3/4); 'OFF'(Vcompare<Vcc*1/4)
//            |                  | 
//                                                       
//   C.Sterzik/B.Nisarga
//   Texas Instruments Inc.
//   April 2009
//   Built with CCSv4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include <msp430f5529.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;     // Stop WDT                     
 
  P1DIR |= BIT6;                // P1.6 output direction
  P1SEL |= BIT6;                // Select CBOUT function on P1.6

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

  __delay_cycles(75);           // delay for the reference to settle
  
  __bis_SR_register(LPM4_bits); // Enter LPM4
  __no_operation();             // For debug 
} 


