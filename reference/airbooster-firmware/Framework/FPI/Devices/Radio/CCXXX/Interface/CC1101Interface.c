/**
 *  @file CC1101Interface.c
 *
 *  @brief CC1101 radio interface function definitions.
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
#include "CC1101Interface.h"

// CC1101 RADIO
////////////////////////////////////////////////////////////////////////////////
#if defined(__RADIO_CCXXX_CC1101) || defined(__RADIO_CCXXX_CC110L) || defined(__RADIO_CCXXX_CC2500)

// PUBLIC INTERFACE
////////////////////////////////////////////////////////////////////////////////
/**
 *  @fn void ConfigureCC1101(Radio * radio)
 *
 *  @brief This function writes the specified configuration settings to the radio 
 *         registers.
 *
 *  @param radio a Radio structure pointer
 */
void ConfigureCC1101(Radio * radio)
{
  if (radio->model == CC1101)
  {
    #if defined(__RADIO_CCXXX_CC1101)
      // Write radio settings.
      CC1101Write(radio, CCXXX_REG_IOCFG2, (uint8_t *)radio->pRadioSettings, sizeof(radio->pRadioSettings->cc1101));
      
      // Write radio channel.
      CC1101Write(radio, CCXXX_REG_CHANNR, (uint8_t *)radio->pRadioChannel, sizeof(radio->pRadioChannel->cc1101));
      
      // Write radio PA table.
      CC1101Write(radio, CCXXX_REG_PATABLE, (uint8_t *)radio->pRadioPower, sizeof(radio->pRadioPower->cc1101));
    #endif
  }
  else if (radio->model == CC110L)
  {
    #if defined(__RADIO_CCXXX_CC110L)
      // Write radio settings.
      CC1101Write(radio, CCXXX_REG_IOCFG2, (uint8_t *)radio->pRadioSettings, sizeof(radio->pRadioSettings->cc110L));
      
      // Write radio channel.
      CC1101Write(radio, CCXXX_REG_FREQ2, (uint8_t *)radio->pRadioChannel, sizeof(radio->pRadioChannel->cc110L));
      
      // Write radio PA table.
      CC1101Write(radio, CCXXX_REG_PATABLE, (uint8_t *)radio->pRadioPower, sizeof(radio->pRadioPower->cc110L));
    #endif
  }
  else if (radio->model == CC2500)
  {
    #if defined(__RADIO_CCXXX_CC2500)
      // Write radio settings.
      CC1101Write(radio, CCXXX_REG_IOCFG2, (uint8_t *)radio->pRadioSettings, sizeof(radio->pRadioSettings->cc2500));
      
      // Write radio channel.
      CC1101Write(radio, CCXXX_REG_CHANNR, (uint8_t *)radio->pRadioChannel, sizeof(radio->pRadioChannel->cc2500));
      
      // Write radio PA table.
      CC1101Write(radio, CCXXX_REG_PATABLE, (uint8_t *)radio->pRadioPower, sizeof(radio->pRadioPower->cc2500));
    #endif
  }
}

/**
 *  @fn void ResetCC1101(Radio * radio)
 *
 *  @brief This function performs a manual power-up sequence. This functionality 
 *         is currently not supported.
 *
 *  @param radio a Radio structure pointer
 */
void ResetCC1101(Radio * radio)
{
}

/**
 *  @fn void CC1101Sleep(Radio * radio)
 *
 *  @brief This function performs radio sleep operation.  
 *
 *  @param radio a Radio structure pointer
 */
void CC1101Sleep(Radio * radio)
{
  // Strobe IDLE
  CC1101Write(radio, CCXXX_STRB_SIDLE, NULL, 0);
  // Strobe SPWD register for SLEEP operation.
  CC1101Write(radio, CCXXX_STRB_SPWD, NULL, 0);
}

/**
 *  @fn void CC1101WakeUp(Radio * radio)
 *
 *  @brief This function performs radio wake up operation. CCxxxx retains most of 
 *         its registers during sleep operation. The few registers that it does 
 *         not retain must be written explicitly. When waking from sleep operation, 
 *         these registers must be rewritten to the radio. These registers are: 
 *         AGCTEST, TEST2, TEST1, TEST0, PATABLE, and FIFO.
 *
 *  @param radio a Radio structure pointer
 */
