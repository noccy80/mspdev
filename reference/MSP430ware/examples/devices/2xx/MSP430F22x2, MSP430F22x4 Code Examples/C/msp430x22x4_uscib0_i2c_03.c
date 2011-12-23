//******************************************************************************
//  MSP430F22x4 Demo - USCI_B0 I2C Master Interface to DAC8571, Write
//
//  Description: Using UCB0TXIE, a continuous sine wave is output to the
//  external DAC using a 16-point look-up table. Only one start condition
//  is executed. Data is handled by the ISR and the CPU is normally in LPM0.
//  ACLK = n/a, MCLK = SMCLK = BRCLK = default DCO = ~1.2MHz
//
//               MSP430F22x4                       DAC8571
//           ------------------                   ------------
//         -|XIN   P3.1/UCB0SDA|<--------------->|SDA         |
//          |      P3.2/UCB0SCL|---------------->|SCL  I2C    |
//         -|XOUT              |                 |    SLAVE   |
//          |     I2C MASTER   |              GND|A0          |
//
//
//  DAC8571 I2C address = 0x4C (A0 = GND)
//
//  Andreas Dannenberg
//  Texas Instruments Inc.
//  March 2006
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x22x4.h"

const unsigned char Sine_Tab[] =            // 16 Point 16-bit Sine Table
{
  0xFF,                                     // MSB Word 0
  0xFF,                                     // LSB
  0xF6,                                     // MSB Word 1
  0x40,                                     // LSB
  0xDA,                                     // MSB Word 2
  0x81,                                     // LSB
  0xB0,                                     // MSB Word 3
  0xFA,                                     // LSB
  0x7F,                                     // MSB Word 4
  0xFF,                                     // LSB
  0x4F,                                     // MSB Word 5
  0x03,                                     // LSB
  0x25,                                     // MSB Word 6
  0x7C,                                     // LSB
  0x09,                                     // MSB Word 7
  0xBD,                                     // LSB
  0x00,                                     // MSB Word 8
  0x00,                                     // LSB
  0x09,                                     // MSB Word 9
  0xBD,                                     // LSB
  0x25,                                     // MSB Word 10
  0x7C,                                     // LSB
  0x4F,                                     // MSB Word 11
  0x03,                                     // LSB
  0x7F,                                     // MSB Word 12
  0xFE,                                     // LSB
  0xB0,                                     // MSB Word 13
  0xFA,                                     // LSB
  0xDA,                                     // MSB Word 14
  0x81,                                     // LSB
  0xF6,                                     // MSB Word 15
  0x40                                      // LSB
};

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop Watchdog Timer
  P3SEL |= 0x06;                            // Assign I2C pins to USCI_B0
  UCB0CTL1 |= UCSWRST;                      // Enable SW reset
  UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;     // I2C Master, synchronous mode
  UCB0CTL1 = UCSSEL_2 + UCSWRST;            // Use SMCLK, keep SW reset
  UCB0BR0 = 12;                             // fSCL = SMCLK/12 = ~100kHz
  UCB0BR1 = 0;
  UCB0I2CSA = 0x4c;                         // Set slave address
  UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
  IE2 |= UCB0TXIE;                          // Enable TX ready interrupt
  UCB0CTL1 |= UCTR + UCTXSTT;               // I2C TX, start condition
  UCB0TXBUF = 0x010;                        // Write DAC control byte
  __bis_SR_register(CPUOFF + GIE);          // Enter LPM0 w/ interrupts
}

// USCI_B0 Data ISR
#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void)
{
  static unsigned char ByteCtr;

  UCB0TXBUF = Sine_Tab[ByteCtr++];          // Transmit data byte
  ByteCtr &= 0x1f;                          // Do not exceed table
}
