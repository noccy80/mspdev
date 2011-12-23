//******************************************************************************
//  MSP430F21x2 Demo - USCI_B0 I2C Slave TX multiple bytes to MSP430 Master
//
//  Description: This demo connects two MSP430's via the I2C bus. The slave
//  transmits to the master. This is the slave code. The interrupt driven
//  data transmission is demonstrated using the USCI_B0 TX interrupt.
//  ACLK = n/a, MCLK = SMCLK = default DCO = ~1.2MHz
//
//                                /|\  /|\
//               MSP430F21x2      10k  10k     MSP430F21x2
//                   slave         |    |        master
//             -----------------   |    |  -----------------
//           -|XIN  P3.1/UCB0SDA|<-|---+->|P3.1/UCB0SDA  XIN|-
//            |                 |  |      |                 |
//           -|XOUT             |  |      |             XOUT|-
//            |     P3.2/UCB0SCL|<-+----->|P3.2/UCB0SCL     |
//            |                 |         |                 |
//******************************************************************************
/*
 * ======== Standard MSP430 includes ========
 */
#include <msp430.h>

/*
 * ======== Grace related includes ========
 */
#include <ti/mcu/msp430/csl/CSL.h>

/*
 *  ======== main ========
 */

unsigned char *PTxData;                     // Pointer to TX data
volatile unsigned char TXByteCtr;
const unsigned char TxData[] =              // Table of data to transmit
{
  0x11,
  0x22,
  0x33,
  0x44,
  0x55
};

void main(int argc, char *argv[])
{
    CSL_init();

    while (1)
    {
      PTxData = (unsigned char *)TxData;      // Start of TX buffer
      TXByteCtr = 0;                          // Clear TX byte count
      __bis_SR_register(CPUOFF + GIE);        // Enter LPM0 w/ interrupts
                                              // Remain in LPM0 until master
                                              // finishes RX
      __no_operation();                       // Set breakpoint >>here<< and
    }                                         // read out the TXByteCtr counter
}

//------------------------------------------------------------------------------
// The USCI_B0 data ISR is used to move data from MSP430 memory to the
// I2C master. PTxData points to the next byte to be transmitted, and TXByteCtr
// keeps track of the number of bytes transmitted.
//------------------------------------------------------------------------------
void USCIAB0TX_ISR(void)
{
    UCB0TXBUF = *PTxData++;                   // Transmit data at address PTxData
    TXByteCtr++;                              // Increment TX byte counter
}

//------------------------------------------------------------------------------
// The USCI_B0 state ISR is used to wake up the CPU from LPM0 in order to do
// processing in the main program after data has been transmitted. LPM0 is
// only exit in case of a (re-)start or stop condition when actual data
// was transmitted.
//------------------------------------------------------------------------------
unsigned short USCIAB0RX_ISR(void)
{
    UCB0STAT &= ~(UCSTPIFG + UCSTTIFG);       // Clear interrupt flags
    if (TXByteCtr)                            // Check TX byte counter
      return CPUOFF;                          // Exit LPM0 if data was
    return 0;                                 // transmitted else LMP0
}
