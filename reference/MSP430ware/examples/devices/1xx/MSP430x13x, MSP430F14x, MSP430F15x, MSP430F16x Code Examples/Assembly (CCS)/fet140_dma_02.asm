;******************************************************************************
;   MSP430F169 Demo - DMA0, Repeated Block to P1OUT, TACCR2 Trigger
;
;   Description: DMA0 is used to transfer a string byte-by-byte as a repeating
;   block to P1OUT. Timer_A operates continuously at ~800Hz with CCR2IFG
;   triggering DMA0. The effect is P1.0/1.1 toggling at different frequencies.
;   ACLK = n/a, MCLK = SMCLK =  TACLK = default DCO ~800k
;
;                MSP430F169
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |             P1.0|--> LED
;            |             P1.1|-->
;
;   M. Buccini / L. Westlund
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430x16x.h"
;------------------------------------------------------------------------------
            .text                  ; Progam Start
;------------------------------------------------------------------------------
RESET       mov.w   #0A00h,SP               ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP1     bis.b   #003h,&P1DIR            ; P1.0/1.1 output
SetupDMA0   mov.w   #DMA0TSEL_1,&DMACTL0    ; CCR2 trigger
            mov.w   #testconst,&DMA0SA      ; Source block address
            mov.w   #P1OUT,&DMA0DA          ; Destination single address
            mov.w   #06h,&DMA0SZ            ; Block size
            mov.w   #DMADT_4+DMASRCINCR_3+DMASBDB+DMAEN,&DMA0CTL; Rpt, inc src
SetupTA     mov.w   #TASSEL_2+MC_2,&TACTL   ; SMCLK/4, contmode
                                            ;
Mainloop    bis.w   #CPUOFF,SR              ;
            nop                             ; Required only for debugger
                                            ;
testconst   .byte  00h,03h,02h,03h,00h,01h
                                            ;
;-----------------------------------------------------------------------------
;           Interrupt Vectors
;-----------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .end
