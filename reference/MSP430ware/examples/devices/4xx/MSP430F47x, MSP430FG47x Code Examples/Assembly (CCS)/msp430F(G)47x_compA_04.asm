;******************************************************************************
;   MSP430F(G)47x Demo - Comparator A, Poll input CA0, result in P4.6
;
;   Description: The voltage at pin CA0 (Vcompare) is compared with reference
;   voltage of diode ref.  LED is toggled when Vcompare crosses the ref voltage.
;
;
;                MSP430F(G)47x
;             -----------------
;         /|\|                 |
;          | |                 |
;          --|RST           CA0|<--Vcompare
;            |                 |
;            |                 |
;            |             P4.6|-->LED
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

            mov.b   #CAON+CAREF_3+CARSEL, &CACTL1  ;Enable comp, ref = Diode ref
            mov.b   #P2CA0, &CACTL2         ; Pin to CA0
            bis.b   #CAPD6,&CAPD            ; Port pin buffer disable

SetupP4     bis.b   #040h,&P4DIR            ; P4.6 output
SetupP2     bis.b   #BIT6,&P2SEL            ; P2.6 = CAOUT

mainloop:
            bit.b   #1,&CACTL2              ; Test result
            jz      CAOUT0                  ; jump if result = 0
                                            ; Set LED on if result =1
            bis.b   #BIT6,&P4OUT            ; Set P4.6
            jmp     mainloop
CAOUT0 
            bic.b   #BIT6,&P4OUT            ; Clear P4.6
            jmp     mainloop

;-------------------------------------------------------------------------------
;           Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;  
            .end
