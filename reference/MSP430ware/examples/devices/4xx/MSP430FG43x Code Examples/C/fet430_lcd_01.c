//******************************************************************************
//  MSP-FET430P430 Demo - LCD, Display "0123456" on SBLCDA4 LCD
//
//  Description: Displays "0123456" on SBLCDA4 LCD as used on 430 Day Watch
//  board.
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//	
//	
//               MSP430FG439
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32kHz
//         --|RST          XOUT|-
//           |                 |      SBLCDA4
//           |                 |      (As used on 430 Day Watch Demo board)
//         +-|R33          S0  |     -----------------
//        1m |              -  |--> | + 7 6 5 4 3 2 1 |
//         +-|R23          S21 |     -----------------
//        1m |             COM0|-----||||
//         +-|R13          COM1|------|||
//        1m |             COM2|-------||
//         +-|R03          COM3|--------|
//         | |                 |
//        Vss
//
//  L. Westlund
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************
#include  <msp430xG43x.h>

// LCD segment definitions.
#define d 0x80
#define c 0x40
#define b 0x20
#define a 0x10
#define h 0x08
#define e 0x04
#define g 0x02
#define f 0x01

const char char_gen[] = {               // As used in 430 Day Watch Demo board
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

void main(void)
{
  int i;
  WDTCTL = WDTPW + WDTHOLD;             // Stop watchdog timer
  FLL_CTL0 |= XCAP18PF;                 // Set load capacitance for xtal  
  LCDCTL = LCDON + LCDSG0_3 + LCD4MUX;  // 4mux LCD, segs0-23 = outputs
  BTCTL = BT_fLCD_DIV128;               // Set LCD frame freq = ACLK/128
  P5SEL  = 0xFC;                        // Set Rxx and COM pins for LCD
                                        // For P5.0, P5.1, P4.6, P4.7 setting
                                        // SEL bits selects Analog for the FG

  for( i = 0; i < 20; i ++)
  {
    LCDMEM[i] = 0;                      // Clear LCD
  }

  for (;;)
  {
    for (i=0; i<7; ++i)                 // Display "0123456"
      LCDMEM[i] = char_gen[i];
  }

}
