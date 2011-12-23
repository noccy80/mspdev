;******************************************************************************
;  MSP430F21x2 Demo - Timer1_A, Toggle P3.6/TA1_1, Up Mode, HF XTAL ACLK
;
;  Description: Toggle P3.6 using hardware TA0_1 output. Timer1_A is configured
;  for up mode with TA1CCR0 defining period. In this
;  example, TA1CCR0 is loaded with 500-1 and TA0_1 will toggle P3.6 at TA1CLK/500.
;  Thus the output frequency on P3.6 will be the TA1CLK/1000. No CPU or
;  software resources required.
;  ACLK = MCLK = TA1CLK = HF XTAL
;  ;* HF XTAL REQUIRED AND NOT INSTALLED ON FET *;
;  ;* Min Vcc required varies with MCLK frequency - refer to datasheet *;
;  As coded with TACLK = ACLK, P3.6 output frequency = HF XTAL/1000
;
;           MSP430F21x2
;         -----------------
;     /|\|              XIN|-
;      | |                 | HF XTAL (3  16MHz crystal or resonator)
;      --|RST          XOUT|-
;        |                 |
;        |       P3.6/TA0_1|--> ACLK/1000
;
;  JL Bile
;  Texas Instruments Inc.
;  May 2008
;  Built with Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x21x2.h"
;-------------------------------------------------------------------------------
 			.text							; Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #025Fh,SP         		; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP3     bis.b   #040h,&P3DIR            ; P3.6 output
            bis.b   #040h,&P3SEL            ; P3.6 option slect
SetupBC     bis.b   #XTS,&BCSCTL1           ; LFXT1 = HF XTAL
            mov.b   #LFXT1S1,&BCSCTL3       ; LFXT1S1 = 3-16Mhz
SetupOsc    bic.b   #OFIFG,&IFG1            ; Clear OSC fault flag
            mov.w   #0FFh,R15               ; R15 = Delay
SetupOsc1   dec.w   R15                     ; Additional delay to ensure start
            jnz     SetupOsc1               ;
            bit.b   #OFIFG,&IFG1            ; OSC fault flag set?
            jnz     SetupOsc                ; OSC Fault, clear flag again
            bis.b   #SELM_3,&BCSCTL2        ; MCLK = LFXT1
SetupC0     mov.w   #OUTMOD_4,&TA1CCTL0      ; TACCR0 toggle mode
            mov.w   #500-1,&TA1CCR0          ;
SetupTA     mov.w   #TASSEL_1+MC_1,&TA1CTL   ; ACLK, upmode
                                            ;
Mainloop    bis.w   #CPUOFF,SR              ; CPU off
            nop                             ; Required only for debugger
                                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"				; MSP430 RESET Vector
            .short	RESET                   ;
            .end
            