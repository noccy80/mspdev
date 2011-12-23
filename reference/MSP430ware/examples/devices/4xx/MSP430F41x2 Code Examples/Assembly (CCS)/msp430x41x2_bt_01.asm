;******************************************************************************
;  MSP430F41x2 Demo - Basic Timer, Toggle P5.1 Inside ISR, DCO SMCLK
;
;  Description: Toggles P5.1 by xor'ing P5.1 inside of a basic timer ISR.
;  SMCLK provides the basic timer clock source. When using default FLL+
;  register settings and an external 32kHz watch crystal, LED toggles
;  every ~244us.
;  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
;  //* An external watch crystal between XIN & XOUT is required for ACLK *//
;
;                MSP430F41x2
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
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
Init_Sys    mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupBT     mov.b   #BTSSEL+BT_fCLK2_DIV256,&BTCTL   ; SMCLK/256
            bis.b   #BTIE,&IE2              ; Enable Basic Timer interrupt
SetupP5     bis.b   #002h,&P5DIR            ; P5.1 output
                                            ;						
Mainloop    bis.w   #CPUOFF+GIE,SR          ; Enter LPM0, enable interrupts
            nop                             ; Required only for debugger
                                            ;
;------------------------------------------------------------------------------
BT_ISR;     Toggle P5.1
;------------------------------------------------------------------------------
            xor.b   #002h,&P5OUT            ; Toggle P5.1
            reti                            ;		
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect	".reset"            ; RESET Vector
            .short  RESET               ;
            .sect   ".int00"	        ; MSP430 Basic Timer Interrupt Vector
            .short  BT_ISR         
            .end
