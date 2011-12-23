//******************************************************************************
//   MSP430F22x4 Demo - USCI_A0, SPI 3-Wire Master Incremented Data
//
//   Description: SPI master talks to SPI slave using 3-wire mode. Incrementing
//   data is sent by the master starting at 0x01. Received data is expected to
//   be same as the previous transmission.  USCI RX ISR is used to handle
//   communication with the CPU, normally in LPM0. If high, P1.0 indicates
//   valid data reception.
//   ACLK = n/a, MCLK = SMCLK = DCO ~1.2MHz, BRCLK = SMCLK/2
//
//   Use with SPI Slave Data Echo code example. If slave is in debug mode, P3.6
//   slave reset signal conflicts with slave's JTAG; to work around, use IAR's
//   "Release JTAG on Go" on slave device.  If breakpoints are set in
//   slave RX ISR, master must stopped also to avoid overrunning slave
//   RXBUF.
//
//                    MSP430F22x4
//                 -----------------
//             /|\|              XIN|-
//              | |                 |
//              --|RST          XOUT|-
//                |                 |
//                |             P3.4|-> Data Out (UCA0SIMO)
//                |                 |
//          LED <-|P1.0         P3.5|<- Data In (UCA0SOMI)
//                |                 |
//  Slave reset <-|P3.6         P3.0|-> Serial Clock Out (UCA0CLK)
//
//
//   A. Dannenberg
//   Texas Instruments Inc.
//   April 2006
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x22x4.h"

unsigned char MST_Data, SLV_Data;

void main(void)
{
  volatile unsigned int i;

  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P1OUT = 0x00;                             // P1 setup for LED
  P1DIR |= 0x01;                            //
  P3OUT = 0x40;                             // Set slave reset
  P3DIR |= 0x40;                            //
  P3SEL |= 0x31;                            // P3.0,4,5 USCI_A0 option select
  UCA0CTL0 |= UCCKPL + UCMSB + UCMST + UCSYNC;  // 3-pin, 8-bit SPI master
  UCA0CTL1 |= UCSSEL_2;                     // SMCLK
  UCA0BR0 |= 0x02;                          // /2
  UCA0BR1 = 0;                              //
  UCA0MCTL = 0;                             // No modulation
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  IE2 |= UCA0RXIE;                          // Enable USCI0 RX interrupt

  P3OUT &= ~0x40;                           // Now with SPI signals initialized,
  P3OUT |= 0x40;                            // reset slave

  for (i = 50; i > 0; i--);                 // Wait for slave to initialize

  MST_Data = 0x01;                          // Initialize data values
  SLV_Data = 0x00;

  UCA0TXBUF = MST_Data;                     // Transmit first character

  __bis_SR_register(LPM0_bits + GIE);       // CPU off, enable interrupts
}

// Test for valid RX and TX character
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCIA0RX_ISR(void)
{
  volatile unsigned int i;

  while (!(IFG2 & UCA0TXIFG));              // USCI_A0 TX buffer ready?

  if (UCA0RXBUF == SLV_Data)                // Test for correct character RX'd
    P1OUT |= 0x01;                          // If correct, light LED
  else
    P1OUT &= ~0x01;                         // If incorrect, clear LED

  MST_Data++;                               // Increment master value
  SLV_Data++;                               // Increment expected slave value
  UCA0TXBUF = MST_Data;                     // Send next value

  for (i = 30; i; i--);                     // Add time between transmissions to
}                                           // make sure slave can keep up

