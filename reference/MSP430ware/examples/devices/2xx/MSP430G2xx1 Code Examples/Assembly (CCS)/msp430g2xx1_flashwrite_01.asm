;*******************************************************************************
;   MSP430G2xx1 Demo - Flash In-System Programming, Copy SegC to SegD
;
;   Description: This program first erases flash seg C, then it increments all
;   values in seg C, then it erases seg C, then copies seg C to seg D.
;   Assumed MCLK 771kHz - 1428kHz.
;   //* Set Breakpoint in the Mainloop to avoid Stressing Flash *//
;
;                MSP430G2xx1
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;
;
;   D. Dang
;   Texas Instruments Inc.
;   October 2010
;   Built with Code Composer Essentials Version: 4.2.0
;*******************************************************************************
value      .equ      R4
 .cdecls C,LIST,  "msp430g2231.h"
;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #0280h,SP               ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
CheckCal    cmp.b   #0FFh,&CALBC1_1MHZ      ; Calibration constants erased?
            jeq     Trap
            cmp.b   #0FFh,&CALDCO_1MHZ
            jne     Load  
Trap        jmp     $                       ; Trap CPU!!
Load        mov.b   &CALBC1_1MHZ,&BCSCTL1   ; Set DCO to 1MHz
            mov.b   &CALDCO_1MHZ,&DCOCTL
            clr.b   value                   ; value = value to write to flash
                                            ;				          							
Mainloop    call    #Write_SegC             ; Copy value to segment C
            inc.b   value                   ;
            call    #CopyC2D                ;
            jmp     Mainloop                ; Repeat,SET BREAKPOINT HERE
                                            ;
;-------------------------------------------------------------------------------
Write_SegC ;Input = value, holds value to write to Seg C, R5 used as working reg.
;-------------------------------------------------------------------------------
            mov.w   #01040h,R5              ;
Timing      mov.w   #FWKEY+FSSEL0+FN1,&FCTL2  ; *Timing generator = MCLK/3
Erase_SegC  mov.w   #FWKEY,&FCTL3           ; Lock = 0
            mov.w   #FWKEY+ERASE,&FCTL1     ; Erase bit = 1, allow interrupts
            mov.w   #0,&01040h              ; Dummy write to SegC to erase
Prog_SegC   mov.w   #FWKEY+WRT,&FCTL1       ; Write bit = 1, block interrupts
            mov.w   #FWKEY,&FCTL3           ; Lock = 0
Prog_L1     mov.b   value,0(R5)             ;
            inc.w   R5                      ;
            cmp.w   #01080h,R5              ;
            jne     Prog_L1                 ;
            mov.w   #FWKEY+LOCK,&FCTL3      ; Lock = 1;
            ret                             ;
                                            ;
;-------------------------------------------------------------------------------
CopyC2D    ;Copy Seg C to Seg D, R5 used as working reg.
;-------------------------------------------------------------------------------
            mov.w   #FWKEY+FSSEL0+FN1,&FCTL2  ; *Timing generator = MCLK/3
Erase_SegD  mov.w   #FWKEY,&FCTL3           ; Lock = 0
            mov.w   #FWKEY+ERASE,&FCTL1     ; Erase bit = 1
            mov.w   #0,&01000h              ; Dummy write to SegD to erase
            mov.w   #01040h,R5              ; R5 = First byte in Seg C
Prog_SegD   mov.w   #FWKEY+WRT,&FCTL1       ; Write bit = 1, block interrupts
            mov.w   #FWKEY,&FCTL3           ; Lock = 0
Prog_L2     mov.b   @R5+,-65(R5)            ; Copy Seg C to Seg D
            cmp.w   #01080h,R5              ;
            jne     Prog_L2                 ;
            mov.w   #FWKEY+LOCK,&FCTL3      ; Lock = 1
            ret

;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .end
