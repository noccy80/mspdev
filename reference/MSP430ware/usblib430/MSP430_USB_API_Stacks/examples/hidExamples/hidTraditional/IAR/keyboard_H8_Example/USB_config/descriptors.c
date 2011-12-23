// (c)2010 by Texas Instruments Incorporated, All Rights Reserved.
/*-----------------------------------------------------------------------------+
|                                                                              |
|                              Texas Instruments                               |
|                                                                              |
|    This is an automatically generated script by MSP430 USB Descriptor Tool   |
|                                                                              |
|    Descriptor Tool Version: 3.0.10                                            |
|    Date: 2011/02/24 16:32:49                                                 |
|                                                                              |
|                                Descriptor.c                                  |
|-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------+
| Include files                                                                |
|-----------------------------------------------------------------------------*/
#include <USB_API/USB_Common/device.h>
#include <USB_API/USB_Common/types.h>                // Basic Type declarations
#include <USB_API/USB_Common/defMSP430USB.h>
#include <USB_API/USB_Common/usb.h>              // USB-specific Data Structures
#include "descriptors.h"
#include <USB_API/USB_CDC_API/UsbCdc.h>
#include <USB_API/USB_HID_API/UsbHidReq.h>

/*-----------------------------------------------------------------------------+
| Device Descriptor                                                            |
|-----------------------------------------------------------------------------*/
BYTE const abromDeviceDescriptor[SIZEOF_DEVICE_DESCRIPTOR] = {
    SIZEOF_DEVICE_DESCRIPTOR,               // Length of this descriptor
    DESC_TYPE_DEVICE,                       // Type code of this descriptor
    0x00, 0x02,                             // Release of USB spec
    0x00,                                   // Device's base class code
    0x00,                                   // Device's sub class code
    0x00,                                   // Device's protocol type code
    EP0_PACKET_SIZE,                        // End point 0's packet size
    USB_VID&0xFF, USB_VID>>8,               // Vendor ID for device, TI=0x0451
                                            // You can order your own VID at www.usb.org
    USB_PID&0xFF, USB_PID>>8,               // Product ID for device,
                                            // this ID is to only with this example
    VER_FW_L, VER_FW_H,                     // Revision level of device
    1,                                      // Index of manufacturer name string desc
    2,                                      // Index of product name string desc
    USB_STR_INDEX_SERNUM,                   // Index of serial number string desc
    1                                       //  Number of configurations supported
};

