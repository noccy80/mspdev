//******************************************************************************
//  MSP-FET430P430 Demo - USART0, SPI Interface to HC165/164 Shift Registers
//
//  Description: Demonstrate USART0 in two-way SPI mode. Data are read from
//  an HC165, and same data written back to the HC164.
//  ACLK = n/a  MCLK = SMCLK = DCO ~ 1.048MHz,  UCLK0 = DCO/2
//  //**SWRST** please see MSP430x4xx Users Guide for description //
//  //*USART0 control bits are in different SFR's from MSP430F14x/13x/12x*//
//
//                          MSP430FG439
//                       -----------------
//                   /|\|              XIN|-
//                    | |                 |     ^      HC164
//          HC165     --|RST          XOUT|-    |  -------------
//        ----------    |                 |     |-|/CLR,B       |  8
//    8  |      /LD|<---|P3.0   P3.1/SIMO0|------>|A          Qx|--\->
//   -\->|A-H   CLK|<---|-- P3.3/UCLK0  --|------>|CLK          |
//     |-|INH    QH|--->|P3.2/SOMI0       |       |             |
//     |-|SER      |    |                 |       |             |
//     - |         |    |                 |       |             |
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//*****************************************************************************
#include  <msp430xG43x.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  ME1 |= USPIE0;                            // Enable USART0 SPI mode
  UCTL0 |= CHAR + SYNC + MM;                // 8-bit SPI Master **SWRST**
  UTCTL0 |= CKPH + SSEL1 + SSEL0 + STC;     // SMCLK, 3-pin mode
  UBR00 = 0x02;                             // UCLK/2
  UBR10 = 0x00;                             // 0
  UMCTL0 = 0x00;                            // no modulation
  UCTL0 &= ~SWRST;                          // Initalize USART state machine
  P3SEL |= 0x0E;                            // P3.1-3 SPI option select
  P3DIR |= 0x01;                            // P3.0 output direction

  while (1)
  {
    volatile unsigned int i;
    for (i = 0xFFFF; i > 0; i--);           // Delay
    while (!(IFG1 & UTXIFG0));              // USART0 TX buffer ready?
    P3OUT &= ~0x01;                         // Latch data into 'HC165
    P3OUT |= 0x01;
    TXBUF0 = RXBUF0;                        // RXBUF0 to TXBUF0
  }
}
