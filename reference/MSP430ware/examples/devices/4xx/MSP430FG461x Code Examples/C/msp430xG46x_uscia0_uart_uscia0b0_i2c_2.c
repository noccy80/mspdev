//******************************************************************************
//   MSP430xG41x Demo - USCI_A0 UART RX single byte and USCI_B0 I2C Slave RX 
//                      single byte from MSP430 Master
//
//   Description: This demo connects two MSP430's via the I2C bus and UART. 
//   The master transmits single bytes to the slave. This is the slave code. 
//   This demonstrates how to implement an I2C slave receiver using the USCI_B0 
//   RX interrupt and UART reception using the USCI_A0 RX interrupt 
//   simultaneously.
//
//
//	***to be used with msp430xG46x_uscia0_uart_uscia0b0_i2c_1.c***
//
//                                 /|\  /|\
//                MSP430xG461x     10k  10k    MSP430xG461x
//                    slave         |    |        master
//              -----------------   |    |  -----------------
//            -|XIN  P3.1/UCB0SDA|<-|---+->|P3.1/UCB0SDA  XIN|-
//       32kHz |                 |  |      |                 | 32kHz
//            -|XOUT             |  |      |             XOUT|-
//             |     P3.2/UCB0SCL|<-+----->|P3.2/UCB0SCL     |
//             |                 |         |                 |
//             |     P4.6/UCA0TXD|<------->|P4.7/UCA0RXD     |
//             |                 |         |                 |
//             |     P4.7/UCA0RXD|<------->|P4.6/UCA0TXD     |
//             |                 |         |                 |
//
//
//   Tim Love/Brandon Elliott
//   Texas Instruments Inc.
//   March 2008
//   Built with IAR Embedded Workbench Version: 5.11
//******************************************************************************
#include "msp430xG46x.h"

void UART_Initialization(void);
void I2C_Initialization(void);

unsigned char I2C_ByteCtr;
unsigned int UART_Data;
unsigned int I2C_Data;

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  
  UART_Initialization();                    // Initialize UART
  I2C_Initialization();                     // Initialize I2C
  
  while (1)
  {
    I2C_ByteCtr = 0;                        // Clear I2C byte count
    _BIS_SR(LPM0_bits + GIE);               // Enter LPM0 w/ interrupt        
                                            // Remain in LPM0 until master
                                            // finishes TX
    _NOP();                                 // Set breakpoint >>here<< and read
  }                                         // read out the UART_Data and 
                                            // I2C_Data buffers
}

//------------------------------------------------------------------------------
// The USCIB0 data ISR is used to move received data from the I2C master
// to the I2C_Data buffer.
//------------------------------------------------------------------------------
#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void)
{
  I2C_Data = UCB0RXBUF;                     // Store RX'ed I2C data
  I2C_ByteCtr++;                            // Increment I2C byte count
}

//------------------------------------------------------------------------------
// The USCIB0 state ISR is used to wake up the CPU from LPM0 in order to
// process the I2C received data in the main program and storing received  
// UART data. LPM0 is only exit in caseof a (re-)start or stop condition when 
// actual data was received. 
//------------------------------------------------------------------------------
#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCIAB0RX_ISR(void)
{
  if(IFG2&UCA0RXIFG)
    UART_Data = UCA0RXBUF;                  // Store RX'ed UART data
  
  if (I2C_ByteCtr)                          // Check I2C byte counter
  {
    UCB0STAT &= ~(UCSTPIFG + UCSTTIFG);     // Clear interrupt flags
    _BIC_SR_IRQ(LPM0_bits + GIE);           // Exit LPM0 if data was received
  }
}

void UART_Initialization(void)
{
  P4SEL |= 0x0C0;                           // P4.7,6 = USCI_A0 RXD/TXD
  UCA0CTL1 |= UCSSEL_2;                     // SMCLK
  UCA0BR0 = 0x09;                           // 1MHz 115200
  UCA0BR1 = 0x00;                           // 1MHz 115200
  UCA0MCTL = 0x02;                          // Modulation
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  IE2 |= UCA0RXIE;                          // Enable USCI_A0 RX interrupt
}

void I2C_Initialization(void)
{
  P3SEL |= 0x06;                            // Assign I2C pins to USCI_B0
  UCB0CTL1 |= UCSWRST;                      // Enable SW reset
  UCB0CTL0 = UCMODE_3 + UCSYNC;             // I2C Slave, synchronous mode
  UCB0I2COA = 0x48;                         // Own Address is 048h
  UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
  UCB0I2CIE |= UCSTPIE;                     // Enable STP condition interrupt
  IE2 |= UCB0RXIE;                          // Enable RX interrupt
}