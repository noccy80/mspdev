/*   Description:  ADC Temperature Sample                                        */
/****************************A_POOL ADC Conversion *******************************/
/*                                                                               */
/*                                                                               */
/*              +----L092---+                                                    */
/*              |*1      14 |                                                    */
/*              | 2      13 |                                                    */
/*              | 3      12 |                                                    */
/*              | 4      11 |                                                    */
/*              | 5      10 |                                                    */
/*              | 6       9 |                                                    */
/*              | 7       8 |                                                    */
/*              +-----------+                                                    */
/*                                                                               */
/*  D.Dang/ D.Archbold/ D.Szmulewicz                                             */
/*  Texas Instruments Inc.                                                       */
/*  Built with IAR Version 5.10.4                                                */
/*********************************************************************************/

#include "msp430l092.h"

int Result;
volatile unsigned long int DegC;

void main(void)
{
   WDTCTL = WDTPW + WDTHOLD;                                       // Stop WDT 
   
  // Begin Configuration of the A-POOL registers
   
    APCTL = 0;                                                     // Clear APCTL register
    APIE |= EOCIE;                                                 // Enable Interrupt for End of Conversion   
    APTRIM = REFTSEL;
    APVDIV = TMPSEN;                                               // Enable Temperature Sensor 
    APCNF = CMPON+DBON+CONVON+APREFON+CLKSEL_MCLK;                 // Configure A-POOL elements, Select MCLK as A-POOL Clock Source


    
    APCTL = OSEL+ODEN+OSWP+APPSEL_5+APNSEL_4;                      // Set Channels and Start Conversion  
    APINT = 0x00;                                                  // Clear ADC-DAC-REG
    
    APCTL |= CBSTP+SBSTP+RUNSTOP;
 __bis_SR_register(LPM0_bits + GIE);                               // Enter LPM0 w/ interrupts enabled
    
    Result = APINT; 
    DegC = (int)(Result-179)*(1/0.464)+30;                        // Refer to datasheet for accuracy and offset specs
    
 __no_operation();                                                 // SET BREAKPOINT HERE

}
    
    
//A_POOL Interrupt Service Routine
#pragma vector=APOOL_VECTOR
__interrupt void A_POOL(void)
{
    APIFG = 0;                                                     // Clear Interrupt Flag      
__bic_SR_register_on_exit(LPM0_bits);                              // Exit Active to calculate Temperature 
   

}

