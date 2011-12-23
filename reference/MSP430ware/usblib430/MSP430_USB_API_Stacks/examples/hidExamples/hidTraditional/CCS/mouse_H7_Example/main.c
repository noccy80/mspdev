// (c)2010 by Texas Instruments Incorporated, All Rights Reserved.
/*----------------------------------------------------------------------------*
|                                                                             |
|                              Texas Instruments                              |
|                                                                             |
|                          MSP430 USB-Example (CDC/HID Driver)                |
|                                                                             |
+-----------------------------------------------------------------------------+
|  Source: main.c, v2.0 2010/08/03                                           |
------------------------------------------------------------------------------+   
Mouse HID Demo:

 Sending/Receiving Reports:
 This application creates a traditional HID device, as opposed to a datapipe
 HID device.  It acts as a mouse on the host, moving the pointer in a circular 
 motion on the screen.  To re-gain control of the mouse, you can either remove 
 the USB cable or type the key sequence to exit debug mode (Ctrl+Shift+D in 
 IAR). 

 A custom report descriptor is defined in descriptors.c.  It defines a top-level
 application collection of "Generic Desktop", and a usage of "Mouse".  Windows
 recognizes this configuration as a mouse, and begins servicing it directly.  
 In this way, Windows acts as the "application", rather than using a separate 
 one (like the HID Demo App).  

 While connected to an active USB connection, this application spends most of 
 its time in LPM0.  Timer_A is configured to wake the CPU every 1/60 sec, 
 prompting the main loop to send another HID report.  er, this is unusual 
 and doesn't provide much value.  

 The polling interval in the HID's IN endpoint descriptor is set to 16, meaning
 the host will poll for a report every 16 USB frames (every 16ms).  Since this 
 is slightly less than 1/60 sec, occasionally the host will poll for a report 
 and not find one; this is OK.  
 

+----------------------------------------------------------------------------+
 Please refer to the MSP430 USB API Stack Programmer's Guide,located 
 in the root directory of this installation for more details.
//----------------------------------------------------------------------------*/

#include "USB_API/USB_Common/device.h"
#include "USB_API/USB_Common/types.h"          // Basic Type declarations
#include "USB_config/descriptors.h"
#include "USB_API/USB_Common/usb.h"        // USB-specific functions

#include "F5xx_F6xx_Core_Lib/HAL_UCS.h"
#include "F5xx_F6xx_Core_Lib/HAL_PMM.h"

#ifdef _CDC_
    #include "USB_API/USB_CDC_API/UsbCdc.h"
#endif
#ifdef _HID_
    #include "USB_API/USB_HID_API/UsbHid.h"
#endif

VOID Init_StartUp(VOID);
  
typedef struct 
{
    BYTE buttons;
    BYTE dX;
    BYTE dY;
    BYTE dZ;
} MOUSE_REPORT;
MOUSE_REPORT mouseReport = { 0, 0, 0, 0 };  // HID report, to be sent to the PC. 

const INT tableSinCosLookUp[93][2];         // Lookup table for mouse data; 
BYTE index = 1;                             // Index for lookup table

BYTE sendNewMousePosition = FALSE;          // Flag by which timer tells main
                                            // loop to send a new report


