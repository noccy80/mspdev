//******************************************************************************
//  MSP430FR57xx Demo - COMPD Hysteresis, CDOUT Toggle in LPM4; High speed mode
//
//  Description: Use Compd and shared reference to determine if input 'Vcompare'
//  is high of low.  Shared reference is configured to generate hysteresis.
//  When Vcompare exceeds Vcc*3/4 CDOUT goes high and when Vcompare is less 
//  than Vcc*1/4 then CDOUT goes low.
//  Connect P3.5/CDOUT to P1.0 externally to see the LED toggle accordingly.
//
//                 MSP430FR5739
//             ------------------                        
//         /|\|                  |                       
//          | |                  |                       
//          --|RST      P1.1/CD0 |<--Vcompare            
//            |                  |                       
//            |        P3.5/CDOUT|----> 'high'(Vcompare>Vcc*3/4); 'low'(Vcompare<Vcc*1/4)
//            |                  |  |
//            |            P1.0  |__| LED 'ON'(Vcompare>Vcc*3/4); 'OFF'(Vcompare<Vcc*1/4)
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

  // Setup Comparatord                                            
                                               
  CDCTL0 |= CDIPEN + CDIPSEL_1; // Enable V+, input channel CD0              
  CDCTL2 |= CDRSEL;             // VRef is applied to -terminal  
  CDCTL2 |= CDRS_1+CDREF13;     // VREF1 is Vcc*1/4             
  CDCTL2 |= CDREF04+CDREF03;    // VREF0 is Vcc*3/4             
  CDCTL3 |= BIT1;               // Input Buffer Disable @P1.1/Cd1    
  CDCTL1 |= CDON;               // Turn On Comparatord           

  __delay_cycles(400);           // delay for the reference to settle
  
  __bis_SR_register(LPM4_bits); // Enter LPM4
  __no_operation();             // For debug 
} 


