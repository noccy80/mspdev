//******************************************************************************
//   MSP430xG461x Demo - USCI_A0 UART TX single byte and USCI_B0 I2C Master TX 
//                       single byte to MSP430 Slave
//
//   Description: This demo connects two MSP430's via the I2C bus and UART. 
//   The master transmits to the slave. This is the master code. It continuously
//   transmits a single byte of data starting at 0 and incrementing from both 
//   UART and I2C. This demonstrates how to implement an I2C master transmitter 
//   using the USCI_B0 TX interrupt and UART transmission using the USCI_A0 TX 
//   interrupt simultaneously.
//   ACLK = 32kHz, MCLK = SMCLK = TACLK = BRCLK = 1MHz
//
//
//	***to be used with msp430xG46x_uscia0_uart_uscia0b0_i2c_2.c***
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
unsigned int UART_Data = 0;
unsigned int I2C_Data = 0;

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  
  UART_Initialization();                    // Initialize UART
  I2C_Initialization();                     // Initialize I2C

  while (1)
  {
    I2C_ByteCtr = 1;                        // Set I2C byte count
    UCB0CTL1 |= UCTR + UCTXSTT;             // I2C TX, start condition
    __bis_SR_register(CPUOFF + GIE);        // Enter LPM0 w/ interrupts
                                            // Remain in LPM0 until all data
                                            // is TX'd
    while (UCB0CTL1 & UCTXSTP);             // Loop until STP is TX'd
    _NOP();                                 // Set breakpoint >>here<< and read
                                            // read out the UART_Data and 
                                            // I2C_Data buffers
  }
}

//------------------------------------------------------------------------------
// The USCIAB0TX_ISR is structured such that it transmits UART data on USCI_A0 
// and I2C data on USCI_B0. UART transmission is disabled until I2C transmission
// has completed. 
//------------------------------------------------------------------------------
#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void)
{
  if((IFG2&UCA0TXIFG)&&(IE2&UCA0TXIE))      // Check for UART TX
  {
    UCA0TXBUF = UART_Data++;                // Load TX buffer
    IE2 &= ~UCA0TXIE;                       // Disable USCI_A0 TX interrupt
  }
  
  if(IFG2&UCB0TXIFG)                        // Check for I2C TX
  {
    if (I2C_ByteCtr)                        // Check I2C byte counter
    {
      UCB0TXBUF = I2C_Data++;               // Load TX buffer
      I2C_ByteCtr--;                        // Decrement I2C byte counter
    }
    else
    {
      UCB0CTL1 |= UCTXSTP;                  // I2C stop condition
      IFG2 &= ~UCB0TXIFG;                   // Clear USCI_B0 TX int flag
      IE2 |= UCA0TXIE;                      // Enable USCI_A0 TX interrupt
      __bic_SR_register_on_exit(CPUOFF + GIE);      // Exit LPM0
    }
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
  IE2 |= UCA0TXIE;                          // Enable USCI_A0 TX interrupt
}

void I2C_Initialization(void)
{ 
  P3SEL |= 0x06;                            // Assign I2C pins to USCI_B0
  UCB0CTL1 |= UCSWRST;                      // Enable SW reset
  UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;     // I2C Master, synchronous mode
  UCB0CTL1 = UCSSEL_2 + UCSWRST;            // Use SMCLK, keep SW reset
  UCB0BR0 = 11;                             // fSCL = SMCLK/11 = 95.3kHz
  UCB0BR1 = 0;
  UCB0I2CSA = 0x48;                         // Slave Address is 048h
  UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
  IE2 |= UCB0TXIE;                          // Enable USCI_B0 TX interrupt  
}