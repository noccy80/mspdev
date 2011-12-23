//******************************************************************************
//   MSP430F51x2 Demo - USCI_A0, SPI 3-Wire SLAVE Data Echo
//
//
//   Description: SPI slave talks to SPI master using 3-wire mode. Data received
//   from master is echoed back.  USCI RX ISR is used to handle communication,
//   CPU normally in LPM4.  Prior to initial data exchange, master pulses
//   slaves RST for complete reset.
//   ACLK = ~32.768kHz, MCLK = SMCLK = DCO ~ 1048kHz
//
//   Use with SPI Master Incremented Data code example.  If the slave is in
//   debug mode, the reset signal from the master will conflict with slave's
//   JTAG; to work around, use IAR's "Release JTAG on Go" on slave device.  If
//   breakpoints are set in slave RX ISR, master must stopped also to avoid
//   overrunning slave RXBUF.
//
//                   MSP430F51x2
//                 -----------------
//            /|\ |                 |
//             |  |                 |
//    Master---+->|RST              |
//                |                 |
//                |             P1.1|-> Data In (UCA0SIMO)
//                |                 |
//                |             P1.2|<- Data Out (UCA0SOMI)
//                |                 |
//                |             P1.0|-> Serial Clock In (UCA0CLK)
//
//
//  B. Nisarga
//  Texas Instruments Inc.
//  Dec 2009
//  Built with CCS v4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include "msp430f5172.h"

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop watchdog timer

  while(!(P1IN&0x01));                      // If clock sig from mstr stays low,
                                            // it is not yet in SPI mode
  P1SEL |= 0x07;                            // P1.0,1,2 option select USCI SPI pins

  UCA0CTL1 |= UCSWRST;                      // **Put state machine in reset**
  UCA0CTL0 |= UCSYNC+UCCKPL+UCMSB;          // 3-pin, 8-bit SPI slave,
                                            // Clock polarity high, MSB
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  UCA0IE |= UCRXIE;                         // Enable USCI_A0 RX interrupt

  __bis_SR_register(LPM4_bits + GIE);       // Enter LPM4, enable interrupts
}

// Echo character
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
{
  switch(__even_in_range(UCA0IV,4))
  {
    case 0:break;                             // Vector 0 - no interrupt
    case 2:                                   // Vector 2 - RXIFG
      while (!(UCA0IFG&UCTXIFG));             // USCI_A0 TX buffer ready?
      UCA0TXBUF = UCA0RXBUF;
      break;
    case 4:break;                             // Vector 4 - TXIFG
    default: break;
  }
}
