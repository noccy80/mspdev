//******************************************************************************
//  MSP430F530x Demo - USCI_B0 I2C Master RX single bytes from MSP430 Slave
//
//  Description: This demo connects two MSP430's via the I2C bus. The master
//  reads from the slave. This is the MASTER CODE. The data from the slave
//  transmitter begins at 0 and increments with each transfer. The received
//  data is in R5 and is checked for validity. If the received data is
//  incorrect, the CPU is trapped and the P1.0 LED will stay on. The USCI_B0
//  RX interrupt is used to know when new data has been received.
//  ACLK = n/a, MCLK = SMCLK = BRCLK = default DCO = ~1.045MHz
//
//                                /|\  /|\
//               MSP430F5310      10k  10k     MSP430F5310
//                   slave         |    |        master
//             -----------------   |    |   -----------------
//           -|XIN  P3.0/UCB0SDA|<-|----+->|P3.0/UCB0SDA  XIN|-
//            |                 |  |       |                 | 32kHz
//           -|XOUT             |  |       |             XOUT|-
//            |     P3.1/UCB0SCL|<-+------>|P3.1/UCB0SCL     |
//            |                 |          |             P1.0|--> LED
//
//   B. Nisarga
//   Texas Instruments Inc.
//   Dec 2010
//   Built with CCSv4.2 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include <msp430f5310.h>

unsigned char RXData;
unsigned char RXCompare;

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1OUT &= ~0x01;                           // P1.0 = 0
  P1DIR |= 0x01;                            // P1.0 output
  P3SEL |= 0x03;                            // Assign I2C pins to USCI_B0
  UCB0CTL1 |= UCSWRST;                      // Enable SW reset
  UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;     // I2C Master, synchronous mode
  UCB0CTL1 = UCSSEL_2 + UCSWRST;            // Use SMCLK
  UCB0BR0 = 12;                             // fSCL = SMCLK/12 = ~100kHz
  UCB0BR1 = 0;
  UCB0I2CSA = 0x48;                         // Slave Address is 048h
  UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
  UCB0IE |= UCRXIE;                         // Enable RX interrupt
  RXCompare = 0x0;                          // Used to check incoming data

  while (1)
  {
    while (UCB0CTL1 & UCTXSTP);             // Ensure stop condition got sent
    UCB0CTL1 |= UCTXSTT;                    // I2C start condition
    while(UCB0CTL1 & UCTXSTT);              // Start condition sent?
    UCB0CTL1 |= UCTXSTP;                    // I2C stop condition
    
    __bis_SR_register(LPM0_bits + GIE);     // Enter LPM0, enable interrupts
    __no_operation();                       // For debugger
  
    if (RXData != RXCompare)                // Trap CPU if wrong
    {
      P1OUT |= 0x01;                        // P1.0 = 1
      while(1);
    }

    RXCompare++;                            // Increment correct RX value
  }
}

// USCI_B0 Data ISR
#pragma vector = USCI_B0_VECTOR
__interrupt void USCI_B0_ISR(void)
{
  switch(__even_in_range(UCB0IV,12))
  {
  case  0: break;                           // Vector  0: No interrupts
  case  2: break;                           // Vector  2: ALIFG
  case  4: break;                           // Vector  4: NACKIFG
  case  6: break;                           // Vector  6: STTIFG
  case  8: break;                           // Vector  8: STPIFG
  case 10:                                  // Vector 10: RXIFG
    RXData = UCB0RXBUF;                     // Get RX data
    __bic_SR_register_on_exit(LPM0_bits);   // Exit active CPU
    break;
  case 12: break;                           // Vector 12: TXIFG
  default: break; 
  }
}


