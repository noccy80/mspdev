#ifndef __RFM70_H__
#define __RFM70_H__

#include <stdint.h>

/**
 * @file rfm70.h
 * @brief RFM70 Radio Module Driver for libair
 *
 * This module implements a majority of the available features of the RFM70
 * radio module. For examples, see examples/rfm70
 *
 * @author Christopher Vagnetoft (NoccyLabs)
 */

// #include <spi.h>

// Radio States
///@const Sleep mode power state
#define RFM70_MODE_SLEEP		0x00
///@const ....
#define RFM70_MODE_SB1			0x01
///@const ...
#define RFM70_MODE_SB2			0x02
///@const Transmit power state
#define RFM70_MODE_TX			0x03
///@const Active receiver power state
#define RFM70_MODE_RX			0x04

// Address size definitions
///@const Use 3-byte addressing
#define RFM70_ADDR_3BYTE		0x01
///@const Use 4-byte addressing
#define RFM70_ADDR_4BYTE		0x02
///@const Use 5-byte addressing
#define RFM70_ADDR_5BYTE		0x03

// RFM70 Registers
///@const Configuration register
#define RFM70_REG_CONFIG		0x00
///@const ...
#define RFM70_REG_EN_AA			0x01
///@const ...
#define RFM70_REG_EN_RXADDR		0x02
///@const ...
#define RFM70_REG_SETUP_AW		0x03
///@const ...
#define RFM70_REG_SETUP_RETR	0x04
///@const ...
#define RFM70_REG_RF_CH			0x05
///@const ...
#define RFM70_REG_RF_SETUP		0x06
///@const ...
#define RFM70_REG_STATUS		0x07
///@const ...
#define RFM70_REG_OBSERVE_TX	0x08
///@const ...
#define RFM70_REG_CD			0x09
///@const ...
#define RFM70_REG_RX_ADDR_P0	0x0A
///@const ...
#define RFM70_REG_RX_ADDR_P1	0x0B
///@const ...
#define RFM70_REG_RX_ADDR_P2	0x0C
///@const ...
#define RFM70_REG_RX_ADDR_P3	0x0D
///@const ...
#define RFM70_REG_RX_ADDR_P4	0x0E
///@const ...
#define RFM70_REG_RX_ADDR_P5	0x0F
///@const ...
#define RFM70_REG_TX_ADDR		0x10
///@const ...
#define RFM70_REG_RX_PW_P0		0x11
///@const ...
#define RFM70_REG_RX_PW_P1		0x12
///@const ...
#define RFM70_REG_RX_PW_P2		0x13
///@const ...
#define RFM70_REG_RX_PW_P3		0x14
///@const ...
#define RFM70_REG_RX_PW_P4		0x15
///@const ...
#define RFM70_REG_RX_PW_P5		0x16
///@const ...
#define RFM70_REG_FIFO_STATUS	0x17
///@const ...
#define RFM70_REG_DYNPD			0x1C
///@const ...
#define RFM70_REG_FEATURE		0x1D 

#ifndef GPIOPIN
#define GPIOPIN unsigned long
#endif

typedef struct _RFM70 {
    int foo;
} RFM70;

/**
 * @brief Initialize the RFM70 chipset.
 *
 * Pass a previously created RFM70 struct to this function, together
 * with the pins you wish to use.
 *
 * @param RFM70* radui The radio to initialize
 * @param GPIOPIN pClock The pin for the clock (CLKOUT)
 * @param GPIOPIN pDataInBi The pin for the input data (MISO)
 * @param GPIOPIN pDataOut The pin for the output data (MOSI)
 * @param int options Option bits
 * @return int Non-zero on failure
 */
int rfm70_initialize( RFM70 *radio,
	GPIOPIN pClock, GPIOPIN pDataInBi, GPIOPIN pDataOut,
	int options
);

/**
 * @brief Set the power state of the RFM70 chipset.
 *
 * The state should be one of the power state constants.
 *
 * @param RFM70* radio The radio to operate upon
 * @param uint8_t state The new radio state
 */
int rfm70_power_state( RFM70 *radio, uint8_t state );

/**
 * @brief Set the callback function to receive the data.
 *
 * @param RFM70* radio The radio to operate upon
 * @param (void*)(callback) The callback function
 * @return int non-zero on failure
 */
int rfm70_set_callback( RFM70 *radio, (void*)(callback) );

/**
 * @brief Read a register from the radio.
 *
 * @param RFM70* radio The radio to query
 * @param long register The register
 */
unsigned int rfm70_get_register( RFM70* radio , long register);



// SPI_SESSION spisess;

#endif
