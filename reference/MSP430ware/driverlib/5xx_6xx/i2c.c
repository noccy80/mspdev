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
//*****************************************************************************
//
//i2c.c - Driver for the I2C Module.
//
//*****************************************************************************
#include "inc/hw_types.h"
#include "driverlib/5xx_6xx/debug.h"
#include "driverlib/5xx_6xx/i2c.h"
#include "msp430xgeneric.h"

//*****************************************************************************
//
//! Initializes the I2C Master block.
//!
//! \param baseAddress is the base address of the I2C Master module.
//! \param selectClockSource is the clocksource.
//!         Valid values are
//!         \b I2C_CLOCKSOURCE_ACLK
//!         \b I2C_CLOCKSOURCE_SMCLK
//! \param i2cClk is the rate of the clock supplied to the I2C module.
//! \param dataRate set up for selecting data transfer rate.
//!         Valid values are
//!         \b I2C_SET_DATA_RATE_400KBPS
//!         \b I2C_SET_DATA_RATE_100KBPS
//!
//! This function initializes operation of the I2C Master block.  Upon
//! successful initialization of the I2C block, this function will have set the
//! bus speed for the master; however I2C module is still disabled till
//! I2C_enable is invoked
//!
//! If the parameter \e dataRate is I2C_SET_DATA_RATE_400KBPS, then the master
//! block will be set up to transfer data at 400 kbps; otherwise, it will be
//! set up to transfer data at 100 kbps.
//!
//! Modified bits are \b UCMST,UCMODE_3,\b UCSYNC of \b UCBxCTL0 register
//!                   \b UCSSELx, \b UCSWRST, of \b UCBxCTL1 register
//!                   \b UCBxBR0 and \b UCBxBR1 regsiters
//! \return None.
//
//*****************************************************************************
void I2C_masterInit (unsigned int baseAddress,
    unsigned char selectClockSource,
    unsigned long i2cClk,
    unsigned long dataRate)
{
    unsigned int preScalarValue;

    ASSERT((I2C_CLOCKSOURCE_ACLK == selectClockSource) ||
        (I2C_CLOCKSOURCE_SMCLK == selectClockSource)
        );

    ASSERT((I2C_SET_DATA_RATE_400KBPS == dataRate) ||
        (I2C_SET_DATA_RATE_100KBPS == dataRate)
        );

    //Disable the USCI module and clears the other bits of control register
    HWREGB(baseAddress + OFS_UCBxCTL1) = UCSWRST;

    /*
     * Configure as I2C master mode.
     * UCMST = Master mode
     * UCMODE_3 = I2C mode
     * UCSYNC = Synchronous mode
     */
    HWREGB(baseAddress + OFS_UCBxCTL0) = UCMST + UCMODE_3 + UCSYNC;

    //Configure I2C clock source
    HWREGB(baseAddress + OFS_UCBxCTL1) = (selectClockSource + UCSWRST );

    /*
     * Compute the clock divider that achieves the fastest speed less than or
     * equal to the desired speed.  The numerator is biased to favor a larger
     * clock divider so that the resulting clock is always less than or equal
     * to the desired clock, never greater.
     */
    preScalarValue = (unsigned short)(i2cClk / dataRate);
    HWREG(baseAddress + OFS_UCBxBRW) = preScalarValue;
}

//*****************************************************************************
//
//! Initializes the I2C Slave block.
//!
//! \param baseAddress is the base address of the I2C Slave module.
//! \param slaveAddress 7-bit slave address
//!
//! This function initializes operation of the I2C as a Slave mode.  Upon
//! successful initialization of the I2C blocks, this function will have set
//! the slave address but the I2C module is still disabled till I2C_enable
//! is invoked.
//!
//! The parameter slaveAddress is the value that will be compared against the
//! slave address sent by an I2C master.
//! Modified buts are \b UCMODE_3, \b UCSYNC of \b UCBxCTL0 register
//!                   \b UCSWRST of \b UCBxCTL1 register
//!                   \b UCBxI2COA register
//!
//! \return None.
//
//*****************************************************************************
void I2C_slaveInit (unsigned int baseAddress,
    unsigned char slaveAddress
    )
{
    //Disable the USCI module
    HWREGB(baseAddress + OFS_UCBxCTL1) |= UCSWRST;

    //Confiugre I2C as Slave and Synchronous mode
    HWREGB(baseAddress + OFS_UCBxCTL0) = UCMODE_3 + UCSYNC;

    //Set up the slave address.
    HWREG(baseAddress + OFS_UCBxI2COA) = slaveAddress;
}

