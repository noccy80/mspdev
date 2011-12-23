;******************************************************************************
;   MSP430x261x Demo - Timer_A, Toggle P1.1/TA0, Up/Down Mode, DCO SMCLK
;
;   Description: Toggle P1.1 using hardware TA0 output. Timer_A is configured
;   for up/down mode with TACCR0 defining period, TA0 also output on P1.1. In
;   this example, TACCR0 is loaded with 250 and TA0 will toggle P1.0 at
;   TACLK/2*250. Thus the output frequency on P1.1 will be the TACLK/1000.
;   No CPU or software resources required.
;   As coded with TACLK = SMCLK, P1.1 output frequency is ~1048000/1000.
;   SMCLK = MCLK = TACLK = default DCO = 32*ACLK = ~1048kHz
;
;                MSP430F241x
;                MSP430F261x
;             -----------------
;         /|\|              XIN|-
;          | |                 |  32.768kHz xtal
;          --|RST          XOUT|-
;            |                 |
;            |         P1.1/TA0|--> SMCLK/1000
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x26x.h"
;-------------------------------------------------------------------------------
			.text	;Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #0850h,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
OFIFGcheck  bic.b   #OFIFG,&IFG1            ; Clear OFIFG
            mov.w   #047FFh,R15             ; Wait for OFIFG to set again if
OFIFGwait   dec.w   R15                     ; not stable yet
            jnz     OFIFGwait
            bit.b   #OFIFG,&IFG1            ; Has it set again?
            jnz     OFIFGcheck              ; If so, wait some more
SetupP1     bis.b   #BIT1,&P1DIR            ; P1.0 output
            bis.b   #BIT1,&P1SEL            ; P1.0 option slect
SetupC0     mov.w   #OUTMOD_4,&TACCTL0      ; TACCR0 toggle mode
            mov.w   #250,&TACCR0            ;
SetupTA     mov.w   #TASSEL_2+MC_3,&TACTL   ; SMCLK, updown mode
                                            ;						
Mainloop    bis.w   #CPUOFF,SR              ; CPU off
            nop                             ; Required only for debugger
                                            ;
;------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"	           ; POR, ext. Reset, Watchdog
            .short  RESET
            .end
          