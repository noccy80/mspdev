//******************************************************************************
//  Description: Use Timer CCRx units and overflow to generate
//  independent timing intervals. For demonstration, TA0CCR1 and TA0CCR2
//  output units are optionally selected with port pins P1.5 and P1.6
//  in toggle mode. As such, these pins will toggle when respective TA0CCRx
//  registers match the TA0R counter. Interrupts are also enabled with all
//  TA0CCRx units, software loads offset to next interval only - as long as
//  the interval offset is added to TACCRx, toggle rate is generated in
//  hardware. Timer0_A1 overflow ISR is used to toggle P1.0 with software.
//  Proper use of the TA0IV interrupt vector generator is demonstrated.
//
/****************************Timer_A0*********************************************/
/*                                                                               */
/*                                                                               */
/*                                                                               */
/*              +----L092---+                                                    */
/*              |*1      14 |     -> P1.6 TA0.1 output                           */
/*              | 2      13 |     -> P1.5 TA0.2 output                           */
/*              | 3      12 |                                                    */
/*              | 4      11 |                                                    */
/*              | 5      10 |                                                    */
/*              | 6       9 |                                                    */
/* SMCLK out<-  | 7       8 |                                                    */
/*              +-----------+                                                    */
/*                                                                               */
/*  D.Dang/D.Archbold/D.Szmulewicz                                               */
/*  Texas Instruments Inc.                                                       */
/*  Built with IAR Version 5.10.4                                                */
/*********************************************************************************/

#include "msp430l092.h"  

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
 
   // Setup Port 1 to output for Timer A0 and SMCLK 
   // P1.1 = SMCLK -> P1DIR.1 = 1; P1SEL0.1 = 1; P1SEL1.1 = 1;
   // P1.5 = TA0.2 -> P1DIR.5 = 1; P1SEL0.5 = 1; P1SEL1.5 = 1; 500Hz
   // P1.6 = TA0.1 -> P1DIR.6 = 1; P1SEL0.6 = 1; P1SEL1.6 = 0; 50Hz
  
  P1SEL0 |= BIT1 + BIT5 + BIT6;
  P1SEL1 |= BIT1 + BIT5;
  P1DIR  |= BIT0 + BIT1 + BIT5 + BIT6;  
    
   /***************************/
   /* Setup CCS               */
   /* SMCLK = HFCLK/1  ~1MHz  */
   /***************************/
    CCSCTL0 = CCSKEY;                       // Unlock CCS
    while (SFRIFG1 & OFIFG)                 // Oscillator Flag(s)?
  {
    CCSCTL7 = 0;                            // Clear HF & LF OSC fault flags
    SFRIFG1 = 0;                            // Clear OFIFG  
  }  
    CCSCTL4 = SELS_0 + SELM_0;              // Select HFCLK/DCO as the source for SMCLK   
    CCSCTL5 = DIVS_0 + DIVM_0;              // Set the Dividers for SMCLK to 1
    CCSCTL0_H |= 0xFF;                      // Lock CCS
   /* Lock by writing to upper byte */
  
  TA0CCTL0 = OUTMOD_4 + CCIE;               // TA0CCR0 toggle, interrupt enabled
  TA0CCTL1 = OUTMOD_4 + CCIE;               // TA0CCR1 toggle, interrupt enabled
  TA0CCTL2 = OUTMOD_4 + CCIE;               // TA0CCR2 toggle, interrupt enabled
  TA0CTL = TASSEL_2 +  MC_2 + TAIE;         // SMCLK, Contmode, int enabled

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}

// Timer0_A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A0(void)
{
  TA0CCR0 += 200;                            // Add Offset to TA0CCR0
}

// Timer0_A1 Interrupt Vector (TAIV) handler
#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer_A1(void)
{
  switch (__even_in_range(TA0IV, 14))        // Efficient switch-implementation
  {
    case  2: TA0CCR1 += 1000;                // Add Offset to TA0CCR1
             break;
    case  4: TA0CCR2 += 10000;               // Add Offset to TA0CCR2
             break;
    case  6: break;                          // Reserved
    case  8: break;                          // Reserved
    case 10: break;                          // Reserved   
    case 12: break;                          // Reserved
    case 14: P1OUT ^= BIT0;                  // Timer_A3 overflow
             break;
  }
}

