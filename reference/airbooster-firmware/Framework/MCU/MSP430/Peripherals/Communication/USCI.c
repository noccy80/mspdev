/**
 *  @file USCI.c
 *
 *  @brief MSP430 USCI module peripheral interface definitions.
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
#include "USCI.h"

// USCI MODULE
////////////////////////////////////////////////////////////////////////////////
#if defined(__MCU_MSP430_USCI)

// PUBLIC INTERFACE
////////////////////////////////////////////////////////////////////////////////
/**
 *  @fn void InitUSCI() 
 *
 *  @brief Initialize the USCI peripheral.
 */
void InitUSCI()
{
  #if defined(__MCU_MSP430_USCIA0)
    InitUSCIA0();
  #endif
  #if defined(__MCU_MSP430_USCIB0)
    InitUSCIB0();
  #endif
}

/**
 *  @fn void InitUSCIA0() 
 *
 *  @brief Initialize the USCI_A0 module.
 */
void InitUSCIA0() 
{
  UCA0CTL1 = UCA0CTL1 | __SET_MSP430_USCIA0_UCA0CTL1;
  UCA0BR0 = __SET_MSP430_USCIA0_UCA0BR0;
  UCA0BR1 = __SET_MSP430_USCIA0_UCA0BR1;
  UCA0MCTL = __SET_MSP430_USCIA0_UCA0MCTL;
  UCA0CTL1 &= ~UCSWRST;	                                                        // Initialize USCI state machine
  IE2 &= ~UCA0RXIE;	                                                        // Disable USCI_A0 RX interrupt
  IFG2 &= ~(UCA0RXIFG | UCA0TXIFG);
  IE2 |= UCA0RXIE;	                                                        // Enable USCI_A0 RX interrupt
  IE2 |= UCA0TXIE;
}

// USCIAx
/**
 *  @fn uint8_t GetUCAxCTL0Register(uint8_t module)
 *
 *  @brief Get the value of UCAxCTL0 register
 *
 *  @param module an unsigned int
 * 
 *  @return an unsigned int
 */
uint8_t GetUCAxCTL0Register(uint8_t module)
{
  // USCIA0 Module
  #if defined(__MCU_MSP430_USCIA0)
    if (module == USCIA0)
      return UCA0CTL0;
  #endif
    
  // USCIA1 Module
  #if defined(__MCU_MSP430_USCIA1)
    if (module == USCIA1)
      return UCA1CTL0;
  #endif
  
  // Error: No valid module selected. Do nothing.
  return 0;
}

/**
 *  @fn uint8_t GetUCAxCTL1Register(uint8_t module)
 *
 *  @brief Get the value of UCAxCTL1 register
 *
 *  @param module an unsigned int
 * 
 *  @return an unsigned int
 */
uint8_t GetUCAxCTL1Register(uint8_t module)
{
  // USCIA0 Module
  #if defined(__MCU_MSP430_USCIA0)
    if (module == USCIA0)
      return UCA0CTL1;
  #endif
    
  // USCIA1 Module
  #if defined(__MCU_MSP430_USCIA1)
    if (module == USCIA1)
      return UCA1CTL1;
  #endif
  
  // Error: No valid module selected. Do nothing.
  return 0;
}

/**
 *  @fn uint8_t GetUCAxBR0Register(uint8_t module)
 *
 *  @brief Get the value of UCAxBR0 register
 *
 *  @param module an unsigned int
 * 
 *  @return an unsigned int
 */
uint8_t GetUCAxBR0Register(uint8_t module)
{
  // USCIA0 Module
  #if defined(__MCU_MSP430_USCIA0)
    if (module == USCIA0)
      return UCA0BR0;
  #endif
    
  // USCIA1 Module
  #if defined(__MCU_MSP430_USCIA1)
    if (module == USCIA1)
      return UCA1BR0;
  #endif
  
  // Error: No valid module selected. Do nothing.
  return 0;
}

/**
 *  @fn uint8_t GetUCAxBR1Register(uint8_t module)
 *
 *  @brief Get the value of UCAxBR1 register
 *
 *  @param module an unsigned int
 * 
 *  @return an unsigned int
 */
