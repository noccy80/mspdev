;*******************************************************************************
;   MSP430x261x Demo - DMA0, Repeated single transfer to DAC0, Sine Output, TACCR1, DCO
;
;   Description: DMA0 is used to transfer a sine look-up table word-by-word
;   as a repeating block to DAC12_0. The effect is sine wave output. Timer_A
;   operates in upmode with TACCR1 loading DAC12_0 on rising edge and
;   DAC12_0IFG triggering next DMA1 transfer. DAC12_0 uses internal 1.5V
;   reference.
;   ACLK = 32kHz, MCLK = SMCLK = TACLK = default DCO 1048576Hz
;
;                MSP430x2619
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |        DAC0/P6.6|--> ~ 1kHz sine wave
;            |                 |
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
SetupADC12  mov.w   #REFON,&ADC12CTL0       ; Internal reference
SetupDMA0   movx.a  #Sin_tab,&DMA0SA        ; Source block address
            movx.a  #DAC12_0DAT,&DMA0DA     ; Destination single address
            mov.w   #020h,&DMA0SZ           ; Block size
            mov.w   #DMA0TSEL_5,&DMACTL0    ; DAC12IFG trigger
            mov.w   #DMADT_4+DMASRCINCR_3+DMAEN,&DMA0CTL; Rpt, inc src, word-word
SetupDAC120 mov.w   #DAC12LSEL_2+DAC12IR+DAC12AMP_5+DAC12IFG+DAC12ENC,&DAC12_0CTL
SetupC1     mov.w   #OUTMOD_3,&TACCTL1      ; TACCR1 set/reset
            mov.w   #01,&TACCR1             ; TACCR1 PWM Duty Cycle
SetupC0     mov.w   #032-1,&TACCR0          ; Clock period of TACCR0
SetupTA     mov.w   #TASSEL_2+MC_1,&TACTL   ; SMCLK, contmode
                                            ;
Mainloop    bis.b   #CPUOFF,SR              ; Enter LPM0
            nop                             ; Needed only for debugger
                                            ;
;-------------------------------------------------------------------------------
; 12-bit Sine Lookup table with 32 steps
;-------------------------------------------------------------------------------
Sin_tab     .word 2048, 2447, 2831, 3185, 3495, 3750, 3939, 4056
            .word 4095, 4056, 3939, 3750, 3495, 3185, 2831, 2447
            .word 2048, 1648, 1264,  910,  600,  345,  156,   39
            .word    0,   39,  156,  345,  600,  910, 1264, 1648
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"	           ; POR, ext. Reset, Watchdog
            .short  RESET
            .end