/*-----------------------------------------------------------------------------+
| Configuration Descriptor                                                     |
|-----------------------------------------------------------------------------*/
const struct abromConfigurationDescriptorGroup abromConfigurationDescriptorGroup=
{
    /* Generic part */
    {
        // CONFIGURATION DESCRIPTOR (9 bytes)
        SIZEOF_CONFIG_DESCRIPTOR,                          // bLength
        DESC_TYPE_CONFIG,                                  // bDescriptorType
        DESCRIPTOR_TOTAL_LENGTH, 0x00,                     // wTotalLength
        USB_NUM_INTERFACES,                 	           // bNumInterfaces
        USB_CONFIG_VALUE,                                  // bConfigurationvalue
        CONFIG_STRING_INDEX,                               // iConfiguration Description offset
        USB_SUPPORT_SELF_POWERED | USB_SUPPORT_REM_WAKE,   // bmAttributes, bus power, remote wakeup
        USB_MAX_POWER                                      // Max. Power Consumption
    },

    /******************************************************* start of HID*************************************/
    {
	/*start HID[0] Here */
        {
            //-------- Descriptor for HID class device -------------------------------------
            // INTERFACE DESCRIPTOR (9 bytes) 
            SIZEOF_INTERFACE_DESCRIPTOR,        // bLength 
            DESC_TYPE_INTERFACE,                // bDescriptorType: 4 
            HID0_REPORT_INTERFACE,              // bInterfaceNumber
            0x00,                               // bAlternateSetting
            2,                                  // bNumEndpoints
            0x03,                               // bInterfaceClass: 3 = HID Device
            0,                                  // bInterfaceSubClass:
            0,                                  // bInterfaceProtocol:
            INTF_STRING_INDEX + 0,              // iInterface:1

            // HID DESCRIPTOR (9 bytes)
            0x09,     			                // bLength of HID descriptor
            0x21,             		            // HID Descriptor Type: 0x21
            0x01,0x01,			                // HID Revision number 1.01
            0x00,			                    // Target country, nothing specified (00h)
            0x01,			                    // Number of HID classes to follow
            0x22,			                    // Report descriptor type
            (SIZEOF_REPORT_DESCRIPTOR& 0x0ff),  // Total length of report descriptor
            (SIZEOF_REPORT_DESCRIPTOR >>8),

            SIZEOF_ENDPOINT_DESCRIPTOR,         // bLength
            DESC_TYPE_ENDPOINT,                 // bDescriptorType
            HID0_INEP_ADDR,                     // bEndpointAddress; bit7=1 for IN, bits 3-0=1 for ep1
            EP_DESC_ATTR_TYPE_INT,              // bmAttributes, interrupt transfers
            0x40, 0x00,                         // wMaxPacketSize, 64 bytes
            48,                                  // bInterval, ms

            SIZEOF_ENDPOINT_DESCRIPTOR,         // bLength
            DESC_TYPE_ENDPOINT,                 // bDescriptorType
            HID0_OUTEP_ADDR,                    // bEndpointAddress; bit7=1 for IN, bits 3-0=1 for ep1
            EP_DESC_ATTR_TYPE_INT,              // bmAttributes, interrupt transfers
            0x40, 0x00,                         // wMaxPacketSize, 64 bytes
            48,                                  // bInterval, ms
	         /* end of HID[0]*/
        }

    },
    /******************************************************* end of HID**************************************/

};
/*-----------------------------------------------------------------------------+
| String Descriptor                                                            |
|-----------------------------------------------------------------------------*/
BYTE const abromStringDescriptor[] = {

	// String index0, language support
	4,		// Length of language descriptor ID
	3,		// LANGID tag
	0x09, 0x04,	// 0x0409 for English

	// String index1, Manufacturer
	36,		// Length of this string descriptor
	3,		// bDescriptorType
	'T',0x00,'e',0x00,'x',0x00,'a',0x00,'s',0x00,' ',0x00,
	'I',0x00,'n',0x00,'s',0x00,'t',0x00,'r',0x00,'u',0x00,
	'm',0x00,'e',0x00,'n',0x00,'t',0x00,'s',0x00,

	// String index2, Product
	48,		// Length of this string descriptor
	3,		// bDescriptorType
	'M',0x00,'S',0x00,'P',0x00,'4',0x00,'3',0x00,'0',0x00,
	'-',0x00,'b',0x00,'a',0x00,'s',0x00,'e',0x00,'d',0x00,
	' ',0x00,'H',0x00,'I',0x00,'D',0x00,' ',0x00,'D',0x00,
	'e',0x00,'v',0x00,'i',0x00,'c',0x00,'e',0x00,

	// String index3, Serial Number
	4,		// Length of this string descriptor
	3,		// bDescriptorType
	'0',0x00,

	// String index4, Configuration String
	22,		// Length of this string descriptor
	3,		// bDescriptorType
	'M',0x00,'S',0x00,'P',0x00,'4',0x00,'3',0x00,'0',0x00,
	' ',0x00,'U',0x00,'S',0x00,'B',0x00,

	// String index5, Interface String
	48,		// Length of this string descriptor
	3,		// bDescriptorType
	'M',0x00,'S',0x00,'P',0x00,'4',0x00,'3',0x00,'0',0x00,
	'-',0x00,'b',0x00,'a',0x00,'s',0x00,'e',0x00,'d',0x00,
	' ',0x00,'H',0x00,'I',0x00,'D',0x00,' ',0x00,'D',0x00,
	'e',0x00,'v',0x00,'i',0x00,'c',0x00,'e',0x00
};

BYTE const abromReportDescriptor[SIZEOF_REPORT_DESCRIPTOR]=
{
	0x05, 0x01, 	                // Usage Page (Generic Desktop)
	0x09, 0x06,		                // Usage (Keyboard)
	0xA1, 0x01,		                // Collection (Application)

	0x05, 0x07,		                // Usage Page (Key Codes)
	0x19, 0xE0,		                // Usage Minimum (224)
	0x29, 0xE7,		                // Usage Maximum (231)
	0x15, 0x00,		                // Logical Minimum (0)
	0x25, 0x01,		                // Logical Maximum (1)
	0x75, 0x01,		                // Report Size (1)
	0x95, 0x08,		                // Report Count (8)
	0x81, 0x02,		                // Input (Data, Variable, Absolute) -- Modifier byte
	0x95, 0x01,		                // Report Count (1)
	0x75, 0x08,	 	                // Report Size (8)
	0x81, 0x03,		 				// (81 01) Input (Constant) -- Reserved byte
	
	0x95, 0x05,		  				// Report Count (5)
	0x75, 0x01,						// Report Size (1)
	0x05, 0x08,						// Usage Page (Page# for LEDs)
	0x19, 0x01,						// Usage Minimum (1)
	0x29, 0x05,						// Usage Maximum (5)
	0x91, 0x02,						// Output (Data, Variable, Absolute) -- LED report
	0x95, 0x01,						// Report Count (1)
	0x75, 0x03,						// Report Size (3)
	0x91, 0x03,						// (91 03) Output (Constant) -- LED report padding
	
	0x95, 0x06,						// Report Count (6)
	0x75, 0x08,						// Report Size (8)
	0x15, 0x00,						// Logical Minimum (0)
	0x25, 0x66,						// Logical Maximum(102)  // was 0x65

	0x05, 0x07,						// Usage Page (Key Codes)
	0x19, 0x00,						// Usage Minimum (0)
	0x29, 0x66,						// Usage Maximum (102) // was 0x65
	0x81, 0x00,						// Input (Data, Array) -- Key arrays (6 bytes)
	0xC0							// End Collection
};

