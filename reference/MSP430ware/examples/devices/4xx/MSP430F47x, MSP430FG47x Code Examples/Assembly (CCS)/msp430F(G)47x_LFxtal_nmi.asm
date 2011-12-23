;******************************************************************************
;   MSP430x47xx Demo - LFXT1 Oscillator Fault Detection
;
;   Description: System runs normally in LPM3 with basic timer clocked by
;   32kHz ACLK with a 1 second interrupt.  P4.6 is normally toggled every
;   1 second inside basic timer interrupt.  If an LFXT1 oscllator fault occurs,
;   NMI is requested forcing exit from LPM3. P4.6 is toggled rapidly by software
;   as long as LFXT1 osciallator fault is present.  Assumed only LFXT1 as NMI
;   source - code does not check for other NMI sources.
;   ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
;   //* An external watch crystal between XIN & XOUT is required for ACLK *//	
;
;                MSP430x47xx
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |             P4.6|-->LED
;
;   P.Thanigai
;   Texas Instruments Inc.
;   September 2008
;   Built with Code Composer Essentials Version: 3.0
;******************************************************************************
 .cdecls C,LIST, "msp430xG47x.h" 

;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #0A00h,SP               ; Initialize stack pointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupFLL    bis.b   #XCAP14PF,&FLL_CTL0     ; Configure load caps
SetupBT     mov.b   #BT_ADLY_1000,&BTCTL    ; One-second interrupt
            bis.b   #BTIE,&IE2              ; Enable Basic Timer interrupt
            bis.b   #040h,&P4DIR            ; P4.6 = output direction
; An immediate Osc Fault will occur next
            bis.b   #OFIE,&IE1              ; Enable osc fault interrupt
                                            ;						
Mainloop    bis.w   #LPM3+GIE,SR            ; Enter LPM3, enable interrupts

;------------------------------------------------------------------------------
NMI_ISR;   Only osc fault enabled, R15 used temporarily and not saved
;          Assumed LFXT1 is only source for NMI interrupt
;------------------------------------------------------------------------------
CheckOsc    bic.b   #OFIFG,&IFG1            ; Clear OSC fault flag
            xor.b   #040h,&P4OUT            ; Toggle P4.6
            mov.w   #03FFFh,R15             ; R15 = Delay
CheckOsc1   dec.w   R15                     ; Time for flag to set
            jnz     CheckOsc1               ;
            bit.b   #OFIFG,&IFG1            ; OSC fault flag set?
            jnz     CheckOsc                ; OSC Fault, clear flag again
            bis.b   #OFIE,&IE1              ; re-enable osc fault interrupt
            reti                            ; return from interrupt
                                            ;
;------------------------------------------------------------------------------
BT_ISR;     
;------------------------------------------------------------------------------
            xor.b   #040h,&P4OUT            ; Toggle P4.6
            reti                            ;		
                                            ;
;-----------------------------------------------------------------------------
;           Interrupt Vectors Used
;-----------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int00"                     ; MSP430 RESET Vector
            .short  BT_ISR 
            .sect   ".int14"                     ; MSP430 RESET Vector
            .short  NMI_ISR             
            .end

