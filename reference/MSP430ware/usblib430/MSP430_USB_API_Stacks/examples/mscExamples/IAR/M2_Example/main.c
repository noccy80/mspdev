// USB #includes
#include "USB_API/USB_Common/device.h"
#include "USB_API/USB_Common/types.h"       
#include "USB_config/descriptors.h"
#include "USB_API/USB_Common/usb.h"        
#include <string.h>
#include "F5xx_F6xx_Core_Lib\HAL_UCS.h"
#include "F5xx_F6xx_Core_Lib\HAL_PMM.h"

// MSC #includes
#include "USB_API/USB_MSC_API/UsbMscScsi.h"
#include "USB_API/USB_MSC_API/UsbMsc.h"
#include "USB_API/USB_MSC_API/UsbMscStateMachine.h"

// Board and FatFs #includes
#include "FatFs/diskio.h"               
#include "FatFs/mmc.h"


BYTE checkInsertionRemoval(void);
void Board_init(void);
void ClockUSB(void);


// Every application using this MSC API must define an instance of this structure.  It establishes
// compile-time information about the storage media.  In this example, only a single LUN
// (Logical UNit) is implemented, so only one is created here.    
struct config_struct USBMSC_config = {
    0x00,     // The number of this LUN.  (Ignored in this version of the API.)
    0x00,     // PDT (Peripheral Device Type). 0x00 = "direct-access block device", which includes all magnetic media.  (Ignored in this version of the API.)
    0x80,     // Indicates whether the medium is removable.  0x00 = not removable, 0x80 = removable
    "TI",     // T10 Vendor ID.  Generally not enforced, and has no particular impact on most operating systems.  
    "MSC",    // T10 Product ID.  Selected by the owner of the vendor ID above.  Has no impact on most OSes.  
    "v3.0",   // T10 revision string.  Selected by the owner of the vendor ID above.  Has no impact on most OSes.  
};


// Data-exchange buffer between the API and the application.  The application allocates it, 
// and then registers it with the API.  Later, the API will pass it back to the application when it
// needs the application to "process" it (exchange data with the media).  
uint8_t RWbuf[512];


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
    USBMSC_registerBufInfo(&RWbuf[0], NULL, sizeof(RWbuf));
 
    
    // The API maintains an instance of the USBMSC_RWbuf_Info structure.  If double-buffering were used, it would
    // maintain one for both the X and Y side.  (This version of the API only supports single-buffering,
    // so only one structure is maintained.)  This is a shared resource between the API and application; the 
    // application must request the pointers.    
    RWbuf_info = USBMSC_fetchInfoStruct();
  
    
    // USBMSC_updateMediaInfo() must be called prior to USB connection.  We check if the card is present, and if so, pull its size
    // and bytes per block.  
    if(detectCard())
      mediaInfo.mediaPresent = kUSBMSC_MEDIA_PRESENT;
    else mediaInfo.mediaPresent = kUSBMSC_MEDIA_NOT_PRESENT;
    mediaInfo.mediaChanged = 0x00;
    mediaInfo.writeProtected = 0x00;
    disk_ioctl(0,GET_SECTOR_COUNT,&mediaInfo.lastBlockLba);   // Returns the number of blocks (sectors) in the media. 
    mediaInfo.bytesPerBlock = 0x200;                          // Block size will always be 512
    USBMSC_updateMediaInfo(0, &mediaInfo); 
    
    
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
                _NOP();
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
                
                // Everything in this section is analogous to READs.  Reference the comments above.   
                while(RWbuf_info->operation == kUSBMSC_WRITE)
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
    USBMSC_updateMediaInfo(0, &mediaInfo);           
  }
     
  if ((!newCardStatus) && (mediaInfo.mediaPresent == kUSBMSC_MEDIA_PRESENT))  
  {
    // A removal has been detected -- inform the API
    mediaInfo.mediaPresent = kUSBMSC_MEDIA_NOT_PRESENT; 
    mediaInfo.mediaChanged = 0x01;
    USBMSC_updateMediaInfo(0, &mediaInfo);              
  }
  
  return newCardStatus;
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