//*****************************************************************************
//
//! Enables the I2C block.
//!
//! \param baseAddress is the base address of the USCI I2C module.
//!
//! This will enable operation of the I2C block.
//! Modified bits are \b UCSWRST of \b UCBxCTL1 register.
//!
//! \return None.
//
//*****************************************************************************
void I2C_enable (unsigned int baseAddress)
{
    //Reset the UCSWRST bit to enable the USCI Module
    HWREGB(baseAddress + OFS_UCBxCTL1) &= ~(UCSWRST);
}

//*****************************************************************************
//
//! Disables the I2C block.
//!
//! \param baseAddress is the base address of the USCI I2C module.
//!
//! This will disable operation of the I2C block.
//! Modified bits are \b UCSWRST of \b UCBxCTL1 register.
//!
//! \return None.
//
//*****************************************************************************
void I2C_disable (unsigned int baseAddress)
{
    //Set the UCSWRST bit to disable the USCI Module
    HWREGB(baseAddress + OFS_UCBxCTL1) |= UCSWRST;
}

//*****************************************************************************
//
//! Sets the address that the I2C Master will place on the bus.
//!
//! \param baseAddress is the base address of the I2C Master module.
//! \param slaveAddress 7-bit slave address
//!
//! This function will set the address that the I2C Master will place on the
//! bus when initiating a transaction.
//! Modified bits are \b UCSWRST of \b UCBxCTL1 register
//!                   \b UCBxI2CSA register
//!
//! \return None.
//
//*****************************************************************************
void I2C_setSlaveAddress (unsigned int baseAddress,
    unsigned char slaveAddress
    )
{
    //Disable the USCI module
    HWREGB(baseAddress + OFS_UCBxCTL1) |= UCSWRST;

    //Set the address of the slave with which the master will communicate.
    HWREG(baseAddress + OFS_UCBxI2CSA) = (slaveAddress);
}

//*****************************************************************************
//
//! Sets the mode of the I2C device
//!
//! \param baseAddress is the base address of the I2C Master module.
//! \param receive indicates whether module is in transmit/receive mode
//!
//! When the receive parameter is set to I2C_TRANSMIT_MODE, the address will
//! indicate that the I2C module is in receive mode; otherwise, the I2C module
//! is in send mode. Valid values are
//!     \b I2C_TRANSMIT_MODE
//!     \b I2C_RECEIVE_MODE [Default value]
//! Modified bits are \b UCTR, \b UCSWRST of \b UCBxCTL1 register
//!
//! \return None.
//
//*****************************************************************************
void I2C_setMode (unsigned int baseAddress,
    unsigned char mode
    )
{
    ASSERT((I2C_TRANSMIT_MODE == mode) ||
        (I2C_RECEIVE_MODE == mode)
        );

    //Disable the USCI module
    HWREGB(baseAddress + OFS_UCBxCTL1) |= UCSWRST;

    HWREGB(baseAddress + OFS_UCBxCTL1) &= ~I2C_TRANSMIT_MODE;
    HWREGB(baseAddress + OFS_UCBxCTL1) |= mode;
}

//*****************************************************************************
//
//! Transmits a byte from the I2C Module.
//!
//! \param baseAddress is the base address of the I2C module.
//! \param transmitData data to be transmitted from the I2C module
//!
//! This function will place the supplied data into I2C trasmit data register
//! to start transmission
//! Modified bit is \b UCBxTXBUF register
//!
//! \return None.
//
//*****************************************************************************
void I2C_slaveDataPut (unsigned int baseAddress,
    unsigned char transmitData
    )
{
    //Send single byte data.
    HWREGB(baseAddress + OFS_UCBxTXBUF) = transmitData;
}

