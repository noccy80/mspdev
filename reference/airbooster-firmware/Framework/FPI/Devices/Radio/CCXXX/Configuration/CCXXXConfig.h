/**
 *  @file CCXXXConfig.h
 *
 *  @brief CCXXX series configuration definitions. Defines radio model supported
 *         peripherals.
 *
 *  @version  1.0
 *
 *  @attention IMPORTANT: Your use of this Software is limited to those specific 
 *             rights granted under the terms of a software license agreement 
 *             between the user who downloaded the software, his/her employer 
 *             (which must be your employer) and Anaren (the "License"). You may
 *             not use this Software unless you agree to abide by the terms of 
 *             the License. The License limits your use, and you acknowledge,
 *             that the Software may not be modified, copied or distributed unless
 *             in connection with an authentic Anaren product. Other than for the 
 *             foregoing purpose, you may not use, reproduce, copy, prepare 
 *             derivative works of, modify, distribute, reverse engineer, decompile,
 *             perform, display or sell this Software and/or its documentation 
 *             for any purpose. 
 *             YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION
 *             ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS 
 *             OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY  WARRANTY OF 
 *             MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR 
 *             PURPOSE. IN NO EVENT SHALL ANAREN OR ITS LICENSORS BE LIABLE OR
 *             OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION,
 *             BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR 
 *             INDIRECT DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY 
 *             INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, 
 *             LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF SUBSTITUTE GOODS,
 *             TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES (INCLUDING BUT
 *             NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS. 
 */
#ifndef __RF_CCXXX_CONFIG_H
#define __RF_CCXXX_CONFIG_H

#include "../../../../../Configuration/Config.h"

// Include correct Radio header files.
#ifdef __RADIO_CCXXX_CC1101
  #include "../Model/CC1101.h"
#endif
#ifdef __RADIO_CCXXX_CC110L
  #include "../Model/CC110L.h"
#endif
#ifdef __RADIO_CCXXX_CC2500
  #include "../Model/CC2500.h"
#endif
#ifdef __RADIO_CCXXX_CC430
  #include "../Model/CC430.h"
#endif

// CCXXX 8-bit configuration registers
#define CCXXX_REG_IOCFG2              0x00      // GDO2 output pin configuration
#define CCXXX_REG_IOCFG1              0x01      // GDO1 output pin configuration
#define CCXXX_REG_IOCFG0              0x02      // GDO0 output pin configuration
#define CCXXX_REG_FIFOTHR             0x03      // RX FIFO and TX FIFO thresholds
#define CCXXX_REG_SYNC1               0x04      // Sync word, high byte
#define CCXXX_REG_SYNC0               0x05      // Sync word, low byte
#define CCXXX_REG_PKTLEN              0x06      // Packet length
#define CCXXX_REG_PKTCTRL1            0x07      // Packet automation control
#define CCXXX_REG_PKTCTRL0            0x08      // Packet automation control
#define CCXXX_REG_ADDR                0x09      // Device address
#define CCXXX_REG_CHANNR              0x0A      // Channel number
#define CCXXX_REG_FSCTRL1             0x0B      // Frequency synthesizer control
#define CCXXX_REG_FSCTRL0             0x0C      // Frequency synthesizer control
#define CCXXX_REG_FREQ2               0x0D      // Frequency control word, high byte
#define CCXXX_REG_FREQ1               0x0E      // Frequency control word, middle byte
#define CCXXX_REG_FREQ0               0x0F      // Frequency control word, low byte
#define CCXXX_REG_MDMCFG4             0x10      // Modem configuration
#define CCXXX_REG_MDMCFG3             0x11      // Modem configuration
#define CCXXX_REG_MDMCFG2             0x12      // Modem configuration
#define CCXXX_REG_MDMCFG1             0x13      // Modem configuration
#define CCXXX_REG_MDMCFG0             0x14      // Modem configuration
#define CCXXX_REG_DEVIATN             0x15      // Modem deviation setting
#define CCXXX_REG_MCSM2               0x16      // Main Radio Control State Machine configuration
#define CCXXX_REG_MCSM1               0x17      // Main Radio Control State Machine configuration
#define CCXXX_REG_MCSM0               0x18      // Main Radio Control State Machine configuration
#define CCXXX_REG_FOCCFG              0x19      // Frequency Offset Compensation configuration
#define CCXXX_REG_BSCFG               0x1A      // Bit Synchronization configuration
#define CCXXX_REG_AGCCTRL2            0x1B      // AGC control
#define CCXXX_REG_AGCCTRL1            0x1C      // AGC control
#define CCXXX_REG_AGCCTRL0            0x1D      // AGC control
#define CCXXX_REG_WOREVT1             0x1E      // High byte Event 0 timeout
#define CCXXX_REG_WOREVT0             0x1F      // Low byte Event 0 timeout
#define CCXXX_REG_WORCTRL             0x20      // Wake On Radio control
#define CCXXX_REG_FREND1              0x21      // Front end RX configuration
#define CCXXX_REG_FREND0              0x22      // Front end TX configuration
#define CCXXX_REG_FSCAL3              0x23      // Frequency synthesizer calibration
#define CCXXX_REG_FSCAL2              0x24      // Frequency synthesizer calibration
#define CCXXX_REG_FSCAL1              0x25      // Frequency synthesizer calibration
#define CCXXX_REG_FSCAL0              0x26      // Frequency synthesizer calibration
#define CCXXX_REG_RCCTRL1             0x27      // RC oscillator configuration
#define CCXXX_REG_RCCTRL0             0x28      // RC oscillator configuration
#define CCXXX_REG_FSTEST              0x29      // Frequency synthesizer calibration control
#define CCXXX_REG_PTEST               0x2A      // Production test
#define CCXXX_REG_AGCTEST             0x2B      // AGC test
#define CCXXX_REG_TEST2               0x2C      // Various test settings
#define CCXXX_REG_TEST1               0x2D      // Various test settings
#define CCXXX_REG_TEST0               0x2E      // Various test settings

