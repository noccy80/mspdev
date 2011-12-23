//******************************************************************************
//  MSP-FET430P140 Demo - I2C, Master Interface to DAC8571, Write
//
//  Description: I2C communication with a DAC8571 write mode is
//  demonstrated. MSP430 writes to the DAC and increments it by
//  256 in a repetitive manner to generate a ramp
//  ACLK = n/a, MCLK = SMCLK = default DCO ~ 800k, SCL = SMCLK/10
//  //* MSP430F169 Device Required *//
//
//                                 /|\  /|\
//                  DAC8571        10k  10k     MSP430F169
//                    slave         |    |        master
//              -----------------|  |    |  -----------------
//             |             SDA |<-|---+->|P3.1         Xin |---
//             |                 |  |      |             Xout|---
//             |                 |  |      |                 |
//      GND <--|A0           SCL |<-+----->|P3.3             |
//             |                 |         |                 |
//             |                 |         |                 |
//             |              Vdd|<---+--->|Vcc              |
//             |             Vref|<---|    |                 |
//             |              GND|<------->|GND              |
//             |                 |         |                 |
//
//
//   DAC8571 I2C address = 0x4C (A0 = GND)
//
//
//  H. Grewal
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************

#include  <msp430x16x.h>

unsigned char ctlbyte = 0x10;
unsigned int DAC_Data = 0;

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Disable the Watchdog.
  P3SEL |= 0x0A;                            // Assign pins to module function
  U0CTL |= I2C + SYNC;                      // Switch USART0 to I2C mode
  U0CTL &= ~I2CEN;                          // Recommended init procedure
  I2CTCTL = I2CSSEL_2;                      // SMCLK
  I2CNDAT = 0x03;                           // Transmit Three bytes
  I2CSA = 0x4C;                             // Slave address
  U0CTL |= I2CEN;                           // Enable I2C, 7 bit addr
  I2CIE = TXRDYIE;                          // I2C receive ready interrupt enable
  U0CTL |= MST;                             // Master
  I2CTCTL |= I2CTRX + I2CSTT + I2CSTP;      // Transmit, ST, SP (clears MST)

  while(1)
  {
   _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0 w/ interrupt
   DAC_Data = DAC_Data + 256;
   while ((I2CTCTL & I2CSTP) == 0x02);       // I2C Stopped?
   U0CTL |= MST;                             // Master
   I2CTCTL |= I2CTRX + I2CSTT + I2CSTP;      // Transmit, ST, SP (clears MST)
  }
}

// I2C Interrupt Vector (I2CIV) handler
#pragma vector=USART0TX_VECTOR
__interrupt void USART0 (void)
{
  static unsigned int count = 0;            // Counter to determine CtlByte
                                            // or MSByte or LSByte Transfer
  switch( I2CIV )
  {
   case 0x0C:                               // TXRDYIFG
   {
    if (count == 0)
    {
     I2CDRB = ctlbyte;                      // Transmit Control Byte
     count ++;
    }
    else if (count == 1)
    {
     I2CDRB = DAC_Data >> 8;                // Transmit MSByte to DAC
     count ++;
    }
    else
    {
     I2CDRB = (DAC_Data & 0x00FF);          // Transmit LSByte to DAC
     count = 0;
     LPM0_EXIT;                             // CPU Active on ISR exit
    }
    break;
   }
  }
}