//*****************************************************************************
//
//! Receives a byte that has been sent to the I2C Module.
//!
//! \param baseAddress is the base address of the I2C module.
//!
//! This function reads a byte of data from the I2C receive data Register.
//!
//! \return Returns the byte received from by the I2C module, cast as an
//! unsigned char.
//! Modified bit is \b UCBxRXBUF register
//
//*****************************************************************************
unsigned char I2C_slaveDataGet (unsigned int baseAddress)
{
    //Read a byte.
    return (HWREGB(baseAddress + OFS_UCBxRXBUF));
}

//*****************************************************************************
//
//! Indicates whether or not the I2C bus is busy.
//!
//! \param baseAddress is the base address of the I2C module.
//!
//! This function returns an indication of whether or not the I2C bus is
//! busy.This function checks the status of the bus via UCBBUSY bit in
//! UCBxSTAT register.
//!
//! \return Returns I2C_BUS_BUSY if the I2C Master is busy; otherwise, returns
//! I2C_BUS_NOT_BUSY.
//
//*****************************************************************************
unsigned char I2C_isBusBusy (unsigned int baseAddress)
{
    //Return the bus busy status.
    return (HWREGB(baseAddress + OFS_UCBxSTAT) & UCBBUSY);
}

//*****************************************************************************
//
//! Indicates whether or not the I2C module is busy.
//!
//! \param baseAddress is the base address of the I2C module.
//!
//! This function returns an indication of whether or not the I2C module is
//! busy transmitting or receiving data. This function checks if the Transmit
//! or receive flag is set.
//!
//! \return Returns I2C_BUS_BUSY if the I2C module is busy; otherwise, returns
//! I2C_BUS_NOT_BUSY.
//
//*****************************************************************************
unsigned char I2C_isBusy (unsigned int baseAddress)
{
    //Return the busy status.
    if ((HWREGB(baseAddress + OFS_UCBxIFG) & (UCTXIFG + UCRXIFG))){
        return (I2C_BUS_BUSY);
    } else   {
        return (I2C_BUS_NOT_BUSY);
    }
}

//*****************************************************************************
//
//! Enables individual I2C interrupt sources.
//!
//! \param baseAddress is the base address of the I2C module.
//! \param interruptFlags is the bit mask of the interrupt sources to be enabled.
//!
//! Enables the indicated I2C interrupt sources.  Only the sources that
//! are enabled can be reflected to the processor interrupt; disabled sources
//! have no effect on the processor.
//!
//! The mask parameter is the logical OR of any of the following:
//!
//! - \b I2C_STOP_INTERRUPT - STOP condition interrupt
//! - \b I2C_START_INTERRUPT - START condition interrupt
//! - \b I2C_RECEIVE_INTERRUPT -Receive interrupt
//! - \b I2C_TRANSMIT_INTERRUPT - Transmit interrupt
//! - \b I2C_NAK_INTERRUPT - Not-acknowledge interrupt
//! - \b I2C_ARBITRATIONLOST_INTERRUPT - Arbitration lost interrupt
//!
//! Modified registers are UCBxIFG and OFS_UCBxIE.
//!
//! \return None.
//
//*****************************************************************************
void I2C_enableInterrupt (unsigned int baseAddress,
    unsigned char mask
    )
{
    ASSERT( 0x00 == ( mask & ~(I2C_STOP_INTERRUPT +
                               I2C_START_INTERRUPT +
                               I2C_RECEIVE_INTERRUPT +
                               I2C_TRANSMIT_INTERRUPT +
                               I2C_NAK_INTERRUPT +
                               I2C_ARBITRATIONLOST_INTERRUPT))
        );

    HWREG(baseAddress + OFS_UCBxIFG) &= ~(mask);

    //Enable the interrupt masked bit
    HWREG(baseAddress + OFS_UCBxIE) |= mask;
}

