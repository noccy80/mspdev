//******************************************************************************
//   CC430x613x Demo -  LCD blinks between two different strings
//
//   Description: The LCD blinks on a WDT interrupt, showing two different
//                character strings on the LCD. 
//                ACLK = REF0 = 32Khz, MCLK = SMCLK = DCO = Default
//
//                 MSP430x631x
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |           
//            |                 |    SBLCDA4
//            |              S0 |     -----------------
//            |               - |--> | + 7 6 5 4 3 2 1 |
//            |              S9 |     -----------------
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
  LCD_A+LCD_B+LCD_C+LCD_E+LCD_F+LCD_G,        // 'A'        10
  LCD_A+LCD_D+LCD_E+LCD_F,                    // 'C'        11
  LCD_B+LCD_C+LCD_D+LCD_E+LCD_G,              // 'd'        12
  LCD_A+LCD_D+LCD_E+LCD_F+LCD_G,              // 'E'        13
  LCD_A+LCD_E+LCD_F+LCD_G,                    // 'F'        14
  LCD_B+LCD_C+LCD_E+LCD_F+LCD_G,              // 'H'        15
  LCD_B+LCD_C+LCD_D+LCD_E,                    // 'J'        16
  LCD_D+LCD_E+LCD_F,                          // 'L'        17
  LCD_A+LCD_B+LCD_E+LCD_F+LCD_G,              // 'P'        18
  LCD_B+LCD_C+LCD_D+LCD_E+LCD_F               // 'U'        19
};

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P5SEL |= (BIT5 | BIT6 | BIT7);
  P5DIR |= (BIT5 | BIT6 | BIT7);

  //**************************************************************************
  // Configure LCD_B 
  
  //LCD_FREQ = ACLK/32/2, LCD Mux 4, turn on LCD
  //LCB_BLK_FREQ = ACLK/512
  LCDBCTL0 =  (LCDDIV0 + LCDDIV1 + LCDDIV2 + LCDDIV3 + LCDDIV4)| LCDPRE0 | LCD4MUX | LCDON | LCDSON;
  LCDBVCTL = LCDCPEN | VLCD_3_44;
  REFCTL0 &= ~REFMSTR;

  //Charge pump generated internally at 3.44V, external bias (V2-V4) generation
  //Internal reference for charge pump 
  LCDBPCTL0 = 0x03FF;                         //Select LCD Segments 0-9
  LCDBPCTL1 = 0x0000;                         //

  //LCD Memory
  LCDM5 |= LCD_Char_Map[15];     //H
  LCDM4 |= LCD_Char_Map[13];     //E
  LCDM3 |= LCD_Char_Map[17];     //L
  LCDM2 |= LCD_Char_Map[17];     //L
  LCDM1 |= LCD_Char_Map[0];      //0
  
  // Blink Memory 
  LCDBM5 |= LCD_Char_Map[11];     //C
  LCDBM4 |= LCD_Char_Map[11];     //C
  LCDBM3 |= LCD_Char_Map[4];     //4
  LCDBM2 |= LCD_Char_Map[3];     //3
  LCDBM1 |= LCD_Char_Map[0];      //0
/****************************************************************/
/* Setup WDT                                                    */
  WDTCTL = WDT_ADLY_1000;                    // WDT 250ms, ACLK, interval timer
  SFRIE1 |= WDTIE;                          // Enable WDT interrupt
/****************************************************************/

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM3 w/interrupt
}

// Watchdog Timer interrupt service routine
#pragma vector = WDT_VECTOR
__interrupt void watchdog_timer(void)
{
  LCDBMEMCTL ^= LCDDISP;
}
