;*******************************************************************************
;  MSP430x54xA Demo - Single-Byte Flash In-System Programming, Copy SegC to SegD
;
;  Description: This program first erases flash seg C, then it increments all
;  values in seg C, then it erases seg D, then copies seg C to seg D. Starting
;  addresses of segments defined in this code: Seg C-0x1880, Seg D-0x1800.
;  RESET the device to re-execute code. This is implemented to prevent
;  stressing of Flash unintentionally.
;  ACLK = REFO = 32kHz, MCLK = SMCLK = default DCO 1048576Hz
;
;                MSP430x54xA
;            -----------------
;        /|\|              XIN|-
;         | |                 |
;         --|RST          XOUT|-
;           |                 |
;
;   D. Dang
;   Texas Instruments Inc.
;   December 2009
;   Built with CCS Version: 4.0.2 and IAR Embedded Workbench Version: 4.11B
;******************************************************************************
    .cdecls C,LIST,"msp430x54xA.h"

;-------------------------------------------------------------------------------
value    .equ    R4 
;-------------------------------------------------------------------------------
            .global _main 
            .text                           ; Assemble to Flash memory
;-------------------------------------------------------------------------------
_main
RESET       mov.w   #0x5C00,SP              ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
            clr.w   value                   ; initialize value

            call    #write_SegC             ; Write segment C, increment value
            call    #copy_C2D               ; Copy segment C to D
Mainloop    jmp     Mainloop                ; Loop forever, SET BREAKPOINT HERE

;-------------------------------------------------------------------------------
write_SegC ;Input = value, holds value to write to Seg C, R5 used as working reg
;-------------------------------------------------------------------------------
            mov.w   #0x1880,R5              ; Initialize Flash pointer
            dint                            ; 5xx Workaround: Disable global
                                            ; interrupt while erasing. Re-Enable
                                            ; GIE if needed
            mov.w   #FWKEY,&FCTL3           ; Clear Lock bit
            mov.w   #FWKEY+ERASE,&FCTL1     ; Set Erase bit
            mov.w   #0,0(R5)                ; Dummy write to erase Flash seg
            mov.w   #FWKEY+WRT,&FCTL1       ; Set WRT bit for write operation
wrt_SegC_L1 mov.b   value,0(R5)             ; Write value to flash
            inc.w   R5
            inc.b   value;
            cmp.w   #0x1900,R5
            jne     wrt_SegC_L1
            mov.w   #FWKEY,&FCTL1           ; Clear WRT bit
            mov.w   #FWKEY+LOCK,&FCTL3      ; Set LOCK bit
            ret                             ;
;------------------------------------------------------------------------------
copy_C2D ;  Copy Seg C to Seg D, R5 used as working reg.
;------------------------------------------------------------------------------
            mov.w   #0x1880,R5              ; Initialize Flash segment C ptr
            dint                            ; 5xx Workaround: Disable global
                                            ; interrupt while erasing. Re-Enable
                                            ; GIE if needed
Erase_SegD  mov.w   #FWKEY,&FCTL3           ; Clear Lock bit
            mov.w   #FWKEY+ERASE,&FCTL1     ; Set Erase bit
            mov.w   #0,&0x1800              ; Dummy write to erase Flash seg D
            mov.w   #FWKEY+WRT,&FCTL1       ; Set WRT bit for write operation
wrt_C2D_L2  mov.b   @R5+,-129(R5);
            cmp.w   #0x1900,R5
            jne     wrt_C2D_L2
            mov.w   #FWKEY,&FCTL1           ; Clear WRT bit
            mov.w   #FWKEY+LOCK,&FCTL3      ; Set LOCK bit
            ret                             ;
;-------------------------------------------------------------------------------
                  ; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; POR, ext. Reset
            .short  RESET
            .end
