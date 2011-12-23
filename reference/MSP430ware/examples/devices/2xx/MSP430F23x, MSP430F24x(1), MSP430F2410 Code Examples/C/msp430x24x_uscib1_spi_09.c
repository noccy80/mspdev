//******************************************************************************
//   MSP430x24x Demo - USCI_B1, SPI 3-Wire Master Incremented Data
//
//   Description: SPI master talks to SPI slave using 3-wire mode. Incrementing
//   data is sent by the master starting at 0x01. Received data is expected to
//   be same as the previous transmission.  USCI RX ISR is used to handle
//   communication with the CPU, normally in LPM0. If high, P1.0 indicates
//   valid data reception.
//   ACLK = n/a, MCLK = SMCLK = DCO ~1.045Mhz, BRCLK = SMCLK/2
//
//   Use with SPI Slave Data Echo code example. If slave is in debug mode, P3.5
//   slave reset signal conflicts with slave's JTAG; to work around, use IAR's
//   "Release JTAG on Go" on slave device. If breakpoints are set in
//   slave RX ISR, master must stopped also to avoid overrunning slave
//   RXBUF.
//                    MSP430F249
//                 -----------------
//             /|\|              XIN|-
//              | |                 |
//              --|RST          XOUT|-
//                |                 |
//                |             P5.1|-> Data Out (UCB1SIMO)
//                |                 |
//          LED <-|P1.0         P5.2|<- Data In (UCB1SOMI)
//                |                 |
//  Slave reset <-|P3.5         P5.3|-> Serial Clock Out (UCB1CLK)
//
//  B. Nisarga
//  Texas Instruments Inc.
//  September 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//******************************************************************************
#include "msp430x24x.h"

unsigned char MST_Data, SLV_Data;

void main(void)
{
  volatile unsigned int i;

  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  if (CALBC1_1MHZ ==0xFF || CALDCO_1MHZ == 0xFF)                                     
  {  
    while(1);                               // If calibration constants erased
                                            // do not load, trap CPU!!
  }   
  BCSCTL1 = CALBC1_1MHZ;                    // Set DCO
  DCOCTL = CALDCO_1MHZ;
  for(i=2100;i>0;i--);                      // Wait for DCO to stabilize.
  
  P1OUT = 0x00;                             // P1 setup for LED
  P1DIR |= 0x01;                            //
  P3OUT = 0x20;                             // Set slave reset - P3.5
  P3DIR |= 0x20;                            // 
  P5SEL |= 0x0E;                            // P5.1,2,3 USCI_B1 option select
  
  UCB1CTL0 |= UCCKPL + UCMSB + UCMST + UCSYNC;  // 3-pin, 8-bit SPI master
  UCB1CTL1 |= UCSSEL_2;                     // SMCLK
  UCB1BR0 |= 0x02;                          // BRCLK = SMCLK/2
  UCB1BR1 = 0;                              //
  UCB1CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  UC1IE |= UCB1RXIE;                        // Enable USCI1 RX interrupt

  P3OUT &= ~0x20;                           // reset slave - RST - active low
  P3OUT |= 0x20;                            // Now with SPI signals initialized,

  for (i = 50; i > 0; i--);                 // Wait for slave to initialize

  MST_Data = 0x01;                          // Initialize data values
  SLV_Data = 0x00;

  UCB1TXBUF = MST_Data;                     // Tx(01) and Rx (00) - first char

  __bis_SR_register(LPM0_bits + GIE);       // CPU off, enable interrupts
}

// Test for valid RX and TX character
#pragma vector=USCIAB1RX_VECTOR
__interrupt void USCIB1RX_ISR(void)
{
  volatile unsigned int i;

  while (!(UC1IFG & UCB1TXIFG));            // USCI_B1 TX buffer ready?
  
  if (UCB1RXBUF == SLV_Data)                // Test for correct character RX'd
    P1OUT |= 0x01;                          // If correct, light LED
  else
    P1OUT &= ~0x01;                         // If incorrect, clear LED

  MST_Data++;                               // Increment master value
  SLV_Data++;                               // Increment expected slave value
  UCB1TXBUF = MST_Data;                     // Send next value (Tx and Rx)

  for (i = 30; i; i--);                     // Add time between transmissions to
}                                           // make sure slave can keep up

