;******************************************************************************
;    MSP430F41x2 Demo - Comparator A, Poll input CA0, result in P5.1
;
;   Description: The Voltage at pin CA0 (Vcompare) is compared with reference
;   voltage of 0.5*Vcc. LED is toggled when Vcompare crosses the ref voltage.
;
;
;                 MSP430F41x2
;             -----------------
;         /|\|                 |
;          | |                 |
;          --|RST           CA0|<--Vcompare
;            |                 |
;            |                 |
;            |             P5.1|-->LED
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
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupFLL    bis.b   #XCAP14PF,&FLL_CTL0     ; Configure load caps

            mov.b   #CAON+CAREF_2+CARSEL,&CACTL1  ; Enable Comp, ref = 0.5*Vcc
            mov.b   #P2CA0,&CACTL2          ; Pin to CA0
            bis.b   #CAPD6,&CAPD            ; Port pin buffer disable

SetupP5     bis.b   #002h,&P5DIR            ; P5.1 output

mainloop:   bit.b   #01, &CACTL2            ; Test result
            jz      Loop                    ; jump if result = 0
                                            ; Set LED on if result =1
            bis.b   #BIT1,&P5OUT            ; Set P5.1
            jmp     mainloop
Loop
            bic.b   #BIT1,&P5OUT            ; Clear P5.1
            jmp     mainloop

;-------------------------------------------------------------------------------
;           Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;  
            .end