uint8_t GetUCAxBR1Register(uint8_t module)
{
  // USCIA0 Module
  #if defined(__MCU_MSP430_USCIA0)
    if (module == USCIA0)
      return UCA0BR1;
  #endif
    
  // USCIA1 Module
  #if defined(__MCU_MSP430_USCIA1)
    if (module == USCIA1)
      return UCA1BR1;
  #endif
  
  // Error: No valid module selected. Do nothing.
  return 0;
}

/**
 *  @fn uint8_t GetUCAxMCTLRegister(uint8_t module)
 *
 *  @brief Get the value of UCAxMCTL register
 *
 *  @param module an unsigned int
 * 
 *  @return an unsigned int
 */
uint8_t GetUCAxMCTLRegister(uint8_t module)
{
  // USCIA0 Module
  #if defined(__MCU_MSP430_USCIA0)
    if (module == USCIA0)
      return UCA0MCTL;
  #endif
    
  // USCIA1 Module
  #if defined(__MCU_MSP430_USCIA1)
    if (module == USCIA1)
      return UCA1MCTL;
  #endif
  
  // Error: No valid module selected. Do nothing.
  return 0;
}

/**
 *  @fn uint8_t GetUCAxSTATRegister(uint8_t module)
 *
 *  @brief Get the value of UCAxSTAT register
 *
 *  @param module an unsigned int
 * 
 *  @return an unsigned int
 */
uint8_t GetUCAxSTATRegister(uint8_t module)
{
  // USCIA0 Module
  #if defined(__MCU_MSP430_USCIA0)
    if (module == USCIA0)
      return UCA0STAT;
  #endif
    
  // USCIA1 Module
  #if defined(__MCU_MSP430_USCIA1)
    if (module == USCIA1)
      return UCA1STAT;
  #endif
  
  // Error: No valid module selected. Do nothing.
  return 0;
}

/**
 *  @fn uint8_t GetUCAxRXBUFRegister(uint8_t module)
 *
 *  @brief Get the value of UCAxRXBUF register
 *
 *  @param module an unsigned int
 * 
 *  @return an unsigned int
 */
uint8_t GetUCAxRXBUFRegister(uint8_t module)
{
  // USCIA0 Module
  #if defined(__MCU_MSP430_USCIA0)
    if (module == USCIA0)
      return UCA0RXBUF;
  #endif
    
  // USCIA1 Module
  #if defined(__MCU_MSP430_USCIA1)
    if (module == USCIA1)
      return UCA1RXBUF;
  #endif
  
  // Error: No valid module selected. Do nothing.
  return 0;
}

/**
 *  @fn uint8_t SetUCAxTXBUFRegister(uint8_t module)
 *
 *  @brief Set the value to UCAxTXBUF register
 *
 *  @param module an unsigned int
 *  @param value an unsigned int
 */
void SetUCAxTXBUFRegister(uint8_t module, uint8_t value)
{
  // USCIA0 Module
  #if defined(__MCU_MSP430_USCIA0)
    if (module == USCIA0)
      UCA0TXBUF = value;
  #endif
    
  // USCIA1 Module
  #if defined(__MCU_MSP430_USCIA1)
    if (module == USCIA1)
      UCA1TXBUF = value;
  #endif
}

/**
 *  @fn uint8_t GetUCAxABCTLRegister(uint8_t module)
 *
 *  @brief Get the value of UCAxABCTL register
 *
 *  @param module an unsigned int
 * 
 *  @return an unsigned int
 */
uint8_t GetUCAxABCTLRegister(uint8_t module)
{
  // USCIA0 Module
  #if defined(__MCU_MSP430_USCIA0)
    if (module == USCIA0)
      return UCA0ABCTL;
  #endif
    
  // USCIA1 Module
  #if defined(__MCU_MSP430_USCIA1)
    if (module == USCIA1)
      return UCA1ABCTL;
  #endif
  
  // Error: No valid module selected. Do nothing.
  return 0;
}

