/**
 *  @file USCIA0.h
 *
 *  @brief MSP430 communication public interface definitions for USCI module
 *
 *  @version 1.0 
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
#ifndef __MCU_MSP430_USCI_H
#define __MCU_MSP430_USCI_H

#include "../../Communication.h"

// USCI MODULE
////////////////////////////////////////////////////////////////////////////////
#if defined(__MCU_MSP430_USCI)

// Global variables
extern CommunicationDataDefinition USCIA0Structure;
extern CommunicationDataBufferDefinition USCIB0Structure;
extern CommunicationDataDefinition * CommStructure[USCICOUNT];

/**
 *  @details USCIAx module registers
 */
typedef struct USCIAxModule
{
  enum
  {
    USCIA0 = 0,
    USCIA1 = 2
  } module;			// USCI_Ax module (A0, A1)
  uint8_t ucaxctl0;		// USCI_Ax control register 0
  uint8_t ucaxctl1;		// USCI_Ax control register 1
  uint8_t ucaxbr0;		// USCI_Ax baud rate control register 0
  uint8_t ucaxbr1;		// USCI_Ax baud rate control register 1
  uint8_t ucaxmctl;		// USCI_Ax modulation control register
  uint8_t ucaxstat;		// USCI_Ax status register
  uint8_t ucaxtxbuf;		// USCI_Ax transmit buffer register
  uint8_t ucaxabctl;		// USCI_Ax auto baud control register
  uint8_t ucaxirtctl;		// USCI_Ax IrDA transmit control register
  uint8_t ucaxirrctl;		// USCI_Ax IrDA receive control register
  uint8_t ucaxtxie;		// USCI_Ax transmit interrupt enable bit
  uint8_t ucaxtxifg;		// USCI_Ax transmit interrupt flag bit
  uint8_t ucaxrxie;		// USCI_Ax receive interrupt enable bit
  uint8_t ucaxrxifg;		// USCI_Ax receive interrupt flag bit
} USCIAxModule;

/**
 *  @details USCIBx module registers
 */
typedef struct USCIBxModule
{
  enum
  {
    USCIB0 = 1,
    USCIB1 = 3
  } module;			// USCI_Bx module (B0, B1)
  uint8_t ucbxctl0;		// USCI_Bx control register 0
  uint8_t ucbxctl1;		// USCI_Bx control register 1
  uint8_t ucbxbr0;		// USCI_Bx baud rate control register 0
  uint8_t ucbxbr1;		// USCI_Bx baud rate control register 1
  uint8_t ucbxstat;		// USCI_Bx status register
  uint8_t ucbxtxbuf;		// USCI_Bx transmit buffer register
  uint8_t ucbxi2cie;		// USCI_Bx I2C interrupt enable register
  uint8_t ucbxi2coa;		// USCI_Bx I2C own address register
  uint8_t ucbxi2csa;		// USCI_Bx I2C slave address register
  uint8_t ucbxtxie;		// USCI_Bx transmit interrupt enable bit
  uint8_t ucbxtxifg;		// USCI_Bx transmit interrupt flag bit
  uint8_t ucbxrxie;		// USCI_Bx receive interrupt enable bit
  uint8_t ucbxrxifg;		// USCI_Bx receive interrupt flag bit
} USCIBxModule;

typedef struct USCIPeripheral
{
  #if defined(__MCU_MSP430_USCIA0) || defined(__MCU_MSP430_USCIA1)
    USCIAxModule * pUSCIAxModule;                                               // USCI_Ax       
  #endif
  #if defined(__MCU_MSP430_USCIB0) || defined(__MCU_MSP430_USCIB1)
    USCIBxModule * pUSCIBxModule;                                               // USCI_Bx
  #endif
} USCIPeripheral;

// PUBLIC INTERFACE
////////////////////////////////////////////////////////////////////////////////

// Initialization
/**
 *  @details Initialize the USCI modules.
 */
void InitUSCI();

/**
 *  @details Initialize the USCIA0 module.
 */
void InitUSCIA0();

/**
 *  @details Initialize the USCIB0 module.
 */
void InitUSCIB0();

// Reconfiguration
/**
 *  @details Reconfigure the USCIAx module.
 */
void ReconfigureUSCIAx(USCIAxModule * pConfiguration);

/**
 *  @details Reconfigure the USCIBx module.
 */
void ReconfigureUSCIBx(USCIBxModule * pConfiguration);

// Set,Get USCI_Ax Registers
/**
 *  @details Set the value to UCAxCTL0 register.
 */
void SetUCAxCTL0Register(uint8_t module, uint8_t value);

/**
 *  @details Get the value of UCAxCTL0 register.
 */
uint8_t GetUCAxCTL0Register(uint8_t module);

/**
 *  @details Set the value to UCAxCTL1 register.
 */
void SetUCAxCTL1Register(uint8_t module, uint8_t value);

/**
 *  @details Get the value of UCAxCTL1 register.
 */
uint8_t GetUCAxCTL1Register(uint8_t module);

/**
 *  @details Set the value to UCAxBR0 register.
 */
void SetUCAxBR0Register(uint8_t module, uint8_t value);

/**
 *  @details Get the value of UCAxBR0 register.
 */
uint8_t GetUCAxBR0Register(uint8_t module);

/**
 *  @details Set the value to UCAxBR1 register.
 */
void SetUCAxBR1Register(uint8_t module, uint8_t value);

/**
 *  @details Get the value of UCAxBR1 register.
 */
uint8_t GetUCAxBR1Register(uint8_t module);

