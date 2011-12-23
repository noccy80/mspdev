//*****************************************************************************
//  MSP-FET430P440 Demo - LCD, Displays Numbers on a 4-Mux LCD
//
//  Description: This program displays digits stored in the
//  variable "value" on a 4-mux LCD then waits in low power mode 3.
//  To use the program run it as is or assign a different BCD number
//  (digits 0-9) to the variable "value".
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//	
//
//                                 Connections MSP430 -> LCD
//                                 -------------------------
//
//                                T.I.                  T.I.
//                           MSP430x44x MCU   STK/EVK 6.5 digit 4 mux LCD
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
#include  <msp430x44x.h>

// NOTE: DO NOT use leading zeros or it will be interpreted as octal data
unsigned long value = 0x43044;              // Number to display,
                                            // range = 0 to 65535
char* LCD = LCDMEM;


const char digit[10] =
{
  0xB7,  // "0"    LCD segments a+b+c+d+e+f
  0x12,  // "1"
  0x8F,  // "2"
  0x1F,  // "3"
  0x3A,  // "4"
  0x3D,  // "5"
  0xBD,  // "6"
  0x13,  // "7"
  0xBF,  // "8"
  0x3F   // "9"
};

void main(void)
{
  volatile unsigned int i;                  // Use volatile to prevent removal
                                            // by compiler optimization

  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  FLL_CTL0 |= XCAP14PF;                     // Configure load caps
  for (i = 0; i < 10000; i++);              // Delay for 32 kHz crystal to
                                            // stabilize

  LCDCTL = LCDSG0_1 + LCD4MUX + LCDON;      // 4-Mux LCD, segments S0-S15
  BTCTL  = BT_fLCD_DIV128;                  // LCD clock freq is ACLK/256
  P5SEL  = 0xFC;                            // Select P5.2-7 as Com and Rxx

  // Clear LCD memory to clear display
  for (i=0; i<19; i++)
  {
    LCD[i] = 0;
  }

  // Display contents of the variable value
  for (i=0; i<5; i++)
  {
    LCD[i] = digit[value & 0xF];            // Remainder = character in table
                                            // to display
    value >>= 4;                            // Shifts right so next character
                                            // can be displayed
  }

  LPM3;                                     // Enter LPM3
}
