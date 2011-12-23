//******************************************************************************
//   CC430x613x Demo -  LCD display a single character
//
//   Description: Cycle through several characters in a single position on the 
//                LCDBA from Softbaugh. Put "0123456" on SBLCDA4 LCD.
//                ACLK = REF0 = 32Khz, MCLK = SMCLK = DCO = Default
//
//                 MSP430x631x
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |           
//            |                 |    SBLCDA4
//            |              S4 |     -----------------
//            |               - |--> | +  5 4 3 2 1 0 |
//            |              S5 |     -----------------
//            |             COM0|-----||||
//            |             COM1|------|||
//            |             COM2|-------||
//            |             COM3|--------|
//            |                 |
//
//
//   Texas Instruments Inc.
//   Built with CCE Version: 3.2.2.1.4
//******************************************************************************

#include "cc430x613x.h"

// LCD Segments
#define LCD_A    BIT0
#define LCD_B    BIT1
#define LCD_C    BIT2
#define LCD_D    BIT3
#define LCD_E    BIT6
#define LCD_F    BIT4
#define LCD_G    BIT5
#define LCD_H    BIT7

// LCD Segment Mapping
const unsigned char  LCD_Char_Map[] =
{
  LCD_A+LCD_B+LCD_C+LCD_D+LCD_E+LCD_F,        // '0' or 'O'
  LCD_B+LCD_C,                                // '1' or 'I'
  LCD_A+LCD_B+LCD_D+LCD_E+LCD_G,              // '2' or 'Z'
  LCD_A+LCD_B+LCD_C+LCD_D+LCD_G,              // '3'
  LCD_B+LCD_C+LCD_F+LCD_G,                    // '4' or 'y'
  LCD_A+LCD_C+LCD_D+LCD_F+LCD_G,              // '5' or 'S'
  LCD_A+LCD_C+LCD_D+LCD_E+LCD_F+LCD_G,        // '6' or 'b'
  LCD_A+LCD_B+LCD_C,                          // '7'
  LCD_A+LCD_B+LCD_C+LCD_D+LCD_E+LCD_F+LCD_G,  // '8' or 'B'
  LCD_A+LCD_B+LCD_C+LCD_D+LCD_F+LCD_G,        // '9' or 'g'
};

void main(void)
{ volatile unsigned char i;
  P5SEL |= (BIT5 | BIT6 | BIT7);
  P5DIR |= (BIT5 | BIT6 | BIT7);

//*******************************************************************************
// Configure LCD_B
//LCD_FREQ = ACLK/32/4, LCD Mux 4, turn on LCD

  LCDBCTL0 =  (LCDDIV0 + LCDDIV1 + LCDDIV2 + LCDDIV3 + LCDDIV4)| LCDPRE0 | LCD4MUX | LCDON | LCDSON;
  LCDBVCTL = LCDCPEN | VLCD_3_44;
  //LCDBCTL0 |= LCDON + LCDSON;
  REFCTL0 &= ~REFMSTR;

  //Charge pump generated internally at 3.44V, external bias (V2-V4) generation
  //Internal reference for charge pump 
  LCDBPCTL0 = 0x0030;                         //Select LCD Segments 4-5
  LCDBPCTL1 = 0x0000;                         //
  
  while(1)
  {
  	for(i=6;i>0;i--)
  	{
  		LCDM3 &= ~LCD_Char_Map[8];           // Clear LCD
        LCDM3 |= LCD_Char_Map[i-1];          // Display Character
        __delay_cycles(500000);
  	}
  }
}
