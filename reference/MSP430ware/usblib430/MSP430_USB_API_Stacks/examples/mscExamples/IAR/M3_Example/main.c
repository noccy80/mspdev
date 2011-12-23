// USB #includes
#include "USB_API/USB_Common/device.h"
#include "USB_API/USB_Common/types.h"          
#include "USB_config/descriptors.h"
#include "USB_API/USB_Common/usb.h"       
#include "F5xx_F6xx_Core_Lib/HAL_UCS.h"
#include "F5xx_F6xx_Core_Lib/HAL_PMM.h"
#include "F5xx_F6xx_Core_Lib/HAL_FLASH.h"
#include <string.h>

// MSC #includes
#include "USB_API/USB_MSC_API/UsbMscScsi.h"
#include "USB_API/USB_MSC_API/UsbMsc.h"
#include "USB_API/USB_MSC_API/UsbMscStateMachine.h"

// Board and FatFs #includes
#include "FatFs/diskio.h"               
#include "FatFs/mmc.h"
#include "mscFse.h"
#include "LUN0_data.h"


BYTE checkInsertionRemoval(void);
void Board_init(void);
void ClockUSB(void);
VOID read_LUN1(VOID);
VOID write_LUN1(VOID);

// The number of bytes per block.  In FAT, this is 512
const WORD BYTES_PER_BLOCK = 512;

volatile BYTE fS1ButtonEvent = 0;  // Flag indicating button S1 was pressed (that is, button S1 on a F552x FET target board)
//extern const BYTE* Root_Dir;
//extern const BYTE* Data559;                // The data block of the storage volume, held in RAM
WORD DataCnt = 0;                  // The index of the next available byte to be written within Data[]
BYTE logCnt = 0x30;                // Holds an incrementing character to be written into each new data log entry


// Data-exchange buffer between the API and the application.  The application allocates it, 
// and then registers it with the API.  Later, the API will pass it back to the application when it
// needs the application to "process" it (exchange data with the media).  
uint8_t RW_dataBuf[512];


// The API allocates an instance of structure type USBMSC_RWbuf_Info to hold all information describing  
// buffers to be processed.  It is a shared resource between the API and application.  It will be initialized
// by calling USBMSC_fetchInfoStruct().    
USBMSC_RWbuf_Info *RWbuf_info;


// The application must tell the API about the media.  This information is conveyed in a call to 
// USBMSC_updateMediaInfo(), passing an instance of USBMSC_RWbuf_Info.  Since SD-cards are removable, this might
// need to occur at any time, so this is made global.  
struct USBMSC_mediaInfoStr mediaInfo;

