//******************************************************************************
//  MSP-FET430P140 Demo - I2C, Master Intf. to TMP100, Set P1.0 if Temp > 28C
//
//  Description: I2C interface to TMP100 temperature sensor in 9-bit mode.
//  Timer_A CCR0 interrupt is used as a wake up and to read the upper byte of
//  the TMP100 temperature register. If the temperature is greater than 28c,
//  P1.0 is set, else reset.  CPU is normally off and used only durring TA_ISR.
//  ACLK = n/a, MCLK = SMCLK = TACLK = I2CCLOCK = DCO~ 800k
//  //* MSP430F169 Device Required *//
//
//
//         /|\           /|\ /|\
//          |   TMP100   10k 10k     MSP430F169
//          |   -------   |   |  -----------------
//          +--|Vcc SDA|<-|---+>|P3.1         P1.0|--->
//          |  |       |  |     |                 |
//          +--|A1,A0  |  |     |                 |
//             |       |  |     |                 |
//          ---|Vss SCL|<-+-----|P3.3             |
//         \|/  -------         |                 |
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
  P1DIR |= 0x01;                            // Set P1.0 to output direction
  P3SEL |= 0x0a;                            // Assign I2C pins to module
  U0CTL |= I2C + SYNC;                      // Switch USART0 to I2C mode
  U0CTL &= ~I2CEN;                          // Recommended I2C init procedure
  I2CTCTL = I2CSSEL_2;                      // SMCLK
  I2CSCLH = 0x03;                           // High period of SCL
  I2CSCLL = 0x03;                           // Low period of SCL
  I2CNDAT = 0x01;                           // Transmit one byte
  I2CSA = 0x4e;                             // Slave address
  U0CTL |= I2CEN;                           // Enable I2C, 7 bit addr,
  CCTL0 = CCIE;                             // CCR0 interrupt enabled
  TACTL = TASSEL_2 + MC_2;                  // SMCLK, contmode

  _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0 w/ interrupt
}

// Timer A0 interrupt service routine
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
  if (I2CDRB > 0x1e) P1OUT |= 0x01;         // LED on
  else P1OUT &= ~0x01;                      // LED off
  U0CTL |= MST;                             // Master
  I2CTCTL |= I2CSTT + I2CSTP;               // Read, ST, SP (clears MST)
}
