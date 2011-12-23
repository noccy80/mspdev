;******************************************************************************
;   MSP-FET430P440 Demo - ADC12, Sample A10 Temp and Convert to oC and oF
;
;   Description: A single sample is made on A10 with reference to internal
;   1.5V Vref. Software sets ADC12SC to start sample and conversion - ADC12SC
;   automatically cleared at EOC. ADC12 internal oscillator times sample
;   and conversion. In Mainloop MSP430 waits in LPM0 to save power until
;   ADC10 conversion is complete. ADC12_ISR forces exit from any LPMx in
;   Mainloop on reti. Result is converted to temperature represented as
;   BCD 0000 - 0145 representing oC saved at 0200h and 0000 - 0292 representing
;   oF saved at 0202h.
;   ACLK = n/a, MCLK = SMCLK = default DCO, ADC12CLK = ADC12OSC
;
;   Uncalibrated temperature measured will vary from device to device do to
;   slope and offset variance - please see datasheet.
;
;                 MSP430F449
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |A10 (Temp)       |
;
;   M. Buccini / A. Dannenberg
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST, "msp430x44x.h"
;------------------------------------------------------------------------------
            .text                  			; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #0A00h,SP               ; Initialize stack pointer
            mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
            mov.w   #SHT0_8+REFON+ADC12ON,&ADC12CTL0 ; 1.5v ref.
            mov.w   #SHP,&ADC12CTL1         ; Enable sample timer
            mov.b   #SREF_1+INCH_10,&ADC12MCTL0  ; Vref = Vref+, temp sensor
            bis.w   #BIT0,&ADC12IE         ; Enable interrupt for ADC12IFG.0
                                            ;
Mainloop    bis.w   #ENC+ADC12SC,&ADC12CTL0 ; Start sampling/conversion
            bis.w   #CPUOFF+GIE,SR          ; LPM0, ADC10_ISR forces exit
            call    #Trans2TempC            ; Transform voltage to temperature
            call    #BIN2BCD4               ; R13 = TempC = 0000 - 0145 BCD
            mov.w   R13,&0200h              ; 0200h = temperature oC
            call    #Trans2TempF            ; Transform voltage to temperature
            call    #BIN2BCD4               ; R13 = TempF = 0000 - 0292 BCD
            mov.w   R13,&0202h              ; 0202h = temperature oF
            jmp     Mainloop                ; set BREAKPOINT HERE
                                            ;
;------------------------------------------------------------------------------
Trans2TempC;Subroutine coverts R12 = R12/4096*423-278
;           oC = ((x/4096)*1500mV)-986mV)*1/3.55mV = x*423/4096 - 278
;           Input:  R12  0000 - 0FFFh, R11 working register
;           Output: R12  0000 - 091h
;------------------------------------------------------------------------------
            mov.w   #423, r11               ; C
            call    #MPYU
            mov.w   r15,  R12               ;
            mov.w   r14,  R11               ;
            rlc.w   R11                     ; /4096
            rlc.w   R12                     ;
            rlc.w   R11                     ;
            rlc.w   R12                     ;
            rlc.w   R11                     ;
            rlc.w   R12                     ;
            rlc.w   R11                     ;
            rlc.w   R12                     ;
            sub.w   #278,R12                ; C
            ret                             ;
                                            ;
;-----------------------------------------------------------------------------
Trans2TempF;Subroutine coverts R12 = R12/4096*761-468
;           oF = ((x/4096*1500mV)-923mV)*1/1.97mV = x*761/4096 - 468
;           Input:  R12  0000 - 0FFFh, R11 working register
;           Output: R12  0000 - 0262
;-----------------------------------------------------------------------------
            mov.w   &ADC12MEM0,R12          ; Clear IFG flag
            mov.w   #761,r11                ; F
            call    #MPYU
            mov.w   r15, R12                ;
            mov.w   r14,R11                 ;
            rlc.w   R11                     ; /4096
            rlc.w   R12                     ;
            rlc.w   R11                     ;
            rlc.w   R12                     ;
            rlc.w   R11                     ;
            rlc.w   R12                     ;
            rlc.w   R11                     ;
            rlc.w   R12                     ;
            sub.w   #468,R12                ; F
            ret                             ;
                                            ;
;------------------------------------------------------------------------------
MPYU   ;    Unsigned Multipy R11 x R12 = R15|R14
       ;    Input:  R11, R12 -- R10 and R13 are working registers
       ;    Output: R15, R14
;------------------------------------------------------------------------------
            clr.w   R14                     ; 0 -> LSBs result
            clr.w   R15                     ; 0 -> MSBs result
MACU        clr.w   R13                     ; MSBs multiplier
            mov.w   #1,R10                  ; bit test register
MPY2        bit.w   R10,R11                 ; test actual bit
            jz      MPY1                    ; IF 0: do nothing
            add.w   R12,R14                 ; IF 1: add multiplier to result
            addc.w  R13,R15                 ;
MPY1        rla.w   R12                     ; multiplier x 2
            rlc.w   R13                     ;
            rla.w   R10                     ; next bit to test
            jnc     MPY2                    ; if bit in carry: finished
            ret                             ; Return from subroutine
                                            ;
;-----------------------------------------------------------------------------
BIN2BCD4  ; Subroutine converts binary number R12 -> Packed 4-digit BCD R13
;           Input:  R12  0000 - 0FFFh, R15 working register
;           Output: R13  0000 - 4095
;-----------------------------------------------------------------------------
            mov.w   #16,R15                 ; Loop Counter
            clr.w   R13                     ; 0 -> RESULT LSD
BIN1        rla.w   R12                     ; Binary MSB to carry
            dadd.w  R13,R13                 ; RESULT x2 LSD
            dec.w   R15                     ; Through?
            jnz     BIN1                    ; Not through
            ret                             ;
                                            ;
;-----------------------------------------------------------------------------
ADC12_ISR;  ADC12MEM0 -> R12, exit any LPMx mode
;           Output: R12  0000 - 0FFFh
;-----------------------------------------------------------------------------
            mov.w   &ADC12MEM0,R12          ; Clears ADC12IFG.0 flag
            mov.w   #GIE,0(SP)              ; Enable Int. exit LPMx on reti
            reti                            ;
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect	".reset"                ; RESET Vector
            .short  RESET                   ;
            .sect   ".int07"                ; ADC12 Vector
            .short  ADC12_ISR               ;
            .end
