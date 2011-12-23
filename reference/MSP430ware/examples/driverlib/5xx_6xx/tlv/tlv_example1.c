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
//******************************************************************************
//!
//!  The contents of TLV device descriptors are read out using the
//!  core library TLV functions and then stored into local variables.  
//!
//!  ACLK = n/a, MCLK = SMCLK = default DCO ~ 1.045MHz
//!
//!                MSP430F5438A
//!             -----------------
//!         /|\|              XIN|-
//!          | |                 |
//!          --|RST          XOUT|-
//!            |                 |
//!            |                 |
//!
//! This example uses the following peripherals and I/O signals.  You must
//! review these and change as needed for your own board:
//! - WDT
//!
//! This example uses the following interrupt handlers.  To use this example
//! in your own application you must add these interrupt handlers to your
//! vector table.
//! - None.
//!
//*****************************************************************************

#include "inc/hw_memmap.h"
#include "driverlib/5xx_6xx/wdt.h"
#include "driverlib/5xx_6xx/tlv.h"

// Die Record Variables
struct s_TLV_Die_Record * pDIEREC;
unsigned char bDieRecord_bytes;
unsigned int temp;
unsigned long WaferID;
unsigned int DieX, DieY, TestRes;

// ADC Variables
struct s_TLV_ADC_Cal_Data * pADCCAL;
unsigned char bADCCAL_bytes;
unsigned int ADCGain, ADCOffset;
unsigned int ADC_15V_Ref_30C, ADC_15V_Ref_85C, ADC_20V_Ref_30C;
unsigned int ADC_20V_Ref_85C, ADC_25V_Ref_30C, ADC_25V_Ref_85C;

// REF Variables
struct s_TLV_REF_Cal_Data * pREFCAL;
unsigned char bREFCAL_bytes;
unsigned int REF_15V, REF_20V, REF_25V;

// Peripheral Variables
struct s_Peripheral_Memory_Data * pPeriph;
unsigned char bPeriph_bytes;
unsigned int Memory_1, Memory_2, Memory_3, Memory_4;
unsigned int PMM_Exist;

void readDieRecord(void);
void readADCCAL(void);
void readREFCAL(void);
void readPeripheral(void);

void main(void)
{
  //Stop WDT
  WDT_hold(__MSP430_BASEADDRESS_WDT_A__);
  
  readDieRecord();
  readADCCAL();
  readREFCAL();
  readPeripheral();
  
  // Place breakpoint here
  while(1);                                 
}

//******************************************************************************
//
// This function will search the TLV block for the Die Record tag and store the 
// address of the first data in the block in the reference pointer passed as an 
// argument. The data is then saved to local variables.
//
//******************************************************************************

void readDieRecord(void)
{
  // Read Die Record Values
  TLV_getInfo(TLV_TAG_DIERECORD, 
              0, 
              &bDieRecord_bytes, 
              (unsigned int **)&pDIEREC
              );

  WaferID = pDIEREC->wafer_id;
  DieX = pDIEREC->die_x_position;
  DieY = pDIEREC->die_y_position;
  TestRes = pDIEREC->test_results;
}

//******************************************************************************
//
// This function will search the TLV block for the ADC CAL tag and store the 
// address of the first data in the block in the reference pointer passed as an 
// argument. The data is then saved to local variables.
//
//******************************************************************************

void readADCCAL(void)
{
  // Read ADC12 Calibration Values
  TLV_getInfo(TLV_TAG_ADCCAL, 
              0, 
              &bADCCAL_bytes, 
              (unsigned int **)&pADCCAL
              );
  
  ADCGain = pADCCAL->adc_gain_factor;
  ADCOffset = pADCCAL->adc_offset;
  ADC_15V_Ref_30C = pADCCAL->adc_ref15_30_temp;
  ADC_15V_Ref_85C = pADCCAL->adc_ref15_85_temp;
  ADC_20V_Ref_30C = pADCCAL->adc_ref20_30_temp;
  ADC_20V_Ref_85C = pADCCAL->adc_ref20_85_temp;
  ADC_25V_Ref_30C = pADCCAL->adc_ref25_30_temp;
  ADC_25V_Ref_85C = pADCCAL->adc_ref25_85_temp;
}

//******************************************************************************
//
// This function will search the TLV block for the REF CAL tag and store the 
// address of the first data in the block in the reference pointer passed as an 
// argument. The data is then saved to local variables.
//
//******************************************************************************

void readREFCAL(void)
{
  // Read REF Calibration Values
  TLV_getInfo(TLV_TAG_REFCAL, 
              0, 
              &bREFCAL_bytes, 
              (unsigned int **)&pREFCAL
              );
  
  REF_15V = pREFCAL->ref_ref15;
  REF_20V = pREFCAL->ref_ref20;
  REF_25V = pREFCAL->ref_ref25;
}

//******************************************************************************
//
// The function checks for the existence of memory blocks in a device. 
// This is followed by checking if the PMM module exists and is defined in the
// peripheral descriptor section.
//  
// The function TLV_getInfo searches the TLV block for the Peripheral tag and
// stores the address of the first data in the block in the reference pointer 
// passed as an argument. The data is then saved to local variables.
// 
// The function Get_TLV_peripheral returns a non-zero value indicating the PMM
// peripheral exists TLV_getPeripheral the current device. This same procedure can be 
// replicated for any peripheral that is listed in the device datasheet. The 
// tag code that corresponds to each peripheral can be found in tlv.h

//******************************************************************************

void readPeripheral(void)
{
  // Read Peripheral Memory Descriptors
  TLV_getInfo(TLV_TAG_PDTAG, 
              0, 
              &bPeriph_bytes, 
              (unsigned int **)&pPeriph
              );
  
  Memory_1 = pPeriph->memory_1;
  Memory_2 = pPeriph->memory_2;
  Memory_3 = pPeriph->memory_3;
  Memory_4 = pPeriph->memory_4;
  
  // Read PMM Descriptor to Show its Availability
  PMM_Exist = TLV_getPeripheral(TLV_PID_PMM, 0);
}
