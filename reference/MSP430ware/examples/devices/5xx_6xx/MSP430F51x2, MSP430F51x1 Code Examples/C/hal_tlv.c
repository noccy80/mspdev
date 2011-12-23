//*******************************************************************************
//  Provides Functions to Read the TLV Data Section of the MSP430 Devices
//    File: hal_TLV.c
//
//    Texas Instruments
//
//    Version 1.0
//    10/17/10
//
//    V1.0  Initial Version
//====================================================================

/* ***********************************************************
* THIS PROGRAM IS PROVIDED "AS IS". TI MAKES NO WARRANTIES OR
* REPRESENTATIONS, EITHER EXPRESS, IMPLIED OR STATUTORY,
* INCLUDING ANY IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS
* FOR A PARTICULAR PURPOSE, LACK OF VIRUSES, ACCURACY OR
* COMPLETENESS OF RESPONSES, RESULTS AND LACK OF NEGLIGENCE.
* TI DISCLAIMS ANY WARRANTY OF TITLE, QUIET ENJOYMENT, QUIET
* POSSESSION, AND NON-INFRINGEMENT OF ANY THIRD PARTY
* INTELLECTUAL PROPERTY RIGHTS WITH REGARD TO THE PROGRAM OR
* YOUR USE OF THE PROGRAM.
*
* IN NO EVENT SHALL TI BE LIABLE FOR ANY SPECIAL, INCIDENTAL,
* CONSEQUENTIAL OR INDIRECT DAMAGES, HOWEVER CAUSED, ON ANY
* THEORY OF LIABILITY AND WHETHER OR NOT TI HAS BEEN ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGES, ARISING IN ANY WAY OUT
* OF THIS AGREEMENT, THE PROGRAM, OR YOUR USE OF THE PROGRAM.
* EXCLUDED DAMAGES INCLUDE, BUT ARE NOT LIMITED TO, COST OF
* REMOVAL OR REINSTALLATION, COMPUTER TIME, LABOR COSTS, LOSS
* OF GOODWILL, LOSS OF PROFITS, LOSS OF SAVINGS, OR LOSS OF
* USE OR INTERRUPTION OF BUSINESS. IN NO EVENT WILL TI'S
* AGGREGATE LIABILITY UNDER THIS AGREEMENT OR ARISING OUT OF
* YOUR USE OF THE PROGRAM EXCEED FIVE HUNDRED DOLLARS
* (U.S.$500).
*
* Unless otherwise stated, the Program written and copyrighted
* by Texas Instruments is distributed as "freeware".  You may,
* only under TI's copyright in the Program, use and modify the
* Program without any charge or restriction.  You may
* distribute to third parties, provided that you transfer a
* copy of this license to the third party and the third party
* agrees to these terms by its first use of the Program. You
* must reproduce the copyright notice and any other legend of
* ownership on each copy or partial copy, of the Program.
*
* You acknowledge and agree that the Program contains
* copyrighted material, trade secrets and other TI proprietary
* information and is protected by copyright laws,
* international copyright treaties, and trade secret laws, as
* well as other intellectual property laws.  To protect TI's
* rights in the Program, you agree not to decompile, reverse
* engineer, disassemble or otherwise translate any object code
* versions of the Program to a human-readable form.  You agree
* that in no event will you alter, remove or destroy any
* copyright notice included in the Program.  TI reserves all
* rights not specifically granted under this license. Except
* as specifically provided herein, nothing in this agreement
* shall be construed as conferring by implication, estoppel,
* or otherwise, upon you, any license or other right under any
* TI patents, copyrights or trade secrets.
*
* You may not use the Program in non-TI devices.
* ********************************************************* */


#include "msp430f5172.h"
#include "hal_TLV.h"

//====================================================================
/**
  * Get Information out of the TLV Table
  *
  * \param tag: Tag of the TLV entry
  * \param instance: Instance of the Tag of the TLV entry
  * \param *length: return: Length of the information if found
  * \param **data_address: return: start pointer of Data
  */