/**
 *  @details Set the value to UCAxMCTL register.
 */
void SetUCAxMCTLRegister(uint8_t module, uint8_t value);

/**
 *  @details Get the value of UCAxMCTL register.
 */
uint8_t GetUCAxMCTLRegister(uint8_t module);

/**
 *  @details Set the value to UCAxSTAT register.
 */
void SetUCAxSTATRegister(uint8_t module, uint8_t value);

/**
 *  @details Get the value of UCAxSTAT register.
 */
uint8_t GetUCAxSTATRegister(uint8_t module);

/**
 *  @details Set the value to UCAxRXBUF register.
 */
void SetUCAxRXBUFRegister(uint8_t module, uint8_t value);

/**
 *  @details Get the value of UCAxRXBUF register.
 */
uint8_t GetUCAxRXBUFRegister(uint8_t module);

/**
 *  @details Set the value to UCAxTXBUF register.
 */
void SetUCAxTXBUFRegister(uint8_t module, uint8_t value);

/**
 *  @details Get the value of UCAxTXBUF register.
 */
uint8_t GetUCAxTXBUFRegister(uint8_t module, uint8_t value);

/**
 *  @details Set the value to UCAxABCTL register.
 */
void SetUCAxABCTLRegister(uint8_t module, uint8_t value);

/**
 *  @details Get the value of UCAxABCTL register.
 */
uint8_t GetUCAxABCTLRegister(uint8_t module);

/**
 *  @details Set the value to UCAxIRTCTL register.
 */
void SetUCAxIRTCTLRegister(uint8_t module, uint8_t value);

/**
 *  @details Get the value of UCAxIRTCTL register.
 */
uint8_t GetUCAxIRTCTLRegister(uint8_t module);

/**
 *  @details Set the value to UCAxIRRCTL register.
 */
void SetUCAxIRRCTLRegister(uint8_t module, uint8_t value);

/**
 *  @details Get the value of UCAxIRRCTL register.
 */
uint8_t GetUCAxIRRCTLRegister(uint8_t module);

/**
 *  @details Set the value to UCAxTXIE bit.
 */
void SetUCAxTXIEBit(uint8_t module, uint8_t value);

/**
 *  @details Get the value of UCAxTXIE bit.
 */
uint8_t GetUCAxTXIEBit(uint8_t module);

/**
 *  @details Set the value to UCAxTXIFG bit.
 */
void SetUCAxTXIFGBit(uint8_t module, uint8_t bit);

/**
 *  @details Get the value of UCAxTXIFG bit.
 */
uint8_t GetUCAxTXIFGBit(uint8_t module);

/**
 *  @details Set the value to UCAxRXIE bit.
 */
void SetUCAxRXIEBit(uint8_t module, uint8_t bit);

/**
 *  @details Get the value of UCAxRXIE bit.
 */
uint8_t GetUCAxRXIEBit(uint8_t module);

/**
 *  @details Set the value to UCAxRXIFG bit.
 */
void SetUCAxRXIFGBit(uint8_t module, uint8_t bit);

/**
 *  @details Get the value of UCAxRXIFG bit.
 */
uint8_t GetUCAxRXIFGBit(uint8_t module);

// Set,Get USCI_Bx Registers

/**
 *  @details Set the value to UCBxTXBUF register.
 */
void SetUCBxTXBUFRegister(uint8_t module, uint8_t value);

/**
 *  @details Get the value of UCBxTXBUF bit.
 */
uint8_t GetUCBxTXBUFRegister(uint8_t module);

/**
 *  @details Set the value to UCBxTXIFG bit.
 */
void SetUCBxTXIEBit(uint8_t module, uint8_t bit);

/**
 *  @details Get the value of UCBxTXIE bit.
 */
uint8_t GetUCBxTXIEBit(uint8_t module);

/**
 *  @details Set the value to UCBxTXIFG bit.
 */
void SetUCBxTXIFGBit(uint8_t module, uint8_t bit);

/**
 *  @details Get the value of UCBxTXIFG bit.
 */
uint8_t GetUCBxTXIFGBit(uint8_t module);

/**
 *  @details Set the value to UCBxRXIE bit.
 */
void SetUCBxRXIEBit(uint8_t module, uint8_t bit);

/**
 *  @details Get the value of UCBxRXIE bit.
 */
uint8_t GetUCBxRXIEBit(uint8_t module);

/**
 *  @details Set the value to UCBxRXIFG bit.
 */
void SetUCBxRXIFGBit(uint8_t module, uint8_t bit);

/**
 *  @details Get the value of UCBxRXIFG bit
 */
uint8_t GetUCBxRXIFGBit(uint8_t module);

/**
 *  @details Write to the specified USCI module.
 */
void USCIWrite(uint8_t module, uint8_t calledfromISR);

/**
 *  @details Read from the specified USCI module.
 */
void USCIRead(uint8_t module, uint8_t calledfromISR);


// PRIVATE INTERFACE
////////////////////////////////////////////////////////////////////////////////

// NOTE: Private interface prototypes go here.

// CALLBACK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/**
 *  @details USCIA0 call back function
 */
void USCIA0Callback();

/**
 *  @details USCIB0 call back function
 */
void USCIB0Callback();

// INTERRUPT SERVICE ROUTINES
////////////////////////////////////////////////////////////////////////////////

/**
 *  @details USCI0 transmit ISR
 */
__interrupt void USCI0TXISR();

/**
 *  @details USCI0 receive ISR
 */
__interrupt void USCI0RXISR();

#endif  // USCI MODULE

#endif // __MCU_MSP430_USCI_H