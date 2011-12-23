//******************************************************************************
// MSP430FR57xx Demo - COMPD interrupt capability; Vcompare is compared against 
//                    internal 1.5V reference
//
// Description: Use CompD and internal reference to determine if input'Vcompare'
// is high of low.  For the first time, when Vcompare exceeds the 1.5V internal
// reference, CDIFG is set and device enters the CompD ISR. In the ISR CDIES is
// toggled such that when Vcompare is less than 1.5V internal reference, 
// CDIFG is set.
// LED is toggled inside the CompD ISR
//                                                   
//                 MSP430FR5739
//             ------------------                        
//         /|\|                  |                       
//          | |                  |                       
//          --|RST      P1.1/CD1 |<--Vcompare            
//            |                  |                                         
//            |            P1.0  |--> LED 'ON'(Vcompare>1.5V); 'OFF'(Vcompare<1.5V)
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
  P1DIR |= BIT0;                // P1.0/LED output direction
// compare input
  P1SEL0 |= BIT1;               // P1.1/CD1
  P1SEL1 |= BIT1; 
 
// Setup ComparatorB                           
  CDCTL0 |= CDIPEN + CDIPSEL_1; // Enable V+, input channel CD1            
  CDCTL2 |= CDRSEL;             // VREF is applied to -terminal 
  CDCTL2 |= CDRS_3+CDREFL_1;    // R-ladder off; bandgap ref voltage (1.2V)
                                // supplied ref amplifier to get Vcref=1.5V (CDREFL_2)            
  CDCTL3 |= BIT1;               // Input Buffer Disable @P1.1/CD1    

  __delay_cycles(400);           // delay for the reference to settle
  
  CDINT &= ~(CDIFG + CDIIFG);   // Clear any errant interrupts  
  CDINT  |= CDIE;               // Enable CompB Interrupt on rising edge of CDIFG (CDIES=0)
  CDCTL1 |= CDON;               // Turn On ComparatorB    
  
  __bis_SR_register(LPM4_bits+GIE);         // Enter LPM4 with inetrrupts enabled
  __no_operation();                         // For debug 
}

// Comp_d ISR - LED Toggle
#pragma vector=COMP_D_VECTOR
__interrupt void Comp_D_ISR (void)
{
  CDCTL1 ^= CDIES;              // Toggles interrupt edge
  CDINT &= ~CDIFG;              // Clear Interrupt flag
  P1OUT ^= 0x01;                // Toggle P1.0
}
