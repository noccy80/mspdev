/**
 *  @file TimerA.c
 *
 *  @brief MSP430 TimerA module peripheral interface definitions.
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
#include "TimerA.h"

#if defined(__MCU_MSP430_TIMERA3)

/**
 *  @fn void InitTimerA3()
 *
 *  @brief Initialize TimerA3.
 */
void InitTimerA3()
{
  #if defined(__MCU_MSP430_X2XX)
    TACTL   = __SET_MSP430_TIMERA_TACTL;                                        // Timer A control
    TAR     = __SET_MSP430_TIMERA_TAR;                                          // Timer A counter
    TACCTL0 = __SET_MSP430_TIMERA_TACCTL0;                                      // Timer A capture/compare control 0
    TACCR0  = __SET_MSP430_TIMERA_TACCR0;                                       // Timer A compare 0
    TACCTL1 = __SET_MSP430_TIMERA_TACCTL1;                                      // Timer A capture/compare control 1
    TACCR1  = __SET_MSP430_TIMERA_TACCR1;                                       // Timer A compare 1
    TACCTL2 = __SET_MSP430_TIMERA_TACCTL2;                                      // Timer A capture/compare control 2  
    TACCR2  = __SET_MSP430_TIMERA_TACCR2;                                       // Timer A compare 2
  #endif
}

/**
 *  @fn void ReconfigureTimerA(TimerAPeripheral * pConfiguration)
 *
 *  @brief Reconfigure TimerA3. This functionality is currently not supported.
 *
 *  @param pConfiguration a TimerAPeripheral structure pointer
 */
void ReconfigureTimerA(TimerAPeripheral * pConfiguration)
{
}

/**
 *  @fn uint8_t GetTimerATACTLRegister()
 *
 *  @brief This function returns the value of TACTL register.
 *
 *  @return an unsigned int
 */
uint8_t GetTimerATACTLRegister()
{
    return TACTL;
}

/**
 *  @fn uint8_t GetTimerATARRegister()
 *
 *  @brief This function returns the value of TAR register.
 *
 *  @return an unsigned int
 */
uint8_t GetTimerATARRegister()
{
    return TAR; 
}

/**
 *  @fn uint8_t GetTimerATACCTL0Register()
 *
 *  @brief This function returns the value of TACCTL0 register.
 *
 *  @return an unsigned int
 */
uint8_t GetTimerATACCTL0Register()
{
    return TACCTL0; 
}

/**
 *  @fn uint8_t GetTimerATACCTL1Register()
 *
 *  @brief This function returns the value of TACCTL1 register.
 *
 *  @return an unsigned int
 */
uint8_t GetTimerATACCTL1Register()
{
    return TACCTL1; 
}

/**
 *  @fn uint8_t GetTimerATACCTL2Register()
 *
 *  @brief This function returns the value of TACCTL2 register.
 *
 *  @return an unsigned int
 */
uint8_t GetTimerATACCTL2Register()
{
    return TACCTL2; 
}

/**
 *  @fn uint8_t GetTimerATACCR0Register()
 *
 *  @brief This function returns the value of TACCR0 register.
 *
 *  @return an unsigned int
 */
uint8_t GetTimerATACCR0Register()
{
    return TACCR0;
}

/**
 *  @fn uint8_t GetTimerATACCR1Register()
 *
 *  @brief This function returns the value of TACCR1 register.
 *
 *  @return an unsigned int
 */
uint8_t GetTimerATACCR1Register()
{
    return TACCR1;
}

/**
 *  @fn uint8_t GetTimerATACCR2Register()
 *
 *  @brief This function returns the value of TACCR2 register.
 *
 *  @return an unsigned int
 */
uint8_t GetTimerATACCR2Register()
{
    return TACCR2;
}

#pragma vector=TIMERA0_VECTOR
__interrupt void TimerA0ISR()
{
  TimerACallback(0);
  TACCTL0 &= ~CCIFG;
  __low_power_mode_off_on_exit();
}

#pragma vector=TIMERA1_VECTOR
__interrupt void TimerA1ISR()
{
  TimerACallback(TAIV);
  TACCTL1 &= ~CCIFG;
  TACCTL2 &= ~CCIFG;
  __low_power_mode_off_on_exit();
}

#endif  // Timer_A3

#if defined(__MCU_MSP430_TIMER0A3)

/**
 *  @fn void InitTimer0A3()
 *
 *  @brief Initialize Timer0A3.
 */
void InitTimer0A3()
{
  #if defined(__MCU_MSP430_X2XX)
    TACTL   = __SET_MSP430_TIMERA_TACTL;                                        // Timer A control
    TAR     = __SET_MSP430_TIMERA_TAR;                                          // Timer A counter
    TACCTL0 = __SET_MSP430_TIMERA_TACCTL0;                                      // Timer A capture/compare control 0
    TACCR0  = __SET_MSP430_TIMERA_TACCR0;                                       // Timer A compare 0
    TACCTL1 = __SET_MSP430_TIMERA_TACCTL1;                                      // Timer A capture/compare control 1
    TACCR1  = __SET_MSP430_TIMERA_TACCR1;                                       // Timer A compare 1
    TACCTL2 = __SET_MSP430_TIMERA_TACCTL2;                                      // Timer A capture/compare control 2  
    TACCR2  = __SET_MSP430_TIMERA_TACCR2;                                       // Timer A compare 2
  #endif
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void TimerA0ISR()
{
  TimerACallback(0);
  TACCTL0 &= ~CCIFG;
  __low_power_mode_off_on_exit();
}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void TimerA1ISR()
{
  TimerACallback(TAIV);
  TACCTL1 &= ~CCIFG;
  TACCTL2 &= ~CCIFG;
  __low_power_mode_off_on_exit();
}

#endif  // Timer0_A3

#if defined(__MCU_MSP430_TIMER0A5)

/**
 *  @fn void InitTimer0A5()
 *
 *  @brief Initialize Timer0A5 to a predetermined state.
 */
void InitTimer0A5()
{
  #if defined(__MCU_MSP430_X5XX)
  #endif
}

#endif  // Timer0_A5

#if defined(__MCU_MSP430_TIMER1A3)

/**
 *  @fn void InitTimer1A3()
 *
 *  @brief Initialize Timer1A3 to a predetermined state.
 */
void InitTimer1A3()
{
  #if defined(__MCU_MSP430_X2XX) || defined(__MCU_MSP430_X5XX)
  #endif
}

#endif  // Timer1_A3

#if defined(__MCU_MSP430_TIMER2A3)

/**
 *  @fn void InitTimer2A3()
 *
 *  @brief Initialize Timer2A3 to a predetermined state.
 */
void InitTimer2A3()
{
  #if defined(__MCU_MSP430_X5XX)
  #endif
}

#endif  // Timer2_A3