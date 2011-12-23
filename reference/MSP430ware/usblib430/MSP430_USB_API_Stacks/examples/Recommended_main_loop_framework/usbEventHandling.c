// KLQ 10/31/10

#include "USB_API/USB_Common/device.h"
#include "USB_API/USB_Common/types.h"
#include "USB_API/USB_Common/defMSP430USB.h"
#include "USB_config/descriptors.h"
#include "USB_API/USB_Common/usb.h"
#include "F5xx_F6xx_Core_Lib/HAL_UCS.h"

#ifdef _CDC_
#include "USB_API/USB_CDC_API/UsbCdc.h"
#endif

#ifdef _HID_
#include "USB_API/USB_HID_API/UsbHid.h"
#endif

#ifdef _MSC_
#include "USB_API/USB_MSC_API/UsbMsc.h"
#endif


/*
If this function gets executed, it's a sign that the output of the USB PLL has failed.
returns TRUE to keep CPU awake
*/
BYTE USB_handleClockEvent()
{
     // Something happened to the PLL.  This might also show up in the system as an oscillator fault on XT2.  
     // The USB connection is probably lost.  Software should ensure any faults on XT2 are resolved, 
     // then can attempt to call USB_enable()/USB_connect() again.  
     USB_disconnect();
     USB_disable();

     return TRUE;   // Since this event is associated with a change in state, it's a good practice to return TRUE so the main loop can adapt.
}

/*
If this function gets executed, it indicates that a valid voltage has just been applied to the VBUS pin.
returns TRUE to keep CPU awake
*/
BYTE USB_handleVbusOnEvent()
{
    // The standard user experience when a USB device gets physically attached to a host is for the host to
    // enumerate the device.  Typically this happens as follows: 
    // 1) the device senses 5V VBUS from the host, which tells it a host is present; (usually; but could also be a powered hub w/o a host!  See state ST_NOENUM_SUSPENDED.) 
    // 2) the device asserts the PUR signal, which tells the host the devicde is present;   
    // 3) the host issues a number of USB device requests, including asking for the device's USB descriptors;  
    // 4) the host decides if it has the appropriate driver for what it sees in the descriptors; and if so, loads it.  Enumeration is now complete.  
    // So -- USB_handleVbusOnEvent occurs if a VBUS-on event has been detected.  We respond by doing the following.  
    // However, keep in mind that USB_enable() might take a few milliseconds while the crystal starts up, and that most events handle in
    // the context of the USB interrupt handler.  If this interrupt latency is unacceptable, it might be better to set a flag for main() to handle it.  
    if (USB_enable() == kUSB_succeed)      // Start the module; 
    {
        USB_reset();                       // Reset the internal API
        USB_connect();                     // Assert PUR, to tell the host we're here
    }                                      // Enumeration will now take place in the background
    return TRUE;                           // Meanwhile, return TRUE to wake the main loop (if LPM was entered), so 
}                                          // that it can take into account the change in state

/*
If this function gets executed, it indicates that a valid voltage has just been removed from the VBUS pin.
returns TRUE to keep CPU awake
*/
BYTE USB_handleVbusOffEvent()
{
    // Typically there's no need to place code here -- the main loop simply shifts to ST_USB_DISCONNECTED.  

    return TRUE;   // Since this event is associated with a change in state, it's a good practice to return TRUE so the main loop can adapt.
}

/*
If this function gets executed, it indicates that the USB host has issued a USB reset event to the device.
returns TRUE to keep CPU awake
*/
BYTE USB_handleResetEvent()
{
    return TRUE;   
}

