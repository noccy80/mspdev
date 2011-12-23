;******************************************************************************
;   MSP430x24x Demo - LFXT1 Oscillator Fault Detection
;
;   Description: System runs normally in LPM3 with Timer A clocked by
;   32kHz ACLK with a 1 second interrupt.  P1.0 is normally toggled every
;   1 second inside timer interrupt.  If an LFXT1 oscllator fault occurs,
;   NMI is requested forcing exit from LPM3. P1.0 is toggled rapidly by software
;   as long as LFXT1 osciallator fault is present.  Assumed only LFXT1 as NMI
;   source - code does not check for other NMI sources.
;   ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
;   //* An external watch crystal between XIN & XOUT is required for ACLK *//	
;
;                MSP430x249
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |             P1.0|-->LED
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
SetupP1     bis.b   #001h,&P1DIR            ; P1.0 = output direction

SetupTA     mov.w   #CCIE,&TACCTL0          ; TACCR0 interrupt enabled
            mov.w   #32767,&TACCR0
            mov.w   #TASSEL_1+MC_1,&TACTL   
            
; An immedate Osc Fault will occur next
            bis.b   #OFIE,&IE1              ; Enable osc fault interrupt
                                            ;						
Mainloop    bis.w   #LPM3+GIE,SR            ; Enter LPM3, enable interrupts
            xor.b   #001h,&P1OUT            ; Toggle P1.0
            jmp     Mainloop                ;
                                            ;
;------------------------------------------------------------------------------
NMI_ISR;   Only osc fault enabled, R15 used temporarily and not saved
;          Assumed LFXT1 is only source for NMI interrupt
;------------------------------------------------------------------------------
CheckOsc    bic.b   #OFIFG,&IFG1            ; Clear OSC fault flag
            xor.b   #001h,&P1OUT            ; Toggle P1.0
            mov.w   #03FFFh,R15             ; R15 = Delay
CheckOsc1   dec.w   R15                     ; Time for flag to set
            jnz     CheckOsc1               ;
            bit.b   #OFIFG,&IFG1            ; OSC fault flag set?
            jnz     CheckOsc                ; OSC Fault, clear flag again
            bis.b   #OFIE,&IE1              ; re-enable osc fault interrupt
            reti                            ; return from interrupt
                                            ;
;------------------------------------------------------------------------------
TA_ISR;     
;------------------------------------------------------------------------------
            xor.b   #001h,&P1OUT            ; Toggle P1.0
            reti                            ;		
                                            ;
;-----------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"            ; POR, ext. Reset
            .short    RESET              ;
            .sect     ".int25"          ; Basic Timer Vector
            .short   TA_ISR                 ;
            .sect   ".int30"              ; NMI vector
            .short   NMI_ISR                 ;
            .end