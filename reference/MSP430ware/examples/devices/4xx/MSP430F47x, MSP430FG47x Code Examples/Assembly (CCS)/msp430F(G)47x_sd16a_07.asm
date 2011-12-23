;*****************************************************************************
;     MSP430FG47x Demo - SD16_A, Using the Integrated Battery Sensor
;
;   Description: This example shows how to use the SD16_A module's integrated
;   Battery sensor (connected to input channel 5) to measure VCC.
;   Run program until it reaches the breakpoint, then use the debugger's
;   register window to view the conversion results. The conversion result
;   for CH5 is stored in R12.  LED lights if batter is low
;   ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
;   //* An external watch crystal between XIN & XOUT is required for ACLK *//	
;   //* Minimum Vcc is required for SD16_A module - see datasheet        *//
;   //* 100nF cap btw Vref and AVss is recommended when using 1.2V ref *//
;
;                 MSP430FG47x
;              -----------------
;          /|\|              XIN|-
;           | |                 | 32kHz
;           --|RST          XOUT|-
;             |                 |
;             |A5+              |
;             |A5-              |
;             |                 |
;             |            VREF |---+
;             |                 |   |
;             |                 |  -+- 100nF
;             |                 |  -+-
;             |                 |   |
;             |            AVss |---+
;             |                 |
;
;   P.Thanigai
;   Texas Instruments Inc.
;   September 2008
;   Built with Code Composer Essentials Version: 3.0
;******************************************************************************
 .cdecls C,LIST, "msp430xG47x.h" 

;-----------CPU Registers Used-------------------------------------------------
RESULTS    .set   R12
LOW_BAT    .equ   0xB999
                                            ; R12 - Store conversion result
                                            ; from SD16MEM2
;           R15 - Temporary working register

;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #0A00h,SP               ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop watchdog
SetupFLL    bis.b   #XCAP14PF,&FLL_CTL0     ; Configure load caps
            mov.w   #10000,R15              ;
Xtal_Wait   dec.w   R15                     ; Delay for 32 kHz crystal to
            jnz     Xtal_Wait		        ; stabilize
            bis.b   #0x40, &P4DIR
SetupSD16   mov.w   #SD16REFON+SD16SSEL0+SD16DIV_3,&SD16CTL ; 1.2V ref, SMCLK/8
            bis.w   #SD16SNGL+SD16IE,&SD16CCTL0 ; Single conv, enable interrupt
            bis.b   #SD16INCH_5,&SD16INCTL0 ; 4th sample generates interrupt
            mov.w   #03600h,R15             ; Delay needed for 1.2V ref startup
L$1         dec.w   R15                     ;
            jnz     L$1                     ;

LED_OFF     bic.b   #0x40,  &P4OUT
Mainloop    bis.w   #SD16SC,&SD16CCTL0      ; Start conversion
            bis.w   #CPUOFF+GIE,SR          ; Enter LPM0 (disable CPU), wait for
                                            ; conversion to complete
            nop                             ; Required for debug only
            cmp.w   #LOW_BAT, RESULTS
            jge     LED_OFF
            bis.b   #0x40, &P4OUT
            jmp     Mainloop                ;
                                            ;
;------------------------------------------------------------------------------
SD16A_ISR    ; SD16_A Interrupt Service Routine
;------------------------------------------------------------------------------
            add.w   &SD16IV,PC              ; Add offset to PC
            reti                            ; Vector 0: No interrupt
            jmp     SD_OV                   ; Vector 2: Overflow
            jmp     SD_CH0                  ; Vector 4: IFG
                                            ;
;-----------SD16_A Interrupt Handler-------------------------------------------
SD_CH0      mov.w   &SD16MEM0,RESULTS       ; Save CH5 conversion result
            bic.w   #CPUOFF,0(SP)           ; Return active
SD_CH0_END  reti                            ; Return from interrupt
                                            ;
;-----------SD16_A Memory Overflow Interrupt Handler---------------------------
SD_OV       reti                            ; Return from interrupt
                                            ;

;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;  
            .sect   ".int07"            ; SD16 Vector
            .short  SD16A_ISR               ;            
            .end