/**** Populating the endpoint information handle here ****/

const struct tUsbHandle stUsbHandle[]=
{
	{
        HID0_INEP_ADDR,
        HID0_OUTEP_ADDR,
        0, 
        HID_CLASS,
        0,
        0,
        OEP1_X_BUFFER_ADDRESS,
        OEP1_Y_BUFFER_ADDRESS,
        IEP1_X_BUFFER_ADDRESS,
        IEP1_Y_BUFFER_ADDRESS
    }
};
//-------------DEVICE REQUEST LIST---------------------------------------------

const tDEVICE_REQUEST_COMPARE tUsbRequestList[] = 
{

    //---- HID 0 Class Requests -----//
    USB_REQ_TYPE_INPUT | USB_REQ_TYPE_CLASS | USB_REQ_TYPE_INTERFACE,
    USB_REQ_GET_REPORT,
    0xff,0xff,
    HID0_REPORT_INTERFACE,0x00,
    0xff,0xff,
    0xcc,&usbGetReport,

    // SET REPORT
    USB_REQ_TYPE_OUTPUT | USB_REQ_TYPE_CLASS | USB_REQ_TYPE_INTERFACE,
    USB_REQ_SET_REPORT,
    0xff,0xFF,                          // bValueL is index and bValueH is type
    HID0_REPORT_INTERFACE,0x00,
    0xff,0xff,
    0xcc,&usbSetReport,
    // GET REPORT DESCRIPTOR
    USB_REQ_TYPE_INPUT | USB_REQ_TYPE_STANDARD | USB_REQ_TYPE_INTERFACE,
    USB_REQ_GET_DESCRIPTOR,
    0xff,DESC_TYPE_REPORT,              // bValueL is index and bValueH is type
    HID0_REPORT_INTERFACE,0x00,
    0xff,0xff,
    0xdc,&usbGetReportDescriptor,

    // GET HID DESCRIPTOR
    USB_REQ_TYPE_INPUT | USB_REQ_TYPE_STANDARD | USB_REQ_TYPE_INTERFACE,
    USB_REQ_GET_DESCRIPTOR,
    0xff,DESC_TYPE_HID,                 // bValueL is index and bValueH is type
    HID0_REPORT_INTERFACE,0x00,
    0xff,0xff,
    0xdc,&usbGetHidDescriptor,

    //---- USB Standard Requests -----//
    // clear device feature
    USB_REQ_TYPE_OUTPUT | USB_REQ_TYPE_STANDARD | USB_REQ_TYPE_DEVICE,
    USB_REQ_CLEAR_FEATURE,
    FEATURE_REMOTE_WAKEUP,0x00,         // feature selector
    0x00,0x00,
    0x00,0x00,
    0xff,&usbClearDeviceFeature,

    // clear endpoint feature
    USB_REQ_TYPE_OUTPUT | USB_REQ_TYPE_STANDARD | USB_REQ_TYPE_ENDPOINT,
    USB_REQ_CLEAR_FEATURE,
    FEATURE_ENDPOINT_STALL,0x00,
    0xff,0x00,
    0x00,0x00,
    0xf7,&usbClearEndpointFeature,

    // get configuration
    USB_REQ_TYPE_INPUT | USB_REQ_TYPE_STANDARD | USB_REQ_TYPE_DEVICE,
    USB_REQ_GET_CONFIGURATION,
    0x00,0x00, 
    0x00,0x00, 
    0x01,0x00,
    0xff,&usbGetConfiguration,

    // get device descriptor
    USB_REQ_TYPE_INPUT | USB_REQ_TYPE_STANDARD | USB_REQ_TYPE_DEVICE,
    USB_REQ_GET_DESCRIPTOR,
    0xff,DESC_TYPE_DEVICE,              // bValueL is index and bValueH is type
    0xff,0xff,
    0xff,0xff,
    0xd0,&usbGetDeviceDescriptor,

    // get configuration descriptor
    USB_REQ_TYPE_INPUT | USB_REQ_TYPE_STANDARD | USB_REQ_TYPE_DEVICE,
    USB_REQ_GET_DESCRIPTOR,
    0xff,DESC_TYPE_CONFIG,              // bValueL is index and bValueH is type
    0xff,0xff,
    0xff,0xff,
    0xd0,&usbGetConfigurationDescriptor,

    // get string descriptor
    USB_REQ_TYPE_INPUT | USB_REQ_TYPE_STANDARD | USB_REQ_TYPE_DEVICE,
    USB_REQ_GET_DESCRIPTOR,
    0xff,DESC_TYPE_STRING,              // bValueL is index and bValueH is type
    0xff,0xff,
    0xff,0xff,
    0xd0,&usbGetStringDescriptor,

    // get interface
    USB_REQ_TYPE_INPUT | USB_REQ_TYPE_STANDARD | USB_REQ_TYPE_INTERFACE,
    USB_REQ_GET_INTERFACE,
    0x00,0x00,
    0xff,0xff,
    0x01,0x00,
    0xf3,&usbGetInterface,

    // get device status
    USB_REQ_TYPE_INPUT | USB_REQ_TYPE_STANDARD | USB_REQ_TYPE_DEVICE,
    USB_REQ_GET_STATUS,
    0x00,0x00,
    0x00,0x00,
    0x02,0x00,
    0xff,&usbGetDeviceStatus, 
    // get interface status
    USB_REQ_TYPE_INPUT | USB_REQ_TYPE_STANDARD | USB_REQ_TYPE_INTERFACE,
    USB_REQ_GET_STATUS,
    0x00,0x00,
    0xff,0x00,
    0x02,0x00,
    0xf7,&usbGetInterfaceStatus,
    // 	get endpoint status
    USB_REQ_TYPE_INPUT | USB_REQ_TYPE_STANDARD | USB_REQ_TYPE_ENDPOINT,
    USB_REQ_GET_STATUS,
    0x00,0x00,
    0xff,0x00,
    0x02,0x00,
    0xf7,&usbGetEndpointStatus,

    // set address
    USB_REQ_TYPE_OUTPUT | USB_REQ_TYPE_STANDARD | USB_REQ_TYPE_DEVICE,
    USB_REQ_SET_ADDRESS,
    0xff,0x00,
    0x00,0x00,
    0x00,0x00,
    0xdf,&usbSetAddress,

    // set configuration
    USB_REQ_TYPE_OUTPUT | USB_REQ_TYPE_STANDARD | USB_REQ_TYPE_DEVICE,
    USB_REQ_SET_CONFIGURATION,
    0xff,0x00,
    0x00,0x00,
    0x00,0x00,
    0xdf,&usbSetConfiguration,

    // set device feature
    USB_REQ_TYPE_OUTPUT | USB_REQ_TYPE_STANDARD | USB_REQ_TYPE_DEVICE,
    USB_REQ_SET_FEATURE,
    0xff,0x00,                      // feature selector
    0x00,0x00,
    0x00,0x00,
    0xdf,&usbSetDeviceFeature,

    // set endpoint feature
    USB_REQ_TYPE_OUTPUT | USB_REQ_TYPE_STANDARD | USB_REQ_TYPE_ENDPOINT,
    USB_REQ_SET_FEATURE,
    0xff,0x00,                      // feature selector
    0xff,0x00,                      // endpoint number <= 127
    0x00,0x00,
    0xd7,&usbSetEndpointFeature,

    // set interface
    USB_REQ_TYPE_OUTPUT | USB_REQ_TYPE_STANDARD | USB_REQ_TYPE_INTERFACE,
    USB_REQ_SET_INTERFACE,
    0xff,0x00,                      // feature selector
    0xff,0x00,                      // interface number
    0x00,0x00,
    0xd7,&usbSetInterface,

    // end of usb descriptor -- this one will be matched to any USB request
    // since bCompareMask is 0x00.
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, 
    0x00,&usbInvalidRequest     // end of list
};

/*-----------------------------------------------------------------------------+
| END OF Descriptor.c FILE                                                     |
|-----------------------------------------------------------------------------*/