uint8_t bDetectCard = 0x00;   // Global flag by which the timer ISR will trigger main() to check the media status

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;                // Stop the watchdog
    __enable_interrupt();                    // Enable general interrupts
    Board_init();                            // Configure's the F5529 EXP board's I/Os
    
    // Initialize power/clocks for use with USB
    SetVCore(3);                             // The USB module requires that VCore be set to highest setting, independent of MCLK freq
    ClockUSB();
    
    disk_initialize(0);                      // SD-cards must go through a setup sequence after powerup.  This FatFs call does this.  
    USB_init();                              // Initializes the USB API, and prepares the USB module to detect USB insertion/removal events
    USB_setEnabledEvents(kUSB_allUsbEvents); // Enable all USB events
      
    // The data interchange buffer (used when handling SCSI READ/WRITE) is declared by the application, and 
    // registered with the API using this function.  This allows it to be assigned dynamically, giving 
    // the application more control over memory management.  
    USBMSC_registerBufInfo(&RW_dataBuf[0], NULL, sizeof(RW_dataBuf));
 
    
    // The API maintains an instance of the USBMSC_RWbuf_Info structure.  If double-buffering were used, it would
    // maintain one for both the X and Y side.  (This version of the API only supports single-buffering,
    // so only one structure is maintained.)  This is a shared resource between the API and application; the 
    // application must request the pointers.    
    RWbuf_info = USBMSC_fetchInfoStruct();
  
    
    // USBMSC_updateMediaInfo() must be called prior to USB connection.  We check if the card is present, and if so, pull its size
    // and bytes per block.  
    // LUN0
    mediaInfo.mediaPresent = 0x01;        // The medium is present, because internal flash is non-removable.  
    mediaInfo.mediaChanged = 0x00;        // It can't change, because it's in internal memory, which is always present.  
    mediaInfo.writeProtected = 0x00;      // It's not write-protected
    mediaInfo.lastBlockLba = 774;         // 774 blocks in the volume. (This number is also found twice in the volume itself; see mscFseData.c. They should match.)
    mediaInfo.bytesPerBlock = BYTES_PER_BLOCK; // 512 bytes per block. (This number is also found in the volume itself; see mscFseData.c. They should match.)
    USBMSC_updateMediaInfo(0, &mediaInfo); 
    
    // LUN1
    if(detectCard())
      mediaInfo.mediaPresent = kUSBMSC_MEDIA_PRESENT;
    else mediaInfo.mediaPresent = kUSBMSC_MEDIA_NOT_PRESENT;
    mediaInfo.mediaChanged = 0x00;
    mediaInfo.writeProtected = 0x00;
    disk_ioctl(0,GET_SECTOR_COUNT,&mediaInfo.lastBlockLba);   // Returns the number of blocks (sectors) in the media. 
    mediaInfo.bytesPerBlock = BYTES_PER_BLOCK;                // Block size will always be 512
    USBMSC_updateMediaInfo(1, &mediaInfo); 
    
    
    // At compile-time for this demo, there will be one file on the volume.  The root directory and data cluster
    // for this file need to be initialized.  
    //flashWrite_LBA(Root_Dir, (BYTE*)Root_Dir_init); 
    //flashWrite_LBA(Data559, (BYTE*)Data559_init); 
    
    
    // Configure Timer_A0 to prompt detection of the SD card every second
    TA0CCTL0 = CCIE;                          // Enable interrupt
    TA0CCR0 = 32768;                          // Clock will be 32kHz, so we set the int to occur when it counts to 32768
    TA0CTL = TASSEL_1 + MC_1 + TACLR;         // ACLK = 32kHz, up mode, clear TAR... go!

  
    // If USB is already connected when the program starts up, then there won't be a USB_handleVbusOnEvent(). 
    // So we need to check for it, and manually connect if the host is already present.   
    if (USB_connectionInfo() & kUSB_vbusPresent)
    {
      if (USB_enable() == kUSB_succeed)
      {
        USB_reset();
        USB_connect();      
      }
    }
  
    while(1)
    {
      switch(USB_connectionState())
      {
        case ST_USB_DISCONNECTED:
                 __bis_SR_register(LPM3_bits + GIE); 	       // Enter LPM3 until VBUS-on event
                
                 // Check if the reason we woke was a button press; and if so, log a new piece of data.  
                 if(fS1ButtonEvent)
                 {
                   // Build string
                   char str[14] = "Data entry #0\n";
                   str[12] = logCnt++;                             // Number the entries 0 through....?
                   
                   memcpy(RW_dataBuf, Data559, BYTES_PER_BLOCK);  // Copy data block 559 from flash to RAM buffer
                   memcpy(&RW_dataBuf[DataCnt], str, sizeof(str)); // Write the new entry to the RAM buffer
                   flashWrite_LBA((PBYTE)Data559, RW_dataBuf);    // Copy it back to flash
                   
                   DataCnt += sizeof(str);                         // Increment the index past the new entry
                   if((DataCnt + sizeof(str)>= BYTES_PER_BLOCK))   // Roll index back to 0, if no more room in the block
                     DataCnt = 0;
        
                   fS1ButtonEvent = 0;
                 }
                break;
          
        case ST_USB_CONNECTED_NO_ENUM:
                break;
          
        case ST_ENUM_ACTIVE:             

                // Call USBMSC_poll() to initiate handling of any received SCSI commands.  Disable interrupts 
                // during this function, to avoid conflicts arising from SCSI commands being received from the host
                // AFTER decision to enter LPM is made, but BEFORE it's actually entered (in other words, avoid
                // sleeping accidentally).  
                __disable_interrupt();
                if((USBMSC_poll() == kUSBMSC_okToSleep) && (!bDetectCard))
                {
                    __bis_SR_register(LPM0_bits + GIE);  // Enable interrupts atomically with LPM0 entry
                }
                __enable_interrupt();
                
                                               
                // If the API needs the application to process a buffer, it will keep the CPU awake by returning kUSBMSC_processBuffer
                // from USBMSC_poll().  The application should then check the 'operation' field of all defined USBMSC_RWbuf_Info
                // structure instances.  If any of them is non-null, then an operation needs to be processed.  A value of 
                // kUSBMSC_READ indicates the API is waiting for the application to fetch data from the storage volume, in response 
                // to a SCSI READ command from the USB host.  After the application does this, it must indicate whether the 
                // operation succeeded, and then close the buffer operation by calling USBMSC_bufferProcessed().  
                
                while(RWbuf_info->operation == kUSBMSC_READ)
                {
                  switch(RWbuf_info->lun)
                  {
                    case 0:
                      RWbuf_info->returnCode = Read_LBA(RWbuf_info->lba, RWbuf_info->bufferAddr, RWbuf_info->lbCount); // Fetch a block from the medium, using file system emulation
                      USBMSC_bufferProcessed();                           // Close the buffer operation
                      break;
                      
                    case 1:
                      read_LUN1();
                      break;
                  }
                }
                
                // Everything in this section is analogous to READs.  Reference the comments above.   
                while(RWbuf_info->operation == kUSBMSC_WRITE)
                {                  
                  switch(RWbuf_info->lun)
                  {
                    case 0:
                      RWbuf_info->returnCode = Write_LBA(RWbuf_info->lba, RWbuf_info->bufferAddr, RWbuf_info->lbCount); // Write the block to the medium, using file system emulation
                      USBMSC_bufferProcessed();                            // Close the buffer operation
                      break;
                    case 1:
                      write_LUN1();
                      break;
                  }
                }
                
                // Every second, the Timer_A ISR sets this flag.  The checking can't be done from within the timer ISR, because the
                // checking enables interrupts, and this is not a recommended practice due to the risk of nested interrupts.  
                if(bDetectCard)
                {
                  checkInsertionRemoval();
                  bDetectCard = 0x00;                          // Clear the flag, until the next timer ISR
                }
                
                break;
                
            case ST_ENUM_SUSPENDED:
                __bis_SR_register(LPM3_bits + GIE);            // Enter LPM3, until a resume or VBUS-off event
                break;
              
          case ST_ENUM_IN_PROGRESS:
                break;
              
          case ST_ERROR:
                break;           
          default:;
      }    
    }
}

