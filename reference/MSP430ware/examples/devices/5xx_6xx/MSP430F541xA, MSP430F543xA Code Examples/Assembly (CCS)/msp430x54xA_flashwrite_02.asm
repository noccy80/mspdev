;*******************************************************************************
;  MSP430x54xA Demo - Flash In-System Programming w/ Long-Word write at 0x1800
;
;  Description: This program first erases flash seg D, then it writes a 32-bit
;  value to memory location 0x1800 using long-word write mode. Long-word write
;  provides faster write than byte/word mode.
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
;
;   D. Dang
;   Texas Instruments Inc.
;   December 2009
;   Built with CCS Version: 4.0.2 
;******************************************************************************

    .cdecls C,LIST,"msp430x54xA.h"

;-------------------------------------------------------------------------------
            .global _main 
            .text                           ; Assemble to Flash memory
;-------------------------------------------------------------------------------
_main
RESET       mov.w   #0x5C00,SP              ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT

            mov.w   #0x1800,R5              ; Initialize Flash pointer
            dint                            ; 5xx Workaround: Disable global
                                            ; interrupt while erasing. Re-Enable
                                            ; GIE if needed
Erase_SegD  mov.w   #FWKEY,&FCTL3           ; Clear Lock bit
            mov.w   #FWKEY+ERASE,&FCTL1     ; Set Erase bit
            mov.w   #0,0(R5)                ; Dummy write to erase Flash seg
write_long  mov.w   #FWKEY+BLKWRT,&FCTL1    ; Enable long-word write
            mov.w   #0x1234,0(R5)
            mov.w   #0x5678,2(R5)           ; Write to Flash
            mov.w   #FWKEY,&FCTL1           ; Clear WRT bit
            mov.w   #FWKEY+LOCK,&FCTL3      ; Set LOCK bit
Mainloop    jmp     Mainloop                ; Loop forever, SET BREAKPOINT HERE
;-------------------------------------------------------------------------------
                  ; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; POR, ext. Reset
            .short  RESET
            .end