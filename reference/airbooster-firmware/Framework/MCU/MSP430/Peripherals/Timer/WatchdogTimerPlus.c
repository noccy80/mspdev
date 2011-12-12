/**
 *  @file WatchdogPlus.c
 *
 *  @brief MSP430 Watchdog+ Timer module peripheral interface definitions.
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
#include "WatchdogTimerPlus.h"

// WATCHDOG PLUS MODULE
////////////////////////////////////////////////////////////////////////////////
#if defined(__MCU_MSP430_WATCHDOGPLUS)

// PUBLIC INTERFACE
////////////////////////////////////////////////////////////////////////////////
/**
 *  @fn ReconfigureWatchdogTimerPlus(WatchdogTimerPlusPeripheral * pConfiguration)
 *
 *  @brief Reconfigure Watchdog Timer Plus.
 *
 *  @param pConfiguration a WatchdogTimerPlusPeripheral structure pointer
 */
ReconfigureWatchdogTimerPlus(WatchdogTimerPlusPeripheral * pConfiguration)
{
  WDTCTL = pConfiguration->wdtctl;                                              // Watchdog timer+ control register
  NMIIE  = pConfiguration->nmiie;                                               // NMI interrupt enable bit
  NMIFFG = pConfiguration->nmiifg;                                              // NMI interrupt flag bit
  WDTIE  = pConfiguration->wdtie;                                               // Watchdog timer+ interrupt enable bit
  WDTIFG = pConfiguration->wdtifg;                                              // Watchdog timer+ interrupt flag bit
}

/**
 *  @fn uint8_t GetWDTPassword()
 *
 *  @brief This function returns the value of WDTPW register.
 * 
 *  @return an unsigned int
 */
uint8_t GetWDTPassword()
{
  return WDTPW;
}

/**
 *  @fn uint8_t GetWDTCTLRegister()
 *
 *  @brief This function returns the value of WDTCTL register.
 * 
 *  @return an unsigned int
 */
uint16_t GetWDTCTLRegister()
{
  return WDTCTL; 
}

/**
 *  @fn uint8_t GetNMIIEBit()
 *
 *  @brief This function returns the value of NMIIE bit.
 * 
 *  @return an unsigned int
 */
uint8_t GetNMIIEBit()
{
  return NMIIE;
}

/**
 *  @fn uint8_t GetNMIIFGBit()
 *
 *  @brief This function returns the value of NMIIFG bit.
 * 
 *  @return an unsigned int
 */
uint8_t GetNMIIFGBit()
{
  return NMIIFG;
}

/**
 *  @fn uint8_t GetWDTIEBit()
 *
 *  @brief This function returns the value of WDTIE bit.
 * 
 *  @return an unsigned int
 */
uint8_t GetWDTIEBit()
{
  return WDTIE;
}

/**
 *  @fn uint8_t GetWDTIFGBit()
 *
 *  @brief This function returns the value of WDTIFG bit.
 * 
 *  @return an unsigned int
 */
uint8_t GetWDTIFGBit()
{
  return WDTIFG;
}

// INTERRUPT SERVICE ROUTINES
////////////////////////////////////////////////////////////////////////////////

#pragma vector=NMI_VECTOR
__interrupt void NMIISR()
{
  __no_operation(); 
}

#pragma vector=WDT_VECTOR
__interrupt void WDTISR()
{
  __no_operation(); 
}

#endif  // WATCHDOG PLUS MODULE