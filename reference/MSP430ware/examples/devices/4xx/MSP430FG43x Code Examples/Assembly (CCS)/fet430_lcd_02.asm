;******************************************************************************
;   MSP-FET430P430 Demo - LCD, Display "430" on Varitronix VI-322 LCD
;
;   Description: Displays "430" on Varitronix VI-322 LCD as used on Softbaugh D437
;   ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
;   //* An external watch crystal between XIN & XOUT is required for ACLK *//	
;
;               MSP430FG439
;            -----------------
;        /|\|              XIN|-
;         | |                 | 32kHz
;         --|RST          XOUT|-
;           |                 |      Varitronix VI-322
;           |                 |     (as used on Softbaugh D437 board)
;           |             S0  |     ---------
;           |              -  |--> | + 3 2 1 |
;           |             S31 |     ---------
;           |             COM0|-----|
;           |                 |
;           |                 |
;           |                 |
;           |                 |
;
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
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT

SetupFLL2   bis.b   #XCAP18PF,&FLL_CTL0     ; Set load capacitance for xtal

SetupLCD    mov.b   #LCDON+LCDSTATIC+LCDOGOFF,&LCDCTL ;static LCD,
                                                      ;segments = 0 - 31
SetupBT     mov.b   #BTFRFQ1+BTFRFQ0,&BTCTL ; LCD freq

            mov.b   #0xFC, &P5SEL           ; Common and Rxx all selected
                                            ; For P5.0 P5.1 P4.6 P4.7 setting
                                            ; SEL bits selects Analog for FG

ClearLCD    mov.w   #18,R15                 ; 18 LCD memory bytes to clear
Clear1      mov.b   #0,LCDM1(R15)           ; write zeros in LCD RAM locations
            dec.w   R15                     ; all LCD mem clear?
            jc      Clear1                  ; more LCD mem to clear, use JC

                                            ; R15  Digits to display
                                            ; R14   LCD Table data for digit
Display     mov.w   #0x430, R15             ; move data to display
            mov.w   R15, R12                ; preserve data
            and.w   #0x0F, R12              ; get 1st digit
            mov.w   LCD_Tab(R12), R14       ; lookup display data in table
            bit.w   #0x01, R12              ; test for odd digit
            jz      EVEN_1                  ; if not, do nothing
            swpb    r14                     ; else, swap bytes to get high
                                            ; byte in table location
EVEN_1      mov.b   R14, &LCDM1             ; shift in data to LCD memory...
            rra.w   R14
            mov.b   R14, &LCDM2
            rra.w   R14
            mov.b   R14, &LCDM3
            rra.w   R14
            mov.b   R14, &LCDM4

            mov.w   R15, R12                ; move data to display
            rra.w   R12                     ; shift to get 2nd digit....
            rra.w   R12
            rra.w   R12
            rra.w   R12
            and.w   #0x0F, R12              ; get 2nd digit
            mov.w   LCD_Tab(R12), R14       ; lookup display data in table
            bit.w   #0x01, R12              ; test for odd digit
            jz      EVEN_2                  ; if not, do nothing
            swpb    r14                     ; else, swap bytes to get high byte
EVEN_2      mov.b   R14, &LCDM5             ; shift data to LCD memory...
            rra.w   R14
            mov.b   R14, &LCDM6
            rra.w   R14
            mov.b   R14, &LCDM7
            rra.w   R14
            mov.b   R14, &LCDM8

            mov.w   R15, R12                ; move data to display
            swpb    R12                     ; 8 RRAs to get 3rd digit
            and.w   #0x0F, R12              ; get 3rd digit
            mov.w   LCD_Tab(R12), R14       ; lookup display data in table
            bit.w   #0x01, R12              ; test for odd digit
            jz      EVEN_3                  ; if not, do nothing
            swpb    r14                     ; else, swap bytes to get high byte
EVEN_3      mov.b   R14, &LCDM11            ; shift data to LCD memory...
            rra.w   R14
            mov.b   R14, &LCDM12
            rra.w   R14
            mov.b   R14, &LCDM13
            rra.w   R14
            mov.b   R14, &LCDM14

LOOP        jmp     LOOP                    ; do nothing so as to display data
;------------------------------------------------------------------------------
;            LCD Type Definition
;------------------------------------------------------------------------------
;Segments definition
a            .equ    001h
b            .equ    010h
c            .equ    002h
d            .equ    020h
e            .equ    004h
f            .equ    040h
g            .equ    008h
h            .equ    080h
             .align 2                       ; align words on .align 2 boundry		
LCD_Tab      .byte   a+b+c+d+e+f            ; Displays "0"
             .byte   b+c                    ; Displays "1"
             .byte   a+b+d+e+g              ; Displays "2"
             .byte   a+b+c+d+g              ; Displays "3"
             .byte   b+c+f+g                ; Displays "4"
             .byte   a+c+d+f+g              ; Displays "5"
             .byte   a+c+d+e+f+g            ; Displays "6"
             .byte   a+b+c                  ; Displays "7"
             .byte   a+b+c+d+e+f+g          ; Displays "8"
             .byte   a+b+c+d+f+g            ; Displays "9"        		
;------------------------------------------------------------------------------

;-----------------------------------------------------------------------------
;           Interrupt Vectors
;-----------------------------------------------------------------------------
            .sect   ".reset"                ; RESET Vector
            .short  RESET                   ;
            .end