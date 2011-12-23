;*******************************************************************************
;   MSP430x24x Demo - ADC12, Repeated Sequence of Conversions
;
;   This example shows how to perform a repeated sequence of conversions using
;   "repeat sequence-of-channels" mode.  AVcc is used for the reference and
;   repeated sequence of conversions is performed on Channels A0, A1, A2, and
;   A3. Each conversion result is stored in ADC12MEM0, ADC12MEM1, ADC12MEM2,
;   and ADC12MEM3 respectively. After each sequence, the 4 conversion results
;   are moved to ram locations.  The conversion results for channel A0 are
;   moved to ram addresses 0x1100 - 0x110E, A1 results are moved to addresses
;   0x1110 - 0x111E, A2 results are moved to addresses 0x1120 - 0x112E, and A3
;   results are moved to 0x1130 - 0x113E. Test by applying voltages to channels
;   A0 - A3. Open a memory window in debugger and view the memory contents at
;   the above locations after stopping program execution. Remember the
;   conversion results are 12-bits so you must set the memory window to 16-bit
;   mode.
;
;   Note that a sequence has no restrictions on which channels are converted.
;   For example, a valid sequence could be A0, A3, A2, A4, A2, A1, A0, and A7.
;   See the MSP430x2xx User's Guide for instructions on using the ADC12.
;
;               MSP430x24x
;            -----------------
;           |              XIN|-
;   Vin0 -->|P6.0/A0          | 32kHz
;   Vin1 -->|P6.1/A1      XOUT|-
;   Vin2 -->|P6.2/A2          |
;   Vin3 -->|P6.3/A3          |
;           |                 |
;
;  JL Bile
;  Texas Instruments Inc.
;  May 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x24x.h"
;------------------------------------------------------------------------------- 
A0result    .equ    01100h                  ; Channel A0 results
A1result    .equ    01110h                  ; Channel A1 results
A2result    .equ    01120h                  ; Channel A2 results
A3result    .equ    01130h                  ; Channel A3 results
;-------------------------------------------------------------------------------
	.text	;Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #0500h,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop watchdog
            bis.b   #0fh,&P6SEL             ; Enable A/D inputs
                                            ;
SetupADC12  mov.w   #SHT0_8+MSC+ADC12ON,&ADC12CTL0
                                            ; Turn on ADC12, use int. osc.
                                            ; extend sampling time so won't
                                            ; get overflow
                                            ; Set MSC so conversions triggered
                                            ; automatically
            mov.w   #SHP+CONSEQ_3,&ADC12CTL1
                                            ; Use sampling timer, set mode
            mov.w   #08h,&ADC12IE           ; Enable ADC12IFG.3 for ADC12MEM3
            mov.b   #INCH_0,ADC12MCTL0      ; A0 goes to MEM0
            mov.b   #INCH_1,ADC12MCTL1      ; A1 goes to MEM1
            mov.b   #INCH_2,ADC12MCTL2      ; A2 goes to MEM2
            mov.b   #EOS+INCH_3,ADC12MCTL3  ; A3 goes to MEM3, end of sequence
                                            ;
            clr.w   R5                      ; Clear pointer
                                            ;
Mainloop    bis.w   #ENC,&ADC12CTL0         ; Enable conversions
            bis.w   #ADC12SC,&ADC12CTL0     ; Start conversions
            bis.w   #CPUOFF+GIE,SR          ; Hold in LPM0, Enable interrupts
            nop                             ; Need only for debug
                                            ;
;-------------------------------------------------------------------------------
ADC12_ISR   ; Interrupt Service Routine for ADC12
;-------------------------------------------------------------------------------
            mov.w   &ADC12MEM0,A0result(R5) ; Move results to RAM
            mov.w   &ADC12MEM1,A1result(R5) ; Move results to RAM
            mov.w   &ADC12MEM2,A2result(R5) ; Move results to RAM
            mov.w   &ADC12MEM3,A3result(R5) ; Move results to RAM, IFG reset
            incd.w  R5                      ; Increment results table pointer
            and.w   #0Eh,R5                 ; Modulo pointer
            reti
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".int21"            ; ADC12 Vector
            .short  ADC12_ISR
            .sect   ".reset"            ; POR, ext. Reset
            .short  RESET
            .end
