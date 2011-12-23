;******************************************************************************
;   MSP430xG46x Demo - LFXT1 Oscillator Fault Detection
;
;   Description: System runs normally in LPM3 with basic timer clocked by
;   32kHz ACLK with a 1 second interrupt.  P5.1 is normally toggled every
;   1 second inside basic timer interrupt.  If an LFXT1 oscllator fault occurs,
;   NMI is requested forcing exit from LPM3. P5.1 is toggled rapidly by software
;   as long as LFXT1 osciallator fault is present.  Assumed only LFXT1 as NMI
;   source - code does not check for other NMI sources.
;   ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
;   //* An external watch crystal between XIN & XOUT is required for ACLK *//	
;
;                MSP430xG461x
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |             P5.1|-->LED
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430xG46x.h"
;-------------------------------------------------------------------------------
			.text	;Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #900,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupFLL    bis.b   #XCAP14PF,&FLL_CTL0     ; Configure load caps
SetupBT     mov.b   #BT_ADLY_1000,&BTCTL    ; One-second interrupt
            bis.b   #BTIE,&IE2              ; Enable Basic Timer interrupt
            bis.b   #002h,&P5DIR            ; P5.1 = output direction
; An immedate Osc Fault will occur next
            bis.b   #OFIE,&IE1              ; Enable osc fault interrupt
                                            ;						
Mainloop    bis.w   #LPM3+GIE,SR            ; Enter LPM3, enable interrupts
            xor.b   #002h,&P5OUT            ; Toggle P5.1
            jmp     Mainloop                ;
                                            ;
;------------------------------------------------------------------------------
NMI_ISR;   Only osc fault enabled, R15 used temporarily and not saved
;          Assumed LFXT1 is only source for NMI interrupt
;------------------------------------------------------------------------------
CheckOsc    bic.b   #OFIFG,&IFG1            ; Clear OSC fault flag
            xor.b   #002h,&P5OUT            ; Toggle P5.1
            mov.w   #03FFFh,R15             ; R15 = Delay
CheckOsc1   dec.w   R15                     ; Time for flag to set
            jnz     CheckOsc1               ;
            bit.b   #OFIFG,&IFG1            ; OSC fault flag set?
            jnz     CheckOsc                ; OSC Fault, clear flag again
            bis.b   #OFIE,&IE1              ; re-enable osc fault interrupt
            reti                            ; return from interrupt
                                            ;
;------------------------------------------------------------------------------
BT_ISR;     Exit LPM3 on reti
;------------------------------------------------------------------------------
            bic.w   #LPM3,0(SP)             ;
            reti                            ;		
                                            ;
;-----------------------------------------------------------------------------
;			Interrupt Vectors
;-----------------------------------------------------------------------------
            .sect	".reset"            	; RESET Vector
            .short   RESET
            .sect	".int16"       			; Basic Timer Vector
            .short   BT_ISR                 ;
            .sect	".int30"              ; NMI vector
            .short   NMI_ISR                 ;
            .end
