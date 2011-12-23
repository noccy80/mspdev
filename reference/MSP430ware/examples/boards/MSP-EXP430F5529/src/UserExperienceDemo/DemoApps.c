/*******************************************************************************
 *
 *  DemoApps.c - Allows the user to select different USB applications.
 *
 *  Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
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
 * @file       DemoApps.c
 * @addtogroup DemoApps
 * @{
 ******************************************************************************/
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "msp430.h"
#include "HAL_PMM.h"
#include "HAL_UCS.h"
#include "HAL_Buttons.h"
#include "HAL_Dogs102x6.h"
#include "HAL_Board.h"
#include "HAL_Menu.h"
#include "EchoUsb.h"
#include "MassStorage.h"
#include "Mouse.h"
#include "DemoApps.h"
#include "descriptors.h"
#include "usb.h"                            // USB-specific functions
#include "UsbCdc.h"
#include "Demo_Cube.h"
#include "CTS_Layer.h"


static const char *const usbMenuText[] = {
    "====Demo Apps====",
    "1. Terminal Echo ",
    "2. USB Mouse ",
    "3. USB microSD ",
    "4. Touch Graph",
    "5. Touch Slide",
    "6. Demo Cube "
};


// Forward Declared Function
char *itoa(int, char *, int);

/***************************************************************************//**
 * @brief  Allows user to select USB apps
 * @param  none
 * @return none
 ******************************************************************************/

void CapDemo(void)
{
    uint8_t quit = 0, spacing = 0, height = 0, height1 = 0, i;
    uint16_t deltaCount[5];

    Dogs102x6_clearScreen();

    buttonsPressed = 0;

    TI_CAPT_Init_Baseline(&slider);
    buttonDebounce = 0;

    Dogs102x6_stringDraw(0, 0, "== Touch  Demo ==", DOGS102x6_DRAW_NORMAL);

    //menu active until selection is made
    while (!quit)
    {
        TI_CAPT_Custom(&slider, deltaCount);

        // 5 = No. of sensors
        for (i = 0; i < 5; i++)
        {
            spacing = 20 * i + 10;

            if (deltaCount[i] < 4000)
                height = 63 - deltaCount[i] / 60;
            else
                height = 10;

            // Limit the height of the columns
            if (height < 10)
                height = 10;

            // three pixels wide
            Dogs102x6_verticalLineDraw(63, height, spacing - 1, DOGS102x6_DRAW_NORMAL);
            Dogs102x6_verticalLineDraw(63, height, spacing, DOGS102x6_DRAW_NORMAL);
            Dogs102x6_verticalLineDraw(63, height, spacing + 1, DOGS102x6_DRAW_NORMAL);

            __delay_cycles(1000);

            // erasing old lines
            Dogs102x6_verticalLineDraw(height, 8, spacing, DOGS102x6_DRAW_INVERT);
            Dogs102x6_verticalLineDraw(height, 8, spacing - 1, DOGS102x6_DRAW_INVERT);
            Dogs102x6_verticalLineDraw(height, 8, spacing + 1, DOGS102x6_DRAW_INVERT);

            if (i < 4)
            {
                //for the "in between" heights
                if (deltaCount[i + 1] < 2400)
                    height1 = 63 - deltaCount[i + 1] / 40;
                else
                    height1 = 10;

                // Limit the height of the columns
                if (height + height1 < 10)
                    height1 = 10;

                Dogs102x6_verticalLineDraw(63, (height + height1) / 2, (spacing + 10),
                                           DOGS102x6_DRAW_NORMAL);
                Dogs102x6_verticalLineDraw(63, (height + height1) / 2, (spacing + 11),
                                           DOGS102x6_DRAW_NORMAL);
                Dogs102x6_verticalLineDraw(63, (height + height1) / 2, (spacing + 9),
                                           DOGS102x6_DRAW_NORMAL);

                __delay_cycles(1000);

                Dogs102x6_verticalLineDraw((height + height1) / 2, 8, (spacing + 11),
                                           DOGS102x6_DRAW_INVERT);
                Dogs102x6_verticalLineDraw((height + height1) / 2, 8, (spacing + 10),
                                           DOGS102x6_DRAW_INVERT);
                Dogs102x6_verticalLineDraw((height + height1) / 2, 8, (spacing + 9),
                                           DOGS102x6_DRAW_INVERT);
            }
        }

        if ((buttonsPressed & BUTTON_S2))
            quit = 1;
    }

    Board_ledOff(LED_ALL);
    Dogs102x6_clearScreen();
    buttonDebounce = 1;
    buttonsPressed = 0;
}

