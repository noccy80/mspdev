;******************************************************************************
;  MSP430F(G)47x Demo - DAC12_0, Output Voltage Ramp on DAC0
;
;  Description: Using DAC12_0 and 1.2V SD16REF reference with a gain of 1,
;  output positive ramp on DAC0. Normal mode is LPM0 with CPU off.  WDT used
;  to provide ~61us interrupt used to wake up the CPU and update the DAC
;  with software.
;  ACLK = n/a, MCLK = SMCLK = default DCO
;
;               MSP430F(G)47x
;            -----------------
;        /|\|              XIN|-
;         | |                 |
;         --|RST          XOUT|-
;           |                 |
;           |        P1.6/DAC0|--> Ramp_positive
;           |                 |
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
SetupWDT    mov.w   #WDT_MDLY_0_064,&WDTCTL   ; WDT 61us interval timer
            bis.b   #WDTIE,&IE1             ; Enable WDT interrupt
SetupSD16  mov.w    #SD16REFON,&SD16CTL     ; Internal 1.2V ref on
SetupDAC120 mov.w   #DAC12IR + DAC12AMP_5 + DAC12ENC + DAC12SREF_3 + DAC12CALON + DAC12OPS,&DAC12_0CTL                                          					
Mainloop    bis.w   #CPUOFF+GIE,SR          ; Enter LPM0, interrupts enabled
            inc.w   &DAC12_0DAT             ; Positive ramp
            and.w   #0FFFh,&DAC12_0DAT      ;
            jmp     Mainloop                ;
                                            ;
;------------------------------------------------------------------------------
WDT_ISR  ;  Exit LPM0 on reti
;------------------------------------------------------------------------------
            bic.w   #CPUOFF,0(SP)           ; TOS = clear LPM0
            reti                            ;
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int10"                     ; MSP430 RESET Vector
            .short  WDT_ISR 
            .end