//*****************************************************************************
//
//! Disables individual I2C interrupt sources.
//!
//! \param baseAddress is the base address of the I2C module.
//! \param mask is the bit mask of the interrupt sources to be
//! disabled.
//!
//! Disables the indicated I2C interrupt sources.  Only the sources that
//! are enabled can be reflected to the processor interrupt; disabled sources
//! have no effect on the processor.
//!
//! The mask parameter is the logical OR of any of the following:
//!
//! - \b I2C_STOP_INTERRUPT - STOP condition interrupt
//! - \b I2C_START_INTERRUPT - START condition interrupt
//! - \b I2C_RECEIVE_INTERRUPT -Receive interrupt
//! - \b I2C_TRANSMIT_INTERRUPT - Transmit interrupt
//! - \b I2C_NAK_INTERRUPT - Not-acknowledge interrupt
//! - \b I2C_ARBITRATIONLOST_INTERRUPT - Arbitration lost interrupt
//!
//! Modified register is \b UCBxIE.
//!
//! \return None.
//
//*****************************************************************************
void I2C_disableInterrupt (unsigned int baseAddress,
    unsigned char mask
    )
{
    ASSERT( 0x00 == ( mask & ~(I2C_STOP_INTERRUPT +
                               I2C_START_INTERRUPT +
                               I2C_RECEIVE_INTERRUPT +
                               I2C_TRANSMIT_INTERRUPT +
                               I2C_NAK_INTERRUPT +
                               I2C_ARBITRATIONLOST_INTERRUPT))
        );

    //Disable the interrupt masked bit
    HWREG(baseAddress + OFS_UCBxIE) &= ~(mask);
}

//*****************************************************************************
//
//! Clears I2C interrupt sources.
//!
//! \param baseAddress is the base address of the I2C Slave module.
//! \param mask is a bit mask of the interrupt sources to be cleared.
//!
//! The I2C interrupt source is cleared, so that it no longer asserts.
//! The highest interrupt flag is automatically cleared when an interrupt vector
//! generator is used.
//!
//! The mask parameter has the same definition as the mask
//! parameter to I2C_enableInterrupt().
//!
//! Modified register is \b UCBxIFG.
//!
//! \return None.
//
//*****************************************************************************
void I2C_clearInterrupt (unsigned int baseAddress,
    unsigned char mask
    )
{
    ASSERT( 0x00 == ( mask & ~(I2C_STOP_INTERRUPT +
                               I2C_START_INTERRUPT +
                               I2C_RECEIVE_INTERRUPT +
                               I2C_TRANSMIT_INTERRUPT +
                               I2C_NAK_INTERRUPT +
                               I2C_ARBITRATIONLOST_INTERRUPT))
        );
    //Clear the I2C interrupt source.
    HWREG(baseAddress + OFS_UCBxIFG) &= ~(mask);
}

//*****************************************************************************
//
//! Gets the current I2C interrupt status.
//!
//! \param baseAddress is the base address of the I2C module.
//! \param mask is the masked interrupt flag status to be returned.
//!
//! This returns the interrupt status for the I2C  module based on which
//! flag is passed. mask parameter can be either any of the following
//! selection.
//!
//! - \b I2C_STOP_INTERRUPT - STOP condition interrupt
//! - \b I2C_START_INTERRUPT - START condition interrupt
//! - \b I2C_RECEIVE_INTERRUPT -Receive interrupt
//! - \b I2C_TRANSMIT_INTERRUPT - Transmit interrupt
//! - \b I2C_NAK_INTERRUPT - Not-acknowledge interrupt
//! - \b I2C_ARBITRATIONLOST_INTERRUPT - Arbitration lost interrupt
//!
//! Modified register is \b UCBxIFG.
//!
//! \returns the masked status of the interrupt flag
//
//*****************************************************************************
unsigned char I2C_getInterruptStatus (unsigned int baseAddress,
    unsigned char mask
    )
{
    ASSERT( 0x00 == ( mask & ~(I2C_STOP_INTERRUPT +
                               I2C_START_INTERRUPT +
                               I2C_RECEIVE_INTERRUPT +
                               I2C_TRANSMIT_INTERRUPT +
                               I2C_NAK_INTERRUPT +
                               I2C_ARBITRATIONLOST_INTERRUPT))
        );
    //Return the interrupt status of the request masked bit.
    return (HWREGB(baseAddress + OFS_UCBxIFG) & mask);
}

