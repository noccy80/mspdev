//******************************************************************************
//   MSP430F51x2 Demo - USCI_A0, SPI 3-Wire MASTER Incremented Data
//
//   Description: SPI master talks to SPI slave using 3-wire mode. Incrementing
//   data is sent by the master starting at 0x01. Received data is expected to
//   be same as the previous transmission.  USCI RX ISR is used to handle
//   communication with the CPU, normally in LPM0. If high, P1.5 indicates
//   valid data reception.  Because all execution after LPM0 is in ISRs,
//   initialization waits for DCO to stabilize against ACLK.
//   ACLK = ~32.768kHz, MCLK = SMCLK = DCO ~ 1048kHz.  BRCLK = SMCLK/2
//
//
//                   MSP430F51x2
//                 -----------------
//             /|\|                 |
//              | |                 |
//              --|RST          P1.4|-> GPIO output; 'high'=> valid data reception
//                |                 |
//                |             P1.1|-> Data Out (UCA0SIMO)
//                |                 |
//                |             P1.2|<- Data In (UCA0SOMI)
//                |                 |
//  Slave reset <-|P1.3         P1.0|-> Serial Clock Out (UCA0CLK)
//
//
//  B. Nisarga
//  Texas Instruments Inc.
//  Dec 2009
//  Built with CCS v4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include "msp430f5172.h"

unsigned char MST_Data,SLV_Data;
unsigned char temp;

void main(void)
{
  volatile unsigned int i;

  WDTCTL = WDTPW+WDTHOLD;                   // Stop watchdog timer

  // Configure ports
  P1DIR |= BIT3+BIT4;                       // Set P1.4 for valid data transfer
                                            // Set P1.3 for slave reset/chip select
  P1OUT |= BIT3;
  P1OUT |= 0x00;                            // Slave select - low
  P1SEL |= 0x07;                            // P1.0,1,2 option select USCI SPI pins
  
  UCA0CTL1 |= UCSWRST;                      // **Put state machine in reset**
  UCA0CTL0 |= UCMST+UCSYNC+UCCKPL+UCMSB;    // 3-pin, 8-bit SPI master
                                            // Clock polarity high, MSB
  UCA0CTL1 |= UCSSEL_2;                     // SMCLK
  UCA0BR0 = 0x02;                           // /2
  UCA0BR1 = 0;                              //
  UCA0MCTL = 0;                             // No modulation
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  UCA0IE |= UCRXIE;                         // Enable USCI_A0 RX interrupt

  P1OUT &= ~BIT3;                           // Now with SPI signals initialized,
  P1OUT |= BIT3;                            // reset slave

  for(i=50;i>0;i--);                        // Wait for slave to initialize

  MST_Data = 0x01;                          // Initialize data values
  SLV_Data = 0x00;                          //

  while (!(UCA0IFG&UCTXIFG));               // USCI_A0 TX buffer ready?
  UCA0TXBUF = MST_Data;                     // Transmit first character

  __bis_SR_register(LPM0_bits + GIE);       // CPU off, enable interrupts
}

#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
{
  volatile unsigned int i;

  switch(__even_in_range(UCA0IV,4))
  {
    case 0: break;                          // Vector 0 - no interrupt
    case 2:                                 // Vector 2 - RXIFG
      while (!(UCA0IFG&UCTXIFG));           // USCI_A0 TX buffer ready?

      if (UCA0RXBUF==SLV_Data)              // Test for correct character RX'd
        P1OUT |= BIT4;                      // If correct, P1.4 high
      else
        P1OUT &= ~BIT4;                     // If incorrect, P1.4 low

      MST_Data++;                           // Increment data
      SLV_Data++;
      UCA0TXBUF = MST_Data;                 // Send next value

      for(i = 20; i>0; i--);                // Add time between transmissions to
                                            // make sure slave can process information
      break;
    case 4: break;                          // Vector 4 - TXIFG
    default: break;
  }
}