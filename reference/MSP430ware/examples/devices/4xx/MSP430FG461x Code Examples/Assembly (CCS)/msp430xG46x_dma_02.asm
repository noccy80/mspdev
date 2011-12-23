;*******************************************************************************
;   MSP430xG461x Demo - DMA0, Repeated Block to P5OUT, TACCR2 Trigger
;
;   Description: DMA0 is used to transfer a string byte-by-byte as a repeating
;   block to P5OUT. Timer_A operates continuously with CCR2IFG
;   triggering DMA0. The effect is P5.0/5.1 toggling at different frequencies.
;   ACLK = 32kHz, MCLK = SMCLK = TACLK = default DCO 1048576Hz
;
;               MSP430xG461x
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |             P5.0|-->
;            |             P5.1|--> LED
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430xG46x.h"
;-------------------------------------------------------------------------------
			.text	;Program Start
;-----------------------------------------------------------------------------
RESET       mov.w   #900,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP5     bis.b   #BIT0+BIT1,&P5DIR       ; P5.0/5.1 output
SetupDMA0   mov.w   #DMA0TSEL_1,&DMACTL0    ; CCR2 trigger
            movx.a  #testconst,&DMA0SA      ; Source block address
            movx.a  #P5OUT,&DMA0DA          ; Destination single address
            mov.w   #06h,&DMA0SZ            ; Block size
            mov.w   #DMADT_4+DMASRCINCR_3+DMASBDB+DMAEN,&DMA0CTL; Rpt, inc src
SetupTA     mov.w   #TASSEL_2+MC_2,&TACTL   ; SMCLK/4, contmode
                                            ;
Mainloop    bis.w   #CPUOFF,SR              ; Enter LPM0
            nop                             ; Required only for debugger
                                            ;
testconst   .byte 00h,03h,02h,03h,00h,01h
                                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"            ; POR, ext. Reset, Watchdog
            .short   RESET
            .end