// This function checks for insertion/removal of the card.  If either is detected, it informs the API
// by calling USBMSC_updateMediaInfo().  Whether it detects it or not, it returns non-zero if the card
// is present, or zero if not present
BYTE checkInsertionRemoval(void)
{
  BYTE newCardStatus = detectCard();                  // Check card status -- there or not?

  if((newCardStatus) && (mediaInfo.mediaPresent == kUSBMSC_MEDIA_NOT_PRESENT)) 
  {
    // An insertion has been detected -- inform the API
    mediaInfo.mediaPresent = kUSBMSC_MEDIA_PRESENT; 
    mediaInfo.mediaChanged = 0x01;
    DRESULT SDCard_result = disk_ioctl(0,GET_SECTOR_COUNT,&mediaInfo.lastBlockLba);  // Get the size of this new medium
    USBMSC_updateMediaInfo(1, &mediaInfo);           
  }
     
  if ((!newCardStatus) && (mediaInfo.mediaPresent == kUSBMSC_MEDIA_PRESENT))  
  {
    // A removal has been detected -- inform the API
    mediaInfo.mediaPresent = kUSBMSC_MEDIA_NOT_PRESENT; 
    mediaInfo.mediaChanged = 0x01;
    USBMSC_updateMediaInfo(1, &mediaInfo);              
  }
  
  return newCardStatus;
}


