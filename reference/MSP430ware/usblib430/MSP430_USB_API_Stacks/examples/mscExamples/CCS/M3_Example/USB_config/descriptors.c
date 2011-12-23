// (c)2010 by Texas Instruments Incorporated, All Rights Reserved.
/*-----------------------------------------------------------------------------+
|                                                                              |
|                              Texas Instruments                               |
|                                                                              |
|    This is an automatically generated script by MSP430 USB Descriptor Tool   |
|                                                                              |
|    Descriptor Tool Version: 3.0.10                                            |
|    Date: 2011/02/24 16:34:33                                                 |
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
#include <USB_API/USB_MSC_API/UsbMscReq.h>

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

    /******************************************************* start of MSC*************************************/
    {
    /*start MSC[0] Here */
        {
            //-------- Descriptor for MSC class device -------------------------------------
            // INTERFACE DESCRIPTOR (9 bytes) 
            SIZEOF_INTERFACE_DESCRIPTOR,                // bLength 
            DESC_TYPE_INTERFACE,                        // bDescriptorType: 4 
            MSC0_DATA_INTERFACE,                        // bInterfaceNumber
            0x00,                                       // bAlternateSetting
            0x02,                                       // bNumEndpoints
            0x08,                                       // bInterfaceClass: 3 = MSC Device
            0x06,                                       // bInterfaceSubClass:
            0x50,                                       // bInterfaceProtocol:
            INTF_STRING_INDEX + 0,                      // iInterface:1

            SIZEOF_ENDPOINT_DESCRIPTOR,                 // bLength
            DESC_TYPE_ENDPOINT,                         // bDescriptorType
            MSC0_INEP_ADDR,                             // bEndpointAddress; bit7=1 for IN, bits 3-0=1 for ep1
            EP_DESC_ATTR_TYPE_BULK,                     // bmAttributes, interrupt transfers
            0x40, 0x00,                                 // wMaxPacketSize, 64 bytes
            0X01,                                       // bInterval, ms

            SIZEOF_ENDPOINT_DESCRIPTOR,                 // bLength
            DESC_TYPE_ENDPOINT,                         // bDescriptorType
            MSC0_OUTEP_ADDR,                            // bEndpointAddress; bit7=1 for IN, bits 3-0=1 for ep1
            EP_DESC_ATTR_TYPE_BULK,                     // bmAttributes, interrupt transfers
            0x40, 0x00,                                 // wMaxPacketSize, 64 bytes
            0x01,                                       // bInterval, ms
            /* end of MSC[0]*/
        }
    }
    /******************************************************* end of MSC**************************************/
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
	38,		// Length of this string descriptor
	3,		// bDescriptorType
	'M',0x00,'S',0x00,'P',0x00,'4',0x00,'3',0x00,'0',0x00,
	'-',0x00,'U',0x00,'S',0x00,'B',0x00,' ',0x00,'E',0x00,
	'x',0x00,'a',0x00,'m',0x00,'p',0x00,'l',0x00,'e',0x00,

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
	28,		// Length of this string descriptor
	3,		// bDescriptorType
	'M',0x00,'S',0x00,'C',0x00,' ',0x00,'I',0x00,'n',0x00,
	't',0x00,'e',0x00,'r',0x00,'f',0x00,'a',0x00,'c',0x00,
	'e',0x00
};

/**** Populating the endpoint information handle here ****/

const struct tUsbHandle stUsbHandle[]=
{
    {
        MSC0_INEP_ADDR,
        MSC0_OUTEP_ADDR,
        0, 
        MSC_CLASS,
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

    //---- MSC Class Requests -----//
    // Reset MSC
    USB_REQ_TYPE_OUTPUT | USB_REQ_TYPE_CLASS | USB_REQ_TYPE_INTERFACE,
    USB_MSC_RESET_BULK,
    0x00,0x00,                    // always zero
    MSC0_DATA_INTERFACE,0x00,     // MSC interface is 0
    0x00,0x00,                    // Size of Structure (data length)
    0xff,&USBMSC_reset,

    // Get Max Lun
    USB_REQ_TYPE_INPUT | USB_REQ_TYPE_CLASS | USB_REQ_TYPE_INTERFACE,
    USB_MSC_GET_MAX_LUN,
    0x00,0x00,                    // always zero
    MSC0_DATA_INTERFACE,0x00,     // MSC interface is 0
    0x01,0x00,                    // Size of Structure (data length)
    0xff,&Get_MaxLUN,

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
