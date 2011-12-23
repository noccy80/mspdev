//******************************************************************************
//   MSP430x42x0 Demo - LCD_A Put "0123456" on SBLCDA4 LCD
//
//  Description; Put "0123456" on SBLCDA4 LCD.
//  ACLK = LFXT1 = 32768, MCLK = SMCLK = DCO = 32xACLK = 1.048576MHz
//  //*An external watch crystal is required on XIN/XOUT for ACLK*//	
//               MSP430F4270
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32kHz
//         --|RST          XOUT|-
//           |                 |
//           |                 |    SBLCDA4
//           |             S0  |     -----------------
//           |              -  |--> | + 7 6 5 4 3 2 1 |
//           |             S13 |     -----------------
//           |             COM0|-----||||
//           |             COM1|------|||
//           |             COM2|-------||
//           |             COM3|--------|
//           |                 |
//
//  L. Westlund / S. Karthikeyan
//  Texas Instruments Inc.
//  June 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.30A
//*****************************************************************************
#include  <msp430x42x0.h>


// LCD segment definitions.
#define d 0x80
#define c 0x40
#define b 0x20
#define a 0x10
#define h 0x08
#define e 0x04
#define g 0x02
#define f 0x01

const char char_gen[] = {                   // definitions for digits
  a+b+c+d+e+f,                              // Displays "0"
  b+c,                                      // Displays "1"
  a+b+d+e+g,                                // Displays "2"
  a+b+c+d+g,                                // Displays "3"
  b+c+f+g,                                  // Displays "4"
  a+c+d+f+g,                                // Displays "5"
  a+c+d+e+f+g,                              // Displays "6"
  a+b+c,                                    // Displays "7"
  a+b+c+d+e+f+g,                            // Displays "8"
  a+b+c+d+f+g                               // Displays "9"
};

void main(void)
{
  int i;
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  FLL_CTL0 |= XCAP14PF;                     // Set load cap for 32k xtal
  LCDACTL = LCDON + LCD4MUX + LCDFREQ_128;  // 4mux LCD, ACLK/128
  LCDAPCTL0 = 0x0F;                         // Segments 0-13

  P5SEL  = 0x1C;                            // Set COM pins for LCD

  for( i = 0; i < 20; i ++)
  {
    LCDMEM[i] = 0;                          // Clear LCD
  }

  for (i=0; i<7; ++i)                      // Display "0123456"
  {
    LCDMEM[i] = char_gen[i];
  }
  _BIS_SR(LPM3_bits);                      // Enter LPM3
}
