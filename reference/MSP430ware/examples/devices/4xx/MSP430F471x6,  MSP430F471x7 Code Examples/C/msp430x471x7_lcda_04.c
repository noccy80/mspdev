//******************************************************************************
//    MSP430x471xx Demo - LCD_A Put "0123456" on SBLCDA4 LCD
//
//  Description; Put "0123456" on SBLCDA4 LCD.
//  ACLK = LFXT1 = 32768, MCLK = SMCLK = DCO = 32xACLK = 1.048576MHz
//  //*An external watch crystal is required on XIN/XOUT for ACLK*//	
//
//                MSP430x471xx
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32kHz
//         --|RST          XOUT|-         SBLCDA4 
//           |                 |        ___________
//           |              S0 |------>|14         |
//           |              S1 |------>|13         | 
//           |             ..  | ....  |..         |
//           |             S13 |------>|1          | 
//           |             COM0|------>|15         |
//           |             COM1|------>|16         | 
//           |             COM2|------>|17         | 
//           |             COM3|------>|18         |
//           |             S14 |------>|19         | 
//           |             S15 |------>|20         | 
//           |              .. | ....  |..         | 
//           |             S21 |------>|26         |     
//           |_________________|       |___________| 
//
//
//   K. Venkat
//   Texas Instruments Inc.
//   May 2009
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************
#include <msp430x471x7.h>

// LCD segment definitions.
#define h 0x80
#define e 0x40
#define g 0x20
#define f 0x10
#define d 0x08
#define c 0x04
#define b 0x02
#define a 0x01

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
  volatile unsigned int i;

  WDTCTL = WDTPW +WDTHOLD;                  // Stop WDT
  FLL_CTL0 |= XCAP14PF;                     // Configure load caps

  // Wait for xtal to stabilize
  do
  {
    IFG1 &= ~OFIFG;                         // Clear OSCFault flag
    for (i = 0x47FF; i > 0; i--);           // Time for flag to set
  }
  while ((IFG1 & OFIFG));                   // OSCFault flag still set?
  
  P5SEL =BIT1+BIT2+BIT3+BIT4;               // Set COM pins for LCD
  LCDACTL = LCDON+LCD4MUX;                  // 4mux LCD, ACLK/32
  LCDAPCTL0 = 0x7F;                         // Segments 0-24
  for( i = 0; i < 20; i ++)
  {
    LCDMEM[i] = 0;                          // Clear LCD
  }

  for (i=0;i<7;i++)
  {
    LCDMEM[i] = char_gen[i];
  }
  _BIS_SR(LPM3_bits);                       // Enter LPM3

}

