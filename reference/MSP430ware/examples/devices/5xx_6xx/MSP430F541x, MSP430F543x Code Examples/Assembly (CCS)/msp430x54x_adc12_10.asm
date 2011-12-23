;******************************************************************************
;  MSP430F54x Demo - ADC12, Sample A10 Temp and Convert to oC and oF
;
;  Description: A single sample is made on A10 with reference to internal
;  1.5V Vref. Software sets ADC12SC to start sample and conversion - ADC12SC
;  automatically cleared at EOC. ADC12 internal oscillator times sample
;  and conversion. In Mainloop MSP430 waits in LPM0 to save power until
;  ADC10 conversion complete, ADC12_ISR will force exit from any LPMx in
;  Mainloop on reti.
;  ACLK = n/a, MCLK = SMCLK = default DCO ~ 1.045MHz, ADC12CLK = ADC12OSC
;
;  Uncalibrated temperature measured from device to devive will vary do to
;  slope and offset variance from device to device - please see datasheet.
;
;                MSP430F5438
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |A10              |
;
;   M. Morales
;   Texas Instruments Inc.
;   September 2008
;   Built with Code Composer Essentials v3.x
;******************************************************************************
    .cdecls C,LIST,"msp430x54x.h"

count    .equ    R4 

;-------------------------------------------------------------------------------
;-------------------------------------------------------------------------------
            .bss    int_deg_c,2 
            .bss    int_deg_f,2 
            .bss    temp,2 

;-------------------------------------------------------------------------------
            .global _main 
            .text                           ; Assemble to Flash memory
;-------------------------------------------------------------------------------
_main
RESET       mov.w   #0x5C00,SP              ; Initialize stackpointer
            mov.w   #WDTPW + WDTHOLD,&WDTCTL; Stop WDT

            mov.w   #ADC12ON + ADC12REFON + ADC12SHT0_8,&ADC12CTL0
                                            ; Internal ref = 1.5V
            mov.w   #ADC12SHP,&ADC12CTL1    ; Enable sample timer
            mov.b   #ADC12INCH_10 + ADC12SREF_1,&ADC12MCTL0
                                            ; ADC input ch A1 = temp sensor
            mov.w   #0x0001,&ADC12IE        ; ADC_IFG upon conversion result

delay_loop  mov.w   #30,R15                 ; Delay loop for Ref to settle
            sub.w   R15,R15
            JNZ     delay_loop

            bis.w   #ADC12ENC,&ADC12CTL0    ; Enable conversions

while_loop  bis.w   #ADC12SC,&ADC12CTL0     ; Start conversion - sw trigger

            bis.w   #LPM0 + GIE,SR          ; Enter LPM0, enable interrupts
            nop                             ; Only for debugging purposes
	                                    ;
            calla   #Trans2TempC            ; Transform voltage to temperature
            calla   #BIN2BCD4               ; R13 = TempC = 0000 - 0145 BCD
            mov.w   R13,&int_deg_c          ; int_deg_c = temperature oC

            calla   #Trans2TempF            ; Transform voltage to temperature
            calla   #BIN2BCD4               ; R13 = TempF = 0000 - 0292 BCD
            mov.w   R13,&int_deg_f          ; int_deg_f = temperature oF
                                            ;
            jmp     while_loop              ; SET BREAKPOINT HERE
                                            ;
;-------------------------------------------------------------------------------
Trans2TempC;Subroutine coverts R12 = R12/4096*423-278
;           oC = ((x/4096)*1500mV)-894mV)*1/3.66mV = x*410/4096 - 244
;           Input:  R12  0000 - 0FFFh, R11 working register
;           Output: R12  0000 - 091h
;-------------------------------------------------------------------------------
            mov.w   temp,&MPY               ;
            mov.w   #410,&OP2               ; C
            mov.w   &RESHI,R12              ;
            mov.w   &RESLO,R11              ;
            rlc.w   R11                     ; /4096
            rlc.w   R12                     ;
            rlc.w   R11                     ;
            rlc.w   R12                     ;
            rlc.w   R11                     ;
            rlc.w   R12                     ;
            rlc.w   R11                     ;
            rlc.w   R12                     ;
            sub.w   #244,R12                ; C
            reta                            ;
                                            ;
;-------------------------------------------------------------------------------
Trans2TempF;Subroutine coverts R12 = R12/4096*761-468
;           oF = ((x/4096*1500mV)-829mV)*1/2.033mV = x*738/4096 - 408
;           Input:  R12  0000 - 0FFFh, R11 working register
;           Output: R12  0000 - 0262
;-------------------------------------------------------------------------------
            mov.w   temp,&MPY               ;
            mov.w   #738,&OP2               ; F
            mov.w   &RESHI,R12              ;
            mov.w   &RESLO,R11              ;
            rlc.w   R11                     ; /4096
            rlc.w   R12                     ;
            rlc.w   R11                     ;
            rlc.w   R12                     ;
            rlc.w   R11                     ;
            rlc.w   R12                     ;
            rlc.w   R11                     ;
            rlc.w   R12                     ;
            sub.w   #408,R12                ; F
            reta                            ;
                                            ;
;-------------------------------------------------------------------------------
BIN2BCD4  ; Subroutine converts binary number R12 -> Packed 4-digit BCD R13
;           Input:  R12  0000 - 0FFFh, R15 working register
;           Output: R13  0000 - 4095
;-------------------------------------------------------------------------------
            mov.w   #16,R15                 ; Loop Counter
            clr.w   R13                     ; 0 -> RESULT LSD
BIN1        rla.w   R12                     ; Binary MSB to carry
            dadd.w  R13,R13                 ; RESULT x2 LSD
            dec.w   R15                     ; Through?
            jnz     BIN1                    ; Not through
            reta                            ;
                                            ;
;-------------------------------------------------------------------------------
ADC12_ISR
;-------------------------------------------------------------------------------
            add.w   &ADC12IV,PC             ; Add offset to PC
            reti                            ; Vector 0:  No interrupt
            reti                            ; Vector 2:  ADC overflow
            reti                            ; Vector 4:  ADC timing overflow
            jmp     ADC12IFG0_HND           ; Vector 6:  ADC12IFG0
            reti                            ; Vector 8:  ADC12IFG1
            reti                            ; Vector 10: ADC12IFG2
            reti                            ; Vector 12: ADC12IFG3
            reti                            ; Vector 14: ADC12IFG4
            reti                            ; Vector 16: ADC12IFG5
            reti                            ; Vector 18: ADC12IFG6
            reti                            ; Vector 20: ADC12IFG7
            reti                            ; Vector 22: ADC12IFG8
            reti                            ; Vector 24: ADC12IFG9
            reti                            ; Vector 26: ADC12IFG10
            reti                            ; Vector 28: ADC12IFG11
            reti                            ; Vector 30: ADC12IFG12
            reti                            ; Vector 32: ADC12IFG13
            reti                            ; Vector 34: ADC12IFG14

ADC12IFG0_HND
            mov.w   &ADC12MEM0,temp         ; Move A0 results, IFG is cleared
            bic.w   #LPM0,0(SP)             ; Exit active from ISR
            reti                            ; Return from interrupt

;-------------------------------------------------------------------------------
                  ; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".int55"                ; ADC12 isr vector
            .short  ADC12_ISR
            .sect   ".reset"                ; POR, ext. Reset
            .short  RESET
            .end

