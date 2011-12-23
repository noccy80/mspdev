//******************************************************************************
//   MSP430x24x Demo - USCI_A0, SPI Interface to HC164 Shift Register
//
//   Description: This program demonstrates USCI_A0 in SPI mode, interfaced to
//   a 'HC164 shift register' (Serial In, Parallel Out), transferring the value 
//   contained in Data.The value is incremented in the mainloop, effectively 
//   incrementing HC164 QA - QH.
//   ACLK = n/a, MCLK = SMCLK = default DCO ~1.045Mhz, BRCLK = SMCLK/2
//
//                MSP430F249
//             -----------------
//         /|\|              XIN|-
//          | |                 |        ^      HC164
//          --|RST          XOUT|-       |  -------------
//            |                 |        |-|/CLR,B       |  8
//            |    UCA0SIMO/P3.4|--------->|A          Qx|--\->
//            |     UCA0CLK/P3.0|--------->|CLK          |
//            |                 |          |             |
//
//  B. Nisarga
//  Texas Instruments Inc.
//  September 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//******************************************************************************
#include "msp430x24x.h"

unsigned char Data;
volatile unsigned int i;

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P3SEL |= 0x11;                            // P3.0,4 USCI_A0 option select
  UCA0CTL0 |= UCCKPH + UCMSB + UCMST + UCSYNC;  // 3-pin, 8-bit SPI master
  UCA0CTL1 |= UCSSEL_2;                     // SMCLK
  UCA0BR0 |= 0x02;
  UCA0BR1 = 0;
  UCA0MCTL = 0;
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**

  Data = 0x0FF;                             // Load inital data

  while(1)
  {
    Data++;                                 // Increment Data value - Set BREAKPOINT here
    while (!(IFG2 & UCA0TXIFG));            // USCI_A0 TX buffer ready?
    UCA0TXBUF = Data;                       // Byte to SPI TXBUF
    for(i = 0xFF; i > 0; i--);            // Delay
  }
}
