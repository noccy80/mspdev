/*   Description: A-Pool ADC conversions with Overdrive Compensation. A single   */
/*   ramp conversion using the ADC-DAC-REG with the DAC as ramp generator.  The  */
/*   counter is cleared by software; channels are set and conversion is triggered*/
/*   by software.  The comparator stops the counter when the ramp voltage crosses*/
/*   the selected input voltage.  The Result is stored in APINT.                 */
/****************************A_POOL ADC Conversion *******************************/
/*                                                                               */
/*                                                                               */
/*              +----L092---+                                                    */
/*              |*1      14 |                                                    */
/*              | 2      13 |                                                    */
/*              | 3      12 |<- Channel A0-Provide Analog Input   (0-256mV)      */
/*              | 4      11 |                                                    */
/*              | 5      10 |                                                    */
/*              | 6       9 |                                                    */
/*              | 7       8 |                                                    */
/*              +-----------+                                                    */
/*  D.Dang/D.Archbold/D.Szmulewicz                                               */
/*  Texas Instruments Inc.                                                       */
/*  Built with IAR Version 5.10.4                                                */
/*********************************************************************************/

#include <msp430l092.h>

int Result;

void main(void)
{
   
     WDTCTL = WDTPW + WDTHOLD;                           // Stop WDT 
     Result = 0;                                         // Initialize Result variable  

// Begin Configuration of the A-POOL registers
     APCTL = 0;                                        // Clear APCTL register
     APIE  = EOCIE;                                    // Enable Interrupt for End of Conversion  
    
     APCNF = CMPON+DBON+CONVON+APREFON+CLKSEL_MCLK;    // Configure A-POOL elements, Select MCLK as A-POOL Clock Source
     APINT = 0x00;                                     // Clear ADC-DAC-REG
     APCTL = OSEL+CBSTP+SBSTP+RUNSTOP+APPSEL_5+APNSEL_0;        // Set Channels and Start Conversion
 __bis_SR_register(LPM0_bits + GIE);                   // Enter LPM0 w/ interrupts enabled
    
     Result = APINT;
     APIE  = EOCIE;                                   // Enable Interrupt for End of Conversion  
     APCTL |= RUNSTOP + SLOPE;                        // Set Down and Start Conversion 
 __bis_SR_register(LPM0_bits + GIE);                  // Enter LPM0 w/ interrupts enabled
    
     Result += APINT;                                 // Add register value to Result variable
     Result >>= 1;                                    // Place Breakpoint Here: 
     
}

//A_POOL Interrupt Service Routine
#pragma vector=APOOL_VECTOR
__interrupt void A_POOL(void)
{
    APIFG = 0;                                        // Clear Interrupt Flag      
__bic_SR_register_on_exit(LPM0_bits);                 // Exit Active to start Down conversion 

}