/**
 *  @fn uint8_t GetUCAxIRTCTLRegister(uint8_t module)
 *
 *  @brief Get the value of UCAxIRTCTL register
 *
 *  @param module an unsigned int
 * 
 *  @return an unsigned int
 */
uint8_t GetUCAxIRTCTLRegister(uint8_t module)
{
  // USCIA0 Module
  #if defined(__MCU_MSP430_USCIA0)
    if (module == USCIA0)
      return UCA0IRTCTL;
  #endif
    
  // USCIA1 Module
  #if defined(__MCU_MSP430_USCIA1)
    if (module == USCIA1)
      return UCA1IRTCTL;
  #endif
  
  // Error: No valid module selected. Do nothing.
  return 0;
}

/**
 *  @fn uint8_t GetUCAxIRRCTLRegister(uint8_t module)
 *
 *  @brief Get the value of UCAxIRRCTL register
 *
 *  @param module an unsigned int
 * 
 *  @return an unsigned int
 */
uint8_t GetUCAxIRRCTLRegister(uint8_t module)
{
  // USCIA0 Module
  #if defined(__MCU_MSP430_USCIA0)
    if (module == USCIA0)
      return UCA0IRRCTL;
  #endif
    
  // USCIA1 Module
  #if defined(__MCU_MSP430_USCIA1)
    if (module == USCIA1)
      return UCA1IRRCTL;
  #endif
  
  // Error: No valid module selected. Do nothing.
  return 0;
}

/**
 *  @fn uint8_t GetUCAxTXIEBit(uint8_t module)
 *
 *  @brief Get the value of UCAxTXIE bit
 *
 *  @param module an unsigned int
 * 
 *  @return an unsigned int
 */
uint8_t GetUCAxTXIEBit(uint8_t module)
{
  // USCIA0 Module
  #if defined(__MCU_MSP430_USCIA0)
    if (module == USCIA0)
      return (IE2 & UCA0TXIE) >> 1;
  #endif
    
  // USCIA1 Module
  #if defined(__MCU_MSP430_USCIA1)
    if (module == USCIA1)
      return (UC1IE & UCA1TXIE) >> 1;
  #endif
  
  // Error: No valid module selected. Do nothing.
  return 0;
}

/**
 *  @fn void SetUCAxTXIEBit(uint8_t module, uint8_t bit)
 *
 *  @brief Set the value to UCAxTXIE bit
 *
 *  @param module an unsigned int
 *  @param bit an unsigned int
 */
void SetUCAxTXIEBit(uint8_t module, uint8_t bit)
{
  // USCIA0 Module
  #if defined(__MCU_MSP430_USCIA0)
    if (module == USCIA0)
      IE2 =  (IE2 & ~BIT1) | ((bit << 1) & UCA0TXIE);
  #endif
    
  // USCIA1 Module
  #if defined(__MCU_MSP430_USCIA1)
    if (module == USCIA1)
      UC1IE = (UC1IE & ~BIT1) | ((bit << 1) & UCA1TXIE));
  #endif
}

/**
 *  @fn uint8_t GetUCAxTXIFGBit(uint8_t module)
 *
 *  @brief Get the value of UCAxTXIFG bit
 *
 *  @param module an unsigned int
 * 
 *  @return an unsigned int
 */
uint8_t GetUCAxTXIFGBit(uint8_t module)
{
  // USCIA0 Module
  #if defined(__MCU_MSP430_USCIA0)
    if (module == USCIA0)
      return (IFG2 & UCA0TXIFG) >> 1;
  #endif
    
  // USCIA1 Module
  #if defined(__MCU_MSP430_USCIA1)
    if (module == USCIA1)
      return (UC1IFG & UCA0TXIFG) >> 1;
  #endif
  
  // Error: No valid module selected. Do nothing.
  return 0;
}

/**
 *  @fn void SetUCAxTXIFGBit(uint8_t module, uint8_t bit)
 *
 *  @brief Set the value to UCAxTXIFG bit
 *
 *  @param module an unsigned int
 *  @param bit an unsigned int
 */
