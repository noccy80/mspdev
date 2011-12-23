//******************************************************************************
//  MSP-FET430P140 Demo - I2C, Master Interface to PCF8574, Read/Write
//
//  Description: I2C communication with a PCF8574 in read and write mode is
//  demonstrated. PCF8574 port P is configured with P0-P3 input, P4-P7. Read
//  P0-P3 input data is written back to Port P4-P7. Normal mode is LPM0 with
//  Timer_A CCRO interrupt used as wake up and to read PCF8574. I2C RX ready
//  interrupt is used to translate read P0-P3 data, and send back to PCF8474.
//  ACLK = n/a, MCLK = SMCLK = default DCO ~ 800k, SCL = SMCLK/10
//  //* MSP430F169 Device Required *//
//
//                                MSP430F169
//                             -----------------
//                 /|\ /|\ /|\|              XIN|-
//                 10k 10k  | |                 |
//      PCF8574     |   |   --|RST          XOUT|-
//      ---------   |   |     |                 |
// --->|P0    SDA|<-|---+---->|P3.1/SDA         |
// --->|P1       |  |         |                 |
// --->|P2       |  |         |                 |
// --->|P3    SCL|<-+---------|P3.3/SCL         |
// <---|P4       |            |                 |
// <---|P5       |            |                 |
// <---|P6       |            |                 |
// <---|P7       |            |                 |
//  +--|A0,A1,A2 |            |                 |
//  |  |         |            |                 |
// \|/
//
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************

#include  <msp430x16x.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog
  P3SEL |= 0x0a;                            // Assign I2C pins to module
  U0CTL |= I2C + SYNC;                      // Switch USART0 to I2C mode
  U0CTL &= ~I2CEN;                          // Recommended I2C init procedure
  I2CTCTL = I2CSSEL_2;                      // SMCLK
  I2CSCLH = 0x03;                           // High period of SCL
  I2CSCLL = 0x03;                           // Low period of SCL
  I2CNDAT = 0x01;                           // Transmit one byte
  I2CSA = 0x20;                             // Slave address
  U0CTL |= I2CEN;                           // Enable I2C, 7 bit addr,
  I2CIE = RXRDYIE;                          // I2C receive ready interrupt enable
  CCTL0 = CCIE;                             // CCR0 interrupt enabled
  TACTL = TASSEL_2 + MC_2;                  // SMCLK, contmode

  _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0 w/ interrupt
}

// Timer A0 interrupt service routine
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
  U0CTL |= MST;                             // Master
  I2CTCTL = I2CSTT + I2CSTP;                // Receive, ST, SP (clears MST)
}

// I2C Interrupt Vector (I2CIV) handler
#pragma vector=USART0TX_VECTOR
__interrupt void USART0 (void)
{
  unsigned int i;
  switch( I2CIV )
  {
   case 10:
   {
    i = I2CDRB;
    i = i << 4;
    i |= 0x0F;
    U0CTL |= MST;                             // Master
    I2CTCTL |= I2CTRX + I2CSTT + I2CSTP;      // Transmit, ST, SP (clears MST)
    I2CDRB = i;
    break;
    }
  }
}
