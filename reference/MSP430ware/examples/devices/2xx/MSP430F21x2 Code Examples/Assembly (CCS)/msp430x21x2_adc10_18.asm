;*******************************************************************************
;   MSP430F21x2 Demo - ADC10, DTC Sample A1/0 -> TA1/2, 2.5V, HF XTAL
;
;   Description: Use DTC to sample both A1 and A0 with reference to internal
;   2.5V Vref continously and directly transfer codes to Timer_A CCR1 and CCR2
;   output units. Timer_A has been configured for 10-bit PWM mode. CCR1 and
;   CCR2 duty cycles are automatically proportional to ADC10 A1 and A0
;   respectively. No CPU resources are required and in this example the CPU is
;   turned off. ADC10 A1/A0 sampling and transfers to TA1/TA2 done continously
;   and automatically by the DTC.
;   MCLK = SMCLK = HF XTAL = 8MHz, ACLK = (HF XTAL)/8
;   As coded, ADC10CLK = ACLK/8 = 125kHz, and each Ax sample and transfer to
;   TAx requires 77 ADC10CLK. With an 8MHz HF XTAL, loop transfer rate is
;   125k/(2*77) = 812/second.
;   //* An external 8MHz XTAL on XIN XOUT is required for ACLK *//
;   //* Min Vcc required varies with MCLK frequency - refer to datasheet *//
;
;                MSP430F21x2
;             -----------------
;         /|\|              XIN|-
;          | |                 | HF XTAL (3  16MHz crystal or resonator)
;          --|RST          XOUT|-
;            |                 |
;        >---|P2.1/A1      P1.2|--> TACCR1 - 0-1024 PWM
;        >---|P2.0/A0      P1.3|--> TACCR2 - 0-1024 PWM
;
;  JL Bile
;  Texas Instruments Inc.
;  May 2008
;  Built with Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x21x2.h"
;-------------------------------------------------------------------------------
 			.text							;Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #025Fh,SP 		        ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupBC     bis.b   #XTS+DIVA_3,&BCSCTL1    ; ACLK = (LFXT1 = HF XTAL)/8
            bis.b   #LFXT1S1,&BCSCTL3       ; 3  16MHz crystal or resonator
SetupOsc    bic.b   #OFIFG,&IFG1            ; Clear OSC fault flag
            mov.w   #0FFh,R15               ; R15 = Delay
SetupOsc1   dec.w   R15                     ; Additional delay to ensure start
            jnz     SetupOsc1               ;
            bit.b   #OFIFG,&IFG1            ; OSC fault flag set?
            jnz     SetupOsc                ; OSC Fault, clear flag again
            bis.b   #SELM_3+SELS,&BCSCTL2   ; MCLK = SMCLK = LFXT1
SetupP1     bis.b   #00Ch,&P1DIR            ; P1.2/P1.3 = outputs
            bis.b   #00Ch,&P1SEL            ; P1.2/P1.2 = TA1/TA2 outputs
SetupC1     mov.w   #OUTMOD_7,&TACCTL1      ; TACCR1 reset/set
            mov.w   #512,&TACCR1            ; TACCR1 PWM Duty Cycle
SetupC2     mov.w   #OUTMOD_7,&TACCTL2      ; TACCR2 reset/set
            mov.w   #512,&TACCR2            ; TACCR2 PWM Duty Cycle
SetupTA     mov.w   #TASSEL_2+MC_1,&TACTL   ; SMCLK, upmode
SetupADC10  mov.w   #INCH_1+ADC10DIV_7+ADC10SSEL_1+CONSEQ_3,&ADC10CTL1 ; ACLK
            mov.w   #SREF_1+ADC10SHT_3+MSC+REF2_5V+REFON+ADC10ON,&ADC10CTL0;
            mov.w   #30,&TACCR0             ; Delay to allow Ref to settle
            bis.w   #CCIE,&TACCTL0          ; Compare-mode interrupt.
            mov.w   #TACLR+MC_1+TASSEL_2,&TACTL; up mode, SMCLK
            bis.w   #LPM0+GIE,SR            ; Enter LPM0,enable interrupts
            bic.w   #CCIE,&TACCTL0          ; Disable timer interrupt
SetupC0     mov.w   #1024-1,&TACCR0         ; PWM Period
            bis.b   #03h,&ADC10AE0          ; P2.0/P2.1 ADC option select
            bis.b   #ADC10CT,&ADC10DTC0     ; Continous transfers
            mov.b   #002h,&ADC10DTC1        ; 2 conversion locations
            mov.w   #TACCR1,&ADC10SA        ; First data trasfer location
            bis.w   #ENC+ADC10SC,&ADC10CTL0 ; Start sampling
                                            ;
Mainloop    bis.b   #CPUOFF,SR              ; CPU not required
            nop                             ; Required only for debugger
                                            ;
;-------------------------------------------------------------------------------
TA0_ISR;    ISR for TACCR0
;-------------------------------------------------------------------------------
            bic.w   #LPM0,0(SP)             ; Exit LPM0 on reti
            reti                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".int09"          		; Timer_A0 Vector
            .short  TA0_ISR
            .sect   ".reset"	            ; POR, ext. Reset
            .short  RESET
            .end
            