void CC1101WakeUp(Radio * radio)
{
  // Set the chip select low. 
  // This will turn on voltage regulator and crystal oscillator and will put the radio into IDLE. 
  ClearGPIOOutputPort(radio->pRadioConnection->csn[0], radio->pRadioConnection->csn[1]);
  // not sure whether to wait before writing the configuration registers.

  for(uint16_t wakeUpVar=0;wakeUpVar<5000;wakeUpVar++){
    __no_operation();
  }
  
  // Last valid calibration results are maintained so that calibration is still valid after waking
  // up from SLEEP. TX/RX FIFOs are flushed. If IOCFGx.GDOx_CFG setting is less that 0x20 and 
  // IOCFGx.GDOx_INV is 0(1), GDO0 and GDO2 pines are hardwired to 0(1), and GDO1 is hardwired to 
  // 1(0), until CSn goes low.
  // Need to rewrite the following registers:
  // AGCTEST, TEST2, TEST1, TEST0, PATABLE(contents of PATABLE are lost except the first byte(index 0))
  if (radio->model == CC1101)
  {
    #if defined(__RADIO_CCXXX_CC1101)
      // Write radio settings.
      CC1101Write(radio, CCXXX_REG_AGCTEST, (uint8_t *)(&(radio->pRadioSettings->cc1101.iocfg2) + CCXXX_REG_AGCTEST), 1);
      CC1101Write(radio, CCXXX_REG_TEST2, (uint8_t *)(&(radio->pRadioSettings->cc1101.iocfg2) + CCXXX_REG_TEST2), 1);
      CC1101Write(radio, CCXXX_REG_TEST1, (uint8_t *)(&(radio->pRadioSettings->cc1101.iocfg2) + CCXXX_REG_TEST1), 1);
      CC1101Write(radio, CCXXX_REG_TEST0, (uint8_t *)(&(radio->pRadioSettings->cc1101.iocfg2) + CCXXX_REG_TEST0), 1);
      
      // Write radio PA table.
      CC1101Write(radio, CCXXX_REG_PATABLE, (uint8_t *)radio->pRadioPower, sizeof(radio->pRadioPower->cc1101));
    #endif
  }
  else if (radio->model == CC110L)
  {
    #if defined(__RADIO_CCXXX_CC110L)
      // Write radio settings.
      CC1101Write(radio, CCXXX_REG_AGCTEST, (uint8_t *)(&(radio->pRadioSettings->cc110L.iocfg2) + CCXXX_REG_AGCTEST), 1);
      CC1101Write(radio, CCXXX_REG_TEST2, (uint8_t *)(&(radio->pRadioSettings->cc110L.iocfg2) + CCXXX_REG_TEST2), 1);
      CC1101Write(radio, CCXXX_REG_TEST1, (uint8_t *)(&(radio->pRadioSettings->cc110L.iocfg2) + CCXXX_REG_TEST1), 1);
      CC1101Write(radio, CCXXX_REG_TEST0, (uint8_t *)(&(radio->pRadioSettings->cc110L.iocfg2) + CCXXX_REG_TEST0), 1);
      
      // Write radio PA table.
      CC1101Write(radio, CCXXX_REG_PATABLE, (uint8_t *)radio->pRadioPower, sizeof(radio->pRadioPower->cc110L));
    #endif
  }
  else if (radio->model == CC2500)
  {
    #if defined(__RADIO_CCXXX_CC2500)
      // Write radio settings.
      CC1101Write(radio, CCXXX_REG_AGCTEST, (uint8_t *)(&(radio->pRadioSettings->cc2500.iocfg2) + CCXXX_REG_AGCTEST), 1);
      CC1101Write(radio, CCXXX_REG_TEST2, (uint8_t *)(&(radio->pRadioSettings->cc2500.iocfg2) + CCXXX_REG_TEST2), 1);
      CC1101Write(radio, CCXXX_REG_TEST1, (uint8_t *)(&(radio->pRadioSettings->cc2500.iocfg2) + CCXXX_REG_TEST1), 1);
      CC1101Write(radio, CCXXX_REG_TEST0, (uint8_t *)(&(radio->pRadioSettings->cc2500.iocfg2) + CCXXX_REG_TEST0), 1);
      
      // Write radio PA table.
      CC1101Write(radio, CCXXX_REG_PATABLE, (uint8_t *)radio->pRadioPower, sizeof(radio->pRadioPower->cc2500));
    #endif
  }
}

/**
 *  @fn void CC1101Write(Radio * radio, uint8_t addr, uint8_t * pBuffer, uint8_t count)
 *
 *  @brief This function performs an external write to the radio.
 *
 *  @param radio a Radio structure pointer
 *  @param addr an unsigned int
 *  @param pBuffer an unsigned integer pointer
 *  @param count an unsigned int
 */