// CCXXX Command strobe registers
#define CCXXX_STRB_SRES     	      0x30      // Reset chip.
#define CCXXX_STRB_SFSTXON            0x31      // Enable and calibrate frequency synthesizer (if MCSM0.FS_AUTOCAL=1).
                                                // If in RX/TX: Go to a wait state where only the synthesizer is
                                                // running (for quick RX / TX turnaround).
#define CCXXX_STRB_SXOFF              0x32      // Turn off crystal oscillator.
#define CCXXX_STRB_SCAL               0x33      // Calibrate frequency synthesizer and turn it off
                               	                // (enables quick start).
#define CCXXX_STRB_SRX                0x34      // Enable RX. Perform calibration first if coming from IDLE and
                                                // MCSM0.FS_AUTOCAL=1.
#define CCXXX_STRB_STX                0x35      // In IDLE state: Enable TX. Perform calibration first if
		                                // MCSM0.FS_AUTOCAL=1. If in RX state and CCA is enabled:
                                                // Only go to TX if channel is clear.
#define CCXXX_STRB_SIDLE              0x36      // Exit RX / TX, turn off frequency synthesizer and exit
                                                // Wake-On-Radio mode if applicable.
#define CCXXX_STRB_SAFC               0x37      // Perform AFC adjustment of the frequency synthesizer
#define CCXXX_STRB_SWOR      	      0x38      // Start automatic RX polling sequence (Wake-on-Radio)
#define CCXXX_STRB_SPWD               0x39      // Enter power down mode when CSn goes high.
#define CCXXX_STRB_SFRX               0x3A      // Flush the RX FIFO buffer.
#define CCXXX_STRB_SFTX	              0x3B      // Flush the TX FIFO buffer.
#define CCXXX_STRB_SWORRST    	      0x3C      // Reset real time clock.
#define CCXXX_STRB_SNOP       	      0x3D      // No operation. May be used to pad strobe commands to two
        	                                // bytes for simpler software.
// CCXXX Status registers
#define CCXXX_STAT_PARTNUM            0x30	// RFIC Part Number
#define CCXXX_STAT_VERSION            0x31	// RFIC Current Version Number	
#define CCXXX_STAT_FREQEST            0x32	// Frequency Offset Estimator
#define CCXXX_STAT_LQI                0x33	// Demodulator estimate for Link Quality
#define CCXXX_STAT_RSSI               0x34	// Received signal strength Indicator
#define CCXXX_STAT_MARCSTATE          0x35	// Control state machine state
#define CCXXX_STAT_WORTIME1           0x36	// High byte of WOR timer
#define CCXXX_STAT_WORTIME0           0x37	// Low byte of WOR timer
#define CCXXX_STAT_PKTSTATUS          0x38	// Current GDOx status and packet status
#define CCXXX_STAT_VCO_VC_DAC         0x39	// Current setting from PLL calibration module
#define CCXXX_STAT_TXBYTES            0x3A	// Underflow and number of bytes in the TX FIFO
#define CCXXX_STAT_RXBYTES            0x3B	// Overflow and number of bytes in the RX FIFO
#define CCXXX_STAT_RCCTRL1_STATUS     0x3C	// Last RC oscillator calibration result
#define CCXXX_STAT_RCCTRL0_STATUS     0x3D	// Last RC oscillator calibration result

// CCXXX Multi-byte registers
#define CCXXX_REG_PATABLE  	      0x3E	// Defines the PA control settings to use for each of the 
                                                // eight PA power values
#define CCXXX_REG_TXFIFO              0x3F	// Write only
#define CCXXX_REG_RXFIFO	      0x3F	// Read only

// Burst/Single access definitions
#define WRITE_SINGLE	              0x00      // Single access for write to radio
#define WRITE_BURST                   0x40      // Burst access for write to radio
#define READ_SINGLE                   0x80      // Single access for read from radio
#define READ_BURST                    0xC0      // Burst access for read from radio.

#endif	// __RF_CCXXX_CONFIG_H