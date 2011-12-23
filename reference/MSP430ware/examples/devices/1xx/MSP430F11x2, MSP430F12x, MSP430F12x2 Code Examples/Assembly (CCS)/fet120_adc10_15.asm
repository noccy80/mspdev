;******************************************************************************
;   MSP-FET430P120 Demo - ADC10, DTC Sample A10 32x to Flash, Int Ref, DCO
;
;   Description: Use DTC to sample A10 32x, Int Reference, and transfer
;   code directly to Flash. Software writes to ADC10SC to trigger sample
;   burst. Timing for Flash programming is important and must meet the device
;   f(FTG) datasheet specification ~ (257kHz)/35 - (476kHz)/35
;   Assume default DCO = SMCLK ~ 800kHz.
;   As programmed;
;   Each ADC10 sample & convert = (SMCLK)/(64+13) = SMCLK/77 = 96us
;   Flash write per word = (SMCLK/2)/35 = SMCLK/70 = 88us
;   Enough time is provided between ADC10 conversions for each word moved by
;   the DTC to Flash to program. DTC transfers ADC10 code to Flash 1080h-10BEh.
;   In Mainloop, the MSP430 waits in LPM0 during conversion and programming,
;   ADC10_ISR(DTC) will force exit from any LPMx in Mainloop on reti.
;   //* MSP430F12x2 or MSP430F11x2 Device Required *//
;
;                MSP430F1232
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |A10              |
;
;   M. Buccini / M. Raju
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430x12x2.h"
;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #0300h,SP               ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupADC10  mov.w   #INCH_10+ADC10SSEL_3+CONSEQ_2,&ADC10CTL1 ; SMCLK
            mov.w   #SREF_1+ADC10SHT_3+MSC+REFON+ADC10ON+ADC10IE,&ADC10CTL0 ;
            mov.w   #30,&TACCR0             ; Delay to allow Ref to settle
            bis.w   #CCIE,&TACCTL0          ; Compare-mode interrupt.
            mov.w   #TACLR+MC_1+TASSEL_2,&TACTL; up mode, SMCLK
            bis.w   #LPM0+GIE,SR            ; Enter LPM0,enable interrupts
            bic.w   #CCIE,&TACCTL0          ; Disable timer interrupt
            dint                            ; Disable Interrupts
            mov.b   #020h,&ADC10DTC1        ; 32 conversions
            mov.w   #FWKEY+FSSEL_2+FN0,&FCTL2  ; SMCLK/2
                                            ;
Mainloop    mov.w   #FWKEY,&FCTL3           ; Lock = 0
            mov.w   #FWKEY+ERASE,&FCTL1     ; Erase bit = 1
            mov.w   #0,&01080h              ; Dummy write to SegA to erase
            bic.w   #ENC,&ADC10CTL0         ;
busy_test   bit     #BUSY,&ADC10CTL1        ; ADC10 core inactive?
            jnz     busy_test               ;
            mov.w   #01080h,&ADC10SA        ; Data buffer start
            mov.w   #FWKEY+WRT,&FCTL1       ; Write bit = 1
            bis.w   #ENC+ADC10SC,&ADC10CTL0 ; Start sampling
            bis.w   #CPUOFF+GIE,SR          ; LPM0, ADC10_ISR will force exit
            mov.w   #FWKEY+LOCK,&FCTL3      ; Lock = 1
            jmp     Mainloop                ; << SET BREAKPOINT HERE
                                            ;
;------------------------------------------------------------------------------
TA0_ISR;    ISR for CCR0
;------------------------------------------------------------------------------
            clr     &TACTL                  ; clear Timer_A control registers
            bic     #LPM0,0(SP)             ; Exit LPMx, interrupts enabled
            reti                            ;
;------------------------------------------------------------------------------
;------------------------------------------------------------------------------
ADC10_ISR;
;------------------------------------------------------------------------------
L2          mov.w   #GIE,0(SP)              ; Exit any LPMx on reti
            reti                            ;		
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int05"                ; ADC10 Vector
            .short  ADC10_ISR               ;
            .sect   ".int09"                ; Timer_A0 Vector
            .short  TA0_ISR                 ;
            .end
