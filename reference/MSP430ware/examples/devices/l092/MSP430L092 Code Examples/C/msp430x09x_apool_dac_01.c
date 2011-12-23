/*   Description: Output an Analog Signal using the APOOL DAC. A write to the    */
/*   APINT register while REFON, ODSEL, DBEN, and ODEN are set to one corresponds*/
/*   to an analog voltage with range 1..256mV driven on Aout.                    */
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
/*              | 7       8 |  -> AOUT- Analog Output Provided ~256mV            */
/*              +-----------+                                                    */
/*  D.Dang/D.Archbold/D.Szmulewicz                                               */
/*  Texas Instruments Inc.                                                       */
/*  Built with IAR Version 5.10.4                                                */
/*********************************************************************************/
#include "msp430l092.h"                               // 

void main(void)
{
   
   WDTCTL = WDTPW + WDTHOLD;                           // Stop WDT 
   
  //Setup of the A-POOL module for DAC output
    
    APCNF = DBON+CONVON+APREFON;                      // Configure A-POOL elements
    APCTL |= ODEN+OSEL;                               // A-POOL Comparator/Saturation Based Stop Enable and Running 
    
    while(1)
   
     {                                                // APINT - A-POOL integer Conversion Register
      APINT =0xFF;                                    // Output a Value of ~256mV on Aout, Change this Value for different
     }                                                // voltages. High Accuracy is reached when Aout > 20mV.
                                                      // Try the following values - 0x00 = 1mV ; 0x7F = 128mV; 0xFF = 256mV
   
}


