;*******************************************************************************
;   MSP430G2xx1 Demo - Basic Clock, LPM3 Using WDT ISR, VLO ACLK
;
;   Description: This program operates MSP430 normally in LPM3, pulsing P1.0
;   ~ 6 second intervals. WDT ISR used to wake-up system. All I/O configured
;   as low outputs to eliminate floating inputs. Current consumption does
;   increase when LED is powered on P1.0. Demo for measuring LPM3 current.
;   ACLK = VLO/2, MCLK = SMCLK = default DCO
;
;                MSP430G2xx1
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |             P1.0|-->LED
;
;   D. Dang
;   Texas Instruments Inc.
;   October 2010
;   Built with Code Composer Essentials Version: 4.2.0
;*******************************************************************************
 .cdecls C,LIST,  "msp430g2231.h"

;------------------------------------------------------------------------------
            .text                           ; Progam Start
;------------------------------------------------------------------------------
RESET       mov.w   #0280h,SP               ; Initialize stackpointer
SetupWDT    mov.w   #WDT_ADLY_1000,&WDTCTL  ; WDT 1s*4 interval timer
            bis.b   #DIVA_1,&BCSCTL1        ; ACLK/2
            bis.b   #LFXT1S_2,&BCSCTL3      ; ACLK = VLO
            bis.b   #WDTIE,&IE1             ; Enable WDT interrupt
SetupP1     mov.b   #0FFh,&P1DIR            ; All P1.x outputs
            clr.b   &P1OUT                  ; All P1.x reset
SetupP2     mov.b   #0FFh,&P2DIR            ; All P2.x outputs
            clr.b   &P2OUT                  ; All P2.x reset
                                            ;					
Mainloop    bis.b   #001h,&P1OUT            ; Set P1.0
            push.w  #5000                   ; Delay to TOS
Delay       dec.w   0(SP)                   ; Decrement TOS
            jnz     Delay                   ; Delay over?
            incd.w  SP                      ; Clean stack
            bic.b   #001h,&P1OUT            ; Reset P1.0
            bis.w   #LPM3+GIE,SR            ; Enter LPM3, enable interrupts
            jmp     Mainloop                ; Again
                                            ;
;-------------------------------------------------------------------------------
WDT_ISR  ;  Exit LPM3 on reti
;-------------------------------------------------------------------------------
            bic.w   #LPM3,0(SP)             ; Clear LPM3 from TOS
            reti                            ;
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .end
