;******************************************************************************
;   MSP430x249 Demo - Timer_A, Toggle P1.1/TA0, Up Mode, 32kHz ACLK
;
;   Description: Toggle P1.1 using hardware TA0 output. Timer_A is configured
;   for up mode with TACCR0 defining period, TA0 also output on P1.1. In this
;   example, TACCR0 is loaded with 10-1 and TA0 will toggle P1.0 at TACLK/10.
;   Thus the output frequency on P1.1 will be the TACLK/20. No CPU or software
;   resources required. Normal operating mode is LPM3.
;   As coded with TACLK = ACLK, P1.1 output frequency = 32768/20 = 1.6384kHz.
;   ACLK = TACLK = 32kHz, MCLK = default DCO ~1048kHz
;   //* External watch crystal installed on XIN XOUT is required for ACLK *//	
;
;                MSP430x249
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |         P1.1/TA0|--> ACLK/20
;
;  JL Bile
;  Texas Instruments Inc.
;  May 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x24x.h"
;-------------------------------------------------------------------------------
			.text	;Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #0500h,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT

OFIFGcheck  bic.b   #OFIFG,&IFG1            ; Clear OFIFG
            mov.w   #047FFh,R15             ; Wait for OFIFG to set again if
OFIFGwait   dec.w   R15                     ; not stable yet
            jnz     OFIFGwait
            bit.b   #OFIFG,&IFG1            ; Has it set again?
            jnz     OFIFGcheck              ; If so, wait some more

SetupP1     bis.b   #BIT1,&P1DIR            ; P1.1 output
            bis.b   #BIT1,&P1SEL            ; P1.1 option slect
SetupC0     mov.w   #OUTMOD_4,&TACCTL0      ; TACCR0 toggle mode
            mov.w   #10-1,&TACCR0           ;
SetupTA     mov.w   #TASSEL_1+MC_1,&TACTL   ; ACLK, upmode
                                            ;						
Mainloop    bis.w   #LPM3,SR                ; Enter LPM3
            nop                             ; Required only for debugger
                                            ;
;------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"            ; POR, ext. Reset
            .short  RESET                   ;
            .end
