//******************************************************************************
//   MSP430xG41x Demo - USCI_A0 UART RX single byte and USCI_B0 SPI Slave RX 
//                      single byte from MSP430 Master
//
//   Description: This demo connects two MSP430's via SPI and UART. The master
//   transmits single bytes to the slave. This is the slave code. This 
//   demonstrates how to implement an SPI slave using the USCI_B0 RX interrupt
//   and UART reception using the USCI_A0 RX interrupt simultaneously.
//
//
//
//	***to be used with msp430xG46x_uscia0b0_uart_spi_01.c***
//
//                MSP430xG461x                 MSP430xG461x
//                    slave                       master
//              -----------------           -----------------
//            -|XIN              |         |              XIN|-
//       32kHz |                 |         |                 | 32kHz
//            -|XOUT             |         |             XOUT|-
//             |    P3.1/UCB0SIMO|<--------|P3.1/UCB0SIMO    |
//             |                 |         |                 |
//             |    P3.2/UCB0SOMI|-------->|P3.2/UCB0SOMI    |
//             |                 |         |                 |
//             |     P3.3/UCB0CLK|<--------|P3.3/UCB0CLK     |
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
void SPI_Initialization(void);

unsigned int UART_Data;
unsigned int SPI_Data;

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  
  UART_Initialization();                    // Initialize UART
  SPI_Initialization();                     // Initialize SPI
  
  while (1)
  {
    _BIS_SR(LPM0_bits + GIE);               // Enter LPM0 w/ interrupt        
                                            // Remain in LPM0 until master
                                            // finishes TX
    _NOP();                                 // Set breakpoint >>here<< and read
  }                                         // read out the UART_Data and 
                                            // SPI_Data variables
}

//------------------------------------------------------------------------------
// The USCIAB0TX_ISR is structured such that it stores received UART data on 
// USCI_A0 and SPI data on USCI_B0.
//------------------------------------------------------------------------------
#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCIAB0RX_ISR(void)
{
  if(IFG2&UCA0RXIFG)
    UART_Data = UCA0RXBUF;                  // Store RX'ed UART data
  
  if(IFG2&UCB0RXIFG)
    SPI_Data = UCB0RXBUF;                   // Store RX'ed SPI data
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

void SPI_Initialization(void)
{
  while(!(P3IN&0x08));                      // If clock sig from mstr stays low,
                                            // it is not yet in SPI mode
  P3SEL |= 0x0E;                            // P3.3,2,1 option select
  UCB0CTL1 = UCSWRST;                       // **Put state machine in reset**
  UCB0CTL0 |= UCSYNC+UCCKPL+UCMSB;          // 3-pin, 8-bit SPI master
  UCB0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  IE2 |= UCB0RXIE;                          // Enable USCI_B0 RX interrupt
}