void Get_TLV_Info(uint8_t tag, uint8_t instance, uint8_t *length, uint16_t ** data_address)
{
  char *TLV_address = (char *)TLV_START;          // TLV Structure Start Address

  while((TLV_address < ( char *)TLV_END)
        && ((*TLV_address != tag) || instance)   // check for tag and instance
        && (*TLV_address != TLV_TAGEND) )        // do range check first
  {
    if (*TLV_address == tag)(instance--);        // repeat till requested instance is reached
    TLV_address += *(TLV_address+1) + 2;         // add (Current TAG address + LENGTH) + 2
  }
  if (*TLV_address == tag)                       // Check if Tag match happened..
  {
    *length = *(TLV_address+1);                  // Return length = Address + 1
    *data_address = (uint16_t *)(TLV_address+2); // Return address of first data/value info = Address + 2
  }
  else                                           // If there was no tag match and the end of TLV structure was reached..
  {
    *length = 0;                                 // Return 0 for TAG not found
    *data_address = 0;                           // Return 0 for TAG not found
  }
}

//====================================================================
/**
  * Get Device Type out of the TLV Table
  *
  * \return device_type - either F5438 or F5438A, depending on device
  */
uint16_t Get_Device_Type(void)
{
  uint16_t *pDeviceType = (uint16_t *)DEVICE_ID_0;
  return (pDeviceType[0]);                       // Return Value from TLV Table
}

//====================================================================
/**
  * Get Memory Info out of the TLV Table
  *
  * \param instance: Index of the Instance [0..]
  * \return Memory Data found
  */
uint16_t Get_TLV_Memory(uint8_t instance)
{
    uint8_t * pPDTAG;
    uint8_t bPDTAG_bytes;
    uint16_t count;

    instance *= 2;                               // set tag for word access comparison
    // TLV access Function Call
    Get_TLV_Info(TLV_PDTAG, 0, &bPDTAG_bytes, (uint16_t **) &pPDTAG); // Get Peripheral data pointer
    for(count=0;count<=instance;count+=2)
    {
      if (pPDTAG[count] == 0) return 0;          // Return 0 if end reached
      if (count == instance) return (pPDTAG[count] | pPDTAG[count+1]<<8);
    }
    return 0;                                    // Return 0: not found
}

//====================================================================
/**
  * Get Peripheral Info out of the TLV Table
  *
  * \param tag: Tag of the TLV entry
  * \param instance: Index of the Instance [0..]
  * \return Peripheral Data found
  */
uint16_t Get_TLV_Peripheral(uint8_t tag, uint8_t instance)
{
    uint8_t * pPDTAG;
    uint8_t bPDTAG_bytes;
    uint16_t count = 0;
    uint16_t pcount = 0;


    Get_TLV_Info(TLV_PDTAG, 0, &bPDTAG_bytes, (uint16_t **) &pPDTAG); // Get Peripheral data pointer
    // read memory configuration from TLV to get offset for Peripherals
    while(Get_TLV_Memory(count))
    { count++; }

    pcount = pPDTAG[count*2 + 1];                // get number of Peripheral entries
    count++;                                     // inc count to first Periperal
    pPDTAG += count*2;                           // adjust point to first address of Peripheral
    count = 0;                                   // set counter back to 0

    pcount *= 2;                                 // align pcount for work comparision

    // TLV access Function Call
    for(count=0;count<=pcount;count+=2)
    {
      if (pPDTAG[count+1] == tag)                // test if required Peripheral is found
        if(instance > 0) {                       // test if required instance is found
          instance--;
        }else{
          return (pPDTAG[count] | pPDTAG[count+1]<<8); // Return found data
        }
    }
    return 0;                                    // Return 0: not found
}

//====================================================================
/**
  * Get Interrupt Info out of the TLV Table
  *
  * \param tag: Tag of the TLV entry
  * \return Interrupt Data found
  */
uint8_t Get_TLV_Interrupt(uint8_t tag)
{
    uint8_t * pPDTAG;
    uint8_t bPDTAG_bytes;
    uint16_t count = 0;
    uint16_t pcount = 0;


    Get_TLV_Info(TLV_PDTAG, 0, &bPDTAG_bytes, (uint16_t **) &pPDTAG); // Get Peripheral data pointer
    // read memory configuration from TLV to get offset for Peripherals
    while(Get_TLV_Memory(count))
    {
      count++;
    }

    pcount = pPDTAG[count*2 + 1];
    count++;                                     // inc count to first Periperal
    pPDTAG += (pcount+count)*2;                  // adjust point to first address of Peripheral
    count = 0;                                   // set counter back to 0

    // TLV access Function Call
    for(count=0;count<=tag;count+=2)
    {
      if (pPDTAG[count] == 0) return 0;          // Return 0: not found/end of table
      if (count == tag) return (pPDTAG[count]);  // Return found data
    }
    return 0;                                    // Return 0: not found
}
