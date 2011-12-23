//******************************************************************************
//  MSP430x11x1 Demo - Software SPI Interface TLC549, Set P1.0 if > 0.5*Vcc
//
//  Description: Read a TLC549 ADC with reference to Vcc using software SPI and
//  store the 8-bit digital code in ADCData.  The TLC549 is sampled in a
//  continous loop. If ADCData > 0.5*Vcc, P1.0 set, else reset.
//  ACLK = n/a. MCLK = SMCLK = default DCO ~800k
//  //* VCC must be at least 3v for TLC549 *//
//
//                       MSP430F1121
//                    -----------------
//                /|\|              XIN|-
//                 | |                 |
//                 --|RST          XOUT|-
//      TLC549       |                 |
//    ----------     |                 |
//   |        CS|<---|P2.0         P1.0|-->LED
// ~>| AIN+  CLK|<---|P2.1             |
//   |        DO|--->|P2.3             |
//
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************

#include <msp430x11x1.h>

#define CS              0x01                // P2.0 - Chip Select
#define CLK             0x02                // P2.1 - Clock
#define DO              0x08                // P2.3 - Data Out

void main (void)
{
  unsigned char ADCData;
  unsigned char Counter;
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P2OUT = CS;                               // /CS set, - P2.x reset
  P2DIR |= CLK + CS;                        // /CS and CLK outputs
  P1DIR |= 0x01;                            // Set P1.0 to output direction

  for (;;)                                  // Infinite loop
  {
  P2OUT &= ~CS;                             // /CS reset, enable ADC
  for (Counter = 8; Counter > 0;)
    {
    ADCData = ADCData  << 1;
      if ((P2IN & DO) == DO)
      {
      ADCData |= 0x01;
      }
    Counter --;
    P2OUT |= CLK;                           // Clock high
    P2OUT &= ~CLK;                          // Clock low
    }
  P2OUT |= CS;                              // /CS set, disable ADC
    if (ADCData < 0x7F)
    {
    P1OUT &= ~0x01;                         // Clear P1.0 LED off
    }
    else
    {
    P1OUT |= 0x01;                          // Set P1.0 LED on
    }
  }
}