//*****************************************************************************
//
//! Does single byte transmission from Master to Slave
//!
//! \param baseAddress is the base address of the I2C Master module.
//! \param txData is the data byte to be transmitted
//!
//! This function is used by the Master module to send a single byte.
//! This function
//! - Sends START
//! - Transmits the byte to the Slave
//! - Sends STOP
//!
//! Modified registers are \b UCBxIE, \b UCBxCTL1, \b UCBxIFG, \b UCBxTXBUF,
//! \b UCBxIE
//!
//! \return None.
//
//*****************************************************************************
void I2C_masterSendSingleByte (unsigned int baseAddress,
    unsigned char txData
    )
{
    //Store current TXIE status
    unsigned char txieStatus = HWREGB(baseAddress + OFS_UCBxIE) & UCTXIE;

    //Disable transmit interrupt enable
    HWREGB(baseAddress + OFS_UCBxIE) &= ~(UCTXIE);

    //Send start condition.
    HWREGB(baseAddress + OFS_UCBxCTL1) |= UCTR + UCTXSTT;

    //Poll for transmit interrupt flag.
    while (!(HWREGB(baseAddress + OFS_UCBxIFG) & UCTXIFG)) ;

    //Send single byte data.
    HWREGB(baseAddress + OFS_UCBxTXBUF) = txData;

    //Poll for transmit interrupt flag.
    while (!(HWREGB(baseAddress + OFS_UCBxIFG) & UCTXIFG)) ;

    //Send stop condition.
    HWREGB(baseAddress + OFS_UCBxCTL1) |= UCTXSTP;

    //Clear transmit interrupt flag before enabling interrupt again
    HWREGB(baseAddress + OFS_UCBxIFG) &= ~(UCTXIFG);

    //Reinstate transmit interrupt enable
    HWREGB(baseAddress + OFS_UCBxIE) |= txieStatus;
}

//*****************************************************************************
//
//! Starts multi-byte transmission from Master to Slave
//!
//! \param baseAddress is the base address of the I2C Master module.
//! \param txData is the first data byte to be transmitted
//!
//! This function is used by the Master module to send a single byte.
//! This function
//! - Sends START
//! - Transmits the first data byte of a multi-byte transmission to the Slave
//!
//! Modified registers are \b UCBxIE, \b UCBxCTL1, \b UCBxIFG, \b UCBxTXBUF,
//! \b UCBxIE
//!
//! \return None.
//
//*****************************************************************************
void I2C_masterMultiByteSendStart (unsigned int baseAddress,
    unsigned char txData
    )
{
    //Store current transmit interrupt enable
    unsigned char txieStatus = HWREGB(baseAddress + OFS_UCBxIE) & UCTXIE;


    //Disable transmit interrupt enable
    HWREGB(baseAddress + OFS_UCBxIE) &= ~(UCTXIE);

    //Send start condition.
    HWREGB(baseAddress + OFS_UCBxCTL1) |= UCTR +  UCTXSTT;

    //Poll for transmit interrupt flag.
    while (!(HWREGB(baseAddress + OFS_UCBxIFG) & UCTXIFG)) ;

    //Send single byte data.
    HWREGB(baseAddress + OFS_UCBxTXBUF) = txData;

    //Reinstate transmit interrupt enable
    HWREGB(baseAddress + OFS_UCBxIE) |= txieStatus;
}

