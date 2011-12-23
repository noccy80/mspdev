//******************************************************************************
//  MSP-FET430P430 Demo - LCD, Display "430" on Varitronix VI-322 LCD
//
//  Description: Displays "430" on Varitronix VI-322 LCD as used on
//  Softbaugh D437 board.
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//	
//	
//               MSP430FG439
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32kHz
//         --|RST          XOUT|-
//           |                 |      Varitronix VI-322
//           |                 |     (As used on Softbaugh D437 board)
//           |             S0  |     ---------
//           |              -  |--> | + 3 2 1 |
//           |             S31 |     ---------
//           |             COM0|-----|
//           |                 |
//           |                 |
//           |                 |
//           |                 |
//
//
//  L. Westlund / H. Grewal
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************
#include  <msp430xG43x.h>

#define a 0x001
#define b 0x010
#define c 0x002
#define d 0x020
#define e 0x004
#define f 0x040
#define g 0x008
#define h 0x080

const char digit[10] = {                // As used on Softbaugh D437 board
  a+b+c+d+e+f,                          // Displays "0"
  b+c,                                  // Displays "1"
  a+b+d+e+g,                            // Displays "2"
  a+b+c+d+g,                            // Displays "3"
  b+c+f+g,                              // Displays "4"
  a+c+d+f+g,                            // Displays "5"
  a+c+d+e+f+g,                          // Displays "6"
  a+b+c,                                // Displays "7"
  a+b+c+d+e+f+g,                        // Displays "8"
  a+b+c+d+f+g                           // Displays "9"
};

int toDisplay = 0x430;

void main(void)
{
  int i;
  WDTCTL = WDTPW + WDTHOLD;             // Stop watchdog timer
  FLL_CTL0 |= XCAP18PF;                 // Configure load caps
  LCDCTL = LCDON + LCDSTATIC + LCDOGOFF;// STK LCD 4Mux, S0-S17
  BTCTL = BTFRFQ1+BTFRFQ0;              // STK LCD freq
  P5SEL = 0xFC;                         // Common and Rxx all selected
                                        // For P5.0, P5.1, P4.6, P4.7 setting
                                        // SEL bits selects Analog for the FG

  for( i = 0; i < 20; i ++)
  {
    LCDMEM[i] = 0;                      // Clear LCD
  }

  for (;;)
  {
    int data;                           // LCD display Data

    data = digit[toDisplay&0x0F];       // get the LCD data for 1st digit
    LCDMEM[0] = data;                   // write data to LCD Memory...
    data = data>>1;                     // shift data for next location...
    LCDMEM[1] = data;
    data = data>>1;
    LCDMEM[2] = data;
    data = data>>1;
    LCDMEM[3] = data;

    data = digit[(toDisplay>>4)&0x0F];  // get the LCD data for 2nd digit
    LCDMEM[4] = data;                   // write data to LCD Memory...
    data = data>>1;                     // shift data for next location...
    LCDMEM[5] = data;
    data = data>>1;
    LCDMEM[6] = data;
    data = data>>1;
    LCDMEM[7] = data;
                                        // skip two for this LCD
    data = digit[(toDisplay>>8)&0x0F];  // get the LCD data for 3rd digit
    LCDMEM[10] = data;                  // write data to LCD Memory...
    data = data>>1;                     // shift data for next location...
    LCDMEM[11] = data;
    data = data>>1;
    LCDMEM[12] = data;
    data = data>>1;
    LCDMEM[13] = data;

  }
}
