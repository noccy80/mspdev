;******************************************************************************
;   MSP430x42x0 Demo - LCD_A Put "0123456" on SBLCDA4 LCD
;
;  Description; Put "0123456" on SBLCDA4 LCD.
;  ACLK = LFXT1 = 32768, MCLK = SMCLK = DCO = 32xACLK = 1.048576MHz
;  //*An external watch crystal is required on XIN/XOUT for ACLK*//	
;               MSP430F4270
;            -----------------
;        /|\|              XIN|-
;         | |                 | 32kHz
;         --|RST          XOUT|-
;           |                 |
;           |                 |    SBLCDA4
;           |             S0  |     -----------------
;           |              -  |--> | + 7 6 5 4 3 2 1 |
;           |             S13 |     -----------------
;           |             COM0|-----||||
;           |             COM1|------|||
;           |             COM2|-------||
;           |             COM3|--------|
;           |                 |
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x42x0.h"
;------------------------------------------------------------------------------
			.text							; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #300h,SP                ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
            bis.b   #XCAP14PF,&FLL_CTL0     ; Set load capacitance for xtal
            mov.b   #LCDON + LCD4MUX + LCDFREQ_128, &LCDACTL ; 4mux LCD, ACLK/128
            mov.b   #0x0F, &LCDAPCTL0       ; Segments 0-13
            mov.b   #0x1C, &P5SEL           ; set COM pins for LCD
ClearLCD    mov.w   #20,R15                 ; 15 LCD memory bytes to clear
Clear1      mov.b   #0,LCDM1(R15)           ; Write zeros in LCD RAM locations
                                            ; to clear display
            dec     R15                     ; All LCD mem clear?
            jc      Clear1                  ; More LCD mem to clear go, use JC
                                            ; to get memory location 0
setLCD      clr.w   R15                     ; 0 is first digit to display
writeLCD    mov.b   LCD_Tab(R15),LCDM1(R15) ; Write correct digit in LCD RAM locations
            inc     R15                     ; All LCD mem clear?
            cmp     #0x07, R15
            jl      writeLCD
            bis     #LPM3,SR                ; Set SR bits to wait in LPM3

d           .equ     0x80
c           .equ     0x40
b           .equ     0x20
a           .equ     0x10
h           .equ     0x08
e           .equ     0x04
g           .equ     0x02
f           .equ     0x01

LCD_Tab     .byte      a+b+c+d+e+f             ; Displays '0'
            .byte      b+c                     ; Displays '1'
            .byte      a+b+d+e+g               ; Displays '2'
            .byte      a+b+c+d+g               ; Displays '3'
            .byte      b+c+f+g                 ; Displays '4'
            .byte      a+c+d+f+g               ; Displays '5'
            .byte      a+c+d+e+f+g             ; Displays '6'
            .byte      a+b+c                   ; Displays '7'
            .byte      a+b+c+d+e+f+g           ; Displays '8'
            .byte      a+b+c+d+f+g             ; Displays '9'

;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect    ".reset"                  ; RESET Vector
            .short   RESET                   ;
            .end
