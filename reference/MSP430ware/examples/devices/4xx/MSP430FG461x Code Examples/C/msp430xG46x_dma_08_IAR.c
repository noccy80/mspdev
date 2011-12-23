//******************************************************************************
//   MSP430xG461x Demo -  DMA0, Rpt'd Block, I2C Master Intf. to DAC8571, DCO
//   Master = MSP430F4619, Slave = DAC8571
//
//   Description: Using the DMA0, 16-bit sine data is transmitted to the
//   external DAC. The DAC8571 is configured and sent continuous data without
//   a stop or repeated start condition. Data is handled in bytes by the I2C
//   module and the CPU is normally in LPM0.
//   ACLK = 32kHz, MCLK = SMCLK = TACLK = BRCLK = 1MHz
//
//                MSP430xG461x                       DAC8571
//            ------------------                   ------------
//          -|XIN   P3.1/UCB0SDA|<--------------->|SDA         |
//     32kHz |      P3.2/UCB0SCL|---------------->|SCL  I2C    |
//          -|XOUT              |                 |    SLAVE   |
//           |     I2C MASTER   |              GND|A0          |
//
//
//   DAC8571 I2C address = 0x4C (A0 = GND)
//
//   A. Dannenberg/ M. Mitchell
//   Texas Instruments Inc.
//   October 2006
//   Built with IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430xG46x.h"

//------------------------------------------------------------------------------
// Sine_Tab;   16 Point 16-bit Sine Table
//------------------------------------------------------------------------------
const char Sine_Tab[32] = { 0xFF,           // MSB Word 0
                            0xFF,           // LSB
                            0xF6,           // MSB Word 1
                            0x40,           // LSB
                            0xDA,           // MSB Word 2
                            0x81,           // LSB
                            0xB0,           // MSB Word 3
                            0xFA,           // LSB
                            0x7F,           // MSB Word 4
                            0xFF,           // LSB
                            0x4F,           // MSB Word 5
                            0x03,           // LSB
                            0x25,           // MSB Word 6
                            0x7C,           // LSB
                            0x09,           // MSB Word 7
                            0xBD,           // LSB
                            0x00,           // MSB Word 8
                            0x00,           // LSB
                            0x09,           // MSB Word 9
                            0xBD,           // LSB
                            0x25,           // MSB Word 10
                            0x7C,           // LSB
                            0x4F,           // MSB Word 11
                            0x03,           // LSB
                            0x7F,           // MSB Word 12
                            0xFE,           // LSB
                            0xB0,           // MSB Word 13
                            0xFA,           // LSB
                            0xDA,           // MSB Word 14
                            0x81,           // LSB
                            0xF6,           // MSB Word 15
                            0x40
                          };

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop Watchdog Timer
  P3SEL |= 0x06;                            // Assign I2C pins to USCI_B0
  UCB0CTL1 |= UCSWRST;                      // Enable SW reset
  UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;     // I2C Master, synchronous mode
  UCB0CTL1 = UCSSEL_2 + UCSWRST;            // Use SMCLK, keep SW reset
  UCB0BR0 = 11;                             // fSCL = SMCLK/11 = 95.3kHz
  UCB0BR1 = 00;
  UCB0I2CSA = 0x04c;                        // Set slave address
  UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
  DMACTL0 = DMA0TSEL_13;                    // USCI_B0 Transmit Ready Trigger
  DMA0SA = (int)Sine_Tab;                   // Source block address
  DMA0DA = UCB0TXBUF_;                      // Destination single address
  DMA0SZ = 0x020;                           // Block size
  DMA0CTL = DMADT_4 + DMASRCINCR_3 + DMADSTBYTE + DMASRCBYTE;
                                            // Rpt, inc src, byte-byte
  UCB0CTL1 |= UCTR + UCTXSTT;               // Transmitter, Send Start Condition
  DMA0CTL |= DMAEN;                         // Enable DMA for consecutive Xfers
  UCB0TXBUF = 0x010;                        // Write DAC control
  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0
}
