//******************************************************************************
//   MSP430x24x Demo - USCI_B0, SPI Interface to TLV1549 10-Bit ADC
//
//   Description: This program demonstrate USCI_B0 in SPI mode interfaced to a
//   TLV1549 10-bit ADC. If AnalogIN > 0.5(REF+ - REF-), P1.0 set, else reset.
//   R15 = MSB(8bits)|LSB(2bits), left justified.  R14 also used and not saved.
//   R12 has the 10bit digital result of the TLV1549 as "data"
//   ACLK = n/a, MCLK = SMCLK = DCO ~1.045Mhz, BRCLK = SMCLK/2
//   //* VCC must be at least 3v for TLV1549 *//
//
//                         MSP430F249
//                       -----------------
//                   /|\|              XIN|-
//       TLV1549      | |                 |
//    -------------   --|RST          XOUT|-
//   |           CS|<---|P3.0             |
//   |      DATAOUT|--->|P3.2/UCB0SOMI    |
// ~>|AIN+  I/O CLK|<---|P3.3/UCB0CLK     |
//   |             |    |             P1.0|--> LED
//
//  B. Nisarga
//  Texas Instruments Inc.
//  September 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//******************************************************************************
#include "msp430x24x.h"

void main(void)
{
  unsigned int data1, data2, data;

  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P1DIR |= 0x01;                            // P1.0 output
  P3SEL |= 0x0C;                            // P3.2,3 USCI_B0 option select
  P3DIR |= 0x01;                            // P3.0 output direction
  UCB0CTL0 |= UCMSB + UCMST + UCSYNC;       // 3-pin, 8-bit SPI mstr, MSB 1st
  UCB0CTL1 |= UCSSEL_2;                     // SMCLK
  UCB0BR0 = 0x02;
  UCB0BR1 = 0;
  UCB0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**

  while(1)
  {
    P3OUT &= ~0x01;                         // Enable TLV1549, /CS reset
    UCB0TXBUF = 0x00;                       // Dummy write to start SPI
    UCB0TXBUF = 0x00;                       // tx twice-receive 2 bytes
    
    while (!(IFG2 & UCB0RXIFG));            // RXBUF ready?, data received??
    data1 = UCB0RXBUF;                      // R15 = 00|MSB - Q9-Q2
    data1 = data1 << 8;
 
    while (!(IFG2 & UCB0RXIFG));            // RXBUF ready?, data received??
    data2 = UCB0RXBUF;
    data1 = data1 + data2;                  // R14 = 00|LSB - Q1-Q0
    
    // (2^10 - 1) = (REF+ - REF-)    
    data = data1 >> 6;                      // 10bit digital value in R12
    
    P3OUT |= 0x01;                          // Disable TLV1549, /CS set
    P1OUT &= ~0x01;                         // P1.0 = 0

    if (data > 0x1FF)                     // Test for correct character RX'd
      P1OUT |= 0x01;                        // P1.0 = 1
  }
}
