/* --COPYRIGHT--,BSD
 * Copyright (c) 2011, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
#ifndef __MSP430WARE_I2C_H__
#define __MSP430WARE_I2C_H__

//*****************************************************************************
//
//The following are the defines to include the required modules for this
//peripheral in msp430xgeneric.h file
//
//*****************************************************************************
#define __MSP430_HAS_USCI_Bx__

//*****************************************************************************
//
//The following are values that can be passed to the I2C_masterInit() API
//as the selectClockSource parameter.
//
//*****************************************************************************
#define I2C_CLOCKSOURCE_ACLK    UCSSEL__ACLK
#define I2C_CLOCKSOURCE_SMCLK   UCSSEL__SMCLK

//*****************************************************************************
//
//The following are values that can be passed to the I2C_enableInterrupt(),
//I2C_disableInterrupt(), I2C_clearInterrupt(), I2C_getInterruptStatus(), API
//as the mask parameter.
//
//*****************************************************************************
#define I2C_NAK_INTERRUPT                UCNACKIE
#define I2C_ARBITRATIONLOST_INTERRUPT    UCALIE
#define I2C_STOP_INTERRUPT               UCSTPIE
#define I2C_START_INTERRUPT              UCSTTIE
#define I2C_TRANSMIT_INTERRUPT           UCTXIE
#define I2C_RECEIVE_INTERRUPT            UCRXIE

//*****************************************************************************
//
//The following are values that can be passed to the I2C_masterInit() API
//as the dataRate parameter.
//
//*****************************************************************************
#define I2C_SET_DATA_RATE_400KBPS             400000
#define I2C_SET_DATA_RATE_100KBPS             100000

//*****************************************************************************
//
//The following are values that is returned by the I2C_isBusy()  and
//I2C_isBusBusy() API
//
//*****************************************************************************
#define I2C_BUS_BUSY     UCBBUSY
#define I2C_BUS_NOT_BUSY 0x00

//*****************************************************************************
//
//The following are values that can be passed to the I2C_setMode() API
//as the mode parameter.
//
//*****************************************************************************
#define I2C_TRANSMIT_MODE       UCTR
#define I2C_RECEIVE_MODE        0x00

//*****************************************************************************
//
//Prototypes for the APIs.
//
//*****************************************************************************
extern void I2C_masterInit (unsigned int baseAddress,
    unsigned char selectClockSource,
    unsigned long i2cClk,
    unsigned long dataRate);
extern void I2C_slaveInit (unsigned int baseAddress,
    unsigned char slaveAddress
    );
extern void I2C_enable (unsigned int baseAddress);
extern void I2C_disable (unsigned int baseAddress);
extern void I2C_setSlaveAddress (unsigned int baseAddress,
    unsigned char slaveAddress
    );
extern void I2C_setMode (unsigned int baseAddress,
    unsigned char mode
    );
extern void I2C_slaveDataPut (unsigned int baseAddress,
    unsigned char transmitData
    );
extern unsigned char I2C_slaveDataGet (unsigned int baseAddress);
extern unsigned char I2C_isBusBusy (unsigned int baseAddress);
extern unsigned char I2C_isBusy (unsigned int baseAddress);
extern void I2C_enableInterrupt (unsigned int baseAddress,
    unsigned char mask
    );
extern void I2C_disableInterrupt (unsigned int baseAddress,
    unsigned char mask
    );
extern void UART_clearInterruptFlag (unsigned int baseAddress,
    unsigned char mask
    );
extern unsigned char I2C_getInterruptStatus (unsigned int baseAddress,
    unsigned char mask
    );
extern void I2C_masterSendSingleByte (unsigned int baseAddress,
    unsigned char txData
    );
extern void I2C_masterMultiByteSendStart (unsigned int baseAddress,
    unsigned char txData
    );
extern void I2C_masterMultiByteSendNext (unsigned int baseAddress,
    unsigned char txData
    );
extern void I2C_masterMultiByteSendFinish (unsigned int baseAddress,
    unsigned char txData
    );
extern void I2C_masterMultiByteSendStop (unsigned int baseAddress);
extern void I2C_masterMultiByteReceiveStart (unsigned int baseAddress);
extern unsigned char I2C_masterMultiByteReceiveNext (unsigned int baseAddress);
extern unsigned char I2C_masterMultiByteReceiveFinish (
    unsigned int baseAddress
    );
extern void I2C_masterMultiByteReceiveStop (unsigned int baseAddress);
extern void I2C_masterSingleReceiveStart (unsigned int baseAddress);
extern unsigned char I2C_masterSingleReceive (unsigned int baseAddress);
extern unsigned long I2C_getReceiveBufferAddressForDMA (
    unsigned int baseAddress
    );
extern unsigned long I2C_getTransmitBufferAddressForDMA (
    unsigned int baseAddress
    );
#endif
