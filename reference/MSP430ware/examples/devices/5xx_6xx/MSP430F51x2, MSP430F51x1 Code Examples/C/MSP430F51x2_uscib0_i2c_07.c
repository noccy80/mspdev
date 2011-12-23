//******************************************************************************
//  MSP430F51x2 Demo - USCI_B0 I2C Slave RX single bytes from MSP430 Master
//
//  Description: This demo connects two MSP430's via the I2C bus. The master
//  transmits to the slave. This is the slave code. The interrupt driven
//  data receiption is demonstrated using the USCI_B0 RX interrupt.
//  ACLK = n/a, MCLK = SMCLK = default DCO = ~1.045MHz
//
//                                /|\  /|\
//               MSP430F51x2      10k  10k     MSP430F51x2
//                   slave         |    |        master
//             -----------------   |    |   -----------------
//           -|XIN  P1.4/UCB0SDA|<-|----+->|P1.4/UCB0SDA  XIN|-
//            |                 |  |       |                 |
//           -|XOUT             |  |       |             XOUT|-
//            |     P1.5/UCB0SCL|<-+------>|P1.5/UCB0SCL     |
//            |                 |          |                 |
//
//  B. Nisarga
//  Texas Instruments Inc.
//  Dec 2009
//  Built with CCS v4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include "msp430f5172.h"

volatile unsigned char RXData;

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  // Configure ports
  P1SEL |= BIT4 + BIT5;                     // Assign I2C pins to USCI_B0
  // Configure I2C
  UCB0CTL1 |= UCSWRST;                      // Enable SW reset
  UCB0CTL0 = UCMODE_3 + UCSYNC;             // I2C Slave, synchronous mode
  UCB0I2COA = 0x48;                         // Own Address is 048h
  UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
  UCB0IE |= UCRXIE;                         // Enable RX interrupt

  while (1)
  {
    __bis_SR_register(LPM0_bits + GIE);     // Enter LPM0, enable interrupts
    __no_operation();                       // Set breakpoint >>here<< and read
  }                                         // RXData
}

// USCI_B0 Data ISR
#pragma vector = USCI_B0_VECTOR
__interrupt void USCI_B0_ISR(void)
{
  switch(__even_in_range(UCB0IV,12))
  {
  case  0: break;                           // Vector  0: No interrupts
  case  2: break;                           // Vector  2: ALIFG
  case  4: break;                           // Vector  4: NACKIFG
  case  6: break;                           // Vector  6: STTIFG
  case  8: break;                           // Vector  8: STPIFG
  case 10:                                  // Vector 10: RXIFG
    RXData = UCB0RXBUF;                     // Get RX data
    __bic_SR_register_on_exit(LPM0_bits);   // Exit LPM0
    break;
  case 12: break;                           // Vector 12: TXIFG  
  default: break;
  }
}
