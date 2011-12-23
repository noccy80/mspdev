/*  Description: Toggle P1.0 using software and Timer_A0 overflow ISR. Timer0_A  */
/*  In this example an ISR triggers when TA0 overflows. Inside the TA overflow   */
/*  ISR P1.0 is toggled.                                                         */                   
/*  Proper use of the TA0IV interrupt vector generator is demonstrated.          */
/****************************Timer_A0*********************************************/
/*                                                                               */
/*                                                                               */
/*                                                                               */
/*                               +----L092---+                                   */
/*                               |*1      14 |                                   */
/*                               | 2      13 |                                   */
/*                               | 3      12 |                                   */
/*                               | 4      11 |                                   */
/*                               | 5      10 |                                   */
/*                               | 6       9 |                                   */
/*     P1.1 SMCLK~ 1Mhz/32  <-   | 7       8 |                                   */
/*                               +-----------+                                   */
/*                                                                               */
/*  D.Dang/D.Archbold/D.Szmulewicz                                               */
/*  Texas Instruments Inc.                                                       */
/*  Built with IAR Version 5.10.4                                                */
/*********************************************************************************/

#include "msp430l092.h"  

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
 
  P1DIR |= BIT0 + BIT1;                     // P1.0 Output Direction           
  P1SEL0 |=  BIT1 ;                
  P1SEL1 |=  BIT1 ;    
    
   /************************/
   /* Setup CCS            */
   /* SMCLK = HFCLK        */
   /************************/
    CCSCTL0 = CCSKEY;                       // Unlock CCS
    while (SFRIFG1 & OFIFG)                 // Oscillator Flag(s)?
  {
    CCSCTL7 = 0;                            // Clear HF & LF OSC fault flags
    SFRIFG1 = 0;                            // Clear OFIFG  
  }
    CCSCTL5 = DIVS_5;                       // Set the Dividers for SMCLK to 32
    CCSCTL4 |= SELS_0;                      // Select HFCLK/DCO as the source for SMCLK   
    CCSCTL0_H |= 0xFF;                      // Lock CCS
   /* Lock by writing to upper byte */
  
  TA0CTL = TASSEL_2 + MC_2 + TAIE;          // SMCLK, contmode, TA interrupt enable

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}

// Timer0_A1 Interrupt Vector (TA0IV) handler
#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer0_A1(void)
{
  switch  (__even_in_range(TA0IV, 14))      // Efficient switch-implementation
  {
    case  2: break;                         // TA0CCR1 not used
    case  4: break;                         // TA0CCR2 not used
    case  6: break;                         // Reserved
    case  8: break;                         // Reserved
    case 10: break;                         // Reserved   
    case 12: break;                         // Reserved
   
    case 14: P1OUT ^= BIT0;                 // overflow -> Toggle P1.0
              break;
  }
}

