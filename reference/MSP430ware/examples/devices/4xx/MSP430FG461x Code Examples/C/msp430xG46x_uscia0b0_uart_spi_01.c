//******************************************************************************
//   MSP430xG461x Demo - USCI_A0 UART TX single byte and USCI_B0 SPI Master TX 
//                       single byte to MSP430 Slave
//
//   Description: This demo connects two MSP430's via SPI and UART. The master
//   transmits to the slave. This is the master code. It continuously
//   transmits a single byte of data starting at 0 and incrementing from both 
//   SPI and UART. This demonstrates how to implement an SPI master using the 
//   USCI_B0 TX interrupt and UART transmission using the USCI_A0 TX interrupt 
//   simultaneously.
//
//	***to be used with msp430xG46x_uscia0b0_uart_spi_02.c***
//
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

unsigned int UART_Data = 0;
unsigned int SPI_Data = 0;

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  
  UART_Initialization();                    // Initialize UART
  SPI_Initialization();                     // Initialize SPI

  while (1)
  {
    __bis_SR_register(CPUOFF + GIE);        // Enter LPM0 w/ interrupts
                                            // Remain in LPM0 until all data
                                            // is TX'd
    _NOP();                                 // Set breakpoint >>here<< and read
                                            // read out the UART_Data and 
                                            // SPI_Data variables
  }
}

//------------------------------------------------------------------------------
// The USCIAB0TX_ISR is structured such that it transmits UART data on USCI_A0 
// and SPI data on USCI_B0. 
//------------------------------------------------------------------------------
#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void)
{
  if(IFG2&UCA0TXIFG)                        // Check for UART TX
    UCA0TXBUF = UART_Data++;                // Load TX buffer
  
  if(IFG2&UCB0TXIFG)                        // Check for SPI TX
    UCB0TXBUF = SPI_Data++;                 // Load TX buffer
  
  __bic_SR_register_on_exit(CPUOFF + GIE);      // Exit LPM0
}

void UART_Initialization(void)
{
  P4SEL |= 0x0C0;                           // P4.7,6 = USCI_A0 RXD/TXD
  UCA0CTL1 |= UCSSEL_2;                     // SMCLK
  UCA0BR0 = 0x09;                           // 1MHz 115200
  UCA0BR1 = 0x00;                           // 1MHz 115200
  UCA0MCTL = 0x02;                          // Modulation
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  IE2 |= UCA0TXIE;                          // Enable USCI_A0 TX interrupt
}

void SPI_Initialization(void)
{ 
  P3SEL |= 0x0E;                            // P3.3,2,1 option select
  UCB0CTL0 |= UCMST+UCSYNC+UCCKPL+UCMSB;    // 3-pin, 8-bit SPI master
  UCB0CTL1 |= UCSSEL_2;                     // SMCLK
  UCB0BR0 = 0x02;                           // /2
  UCB0BR1 = 0;                              //
  UCB0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  IE2 |= UCB0TXIE;                          // Enable USCI_A0 TX interrupt 
}