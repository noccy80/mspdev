//******************************************************************************
//   MSP-FET430P140 Demo - I2C, Master Interface to DAC8571 in Repeat Mode
//   Master = '169, Slave = DAC8571
//
//   Description: Using the I2C interrupt TXRDY, a continuous
//   sine wave is output to the external DAC using a 16-point look-up table.
//   Only one start condition is executed. Data is handled in bytes by the I2C
//   module and the CPU is normally in LPM0.
//   ACLK = n/a, MCLK = SMCLK = I2CCLOCK = DCO ~ 800kHz
//  //* MSP430F169 Device Required *//
//
//                    MSP430x169                         DAC8571
//                  ---------------                   ------------
//                 |            SDA|<--------------->|SDA         |
//                 |     I2C    SCL|---------------->|SCL  I2C    |
//                 |   MASTER      |                 |    SLAVE   |
//                 |               |              GND|A0          |
//
//
//   DAC8571 I2C address = 0x4C (A0 = GND)
//
//  Z. Albus
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************

#include  <msp430x16x.h>

//------------------------------------------------------------------------------
// Flash - 16-bit Sine Lookup table with 16 steps
//------------------------------------------------------------------------------
const char Sin_tab[32] = {
       0xFF,
       0xFF,
       0xF6,
       0x40,
       0xDA,
       0x81,
       0xB0,
       0xFA,
       0x7F,
       0xFF,
       0x4F,
       0x03,
       0x25,
       0x7C,
       0x09,
       0xBD,
       0x00,
       0x00,
       0x09,
       0xBD,
       0x25,
       0x7C,
       0x4F,
       0x03,
       0x7F,
       0xFF,
       0xB0,
       0xFA,
       0xDA,
       0x81,
       0xF6,
       0x40
};

static char i = 0;                       // Data Pointer

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;              // Stop watchdog
  P3SEL |= 0x0A;                         // Assign I2C pins to module
  U0CTL |= I2C + SYNC;                   // Switch USART0 to I2C mode
  U0CTL &= ~I2CEN;                       // Disable I2C
  I2CTCTL = I2CRM + I2CSSEL1;            // S/W controls data flow, SMCLK
  I2CSA = 0x4C;                          // Slave address
  I2CIE = TXRDYIE;                       // Enable I2C interrupts
  U0CTL |= I2CEN;                        // Enable I2C

  U0CTL |= MST;                          // Master
  I2CTCTL |= I2CTRX + I2CSTT;            // Write, ST
  I2CDRB = 0x10;                         // Write DAC control byte

  _BIS_SR(LPM0_bits + GIE);              // Enter LPM0 w/ interrupt
}

// USART0 I2C interrupt service routine
#pragma vector=USART0TX_VECTOR
__interrupt void I2C_IV (void)
{
  switch( I2CIV )
  {
  case 0x02: break;                      // ALIFG: n/a
  case 0x04: break;                      // NACKIFG: n/a
  case 0x06: break;                      // OAIFG: n/a
  case 0x08: break;                      // ARDYIFG: n/a
  case 0x0A: break;                      // RXRDYIFG: n/a
  case 0x0C: I2CDRB = Sin_tab[i];        // TXRDYIFG: Write next byte
             i = (i+1) & 0x1F;           // Increment & maintain pointer
             break;
  case 0x0E: break;                      // GCIFG: n/a
  case 0x10: break;                      // STTIFG: n/a
 }
}