void SetUCAxTXIFGBit(uint8_t module, uint8_t bit)
{
  // USCIA0 Module
  #if defined(__MCU_MSP430_USCIA0)
    if (module == USCIA0)
      IFG2 = (IFG2 & ~BIT1) | ((bit << 1) & UCA0TXIFG);
  #endif
    
  // USCIA1 Module
  #if defined(__MCU_MSP430_USCIA1)
    if (module == USCIA1)
      UC1IFG = (UC1IFG & ~BIT1) | ((bit << 1) & UCA1TXIFG);
  #endif
}

/**
 *  @fn uint8_t GetUCAxRXIEBit(uint8_t module)
 *
 *  @brief Get the value of UCAxRXIE bit
 *
 *  @param module an unsigned int
 * 
 *  @return an unsigned int
 */
uint8_t GetUCAxRXIEBit(uint8_t module)
{
  // USCIA0 Module
  #if defined(__MCU_MSP430_USCIA0)
    if (module == USCIA0)
      return (IE2 & UCA0RXIE) >> 0;
  #endif
    
  // USCIA1 Module
  #if defined(__MCU_MSP430_USCIA1)
    if (module == USCIA1)
      return (UC1IE & UCA1RXIE) >> 0;
  #endif
  
  // Error: No valid module selected. Do nothing.
  return 0;
}

/**
 *  @fn void SetUCAxRXIEBit(uint8_t module, uint8_t bit)
 *
 *  @brief Set the value to UCAxRXIE bit
 *
 *  @param module an unsigned int
 *  @param bit an unsigned int
 */
void SetUCAxRXIEBit(uint8_t module, uint8_t bit)
{
  // USCIA0 Module
  #if defined(__MCU_MSP430_USCIA0)
    if (module == USCIA0)
      IE2 =  (IE2 & ~BIT0) | ((bit << 0) & UCA0RXIE);
  #endif
    
  // USCIA1 Module
  #if defined(__MCU_MSP430_USCIA1)
    if (module == USCIA1)
      UC1IE = (UC1IE & ~BIT0) | ((bit << 0) & UCA1RXIE));
  #endif
}

/**
 *  @fn uint8_t GetUCAxRXIFGBit(uint8_t module)
 *
 *  @brief Get the value of UCAxRXIFG bit
 *
 *  @param module an unsigned int
 * 
 *  @return an unsigned int
 */
uint8_t GetUCAxRXIFGBit(uint8_t module)
{
  // USCIA0 Module
  #if defined(__MCU_MSP430_USCIA0)
    if (module == USCIA0)
      return (IFG2 & UCA0RXIFG) >> 0;
  #endif
    
  // USCIA1 Module
  #if defined(__MCU_MSP430_USCIA1)
    if (module == USCIA1)
      return (UC1IFG & UCA1RXIFG) >> 0;
  #endif
  
  // Error: No valid module selected. Do nothing.
  return 0;
}

/**
 *  @fn void SetUCAxRXIFGBit(uint8_t module, uint8_t bit)
 *
 *  @brief Set the value to UCAxRXIFG bit
 *
 *  @param module an unsigned int
 *  @param bit an unsigned int
 */
void SetUCAxRXIFGBit(uint8_t module, uint8_t bit)
{
  // USCIA0 Module
  #if defined(__MCU_MSP430_USCIA0)
    if (module == USCIA0)
      IFG2 = (IFG2 & ~BIT0) | ((bit << 0) & UCA0RXIFG);
  #endif
    
  // USCIA1 Module
  #if defined(__MCU_MSP430_USCIA1)
    if (module == USCIA1)
      UC1IFG = (UC1IFG & ~BIT0) | ((bit << 0) & UCA1RXIFG);
  #endif
}

// USCIBx
/**
 *  @fn void InitUSCIB0() 
 *
 *  @brief Initialize the USCI_B0 module.
 */