VOID read_LUN1(VOID)
{
  // A READ operation is underway, and the app has been requested to access the medium.  So, call file system to read 
  // to do so.  Note this is a low level FatFs call -- we are not attempting to open a file ourselves.  The host is
  // in control of this access, we're just carrying it out.  
  DRESULT dresult = disk_read(0,                      // Physical drive number (0)
                              RWbuf_info->bufferAddr, // Pointer to the user buffer 
                              RWbuf_info->lba,        // First LBA of this buffer operation
                              RWbuf_info->lbCount);   // The number of blocks being requested as part of this operation
  
  // The result of the file system call needs to be communicated to the host.  Different file system software uses 
  // different return codes, but they all communicate the same types of results.  This code ultimately gets passed to the
  // host app that issued the command to read (or if the user did it the host OS, perhaps in a dialog box).  
  switch(dresult)
  {
    case RES_OK:
      RWbuf_info->returnCode = kUSBMSC_RWSuccess;
      break;
    case RES_ERROR:                      // In FatFs, this result suggests the medium may have been removed recently.  
      if(!checkInsertionRemoval())       // This application function checks for the SD-card, and if missing, calls USBMSC_updateMediaInfo() to inform the API
        RWbuf_info->returnCode = kUSBMSC_RWMedNotPresent;
      break;                  
    case RES_NOTRDY:
      RWbuf_info->returnCode = kUSBMSC_RWNotReady;
      break;
    case RES_PARERR:
      RWbuf_info->returnCode = kUSBMSC_RWLbaOutOfRange;
     break;
  }
  
  USBMSC_bufferProcessed(); 
}


VOID write_LUN1(VOID)
{
   DRESULT dresult = disk_write(0,                      // Physical drive number (0)
                               RWbuf_info->bufferAddr, // Pointer to the user buffer 
                               RWbuf_info->lba,        // First LBA of this buffer operation
                               RWbuf_info->lbCount);   // The number of blocks being requested as part of this operation
  switch(dresult)
  {
    case RES_OK:
      RWbuf_info->returnCode = kUSBMSC_RWSuccess;
      break;
    case RES_ERROR:
      if(!checkInsertionRemoval())
        RWbuf_info->returnCode = kUSBMSC_RWMedNotPresent;
      break;                  
    case RES_NOTRDY:
      RWbuf_info->returnCode = kUSBMSC_RWNotReady;
      break;
    case RES_PARERR:
      RWbuf_info->returnCode = kUSBMSC_RWLbaOutOfRange;
      break;
    default:
      RWbuf_info->returnCode = kUSBMSC_RWNotReady;
      break;                  
  }
  USBMSC_bufferProcessed(); 

}


#pragma vector = TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void)
{
  bDetectCard = 0x01;                     // Set the flag that will trigger main() to detect the card
  __bic_SR_register_on_exit(LPM0_bits);   // Wake from ISR, if sleeping
}


/***************************************************************************//**
 * @brief  Initializes USB clock
 * @param  none  
 * @return none 
 ******************************************************************************/