/*----------------------------------------------------------------------------+
| Main Routine                                                                |
+----------------------------------------------------------------------------*/
VOID main(VOID)
{
    WDTCTL = WDTPW + WDTHOLD;	    // Stop watchdog timer
    Init_StartUp();                 //initialize device
    USB_init();                     //init USB

    // Configure an LED to blink when a report is sent
    P1DIR |= 0x01;
    P1OUT &= ~0x01;
    
    // Timer_A will repeatedly run to 547, using 32kHz clock, and then generate
    // an interrupt that wakes the main loop (every 1/60 sec)
    TA0CCTL0 = CCIE;                          // CCR0 interrupt enabled
    TA0CCR0 = 547;                            // 547/32768 = a period of 16.7ms
    TA0CTL = TASSEL_1 + TACLR;                // ACLK, up mode
    
    __enable_interrupt();                     // Enable interrupts globally
    
    USB_setEnabledEvents(kUSB_VbusOnEvent+kUSB_VbusOffEvent+kUSB_receiveCompletedEvent
                          +kUSB_UsbSuspendEvent+kUSB_UsbResumeEvent);

    // In case USB is already attached (meaning no VBUS event will 
    // occur), manually start the connection 
    if (USB_connectionInfo() & kUSB_vbusPresent)
      USB_handleVbusOnEvent();
    
    
    while(1)
    {
      switch(USB_connectionState())
      {
         case ST_USB_DISCONNECTED:
              TA0CTL &= ~MC_1;
               __bis_SR_register(LPM3_bits + GIE); 	  // Enter LPM3 w/interrupt
              _NOP();
              break;
              
         case ST_USB_CONNECTED_NO_ENUM:
              break;
              
         case ST_ENUM_ACTIVE:
                          
              // Start timer
              TA0CTL |= MC_1;
              
              // Enter LPM0, until the timer wakes the CPU
              __bis_SR_register(LPM0_bits + GIE); 	
            
              // Timer has awakened the CPU.  Proceed with main loop...
              if (sendNewMousePosition)   
              {
                // Build the report
                mouseReport.dX = (tableSinCosLookUp[index][0] - tableSinCosLookUp[index-1][0])>>1;
                mouseReport.dY = (tableSinCosLookUp[index][1] - tableSinCosLookUp[index-1][1])>>1;
                
                // Send the report
                USBHID_sendReport((void *)&mouseReport, 0);  
                
                P1OUT ^= 0x01;              // Toggle LED on P1.0
                
                if(index++>=90)
                  index = 1;
                
              }
              break;  
              
         case ST_ENUM_SUSPENDED:
             TA0CTL &= ~MC_1;
             P1OUT &= ~BIT0;        
             __bis_SR_register(LPM3_bits + GIE); 	// Enter LPM3 w/interrupt
             break;
              
         case ST_ENUM_IN_PROGRESS:
              break;
              
         case ST_NOENUM_SUSPENDED:
              __bis_SR_register(LPM3_bits + GIE);                
              break;                
              
         case ST_ERROR:
              _NOP();
              break;
              
         default:;
      } 
    }  // while(1) 
} //main()



/*----------------------------------------------------------------------------+
| System Initialization Routines                                              |
+----------------------------------------------------------------------------*/

VOID Init_Clock(VOID)
{
	#if defined (__MSP430F563x_F663x)
		while(BAKCTL & LOCKIO)                    // Unlock XT1 pins for operation
      	BAKCTL &= ~(LOCKIO);                    // enable XT1 pins
     	// Workaround for USB7
    	UCSCTL6 &= ~XT1OFF;
    #endif
    //Initialization of clock module
    if (USB_PLL_XT == 2)
    {
    	
        #if defined (__MSP430F552x) || defined (__MSP430F550x)
        	P5SEL |= 0x0C;                        // enable XT2 pins for F5529
		#elif defined (__MSP430F563x_F663x)
			P7SEL |= 0x0C;
		#endif
        // Use 32 kHz quarz for FLL and ACLK
        //LFXT_Start();

        // use REFO for FLL and ACLK
        UCSCTL3 = (UCSCTL3 & ~(SELREF_7)) | (SELREF__REFOCLK);
        UCSCTL4 = (UCSCTL4 & ~(SELA_7)) | (SELA__REFOCLK);

        Init_FLL(USB_MCLK_FREQ/1000, USB_MCLK_FREQ/32768);             // set FLL (DCOCLK)
        //XT2_Start(XT2DRIVE_3);
    }
    else
    {
        #if defined (__MSP430F552x) || defined (__MSP430F550x)
        P5SEL |= 0x10;                    // enable XT1 pins
		#endif 
        UCSCTL3 = SELREF__REFOCLK;            // run FLL mit REF_O clock
        UCSCTL4 = (UCSCTL4 & ~(SELA_7)) | (SELA__REFOCLK); // set ACLK = REFO
        Init_FLL(USB_MCLK_FREQ/1000, USB_MCLK_FREQ/32768);       // set FLL (DCOCLK)
        //XT1_Start(XT1DRIVE_3);
    }
    //  SFRIE1 |= OFIFG;                     // Enable OscFault ISR
}

