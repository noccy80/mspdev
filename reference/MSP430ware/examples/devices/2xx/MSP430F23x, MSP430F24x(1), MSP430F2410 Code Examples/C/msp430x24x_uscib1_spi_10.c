//******************************************************************************
//   MSP430F249 Demo - USCI_B1, SPI 3-Wire Slave Data Echo
//
//   Description: SPI slave talks to SPI master using 3-wire mode. Data received
//   from master is echoed back.  USCI RX ISR is used to handle communication,
//   CPU normally in LPM4.  Prior to initial data exchange, master pulses
//   slaves RST for complete reset.
//   ACLK = n/a, MCLK = SMCLK = DCO ~1.045Mhz
//
//   Use with SPI Master Incremented Data code example.  If the slave is in
//   debug mode, the reset signal from the master will conflict with slave's
//   JTAG; to work around, use IAR's "Release JTAG on Go" on slave device.  If
//   breakpoints are set in slave RX ISR, master must stopped also to avoid
//   overrunning slave RXBUF.
//
//                MSP430F249
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          | |             XOUT|-
// Master---+-|RST              |
//            |             P5.1|<- Data Out (UCB1SOMI)
//            |                 |
//            |             P5.2|-> Data In (UCB1SIMO)
//            |                 |
//            |             P5.3|<- Serial Clock In (UCB1CLK)
//
//  B. Nisarga
//  Texas Instruments Inc.
//  September 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//******************************************************************************
#include "msp430x24x.h" 

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  if (CALBC1_1MHZ ==0xFF || CALDCO_1MHZ == 0xFF)                                     
  {  
    while(1);                               // If calibration constants erased
                                            // do not load, trap CPU!!
  }   
  BCSCTL1 = CALBC1_1MHZ;                    // Set DCO to 1MHz
  DCOCTL = CALDCO_1MHZ;
 
  while (!(P5IN & BIT3));                   // If clock sig from mstr stays low,
                                            // it is not yet in SPI mode
  P5SEL |= 0x00E;                           // P5.1,2,3 USCI_B1 option select
  UCB1CTL1 = UCSWRST;                       // **Put state machine in reset**
  UCB1CTL0 |= UCCKPL + UCMSB + UCSYNC;      // 3-pin, 8-bit SPI master
  UCB1CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  UC1IE |= UCB1RXIE;                        // Enable USCI1 RX interrupt

  __bis_SR_register(LPM4_bits + GIE);       // Enter LPM4, enable interrupts
}

// Echo character
#pragma vector=USCIAB1RX_VECTOR
__interrupt void USCI1RX_ISR (void)
{
  while (!(UC1IFG & UCB1TXIFG));            // USCI_B1 TX buffer ready?
  UCB1TXBUF = UCB1RXBUF;
}
