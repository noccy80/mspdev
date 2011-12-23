;******************************************************************************
;   MSP-FET430P410 Demo - SD16, Single Conversion on Single Channel Using ISR
;
;   Description: This program uses the SD16 module to perform a single
;   conversion on a single channel. A SD16 interrupt occurs when a
;   conversion has completed. Test by applying a voltage to CH2
;   (A2.0+, A2.0-) and setting a breakpoint at the line indicated below.
;   Run program until it reaches the breakpoint, then use the debugger's
;   register window to view the conversion results. The conversion result
;   for CH2 is stored in R12.
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
StopWDT     mov     #WDTPW+WDTHOLD,&WDTCTL  ; Stop watchdog
SetupFLL    bis.b   #XCAP14PF,&FLL_CTL0     ; Configure load caps
            mov     #10000,R15              ;
Xtal_Wait   dec     R15                     ; Delay for 32 kHz crystal to
            jnz     Xtal_Wait		        ; stabilize
SetupSD16   mov     #SD16REFON+SD16SSEL0,&SD16CTL ; 1.2V ref, SMCLK
            bis     #SD16SNGL+SD16IE,&SD16CCTL2 ; Single conv, enable interrupt
            bis.b   #SD16INTDLY0,&SD16INCTL2 ; Third sample generates interrupt
            mov     #03600h,R15             ; Delay needed for 1.2V ref startup
L$1         dec     R15                     ;
            jnz     L$1                     ;
            eint                            ; Enable general interrupts
Mainloop    bis     #SD16SC,&SD16CCTL2      ; Start conversion
            bis     #CPUOFF,SR              ; Enter LPM0 (disable CPU), wait for
                                            ; conversion to complete
            nop                             ; Required for debug only
            jmp     Mainloop                ; set BREAKPOINT HERE
                                            ;
;------------------------------------------------------------------------------
SD16_ISR    ; SD16 Interrupt Service Routine
;------------------------------------------------------------------------------
            add.w   &SD16IV,PC              ; Add offset to PC
            reti                            ; Vector 0: No interrupt
            jmp     SD_OV                   ; Vector 2: Overflow
            jmp     SD_CH0                  ; Vector 4: CH0 IFG
            jmp     SD_CH1                  ; Vector 6: CH1 IFG
                                            ; Vector 8: CH2 IFG
                                            ;
;-----------SD16 Channel 2 Interrupt Handler-----------------------------------
SD_CH2      mov     &SD16MEM2,RESULTS       ; Save CH2 conversion result
            bic     #CPUOFF,0(SP)           ; Return active
SD_CH2_END  reti                            ; Return from interrupt
                                            ;
;-----------SD16 Memory Overflow Interrupt Handler-----------------------------
SD_OV       reti                            ; Return from interrupt
                                            ;
;-----------SD16 Channel 0 Interrupt Handler-----------------------------------
SD_CH0      reti                            ; Return from interrupt
                                            ;
;-----------SD16 Channel 1 Interrupt Handler-----------------------------------
SD_CH1      reti                            ; Return from interrupt
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; RESET Vector
            .short  RESET                   ;
            .sect   ".int12"                ; SD16 Vector
            .short  SD16_ISR                ;
            .end



