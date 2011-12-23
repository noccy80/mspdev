//*****************************************************************************
//  MSP-FET430P410 Demo - LCD, Display Numbers on a 4-Mux LCD
//
//  Description: This program displays digits stored in the variable "value"
//  on a 4-mux LCD, then waits in low power mode 3. To use the program run it
//  as is or use the debugger to assign a different BCD number (digits 0-9)
//  to the variable "value".
//  ACLK = LFXT1 = 32768 Hz, MCLK = SMCLK = DCO = 32 x ACLK = 1048576 Hz
//  //* An external watch crystal is required on XIN/XOUT for ACLK *//	
//
//                                 Connections MSP430 -> LCD
//                                 -------------------------
//
//                                T.I.            T.I. MSP-EVK430S320
//                           MSP430x41x MCU   STK/EVK 6.5 digit 4 mux LCD
//                                                    #T218010
//                           ---------------       --------------
//                          |          COM3 |-----|2    COM4     |
//                          |          COM2 |-----|1    COM3     |
//                          |          COM1 |-----|3    COM2     |
//                          |          COM0 |-----|4,20 COM1     |
//                          |          SEG0 |-----|19            |
//                          |          SEG1 |-----|18            |
//                          |          SEG2 |-----|17            |
//                          |          SEG3 |-----|16            |
//                          |          SEG4 |-----|15            |
//                          |          SEG5 |-----|14            |
//                          |          SEG6 |-----|13            |
//                          |          SEG7 |-----|12            |
//                          |          SEG8 |-----|11            |
//                          |          SEG9 |-----|10            |
//                          |          SEG10|-----|9             |
//                          |          SEG11|-----|8             |
//                          |          SEG12|-----|7             |
//                          |          SEG13|-----|6             |
//                          |          SEG14|-----|5 (bits C,E,H |
//                          |               |     |   of digit 7)|
//                          |               |      --------------
//                          |               |
//                           ---------------
//
//                   NOTE: Pin R03 on the MSP430 must be connected to GND
//
//  G. Morton / H. Grewal
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//*****************************************************************************
#include  <msp430x41x.h>


unsigned int h;
unsigned int index;
unsigned int dig_pntr;


/* Variable Declarations */
unsigned long value = 0x43044;               // Number to display,
                                            // range = 0 to 65535
                                            // NOTE: DO NOT use leading zeros
                                            //       or it will be interpreted
                                            //       as octal data


char* LCD = LCDMEM;


/* LCD Mapping Array */
const char digit[10] =
{
  0xB7,  // '0'    LCD segments a+b+c+d+e+f
  0x12,  // '1'
  0x8F,  // '2'
  0x1F,  // '3'
  0x3A,  // '4'
  0x3D,  // '5'
  0xBD,  // '6'
  0x13,  // '7'
  0xBF,  // '8'
  0x3F   // '9'
};


void main(void)
{
  volatile unsigned int i;                  // Use volatile to prevent removal
                                            // by compiler optimization

  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  FLL_CTL0 |= XCAP14PF;                     // Configure load caps
  for (i = 0; i < 10000; i++);              // Delay for 32 kHz crystal to
                                            // stabilize

  // Initialize LCD
  LCDCTL = LCDP1+LCDP0+LCD4MUX+LCDON;       // 4-Mux LCD, segments S0-S23
  BTCTL  = BTFRFQ1;                         // Set freqLCD = ACLK/128
  P5SEL  = 0xFC;                            // Set Rxx and COM pins for LCD

  // Clear LCD memory to clear display
  for (index=0; index<12; index++)
  {
    LCD[index] = 0;
  }

  // Display contents of the variable value
  for (index=0; index<5; index++)
  {
    LCD[index] = digit[value & 0xF];        // Remainder = character in table to display
    value >>= 4;                            // Shifts right so next character can be displayed
  }

  LPM3;                                     // Enter low power mode 3
}
