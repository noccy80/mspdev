// Comparator in Compensated Mode - An input signal on A0 is compared with 
// internal voltage reference.  The Results of the Comparator will be present on P1.3
// 
//                                     MSP430 L092
//                                   -----------------
//                               /|\|              XIN|-
//                                | |                 |
//                                --|RST          XOUT|-
//                                  |             P1.4|<--Comparator Input A0 
//                                  |             P1.3|-->Comparator Output
//
//  D.Dang/ D.Archbold/ D.Szmulewicz                                           
//  Texas Instruments Inc.                                                 
//  Built with IAR Version 5.10.4                                                    
//****************************************************************************
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
  APCNF = CLKSEL_2 + APREFON;             // Select SMCLK for APOOL Master Clock and Enable APOOL reference
  APIFG = 0;                              // Clear all APIFG 

  APCTL = APPSEL_0 + APNSEL_7;            // Select Channels A0 and Voltage Reference
  APOMR = AZCMP;                          // Select Comparator Mode
  APCNF |= CMPON;                         // Comparator ON
                                          // If Vref < A0, P1.3 = 1, else P1.3 = 0
__no_operation();
while (1);  

}