void InitUSCIB0() 
{
  UCB0CTL0 = __SET_MSP430_USCIB0_UCB0CTL0;  // 3-pin, 8-bit SPI master
  UCB0CTL1 = UCSWRST | __SET_MSP430_USCIB0_UCB0CTL1;  // SMCLK
  UCB0BR0 = __SET_MSP430_USCIB0_UCB0BR0;    // Division factor of the USCI clock source BRCLK ( = SMCLK)
  UCB0BR1 = __SET_MSP430_USCIB0_UCB0BR1;
  UCB0CTL1 &= ~UCSWRST;                     // Initialize USCI state machine
  IFG2 &= ~(UCB0RXIFG | UCB0TXIFG);         // Clear USCI_A RX and TX interrupt flags
  IE2 |= UCB0RXIE;                          // Enable USCI_A RX and TX interrupt
  IE2 |= UCB0TXIE;
}

/**
 *  @fn uint8_t GetUCBxRXBUFRegister(uint8_t module)
 *
 *  @brief Get the value of UCBxRXBUF register
 *
 *  @param module an unsigned int
 * 
 *  @return an unsigned int
 */
uint8_t GetUCBxRXBUFRegister(uint8_t module)
{
  // USCIA0 Module
  #if defined(__MCU_MSP430_USCIB0)
    if (module == USCIB0)
      return UCB0RXBUF;
  #endif
    
  // USCIA1 Module
  #if defined(__MCU_MSP430_USCIB1)
    if (module == USCIB1)
      return UCB1RXBUF;
  #endif
  
  // Error: No valid module selected. Do nothing.
  return 0;
}

/**
 *  @fn uint8_t GetUCBxTXIEBit(uint8_t module)
 *
 *  @brief Get the value of UCBxTXIE bit
 *
 *  @param module an unsigned int
 * 
 *  @return an unsigned int
 */
uint8_t GetUCBxTXIEBit(uint8_t module)
{
  // USCIB0 Module
  #if defined(__MCU_MSP430_USCIB0)
    if (module == USCIB0)
      return (IE2 & UCB0TXIE) >> 3;
  #endif
    
  // USCIB1 Module
  #if defined(__MCU_MSP430_USCIB1)
    if (module == USCIB1)
      return (UC1IE & UCB1TXIE) >> 3;
  #endif
  
  // Error: No valid module selected. Do nothing.
  return 0;
}

/**
 *  @fn void SetUCBxTXIEBit(uint8_t module, uint8_t bit)
 *
 *  @brief Set the value to UCBxTXIE bit
 *
 *  @param module an unsigned int
 *  @param bit an unsigned int
 */
void SetUCBxTXIEBit(uint8_t module, uint8_t bit)
{
  // USCIB0 Module
  #if defined(__MCU_MSP430_USCIB0)
    if (module == USCIB0)
      IE2 =  (IE2 & ~BIT3) | ((bit << 3) & UCB0TXIE);
  #endif
    
  // USCIB1 Module
  #if defined(__MCU_MSP430_USCIB1)
    if (module == USCIB1)
      UC1IE = (UC1IE & ~BIT3) | ((bit << 3) & UCB1TXIE));
  #endif
}

/**
 *  @fn uint8_t GetUCBxTXIFGBit(uint8_t module)
 *
 *  @brief Get the value of UCBxTXIFG bit
 *
 *  @param module an unsigned int
 * 
 *  @return an unsigned int
 */
uint8_t GetUCBxTXIFGBit(uint8_t module)
{
  // USCIB0 Module
  #if defined(__MCU_MSP430_USCIB0)
    if (module == USCIB0)
      return (IFG2 & UCB0TXIFG) >> 3;
  #endif
    
  // USCIB1 Module
  #if defined(__MCU_MSP430_USCIB1)
    if (module == USCIB1)
      return (UC1IFG & UCB0TXIFG) >> 3;
  #endif
  
  // Error: No valid module selected. Do nothing.
  return 0;
}

/**
 *  @fn void SetUCBxTXIFGBit(uint8_t module, uint8_t bit)
 *
 *  @brief Set the value to UCBxTXIFG bit
 *
 *  @param module an unsigned int
 *  @param bit an unsigned int
 */
