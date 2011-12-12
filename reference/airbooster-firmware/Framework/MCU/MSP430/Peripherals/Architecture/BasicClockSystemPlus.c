/**
 *  @file BasicClockSystemPlus.c
 *
 *  @brief MSP430 Basic Clock System+ module peripheral interface definitions.
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
#include "BasicClockSystemPlus.h"

// BASIC CLOCK PLUS MODULE
////////////////////////////////////////////////////////////////////////////////
#if defined(__MCU_MSP430_BASICCLOCKSYSTEMPLUS)

// PUBLIC INTERFACE
////////////////////////////////////////////////////////////////////////////////

/**
 *  @fn void InitBasicClockSystemPlus()
 * 
 *  @brief This function initializes the peripheral Basic Clock System Plus.
 */
void InitBasicClockSystemPlus()
{
  #if defined(__SET_MSP430_BASICCLOCKSYSTEMPLUS_DCOCTL)
    DCOCTL = __SET_MSP430_BASICCLOCKSYSTEMPLUS_DCOCTL;
  #endif
    
  #if defined(__SET_MSP430_BASICCLOCKSYSTEMPLUS_BCSCTL1)
    BCSCTL1 = __SET_MSP430_BASICCLOCKSYSTEMPLUS_BCSCTL1;
  #endif
    
  #if defined(__SET_MSP430_BASICCLOCKSYSTEMPLUS_BCSCTL2)
    BCSCTL2 = __SET_MSP430_BASICCLOCKSYSTEMPLUS_BCSCTL2;
  #endif
    
  #if defined(__SET_MSP430_BASICCLOCKSYSTEMPLUS_BCSCTL3)
    BCSCTL3 = __SET_MSP430_BASICCLOCKSYSTEMPLUS_BCSCTL3;
  #endif
    
  #if defined(__SET_MSP430_BASICCLOCKSYSTEMPLUS_IE1_OFIE)
    SetOFIEBit(__SET_MSP430_BASICCLOCKSYSTEMPLUS_IE1_OFIE);
  #endif
    
  #if defined(__SET_MSP430_BASICCLOCKSYSTEMPLUS_IFG1_OFIFG)
    SetOFIFGBit(__SET_MSP430_BASICCLOCKSYSTEMPLUS_IFG1_OFIFG);
  #endif
}     

/**
 *  @fn void ReconfigureBasicClockSystemPlus(BasicClockSystemPlusPeripheral * pConfiguration)
 * 
 *  @brief This function reconfigures the peripheral Basic Clock System Plus.
 */
void ReconfigureBasicClockSystemPlus(BasicClockSystemPlusPeripheral * pConfiguration)
{
  DCOCTL = pConfiguration->dcoctl;
  BCSCTL1 = pConfiguration->bcsctl1;
  BCSCTL2 = pConfiguration->bcsctl2;
  BCSCTL3 = pConfiguration->bcsctl3;
  IE1 = (IE1 & 0xFD) | ((pConfiguration->ofie & BIT0) << 1);
  IFG1 = (IFG1 & 0xFD) | ((pConfiguration->ofifg & BIT0) << 1);
}

/**
 *  @fn uint8_t GetDCOCTLRegister()
 * 
 *  @brief This function returns the value of DCOCTL register.
 *
 *  @return an unsigned int
 */
uint8_t GetDCOCTLRegister() { return DCOCTL; }

/**
 *  @fn uint8_t GetBCSCTL1Register()
 * 
 *  @brief This function returns the value of BCSCTL1 register.
 *
 *  @return an unsigned int
 */
uint8_t GetBCSCTL1Register() { return BCSCTL1; }
  
/**
 *  @fn uint8_t GetBCSCTL2Register()
 * 
 *  @brief This function returns the value of BCSCTL2 register.
 *
 *  @return an unsigned int
 */
uint8_t GetBCSCTL2Register() { return BCSCTL2; }

/**
 *  @fn uint8_t GetBCSCTL3Register()
 * 
 *  @brief This function returns the value of BCSCTL3 register.
 *
 *  @return an unsigned int
 */
uint8_t GetBCSCTL3Register() { return BCSCTL3; }

/**
 *  @fn uint8_t GetOFIEBit()
 * 
 *  @brief This function returns the value of OFIE bit from IE1 register.
 *
 *  @return an unsigned int
 */
uint8_t GetOFIEBit() { return (IE1 & OFIE) >> 1; }

/**
 *  @fn uint8_t GetOFIFGBit()
 * 
 *  @brief This function returns the value of OFIFG bit from IFG1 register.
 *
 *  @return an unsigned int
 */
uint8_t GetOFIFGBit() { return (IFG1 & OFIFG) >> 1; }

#endif  // BASIC CLOCK SYSTEM PLUS PERIPHERAL