;******************************************************************************
; MSP430x66x Demo - COMPB Toggle from LPM4; CompB in ultra low power mode
; 		Vcompare is compared against the Vcc*1/2
;
; Description: Use CompB and shared reference to determine if input 'Vcompare'
;    is high or low.  When Vcompare exceeds Vcc*1/2 CBOUT goes high and when 
;    Vcompare is less than Vcc*1/2 then CBOUT goes low. 
;    Connect P3.0/CBOUT to P1.0 externally to see the LED toggle accordingly.
;                                                   
;                 MSP430x66x
;             ------------------                        
;         /|\|                  |                       
;          | |                  |                       
;          --|RST      P6.0/CB0 |<--Vcompare            
;            |                  |                                         
;            |        P3.0/CBOUT|----> 'high'(Vcompare>Vcc*1/2); 'low'(Vcompare<Vcc*1/2)
;            |                  |  |
;            |            P1.0  |__| LED 'ON'(Vcompare>Vcc*1/2); 'OFF'(Vcompare<Vcc*1/2)
;            |                  | 
;
;   Priya Thanigai
;   Texas Instruments Inc.
;   August 2011
;   Built with CCS V5
;******************************************************************************
            .cdecls C,LIST,"msp430f6638.h"

;-------------------------------------------------------------------------------
            .global _main
            .text                           ; Assemble to Flash memory
;-------------------------------------------------------------------------------
_main
RESET       mov.w   #0x63FE,SP              ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
            
SetupPort   bis.b   #BIT0,&P3DIR            ; P3.0 output
            bis.b   #BIT0,&P3SEL            ; P3.0 option select

            bis.w   #CBIPEN+CBIPSEL_0,&CBCTL0; Enable V+, input channel CB0
            bis.w   #CBPWRMD_2+CBMRVS,&CBCTL1; normal power mode, selects ref
            bis.w   #CBRSEL,&CBCTL2         ; Vref to -ve terminal
            bis.w   #CBRS_1+CBREF04,&CBCTL2 ; VCC applied to R-ladder
                                            ; VREF0 is Vcc*1/2
            
            bis.w   #BIT0,&CBCTL3           ; Input buffer disable P6.0
            bis.w   #CBON,&CBCTL1
            
; Delay for reference settle = 75us
            mov.w   #01ffh,R15
delay_L1    dec.w   R15
            jnz     delay_L1
            
            bis.w   #LPM4,SR                ; Enter low power mode
            nop

;-------------------------------------------------------------------------------
                  ; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; POR, ext. Reset
            .short  RESET
            .end
