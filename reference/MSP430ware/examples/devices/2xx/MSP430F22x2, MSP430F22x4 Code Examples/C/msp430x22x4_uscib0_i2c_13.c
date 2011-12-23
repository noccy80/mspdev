//******************************************************************************
//  MSP430x22x4 Demo - USCI_B0 I2C Slave RX/TX multiple bytes to MSP430 Master
//
//  Description: This demo connects two MSP430's via the I2C bus. The slave
//  recieves then transmits to the master. This is the slave code. The interrupt 
//  driven data transmission is demonstrated using the USCI_B0 TX interrupt.
//  ACLK = n/a, MCLK = SMCLK = default DCO = ~1.045Mhz
//
//	***to be used with msp430x22x4_uscib0_i2c_12.c***
//
//                                /|\  /|\
//               MSP430F22x4       10k  10k     MSP430F22x4
//                   slave         |    |        master
//             -----------------   |    |  -----------------
//           -|XIN  P3.1/UCB0SDA|<-|---+->|P3.1/UCB0SDA  XIN|-
//            |                 |  |      |                 |
//           -|XOUT             |  |      |             XOUT|-
//            |     P3.2/UCB0SCL|<-+----->|P3.2/UCB0SCL     |
//            |                 |         |                 |
//
//  R. B. Elliott / H. Grewal
//  Texas Instruments Inc.
//  April 2008
//  Built with IAR Embedded Workbench Version: 3.42A
//******************************************************************************
#include "msp430x22x2.h"


#define NUM_BYTES  2                        // How many bytes?
//**** Please note this value needs to be the same as NUM_BYTES_RX in the
//     associated master code. This definition lets the slave know when to
//     switch from RX interrupt sources to TX interrupt sources. This is 
//     important since the interrupt vectors are shared by TX and RX flags.

unsigned char *PTxData;                     // Pointer to TX data
unsigned char *PRxData;                     // Pointer to RX data
volatile unsigned char RxBuffer[128];       // Allocate 128 byte of RAM
char SLV_Data = 0x11;
volatile unsigned char TXByteCtr, RXByteCtr, RX = 0;
volatile unsigned char RxBuffer[128];       // Allocate 128 byte of RAM


void USCI_SLAVE_SETUP(void);
void Setup_RX(void);
void Receive(void);

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
 
  while(1){
  USCI_SLAVE_SETUP();
  }
}

//------------------------------------------------------------------------------
// The USCI_B0 data ISR is used to move data from MSP430 memory to the
// I2C master. PTxData points to the next byte to be transmitted, and TXByteCtr
// keeps track of the number of bytes transmitted.
//------------------------------------------------------------------------------
#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void)
{
  if(RX == 0){ UCB0TXBUF = SLV_Data++;      // Transmit data at address PTxData
  TXByteCtr++;                              // Increment TX byte counter
  }  
  if(RX == 1){*PRxData++ = UCB0RXBUF;       // Move RX data to address PRxData
  RXByteCtr++;                              // Increment RX byte count
  if(RXByteCtr >= NUM_BYTES){               // Received enough bytes to switch 
  RX = 0;                                   // to TX? 
  IE2 &= ~UCB0RXIE; 
  IE2 |= UCB0TXIE; 
  RXByteCtr = 0;
  }
  }
}

//------------------------------------------------------------------------------
// The USCI_B0 state ISR is used to wake up the CPU from LPM0 in order to do
// processing in the main program after data has been transmitted. LPM0 is
// only exit in case of a (re-)start or stop condition when actual data
// was transmitted.
//------------------------------------------------------------------------------
#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCIAB0RX_ISR(void)
{ 
  if(RX == 0){ UCB0STAT &= ~(UCSTPIFG + UCSTTIFG);       // Clear interrupt flags
  if (TXByteCtr)                            // Check TX byte counter
   __bic_SR_register_on_exit(CPUOFF);       // Exit LPM0 if data was
}                                           // transmitted
  if(RX == 1){UCB0STAT &= ~(UCSTPIFG + UCSTTIFG);       // Clear interrupt flags
}
}
void Setup_RX(void){
  _DINT();
  RX = 1;
  IE2 &= ~UCB0TXIE;                         // Disable TX interrupt
  UCB0CTL1 |= UCSWRST;                      // Enable SW reset
  UCB0CTL0 = UCMODE_3 + UCSYNC;             // I2C Slave, synchronous mode
  UCB0I2COA = 0x48;                         // Own Address is 048h
  UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
  UCB0I2CIE |= UCSTPIE + UCSTTIE;           // Enable STT and STP interrupt
  IE2 |= UCB0RXIE;                          // Enable RX interrupt
  
}

void Receive(void){
    PRxData = (unsigned char *)RxBuffer;    // Start of RX buffer
    RXByteCtr = 0;                          // Clear RX byte count
    TXByteCtr = 0;
    __bis_SR_register(CPUOFF + GIE);        // Enter LPM0 w/ interrupts
                                            // Remain in LPM0 until master
                                            // finishes TX
}
void USCI_SLAVE_SETUP(void){
  P3SEL |= 0x06;                            // Assign I2C pins to USCI_B0
  Setup_RX();
  Receive();
}
