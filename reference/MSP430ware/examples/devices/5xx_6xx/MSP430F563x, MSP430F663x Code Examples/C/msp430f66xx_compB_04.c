//******************************************************************************
// MSP430x66x Demo - COMPB Toggle from LPM4; CompB in ultra low power mode
// 		Vcompare is compared against the Vcc*1/2
//
// Description: Use CompB and shared reference to determine if input 'Vcompare'
//    is high or low.  When Vcompare exceeds Vcc*1/2 CBOUT goes high and when 
//    Vcompare is less than Vcc*1/2 then CBOUT goes low. 
//    Connect P3.0/CBOUT to P1.0 externally to see the LED toggle accordingly.
//                                                   
//                 MSP430x66x
//             ------------------                        
//         /|\|                  |                       
//          | |                  |                       
//          --|RST      P6.0/CB0 |<--Vcompare            
//            |                  |                                         
//            |        P3.0/CBOUT|----> 'high'(Vcompare>Vcc*1/2); 'low'(Vcompare<Vcc*1/2)
//            |                  |  |
//            |            P1.0  |__| LED 'ON'(Vcompare>Vcc*1/2); 'OFF'(Vcompare<Vcc*1/2)
//            |                  | 
//
//   Priya Thanigai
//   Texas Instruments Inc.
//   Nov 2009
//   Built with IAR Embedded Workbench Version: 4.20 & Code Composer Studio V4.0
//******************************************************************************
#include <msp430f6638.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P3DIR |= BIT0;                            // P3.0CBOUT output direction
  P3SEL |= BIT0;                            // Select CBOUT function on P3.0/CBOUT

// Setup ComparatorB                           
  CBCTL0 |= CBIPEN+CBIPSEL_0;               // Enable V+, input channel CB0              
  CBCTL1 |= CBMRVS;                         // CMRVL selects the refV - VREF0
  CBCTL1 |= CBPWRMD_2;                      // Ultra-Low Power mode         
  CBCTL2 |= CBRSEL;                         // VREF is applied to -terminal 
  CBCTL2 |= CBRS_1+CBREF04;                 // VCC applied to R-ladder; VREF0 is Vcc*1/2
  CBCTL3 |= BIT0;                           // Input Buffer Disable @P6.0/CB0    
  CBCTL1 |= CBON;                           // Turn On ComparatorB           

  __delay_cycles(75);                       // delay for the reference to settle

  __bis_SR_register(LPM4_bits);             // Enter LPM4
  __no_operation();                         // For debug 
}
