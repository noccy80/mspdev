// Description: The following code example starts and stops the A-Pool with Timer_A0. 
// The starting and stopping ADC ramps can be observed on the AOUT pin. The ADC ramp 
// does not stop at a specific voltage level, because no SBSTP or CBSTP bits are set.
/****************************A_POOL ADC Conversion *******************************/
/*                                                                               */
/*                                                                               */
/*              +----L092---+                                                    */
/*              |*1      14 |                                                    */
/*              | 2      13 |                                                    */
/*              | 3      12 |<- Channel A0-Provide Analog Input                  */
/*              | 4      11 |                                                    */
/*              | 5      10 |                                                    */
/*              | 6       9 |                                                    */
/*              | 7       8 |-> AOUT                                             */
/*              +-----------+                                                    */
/*                                                                               */
/*  D.Dang/D.Archbold/D.Szmulewicz                                               */
/*  Texas Instruments Inc.                                                       */
/*  Built with IAR Version 5.10.4                                                */
/*********************************************************************************/

#include "msp430l092.h"

int Result;

void main(void)
{
   
   WDTCTL = WDTPW + WDTHOLD;                          // Stop WDT 
   TA0CCR0 = 600;                                     // Set start value to 600
   TA0CCR1 = 300;                                     // Set stop value to 300
   TA0CCTL0 = OUTMOD_3;                               // Set CCR0 outmode to Set/Reset
   TA0CCTL1 = OUTMOD_3;                               // Set CCR0 outmode to Set/Reset
   TA0CTL = TASSEL_2+MC_1+TACLR;                      // Set SMCLK to timer clock source +
                                                      // Set timer to up mode +
                                                      // Clear timer count register
// Begin Configuration of the A-POOL registers
   APCNF = CMPON+DBON+CONVON+APREFON+TA0EN;           // Enable comparator on +
                                                      // Enable DAC buffer +
                                                      // Enable conversion +
                                                      // Enable reference +
                                                      // Enable TimerA0 start
   APCTL = APPSEL_5+APPSEL_0+OSEL+ODEN+TBSTP;         // Set DAC buffer output to PSEL +
                                                      // Select output buffer +
                                                      // Enable output driver +
                                                      // Enable timer based stop    
      
while(1);
}