void CC1101Write(Radio * radio, uint8_t addr, uint8_t * pBuffer, uint8_t count)
{
  uint8_t command;                                                              // Command is R/W, Burst/Single, and Address.

  // Check if this is a Strobe command
  if (addr > 0x2F && addr < 0x3E)
  {
    count = 0; 
  }

  // Format command (R/W, Burst/Single, Address[5:0]).
  if (count < 2)                                                                // Single write to register
  {
    command = addr & 0x3F;
  }
  else                                                                          // Burst write to registers
  {
    command = (addr & 0x3F) | 0x40;
  }

  // Perform an external write to radio.
  CC1101SPIExternalReadWrite(radio, command, pBuffer, count, __WRITE);
}

/**
 *  @fn uint8_t CC1101Read(Radio * radio, uint8_t addr, uint8_t * pBuffer, uint8_t count)
 *
 *  @brief This function performs an externa; read from the radio.
 *
 *  @param radio a Radio structure pointer
 *  @param addr an unsigned int
 *  @param pBuffer an unsigned integer pointer
 *  @param count an unsigned int
 *
 *  @return an unsigned int
 */
uint8_t CC1101Read(Radio * radio, uint8_t addr, uint8_t * pBuffer, uint8_t count)
{
  uint8_t command;                                                              // Command is R/W, Burst/Single, and Address.

  // Format command (R/W, Burst/Single, Address[5:0]).
  if (count < 2 && (addr <= 0x2F || addr > 0x3E))                               // Single read from register
  {
    command = addr | 0x80;
  }
  else                                                                          // Burst read from registers
  {
    command = addr | 0xC0;
  }

  // Perform an external read from radio.
  CC1101SPIExternalReadWrite(radio, command, pBuffer, count, __WRITEREAD);

  return 0;
}

// PRIVATE INTERFACE
////////////////////////////////////////////////////////////////////////////////
/**
 *  @fn void CC1101SPIExternalReadWrite(Radio * radio, uint8_t command, uint8_t * pBuffer, uint8_t count, uint8_t readwrite)
 *
 *  @brief This function performs read/write operation from/to the radio.
 *
 *  @param radio a Radio structure pointer
 *  @param command an unsigned int
 *  @param pBuffer an unsigned integer pointer
 *  @param count an unsigned int
 *  @param readwrite an unsigned int
 */
void CC1101SPIExternalReadWrite(Radio * radio, uint8_t command, uint8_t * pBuffer, uint8_t count, uint8_t readwrite)
{
  #if defined(__BOARD_LAUNCHPAD_SERIES)
    // Block the Green LED, free up the MISO line.
    __BOARD_RADIO1_SPIPIN_SEL  = 1;
    __BOARD_RADIO1_SPIPIN_SEL2 = 1;
    __BOARD_RADIO1_SPIPIN_DIR  = 0;
  #endif
    
  // Set the chip select low.
  ClearGPIOOutputPort(radio->pRadioConnection->csn[0], radio->pRadioConnection->csn[1]);

  // Write the SPI command (addr with burst & read/write).
  CommunicationReadWrite(radio->pRadioConnection->peripheral, &command, 1, __WRITE, __DISABLE_PERIPHERAL_INTERRUPTS);

  // Read/Write the SPI data.
  if((count > 0) && (pBuffer != NULL))
  {
    CommunicationReadWrite(radio->pRadioConnection->peripheral, pBuffer, count, readwrite, __DISABLE_PERIPHERAL_INTERRUPTS);
  }
  
  // Set the chip select high.
  SetGPIOOutputPort(radio->pRadioConnection->csn[0], radio->pRadioConnection->csn[1]);
  
  #if defined(__BOARD_LAUNCHPAD_SERIES)
    // Block the MISO line, free up Green LED.
    __BOARD_RADIO1_SPIPIN_SEL  = 0;
    __BOARD_RADIO1_SPIPIN_SEL2 = 0;
    __BOARD_RADIO1_SPIPIN_DIR  = 1;
  #endif
}

/**
 *  @fn void CC1101WritePATable(Radio * radio, uint8_t * pBuffer, uint8_t count)
 *
 *  @brief This function performs write operation to the PATABLE of the radio.
 *         This functionality is currently not supported.
 *
 *  @param radio a Radio structure pointer
 *  @param pBuffer an unsigned integer pointer
 *  @param count an unsigned int
 */
void CC1101WritePATable(Radio * radio, uint8_t * pBuffer, uint8_t count)
{
}

#endif  // CC1101 RADIO
