//*****************************************************************************
//  MSP-FET430P140 Demo - DMA0, Rpt'd Blk, I2C Master Interface to DAC8571
//  Master = '169, Slave = DAC8571
//
//  Description: Using the DMA0 16-bit sine data is transmitted to the external
//  DAC. The DAC8571 is configured and sent continuous data without a stop or
//  repeated start condition. Data is handled in bytes by the I2C module and
//  the CPU is normally in LPM0.
//  ACLK = n/a, MCLK = SMCLK = I2CCLOCK = DCO ~ 750kHz
//  //* MSP430F169 Device Required *//
//
//                   MSP430F169                         DAC8571
//                 ---------------                   ------------
//                |            SDA|<--------------->|SDA         |
//                |     I2C    SCL|---------------->|SCL  I2C    |
//                |   MASTER      |                 |    SLAVE   |
//                |               |              GND|A0          |
//
//
//  DAC8571 I2C address = 0x4C (A0 = GND)
//
//  Z. Albus
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************

#include  <msp430x16x.h>


//------------------------------------------------------------------------------
// Flash - 16-bit Sine Lookup table with 16 steps (byte-wide format)
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

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog
  P3SEL |= 0x0A;                            // Assign I2C pins to module
  U0CTL |= TXDMAEN + I2C + SYNC;            // Enable DMA for TX, I2C mode
  U0CTL &= ~I2CEN;                          // Disable I2C
  I2CTCTL = I2CRM + I2CSSEL1;               // S/W controls data flow, SMCLK
  I2CSA = 0x4C;                             // Slave address
  U0CTL |= I2CEN;                           // Enable I2C
  DMACTL0 = DMA0TSEL_4;                     // I2CTXRDY trigger
  DMA0SA = (int) Sin_tab;                   // Source block address
  DMA0DA = (unsigned int)&I2CDRB;           // Destination single address
  DMA0SZ = 0x20;                            // Block size
  DMA0CTL = DMADT_4 + DMASRCINCR_3 + DMADSTBYTE + DMASRCBYTE + DMAEN;
                                            // Rpt, inc src, byte-byte
  U0CTL |= MST;                             // Master
  I2CTCTL |= I2CTRX + I2CSTT;               // Write, ST
  I2CDRB = 0x10;                            // Write DAC control

  _BIS_SR(LPM0_bits);                       // Enter LPM0
}