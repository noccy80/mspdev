;******************************************************************************
;   MSP-FET430P430 Demo - LCD, Display "0123456" on SBLCDA4 LCD
;
;   Description: Displays "0123456" on SBLCDA4 LCD as used on 430 Day Watch
;   demo board.
;   ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
;   //* An external watch crystal between XIN & XOUT is required for ACLK *//	
;
;               MSP430FG439
;            -----------------
;        /|\|              XIN|-
;         | |                 | 32kHz
;         --|RST          XOUT|-
;           |                 |      SBLCDA4
;           |                 |      (As used on 430 Day Watch Demo board)
;         +-|R33          S0  |     -----------------
;        1m |              -  |--> | + 7 6 5 4 3 2 1 |
;         +-|R23          S21 |     -----------------
;        1m |             COM0|-----||||
;         +-|R13          COM1|------|||
;        1m |             COM2|-------||
;         +-|R03          COM3|--------|
;         | |                 |
;        Vss
;
;   L. Westlund / M. Mitchell
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430xG43x.h"
;------------------------------------------------------------------------------
            .text                  ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #0A00h,SP               ; Initialize stack pointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop Watchdog Timer
SetupFLL    bis.b   #XCAP14PF,&FLL_CTL0     ; Configure load caps

SetupLCD    mov.b   #LCDON+LCDSG0_3+LCD4MUX,&LCDCTL; 4mux LCD, segs0-23=outputs
SetupBT     mov.b   #BT_fLCD_DIV128,&BTCTL  ; Set LCD frame freq = ACLK/128
SetupIO     mov.b   #0xFC,&P5SEL            ; Common and Rxx all selected
                                            ; For P5.0 P5.1 P4.6 P4.7 setting
                                            ; SEL bits selects Analog for FG
Mainloop    clr.w   R5                      ; Clear pointer
Disp        mov.b   LCD_Tab(R5),LCDMEM(R5)  ;
            inc.w   R5                      ;
            cmp.w   #07,R5                  ;
            jne     Disp                    ;
            jmp     Mainloop                ; Again

                                            ; As used on 430 Day Watch board
LCD_Tab     .byte   0F5h                    ; displays "0"
            .byte   060h                    ; displays "1"
            .byte   0B6h                    ; displays "2"
            .byte   0F2h                    ; displays "3"
            .byte   063h                    ; displays "4"
            .byte   0D3h                    ; displays "5"
            .byte   0D7h                    ; displays "6"
            .byte   070h                    ; displays "7"
            .byte   0F7h                    ; displays "8"
            .byte   0F3h                    ; displays "9"
;-----------------------------------------------------------------------------
;           Interrupt Vectors
;-----------------------------------------------------------------------------
            .sect   ".reset"                ; RESET Vector
            .short  RESET                   ;
            .end