void SetUCBxTXIFGBit(uint8_t module, uint8_t bit)
{
  // USCIB0 Module
  #if defined(__MCU_MSP430_USCIB0)
    if (module == USCIB0)
      IFG2 = (IFG2 & ~BIT3) | ((bit << 3) & UCB0TXIFG);
  #endif
    
  // USCIB1 Module
  #if defined(__MCU_MSP430_USCIB1)
    if (module == USCIB1)
      UC1IFG = (UC1IFG & ~BIT3) | ((bit << 3) & UCB1TXIFG);
  #endif
}

/**
 *  @fn uint8_t GetUCBxRXIEBit(uint8_t module)
 *
 *  @brief Get the value of UCBxRXIE bit
 *
 *  @param module an unsigned int
 * 
 *  @return an unsigned int
 */
uint8_t GetUCBxRXIEBit(uint8_t module)
{
  // USCIB0 Module
  #if defined(__MCU_MSP430_USCIB0)
    if (module == USCIB0)
      return (IE2 & UCB0RXIE) >> 2;
  #endif
    
  // USCIB1 Module
  #if defined(__MCU_MSP430_USCIB1)
    if (module == USCIB1)
      return (UC1IE & UCB1RXIE) >> 2;
  #endif
  
  // Error: No valid module selected. Do nothing.
  return 0;
}

/**
 *  @fn void SetUCBxRXIEBit(uint8_t module, uint8_t bit)
 *
 *  @brief Set the value to UCBxRXIE bit
 *
 *  @param module an unsigned int
 *  @param bit an unsigned int
 */
void SetUCBxRXIEBit(uint8_t module, uint8_t bit)
{
  // USCIB0 Module
  #if defined(__MCU_MSP430_USCIB0)
    if (module == USCIB0)
      IE2 =  (IE2 & ~BIT2) | ((bit << 2) & UCB0RXIE);
  #endif
    
  // USCIB1 Module
  #if defined(__MCU_MSP430_USCIB1)
    if (module == USCIB1)
      UC1IE = (UC1IE & ~BIT2) | ((bit << 2) & UCB1RXIE));
  #endif
}

/**
 *  @fn uint8_t GetUCBxRXIFGBit(uint8_t module)
 *
 *  @brief Get the value of UCBxRXIFG bit
 *
 *  @param module an unsigned int
 * 
 *  @return an unsigned int
 */
uint8_t GetUCBxRXIFGBit(uint8_t module)
{
  // USCIB0 Module
  #if defined(__MCU_MSP430_USCIB0)
    if (module == USCIB0)
      return (IE2 & UCB0RXIFG) >> 2;
  #endif
    
  // USCIB1 Module
  #if defined(__MCU_MSP430_USCIB1)
    if (module == USCIB1)
      return (UC1IFG & UCB1RXIFG) >> 2;
  #endif
  
  // Error: No valid module selected. Do nothing.
  return 0;
}

/**
 *  @fn void SetUCBxRXIFGBit(uint8_t module, uint8_t bit)
 *
 *  @brief Set the value to UCBxRXIFG bit
 *
 *  @param module an unsigned int
 *  @param bit an unsigned int
 */
void SetUCBxRXIFGBit(uint8_t module, uint8_t bit)
{
  // USCIB0 Module
  #if defined(__MCU_MSP430_USCIB0)
    if (module == USCIB0)
      IFG2 = (IFG2 & ~BIT2) | ((bit << 2) & UCB0RXIFG);
  #endif
    
  // USCIB1 Module
  #if defined(__MCU_MSP430_USCIB1)
    if (module == USCIB1)
      UC1IFG = (UC1IFG & ~BIT2) | ((bit << 2) & UCB1RXIFG);
  #endif
}

/**
 *  @fn void SetUCBxTXBUFRegister(uint8_t module, uint8_t bit)
 *
 *  @brief Set the value to UCBxTXBUF register
 *
 *  @param module an unsigned int
 *  @param bit an unsigned int
 */
void SetUCBxTXBUFRegister(uint8_t module, uint8_t value)
{
  // USCIB0 Module
  #if defined(__MCU_MSP430_USCIB0)
    if (module == USCIB0)
      UCB0TXBUF = value;
  #endif
    
  // USCIB1 Module
  #if defined(__MCU_MSP430_USCIB1)
    if (module == USCIB1)
      UCB1TXBUF = value;
  #endif
}

