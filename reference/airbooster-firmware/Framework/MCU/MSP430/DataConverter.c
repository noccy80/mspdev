/**
 *  @file DataConverter.c
 *
 *  @brief MSP430 data converter definitions for the ADC10, ADC12, 
 *         DAC12, SD16, and SD24 module.
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
#include "DataConverter.h"

// PUBLIC INTERFACE
////////////////////////////////////////////////////////////////////////////////

/**
 *  @fn void InitDataConverters() 
 *
 *  @brief Initialize data converter modules.
 */
void InitDataConverters() 
{
  #ifdef __MCU_MSP430_ADC10
    InitADC10();
  #endif

  #ifdef __MCU_MSP430_ADC12
  #endif

  #ifdef __MCU_MSP430_DAC12
  #endif

  #ifdef __MCU_MSP430_SD16
  #endif

  #ifdef __MCU_MSP430_SD24
  #endif
}


// CALLBACK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/**
 *  @details Data converter module ISR extension
 */
void DataConverterISRExtension()
{
  DataConverterISRExtension1();
}