;******************************************************************************
;   MSP430x24x Demo - XT2 Oscillator Fault Detection
;
;   Description: System runs normally in LPM3 with Timer A clocked by
;   ACLK.  Basic Timer interrupt causes an exit from LPM3, and toggles P1.0.
;   If an XT2 oscillator fault occurs, NMI is requested, pausing execution and
;   flashing LED quickly until fault is resolved.  Assumed only XT2 as NMI
;   source - code does not check for other NMI sources. MCLK is buffered on 
;   P5.4. If fault occurs for crystal osc sourcing the MCLK, MCLK is 
;   automatically switched to DCO for its clock source
;   MCLK = XT2 = 8MHz normally, within ISRs MCLK = DCO freq ~1045kHz
;   //* An external 8MHx crystal is required between XT2 and XT2OUT , and
;   an external 32kHz crystal is required between XIN and XOUT.  *//	
;
;                MSP430x249
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32KHz
;          --|RST          XOUT|-
;            |                 |
;            |            XT2IN|-
;            |                 | 8MHz
;            |           XT2OUT|-
;            |                 |
;            |             P1.0|-->LED
;            |        P5.4/MCLK|-->MCLK = XT2 HFXTAL
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

SetupBC     bic.b   #XT2OFF,&BCSCTL1        ; Activate XT2 high freq xtal
            bis.b   #XT2S_2,&BCSCTL3        ; 3  16MHz crystal or resonator

SetupOsc    bic.b   #OFIFG,&IFG1            ; Clear OSC fault flag
            mov.w   #01FFFh,R15               ; R15 = Delay
SetupOsc1   dec.w   R15                     ; Additional delay to ensure start
            jnz     SetupOsc1               ;
            bit.b   #OFIFG,&IFG1            ; OSC fault flag set?
            jnz     SetupOsc                ; OSC Fault, clear flag again
                                           
            bis.b   #SELM_2, &BCSCTL2       ; MCLK = XT2 HF XTAL (safe)
                                            ;
SetupP1     bis.b   #010h,&P5DIR            ; P5.4 output direction
            bis.b   #010h,&P5SEL            ; P5.4 option select

SetupTimer  mov.w   #CCIE,&TACCTL0          ; One-second interrupt
            mov.w   #32767,&TACCR0
SetupTA     mov.w   #TASSEL_1+MC_2,&TACTL   ; SMCLK, continuous mode

            bis.b   #001h,&P1DIR            ; P1.0 = output direction
            bic.b   #001h, &P1OUT
; An immediate Osc Fault will occur next
            bis.b   #OFIE,&IE1              ; Enable osc fault interrupt

Mainloop    bis.w   #LPM0+GIE,SR            ; Enter LPM3, enable interrupts
            xor.b   #001h,&P1OUT            ; Toggle P1.0
            jmp     Mainloop                ;
                                            ;
;------------------------------------------------------------------------------
NMI_ISR;   Only osc fault enabled, R15 used temporarily and not saved
;          Assumed LFXT1 is only source for NMI interrupt
;------------------------------------------------------------------------------
CheckOsc    bic.b   #OFIFG,&IFG1            ; Clear OSC fault flag
            xor.b   #001h,&P1OUT            ; Toggle P1.0
            mov.w   #047FFh,R15             ; R15 = Delay
CheckOsc1   dec.w   R15                     ; Time for flag to set
            jnz     CheckOsc1               ;
            bit.b   #OFIFG,&IFG1            ; OSC fault flag set?
            jnz     CheckOsc                ; OSC Fault, clear flag again
            bis.b   #OFIE,&IE1              ; Re-enable osc fault interrupt
            reti                            ; Return from interrupt
                                            ;
;------------------------------------------------------------------------------
TA0_ISR;     Exit LPM3 on reti
;------------------------------------------------------------------------------
            bic.w   #LPM3,0(SP)             ;
            reti                            ;		
                                            ;
;-----------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"            ; POR, ext. Reset
            .short    RESET              ;
            .sect     ".int25"          ; Timer_A0 Vector
            .short   TA0_ISR                 ;
            .sect   ".int30"              ; NMI vector
            .short   NMI_ISR                 ;
            .end
