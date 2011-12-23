//******************************************************************************
//   MSP430x41x2 Demo - USCI_A0, SPI 3-Wire Master Incremented Data
//
//   Description: SPI master talks to SPI slave using 3-wire mode. Incrementing
//   data is sent by the master starting at 0x01. Received data is expected to
//   be same as the previous transmission.  USCI RX ISR is used to handle
//   communication with the CPU, normally in LPM0. If high, P5.1 indicates
//   valid data reception.  Because all execution after LPM0 is in ISRs,
//   initialization waits for DCO to stabilize against ACLK.
//   ACLK = 32.768kHz, MCLK = SMCLK = DCO ~ 1048kHz.  BRCLK = SMCLK/2
//
//   Use with SPI Slave Data Echo code example.  
//
//                    MSP430F41x2
//                 -----------------
//             /|\|              XIN|-
//              | |                 |  32kHz xtal
//              --|RST          XOUT|-
//                |                 |
//                |             P6.6|-> Data Out (UCA0SIMO)
//                |                 |
//          LED <-|P5.1         P6.5|<- Data In (UCA0SOMI)
//                |                 |
//  Slave reset <-|P1.1         P6.3|-> Serial Clock Out (UCA0CLK)
//
//
//  P. Thanigai
//  Texas Instruments Inc.
//  January 2009
//  Built with CCE Version: 3.1 and IAR Embedded Workbench Version: 4.11
//******************************************************************************
#include  <msp430x41x2.h>

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
  
  P1OUT |= 0x02;                            // P1 setup for slave reset
  P1DIR |= 0x02;                            //
  P5OUT |= 0x02;                            // P5 setup for LED
  P5DIR |= 0x02;                            //
  P6SEL |= BIT3 + BIT5 + BIT6;              // P6.5,6,3 option select
  UCA0CTL0 |= UCMST+UCSYNC+UCCKPL+UCMSB;    //3-pin, 8-bit SPI master
  UCA0CTL1 |= UCSSEL_2;                     // SMCLK
  UCA0BR0 = 0x02;                           // /2
  UCA0BR1 = 0;                              //
  UCA0MCTL = 0;                             // No modulation
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  IE2 |= UCA0RXIE;                          // Enable USCI_A0 RX interrupt

  P1OUT &= ~0x02;                           // Now with SPI signals initialized,
  P1OUT |= 0x02;                            // reset slave

  for(i=50;i>0;i--);                        // Wait for slave to initialize

  MST_Data = 0x001;                         // Initialize data values
  SLV_Data = 0x000;                         //

  UCA0TXBUF = MST_Data;                     // Transmit first character

  _BIS_SR(LPM0_bits + GIE);                 // CPU off, enable interrupts
}

#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCIA0RX_ISR (void)
{
  volatile unsigned int i;

  while (!(IFG2 & UCA0TXIFG));              // USART1 TX buffer ready?
  if (UCA0RXBUF==SLV_Data)                  // Test for correct character RX'd
    P5OUT |= 0x02;                          // If correct, light LED
  else
    P5OUT &= ~0x02;                         // If incorrect, clear LED

  MST_Data++;                               // Increment data
  SLV_Data++;
  UCA0TXBUF = MST_Data;                     // Send next value

  for(i=30;i>0;i--);                        // Add time between transmissions to
}                                           // make sure slave can keep up