//*****************************************************************************
//
//! Continues multi-byte transmission from Master to Slave
//!
//! \param baseAddress is the base address of the I2C Master module.
//! \param txData is the next data byte to be transmitted
//!
//! This function is used by the Master module continue each byte of a
//! multi-byte trasmission. This function
//! - Transmits each data byte of a multi-byte transmission to the Slave
//!
//! Modified registers are \b UCBxTXBUF
//!
//! \return None.
//
//*****************************************************************************
void I2C_masterMultiByteSendNext (unsigned int baseAddress,
    unsigned char txData
    )
{
    //If interrupts are not used, poll for flags
    if (!(HWREGB(baseAddress + OFS_UCBxIE) & UCTXIE)){
        //Poll for transmit interrupt flag.
        while (!(HWREGB(baseAddress + OFS_UCBxIFG) & UCTXIFG)) ;
    }

    //Send single byte data.
    HWREGB(baseAddress + OFS_UCBxTXBUF) = txData;
}

//*****************************************************************************
//
//! Finishes multi-byte transmission from Master to Slave
//!
//! \param baseAddress is the base address of the I2C Master module.
//! \param txData is the last data byte to be transmitted in a multi-byte
//! tramsission
//!
//! This function is used by the Master module to send the last byte and STOP.
//! This function
//! - Transmits the last data byte of a multi-byte transmission to the Slave
//! - Sends STOP
//!
//! Modified registers are \b UCBxTXBUF and \b UCBxCTL1.
//!
//! \return None.
//
//*****************************************************************************
void I2C_masterMultiByteSendFinish (unsigned int baseAddress,
    unsigned char txData
    )
{
    //If interrupts are not used, poll for flags
    if (!(HWREGB(baseAddress + OFS_UCBxIE) & UCTXIE)){
        //Poll for transmit interrupt flag.
        while (!(HWREGB(baseAddress + OFS_UCBxIFG) & UCTXIFG)) ;
    }

    //Send single byte data.
    HWREGB(baseAddress + OFS_UCBxTXBUF) = txData;

    //Poll for transmit interrupt flag.
    while (!(HWREGB(baseAddress + OFS_UCBxIFG) & UCTXIFG)) ;

    //Send stop condition.
    HWREGB(baseAddress + OFS_UCBxCTL1) |= UCTXSTP;
}

//*****************************************************************************
//
//! Send STOP byte at the end of a multi-byte transmission from Master to Slave
//!
//! \param baseAddress is the base address of the I2C Master module.
//!
//! This function is used by the Master module send STOP at the end of a
//! multi-byte trasmission
//!
//! This function
//! - Send a STOP after current transmission is complete
//!
//! Modified bits are \b UCTXSTP bit of \b UCBxCTL1.
//! \return None.
//
//*****************************************************************************
void I2C_masterMultiByteSendStop (unsigned int baseAddress)
{
    //If interrupts are not used, poll for flags
    if (!(HWREGB(baseAddress + OFS_UCBxIE) & UCTXIE)){
        //Poll for transmit interrupt flag.
        while (!(HWREGB(baseAddress + OFS_UCBxIFG) & UCTXIFG)) ;
    }

    //Send stop condition.
    HWREGB(baseAddress + OFS_UCBxCTL1) |= UCTXSTP;
}

//*****************************************************************************
//
//! Starts multi-byte reception at the Master end
//!
//! \param baseAddress is the base address of the I2C Master module.
//!
//! This function is used by the Master module initiate reception of a single
//! byte. This function
//! - Sends START
//!
//! Modified bits are \b UCTXSTT bit of \b UCBxCTL1.
//! \return None.
//
//*****************************************************************************
void I2C_masterMultiByteReceiveStart (unsigned int baseAddress)
{
    //Send start
    HWREGB(baseAddress + OFS_UCBxCTL1) |= UCTXSTT;
}

//*****************************************************************************
//
//! Starts multi-byte reception at the Master end one byte at a time
//!
//! \param baseAddress is the base address of the I2C Master module.
//!
//! This function is used by the Master module to receive each byte of a
//! multi-byte reception
//! This function reads currently received byte
//!
//! Modified register is \b UCBxRXBUF.
//! \return Received byte at Master end.
//
//*****************************************************************************
unsigned char I2C_masterMultiByteReceiveNext (unsigned int baseAddress)
{
    return (HWREGB(baseAddress + OFS_UCBxRXBUF));
}

