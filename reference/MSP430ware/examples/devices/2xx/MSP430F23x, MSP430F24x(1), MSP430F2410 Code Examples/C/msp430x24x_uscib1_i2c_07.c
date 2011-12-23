//******************************************************************************
//  MSP430x24x Demo - USCI_B1 I2C Slave RX single bytes from MSP430 Master
//
//  Description: This demo connects two MSP430's via the I2C bus. The master
//  transmits to the slave. This is the slave code. The interrupt driven
//  data receiption is demonstrated using the USCI_B1 RX interrupt.
//  ACLK = n/a, MCLK = SMCLK = default DCO = ~1.045Mhz
//
//                                /|\  /|\
//               MSP430F249      10k  10k     MSP430F22x4
//                   slave         |    |        master
//             -----------------   |    |  -----------------
//           -|XIN  P5.1/UCB1SDA|<-|---+->|P5.1/UCB1SDA  XIN|-
//            |                 |  |      |                 |
//           -|XOUT             |  |      |             XOUT|-
//            |     P5.2/UCB1SCL|<-+----->|P5.2/UCB1SCL     |
//            |                 |         |                 |
//
//  B. Nisarga
//  Texas Instruments Inc.
//  September 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//******************************************************************************
#include "msp430x24x.h"

volatile unsigned char RXData;

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P5SEL |= 0x06;                            // Assign I2C pins to USCI_B1
  UCB1CTL1 |= UCSWRST;                      // Enable SW reset
  UCB1CTL0 = UCMODE_3 + UCSYNC;             // I2C Slave, synchronous mode
  UCB1I2COA = 0x48;                         // Own Address is 048h
  UCB1CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
  UC1IE |= UCB1RXIE;                        // Enable RX interrupt

  while (1)
  {
    __bis_SR_register(CPUOFF + GIE);        // Enter LPM0 w/ interrupts
    __no_operation();                       // Set breakpoint >>here<< and read
  }                                         // RXData
}

// USCI_B1 Data ISR
#pragma vector = USCIAB1TX_VECTOR
__interrupt void USCIAB1TX_ISR(void)
{
  RXData = UCB1RXBUF;                       // Get RX data
  __bic_SR_register_on_exit(CPUOFF);        // Exit LPM0
}
