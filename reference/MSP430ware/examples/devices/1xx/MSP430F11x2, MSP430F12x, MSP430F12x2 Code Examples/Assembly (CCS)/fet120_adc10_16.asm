;******************************************************************************
;   MSP-FET430P120 Demo - ADC10, DTC Sample A0 -> TA1, AVcc, DCO
;
;   Description: Use DTC to sample A0 with reference to AVcc and directly
;   transfer code to CCR1. Timer_A has been configured for 10-bit PWM mode.
;   CCR1 duty cycle is automatically proportional to ADC10 A0. WDT_ISR used
;   as a period wakeup timer approximately 30ms based on default ~ 800khz
;   DCO/SMCLK clock source used in this example for the WDT clock source.
;   Timer_A also uses default DCO.
;   //* MSP430F12x2 or MSP430F11x2 Device Required *//
;
;                MSP430F1232
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;        >---|A0           P1.2|--> CCR1 - 0-1024 PWM
;
;   M. Buccini / M. Raju
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430x12x2.h"
;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #0300h,SP               ; Initialize stackpointer
SetupWDT    mov.w   #WDT_MDLY_32,&WDTCTL    ; WDT ~30ms interval timer
            bis.b   #WDTIE,&IE1             ; Enable WDT interrupt
SetupADC10  mov.w   #ADC10SHT_2+ADC10ON,&ADC10CTL0 ;
            bis.b   #01h,&ADC10AE           ; P2.0 ADC option select
            mov.b   #001h,&ADC10DTC1        ; 1 conversion
SetupP1     bis.b   #004h,&P1DIR            ; P1.2 = output
            bis.b   #004h,&P1SEL            ; P1.2 = TA1 output
SetupC0     mov.w   #1024-1,&CCR0           ; PWM Period
SetupC1     mov.w   #OUTMOD_7,&CCTL1        ; CCR1 reset/set
            mov.w   #512,&CCR1              ; CCR1 PWM Duty Cycle	
SetupTA     mov.w   #TASSEL_2+MC_1,&TACTL   ; SMCLK, upmode
                                            ;
Mainloop    bis.b   #CPUOFF+GIE,SR          ; LPM0, WDT_ISR will force exit
            mov.w   #CCR1,&ADC10SA          ; Data trasfer location
            bis.w   #ENC+ADC10SC,&ADC10CTL0 ; Start sampling
            jmp     Mainloop                ; Again
                                            ;
;------------------------------------------------------------------------------
WDT_ISR;    Exit all LPMx modes, reti returns system active with GIE enabled
;------------------------------------------------------------------------------
            mov.w   #GIE,0(SP)              ; System active on TOS
            reti                            ;		
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int10"                ; WDT Vector
            .short  WDT_ISR                 ;
            .end
