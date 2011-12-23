// Comparator in Compensated Mode - An input signal on A0 is compared with 
// an input signal on A2.  The signal present on A2 uses the input divider of 
// the module. The Results of the Comparator will be present on P1.3
// 
//                                     MSP430 L092
//                                   -----------------
//                               /|\|              XIN|-
//                                | |                 |
//                                --|RST          XOUT|-
//                                  |             P1.4|<--Comparator Input A0 
//           Comparator Input A2--> | P1.0        P1.3|-->Comparator Output
//
//    D.Dang/D.Archbold/D.Szmulewicz                                            
//    Texas Instruments Inc.                                                      
//    Built with IAR Version 5.10.4                                               
//******************************************************************************
#include "msp430l092.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;               // Stop watchdog timer to prevent time out reset
  SYSCNF |= 0x3000;                       // debug issue

  
  /**************************/
  /* Setup CCS              */
  /* MCLK = SMCLK = HFCLK/1 */
  /**************************/

  CCSCTL0 = CCSKEY;                       // Unlock CCS
  while (SFRIFG1 & OFIFG)                 // Oscillator Flag(s)?
  {
    CCSCTL7 = 0;                          // Clear HF & LF OSC fault flags
    SFRIFG1 = 0;                          // Clear OFIFG  
  }

  CCSCTL5 =  DIVM_0 + DIVS_0;             // Set the Dividers for  MCLK, and SMCLK to 1
  CCSCTL4 |= SELM_0 + SELS_0;             // Select HFCLK as the source for MCLK, and SMCLK                 
  CCSCTL0_H |= 0xFF;                      // Lock CCS
 
  /**************************/
  /* Setup Port 1           */
  /* Output P1.3            */
  /**************************/
                       
  P1DIR |= BIT3;
  P1SEL0 |= BIT3;
  P1SEL1 |= BIT3;
  
  /**************************/
  /* Configure APOOL        */
  /**************************/
  
  APIFG = 0;                              // Clear all APIFG 
  APCNF = CLKSEL_2;  
  APIFG = 0; 

  APCTL = APNSEL_0 + APPSEL_2;            // A2=P vs A0=N 
  APVDIV |= A2DIV_2;                      // A2 divide by 8
  APOMR = AZCMP;                          // Comparator in Compensated mode (CTEN = 0) 
  APCNF |= CMPON;                         // Enable comparator

__no_operation();                         // If A2/8 > A0, P1.3 = 1, else P1.3 = 0
while (1);  

}

