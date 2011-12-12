/**
 *  @file ADC10.c
 *
 *  @brief MSP430 ADC10 module peripheral interface definitions.
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
#include "ADC10.h"

// ADC10 MODULE
////////////////////////////////////////////////////////////////////////////////
#if defined(__MCU_MSP430_ADC10)

// PUBLIC INTERFACE
////////////////////////////////////////////////////////////////////////////////

/**
 *  @fn void InitADC10()
 *
 *  @brief Initialize ADC10 peripheral.
 */
void InitADC10()
{
  ADC10AE0  = __SET_MSP430_ADC10_ADC10AE0;
  #if defined(ADC10AE1_)
  ADC10AE1  = __SET_MSP430_ADC10_ADC10AE1;
  #endif
  ADC10CTL1 = __SET_MSP430_ADC10_ADC10CTL1;                                     // Write CTL1 before CTL0
  ADC10CTL0 = __SET_MSP430_ADC10_ADC10CTL0;
  ADC10DTC0 = __SET_MSP430_ADC10_ADC10DTC0;
  ADC10DTC1 = __SET_MSP430_ADC10_ADC10DTC1;
  ADC10SA   = __SET_MSP430_ADC10_ADC10SA;
}

/**
 *  @fn void ReconfigureADC10(ADC10Peripheral * pConfiguration)
 *
 *  @brief Reconfigure ADC10 peripheral
 *
 *  @param pConfiguration an ADC10Peripheral structure pointer
 */
void ReconfigureADC10(ADC10Peripheral * pConfiguration)
{
  ADC10AE0  = pConfiguration->adc10ae0;
  #if defined(ADC10AE1_)
    ADC10AE1  = pConfiguration->adc10ae1;
  #endif
  ADC10CTL1 = pConfiguration->adc10ctl1;                                        // Write CTL1 before CTL0
  ADC10CTL0 = pConfiguration->adc10ctl0;
  ADC10DTC0 = pConfiguration->adc10dtc0;
  ADC10DTC1 = pConfiguration->adc10dtc1;
  ADC10SA   = pConfiguration->adc10sa;
}

/**
 * @fn uint8_t GetADC10AE0Register()
 *
 * @brief Get the value of ADC10AE0 register.
 *
 * @return an unsigned int
 */
uint8_t GetADC10AE0Register()
{
  return ADC10AE0;
}

#if defined(ADC10AE1_)
/**
 * @fn uint8_t GetADC10AE1Register()
 *
 * @brief Get the value of ADC10AE1 register.
 *
 * @return an unsigned int
 */
uint8_t GetADC10AE1Register()
{
  return ADC10AE1;
}
#endif

/**
 * @fn uint8_t GetADC10CTL0Register()
 *
 * @brief Get the value of ADC10CTL0 register.
 *
 * @return an unsigned int
 */
uint16_t GetADC10CTL0Register()
{
  return ADC10CTL0;
}

/**
 * @fn uint8_t GetADC10CTL1Register()
 *
 * @brief Get the value of ADC10CTL1 register.
 *
 * @return an unsigned int
 */
uint16_t GetADC10CTL1Register()
{
  return ADC10CTL1;
}

/**
 * @fn uint8_t GetADC10MEMRegister()
 *
 * @brief Get the value of ADC10MEM register.
 *
 * @return an unsigned int
 */
uint8_t GetADC10MEMRegister()
{
  return ADC10MEM;
}

/**
 * @fn uint8_t GetADC10DTC0Register()
 *
 * @brief Get the value of ADC10DTC0 register.
 *
 * @return an unsigned int
 */
uint8_t GetADC10DTC0Register()
{
  return ADC10DTC0;
}

/**
 * @fn uint8_t GetADC10DTC1Register()
 *
 * @brief Get the value of ADC10DTC1 register.
 *
 * @return an unsigned int
 */
uint8_t GetADC10DTC1Register()
{
  return ADC10DTC1;
}

/**
 * @fn uint8_t GetADC10SARegister()
 *
 * @brief Get the value of ADC10SA register.
 *
 * @return an unsigned int
 */
uint16_t GetADC10SARegister()
{
  return ADC10SA;
}

// INTERRUPT SERVICE ROUTINES
////////////////////////////////////////////////////////////////////////////////

#pragma vector=ADC10_VECTOR
__interrupt void ADC10ISR()
{  
  // Toggle ENC bit to arm next conversion
  ADC10CTL0 &= ~ENC;
  ADC10CTL0 |= ENC;

  // Go to DataConverter interrupt service routine extension for application access.
  DataConverterISRExtension();

  // Exit low power mode if the processor was asleep when this interrupt was triggered.
  __low_power_mode_off_on_exit();
}

#endif  // ADC10 MODULE