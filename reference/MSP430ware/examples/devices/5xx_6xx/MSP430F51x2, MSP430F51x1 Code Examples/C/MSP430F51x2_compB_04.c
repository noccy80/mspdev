//******************************************************************************
// MSP430F51x2 Demo - COMPB Toggle from LPM4; CompB in ultra low power mode
// 		Vcompare is compared against the Vcc*1/2
//
// Description: Use CompB and shared reference to determine if input 'Vcompare'
//    is high/low.  When Vcompare exceeds 0.5*Vcc CBOUT goes high and when 
//    Vcompare is less than 0.5*Vcc then CBOUT goes low. 
//    Connect P3.3/CBOUT to P1.0 externally to see the LED toggle accordingly.
//                                                   
//                 MSP430F51x2
//             ------------------                        
//         /|\|                  |                       
//          | |                  |                       
//          --|RST      P1.1/CB1 |<--Vcompare            
//            |                  |                                         
//            |        P3.3/CBOUT|----> 'high'(Vcompare>Vcc*0.5); 'low'(Vcompare<Vcc*0.5)
//            |                  |  |
//            |            P1.0  |__| LED 'ON'(Vcompare>Vcc*0.5); 'OFF'(Vcompare<Vcc*0.5)
//            |                  | 
//
//  C.Sterzik/B.Nisarga
//  Texas Instruments Inc.
//  Dec 2009
//  Built with CCS v4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include "msp430f5172.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;     // Stop WDT
  P3DIR |= BIT3;                // P3.3 output direction
  P3SEL |= BIT3;                // Select CBOUT function on P3.3/CBOUT

// Setup ComparatorB                           
  CBCTL0 |= CBIPEN+CBIPSEL_1;   // Enable V+, input channel CB1              
  CBCTL1 |= CBMRVS;             // CMRVL selects the refV - VREF0
  CBCTL1 |= CBPWRMD_2;          // Ultra-Low Power mode         
  CBCTL2 |= CBRSEL;             // VREF is applied to -terminal 
  CBCTL2 |= CBRS_1+CBREF04;     // VCC applied to R-ladder; VREF0 is Vcc*1/2
  CBCTL3 |= BIT1;               // Input Buffer Disable @P1.1/CB1    
  CBCTL1 |= CBON;               // Turn On ComparatorB           

  __delay_cycles(75);           // delay for the reference to settle

  __bis_SR_register(LPM4_bits);             // Enter LPM4
  __no_operation();                         // For debug 
}