void ClockUSB(void)
{
  if (USB_PLL_XT == 2)
  {
    P5SEL |= 0x0C;                                      // Enable the XT2 pins.  Without this, the xtal pins default to being I/O's.  
        
    // Use the REFO oscillator to source the FLL and ACLK
    UCSCTL3 = (UCSCTL3 & ~(SELREF_7)) | (SELREF__REFOCLK);
    UCSCTL4 = (UCSCTL4 & ~(SELA_7)) | (SELA__REFOCLK);
        
    // MCLK will be driven by the FLL (not by XT2), referenced to the REFO
    SFRIE1 &= ~OFIE;
    Init_FLL_Settle(USB_MCLK_FREQ/1000, USB_MCLK_FREQ/32768);  // Start the FLL, at the freq indicated by the config constant USB_MCLK_FREQ
        
    XT2_Start(XT2DRIVE_0);                                        // Start the "USB crystal"
    SFRIE1 |= OFIE;
  }
  else
  {
    P5SEL |= 0x10;                                      // Enable the XT1 pins.  Without this, the xtal pins default to being I/O's.  
        
    // Use the REFO oscillator to source the FLL and ACLK
    UCSCTL3 = SELREF__REFOCLK;             
    UCSCTL4 = (UCSCTL4 & ~(SELA_7)) | (SELA__REFOCLK); 
        
    SFRIE1 &= ~OFIE;
    // MCLK will be driven by the FLL (not by XT2), referenced to the REFO
    Init_FLL_Settle(USB_MCLK_FREQ/1000, USB_MCLK_FREQ/32768); // set FLL (DCOCLK)
        
    XT1_Start(XT1DRIVE_0);                                       // Start the "USB crystal"
    SFRIE1 |= OFIE;
  }
}




/***************************************************************************//**
 * @brief  Initialize the board - configure ports
 * @param  None
 * @return none
 ******************************************************************************/
void Board_init(void)
{
  //setup XT1 and XT2
  P5SEL |= (BIT4 + BIT5) + (BIT2 + BIT3);
  
  //setup LEDs
  P1DIR |= BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5;
  P1OUT &= ~(BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5);
  P8DIR |= BIT1 + BIT2;
  P8OUT &= ~(BIT1 + BIT2);
  
  //configure unused ports for low power
  P2DIR |= BIT0 + BIT1 + BIT3 + BIT4 + BIT6;
  P2OUT &= ~(BIT0 + BIT1 + BIT3 + BIT4 + BIT6);
  
  P3DIR |= BIT0 + BIT1 + BIT2;
  P3OUT &= ~(BIT0 + BIT1 + BIT2);
  
  P4DIR |= BIT0 + BIT6 + BIT7;
  P4OUT &= ~(BIT0 + BIT6 + BIT7);
  
  P5DIR |= BIT1;
  P5OUT &= ~BIT1;
  
  P6DIR |= BIT6 + BIT7;
  P6DIR &= ~(BIT6 + BIT7);
  
  P7DIR |= BIT0 + BIT1 + BIT2 + BIT3 + BIT5 + BIT7;
  P7OUT &= ~(BIT0 + BIT1 + BIT2 + BIT3 + BIT5 + BIT7);
    
}


/***************************************************************************//**
 * @brief  Handles UNMI interrupts
 * @param  none  
 * @return none 
 ******************************************************************************/
#pragma vector = UNMI_VECTOR
__interrupt VOID UNMI_ISR(VOID)
{
    switch (__even_in_range(SYSUNIV, SYSUNIV_SYSBUSIV))
    {
      case SYSUNIV_NONE:
        __no_operation();
        break;
      case SYSUNIV_NMIIFG:
        __no_operation();
        break;
      case SYSUNIV_OFIFG:
        UCSCTL7 &= ~(DCOFFG+XT1LFOFFG+XT2OFFG); // Clear OSC flaut Flags fault flags
        SFRIFG1 &= ~OFIFG;                                // Clear OFIFG fault flag
        break;
      case SYSUNIV_ACCVIFG:
        __no_operation();
        break;
      case SYSUNIV_SYSBUSIV:
        // If bus error occured - the cleaning of flag and re-initializing of USB is required.
        SYSBERRIV = 0;            // clear bus error flag
        USB_disable();            // Disable
    }
}

/***************************************************************************//**
 * @}
 ******************************************************************************/