/**
 *  @fn void USCIWrite(uint8_t module, uint8_t calledfromISR)
 *
 *  @brief This function writes to the specified USCI module.
 *
 *  @param module an unsigned int
 *  @param calledfromISR an unsigned int
 */
void USCIWrite(uint8_t module, uint8_t calledfromISR)
{
  uint8_t current_interrupt_state = __get_interrupt_state();
 // Interrupts must be disabled when manipulating queue read pointers.

  // CRITICAL SECTION: TXQueue pointer manipulation.
  __disable_interrupt();

  switch(module)
  {
    #if defined(__MCU_MSP430_USCIA0)
    case USCIA0:
      if (USCIA0Structure.count > 0)
      {
        SetUCAxTXBUFRegister(module, *(USCIA0Structure.TXQueue.pRead));
        USCIA0Structure.count--;

        // Check the queue read pointer for loopback.
        if (USCIA0Structure.TXQueue.pRead >= (USCIA0Structure.TXQueue.pBuffer + USCIA0Structure.TXQueue.bufsize) - 1)
        {
          // Set the write pointer back to the beginning.
          USCIA0Structure.TXQueue.pRead = USCIA0Structure.TXQueue.pBuffer;
        }
        else
        {
          // Increment the read pointer.
          USCIA0Structure.TXQueue.pRead++;
        }
      }
      else
      {
        // Set done flag if this was last byte in queue.
        USCIA0Structure.done = 1;
      }
      break;
    #endif
    #if defined(__MCU_MSP430_USCIA1)
    break USCIA1:
      if (USCIA1Structure.count > 0)
      {
        SetUCAxTXBUFRegister(module, *(USCIA1Structure.TXQueue.pRead));
        USCIA1Structure.count--;

        // Check the queue read pointer for loopback.
        if (USCIA1Structure.TXQueue.pRead >= (USCIA1Structure.TXQueue.pBuffer + USCIA1Structure.TXQueue.bufsize) - 1)
        {
          // Set the write pointer back to the beginning.
          USCIA1Structure.TXQueue.pRead = USCIA1Structure.TXQueue.pBuffer;
        }
        else
        {
          // Increment the read pointer.
          USCIA1Structure.TXQueue.pRead++;
        }
      }
      else
      {
        // Set done flag if this was last byte in queue.
        USCIA1Structure.done = 1;
      }
      break;
    #endif
    #if defined(__MCU_MSP430_USCIB0)
    case USCIB0:
      if (USCIB0Structure.count > 0)
      {
        SetUCBxTXBUFRegister(module, USCIB0Structure.TXBuffer[USCIB0Structure.TXBufferIndex]);
        USCIB0Structure.TXBufferIndex++;
        USCIB0Structure.count--;
      }
      else
      {
        USCIB0Structure.TXBufferIndex = 0;
        USCIB0Structure.RXBufferIndex = 0;
        // Set done flag if this was last byte in queue.
        USCIB0Structure.done = 1;
      }
      break;
    #endif
    #if defined(__MCU_MSP430_USCIB1)
    case USCIB1:
      if (USCIB1Structure.count > 0)
      {
        SetUCBxTXBUFRegister(module, *(USCIB1Structure.TXQueue.pRead));
        USCIB1Structure.count--;

        // Check the queue read pointer for loopback.
        if (USCIB1Structure.TXQueue.pRead >= (USCIB1Structure.TXQueue.pBuffer + USCIB1Structure.TXQueue.bufsize) - 1)
        {
          // Set the write pointer back to the beginning.
          USCIB1Structure.TXQueue.pRead = USCIB1Structure.TXQueue.pBuffer;
        }
        else
        {
          // Increment the read pointer.
          USCIB1Structure.TXQueue.pRead++;
        }
      }
      else
      {
        // Set done flag if this was last byte in queue.
        USCIB1Structure.done = 1;
      }
      break;
    #endif
    default:
      // Error: Module is not defined for the selected peripheral.
      break;
  }

  __set_interrupt_state(current_interrupt_state);
}

