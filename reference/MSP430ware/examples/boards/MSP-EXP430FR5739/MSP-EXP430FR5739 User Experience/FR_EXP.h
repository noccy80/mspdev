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
 ******************************************************************************/

// Mode Definitions
#define MAX_FRAM_WRITE 2
#define SLOW_FRAM_WRITE 4
#define ACCEL_MEAS  6
#define TEMP_MEAS   8

// The FRAM section from 0xD000 - 0xF000 is used by all modes
// for performing writes to FRAM
// Do not use this section for code or data placement. 
// It will get overwritten!
#define ADC_START_ADD 0xD400
#define ADC_END_ADD 0xF000
#define FRAM_TEST_START 0xD400
#define FRAM_TEST_END 0xF000
#define MEM_UNIT 0x200

// Pin Definitions
#define ACC_PWR_PIN       BIT7
#define ACC_PWR_PORT_DIR  P2DIR
#define ACC_PWR_PORT_OUT  P2OUT
#define ACC_PORT_DIR      P3DIR
#define ACC_PORT_OUT      P3OUT
#define ACC_PORT_SEL0     P3SEL0
#define ACC_PORT_SEL1     P3SEL1
#define ACC_X_PIN         BIT0
#define ACC_Y_PIN         BIT1
#define ACC_Z_PIN         BIT2

// Accelerometer Input Channel Definitions
#define ACC_X_CHANNEL     ADC10INCH_12
#define ACC_Y_CHANNEL     ADC10INCH_13
#define ACC_Z_CHANNEL     ADC10INCH_14

#define DOWN 0
#define UP 1

// Function Declarations

extern void SystemInit(void);
extern void  StartUpSequence(void);
extern void FRAM_Write(unsigned int StartAddress);
extern void Mode1(void);
extern void Mode2(void);
extern void Mode3(void);
extern void Mode4(void);
extern unsigned int CalibrateADC(void); 
extern void TakeADCMeas(void);
extern void SetupAccel(void); // setup ADC for Acc
extern void ShutDownAccel(void);
extern void SetupThermistor(void);
extern void ShutDownTherm(void);
extern void LEDSequence(unsigned int, unsigned char);
extern void LEDSequenceWrite(unsigned char);
extern void DisableSwitches(void);
extern void EnableSwitches(void);
extern void StartDebounceTimer(unsigned char);
extern void LongDelay(void);
extern void TXData(void);
extern void TXBreak(unsigned char);

