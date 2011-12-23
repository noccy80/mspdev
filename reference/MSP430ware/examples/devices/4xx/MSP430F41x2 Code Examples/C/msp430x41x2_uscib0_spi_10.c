//******************************************************************************
//   msp430x41x2 Demo - USCI_B0, SPI 3-Wire Slave Data Echo
//
//   Description: SPI slave talks to SPI master using 3-wire mode. Data received
//   from master is echoed back.  USCI RX ISR is used to handle communication,
//   CPU normally in LPM4.  Prior to initial data exchange, master pulses
//   slaves RST for complete reset.
//   ACLK = n/a, MCLK = SMCLK = DCO ~ 1048kHz
//
//   Use with SPI Master Incremented Data code example.  
//
//                MSP430F41x2
//             -----------------
//         /|\|              XIN|-
//          | |                 |   
//          | |             XOUT|-
// Master---+-|RST              |
//            |             P6.2|<- Data In (UCB0SIMO)
//            |                 |
//            |             P6.1|-> Data Out (UCB0SOMI)
//            |                 |
//            |             P6.4|<- Serial Clock In (UCB0CLK)
//
//
//  P. Thanigai
//  Texas Instruments Inc.
//  January 2009
//  Built with CCE Version: 3.1 and IAR Embedded Workbench Version: 4.11
//******************************************************************************
#include  <msp430x41x2.h>

void main(void)
{
  volatile unsigned int i;

  WDTCTL = WDTPW+WDTHOLD;                   // Stop watchdog timer

  while(!(P6IN&0x10));                      // If clock sig from mstr stays low,
                                            // it is not yet in SPI mode
  P6SEL |= BIT1 + BIT2 + BIT4;              // P6.1,2,4 option select
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
