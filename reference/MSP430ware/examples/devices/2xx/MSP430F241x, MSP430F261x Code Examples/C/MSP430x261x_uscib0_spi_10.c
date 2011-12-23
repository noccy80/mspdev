//******************************************************************************
//   msp430x26x Demo - USCI_B0, SPI 3-Wire Slave Data Echo
//
//   Description: SPI slave talks to SPI master using 3-wire mode. Data received
//   from master is echoed back.  USCI RX ISR is used to handle communication,
//   CPU normally in LPM4.  Prior to initial data exchange, master pulses
//   slaves RST for complete reset.
//   ACLK = n/a, MCLK = SMCLK = DCO ~ 1048kHz
//
//   Use with SPI Master Incremented Data code example.  If the slave is in
//   debug mode, the reset signal from the master will conflict with slave's
//   JTAG; to work around, use IAR's "Release JTAG on Go" on slave device.  If
//   breakpoints are set in slave RX ISR, master must stopped also to avoid
//   overrunning slave RXBUF.
//
//                MSP430F261x/241x
//             -----------------
//         /|\|              XIN|-
//          | |                 |   
//          | |             XOUT|-
// Master---+-|RST              |
//            |             P3.1|<- Data In (UCB0SIMO)
//            |                 |
//            |             P3.2|-> Data Out (UCB0SOMI)
//            |                 |
//            |             P3.3|<- Serial Clock In (UCB0CLK)
//
//
//  B. Nisarga
//  Texas Instruments Inc.
//  September 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//******************************************************************************
#include  <msp430x26x.h>

void main(void)
{
  volatile unsigned int i;

  WDTCTL = WDTPW+WDTHOLD;                   // Stop watchdog timer
  if (CALBC1_1MHZ ==0xFF || CALDCO_1MHZ == 0xFF)                                     
  {  
    while(1);                               // If calibration constants erased
                                            // do not load, trap CPU!!
  }    
  BCSCTL1 = CALBC1_1MHZ;                    // Set DCO to 1MHz
  DCOCTL = CALDCO_1MHZ;

  while(!(P3IN&0x08));                      // If clock sig from mstr stays low,
                                            // it is not yet in SPI mode
  P3SEL |= 0x0E;                            // P3.3,2,1 option select
  UCB0CTL1 = UCSWRST;                       // **Put state machine in reset**
  UCB0CTL0 |= UCSYNC+UCCKPL+UCMSB;          //3-pin, 8-bit SPI master
  UCB0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  IE2 |= UCB0RXIE;                          // Enable USCI_B0 RX interrupt

  _BIS_SR(LPM3_bits + GIE);                 // Enter LPM4, enable interrupts
}

// Echo character
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCIB0RX_ISR (void)
{
  while (!(IFG2 & UCB0TXIFG));              // USCI_B0 TX buffer ready?
  UCB0TXBUF = UCB0RXBUF;
}
