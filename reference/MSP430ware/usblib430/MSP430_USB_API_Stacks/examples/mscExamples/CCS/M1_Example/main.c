// (c)2010 by Texas Instruments Incorporated, All Rights Reserved.

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
#include "mscFseData.h"
#include "mscFse.h"

void Init_StartUp();               // Initialize clocks, power, and I/Os


// The number of bytes per block.  In FAT, this is 512
const WORD BYTES_PER_BLOCK = 512;


// Data-exchange buffer between the API and the application.  The application allocates it, 
// and then registers it with the API.  Later, the API will pass it back to the application when it
// needs the application to "process" it (exchange data with the media).  
__no_init BYTE RW_dataBuf[512 * 2];


// The API allocates an instance of structure type USBMSC_RWbuf_Info to hold all information describing  
// buffers to be processed.  The structure instance is a shared resource between the API and application.  
// During initialization, we'll call USBMSC_fetchInfoStruct() to obtain the pointer from the API.    
USBMSC_RWbuf_Info *RWbuf;


volatile BYTE fS1ButtonEvent = 0;  // Flag indicating button S1 was pressed (that is, button S1 on a F552x FET target board)
WORD DataCnt = 0;                  // The index of the next available byte to be written within Data[]
BYTE logCnt = 0x30;                // Holds an incrementing character to be written into each new data log entry


/*----------------------------------------------------------------------------+
| Main Routine                                                                |
+----------------------------------------------------------------------------*/
VOID main(VOID)
{
    WDTCTL = WDTPW + WDTHOLD;	    // Stop watchdog timer
    Init_StartUp();                 // Initialize clocks, power, I/Os
    __enable_interrupt(); 
    USB_init();                     // Initialize the USB module


    // Enable all USB events
    USB_setEnabledEvents(kUSB_allUsbEvents);

    
    // The data interchange buffer (used when handling SCSI READ/WRITE) is declared by the application, and 
    // registered with the API using this function.  This allows it to be assigned dynamically, giving 
    // the application more control over memory management.  
    USBMSC_registerBufInfo(&RW_dataBuf[0], NULL, sizeof(RW_dataBuf));
   
    
    // The API maintains an instance of the USBMSC_RWbuf_Info structure.  If double-buffering were used, it would
    // maintain one for both the X and Y side.  (This version of the API only supports single-buffering,
    // so only one structure is maintained.)  This is a shared resource between the API and application; the 
    // application must request the pointers.  This function returns the pointer for a given LUN and buffer side.  
    RWbuf = USBMSC_fetchInfoStruct();  // 0 for X-buffer
    
    
    // The application must tell the API about the media.  Since the media isn't removable, this is only called 
    // once, at the beginning of execution.  If the media were removeable, the application must call this any time
    // the status of the media changes.  
    struct USBMSC_mediaInfoStr mediainfo; // This struct type contains information about the state of the medium.   
                                          // Since it's only used locally, it's declared within main so that it's 
                                          // taken from the heap rather than as a static global.
    mediainfo.mediaPresent = 0x01;        // The medium is present, because internal flash is non-removable.  
    mediainfo.mediaChanged = 0x00;        // It can't change, because it's in internal memory, which is always present.  
    mediainfo.writeProtected = 0x00;      // It's not write-protected
    mediainfo.lastBlockLba = 774;         // 774 blocks in the volume. (This number is also found twice in the volume itself; see mscFseData.c. They should match.)
    mediainfo.bytesPerBlock = BYTES_PER_BLOCK; // 512 bytes per block. (This number is also found in the volume itself; see mscFseData.c. They should match.)
    USBMSC_updateMediaInfo(0, &mediainfo); 
    
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
                // AFTER decision to enter LPM is made, but BEFORE it's actually entered (avoid sleeping accidentally).  
                __disable_interrupt();
                if(USBMSC_poll() == kUSBMSC_okToSleep)
                {
                    __bis_SR_register(LPM0_bits + GIE);  // Enable interrupts atomically with LPM0 entry
                }
                __enable_interrupt();
                        
                            
                // If the API needs the application to process a buffer, it will keep the CPU awake by returning kUSBMSC_processBuffer
                // from USBMSC_poll().  The application should respond by checking the 'operation' field of all defined USBMSC_RWbuf_Info
                // structure instances.  If any of them is non-null, then an operation needs to be processed.  A value of 
                // kUSBMSC_READ indicates the API is waiting for the application to fetch data from the storage volume, in response 
                // to a SCSI READ command from the USB host.  After doing so, we must indicate whether the operation succeeded, and 
                // close the buffer operation by calling USBMSC_bufferProcessed().  
                while(RWbuf->operation == kUSBMSC_READ)
                {
                  RWbuf->returnCode = Read_LBA(RWbuf->lba, RWbuf->bufferAddr, RWbuf->lbCount); // Fetch a block from the medium, using file system emulation
                  USBMSC_bufferProcessed();                           // Close the buffer operation
                }
                
                // Same as above, except for WRITE.  If operation == kUSBMSC_WRITE, then the API is waiting for us to 
                // process the buffer by writing the contents to the storage volume.  
                while(RWbuf->operation == kUSBMSC_WRITE)
                {
                  RWbuf->returnCode = Write_LBA(RWbuf->lba, RWbuf->bufferAddr, RWbuf->lbCount); // Write the block to the medium, using file system emulation
                  USBMSC_bufferProcessed();                            // Close the buffer operation
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
    }  // while(1)
} //main()


