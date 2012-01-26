s#ifndef __RFM70_H__
#define __RFM70_H__

#include <spi.h>

#define RFM70_MODE_SLEEP
#define RFM70_MODE_SB1
#define RFM70_MODE_SB2
#define RFM70_MODE_TX
#define RFM70_MODE_RX

#define RFM70_ADDR_3BYTE
#define RFM70_ADDR_4BYTE
#define RFM70_ADDR_5BYTE

// RFM70 Registers
#define RFM70_REG_CONFIG      0x00
#define RFM70_REG_EN_AA       0x01
#define RFM70_REG_EN_RXADDR   0x02
#define RFM70_REG_SETUP_AW    0x03
#define RFM70_REG_SETUP_RETR  0x04
#define RFM70_REG_RF_CH       0x05
#define RFM70_REG_RF_SETUP    0x06
#define RFM70_REG_STATUS      0x07
#define RFM70_REG_OBSERVE_TX  0x08
#define RFM70_REG_CD          0x09
#define RFM70_REG_RX_ADDR_P0  0x0A
#define RFM70_REG_RX_ADDR_P1  0x0B
#define RFM70_REG_RX_ADDR_P2  0x0C
#define RFM70_REG_RX_ADDR_P3  0x0D
#define RFM70_REG_RX_ADDR_P4  0x0E
#define RFM70_REG_RX_ADDR_P5  0x0F
#define RFM70_REG_TX_ADDR     0x10
#define RFM70_REG_RX_PW_P0    0x11
#define RFM70_REG_RX_PW_P1    0x12
#define RFM70_REG_RX_PW_P2    0x13
#define RFM70_REG_RX_PW_P3    0x14
#define RFM70_REG_RX_PW_P4    0x15
#define RFM70_REG_RX_PW_P5    0x16
#define RFM70_REG_FIFO_STATUS 0x17
#define RFM70_REG_DYNPD       0x1C
#define RFM70_REG_FEATURE     0x1D 

int rfm70_initialize( RFM70 *radio,
	GPIOPIN pClock, GPIOPIN pDataInBi, GPIOPIN pDataOut,
	long options
);
int rfm70_power_state( RFM70 *radio, uint8_t state );
int rfm70_set_callback( RFM70 *radio );

unsigned int rfm70_get_register( RFM70* radio , unsigned int register);



SPI_SESSION spisess;

#endif
