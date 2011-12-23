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
#ifndef __MSP430WARE_PU_H__
#define __MSP430WARE_PU_H__
//*****************************************************************************
//
//The following are the defines to include the required modules for this
//peripheral in msp430xgeneric.h file
//
//*****************************************************************************
#define __MSP430_HAS_PU__

//*****************************************************************************
//
//The following are values that can be passed to the LDOPWR_enableInterrupt(),
//LDOPWR_disableInterrupt(), LDOPWR_getInterruptStatus(),
//LDOPWR_clearInterruptStatus() API as the mask parameter.
//
//*****************************************************************************
#define LDOPWR_LDOI_VOLTAGE_GOING_OFF_INTERRUPT     LDOOFFIE_H
#define LDOPWR_LDOI_VOLTAGE_COMING_ON_INTERRUPT     LDOONIE_H
#define LDOPWR_LDO_OVERLOAD_INDICATION_INTERRUPT    LDOOVLIE_H

//*****************************************************************************
//
//The following are values that can be returned by LDOPWR_LDOInputValid() API
//
//*****************************************************************************
#define LDOPWR_LDO_INPUT_VALID      LDOBGVBV
#define LDOPWR_LDO_INPUT_INVALID    0x00

//*****************************************************************************
//
//The following are values that can be returned by
//the LDOPWR_getOverloadAutoOffStatus() API
//
//*****************************************************************************
#define LDOPWR_AUTOOFF_ENABLED  OVLAOFF_H
#define LDOPWR_AUTOOFF_DISABLED  0x00

//*****************************************************************************
//
//The following are values that can be returned by LDOPWR_getPortU1InputData(),
//LDOPWR_getPortU0InputData(), LDOPWR_getPortU1OutputData(),
//LDOPWR_getPortU0OutputData(), LDOPWR_setPortU1OutputData(),
//API and may be passed as value parameter to LDOPWR_setPortU0OutputData(),
//LDOPWR_setPortU1OutputData() API
//
//*****************************************************************************
#define LDOPWR_PORTU_PIN_HIGH  PUOUT0
#define LDOPWR_PORTU_PIN_LOW  0x00

//*****************************************************************************
//
//Prototypes for the APIs.
//
//*****************************************************************************
extern
void LDOPWR_unLockConfiguration ( unsigned int baseAddress );
extern
void LDOPWR_lockConfiguration ( unsigned int baseAddress );
extern
void LDOPWR_enablePort_U_inputs (unsigned int baseAddress );
extern
void LDOPWR_disablePort_U_inputs (unsigned int baseAddress );
extern
void LDOPWR_enablePort_U_outputs (unsigned int baseAddress );
extern
void LDOPWR_disablePort_U_outputs (unsigned int baseAddress );
extern
unsigned char LDOPWR_getPort_U1_inputData (unsigned int baseAddress );
extern
unsigned char LDOPWR_getPort_U0_inputData (unsigned int baseAddress );
extern
unsigned char LDOPWR_getPort_U1_outputData (unsigned int baseAddress );
extern
unsigned char LDOPWR_getPort_U0_outputData (unsigned int baseAddress );
extern
void LDOPWR_enableInterrupt (unsigned int baseAddress,
    unsigned int mask
    );
extern
void LDOPWR_disableInterrupt (unsigned int baseAddress,
    unsigned int mask
    );
extern
void LDOPWR_enable (unsigned int baseAddress);
extern
void LDOPWR_disable (unsigned int baseAddress);
extern
unsigned char LDOPWR_getInterruptStatus (unsigned int baseAddress,
    unsigned int mask
    );
extern
unsigned char LDOPWR_isLDOInputValid (unsigned int baseAddress);
extern
void LDOPWR_enableOverloadAutoOff (unsigned int baseAddress);
extern
void LDOPWR_disableOverloadAutoOff (unsigned int baseAddress);
extern
unsigned char LDOPWR_getOverloadAutoOffStatus (unsigned int baseAddress);
extern
void LDOPWR_clearInterruptStatus (unsigned int baseAddress,
    unsigned int mask
    );
extern
void LDOPWR_setPort_U0_outputData (unsigned int baseAddress,
    unsigned char value
    );
extern
void LDOPWR_togglePort_U1_outputData (unsigned int baseAddress);
extern
void LDOPWR_togglePort_U0_outputData (unsigned int baseAddress);
extern
void LDOPWR_setPort_U1_outputData (unsigned int baseAddress,
    unsigned char value
    );
#endif
