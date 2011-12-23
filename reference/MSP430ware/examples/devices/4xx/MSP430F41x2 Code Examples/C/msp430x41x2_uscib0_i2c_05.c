//******************************************************************************
//  MSP430F41x2 Demo - USCI_B0 I2C Slave TX single bytes to MSP430 Master
//
//  Description: This demo connects two MSP430's via the I2C bus. The master
//  reads from the slave. This is the slave code. The TX data begins at 0
//  and is incremented each time it is sent. An incoming start condition
//  is used as a trigger to increment the outgoing data. The master checks the
//  data it receives for validity. The USCI_B0 TX interrupt is used to know
//  when to TX.
//  ACLK = n/a, MCLK = SMCLK = default DCO = ~1.2MHz
//
//                                /|\  /|\
//               MSP430F41x2      10k  10k     MSP430F41x2
//                   slave         |    |        master
//             -----------------   |    |  -----------------
//           -|XIN  P6.2/UCB0SDA|<-|---+->|P6.2/UCB0SDA  XIN|-
//            |                 |  |      |                 |
//           -|XOUT             |  |      |             XOUT|-
//            |     P6.1/UCB0SCL|<-+----->|P6.1/UCB0SCL     |
//            |                 |         |                 |
//
//  P. Thanigai
//  Texas Instruments Inc.
//  January 2009
//  Built with CCE Version: 3.1 and IAR Embedded Workbench Version: 4.11
//******************************************************************************
#include "msp430x41x2.h"

unsigned char TXData;

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P6SEL |= BIT1 + BIT2;                     // Assign I2C pins to USCI_B0
  UCB0CTL1 |= UCSWRST;                      // Enable SW reset
  UCB0CTL0 = UCMODE_3 + UCSYNC;             // I2C Slave, synchronous mode
  UCB0I2COA = 0x48;                         // Own Address is 048h
  UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
  UCB0I2CIE |= UCSTTIE;                     // Enable STT interrupt
  IE2 |= UCB0TXIE;                          // Enable TX interrupt
  TXData = 0xff;                            // Used to hold TX data

  while (1)
  {
    __bis_SR_register(CPUOFF + GIE);        // Enter LPM0 w/ interrupts
  }
}

// USCI_B0 Data ISR
#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void)
{
  UCB0TXBUF = TXData;                       // TX data
  __bic_SR_register_on_exit(CPUOFF);        // Exit LPM0
}

// USCI_B0 State ISR
#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCIAB0RX_ISR(void)
{
  UCB0STAT &= ~UCSTTIFG;                    // Clear start condition int flag
  TXData++;                                 // Increment data
}
