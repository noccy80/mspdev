//******************************************************************************
//  MSP430F22x4 Demo - USCI_B0 I2C Master Interface to PCF8574, Read/Write
//
//  Description: I2C communication with a PCF8574 in read and write mode is
//  demonstrated. PCF8574 port P is configured with P0-P3 input, P4-P7. Read
//  P0-P3 input data is written back to Port P4-P7. This example uses the
//  RX ISR and generates an I2C restart condition while switching from
//  master receiver to master transmitter.
//  ACLK = n/a, MCLK = SMCLK = TACLK = BRCLK = default DCO = ~1.2MHz
//
//                                MSP430F22x4
//                              -----------------
//                  /|\ /|\ /|\|              XIN|-
//                  10k 10k  | |                 |
//       PCF8574     |   |   --|RST          XOUT|-
//       ---------   |   |     |                 |
//  --->|P0    SDA|<-|---+---->|P3.1/UCB0SDA     |
//  --->|P1       |  |         |                 |
//  --->|P2       |  |         |                 |
//  --->|P3    SCL|<-+---------|P3.2/UCB0SCL     |
//  <---|P4       |            |                 |
//  <---|P5       |            |                 |
//  <---|P6       |            |                 |
//  <---|P7       |            |                 |
//   +--|A0,A1,A2 |            |                 |
//   |  |         |            |                 |
//  \|/
//
//  Andreas Dannenberg
//  Texas Instruments Inc.
//  March 2006
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x22x4.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop Watchdog Timer
  P3SEL |= 0x06;                            // Assign I2C pins to USCI_B0
  UCB0CTL1 |= UCSWRST;                      // Enable SW reset
  UCB0CTL0 = UCMST+UCMODE_3+UCSYNC;         // I2C Master, synchronous mode
  UCB0CTL1 = UCSSEL_2+UCSWRST;              // Use SMCLK, keep SW reset
  UCB0BR0 = 12;                             // fSCL = SMCLK/12 = ~100kHz
  UCB0BR1 = 0;
  UCB0I2CSA = 0x20;                         // Set slave address
  UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
  IE2 |= UCB0RXIE;                          // Enable RX interrupt
  TACCTL0 = CCIE;                           // TACCR0 interrupt enabled
  TACTL = TASSEL_2 + MC_2;                  // SMCLK, contmode

  while (1)
  {
    __bis_SR_register(CPUOFF + GIE);        // CPU off, interrupts enabled
    UCB0CTL1 &= ~UCTR;                      // I2C RX
    UCB0CTL1 |= UCTXSTT;                    // I2C start condition
    while (UCB0CTL1 & UCTXSTT);             // Loop until I2C STT is sent
    UCB0CTL1 |= UCTR + UCTXSTT;             // I2C TX, start condition
    __bis_SR_register(CPUOFF + GIE);        // CPU off, interrupts enabled
    while (UCB0CTL1 & UCTXSTT);             // Loop until I2C STT is sent
    UCB0CTL1 |= UCTXSTP;                    // I2C stop condition after 1st TX
  }
}

#pragma vector = TIMERA0_VECTOR
__interrupt void TA0_ISR(void)
{
  __bic_SR_register_on_exit(CPUOFF);        // Exit LPM0
}

// USCI_B0 Data ISR
#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void)
{
  UCB0TXBUF = (UCB0RXBUF << 4) | 0x0f;      // Move RX data to TX
  __bic_SR_register_on_exit(CPUOFF);        // Exit LPM0
}