void CapLED(void)
{
    uint8_t sliderPosition = 0;

    Board_ledOff(LED_ALL);
    Dogs102x6_clearScreen();
    buttonsPressed = 0;

    Dogs102x6_stringDraw(1, 0, " Slide Finger on ", DOGS102x6_DRAW_NORMAL);
    Dogs102x6_stringDraw(2, 0, "   Touch Pads    ", DOGS102x6_DRAW_NORMAL);

    TI_CAPT_Init_Baseline(&slider);

    while (!(buttonsPressed & BUTTON_S2))
    {
        sliderPosition = TI_CAPT_Slider(&slider);

        sliderPosition = (sliderPosition + 10) / 20;

        switch (sliderPosition)
        {
            case 0: Board_ledOff(LED4 + LED5 + LED6 + LED7 + LED8);
                break;
            case 1: Board_ledOn(LED4);
                Board_ledOff(LED5 + LED6 + LED7 + LED8);
                break;
            case 2: Board_ledOn(LED4 + LED5);
                Board_ledOff(LED6 + LED7 + LED8);
                break;
            case 3: Board_ledOn(LED4 + LED5 + LED6);
                Board_ledOff(LED7 + LED8);
                break;
            case 4: Board_ledOn(LED4 + LED5 + LED6 + LED7);
                Board_ledOff(LED8);
                break;
            case 5: Board_ledOn(LED4 + LED5 + LED6 + LED7 + LED8);
                break;
            case (255 / 17):
                break;
        }
    }

    Board_ledOff(LED_ALL);
    Dogs102x6_clearScreen();
    buttonsPressed = 0;
}

void DemoApp(void)
{
    uint8_t selection = 0;

    buttonsPressed = 0;
    Dogs102x6_clearScreen();

    while (!(buttonsPressed & BUTTON_S2))
    {
        selection = Menu_active((char **)usbMenuText, 6);
        if (buttonsPressed & BUTTON_S2) break;
        switch (selection)
        {
            case 1: EchoUSB();  break;
            case 2: Mouse();  break;
            case 3: MassStorage(); break;
            case 4: CapDemo(); break;
            case 5: CapLED(); break;
            case 6: Demo_Cube(); break;
            default:  break;
        }
    }
    buttonsPressed = 0;
    Dogs102x6_clearScreen();
}

/***************************************************************************//**
 * @brief  Handles UNMI interrupts
 * @param  none
 * @return none
 ******************************************************************************/
#pragma vector = UNMI_VECTOR
__interrupt void UNMI_ISR(void)
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
            UCSCTL7 &= ~(DCOFFG + XT1LFOFFG + XT2OFFG); // Clear OSC flaut Flags fault flags
            SFRIFG1 &= ~OFIFG;                          // Clear OFIFG fault flag
            break;
        case SYSUNIV_ACCVIFG:
            __no_operation();
            break;
        case SYSUNIV_BUSIFG:
            // If bus error occurred - the cleaning of flag and re-initializing of USB is required.
            SYSBERRIV = 0;                              // clear bus error flag
            USB_disable();                              // Disable
    }
}

/***************************************************************************//**
 * @}
 ******************************************************************************/




