//******************************************************************************
//   msp430x26x Demo - USCI_B0, SPI 3-Wire Master Incremented Data
//
//   Description: SPI master talks to SPI slave using 3-wire mode. Incrementing
//   data is sent by the master starting at 0x01. Received data is expected to
//   be same as the previous transmission.  USCI RX ISR is used to handle
//   communication with the CPU, normally in LPM0. If high, P1.0 indicates
//   valid data reception.  Because all execution after LPM0 is in ISRs,
//   initialization waits for DCO to stabilize against ACLK.
//   ACLK = n/a, MCLK = SMCLK = DCO ~ 1048kHz.  BRCLK = SMCLK/2
//
//   Use with SPI Slave Data Echo code example.  If slave is in debug mode, P1.1
//   slave reset signal conflicts with slave's JTAG; to work around, use IAR's
//   "Release JTAG on Go" on slave device.  If breakpoints are set in
//   slave RX ISR, master must stopped also to avoid overrunning slave
//   RXBUF.
//
//                    MSP430F261x/241x
//                 -----------------
//             /|\|              XIN|-
//              | |                 |  
//              --|RST          XOUT|-
//                |                 |
//                |             P3.1|-> Data Out (UCB0SIMO)
//                |                 |
//          LED <-|P1.0         P3.2|<- Data In (UCB0SOMI)
//                |                 |
//  Slave reset <-|P1.1         P3.3|-> Serial Clock Out (UCB0CLK)
//
//
//  B. Nisarga
//  Texas Instruments Inc.
//  September 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//******************************************************************************
#include  <msp430x26x.h>

unsigned char MST_Data,SLV_Data;

void main(void)
{
  volatile unsigned int i;

  WDTCTL = WDTPW+WDTHOLD;                   // Stop watchdog timer
  if (CALBC1_1MHZ ==0xFF || CALDCO_1MHZ == 0xFF)                                     
  {  
    while(1);                               // If calibration constants erased
                                            // do not load, trap CPU!!
  }    
  BCSCTL1 = CALBC1_1MHZ;                    // Set DCO
  DCOCTL = CALDCO_1MHZ;
  for(i=2100;i>0;i--);                      // Wait for DCO to stabilize.
                                       
  P1OUT |= 0x02;                             // P1 setup for LED and slave reset
  P1DIR |= 0x03;                            //
  P3SEL |= 0x0E;                            // P3.3,2,1 option select
  UCB0CTL0 |= UCMST+UCSYNC+UCCKPL+UCMSB;    //3-pin, 8-bit SPI master
  UCB0CTL1 |= UCSSEL_2;                     // SMCLK
  UCB0BR0 = 0x02;                           // /2
  UCB0BR1 = 0;                              //
  UCB0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  IE2 |= UCB0RXIE;                          // Enable USCI_A0 RX interrupt

  P1OUT &= ~0x02;                           // Now with SPI signals initialized,
  P1OUT |= 0x02;                            // reset slave

  for(i=50;i>0;i--);                        // Wait for slave to initialize

  MST_Data = 0x001;                         // Initialize data values
  SLV_Data = 0x000;                         //

  UCB0TXBUF = MST_Data;                     // Transmit first character

  _BIS_SR(LPM0_bits + GIE);                 // CPU off, enable interrupts
}

#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCIA0RX_ISR (void)
{
  volatile unsigned int i;

  while (!(IFG2 & UCB0TXIFG));              // USCI_B0 TX buffer ready?
  if (UCB0RXBUF==SLV_Data)                  // Test for correct character RX'd
    P1OUT |= 0x01;                          // If correct, light LED
  else
    P1OUT &= ~0x01;                         // If incorrect, clear LED

  MST_Data++;                               // Increment data
  SLV_Data++;
  UCB0TXBUF = MST_Data;                     // Send next value; "TX/RX of master happens here"

  for(i=30;i>0;i--);                        // Add time between transmissions to
}                                           // make sure slave can keep up
