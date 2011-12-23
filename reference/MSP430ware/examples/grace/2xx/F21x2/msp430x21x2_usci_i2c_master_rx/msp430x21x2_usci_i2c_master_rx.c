//******************************************************************************
//  MSP430F21x2 Demo - USCI_B0 I2C Master RX multiple bytes from MSP430 Slave
//
//  Description: This demo connects two MSP430's via the I2C bus. The slave
//  transmits to the master. This is the master code. It continuously
//  receives an array of data and demonstrates how to implement an I2C
//  master receiver receiving multiple bytes using the USCI_B0 TX interrupt.
//  ACLK = n/a, MCLK = SMCLK = BRCLK = default DCO = ~1.2MHz
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
//
//  Andreas Dannenberg
//  Texas Instruments Inc.
//  October 2006
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
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

unsigned char *PRxData;                     // Pointer to RX data
unsigned char RXByteCtr;
volatile unsigned char RxBuffer[128];       // Allocate 128 byte of RAM

void main(int argc, char *argv[])
{
    CSL_init();

    while (1)
    {
      PRxData = (unsigned char *)RxBuffer;    // Start of RX buffer
      RXByteCtr = 5;                          // Load RX byte counter
      while (UCB0CTL1 & UCTXSTP);             // Ensure stop condition got sent
      UCB0CTL1 |= UCTXSTT;                    // I2C start condition
      __bis_SR_register(CPUOFF + GIE);        // Enter LPM0 w/ interrupts
                                              // Remain in LPM0 until all data
                                              // is RX'd
      __no_operation();                       // Set breakpoint >>here<< and
    }                                         // read out the RxBuffer buffer
}

//-------------------------------------------------------------------------------
// The USCI_B0 data ISR is used to move received data from the I2C slave
// to the MSP430 memory. It is structured such that it can be used to receive
// any 2+ number of bytes by pre-loading RXByteCtr with the byte count.
//-------------------------------------------------------------------------------
unsigned short USCIAB0TX_ISR(void)
{
    RXByteCtr--;                              // Decrement RX byte counter
    if (RXByteCtr)
    {
      *PRxData++ = UCB0RXBUF;                 // Move RX data to address PRxData
      if (RXByteCtr == 1)                     // Only one byte left?
        UCB0CTL1 |= UCTXSTP;                  // Generate I2C stop condition
      return 0;
    }
    else
    {
      *PRxData = UCB0RXBUF;                   // Move final RX data to PRxData
      return CPUOFF;      // Exit LPM0
    }
}
