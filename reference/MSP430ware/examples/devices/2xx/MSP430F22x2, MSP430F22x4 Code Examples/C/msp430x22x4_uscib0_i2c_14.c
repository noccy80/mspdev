//******************************************************************************
//  MSP430F22x4 Demo - USCI_B0 I2C Master TX single bytes to MSP430 Slave and 
//                     USCI_A0 SPI Master TX single bytes simultaneously.
//
//  Description: This demo connects two MSP430's via the I2C bus. The master
//  transmits to the slave. This is the master code. It continuously
//  transmits 55h, 56h, etc...(SPI) and AAh, ABh, etc(I2C). 
//  This example illustrates how to manage interrupt operations with a shared 
//  ISR.  ACLK = n/a, MCLK = SMCLK = BRCLK = default DCO = ~1.2MHz
//
//  (To be used with msp430x24x_uscib0_i2c_15.c)
//
//                    MSP430F22x4 - Master SPI/I2C
//
//                                    /|\  /|\
//                 -----------------   10k  10k  
//             /|\|              XIN|- |    |
//              | |                 |  |    |
//              --|RST          XOUT|- |    |
//                |                 |  |    |
//                |     P3.1/UCB0SDA|<-|----+-> (Slave SDA)
//                |                 |  |    
//                |                 |  |    
//                |     P3.2/UCB0SCL|<-+----->  (Slave SCL)
//                |                 |
//                |             P3.4|-> Data Out (UCA0SIMO)
//                |                 |
//          LED <-|P1.0         P3.5|<- Data In (UCA0SOMI)
//                |                 |
//                |             P3.0|-> Serial Clock Out (UCA0CLK)
//
//  R. B. Elliott / H. Grewal
//  Texas Instruments Inc.
//  March 2008
//  Built with IAR Embedded Workbench Version: 3.42A
//******************************************************************************
#include "msp430x22x2.h"

void SPI_TX_Setup (void);
void I2C_TX_Setup (void);
unsigned char MST_Data, SLV_Data, TXData, TXByteCtr=0;

void main(void)
{
  volatile unsigned int i;
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  MST_Data = 0x55;                          // Initialize data values
  TXData = 0xAA;                            // Holds TX data
  
while(1){  
  SPI_TX_Setup();
  I2C_TX_Setup();
  
  UCB0CTL1 |= UCTR + UCTXSTT;               // I2C TX, start condition
  __bis_SR_register(CPUOFF+GIE);            // CPU off, enable interrupts

   TXData++;                                // Increment data byte
   MST_Data++;
        } 
}

void SPI_TX_Setup (void){

  UCA0CTL1 |= UCSWRST;                      // Enable SW reset

  P1OUT = 0x00;                             // P1 setup for LED
  P1DIR |= 0x01;                            //
  P3SEL |= 0x31;                            // P3.0,4,5 USCI_A0 option select

  UCA0CTL0 |= UCCKPL + UCMSB + UCMST + UCSYNC;  // 3-pin, 8-bit SPI master
  UCA0CTL1 |= UCSSEL_2;                     // SMCLK
  UCA0BR0 |= 0x02;                          // /2
  UCA0BR1 = 0;                              //
  UCA0MCTL = 0;                             // No modulation
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  IE2 |= UCA0TXIE;                          // Enable USCI0 TX interrupt

  for (int i = 50; i > 0; i--);             // Wait for slave to initialize
}

void I2C_TX_Setup (void){

  P3SEL |= 0x06;                            // Assign I2C pins to USCI_B0
  UCB0CTL1 |= UCSWRST;                      // Enable SW reset
  UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;     // I2C Master, synchronous mode
  UCB0CTL1 = UCSSEL_2 + UCSWRST;            // Use SMCLK, keep SW reset
  UCB0BR0 = 12;                             // fSCL = SMCLK/12 = ~100kHz
  UCB0BR1 = 0;
  UCB0I2CSA = 0x48;                         // Slave Address is 048h
  UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
  TXByteCtr = 1;                            // Load TX byte counter (I2C)
  IE2 |= UCB0TXIE;                          // Enable TX interrupt
  while (UCB0CTL1 & UCTXSTP);               // Ensure stop condition got sent
}



//------------------------------------------------------------------------------
// The USCIAB0TX_ISR is structured such that it can be used to transmit any
// number of bytes by pre-loading TXByteCtr with the byte count.
//------------------------------------------------------------------------------
#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void)
{
 // SPI stuff 
  if((IFG2 & UCA0TXIFG)){                   // USCI_A0 TX buffer ready?
  P1OUT ^= 0x01;
  UCA0TXBUF = MST_Data;                     // Transmit first character (SPI)
  IE2 &= ~UCA0TXIE;
  }
  
 
 //I2C Stuff 
  if (TXByteCtr)                            // Check TX byte counter
  {
    UCB0TXBUF = TXData;                     // Load TX buffer
    TXByteCtr--;                            // Decrement TX byte counter
  }
  else
  {
    UCB0CTL1 |= UCTXSTP;                    // I2C stop condition
    IFG2 &= ~UCB0TXIFG;                     // Clear USCI_B0 TX int flag
    __bic_SR_register_on_exit(CPUOFF+GIE);  // Exit LPM0
  }
}

