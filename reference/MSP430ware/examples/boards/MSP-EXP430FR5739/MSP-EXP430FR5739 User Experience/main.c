/*******************************************************************************
 *
 * main.c
 * User Experience Code for the MSP-EXP430FR5739
 * 
 *
 * Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/ 
 * 
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
 * Created: Version 1.0 04/13/2011
 *          Version 1.1 05/11/2011
 *          Version 1.2 08/31/2011
 *  
 ******************************************************************************/
#include "msp430fr5739.h"
#include "FR_EXP.h"

const unsigned char LED_Menu[] = {0x80,0xC0,0xE0,0xF0};
// These golabal variables are used in the ISRs and in FR_EXP.c
volatile unsigned char mode = 0;
volatile unsigned char UserInput = 0;
volatile unsigned char ULP =0; 
volatile unsigned int *FRAMPtr = 0;
volatile unsigned char active = 0;
volatile unsigned char SwitchCounter=0;
volatile unsigned char Switch1Pressed=0;
volatile unsigned char Switch2Pressed=0;
volatile unsigned int ADCResult = 0;

void main(void)
{  
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT  
  SystemInit();                             // Init the Board
  StartUpSequence();                        // Light up LEDs
  
  // Setup ADC data storage pointer for Modes 3&4
  FRAMPtr = (unsigned int *) ADC_START_ADD;
  
  while(1)  
  {
    // Variable initialization
    active = 0;
    Switch2Pressed = 0;
    ULP = 0;
    // Wait in LPM4 for user input 
    __bis_SR_register(LPM4_bits + GIE);     // Enter LPM4 w/interrupt
    __no_operation();			            // For debugger
    
    // Wake up from LPM because user has entered a mode
    switch(mode)
    {
      case MAX_FRAM_WRITE:
        Mode1();
        break;
        
      case SLOW_FRAM_WRITE:
        Mode2();
        break;
        
      case ACCEL_MEAS:
        Mode3();
        break;
        
      case TEMP_MEAS:
        Mode4();      
        break;
        
      default:
        // This is not a valid mode
        // Blink LED1 to indicate invalid entry
        // Switch S2 was pressed w/o mode select
        while((mode > 0x08)&& (UserInput == 0))
          {
            P3OUT ^= BIT7;
            LongDelay();
          }
    break;
    }
  }    
}
 
// Interrupt Service Routines
/**********************************************************************//**
 * @brief  Port 4 ISR for Switch Press Detect
 * 
 * @param  none 
 *  
 * @return none
 *************************************************************************/
#pragma vector=PORT4_VECTOR
__interrupt void Port_4(void)
{
  // Clear all LEDs
  PJOUT &= ~(BIT0 +BIT1+BIT2+BIT3);                  
  P3OUT &= ~(BIT4 +BIT5+BIT6+BIT7);
  
  switch(__even_in_range(P4IV,P4IV_P4IFG1))
    {
      case P4IV_P4IFG0:        
        DisableSwitches();               
        Switch2Pressed = 0;
        UserInput = 1;
        P4IFG &= ~BIT0;                         // Clear P4.0 IFG
        P3OUT = LED_Menu[SwitchCounter];
        SwitchCounter++;
        if (SwitchCounter>3)
          {
            SwitchCounter =0;
            Switch1Pressed++;
          }           
        StartDebounceTimer(0);                // Reenable switches after debounce
        break;
          
      case P4IV_P4IFG1:
        DisableSwitches();
        StartDebounceTimer(0);              // Reenable switches after debounce        
        P4IFG &= ~BIT1;                     // Clear P4.1 IFG                
        // This is the second time Switch2 is pressed
        // Was the code executing inside of the modes?
        // ULP option on or off? 
        if ((Switch2Pressed > 0)&& (active == 1))
        {
          ULP ^= 0x01;                    // Toggle Display ON/OFF
          break; 
        }
        else
          Switch2Pressed = 1;                                    
        UserInput = 0;   
        // If the counter value is 0 it indicates either Mode 4 or invalid entry
        if((SwitchCounter == 0) && (Switch1Pressed >0))
          mode = 4;                         // because counter rollsover after 3
        if((SwitchCounter == 0) && (Switch1Pressed == 0))
          mode = 5;                         // no switch1 press - invalid
        if(SwitchCounter>3)
          mode = 5;                         // too high! this is invalid entry 
        if((SwitchCounter>0) && (SwitchCounter<=3))// this entry is correct
          mode = SwitchCounter;             // store mode        
        mode = mode * 2;                    // make it an even number
        // Reset variables
        Switch1Pressed = 0; 
        SwitchCounter = 0;
        __bic_SR_register_on_exit(LPM4_bits);// Exit LPM4
        break;
  
      default:
        break;
    }  
}

/**********************************************************************//**
 * @brief  Timer A0 ISR for MODE2, Slow FRAM writes, 40ms timer
 * 
 * @param  none 
 *  
 * @return none
 *************************************************************************/
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{  
  __bic_SR_register_on_exit(LPM4_bits);
}

/**********************************************************************//**
 * @brief  ADC10 ISR for MODE3 and MODE4
 * 
 * @param  none 
 *  
 * @return none
 *************************************************************************/
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
  switch(__even_in_range(ADC10IV,ADC10IV_ADC10IFG))
  {
    case ADC10IV_NONE: break;               // No interrupt
    case ADC10IV_ADC10OVIFG: break;         // conversion result overflow
    case ADC10IV_ADC10TOVIFG: break;        // conversion time overflow
    case ADC10IV_ADC10HIIFG: break;         // ADC10HI
    case ADC10IV_ADC10LOIFG: break;         // ADC10LO
    case ADC10IV_ADC10INIFG: break;         // ADC10IN
    case ADC10IV_ADC10IFG: 
             ADCResult = ADC10MEM0;
             *FRAMPtr = ADCResult;
             FRAMPtr++;
             // Pointer round off, once 0x200 locations are written, the pointer
             // rolls over
             if (FRAMPtr > (unsigned int *)ADC_END_ADD)
                  FRAMPtr = (unsigned int *) ADC_START_ADD; 
             __bic_SR_register_on_exit(CPUOFF);                                              
             break;                          // Clear CPUOFF bit from 0(SR)                         
    default: break; 
  }  
}

/**********************************************************************//**
 * @brief Timer A1 ISR for debounce Timer
 * 
 * @param  none 
 *  
 * @return none
 *************************************************************************/
#pragma vector = TIMER1_A0_VECTOR
__interrupt void Timer1_A0_ISR(void)
{
  TA1CCTL0 = 0;
  TA1CTL = 0;
  EnableSwitches();  
}

