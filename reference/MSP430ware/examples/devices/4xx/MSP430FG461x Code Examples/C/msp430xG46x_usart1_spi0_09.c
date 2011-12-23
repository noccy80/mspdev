//******************************************************************************
//   MSP430xG46x Demo - USART1, SPI 3-Wire Master Incremented Data
//
//   Description: SPI master talks to SPI slave using 3-wire mode.  Incrementing
//   data is sent by the master starting at 0x01.  Received data is expected to
//   be same as the previous transmission.  USART1 RX ISR is used to handle
//   communication with the CPU, normally in LPM0.  If high, P5.1 indicates
//   valid data reception.  Because all execution after LPM0 is in ISRs,
//   initialization waits for DCO to stabilize against ACLK before entering
//   LPM0.  ACLK = 32.768kHz, MCLK = SMCLK = DCO ~ 1048kHz
//
//   Use with SPI Slave Data Echo code example.  If slave is in debug mode, P5.2
//   slave reset signal conflicts with slave's JTAG; to work around, use IAR's
//   "Release JTAG on Go" on slave device.  If breakpoints are set in
//   slave RX ISR, master must be stopped also to avoid overrunning slave
//   RXBUF.
//
//                    MSP430xG461x
//                 -----------------
//             /|\|              XIN|-
//              | |                 |  32kHz xtal
//              --|RST          XOUT|-
//                |                 |
//                |             P4.3|-> Data Out (SIMO1)
//                |                 |
//          LED <-|P5.1         P4.4|<- Data In (SOMI1)
//                |                 |
//  Slave reset <-|P5.2         P4.5|-> Serial Clock Out (UCLK1)
//
//
//   K. Quiring/ M. Mitchell
//   Texas Instruments Inc.
//   March 2006
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include  <msp430xG46x.h>

unsigned char MST_Data,SLV_Data;

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
  P5OUT = 0x04;                             // P5 setup for LED and slave reset
  P5DIR |= 0x06;                            //
  P4SEL |= 0x038;                           // P4.5,4,3 SPI option select
  U1CTL = CHAR+SYNC+MM+SWRST;               // 8-bit, SPI, Master
  U1TCTL |= CKPL+SSEL1+STC;                 // Polarity, SMCLK, 3-wire
  U1BR0 = 0x002;                            // SPICLK = SMCLK/2
  U1BR1 = 0x000;                            //
  U1MCTL = 0x000;                           //
  ME2 |= USPIE1;                            // Module enable
  U1CTL &= ~SWRST;                          // SPI enable
  IE2 |= URXIE1;                            // Receive interrupt enable

  P5OUT &= ~0x04;                           // Now with SPI signals initialized,
  P5OUT |= 0x04;                            // reset slave

  for(i=50;i>0;i--);                        // Wait for slave to initialize

  MST_Data = 0x001;                         // Initialize data values
  SLV_Data = 0x000;                         //
  U1TXBUF = MST_Data;                       // Transmit first character

  _BIS_SR(LPM0_bits + GIE);                 // CPU off, enable interrupts
}


#pragma vector=USART1RX_VECTOR
__interrupt void USART1_rx (void)
{
  volatile unsigned int i;

  while (!(IFG2 & UTXIFG1));                // USART1 TX buffer ready?
  if (U1RXBUF==SLV_Data)                    // Test for correct character RX'd
    P5OUT |= 0x02;                          // If correct, light LED
  else
    P5OUT &= ~0x02;                         // If incorrect, clear LED

  MST_Data++;
  SLV_Data++;
  U1TXBUF = MST_Data;                       // Send next value

  for(i=30;i>0;i--);                        // Add time between transmissions to
}                                           // make sure slave can keep up
