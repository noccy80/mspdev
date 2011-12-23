;*******************************************************************************
;   MSP430F41x2 Demo - ADC10, DTC Sample A0 -> TA1, AVcc, DCO
;
;   Description: Use DTC to sample A0 with reference to AVcc and directly
;   transfer code to CCR1. Timer_A has been configured for 10-bit PWM mode.
;   CCR1 duty cycle is automatically proportional to ADC10 A0. WDT_ISR used
;   as a period wakeup timer approximately 27ms based on default ~1.2MHz
;   DCO/SMCLK clock source used in this example for the WDT clock source.
;   Timer_A also uses default DCO.
;
;                MSP430F41x2
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;        >---|P7.4/A0      P1.2|--> TACCR1 - 0-1024 PWM
;
;  P. Thanigai
;  Texas Instruments Inc.
;  January 2009
;  Built with CCE Version: 3.1   
;******************************************************************************
 .cdecls C,LIST, "msp430x41x2.h" 
  
            .global _main
;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
_main
RESET       mov.w   #0400h,SP               ; Initialize stack pointer
SetupWDT    mov.w   #WDT_MDLY_32,&WDTCTL    ; WDT ~27ms interval timer
            bis.b   #WDTIE,&IE1             ; Enable WDT interrupt
SetupADC10  mov.w   #ADC10SHT_2+ADC10ON,&ADC10CTL0 ;
            bis.b   #001h,&ADC10AE0         ; P2.0 ADC option select
            mov.b   #001h,&ADC10DTC1        ; 1 conversion
SetupP1     bis.b   #004h,&P1DIR            ; P1.2 = output
            bis.b   #004h,&P1SEL            ; P1.2 = TA1 output
SetupC0     mov.w   #1024-1,&TA0CCR0        ; PWM Period
SetupC1     mov.w   #OUTMOD_7,&TA0CCTL1     ; TACCR1 reset/set
            mov.w   #512,&TA0CCR1           ; TACCR1 PWM Duty Cycle
SetupTA     mov.w   #TASSEL_2+MC_1,&TA0CTL  ; SMCLK, upmode
                                            ;
Mainloop    bis.b   #CPUOFF+GIE,SR          ; LPM0, WDT_ISR will force exit
            mov.w   #TA0CCR1,&ADC10SA       ; Data transfer location
            bis.w   #ENC+ADC10SC,&ADC10CTL0 ; Start sampling
            jmp     Mainloop                ; Again
                                            ;
;-------------------------------------------------------------------------------
WDT_ISR;    Exit LPM0 mode, reti returns system active
;-------------------------------------------------------------------------------
            bic.w   #CPUOFF,0(SP)           ; Exit LPM0 on reti
            reti                            ;
                                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".int10"              ; Watchdog Timer
            .short	WDT_ISR
            .sect	".reset"	          ; POR, ext. Reset
            .short      RESET
            .end
