//******************************************************************************
//   MSP430x471xx Demo - USCI_B0, SPI Interface to TLC549 8-Bit ADC
//
//   Description: This program demonstrate USCI_A1 in SPI mode interfaced to a
//   TLC549 8-bit ADC. If AIN > 0.5(REF+ - REF-), P5.1 set, else reset.
//   R15 = 8-bit ADC code.
//   ACLK = 32.768kHz, MCLK = SMCLK = default DCO ~1048k, BRCLK = SMCLK/2
//   //* VCC must be at least 3v for TLC549 *//
//
//                           MSP430x471xx
//                       -----------------
//                   /|\|              XIN|-
//        TLC549      | |                 |   32kHz
//    -------------   --|RST          XOUT|-
//   |           CS|<---|P3.0             |
//   |      DATAOUT|--->|P3.2/UCB0SOMI    |
// ~>| IN+  I/O CLK|<---|P3.3/UCB0CLK     |
//   |             |    |             P5.1|--> LED
//
//   K. Venkat
//   Texas Instruments Inc.
//   May 2009
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************
#include  "msp430x471x7.h"

void main(void)
{
  volatile unsigned int i;
  char data;

  WDTCTL = WDTPW+WDTHOLD;                   // Stop watchdog timer
  FLL_CTL0 |= XCAP14PF;                     // Configure load caps

  // Wait for xtal to stabilize
  do
  {
  IFG1 &= ~OFIFG;                           // Clear OSCFault flag
  for (i = 0x47FF; i > 0; i--);             // Time for flag to set
  }
  while ((IFG1 & OFIFG));                   // OSCFault flag still set?

  P5DIR |= BIT1;                            // P5.1 output
  P3SEL |= BIT3+BIT2;                       // P3.3,2 option select
  P3DIR |= BIT0;                            // P3.0 output direction
  UCB0CTL0 |= UCMST+UCSYNC+UCMSB;           // 3-pin, 8-bit SPI mstr, MSb 1st
  UCB0CTL1 |= UCSSEL_2;                     // SMCLK
  UCB0BR0 = 0x02;
  UCB0BR1 = 0;
  UCB0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**

  while(1)
  {
    P3OUT &= ~BIT0;                         // Enable TLC549, /CS reset
    UCB0TXBUF = 0x00;                       // Dummy write to start SPI
    while (!(IFG2 & UCB0RXIFG));            // USCI_B0 RX buffer ready?

    data = UCB0RXBUF;                       // data = 00|DATA

    P3OUT |= BIT0;                          // Disable TLC549, /CS set
    P5OUT &= ~BIT1;                         // P5.1 = 0

    if(data>=0x7F)                          // data = AIN > 0.5(REF+ - REF-)?
      P5OUT |= BIT1;                        // P5.1 = 1
  }
}
