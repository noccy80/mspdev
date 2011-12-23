;*******************************************************************************
;   MSP430F23x0 Demo - Comp_A+, Simple 2.2V Low Battery Detect
;
;   Description: Two Comparator_A+ reference generators 0.25*Vcc and ~0.55V
;   are compared for a simple battery check of 2.2V. In the subroutine
;   Batt_Check, a small capacitor between P2.4 and Vss is first charged
;   to 0.25*Vcc and then compared to ~0.55V. If 0.25*Vcc,
;   is above ~0.55V, P1.0 is toggled, else set. Batt_Check is called
;   constantly in an endless loop. In an actual application, Batt_Check
;   should be called infrequently to save power.
;
;   There is a tolerance of the Comp_A+ reference generator and in the
;   device specific datasheet. In most applications, the tolerence of the
;   reference generator is more than adequate to detect Low Battery.
;   ACLK = n/a, MCLK = SMCLK = default DCO ~1.2MHz
;
;                MSP430F23x0
;             -----------------
;        /|\ |              XIN|-
;         |  |                 |
;         ---|RST          XOUT|-
;            |                 |
;      +-----|P2.4/CA1     P1.0|-->LED
;      |     |                 |
;     ===.1uF|                 |
;      |     |                 |
;      +-----|Vss              |
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x23x0.h"
;-------------------------------------------------------------------------------
	.text	;Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #450h,SP         ; Initialize stackpointer
            mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
            bis.b   #001h,&P1DIR            ; P1.0 output
            mov.b   #P2CA4,&CACTL2          ; P2.4 = CA1
                                            ;
Mainloop    call    #Batt_Check             ;
            jmp     Mainloop                ;
                                            ;
;-------------------------------------------------------------------------------
Batt_Check
;-------------------------------------------------------------------------------
            mov.b   #CAREF0+CAON,&CACTL1    ; 0.25*Vcc on P2.4, Comp, on
Wait        clr.w   R15                     ; SW delay, charge ext. cap
L1          dec.w   R15                     ;
            jnz     L1                      ; Delay over?
            mov.b   #CARSEL+CAREF_3+CAON,&CACTL1  ; 0.55V on -Comp, on
            bit.b   #CAOUT,&CACTL2          ; Test Comparator_A+ output
            clr.b   &CACTL1                 ; Disable Comp_A+, save power
            jnc     Batt_Low                ;
            xor.b   #001h,&P1OUT            ; P1.0 toggle
            ret                             ;
Batt_Low    bis.b   #001h,&P1OUT            ; P1.0 set
            ret                             ;
                                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"            ; MSP430 RESET Vector
            .short	RESET                   ;
            .end