// PORT1 interrupt service routine.  Check for button S1 (on a F552x FET target board) being pressed.  
#pragma vector=PORT1_VECTOR
__interrupt VOID Port1InterruptHandler(VOID)
{
    WORD P1IV_isr = P1IV; // port1 interrupt
    fS1ButtonEvent = 1;   // Set boolean flag
    P1IFG = 0;            // Clear I/O interrupt flags
    __bic_SR_register_on_exit(LPM3_bits);  // Keep CPU awake when this ISR exits; resume execution from LPMx entry
}



//-------------------------------------------------------------------------------



/*----------------------------------------------------------------------------+
| System Initialization Routines                                              |
+----------------------------------------------------------------------------*/

// This function initializes the F5xx Universal Clock System (UCS):
// MCLK/SMCLK:  driven by the DCO/FLL, set to USB_MCLK_FREQ (a configuration constant defined by the Descriptor Tool)
// ACLK:  the internal REFO oscillator
// FLL reference:  the REFO
// This function anticipates any MSP430 USB device (F552x/1x/0x, F563x/663x), based on the project settings.  

VOID Init_Clock(VOID)
{
#   if defined (__MSP430F563x_F663x)
		while(BAKCTL & LOCKIO)                    // Unlock XT1 pins for operation
      	BAKCTL &= ~(LOCKIO);                    // enable XT1 pins
     	// Workaround for USB7
    	UCSCTL6 &= ~XT1OFF;
#   endif
    
    //Initialization of clock module
    if (USB_PLL_XT == 2)
    {
#       if defined (__MSP430F552x) || defined (__MSP430F550x)
        	P5SEL |= 0x0C;                        // enable XT2 pins for F5529
#       elif defined (__MSP430F563x_F663x)
			P7SEL |= 0x0C;
#       endif
        // use REFO for FLL and ACLK
        UCSCTL3 = (UCSCTL3 & ~(SELREF_7)) | (SELREF__REFOCLK);
        UCSCTL4 = (UCSCTL4 & ~(SELA_7)) | (SELA__REFOCLK);
         
        Init_FLL(USB_MCLK_FREQ/1000, USB_MCLK_FREQ/32768);             // set FLL (DCOCLK)
        XT2_Start(XT2DRIVE_3);
    }
    else
    {
#       if defined (__MSP430F552x) || defined (__MSP430F550x)
            P5SEL |= 0x10;                    // enable XT1 pins
#       endif 
        UCSCTL3 = SELREF__REFOCLK;            // run FLL mit REF_O clock
        UCSCTL4 = (UCSCTL4 & ~(SELA_7)) | (SELA__REFOCLK); // set ACLK = REFO
        Init_FLL(USB_MCLK_FREQ/1000, USB_MCLK_FREQ/32768);       // set FLL (DCOCLK)
        XT1_Start(XT1DRIVE_3);
    }
    //  SFRIE1 |= OFIFG;                     // Enable OscFault ISR
}

