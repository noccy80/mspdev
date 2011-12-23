//******************************************************************************
//  CC430F513x Demo - USCI_B0 I2C Slave TX multiple bytes to MSP430 Master
//
//  Description: This demo connects two MSP430's via the I2C bus. The slave
//  transmits to the master. This is the slave code. The interrupt driven
//  data transmission is demonstrated using the USCI_B0 TX interrupt.
//  ACLK = n/a, MCLK = SMCLK = default DCO = ~1.045MHz
//
//                                /|\  /|\
//               CC430F5137      10k  10k     CC430F5137
//                   slave         |    |        master
//             -----------------   |    |   -----------------
//           -|XIN  P2.6/UCB0SDA|<-|----+->|P2.6/UCB0SDA  XIN|-
//            |                 |  |       |                 | 32kHz
//           -|XOUT             |  |       |             XOUT|-
//            |     P2.7/UCB0SCL|<-+------>|P2.7/UCB0SCL     |
//            |                 |          |             P1.0|--> LED
//
//   M Morales
//   Texas Instruments Inc.
//   April 2009
//   Built with CCE Version: 3.2.2 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************

#include "cc430x513x.h"

unsigned char *PTxData;                     // Pointer to TX data
const unsigned char TxData[] =              // Table of data to transmit
{
  0x11,
  0x22,
  0x33,
  0x44,
  0x55
};

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  
  PMAPPWD = 0x02D52;                        // Get write-access to port mapping regs  
  P2MAP6 = PM_UCB0SDA;                      // Map UCB0SDA output to P2.6 
  P2MAP7 = PM_UCB0SCL;                      // Map UCB0SCL output to P2.7 
  PMAPPWD = 0;                              // Lock port mapping registers 
  
  P2SEL |= BIT6 + BIT7;                     // Select P2.6 & P2.7 to I2C function
    
  UCB0CTL1 |= UCSWRST;                      // Enable SW reset
  UCB0CTL0 = UCMODE_3 + UCSYNC;             // I2C Slave, synchronous mode
  UCB0I2COA = 0x48;                         // Own Address is 048h
  UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
  UCB0IE |= UCTXIE + UCSTPIE + UCSTTIE;     // Enable STT and STP interrupt
                                            // Enable TX interrupt

  while (1)
  {
    PTxData = (unsigned char *)TxData;      // Start of TX buffer
    
    __bis_SR_register(LPM0_bits + GIE);     // Enter LPM0, enable interrupts
                                            // Remain in LPM0 until master
                                            // finishes RX
    __no_operation();                       // Set breakpoint >>here<< and
  }                                         // read out the TXByteCtr counter
}

//------------------------------------------------------------------------------
// The USCI_B0 data ISR TX vector is used to move data from MSP430 memory to the
// I2C master. PTxData points to the next byte to be transmitted, and TXByteCtr
// keeps track of the number of bytes transmitted.
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// The USCI_B0 state ISR TX vector is used to wake up the CPU from LPM0 in order
// to do processing in the main program after data has been transmitted. LPM0 is
// only exit in case of a (re-)start or stop condition when actual data
// was transmitted.
//------------------------------------------------------------------------------
#pragma vector = USCI_B0_VECTOR
__interrupt void USCI_B0_ISR(void)
{
  switch(__even_in_range(UCB0IV,12))
  {
  case  0: break;                           // Vector  0: No interrupts
  case  2: break;                           // Vector  2: ALIFG
  case  4: break;                           // Vector  4: NACKIFG
  case  6:                                  // Vector  6: STTIFG
    UCB0IFG &= ~UCSTTIFG;                   // Clear start condition int flag
    break;
  case  8:                                  // Vector  8: STPIFG
    UCB0IFG &= ~UCSTPIFG;                   // Clear stop condition int flag
    __bic_SR_register_on_exit(LPM0_bits);   // Exit LPM0 if data was transmitted
    break;
  case 10: break;                           // Vector 10: RXIFG
  case 12:                                  // Vector 12: TXIFG  
    UCB0TXBUF = *PTxData++;                 // Transmit data at address PTxData
    break;
  default: break;
  }
}
