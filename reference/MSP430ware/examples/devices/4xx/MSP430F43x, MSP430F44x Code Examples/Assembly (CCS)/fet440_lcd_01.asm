;******************************************************************************
;   MSP-FET430P440 Demo - LCD, Display "6543210" on STK/EVK LCD
;
;   Description: Display "6543210" on MSP-EVK430S320 LCD.
;   ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
;   //* An external watch crystal between XIN & XOUT is required for ACLK *//	
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
;   M. Buccini / A. Dannenberg
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST, "msp430x44x.h"

;------------------------------------------------------------------------------
            .text                  			; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #0A00h,SP               ; Initialize stack pointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupFLL    bis.b   #XCAP14PF,&FLL_CTL0     ; Configure load caps
            mov.w   #10000,R15              ;
Xtal_Wait   dec.w   R15                     ; Delay for 32 kHz crystal to
            jnz     Xtal_Wait		    	; stabilize
SetupLCD    mov.b   #LCDON+LCD4MUX+LCDSG0_4,&LCDCTL
                                            ; LCD on, 4-Mux, select pins S0-S27
SetupBT     mov.b   #BT_fLCD_DIV128,&BTCTL  ; freqLCD = ACLK/128
SetupIO     mov.b   #0FCh,&P5SEL            ; COMx and Rxx selected
                                            ;
Mainloop    clr.w   R5                      ; Clear index
Disp        mov.b   LCD_Tab(R5),LCDMEM(R5)  ; Copy LCD map value to LCD memory
            inc.w   R5                      ; Increment index
            cmp.w   #7,R5                   ; Is index = 7?
            jne     Disp                    ; No, jump to label
            jmp     Mainloop                ; Again
                                            ;
LCD_Tab     .byte   0B7h                    ; Displays '0'
            .byte   012h                    ; Displays '1'
            .byte   08Fh                    ; Displays '2'
            .byte   01Fh                    ; Displays '3'
            .byte   03Ah                    ; Displays '4'
            .byte   03Dh                    ; Displays '5'
            .byte   0BDh                    ; Displays '6'
            .byte   013h                    ; Displays '7'
            .byte   0BFh                    ; Displays '8'
            .byte   03Fh                    ; Displays '9'
                                            ;										
;-----------------------------------------------------------------------------
;           Interrupt Vectors
;-----------------------------------------------------------------------------
            .sect   ".reset"                ; RESET Vector
            .short  RESET                   ;
            .end
