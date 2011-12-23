// Description: A single sample is made on the supply voltage with reference to the           
//  DAC buffer output. Software sets ADC10SC to start sample and conversion - ADC10SC
//  automatically cleared at EOC. ADC10 internal oscillator times sample (16x)
//  and conversion. In Mainloop MSP430 waits in LPM0 to save power until ADC10
//  conversion complete, ADC10_ISR will force exit from LPM0 in Mainloop on
//  reti. If VCC<0.9V, P1.0 is set indicating low-battery condition. 

/****************************A_POOL ADC Conversion *******************************/
/*                                                                               */
/*                                                                               */
/*              +----L092---+                                                    */
/*              |*1      14 |                                                    */
/*              | 2      13 |                                                    */
/*              | 3      12 |                                                    */
/*              | 4      11 |                                                    */
/*              | 5      10 |                                                    */
/*     P1.0  <- | 6       9 |                                                    */
/*              | 7       8 |                                                    */
/*              +-----------+                                                    */
/*  D.Dang/D.Archbold/D.Szmulewicz                                               */
/*  Texas Instruments Inc.                                                       */
/*  Built with IAR Version 5.10.4                                                */
/*********************************************************************************/


#include <msp430l092.h>

void main(void)

{
  

   WDTCTL = WDTPW + WDTHOLD;                          // Stop WDT 
   P1DIR = BIT0;                                      // Set P1.0 as an output
  

   // Begin Configuration of the A-POOL registers

    APCTL = 0;                                        // Clear APCTL register
    APIE  = EOCIE;                                    // Enable Interrupt for End of Conversion    
    APCNF = CMPON+DBON+CONVON+APREFON+CLKSEL_MCLK;    // Configure A-POOL elements, Select MCLK as A-POOL Clock Source
                                                      // Clear ADC-DAC-REG


   for (;;)
  {
     APINT = 0x00;  
     APIFG = 0;
     APCTL = OSEL+CBSTP+SBSTP + RUNSTOP+APPSEL_5+APNSEL_6;   // Set Channels and Start Conversion
    __bis_SR_register(LPM0_bits + GIE);                    // Enter LPM0 w/ interrupts enabled
 //   __no_operation();
 
    // Low-Battery voltage = 0.9V/8 = 113 mV(since APNSEL_6 was chosen). Full scale of ADC = 256mV (0xFF)
    // Then 113mV ~ 0x70
    if (APINT > 0x70)                              
      P1OUT &= ~0x01;                                 // Clear P1.0 LED: Battery voltage is good. 
    else
      P1OUT |= 0x01;                                   // Set0 P1.0 LED on if VCC is less than 0.9V
  }

}

 

//A_POOL Interrupt Service Routine

#pragma vector=APOOL_VECTOR
__interrupt void A_POOL(void)
{
  APIFG = 0;                                          // Clear APOOL interrupt flag
__bic_SR_register_on_exit(LPM0_bits);                 // Exit Active to start Down conversion 

}