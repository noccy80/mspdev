;******************************************************************************
;   MSP430xG461x Demo - Real Time Clock, Toggle P5.1 Inside ISR, 32kHz ACLK
;                       and send Time via UART
;
;   Description: This program toggles P5.1 by xor'ing P5.1 inside of
;   a Real Time Clock ISR. The Real Time Clock ISR is called once a minute using
;   the Alarm function provided by the RTC. ACLK used to clock basic timer.
;   ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
;   //* An external watch crystal between XIN & XOUT is required for ACLK *//
;
;                MSP430FG4619
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |             P5.1|-->LED
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430xG46x.h"
;-------------------------------------------------------------------------------
			.text	;Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #900,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupFLL    bis.b   #XCAP14PF,&FLL_CTL0     ; Configure load caps
SetupRTC    mov.b   #RTCBCD+RTCHOLD+RTCMODE_3+RTCTEV_0+RTCIE,&RTCCTL
                                            ; RTC enable, BCD mode,
                                            ; alarm every Minute,
                                            ; enable RTC interrupt
            ; Init time
            mov.b   #000h,&RTCSEC           ; Set Seconds
            mov.b   #000h,&RTCMIN           ; Set Minutes
            mov.b   #008h,&RTCHOUR          ; Set Hours

            ; Init date
            mov.b   #002h,&RTCDOW           ; Set DOW
            mov.b   #023h,&RTCDAY           ; Set Day
            mov.b   #008h,&RTCMON           ; Set Month
            mov.w   #02005h,&RTCYEAR        ; Set Year


            bic.b   #RTCHOLD,&RTCCTL        ; Enable RTC
SetupP5     bis.b   #002h,&P5DIR            ; P5.1 output

Mainloop    bis.w   #LPM3+GIE,SR            ; Enter LPM3, enable interrupts
            nop                             ; Required only for debugger
                                            ;
;-------------------------------------------------------------------------------
BT_ISR;     Toggle P5.1
;-------------------------------------------------------------------------------
            xor.b   #002h,&P5OUT            ; Toggle P5.1
            reti                            ;
                                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".int16"       ; Basic Timer Vector
            .short   BT_ISR                  ;
            .sect	".reset"            	; POR, ext. Reset, Watchdog
            .short   RESET
            .end
