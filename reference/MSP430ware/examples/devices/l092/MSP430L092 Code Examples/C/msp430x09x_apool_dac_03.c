/*   Description: Output several Analog Signals using the APOOL DAC. A triangle  */
/*   waveform is created on the ouput of the DAC.  A timer interrupt is used to  */
/*   change the value of the DAC.                                                */
/*                                                                               */
/****************************A_POOL DAC ******************************************/
/*                                                                               */
/*                                                                               */
/*              +----L092---+                                                    */
/*              |*1      14 |                                                    */
/*              | 2      13 |                                                    */
/*              | 3      12 |                                                    */
/*              | 4      11 |                                                    */
/*              | 5      10 |                                                    */
/*              | 6       9 |                                                    */
/*              | 7       8 |  -> AOUT- Analog Output Provided                   */
/*              +-----------+                                                    */
/*                                                                               */
/*  D.Dang/D.Archbold/D.Szmulewicz                                               */
/*  Texas Instruments Inc.                                                       */
/*  Built with IAR Version 5.10.4                                                */
/*********************************************************************************/
#include "msp430l092.h"

short Output=0x80; 

void main(void)
{
   
   WDTCTL = WDTPW + WDTHOLD;                          // Stop WDT 
   
  // Setup of TimerA0 Capture Compare Register 0    
   TA0CCTL0 = CCIE;                                   // TA0CCRO Interupt Enable 
   TA0CCR0 = 1;
   
  //Setup of the A-POOL module for DAC output
   APCNF = DBON+CONVON+APREFON;                       // Configure A-POOL elements
   APCTL |= ODEN+OSEL;                                // A-POOL Comparator/Saturation Based Stop Enable and Running 
    
  // Setup of TimerA0 Control Register   
   TA0CTL = TASSEL_2 + MC_1 + TACLR;                  // SMCLK, Up Mode
   
   __bis_SR_register(LPM0_bits + GIE);                // Enter LPM0 w/ interrupts enabled
}


#pragma vector=TIMER0_A0_VECTOR 
__interrupt void Timer_A (void)
{
 
  if (APFRACT_H == 0xFF)                              // Check for Value of Analog Output 128mV 
  {
   Output = 0;
   APFRACT_H = Output;                                // Set the Output Value to 129mV
  }
  
  else if (APFRACT_H == 0x7F)                         // Check for Max Value of Analog Output 256mV 
  {
   Output = 0x80;
   APFRACT_H = Output;                                // Set the Output Value to 1mV
  }
 
  else if (APFRACT_H < 0xFF)                          // Check for Max Value of Analog Output 256mV 
  {
   APFRACT_H = Output++;                              // Increase the Value of the Output by 1mv
  }

  
}
