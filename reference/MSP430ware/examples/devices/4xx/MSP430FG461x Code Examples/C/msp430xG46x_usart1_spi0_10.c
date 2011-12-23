//******************************************************************************
//   MSP430xG46x Demo - USART1, SPI 3-Wire Slave Data Echo
//
//   Description: SPI slave talks to SPI master using 3-wire mode. Data received
//   from master is echoed back.  USART1 RX ISR is used to handle communication,
//   CPU normally in LPM4.  Prior to initial data exchange, master pulses
//   slaves RST for complete reset.
//   ACLK = 32.768kHz, MCLK = SMCLK = DCO = ~1048kHz
//
//   Use with SPI Master Incremented Data code example.  If the slave is in
//   debug mode, the reset signal from the master will conflict with slave's
//   JTAG; to work around, use IAR's "Release JTAG on Go" on slave device.  If
//   breakpoints are set in slave RX ISR, master must stopped also to avoid
//   overrunning slave RXBUF.
//
//                MSP430xG461x
//             -----------------
//         /|\|              XIN|-
//          | |                 |   32kHz xtal
//          | |             XOUT|-
// Master---+-|RST              |
//            |             P4.3|<- Data In (SIMO1)
//            |                 |
//            |             P4.4|-> Data Out (SOMI1)
//            |                 |
//            |             P4.5|<- Serial Clock In (UCLK1)
//
//
//   K. Quiring/ M. Mitchell
//   Texas Instruments Inc.
//   March 2006
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include  <msp430xG46x.h>

void main(void)
{
  volatile unsigned int i;

  WDTCTL = WDTPW+WDTHOLD;                   // Stop watchdog timer
  FLL_CTL0 |= XCAP14PF;                     // Configure load caps

  // Wait for xtal to stabilize
  do
  {
  IFG1 &= ~OFIFG;                           // Clear OSCFault flag
  for (i = 0x47FF; i > 0; i--);             // Time for flag to set
  }
  while ((IFG1 & OFIFG));                   // OSCFault flag still set?

  for(i=2100;i>0;i--);                      // Now with stable ACLK, wait for
                                            // DCO to stabilize.
  while(!(P4IN&0x20));                      // If clock sig from mstr stays low,
                                            // it is not yet in SPI mode
  P4SEL |= 0x038;                           // P4.5,4,3 SPI option select
  U1CTL = CHAR+SYNC+SWRST;                  // 8-bit, SPI, Slave
  U1TCTL |= CKPL+STC;                       // Polarity, UCLK, 3-wire
  ME2 |= USPIE1;                            // Module enable
  U1CTL &= ~SWRST;                          // SPI enable
  IE2 |= URXIE1;                            // Receive interrupt enable

  _BIS_SR(LPM4_bits + GIE);                 // Enter LPM4, enable interrupts
}

// Echo character
#pragma vector=USART1RX_VECTOR
__interrupt void USART1RX_ISR (void)
{
  while (!(IFG2 & UTXIFG1));                // USART1 TX buffer ready?
  U1TXBUF = U1RXBUF;
}
