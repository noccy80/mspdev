;*******************************************************************************
;   MSP430x11x1 Demo - Comp_A, Output Reference Voltages on P2.3
;
;   Description: Output comparator_A reference levels on P2.3.  Program will
;   cycle through the on-chip comparator_A reference voltages with output on
;   P2.3. Normal mode is LPM0 with TA0 triggering interrupt for next mode.
;   ACLK = n/a, MCLK = SMCLK = default DCO ~800k
;
;		 MSP430F1121
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |             P2.3|-->Vref
;            |                 |			
;
;   M. Buccini / Z. Albus
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;*******************************************************************************
 .cdecls C,LIST,  "msp430x11x1.h"
;-------------------------------------------------------------------------------
            .text                           ; Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #300h,SP                ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
            mov.b   #008h, &CAPD            ; Disconnect port pins
            mov.b   #P2CA0,&CACTL2          ; P2.3 = CA0
SetupC0     mov.w   #CCIE,&CCTL0            ; CCR0 interrupt enabled
SetupTA     mov.w   #TASSEL_2+ID_3+MC_2,&TACTL   ; SMCLK/8, contmode
            eint                            ; General enable interrupts
                                            ;
Mainloop    clr.b   &CACTL1                 ; No reference voltage
            bis.w   #CPUOFF,SR              ; CPU off
Ref1        mov.b   #CAREF0+CAON,&CACTL1    ; 0.25*Vcc on P2.3, Comp. on
            bis.w   #CPUOFF,SR              ; CPU off
Ref2        mov.b   #CAREF1+CAON,&CACTL1    ; 0.5*Vcc on P2.3, Comp. on
            bis.w   #CPUOFF,SR              ; CPU off
Ref3        mov.b   #CAREF1+CAREF0+CAON,&CACTL1     ; 0.55V on P2.3, Comp. on
            bis.w   #CPUOFF,SR              ; CPU off
            jmp     Mainloop                ;

;-------------------------------------------------------------------------------
TA0_ISR;    Exit LPM0
;-------------------------------------------------------------------------------
            bic.w   #CPUOFF,0(SP)           ; Exit LPM0 on RETI
            reti                            ;		
                                            ;
;-------------------------------------------------------------------------------
;           Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int09"                ; Timer_A0 Vector
            .short  TA0_ISR                 ;
            .end
