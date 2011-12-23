/*******************************************************************************
 *
 *  EchoUsb.c - Echoes characters typed on the PC back to the terminal and
 *              displays them on the LCD.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************/

/***************************************************************************//**
 * @file       EchoUsb.c
 * @addtogroup EchoUsb
 * @{
 ******************************************************************************/
#include <stdint.h>
#include <string.h>
#include "msp430.h"
#include "HAL_UCS.h"
#include "HAL_Board.h"
#include "HAL_Buttons.h"
#include "HAL_Dogs102x6.h"
#include "HAL_Wheel.h"
#include "EchoUsb.h"
#include "descriptors.h"
#include "usb.h"                            // USB-specific functions
#include "usbConstructs.h"
#include "MassStorageCommon.h"

#define BUFFER_SIZE         130
uint8_t dataBuffer[BUFFER_SIZE];            // User buffer to hold the data

/***************************************************************************//**
 * @brief  Echoes everything the user types in the terminal back to the
 *         terminal, and prints to the LCD.
 * @param  none
 * @return none
 ******************************************************************************/

void EchoUSB(void)
{
    WORD bytesReceived;
    uint8_t row = 2;
    uint8_t col = 0;
    uint8_t i = 0;

    buttonsPressed = 0;

    Dogs102x6_clearScreen();
    Dogs102x6_stringDraw(0, 0, "Type on PC.      ", DOGS102x6_DRAW_INVERT);
    Dogs102x6_stringDraw(1, 0, "Press S2 to quit.", DOGS102x6_DRAW_INVERT);

    // Init USB
    USB_init();

    // Enable various USB event handling routines
    USB_setEnabledEvents(kUSB_allUsbEvents);

    msc_Init();

    // If USB is already connected when the program starts up, then there won't
    // be a USB_handleVbusOnEvent(). So we need to check for it, and manually
    // connect if the host is already present.
    if (USB_connectionInfo() & kUSB_vbusPresent)
    {
        if (USB_enable() == kUSB_succeed)
        {
            USB_reset();
            USB_connect();
        }
    }

    while (!(buttonsPressed & BUTTON_S2))
    {
        // Check the USB state and loop accordingly
        switch (USB_connectionState())
        {
            case  ST_USB_DISCONNECTED:
                // Enter LPM3 until USB is connected
                __bis_SR_register(LPM3_bits + GIE);
                __no_operation();
                break;

            case  ST_USB_CONNECTED_NO_ENUM:
                __no_operation();
                break;

            case  ST_ENUM_ACTIVE:
                // Enter LPM0 until awakened by an event handler
                __bis_SR_register(LPM0_bits + GIE);

                msc_Loop();

                bytesReceived = cdcReceiveDataInBuffer(dataBuffer, BUFFER_SIZE,
                                                       CDC0_INTFNUM);

                if (bytesReceived){
                    // Echo back to the host
                    cdcSendDataInBackground(dataBuffer, bytesReceived,
                                            CDC0_INTFNUM, 0);

                    // Display on the lcd as well
                    for (i = 0; i < bytesReceived; i++)
                    {
                        Dogs102x6_charDraw(row,
                                           col,
                                           dataBuffer[i],
                                           DOGS102x6_DRAW_NORMAL);
                        col += 6;
                        if (col > 101)
                        {
                            if (row < 7)
                            {
                                row++;
                                col = 0;
                            }
                            else
                            {
                                row = 2;
                                col = 0;
                            }
                        }
                    }
                }
                break;

            case ST_NOENUM_SUSPENDED:
                __bis_SR_register(LPM3_bits + GIE);
                __no_operation();
                break;

            case  ST_ENUM_SUSPENDED:
                Board_ledOff(LED1);
                // Enter LPM3 until a resume or VBUS-off event
                __bis_SR_register(LPM3_bits + GIE);
                __no_operation();
                break;

            case ST_ENUM_IN_PROGRESS:
                __no_operation();
                break;

            case  ST_ERROR:
                __no_operation();
                break;

            default:;
        }
    }

    USB_disable();
    SFRIE1 &= ~OFIE;
    Init_FLL_Settle(25000, 762);          // Return to normal clock settings
    SFRIE1 |= OFIE;
    Dogs102x6_clearScreen();
}

/***************************************************************************//**
 * @}
 ******************************************************************************/
