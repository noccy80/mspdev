//******************************************************************************
// MSP430x552x Demo - COMPB Toggle from LPM4; CompB in ultra low power mode
// 		Vcompare is compared against the Vcc*1/2
//
// Description: Use CompB and shared reference to determine if input 'Vcompare'
//    is high of low.  When Vcompare exceeds Vcc*1/2 CBOUT goes high and when 
//    Vcompare is less than Vcc*1/2 then CBOUT goes low. 
//    Connect P1.6/CBOUT to P1.0 externally to see the LED toggle accordingly.
//                                                   
//                 MSP430x552x
//             ------------------                        
//         /|\|                  |                       
//          | |                  |                       
//          --|RST      P6.0/CB0 |<--Vcompare            
//            |                  |                                         
//            |        P1.6/CBOUT|----> 'high'(Vcompare>Vcc*1/2); 'low'(Vcompare<Vcc*1/2)
//            |                  |  |
//            |            P1.0  |__| LED 'ON'(Vcompare>Vcc*1/2); 'OFF'(Vcompare<Vcc*1/2)
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
  P1DIR |= BIT6;                // P1.6/CBOUT output direction
  P1SEL |= BIT6;                // Select CBOUT function on P1.6/CBOUT

// Setup ComparatorB                           
  CBCTL0 |= CBIPEN+CBIPSEL_0;   // Enable V+, input channel CB0              
  CBCTL1 |= CBMRVS;             // CMRVL selects the refV - VREF0
  CBCTL1 |= CBPWRMD_2;          // Ultra-Low Power mode         
  CBCTL2 |= CBRSEL;             // VREF is applied to -terminal 
  CBCTL2 |= CBRS_1+CBREF04;     // VCC applied to R-ladder; VREF0 is Vcc*1/2
  CBCTL3 |= BIT0;               // Input Buffer Disable @P6.0/CB0    
  CBCTL1 |= CBON;               // Turn On ComparatorB           

  __delay_cycles(75);           // delay for the reference to settle

  __bis_SR_register(LPM4_bits);             // Enter LPM4
  __no_operation();                         // For debug 
}
