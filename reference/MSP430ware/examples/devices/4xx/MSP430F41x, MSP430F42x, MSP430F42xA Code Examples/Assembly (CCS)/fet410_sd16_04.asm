;******************************************************************************
;   MSP-FET430P410 Demo - SD16, Single Conversion on Single Channel Polling IFG
;
;   Description: This program uses the SD16 module to perform a single
;   conversion on a single channel. The SD16 interrupt flag for CH2 is polled
;   to determine when a conversion has completed. Test by applying a voltage
;   to CH2 (A2.0+, A2.0-) and setting a breakpoint at the line indicated
;   below. Run program until it reaches the breakpoint, then use the
;   debugger's register window to view the conversion results. The conversion
;   result for CH2 is stored in R12.
;   ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
;   ;* An external watch crystal between XIN & XOUT is required for ACLK *//	
;   ;* Minimum Vcc is required for SD16 module - see datasheet        *//
;   ;* 100nF cap btw Vref and AVss is recommended when using 1.2V ref *//
;
;                 MSP430F427
;              -----------------
;          /|\|              XIN|-
;           | |                 | 32kHz
;           --|RST          XOUT|-
;             |                 |
;     Vin+ -->|A2.0+            |
;     Vin- -->|A2.0-            |
;             |                 |
;             |            VREF |---+
;             |                 |   |
;             |                 |  -+- 100nF
;             |                 |  -+-
;             |                 |   |
;             |            AVss |---+
;             |                 |
;
;   H. Grewal / S. Karthikeyan
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430x42x.h"

;-----------CPU Registers Used-------------------------------------------------
RESULTS .equ     R12
                                            ; R12 - Store conversion result
                                            ; from SD16MEM2
;           R15 - Temporary working register

;------------------------------------------------------------------------------
            .text                  ; Program Start
;------------------------------------------------------------------------------
RESET       mov     #600h,SP                ; Initialize stack pointer
StopWDT     mov     #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupFLL    bis.b   #XCAP14PF,&FLL_CTL0     ; Configure load caps
            mov     #10000,R15              ;
Xtal_Wait   dec     R15                     ; Delay for 32 kHz crystal to
            jnz     Xtal_Wait		    ; stabilize
SetupSD16   mov     #SD16REFON+SD16SSEL0,&SD16CTL ; 1.2V ref, SMCLK
            bis     #SD16SNGL,&SD16CCTL2    ; Single conversion
            mov     #03600h,R15             ; Delay needed for 1.2V ref startup
L$1         dec     R15                     ;
            jnz     L$1                     ;
Mainloop    bis     #SD16SC,&SD16CCTL2      ; Start conversion
testIFG     bit     #SD16IFG,&SD16CCTL2     ; Is conversion done?
            jz      testIFG                 ; No, test again
            mov     &SD16MEM2,RESULTS       ; Yes, save conversion result
            ;                               ; (automatically clears SD16IFG)
            jmp     Mainloop                ; set BREAKPOINT HERE
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector"
            .short  RESET                   ;
            .end