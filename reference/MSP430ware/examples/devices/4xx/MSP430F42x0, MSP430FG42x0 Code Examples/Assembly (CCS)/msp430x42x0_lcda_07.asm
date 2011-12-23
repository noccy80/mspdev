;******************************************************************************
;   MSP430x42x0 Demo - LCD_A run a 0-9 counter on SBLCDA4
;
;  Description; Count 0-9 on a SBLCDA4
;  ACLK = LFXT1 = 32768, MCLK = SMCLK = DCO = 32xACLK = 1.048576MHz
;  Segments attached in accordance with Static LCD diagram in 4xx User's Guide
;  //*An external watch crystal is required on XIN/XOUT for ACLK*//	
;  //* WARNING: Do NOT enable Charge Pump with Static LCD *//
;  //* See Errata for more details: LCDA1 *//
;
;             MSP430F4270
;            -----------------
;        /|\|              XIN|-
;         | |                 | 32kHz
;         --|RST          XOUT|-
;           |                 |
;           |                 |    SBLCDA4
;           |             S0  |     -----------------
;           |              -  |--> | + 7 6 5 4 3 2 1 |
;           |             S6 |     -----------------
;           |             COM0|-----||||
;           |             COM1|------|||
;           |             COM2|-------||
;           |             COM3|--------|
;           |                 |
;
;	//*S0-S6 are connected to Pin 1-7 of SBLCDA4
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x42x0.h"
;------------------------------------------------------------------------------
            .text                 ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #300h,SP                ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
            bis.b   #XCAP14PF,&FLL_CTL0     ; Set load capacitance for xtal
            mov.b   #LCDON + LCD4MUX + LCDFREQ_128, &LCDACTL ; 4mux LCD ACLK/128
            mov.b   #0x03, &LCDAPCTL0       ; s0-s6 used
             mov.b   #0x1C, &P5SEL           ; set COM pins for LCD
ClearLCD    mov.w   #20,R15                 ; 15 LCD memory bytes to clear
Clear1      mov.b   #0,LCDM1(R15)           ; Write zeros in LCD RAM locations
                                            ; to clear display
            dec     R15                     ; All LCD mem clear?
            jc      Clear1                  ; More LCD mem to clear, use JC
                                            ; to get memory location 0
            mov.b   #0,    R15              ; R15 is a scratch loop value  --< check for clear already
            mov.b   #0,    R14              ; R14 is value to display
Loop        mov.b   R14,   R13              ; copy value to R13 to become index

Char_loop   mov.b   LCD_Tab(R13), LCDMEM(R15)
            inc.b   R13
            mov.w   #0xffff, R15
Delay_loop  dec.w   R15
            tst.w   R15
            jnz     Delay_loop
            cmp     #9,    R14
            jne     Add_One
            clr.b   R14
            jmp     Loop
Add_One     inc.b   R14
            jmp     Loop


d           .equ     0x80
c           .equ     0x40
b           .equ     0x20
a           .equ     0x10
h           .equ     0x08
e           .equ     0x04
g           .equ     0x02
f           .equ     0x01

LCD_Tab     .byte      a+b+c+d+e+g             ; Displays '0'
            .byte      a+c                     ; Displays '1'
            .byte      a+b+d+e+f             ; Displays '2'
            .byte      a+b+c+d+f               ; Displays '3'
            .byte      a+c+f+g                 ; Displays '4'
            .byte      b+c+d+f+g               ; Displays '5'
            .byte      b+c+d+e+g+f             ; Displays '6'
            .byte      a+b+c                   ; Displays '7'
            .byte      a+b+c+d+e+f+g           ; Displays '8'
            .byte      a+b+c+d+f+g             ; Displays '9'
            
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect    ".reset"                  ; RESET Vector
            .short   RESET                   ;
            .end
          