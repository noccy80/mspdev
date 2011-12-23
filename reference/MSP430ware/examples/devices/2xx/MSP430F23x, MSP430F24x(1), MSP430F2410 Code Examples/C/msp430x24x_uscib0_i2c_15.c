//******************************************************************************
//  MSP430F24x Demo - USCI_B0 I2C Slave RX multiple bytes from MSP430 Master &
//                    USCI_A1 SPI Slave RX single bytes simultaneously.
//
//  Description: This demo connects two MSP430's via the I2C bus on channel B0
//  and SPI on channel A1. The master transmits to the slave. This is the slave 
//  code. ACLK = n/a, MCLK = SMCLK = default DCO = ~1.045MHz
//
//  (To be used with msp430F22x2_uscib0_i2c_14.c)
//
//                   MSP430F24x - Slave SPI/I2C
//
//                                    /|\  /|\
//                 -----------------   10k  10k  
//             /|\|              XIN|- |    |
//              | |                 |  |    |
//              --|RST          XOUT|- |    |
//                |                 |  |    |
//                |     P3.1/UCB0SDA|<-|----+-> (Master SDA)
//                |                 |  |    
//                |                 |  |    
//                |     P3.2/UCB0SCL|<-+----->  (Master SCL)
//                |                 |
//                |             P3.6|<- Data In (UCA1SIMO)
//                |                 |
//          LED <-|P1.0         P3.7|-> Data Out (UCA1SOMI)
//                |                 |
//                |          P5.0|-> Serial Clock In (UCA1CLK)
//
//  R. B. Elliott / H. Grewal
//  Texas Instruments Inc.
//  March 2008
//  Built with IAR Embedded Workbench Version: 3.42A
//******************************************************************************
#include "msp430x24x.h"

unsigned char *PRxData;                     // Pointer to RX data
unsigned char RXByteCtr;
volatile unsigned char RxBuffer[128];       // Allocate 128 byte of RAM

void SetupSPI(void);
void SetupI2C(void);

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  
  SetupI2C();			            // Configure I2C slave channel B0
  SetupSPI();			            // Configure SPI slave channel A0

  while (1)
  {
    PRxData = (unsigned char *)RxBuffer;    // Start of RX buffer
    RXByteCtr = 0;                          // Clear RX byte count
    __bis_SR_register(CPUOFF + GIE);        // Enter LPM0 w/ interrupts
                                            // Remain in LPM0 until master
                                            // finishes TX
    __no_operation();                       // Set breakpoint >>here<< and read
  }                                         // read out the RxData buffer
}

//------------------------------------------------------------------------------
// The USCI_B0 data ISR is used to move received data from the I2C master
// to the MSP430 memory.
//------------------------------------------------------------------------------
#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void)
{
  *PRxData++ = UCB0RXBUF;                   // Move RX data to address PRxData
  RXByteCtr++;                              // Increment RX byte count
}

//------------------------------------------------------------------------------
// The USCI_B0 state ISR is used to wake up the CPU from LPM0 in order to
// process the received data in the main program. LPM0 is only exit in case
// of a (re-)start or stop condition when actual data was received.
//------------------------------------------------------------------------------
#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCIAB0RX_ISR(void)
{

  UCB0STAT &= ~(UCSTPIFG + UCSTTIFG);       // Clear interrupt flags
  if (RXByteCtr)                            // Check RX byte counter
    __bic_SR_register_on_exit(CPUOFF);      // Exit LPM0 if data was
}                                           // received

// Echo character
#pragma vector=USCIAB1RX_VECTOR
__interrupt void USCI1RX_ISR (void)
{
  while (!(UC1IFG & UCA1TXIFG));              // USCI_A1 TX buffer ready?
  UCA1TXBUF = UCA1RXBUF;
}


void SetupSPI(void){
  P3SEL |= 0x0C0;                           // P3.6,7 USCI_A1 option select
  P5SEL |= 0x01;                            // P5.0 USCI_A1 option select
  UCA1CTL1 = UCSWRST;                       // **Put state machine in reset**
  UCA1CTL0 |= UCCKPL + UCMSB + UCSYNC;      // 3-pin, 8-bit SPI master
  UCA1CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  UC1IE |= UCA1RXIE;                        // Enable USCI1 RX interrupt
}

void SetupI2C(void){
  P3SEL |= 0x06;                            // Assign I2C pins to USCI_B0
  UCB0CTL1 |= UCSWRST;                      // Enable SW reset
  UCB0CTL0 = UCMODE_3 + UCSYNC;             // I2C Slave, synchronous mode
  UCB0I2COA = 0x48;                         // Own Address is 048h
  UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
  UCB0I2CIE |= UCSTPIE + UCSTTIE;           // Enable STT and STP interrupt
  IE2 |= UCB0RXIE;                          // Enable RX interrupt

}

