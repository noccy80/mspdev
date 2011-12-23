//******************************************************************************
//  MSP-FET430P140 Demo - I2C, Slave Reads/Writes with Master, Rptd Start
//
//  Description: This example shows the repeated start condition  It talks to
//  the MSP430F169.  It first does two writes, then sends repeated start and
//  does a read, then sets STP.
//  Access ready Interrupt occurs when 2 bytes are sent by master, and then
//  master is switched to Reciever. Another ARDY Interrupt occurs when data
//  is read from I2CDRB and then a stop condition is issued.
//  The received data is in RXData and is checked for validity. If the received
//  data is incorrect, the CPU is trapped and P1.0 LED will stay on.
//
//  This is the Slave code.
//  The Master code is called fet140_i2c_16.c
//
//  ACLK = n/a, MCLK = SMCLK = I2CCLOCK = DCO ~ 800kHz
//  //* MSP430F15x, MSP430F16x Device Required *//
//
//                                 /|\  /|\
//                  MSP430F169     10k  10k     MSP430F169
//                    slave         |    |        master
//              -----------------|  |    |  -----------------
//             |             P3.1|<-|---+->|P3.1             |
//             |                 |  |      |             P1.0|-->LED
//             |                 |  |      |                 |
//             |             P3.3|<-+----->|P3.3             |
//             |                 |         |                 |
//
//
//  H. Grewal / L. Westlund
//  Texas Instruments Inc.
//  Nov 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.30A
//******************************************************************************

#include  <msp430x16x.h>

char TXData = 0;
char RXData = 0;
char TestData = 0;

void main (void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P3SEL |= 0x0A;                            // Select I2C pins
  U0CTL |= I2C + SYNC;                      // Recommended init procedure
  U0CTL &= ~I2CEN;                          // Recommended init procedure
  I2CTCTL |= I2CSSEL1;                      // SMCLK
  I2COA = 0x0048;                           // Own Address is 048h
  I2CIE = TXRDYIE+RXRDYIE;                  // Enable TXRDYIFG interrupt
  U0CTL |= I2CEN;                           // Enable I2C
  P1DIR |= 0x01;
  P1OUT = 0;

  _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0 w/ interrupt
  I2CIE &= ~TXRDYIE+RXRDYIE;                // Disable TXRDYIFG interrupt
  P1OUT |= 0x01;
  while(1);
}


// Common ISR for I2C Module
#pragma vector=USART0TX_VECTOR
__interrupt void I2C_ISR(void)
{
 switch( I2CIV )
 {
   case  2: break;                          // Arbitration lost
   case  4: break;                          // No Acknowledge
   case  6: break;                          // Own Address
   case  8: break;                          // Register Access Ready
   case 10:
     RXData = I2CDRB;                       // RX data
     if (TestData++ != RXData)
       _BIC_SR_IRQ(CPUOFF);                 // Clear LPM0
     break;                                 // Receive Ready
   case 12:                                 // Transmit Ready
     I2CDRB = TXData++;                     // Load I2CDRB and increment
     break;
   case 14: break;                          // General Call
   case 16: break;                          // Start Condition
 }
}




