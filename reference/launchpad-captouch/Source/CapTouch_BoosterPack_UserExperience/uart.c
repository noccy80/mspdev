/*******************************************************************************
 *
 *  uart.c - c file for UART communication using MSP430 TimerA 
 *         - peripheral  
 *
 *  Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/ 
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 ******************************************************************************/
#include "uart.h"
unsigned char timerA_UART_mode = 0;
unsigned int txData; 
//------------------------------------------------------------------------------
// Function configures Timer_A for full-duplex UART operation
//------------------------------------------------------------------------------
void TimerA_UART_init(void)
{
  DCOCTL = 0x00;                          // Set DCOCLK to 1MHz
  BCSCTL1 = CALBC1_1MHZ;
  DCOCTL = CALDCO_1MHZ;
  BCSCTL2 &= ~DIVS_3;                     // SMCLK = 1MHz  
  
  P1SEL |= UART_TXD + UART_RXD;            // Timer function for TXD/RXD pins
//  P1SEL |= UART_TXD ;
  P1DIR |= UART_TXD;                        // TXD 
  P1DIR &= ~UART_RXD;
  
  TACCTL0 = OUT;                          // Set TXD Idle as Mark = '1'
  // TACCTL1 = SCS + CM1 + CAP + CCIE;       // Sync, Neg Edge, Capture, Int
  TACTL |= TACLR;                           // SMCLK, start in continuous mode  
  TACTL = TASSEL_2 + MC_2;                // SMCLK, start in continuous mode
  timerA_UART_mode = 1;
}
//------------------------------------------------------------------------------
// Function unconfigures Timer_A for full-duplex UART operation
//------------------------------------------------------------------------------
void TimerA_UART_shutdown(void)
{
  timerA_UART_mode = 0;
  P1SEL &= ~(UART_TXD + UART_RXD);            // Timer function for TXD/RXD pins
//  P1SEL &= ~(UART_TXD );            // Timer function for TXD/RXD pins  
  TACCTL1 &= ~CCIE;                           // Sync, Neg Edge, Capture, Int
  TACTL &= ~MC_3;                             // Clear TA modes --> Stop Timer Module
  P1OUT &= ~UART_TXD;
}
//------------------------------------------------------------------------------
// Outputs one byte using the Timer_A UART
//------------------------------------------------------------------------------
void TimerA_UART_tx(unsigned char byte)
{
    while (TACCTL0 & CCIE);                 // Ensure last char got TX'd
    TACCR0 = TAR;                           // Current state of TA counter
    TACCR0 += UART_TBIT;                    // One bit time till first bit
    txData = byte;                          // Load global variable
    txData |= 0x100;                        // Add mark stop bit to TXData
    txData <<= 1;                           // Add space start bit
    TACCTL0 = OUTMOD0 + CCIE;               // Set TXD on EQU2 (idle), Int
    __bis_SR_register( LPM0_bits + GIE);
}
//------------------------------------------------------------------------------
// Prints a string over using the Timer_A UART
//------------------------------------------------------------------------------
void TimerA_UART_print(char *string)
{
    while (*string) {
        TimerA_UART_tx(*string++);
    }
}
//------------------------------------------------------------------------------
// Timer_A UART - Transmit Interrupt Handler
//------------------------------------------------------------------------------
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A0_ISR(void)
{
    static unsigned char txBitCnt = 10;
    if (!timerA_UART_mode)
      __bic_SR_register_on_exit(LPM3_bits+GIE); 
    else
    {
      TACCR0 += UART_TBIT;                    // Add Offset to CCRx
      if (--txBitCnt == 0)                    // All bits TXed?
      {                    
          TACCTL0 &= ~CCIE;                   // All bits TXed, disable interrupt
          txBitCnt = 10;
          __bic_SR_register_on_exit(LPM0_bits+GIE);
      }
      else {
          if (txData & 0x01) {
            TACCTL0 &= ~OUTMOD2;              // TX Mark '1'
          }
          else {
            TACCTL0 |= OUTMOD2;               // TX Space '0'
          }
          txData >>= 1;
          
      }
    }
}
   