/**
 *  @fn void USCIRead(uint8_t module, uint8_t calledfromISR)
 *
 *  @brief This function reads from the specified USCI module.
 *
 *  @param module an unsigned int
 *  @param calledfromISR an unsigned int
 */
void USCIRead(uint8_t module, uint8_t calledfromISR)
{
  uint8_t current_interrupt_state = __get_interrupt_state();
 // Interrupts must be disabled when manipulating queue write pointers.

  // CRITICAL SECTION: TXQueue pointer manipulation.
  __disable_interrupt();

  switch(module)
  {
    #if defined(__MCU_MSP430_USCIA0)
    case USCIA0:
      *(USCIA0Structure.RXQueue.pWrite) = GetUCAxRXBUFRegister(USCIA0);
      if((USCIA0Structure.RXQueue.pWrite) < (USCIA0Structure.RXQueue.pBuffer
                                             + USCIA0Structure.RXQueue.bufsize))
      {
        USCIA0Structure.RXQueue.pWrite++;
      }
      else
      {
        USCIA0Structure.RXQueue.pWrite = USCIA0Structure.RXQueue.pBuffer;
      }
      break;
    #endif
    #if defined(__MCU_MSP430_USCIA1)
    case USCIA1:
      *(USCIA1Structure.RXQueue.pWrite) = GetUCAxRXBUFRegister(USCIA1);
      if((USCIA1Structure.RXQueue.pWrite) < (USCIA1Structure.RXQueue.pBuffer
                                             + USCIA1Structure.RXQueue.bufsize))
      {
        USCIA1Structure.RXQueue.pWrite++;
      }
      else
      {
        USCIA1Structure.RXQueue.pWrite = USCIA1Structure.RXQueue.pBuffer;
      }
      break;
    #endif
    #if defined(__MCU_MSP430_USCIB0)
    case USCIB0:
      USCIB0Structure.TXBuffer[USCIB0Structure.RXBufferIndex] = GetUCBxRXBUFRegister(USCIB0);
      USCIB0Structure.RXBufferIndex++;
      break;
    #endif
    #if defined(__MCU_MSP430_USCIB1)
    case USCIB1:
      *(USCIB1Structure.RXQueue.pWrite) = GetUCBxRXBUFRegister(USCIB1);
      if((USCIB1Structure.RXQueue.pWrite) < (USCIB1Structure.RXQueue.pBuffer
                                             + USCIB1Structure.RXQueue.bufsize))
      {
        USCIB1Structure.RXQueue.pWrite++;
      }
      else
      {
        USCIB1Structure.RXQueue.pWrite = USCIB1Structure.RXQueue.pBuffer;
      }
      break;
    #endif
    default:
      // Error: Module is not defined for the selected peripheral.
      break;
  }

  __set_interrupt_state(current_interrupt_state);
}

// INTERRUPT SERVICE ROUTINES
////////////////////////////////////////////////////////////////////////////////

#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCI0TXISR()
{
  if(IFG2 & UCA0TXIFG)
  {
    IFG2 &= ~UCA0TXIFG;
    USCIWrite(USCIA0, 1);
  }
  else if (IFG2 & UCB0TXIFG)
  {                     
    IFG2 &= ~UCB0TXIFG;
    USCIWrite(USCIB0, 1);
  }
  __low_power_mode_off_on_exit();
}

#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RXISR() 
{
  if(IFG2 & UCA0RXIFG)
  {
    IFG2 &= ~UCA0RXIFG;
    USCIRead(USCIA0, 1);
    CommunicationCallback(USCIA0);
  }
  else if (IFG2 & UCB0RXIFG)
  {
    IFG2 &= ~UCB0RXIFG;
    USCIRead(USCIB0, 1);
    CommunicationCallback(USCIB0);
  }
  __low_power_mode_off_on_exit();  // not needed since we're already clearing CPUOFF bit in asm line above
}

#endif  // USCI MODULE