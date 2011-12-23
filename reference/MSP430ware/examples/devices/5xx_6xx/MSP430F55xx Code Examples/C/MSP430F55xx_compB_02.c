// MSP430x552x Demo - COMPB Toggle from LPM4; input channel CB1;
// 		Vcompare is compared against the internal reference 2.0V
//
// Description: Use CompB (input channel CB1) and internal reference to
//	  determine if input'Vcompare'is high of low.  When Vcompare exceeds 2.0V 
//    CBOUT goes high and when Vcompare is less than 2.0V then CBOUT goes low.
//    Connect P1.6/CBOUT to P1.0 externally to see the LED toggle accordingly.
//                                                   
//                 MSP430x552x
//             ------------------                        
//         /|\|                  |                       
//          | |                  |                       
//          --|RST       P6.1/CB1|<--Vcompare            
//            |                  |                                         
//            |        P1.6/CBOUT|----> 'high'(Vcompare>2.0V); 'low'(Vcompare<2.0V)
//            |                  |  |
//            |            P1.0  |__| LED 'ON'(Vcompare>2.0V); 'OFF'(Vcompare<2.0V)
//            |                  | 
//
//   Bhargavi Nisarga
//   Texas Instruments Inc.
//   April 2009
//   Built with CCSv4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include <msp430f5529.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;     // Stop WDT
  P1DIR |= BIT6;                // P1.6 output direction
  P1SEL |= BIT6;                // Select CBOUT function on P1.6/CBOUT

// Setup ComparatorB                           
  CBCTL0 |= CBIPEN + CBIPSEL_1; // Enable V+, input channel CB1              
  CBCTL1 |= CBPWRMD_1;          // normal power mode         
  CBCTL2 |= CBRSEL;             // VREF is applied to -terminal 
  CBCTL2 |= CBRS_3+CBREFL_2;    // R-ladder off; Bandgap voltage amplifier ON and generates 2.0V reference              
  CBCTL3 |= BIT1;               // Input Buffer Disable @P6.1/CB1    
  CBCTL1 |= CBON;               // Turn On ComparatorB           

  __delay_cycles(75);           // delay for the reference to settle

  __bis_SR_register(LPM4_bits);             // Enter LPM4
  __no_operation();                         // For debug 
}
