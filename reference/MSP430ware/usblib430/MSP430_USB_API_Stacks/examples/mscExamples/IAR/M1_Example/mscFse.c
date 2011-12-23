// (c)2010 by Texas Instruments Incorporated, All Rights Reserved.

#include "msp430.h"
#include "USB_API/USB_Common/types.h"
#include "USB_config/descriptors.h"
#include "HAL_FLASH.h"
#include "USB_API/USB_MSC_API/UsbMscScsi.h"
#include "mscFseData.h"
#include "mscFse.h"
#include <string.h>

extern const WORD BYTES_PER_BLOCK;

// Every application using this MSC API must define an instance of this structure.  It establishes
// compile-time information about the storage media.  In today's version of the API, only a single LUN
// (Logical UNit) is supported.  In a future version, multiple LUNs will be supported, and defined 
// by this structure.  
struct config_struct USBMSC_config = {
    0x00,     // The number of this LUN.  (Ignored in this version of the API.)
    0x00,     // PDT (Peripheral Device Type). 0x00 = "direct-access block device", which includes all magnetic media.  (Ignored in this version of the API.)
    0x80,     // Indicates whether the medium is removable.  0x00 = not removable, 0x80 = removable
    "TI",     // T10 Vendor ID.  Generally not enforced, and has no particular impact on most operating systems.  
    "MSC",    // T10 Product ID.  Selected by the owner of the vendor ID above.  Has no impact on most OSes.  
    "v3.0",   // T10 revision string.  Selected by the owner of the vendor ID above.  Has no impact on most OSes.  
};


// Writes a 512-byte block to flash.  Flash segments on the F550x, F552x, and F563x/663x 
// are 512 bytes in size -- same as our FAT blocks
VOID flashWrite_LBA(BYTE* flashAddr, BYTE* data)
{
  WORD i;
  unsigned short bGIE;
  
  bGIE  = (__get_SR_register() & GIE);  //save interrupt status
  __disable_interrupt();
    
  // Erase the segment
  FCTL3 = FWKEY;                            // Clear the lock bit
  FCTL1 = FWKEY+ERASE;                      // Set the Erase bit
  *flashAddr = 0;                           // Dummy write, to erase the segment
  
  // Write the data to the segment
  FCTL1 = FWKEY+WRT;                        // Set WRT bit for write operation
  for (i = 0; i < 512; i++)
    *flashAddr++ = *data++;                 // Write the block to flash
  FCTL1 = FWKEY;                            // Clear WRT bit
  FCTL3 = FWKEY+LOCK;                       // Set LOCK bit
  
  __bis_SR_register(bGIE); //restore interrupt status 
}


// This function implements the "file system emulation" approach.  It reads a block from the "storage medium", which
// in this case is internal flash.  It evaluates the block address (LBA) and uses memcpy() to exchange "lbaCount" blocks.  
// The switch() statement can be thought of as a map to the volume's block addresses.  
BYTE Read_LBA(DWORD LBA, BYTE *buff,  BYTE lbaCount)
{
    BYTE i,ret = kUSBMSC_RWSuccess;
    for (i=0; i<lbaCount; i++)
    {
        switch(LBA)
        {
          // The Master Boot Record (MBR).  
          // This is always the first sector.  
          case 0:     
              memcpy(buff, MBR, BYTES_PER_BLOCK);
              break;
  
          // Partition block
          // The contents of the MBR had indicated that the partition block start at 0x27.  
          case 39:    // 0x27
              memcpy(buff, Partition, BYTES_PER_BLOCK);
              break;
  
          // File Allocation Tables
          // The FAT file system requires two copies of the FAT table.  In our example, we actually store only one and report 
          // it in response to the host requesting either.  Note that the partition segement's "sectors per FAT" field indicated
          // the FAT tables were to be 0xF2 = 242 segments long; we only store the first one.  Note also that the number of segments 
          // allotted in this map for both the first FAT table (285-43=242) and the second FAT table (527-285=242) are both that length.    
          case 43:    // First FAT   0x2B 
          case 285:   // Second FAT  0x11D         
              memcpy(buff, FAT, BYTES_PER_BLOCK);
              break;
  
          // Root directory
          // This area is actually 32 blocks long, but this example only stores the first.  
          case 527:   // 0x20F
              memcpy(buff, Root_Dir, BYTES_PER_BLOCK);
              break;

              // The data blocks.  We store blocks 559-565, which is three clusters.  (Note that the partition segment
          // had indicated two blocks per cluster.)
          case 559:   // 0x22F
              memcpy(buff, Data559, BYTES_PER_BLOCK);
              break;
          case 560:   
              memcpy(buff, Data560, BYTES_PER_BLOCK);
              break;
          case 561:   
              memcpy(buff, Data561, BYTES_PER_BLOCK);
              break;
          case 562:   
              memcpy(buff, Data562, BYTES_PER_BLOCK);
              break;
          case 563:   
              memcpy(buff, Data563, BYTES_PER_BLOCK);
              break;
          case 564:   
              memcpy(buff, Data564, BYTES_PER_BLOCK);
              break;
          case 565:   
              memcpy(buff, Data565, BYTES_PER_BLOCK);
              break;

          // For any other block address, return a blank block
          default:
              memset(buff, 0x00, BYTES_PER_BLOCK);
        }
        LBA++;
        buff += BYTES_PER_BLOCK;
    }
    return ret;
}

//--------------------------------------------------------------------------------------------------------
// This function implements the "file system emulation" approach.  It writes a block to the "medium".  It supports
// writes to the first block of the FAT table (which is sufficient for the number of limited numbers of files we
// support); the first block of the root directory (same); and blocks 559-565.  This is three data clusters,
// generally sufficient for three small files.  
BYTE Write_LBA(DWORD LBA, BYTE *buff, BYTE lbaCount)
{
    BYTE i,ret = kUSBMSC_RWSuccess;
    for (i=0; i<lbaCount; i++)
    {    
      
        switch(LBA)
        {
          case 43:   // First FAT               
          case 285:  // Second FAT              
              flashWrite_LBA((BYTE*)FAT,buff);
              break;
          case 527:  // Root directory
              flashWrite_LBA((BYTE*)Root_Dir,buff);
              break;

          case 559:  // Data block
              flashWrite_LBA((BYTE*)Data559,buff);
              break;
          case 560:  // Data block
              flashWrite_LBA(Data560,buff);
              break;
          case 561:  // Data block
              flashWrite_LBA(Data561,buff);
              break;
          case 562:  // Data block
              flashWrite_LBA(Data562,buff);
              break;
          case 563:  // Data block
              flashWrite_LBA(Data563,buff);
              break;
          case 564:  // Data block
              flashWrite_LBA(Data564,buff);
              break;
          case 565:  // Data block
              flashWrite_LBA(Data565,buff);
              break;
          case 566:  // Data block
              flashWrite_LBA(Data566,buff);
              break;
        default:
              break;
        }
        LBA++;
        buff += BYTES_PER_BLOCK;
    }
    
    return ret;
}


/*----------------------------------------------------------------------------+
| End of source file                                                          |
+----------------------------------------------------------------------------*/
/*------------------------ Nothing Below This Line --------------------------*/
