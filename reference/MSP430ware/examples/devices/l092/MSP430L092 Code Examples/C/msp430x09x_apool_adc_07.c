/*   Description: Multiple ADC Channels*/
/****************************A_POOL ADC Conversion *******************************/
/*                                                                               */
/*                                                                               */
/*                          +----L092---+                                        */
/*                          |*1      14 |                                        */
/*                          | 2      13 |                                        */
/*                          | 3      12 |<- Channel A0(0-256mV)                  */
/*                          | 4      11 |                                        */
/*                          | 5      10 |                                        */
/* Channel A2 (0-256mV)->   | 6       9 |                                        */
/* Channel A1 (0-256mV)->   | 7       8 |                                        */
/*                          +-----------+                                        */
/*                                                                               */
/*  D.Dang/ D.Archbold/ D.Szmulewicz                                             */
/*  Texas Instruments Inc.                                                       */
/*  Built with IAR Version 5.10.4                                                */
/*********************************************************************************/

#include "msp430l092.h"

int  ChannelA0, ChannelA1, ChannelA2;

void main(void)
{
   
   WDTCTL = WDTPW + WDTHOLD;                              // Stop WDT 
   
 // Begin Configuration of the A-POOL registers  
    APCTL = 0;                                            // Clear APCTL register
    APCNF = CMPON+DBON+CONVON+EOCBU+APREFON+CLKSEL_MCLK;  // Configure A-POOL elements, Select MCLK as A-POOL Clock Source
    APINT = 0x00;                                         // Clear ADC-DAC-REG
    
    while(1)
    {
    APIE  = EOCIE;                                        // Enable Interrupt for End of Conversion    
    APINT = 0x00;                                         // Clear ADC-DAC-REG
      APCTL = OSEL+CBSTP+RUNSTOP+APNSEL_0+APPSEL_5;       // Set Channels and Start Conversion
    __bis_SR_register(LPM0_bits + GIE);                   // Enter LPM0 w/ interrupts enabled
    ChannelA0 = APINT;                                    // Get Result for A0
   
    APIE  = EOCIE;                                        // Enable Interrupt for End of Conversion    
    APINT = 0x00;                                         // Clear ADC-DAC-REG
     APCTL = OSEL+CBSTP+RUNSTOP+APNSEL_1+APPSEL_5;        // Set Channels and Start Conversion
    __bis_SR_register(LPM0_bits + GIE);                   // Enter LPM0 w/ interrupts enabled 
    ChannelA1 = APINT;                                    // Get Result for A1
   
    APIE  = EOCIE;                                        // Enable Interrupt for End of Conversion
    APINT = 0x00;                                         // Clear ADC-DAC-REG
    APCTL = OSEL+CBSTP+RUNSTOP+APNSEL_2+APPSEL_5;         // Set Channels and Start Conversion
    __bis_SR_register(LPM0_bits + GIE);                   // Enter LPM0 w/ interrupts enabled 
    ChannelA2 = APINT;                                    // Get Result for A2    
    __no_operation();                                     // Place breakpoint here
    }
 
}

//A_POOL Interrupt Service Routine
#pragma vector=APOOL_VECTOR
__interrupt void A_POOL(void)
{

    APIFG = 0;                                        // Clear Interrupt Flag      
__bic_SR_register_on_exit(LPM0_bits);                 // Exit Active to Sample next Channel

}

