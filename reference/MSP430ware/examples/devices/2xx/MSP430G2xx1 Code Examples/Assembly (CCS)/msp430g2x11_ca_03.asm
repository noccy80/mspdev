;*******************************************************************************
;   MSP430G2x11 Demo - Comp_A, Simple 2.2V Low Battery Detect
;
;   Description: Two comparator_A reference generators 0.25*Vcc and ~ 0.55V
;   are compared for a simple battery check of 2.2V. In the subroutine
;   Batt_Check a small capacitor that must be added to P2.3 is first charged
;   to 0.25*Vcc and then compared to ~ 0.55V. If 0.25*Vcc,
;   is above ~0.55V, P1.0 is toggled, else set. Batt_Check is
;   called constantly in an endless loop - in an actual application,
;   Batt_Check should be called very infrequently to save power.
;   ACLK = n/a, MCLK = SMCLK = default DCO
;
;   There is a tolerence of the Comp_A reference generator and in the
;   device specific datasheet. In most applications, the tolerence of the
;   reference generator is more than adequate to detect Low Battery.
;
;		 MSP430G2x11
;             -----------------
;        /|\ |              XIN|-
;         |  |                 |
;         ---|RST          XOUT|-
;            |                 |
;      +-----|P1.1         P1.0|-->LED
;      |     |                 |
;     ===.1uf|                 |
;      |     |                 |			
;      +-----|VSS
;
;   D. Dang
;   Texas Instruments Inc.
;   October 2010
;   Built with Code Composer Essentials Version: 4.2.0
;*******************************************************************************
 .cdecls C,LIST,  "msp430g2211.h"
;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #0280h,SP               ; Initialize stackpointer
            mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
            bis.b   #001h,&P1DIR            ; P1.0 output
            mov.b   #P2CA4,&CACTL2          ; P1.1 = CA1
                                            ;
Mainloop    call    #Batt_Check             ;
            jmp     Mainloop                ;
                                            ;
;-------------------------------------------------------------------------------
Batt_Check
;-------------------------------------------------------------------------------
            mov.b   #CAREF0+CAON,&CACTL1    ; 0.25*Vcc on P2.3, Comp. on
Wait        clr.w   R15                     ; Delay to R15
L1          dec.w   R15                     ;
            jnz     L1                      ; Delay over?
            mov.b   #CARSEL+CAREF1+CAREF0+CAON,&CACTL1 ; 0.55V on -, Comp. on
            bit.b   #CAOUT,&CACTL2          ;
            clr.b   &CACTL1                 ; Disable Comp_A, save power
            jnc      Batt_Low               ;
            xor.b   #001h,&P1OUT            ; P1.0 toggle
            ret                             ;
Batt_Low    bis.b   #001h,&P1OUT            ; P1.0 set
            ret

;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;      
            .end
