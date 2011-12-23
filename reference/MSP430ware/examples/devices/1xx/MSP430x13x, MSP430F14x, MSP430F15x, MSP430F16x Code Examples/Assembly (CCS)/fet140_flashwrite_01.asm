;*****************************************************************************
;   MSP-FET430P140 Demo - Flash In-System Programming, Copy SegA to SegB
;
;   Description: This program first erases flash seg A, then it increments all
;   values in seg A, then it erases seg B, then  copies seg A to seg B.
;   Assumed MCLK 550kHz - 900kHz.
;   //* Set Breakpoint in the Mainloop to avoid Stressing Flash *//
;
;                MSP430F149
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;
value   .equ     R4
;
;   M. Buccini / G. Morton
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430x14x.h"
;------------------------------------------------------------------------------
            .text                           ; Progam Start
;------------------------------------------------------------------------------
RESET       mov.w   #0A00h,SP               ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
            clr.b   value                   ; value = value to write to flash
                                            ;				          			
Mainloop    call    #Write_SegA             ; Copy value to segment A
            inc.b   value                   ;
            call    #CopyA2B                ;
            jmp     Mainloop                ; Repeat, SET BREAKPOINT HERE
                                            ;
;------------------------------------------------------------------------------
Write_SegA ;Input = value, holds value to write to Seg A, R5 used as working reg.
;------------------------------------------------------------------------------
            mov.w   #01080h,R5              ;
Timing      mov.w   #FWKEY+FSSEL0+FN0,&FCTL2 ; *Timing generator = MCLK/2
Erase_SegA  mov.w   #FWKEY,&FCTL3           ; Lock = 0
            mov.w   #FWKEY+ERASE,&FCTL1     ; Erase bit = 1
            mov.w   #0,&01080h              ; Dummy write to SegA to erase
Prog_SegA   mov.w   #FWKEY+WRT,&FCTL1       ; Write bit = 1
Prog_L1     mov.b   value,0(R5)             ;
            inc.w   R5                      ;
            cmp.w   #01100h,R5              ;
            jne     Prog_L1                 ;
            mov.w   #FWKEY+LOCK,&FCTL3      ; Lock = 1
            ret                             ;
                                            ;
;------------------------------------------------------------------------------
CopyA2B    ;Copy Seg A to Seg B, R5 used as working reg.
;------------------------------------------------------------------------------
            mov.w   #FWKEY+FSSEL0+FN1,&FCTL2  ; *Timing generator = MCLK/3
Erase_SegB  mov.w   #FWKEY,&FCTL3           ; Lock = 0
            mov.w   #FWKEY+ERASE,&FCTL1     ; Erase bit = 1
            mov.w   #0,&01000h              ; Dummy write to SegB to erase
            mov.w   #01080h,R5              ; R5 = First byte in Seg A
Prog_SegB   mov.w   #FWKEY+WRT,&FCTL1       ; Write bit = 1
Prog_L2     mov.b   @R5+,-129(R5)           ; Copy Seg A to Seg B
            cmp.w   #01100h,R5              ;
            jne     Prog_L2                 ;
            mov.w   #FWKEY+LOCK,&FCTL3      ; Lock = 1
            ret

;-----------------------------------------------------------------------------
;           Interrupt Vectors
;-----------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .end
