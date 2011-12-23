;******************************************************************************
;   MSP-FET430P410 Demo - LCD, Display Numbers on a 4-Mux LCD
;
;   Description: This program displays digits stored in regiser
;   R14 on a 4 mux LCD, then waits in low power mode 3. To use the program,
;   enter a 4 digit BCD number (digits 0-9) in R14 and press enter.  Reset
;   and run the program.  The value in R14 will be displayed on the LCD. If
;   the user does not have the LCD connected, the functioning of the software
;   can still be followed by single stepping and watching the register values
;   and the LCD memory values in the LCD memory
;   locations.
;
;   NOTE: The code is written such that single digits can be passed to the
;         display routine.  The routine to shift bytes in the mainloop
;         could be moved to the display routine if passing of multiple digits
;         is preferred
;
;   ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
;   ;* An external watch crystal between XIN & XOUT is required for ACLK *//	
;
;                                 Connections MSP430 -> LCD
;                                 -------------------------
;
;                                              T.I. MSP-EVK430S320
;                             MSP430F449       6.5 digit 4 mux LCD
;                                                    #T218010
;                       /|\ ---------------       --------------
;                        | |          COM3 |-----|2    COM4     |
;                        --|RST       COM2 |-----|1    COM3     |
;                          |          COM1 |-----|3    COM2     |
;                          |          COM0 |-----|4,20 COM1     |
;                         -|XIN       SEG0 |-----|19            |
;                     32kHz|          SEG1 |-----|18            |
;                         -|XOUT      SEG2 |-----|17            |
;                          |          SEG3 |-----|16            |
;                          |          SEG4 |-----|15            |
;                          |          SEG5 |-----|14            |
;                          |          SEG6 |-----|13            |
;                          |          SEG7 |-----|12            |
;                        +-|R33       SEG8 |-----|11            |
;                       1M |          SEG9 |-----|10            |
;                        +-|R23       SEG10|-----|9             |
;                       1M |          SEG11|-----|8             |
;                        +-|R13       SEG12|-----|7             |
;                       1M |          SEG13|-----|6             |
;                        +-|R03       SEG14|-----|5 (bits C,E,H |
;                        | |               |     |   of digit 7)|
;                       Vss ---------------       --------------
;
;   G. Morton / S. Karthikeyan
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430x41x.h"

;-----------CPU registers used-------------------------------------------------
;;;;;;;     R13, R14, R15                   ; Used as temporary registers, can
                                            ; be reused
;-----------RAM words used for variables---------------------------------------
CDTEMP      .equ    0200h                   ; Temporary storage in LCD routine

;------------------------------------------------------------------------------
            .text                  			; Program reset
;------------------------------------------------------------------------------
RESET       mov.w   #300h,SP                ; Initialize stack pointer
            call    #Setup                  ; Setup

Mainloop    mov.b   R14,R13                 ; Copy R14 to R13 (save R14)
            call    #ToLCD                  ; Call to display 1st digit
            mov.b   R14,R13                 ; Copy R14 to R13 (save R14)
            rra.b   R13                     ; Right shift R13 4 times to
            rra.b   R13                     ; move 2nd nibble to lower 4 bits
            rra.b   R13                     ;
            rra.b   R13                     ;
            call    #ToLCD                  ; Call to display 2nd digit
            swpb    R14                     ; Swap bytes in R14
            mov.b   R14,R13                 ; Copy R14 to R13 (save R14)
            call    #ToLCD                  ; Call to display 3rd digit
            mov.b   R14,R13                 ; Copy R14 to R13
            rra.b   R13                     ; Right shift R13 4 times to
            rra.b   R13                     ; move 2nd nibble to lower 4 bits
            rra.b   R13                     ;
            rra.b   R13                     ;
            call    #ToLCD                  ; Call to display 4th digit
            bis     #LPM3,SR                ; .set SR bits to wait in LPM3

;------------------------------------------------------------------------------
;           Display 1 digit on 4 mux LCD. CPU Registers R13 & R15 used
;           temporarily.
;------------------------------------------------------------------------------
ToLCD       and.w   #000Fh,R13              ; Blank upper 12 bits
            mov.b   LCD_Tab(R13),0(R15)     ; Byte from table LCD memory
            inc.w   R15                     ; Increment pointer by 1 to next
                                            ; LCD memory byte
EndLCD      ret                             ; Return from call

;------------------------------------------------------------------------------
Setup       ; Configure modules and control registers
;------------------------------------------------------------------------------
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop Watchdog Timer
SetupFLL2   bis.b   #XCAP18PF,&FLL_CTL0     ; .set load capacitance for xtal
            mov.w   #10000,R15              ;
Xtal_Wait   dec.w   R15                     ; Delay for 32 kHz crystal to
            jnz     Xtal_Wait		    ; stabilize
SetupLCD    mov.b   #LCDP1+LCDP0+LCD4MUX+LCDON,&LCDCTL
                                            ; 4-Mux LCD, segments S0-S23
SetupIO     bis.b   #0FCh,&P5SEL            ; .set Rxx and COM pins for LCD
SetupBT     mov.b   #BTFRFQ1,&BTCTL         ; .set freqLCD = ACLK/128
SetupPorts  mov.b   #0FFh,&P1DIR            ; .set port to outputs
SetupPx     mov.b   #0FFh,&P2DIR            ; .set port to outputs
            mov.b   #0FFh,&P3DIR            ; .set port to outputs
            mov.b   #0FFh,&P4DIR            ; .set port to outputs
            mov.b   #0FFh,&P5DIR            ; .set port to outputs
            mov.b   #0FFh,&P6DIR            ; .set port to outputs

ClearLCD    mov.w   #15,R15                 ; 15 LCD memory bytes to clear
Clear1      mov.b   #0,LCDM1(R15)           ; Write zeros in LCD RAM locations
                                            ; to clear display
            dec.w   R15                     ; All LCD mem clear?
            jc      Clear1                  ; More LCD mem to clear go, use JC
                                            ; to get memory location 0
            mov.b   #LCDM1,R15;             ; R15 points to first LCD location
            ret

;------------------------------------------------------------------------------
;           Define characters for T218010 = 6.5 digit 4 mux LCD
;------------------------------------------------------------------------------
a           .equ    01h	
b           .equ    02h
c           .equ    10h
d           .equ    04h
e           .equ    80h
f           .equ    20h
g           .equ    08h
h           .equ    40h

LCD_Tab     .byte   a+b+c+d+e+f             ; Displays '0'
            .byte   b+c                     ; Displays '1'
            .byte   a+b+d+e+g               ; Displays '2'
            .byte   a+b+c+d+g               ; Displays '3'
            .byte   b+c+f+g                 ; Displays '4'
            .byte   a+c+d+f+g               ; Displays '5'
            .byte   a+c+d+e+f+g             ; Displays '6'
            .byte   a+b+c                   ; Displays '7'
            .byte   a+b+c+d+e+f+g           ; Displays '8'
            .byte   a+b+c+d+f+g             ; Displays '9'

;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect     ".reset"                  ; RESET Vector
            .short  RESET
            .end



