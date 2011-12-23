//******************************************************************************
// MSP430x530x Demo - COMPB interrupt capability; Vcompare is compared against 
//                    internal 1.5V reference
//
// Description: Use CompB and internal reference to determine if input'Vcompare'
//    is high of low.  For the first time, when Vcompare exceeds the 1.5V internal
//	  reference, CBIFG is set and device enters the CompB ISR. In the ISR CBIES is
//	  toggled such that when Vcompare is less than 1.5V internal reference, CBIFG is set.
//    LED is toggled inside the CompB ISR
//                                                   
//                 MSP430x530x
//             ------------------                        
//         /|\|                  |                       
//          | |                  |                       
//          --|RST      P6.0/CB0 |<--Vcompare            
//            |                  |                                         
//            |            P1.0  |--> LED 'ON'(Vcompare>1.5V); 'OFF'(Vcompare<1.5V)
//            |                  | 
//
//   B. Nisarga
//   Texas Instruments Inc.
//   Dec 2010
//   Built with CCSv4.2 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include <msp430f5310.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;     // Stop WDT
  P1DIR |= BIT0;                // P1.0/LED output direction
 
// Setup ComparatorB                           
  CBCTL0 |= CBIPEN + CBIPSEL_0; // Enable V+, input channel CB0            
  CBCTL1 |= CBPWRMD_1;          // normal power mode         
  CBCTL2 |= CBRSEL;             // VREF is applied to -terminal 
  CBCTL2 |= CBRS_3+CBREFL_1;    // R-ladder off; bandgap ref voltage (1.2V)
                                // supplied ref amplifier to get Vcref=1.5V (CBREFL_2)            
  CBCTL3 |= BIT0;               // Input Buffer Disable @P6.0/CB0    

  __delay_cycles(75);           // delay for the reference to settle
  
  CBINT &= ~(CBIFG + CBIIFG);   // Clear any errant interrupts  
  CBINT  |= CBIE;               // Enable CompB Interrupt on rising edge of CBIFG (CBIES=0)
  CBCTL1 |= CBON;               // Turn On ComparatorB    
  
  __bis_SR_register(LPM4_bits+GIE);         // Enter LPM4 with inetrrupts enabled
  __no_operation();                         // For debug 
}

// Comp_B ISR - LED Toggle
#pragma vector=COMP_B_VECTOR
__interrupt void Comp_B_ISR (void)
{
  CBCTL1 ^= CBIES;              // Toggles interrupt edge
  CBINT &= ~CBIFG;              // Clear Interrupt flag
  P1OUT ^= 0x01;                // Toggle P1.0
}