//----------------------------------------------------------------------------

// This function initializes the I/Os.  It expects to be running on an MSP430 FET target board; so
// if using on another board, it's a good idea to double-check these settings.  It sets most of the
// I/Os as outputs, to eliminate floating inputs, for optimum power usage.  
// This function anticipates any MSP430 USB device (F552x/1x/0x, F563x/663x), based on the project settings.  

VOID Init_Ports(VOID)
{
    // Initialization of ports all unused pins as outputs with low-level

    // set all ports  to low on all pins
    PAOUT   =   0x0000;
    PASEL   =   0x0000;
    PADIR   =   0xFFFF;

    PBOUT   =   0x0000;
    PBSEL   =   0x0000;
    PBDIR   =   0xFFFF;

    PCOUT   =   0x0000;
    PCSEL   =   0x0000;
    PCDIR   =   0xFFFF;

#   ifndef __MSP430F550x
        PDOUT   =   0x0000;      //	If using a device other than: 
        PDSEL   =   0x0000;	     //	F5510, F5529, F5638, or F6638 
        PDDIR   =   0xFFFF;      //	you may need to comment out these lines 
#   endif 
    
#   if defined (__MSP430F563x_F663x)
        P9OUT   =   0x00;
        P9SEL   =   0x00;
        P9DIR   =   0xFF;
#   endif

    PJDIR   =   0xFFFF;
    PJOUT   =   0x0000;
}


//----------------------------------------------------------------------------

VOID Init_StartUp(VOID)
{
   unsigned short bGIE;
   bGIE  = (__get_SR_register() &GIE);  //save interrupt status

   __disable_interrupt();               // Disable global interrupts
    
#   ifdef __MSP430F6638    
        // only for F663x devices!
        while (BAKCTL & LOCKBAK)            // check if bit for backup subsystem is cleared
        {
            BAKCTL &= ~LOCKBAK;             // clear lock backup bit for backup subsystem 
        }
#   endif
    
    Init_Ports();                        // Init ports (do first ports because clocks do change ports)
    SetVCore(3);                         // USB core requires the VCore set to 1.8 volt, independ of CPU clock frequency
    Init_Clock();

# if 0  // Use for FET boards
    // Configure P1.6 as a button input
    P1DIR &= ~BIT6; // Input
    P1OUT |= BIT6;  
    P1REN |= BIT6;  // Together with P1OUT, creates a pullup
    P1IFG &= ~BIT6; // Clear the flag
    P1IE |= BIT6;   // Enable interrupts

# else  // Use for F5529 EXP board
    P1DIR &= ~BIT7; // Input
    P1OUT |= BIT7;  
    P1REN |= BIT7;  // Together with P1OUT, creates a pullup
    P1IFG &= ~BIT7; // Clear the flag
    P1IE |= BIT7;   // Enable interrupts
# endif
    
    __bis_SR_register(bGIE); //restore interrupt status
}


#pragma vector = UNMI_VECTOR
__interrupt VOID UNMI_ISR(VOID)
{
    switch (__even_in_range(SYSUNIV, SYSUNIV_BUSIFG))
    {
    case SYSUNIV_NONE:
      __no_operation();
      break;
    case SYSUNIV_NMIIFG:
      __no_operation();
      break;
    case SYSUNIV_OFIFG:
      UCSCTL7 &= ~(DCOFFG+0+0+XT2OFFG); // Clear OSC flaut Flags fault flags
      SFRIFG1 &= ~OFIFG;                                // Clear OFIFG fault flag
      break;
    case SYSUNIV_ACCVIFG:
      __no_operation();
      break;
    case SYSUNIV_BUSIFG:

      // If bus error occurred - the cleaning of flag and re-initializing of USB is required.
      SYSBERRIV = 0;            // clear bus error flag
      USB_disable();            // Disable
    }
}

/*----------------------------------------------------------------------------+
| End of source file                                                          |
+----------------------------------------------------------------------------*/
/*------------------------ Nothing Below This Line --------------------------*/