/*
If this function gets executed, it indicates that the USB host has chosen to suspend this device after a period of active operation.
returns TRUE to keep CPU awake
*/
BYTE USB_handleSuspendEvent()
{
    // If this device draws power from the host over VBUS, then this event is the signal for software to ensure that
    // no more than 2.5mA is drawn over VBUS.  Code can be placed here to do this, or it can be placed in the main loop
    // under ST_ENUM_SUSPENDED (but make sure this handler returns TRUE to wake the main loop, if LPM0 was entered).  
  
  
    // Or, if the device was attached to a bus situation that's somehow providing VBUS but has no active host (host is in standby,
    // or attached to a powered hub with no upstream host), then this will show up as a suspend event without successful enumeration.  
    // A good course of action might be to "cancel" the attempt to enumerate:
    if(!(USB_connectionInfo() & kUSB_Enumerated))
    {
      USB_disconnect();
      USB_disable();
    }  // Now, if this branch executes, the USB state will shift to ST_USB_DISCONNECTED when the function returns.  
    
    
    return TRUE;   // Return TRUE so that the main loop can adapt.
}

/*
If this function gets executed, it indicates that the USB host has chosen to resume this device after a period of suspended operation.
returns TRUE to keep CPU awake
*/
BYTE USB_handleResumeEvent()
{
    // If functionality was shut off during USB_handleSuspendEvent(), it can be re-enabled here.  

    return TRUE;   // Since this event is associated with a change in state, it's a good practice to return TRUE so the main loop can adapt.  
}

/*
If this function gets executed, it indicates that the USB host has enumerated this device :
after host assigned the address to the device. 
returns TRUE to keep CPU awake
*/
BYTE USB_handleEnumCompleteEvent()
{
    // Typically there's no need to place code here -- the main loop shifts to ST_ENUM_ACTIVE.  
  
    return TRUE;   // Since this event is associated with a change in state, it's a good practice to return TRUE so the main loop can adapt.
}                   



#ifdef _CDC_

/*
This event indicates that data has been received for interface intfNum, but no data receive operation is underway.
returns TRUE to keep CPU awake
*/
BYTE USBCDC_handleDataReceived(BYTE intfNum)
{
    //TO DO: You can place your code here

    return FALSE;   //return TURE to wake up after data was received
}

/*
This event indicates that a send operation on interface intfNum has just been completed.
returns TRUE to keep CPU awake
*/
BYTE USBCDC_handleSendCompleted(BYTE intfNum)
{
    //TO DO: You can place your code here

    return FALSE;   //return FALSE to go asleep after interrupt (in the case the CPU slept before interrupt)
}

/*
This event indicates that a receive operation on interface intfNum has just been completed.
*/
BYTE USBCDC_handleReceiveCompleted(BYTE intfNum)
{
    //TO DO: You can place your code here

    return FALSE;   //return FALSE to go asleep after interrupt (in the case the CPU slept before interrupt)
}

#endif // _CDC_

#ifdef _HID_

/*
This event indicates that data has been received for interface intfNum, but no data receive operation is underway.
returns TRUE to keep CPU awake
*/
BYTE USBHID_handleDataReceived(BYTE intfNum)
{
    //TO DO: You can place your code here

    return FALSE;   //return FALSE to go asleep after interrupt (in the case the CPU slept before interrupt)
}

/*
This event indicates that a send operation on interface intfNum has just been completed.
returns TRUE to keep CPU awake
*/
BYTE USBHID_handleSendCompleted(BYTE intfNum)
{
    //TO DO: You can place your code here

    return FALSE;   //return FALSE to go asleep after interrupt (in the case the CPU slept before interrupt)
}

/*
This event indicates that a receive operation on interface intfNum has just been completed.
*/
BYTE USBHID_handleReceiveCompleted(BYTE intfNum)
{
    //TO DO: You can place your code here

    return FALSE;   //return FALSE to go asleep after interrupt (in the case the CPU slept before interrupt)
}

#endif // _HID_

#ifdef _MSC_
BYTE USBMSC_handleBufferEvent(VOID)
{

    return FALSE;	//return FALSE to go asleep after interrupt (in the case the CPU slept before interrupt)

}
#endif // _MSC_


/*----------------------------------------------------------------------------+
| End of source file                                                          |
+----------------------------------------------------------------------------*/
/*------------------------ Nothing Below This Line --------------------------*/
