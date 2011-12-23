/* --COPYRIGHT--,BSD
 * Copyright (c) 2011, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
#ifndef __MSP430WARE_MPY32_H__
#define __MSP430WARE_MPY32_H__

//*****************************************************************************
//
//The following are the defines to include the required modules for this
//peripheral in msp430xgeneric.h file
//
//*****************************************************************************
#define __MSP430_HAS_MPY32__


//*****************************************************************************
//
//The following is a struct that can be returned by MPY32_getResult64Bit()
//
//*****************************************************************************
typedef struct {
    unsigned int RES0;
    unsigned int RES1;
    unsigned int RES2;
    unsigned int RES3;
} uint64;

//*****************************************************************************
//
//The following are values that can be passed to MPY32_setWriteDelay() in the
//delaySelect parameter.
//
//*****************************************************************************
#define MPY32_WRITEDELAY_OFF   ( !(MPYDLY32 + MPYDLYWRTEN) )
#define MPY32_WRITEDELAY_32BIT (MPYDLYWRTEN)
#define MPY32_WRITEDELAY_64BIT (MPYDLY32 + MPYDLYWRTEN)

//*****************************************************************************
//
//The following are values that can be passed to MPY32_setOperandOne8Bit(),
//MPY32_setOperandOne8Bit(), MPY32_setOperandOne8Bit(), and
//MPY32_setOperandOne8Bit() in the multiplicationType parameter.
//
//*****************************************************************************
#define MPY32_MULTIPLY_UNSIGNED           (0x00)
#define MPY32_MULTIPLY_SIGNED             (0x02)
#define MPY32_MULTIPLYACCUMULATE_UNSIGNED (0x04)
#define MPY32_MULTIPLYACCUMULATE_SIGNED   (0x06)

//*****************************************************************************
//
//Prototypes for the APIs.
//
//*****************************************************************************

extern void MPY32_setWriteDelay (unsigned int baseAddress,
    unsigned int writeDelaySelect);

extern void MPY32_setSaturationMode (unsigned int baseAddress);

extern void MPY32_resetSaturationMode (unsigned int baseAddress);

extern void MPY32_setFractionMode (unsigned int baseAddress);

extern void MPY32_resetFractionMode (unsigned int baseAddress);

extern void MPY32_setOperandOne8Bit (unsigned int baseAddress,
    unsigned char multiplicationType,
    unsigned char operand);

extern void MPY32_setOperandOne16Bit (unsigned int baseAddress,
    unsigned char multiplicationType,
    unsigned int operand);

extern void MPY32_setOperandOne24Bit (unsigned int baseAddress,
    unsigned char multiplicationType,
    unsigned long operand);

extern void MPY32_setOperandOne32Bit (unsigned int baseAddress,
    unsigned char multiplicationType,
    unsigned long operand);

extern void MPY32_setOperandTwo8Bit (unsigned int baseAddress,
    unsigned char operand);

extern void MPY32_setOperandTwo16Bit (unsigned int baseAddress,
    unsigned int operand);

extern void MPY32_setOperandTwo24Bit (unsigned int baseAddress,
    unsigned long operand);

extern void MPY32_setOperandTwo32Bit (unsigned int baseAddress,
    unsigned long operand);

extern unsigned char MPY32_getResult8Bit (unsigned int baseAddress);

extern unsigned int MPY32_getResult16Bit (unsigned int baseAddress);

extern unsigned long MPY32_getResult24Bit (unsigned int baseAddress);

extern unsigned long MPY32_getResult32Bit (unsigned int baseAddress);

extern uint64 MPY32_getResult64Bit (unsigned int baseAddress);

extern unsigned int MPY32_getSumExtension (unsigned int baseAddress);

extern unsigned short MPY32_getCarryBitValue (unsigned int baseAddress);

#endif
