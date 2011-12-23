//******************************************************************************
//  MSP430F552x Demo - USCI_B0 I2C Slave RX multiple bytes from MSP430 Master
//
//  Description: This demo connects two MSP430's via the I2C bus. The master
//  transmits to the slave. This is the slave code. The interrupt driven
//  data receiption is demonstrated using the USCI_B0 RX interrupt.
//  ACLK = n/a, MCLK = SMCLK = default DCO = ~1.045MHz
//
//                                /|\  /|\
//                MSP430F5529     10k  10k     MSP430F5529
//                   slave         |    |         master
//             -----------------   |    |   -----------------
//           -|XIN  P3.0/UCB0SDA|<-|----+->|P3.0/UCB0SDA  XIN|-
//            |                 |  |       |                 |
//           -|XOUT             |  |       |             XOUT|-
//            |     P3.1/UCB0SCL|<-+------>|P3.1/UCB0SCL     |
//            |                 |          |                 |
//
//   Bhargavi Nisarga
//   Texas Instruments Inc.
//   April 2009
//   Built with CCSv4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************

#include <msp430f5529.h>

unsigned char *PRxData;                     // Pointer to RX data
unsigned char RXByteCtr;
volatile unsigned char RxBuffer[128];       // Allocate 128 byte of RAM

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  
  P3SEL |= 0x03;                            // Assign I2C pins to USCI_B0
  UCB0CTL1 |= UCSWRST;                      // Enable SW reset
  UCB0CTL0 = UCMODE_3 + UCSYNC;             // I2C Slave, synchronous mode
  UCB0I2COA = 0x48;                         // Own Address is 048h
  UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
  UCB0IE |= UCSTPIE + UCSTTIE + UCRXIE;     // Enable STT, STP & RX interrupt

  while (1)
  {
    PRxData = (unsigned char *)RxBuffer;    // Start of RX buffer
    RXByteCtr = 0;                          // Clear RX byte count
    __bis_SR_register(LPM0_bits + GIE);     // Enter LPM0, enable interrupts
                                            // Remain in LPM0 until master
                                            // finishes TX
    __no_operation();                       // Set breakpoint >>here<< and read
  }                                         // read out the RxData buffer
}

//------------------------------------------------------------------------------
// The USCI_B0 data ISR RX vector is used to move received data from the I2C
// master to the MSP430 memory.
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// The USCI_B0 state ISR TX vector is used to wake up the CPU from LPM0 in order
// to process the received data in the main program. LPM0 is only exit in case
// of a (re-)start or stop condition when actual data was received.
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
    UCB0IFG &= ~UCSTTIFG;
    break;
  case  8:                                  // Vector  8: STPIFG
    UCB0IFG &= ~UCSTPIFG;
    if (RXByteCtr)                          // Check RX byte counter
      __bic_SR_register_on_exit(LPM0_bits);
    break;
  case 10:                                  // Vector 10: RXIFG
    *PRxData++ = UCB0RXBUF;                 // Get RX'd byte into buffer
    RXByteCtr++;
    break;
  case 12: break;                           // Vector 12: TXIFG  
  default: break;
  }  
}
