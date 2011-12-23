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
#ifndef __MSP430WARE_COMPB_H__
#define __MSP430WARE_COMPB_H__

#define __MSP430_HAS_COMPB__


//*****************************************************************************
//
//The following are values that can be passed to Comp_init(),
//Comp_disableInputBuffer(), and Comp_enableInputBuffer() in the
//positiveTerminalInput, negativeTerminalInput, and inputPort parameters.
//
//*****************************************************************************
#define COMPB_INPUT0  (CBIPSEL_0)
#define COMPB_INPUT1  (CBIPSEL_1)
#define COMPB_INPUT2  (CBIPSEL_2)
#define COMPB_INPUT3  (CBIPSEL_3)
#define COMPB_INPUT4  (CBIPSEL_4)
#define COMPB_INPUT5  (CBIPSEL_5)
#define COMPB_INPUT6  (CBIPSEL_6)
#define COMPB_INPUT7  (CBIPSEL_7)
#define COMPB_INPUT8  (CBIPSEL_8)
#define COMPB_INPUT9  (CBIPSEL_9)
#define COMPB_INPUT10 (CBIPSEL_10)
#define COMPB_INPUT11 (CBIPSEL_11)
#define COMPB_INPUT12 (CBIPSEL_12)
#define COMPB_INPUT13 (CBIPSEL_13)
#define COMPB_INPUT14 (CBIPSEL_14)
#define COMPB_INPUT15 (CBIPSEL_15)
#define COMPB_VREF    (0x10)

//*****************************************************************************
//
//The following are values that can be passed to Comp_init() in the
//powerModeSelect parameter.
//
//*****************************************************************************
#define COMPB_POWERMODE_HIGHSPEED     (CBPWRMD_0)
#define COMPB_POWERMODE_NORMALMODE    (CBPWRMD_1)
#define COMPB_POWERMODE_ULTRALOWPOWER (CBPWRMD_2)

//*****************************************************************************
//
//The following are values that can be passed to Comp_init() in the
//outputFilterEnableAndDelayLevel parameter.
//
//*****************************************************************************
#define COMPB_FILTEROUTPUT_OFF     0x00
#define COMPB_FILTEROUTPUT_DLYLVL1 (CBF + CBFDLY_0)
#define COMPB_FILTEROUTPUT_DLYLVL2 (CBF + CBFDLY_1)
#define COMPB_FILTEROUTPUT_DLYLVL3 (CBF + CBFDLY_2)
#define COMPB_FILTEROUTPUT_DLYLVL4 (CBF + CBFDLY_3)

//*****************************************************************************
//
//The following are values that can be passed to Comp_init() in the
//invertedOutputPolarity parameter.
//
//*****************************************************************************
#define COMPB_NORMALOUTPUTPOLARITY   ( !(CBOUTPOL) )
#define COMPB_INVERTEDOUTPUTPOLARITY (CBOUTPOL)

//*****************************************************************************
//
//The following are values that can be passed to Comp_setReferenceVoltage() in
//the supplyVoltageBase parameter.
//
//*****************************************************************************
#define COMPB_VREFBASE_VCC (CBREFL_0)
#define COMPB_VREFBASE1_5V (CBREFL_1)
#define COMPB_VREFBASE2_0V (CBREFL_2)
#define COMPB_VREFBASE2_5V (CBREFL_3)

//*****************************************************************************
//
//The following are values that can be passed to Comp_setEdgeDirection() in
//the edgeDirection parameter.
//
//*****************************************************************************
#define COMPB_FALLINGEDGE ( !(CBIES) )
#define COMPB_RISINGEDGE  (CBIES)

//*****************************************************************************
//
//The following are values that returned by COMPB_outputValue().
//
//*****************************************************************************
#define COMPB_LOW  (0x0)
#define COMPB_HIGH (0x1)


//*****************************************************************************
//API
//*****************************************************************************

extern unsigned short COMPB_init (unsigned int baseAddress,
    unsigned char positiveTerminalInput,
    unsigned char negativeTerminalInput,
    unsigned int powerModeSelect,
    unsigned char outputFilterEnableAndDelayLevel,
    unsigned short invertedOutputPolarity);

extern void COMPB_setReferenceVoltage (unsigned int baseAddress,
    unsigned int supplyVoltageReferenceBase,
    unsigned int lowerLimitSupplyVoltageFractionOf32,
    unsigned int upperLimitSupplyVoltageFractionOf32);

extern void COMPB_enableInterrupt (unsigned int baseAddress, unsigned int mask);

extern void COMPB_disableInterrupt (unsigned int baseAddress,
    unsigned int mask);

extern void COMPB_clearInterrupt (unsigned int baseAddress, unsigned int mask);

extern unsigned char COMPB_getInterruptStatus (unsigned int baseAddress,
    unsigned int mask);

extern void COMPB_interruptSetEdgeDirection (unsigned int baseAddress,
    unsigned short edgeDirection);

extern void COMPB_interruptToggleEdgeDirection (unsigned int baseAddress);

extern void COMPB_enable (unsigned int baseAddress);

extern void COMPB_disable (unsigned int baseAddress);

extern void COMPB_enableShortOfInputs (unsigned int baseAddress);

extern void COMPB_disableShortOfInputs (unsigned int baseAddress);

extern void COMPB_disableInputBuffer (unsigned int baseAddress,
    unsigned char inputPort);

extern void COMPB_enableInputBuffer (unsigned int baseAddress,
    unsigned char inputPort);

extern void COMPB_IOSwap (unsigned int baseAddress);

extern unsigned short COMPB_outputValue (unsigned int baseAddress);

#endif