//----------------------------------------------------------------------------

VOID Init_Ports(VOID)
{
    // Initialization of ports (all unused pins as outputs with low-level
    P2OUT = 0x00;
    P2DIR = 0xFF;

    // Initialize port 3
    P3OUT = 0x00;
    P3SEL = 0x03;                           // Assign I2C pins to USCI_B0
    P3DIR = 0xFF;

    // Initialize port 4
    P4OUT = 0x00;
    P4DIR = 0xFF;

    // Initialize all other port pins. Use word-access to initialize
    // two ports simultaneously.
    PCOUT = 0x0000;
    PCDIR = 0xFFFF;
    
    #ifndef __MSP430F550x
    PDOUT   =   0x0000;      //	If using a device other than: 
   	PDDIR   =   0xFFFF;      //	F5510, F5529, F5638, or F6638 
    					    //	you may need to comment out these lines 
    #endif 
    
    #if defined (__MSP430F563x_F663x)
    P9OUT   =   0x00;
    P9DIR   =   0xFF;
    #endif
    
    PJOUT = 0x0000;
    PJDIR = 0xFFFF;
}


//----------------------------------------------------------------------------

VOID Init_StartUp(VOID)
{
    __disable_interrupt();               // Disable global interrupts

    Init_Ports();                        // Init ports (do first ports because clocks do change ports)
    Init_Clock();

    __enable_interrupt();                // enable global interrupts
}

//----------------------------------------------------------------------------

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
        UCSCTL7 &= ~(DCOFFG+0+0+0); // Clear OSC flaut Flags fault flags
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


// Timer0 A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void)
{
  sendNewMousePosition = TRUE;            // Set flag telling main loop to send a report
  __bic_SR_register_on_exit(LPM0_bits);   // Keep CPU awake after returning;
                                          // enables a run through the main loop
}


// Lookup table for mouse position values.  "const" indicates it will be stored
// in flash.  
const INT tableSinCosLookUp[93][2] = 
{
0,200,
14,200,
28,198,
42,196,
55,192,
68,188,
81,183,
94,177,
106,170,
118,162,
129,153,
139,144,
149,134,
158,123,
166,112,
173,100,
180,88,
185,75,
190,62,
194,48,
197,35,
199,21,
200,7,
200,-7,
199,-21,
197,-35,
194,-48,
190,-62,
185,-75,
180,-88,
173,-100,
166,-112,
158,-123,
149,-134,
139,-144,
129,-153,
118,-162,
106,-170,
94,-177,
81,-183,
68,-188,
55,-192,
42,-196,
28,-198,
14,-200,
0,-200,
-14,-200,
-28,-198,
-42,-196,
-55,-192,
-68,-188,
-81,-183,
-94,-177,
-106,-170,
-118,-162,
-129,-153,
-139,-144,
-149,-134,
-158,-123,
-166,-112,
-173,-100,
-180,-88,
-185,-75,
-190,-62,
-194,-48,
-197,-35,
-199,-21,
-200,-7,
-200,7,
-199,21,
-197,35,
-194,48,
-190,62,
-185,75,
-180,88,
-173,100,
-166,112,
-158,123,
-149,134,
-139,144,
-129,153,
-118,162,
-106,170,
-94,177,
-81,183,
-68,188,
-55,192,
-42,196,
-28,198,
-14,200,
0,200
};

/*----------------------------------------------------------------------------+
| End of source file                                                          |
+----------------------------------------------------------------------------*/
/*------------------------ Nothing Below This Line --------------------------*/
