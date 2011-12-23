;*******************************************************************************
;   MSP430x261x Demo - DMA2, Rpt'd single transfer to DAC1, 8-Bit Sine, TBCCR2, DCO
;
;   Description: DMA2 is used to transfer a sine look-up table byte-by-byte
;   as a repeating block to DAC12_1. The effect is a sine wave output. Timer_B
;   operates in upmode with CCR2 loading DAC12_1 on the rising edge, CCR2_CCIFG
;   triggering the next DMA2 transfer. Use external reference on VeRef+.
;   ACLK = 32kHz, MCLK = SMCLK = TBCLK = default DCO 1048576Hz
;
;                MSP430x2619
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;   Ext Ref->|VeRef+  DAC1/P6.7|--> ~ 1kHz sine wave output
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x26x.h"
;-------------------------------------------------------------------------------
	.text	;Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #0850h,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop watchdog timer
SetupDMA2   movx.a  #Sin_tab,&DMA2SA        ; Source block address
            movx.a  #DAC12_1DAT,&DMA2DA     ; Destination single address
            mov.w   #020h,&DMA2SZ           ; Block size
            mov.w   #DMA2TSEL_2,&DMACTL0    ; DAC12IFG trigger
            mov.w   #DMASBDB+DMADT_4+DMASRCINCR_3+DMAEN,&DMA2CTL; Rpt, inc src, byte-byte
SetupDAC12  mov.w   #DAC12SREF_2+DAC12RES+DAC12LSEL_3+DAC12IR+DAC12AMP_5+DAC12ENC,&DAC12_1CTL
                                            ;
SetupC1     mov.w   #OUTMOD_7,&TBCCTL2      ; Reset/set
            mov.w   #01,&TBCCR2             ; PWM Duty Cycle
SetupC0     mov.w   #032-1,&TBCCR0          ; Clock period of TBCCR0
SetupTB     mov.w   #TBSSEL_2+MC_1,&TBCTL   ; SMCLK, up mode
                                            ;
Mainloop    bis.b   #CPUOFF,SR              ; Enter LPM0
            nop                             ; Needed only for debugger
                                            ;
;-------------------------------------------------------------------------------
; 8-bit Sine Lookup table with 32 steps
;-------------------------------------------------------------------------------
Sin_tab     .byte 128, 152, 176, 198, 218, 234, 245, 253
            .byte 255, 253, 245, 234, 218, 198, 176, 152
            .byte 128, 103,  79,  57,  37,  21,  10,   2
            .byte   0,   2,  10,  21,  37,  57,  79, 103
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"	           ; POR, ext. Reset, Watchdog
            .short  RESET
            .end

