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

int Output=0; 

void main(void)
{
   
   WDTCTL = WDTPW + WDTHOLD;                         // Stop WDT 
   
  // Setup of TimerA0 Capture Compare Register 0    
   TA0CCTL0 = CCIE;                                  // TA0CCRO Interupt Enable 
   TA0CCR0 = 1;
   
  //Setup of the A-POOL module for DAC output
   APCNF = DBON+CONVON+APREFON;                      // Configure A-POOL elements
   APCTL |= ODEN+OSEL;                               // A-POOL Comparator/Saturation Based Stop Enable and Running 
    
  // Setup of TimerA0 Control Register   
   TA0CTL = TASSEL_2 + MC_1 + TACLR;                // SMCLK, Up Mode
   
   __bis_SR_register(LPM0_bits + GIE);              // Enter LPM0 w/ interrupts enabled
}


#pragma vector=TIMER0_A0_VECTOR 
__interrupt void Timer_A (void)
{
 
  if (APINT < 0xFF)                                  // Check for Max Value of Analog Output 256mV 
  {
    APINT = Output++;                                // Increase the Value of the Output by 1mv
  }
 
  else
  {
    APINT = 0;                                      // When max value has been reached, restart with output of 1mv
    Output = 0;                                     // Re-initialize the output value
  } 
  
}