//*****************************************************************************
//
//! Finishes multi-byte reception at the Master end
//!
//! \param baseAddress is the base address of the I2C Master module.
//!
//! This function is used by the Master module to initiate completion of a
//! multi-byte reception
//! This function
//! - Receives the current byte and initiates the STOP from Master to Slave
//!
//! Modified bits are \b UCTXSTP bit of \b UCBxCTL1.
//!
//! \return Received byte at Master end.
//
//*****************************************************************************
unsigned char I2C_masterMultiByteReceiveFinish (unsigned int baseAddress)
{
    //Send stop condition.
    HWREGB(baseAddress + OFS_UCBxCTL1) |= UCTXSTP;

    //Capture data from receive buffer after setting stop bit due to
    //MSP430 I2C critical timing.
    return (HWREGB(baseAddress + OFS_UCBxRXBUF));
}

//*****************************************************************************
//
//! Sends the STOP at the end of a multi-byte reception at the Master end
//!
//! \param baseAddress is the base address of the I2C Master module.
//!
//! This function is used by the Master module to initiate STOP
//!
//! Modified bits are UCTXSTP bit of UCBxCTL1.
//!
//! \return None.
//
//*****************************************************************************
void I2C_masterMultiByteReceiveStop (unsigned int baseAddress)
{
    //Send stop condition.
    HWREGB(baseAddress + OFS_UCBxCTL1) |= UCTXSTP;
}

//*****************************************************************************
//
//! Initiates a single byte Reception at the Master End
//!
//! \param baseAddress is the base address of the I2C Master module.
//!
//! This function sends a START and STOP immediately to indicate Single byte
//! reception
//!
//! Modified bits are \b UCTXSTT and \b UCTXSTP of \b UCBxCTL1, GIE
//!
//! \return None.
//
//*****************************************************************************
void I2C_masterSingleReceiveStart (unsigned int baseAddress)
{
    //local variable to store GIE status
    unsigned int gieStatus;

    //Store current SR register
    gieStatus = __get_SR_register() & GIE;

    //Disable global interrupt
    __disable_interrupt();

    //Send start condition.
    HWREGB(baseAddress + OFS_UCBxCTL1) |= UCTXSTT;

    //Poll for Start bit to complete
    while (HWREGB(baseAddress + OFS_UCBxCTL1) & UCTXSTT) ;

    //Send stop condition.
    HWREGB(baseAddress + OFS_UCBxCTL1) |= UCTXSTP;

    //Reinstate SR register
    __bis_SR_register(gieStatus);
}

//*****************************************************************************
//
//! Receives a byte that has been sent to the I2C Master Module.
//!
//! \param baseAddress is the base address of the I2C module.
//!
//! This function reads a byte of data from the I2C receive data Register.
//!
//! \return Returns the byte received from by the I2C module, cast as an
//! unsigned char.
//
//*****************************************************************************
unsigned char I2C_masterSingleReceive (unsigned int baseAddress)
{
    //Read a byte.
    return (HWREGB(baseAddress + OFS_UCBxRXBUF));
}

//*****************************************************************************
//
//! Returns the address of the RX Buffer of the I2C for the DMA module.
//!
//! \param baseAddress is the base address of the I2C module.
//!
//! Returns the address of the I2C RX Buffer. This can be used in conjunction
//! with the DMA to store the received data directly to memory.
//!
//! \return NONE
//
//*****************************************************************************
unsigned long I2C_getReceiveBufferAddressForDMA (unsigned int baseAddress)
{
    return ( baseAddress + OFS_UCBxRXBUF );
}

//*****************************************************************************
//
//! Returns the address of the TX Buffer of the I2C for the DMA module.
//!
//! \param baseAddress is the base address of the I2C module.
//!
//! Returns the address of the I2C TX Buffer. This can be used in conjunction
//! with the DMA to obtain transmitted data directly from memory.
//!
//! \return NONE
//
//*****************************************************************************
unsigned long I2C_getTransmitBufferAddressForDMA (unsigned int baseAddress)
{
    return ( baseAddress + OFS_UCBxTXBUF );
}

//*****************************************************************************
//
//Close the Doxygen group.
//! @}
//
//*****************************************************************************
