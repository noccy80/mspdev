;******************************************************************************
;   MSP-FET430P140 Demo - USART0, SPI Interface to TLV5616 DAC
;
;   Description: Demonstrate USART0 in SPI mode interface to TLV5616 DAC.
;   USART0 is used to transmit data to DAC, Timer_A CCR1/CCRO used to generate
;   frame sync pulse, DAC is updated inside CCR0 ISR. R5 used as pointer
;   into Sin_tab.
;   ACLK = MCLK = LFXT1 = HF XTAL = 3.58MHz, UCLK0 = LFXT1/2
;   //** SWRST** please see MSP430x1xx Users Guide for description **//
;   //* USART0 control bits are in different SFR's from other MSP430's *//
;   //* 3.58Mhz XTAL CRYSTAL REQUIRED - NOT INSTALLED ON FET *//
;
;                MSP430F149
;             -----------------
;         /|\|              XIN|-
;          | |                 | 3.58MHz   TLV5616
;          --|RST          XOUT|-       -------------
;            |             P2.3|------>|FS        OUT|--> ~ 1kHz sine wave
;            |       SIMO0/P3.1|------>|DIN          |
;            |       UCLK0/P3.3|------>|SCLK       CS|-|
;            |                 |       |             | v
;
;
;   M. Buccini / G. Morton
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430x14x.h"
;------------------------------------------------------------------------------
            .text                           ; Progam Start
;------------------------------------------------------------------------------
RESET       mov.w   #0A00h,SP               ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop watchdog timer
SetupP3     bis.b   #0Ah,&P3SEL             ; P3.1,3 SPI option select
            bis.b   #0Ah,&P3DIR             ; P3.1,3 output direction
SetupP2     bis.b   #08h,&P2SEL             ; P2.3 CCR1 option select
            bis.b   #08h,&P2DIR             ; P2.3 output
SetupBC     bis.b   #XTS,&BCSCTL1           ; ACLK = LFXT1 = HF XTAL
SetupOsc    bic.b   #OFIFG,&IFG1            ; Clear OSC fault flag
            mov.w   #0FFh,R15               ; R15 = Delay
SetupOsc1   dec.w   R15                     ; Additional delay to ensure start
            jnz     SetupOsc1               ;
            bit.b   #OFIFG,&IFG1            ; OSC fault flag set?
            jnz     SetupOsc                ; OSC Fault, clear flag again
            bis.b   #SELM1+SELM0,&BCSCTL2   ; MCLK = LFXT1
SetupSPI    bis.b   #USPIE0,&ME1            ; Enable USART0 SPI
            bis.b   #CHAR+SYNC+MM,&UCTL0    ; 8-bit SPI Master **SWRST**
            mov.b   #CKPH+CKPL+SSEL0+STC,&UTCTL0 ; Inv. delayed, ACLK,3-pin
            mov.b   #02h,&UBR00             ; ACLK/2 for baud rate
            clr.b   &UBR10                  ; ACLK/2 for baud rate
            clr.b   &UMCTL0                 ; Clear modulation
            bic.b   #SWRST,&UCTL0           ; **Initialize USART state machine**
            clr.w   R5                      ; Clear pointer
SetupC1     mov.w   #OUTMOD_7,&CCTL1        ; CCR1 reset/set
            mov.w   #01,&CCR1               ; CCR1 PWM Duty Cycle	
SetupC0     mov.w   #CCIE,&CCTL0            ; CCR0 interrupt enabled
            mov.w   #111-1,&CCR0            ; Clock period of CCR0
SetupTA     mov.w   #TASSEL_1+MC_1,&TACTL   ; ACLK, upmode
                                            ;
Mainloop    bis.b   #CPUOFF+GIE,SR          ; Enter LPM0, enable interrupts
            nop                             ; Needed only for debugger
                                            ;
;------------------------------------------------------------------------------
TA0_ISR;    Timer_A CCR0 ISR
;           SPI buffer TXBUF0 needs to be ready prior to writing, with
;           UCLK0 = MCLK/2 it is safe to write back to back as first word
;           transfers in two clocks, faster than.b mov operation.
;------------------------------------------------------------------------------
            mov.b   Sin_tab+1(R5),&TXBUF0   ; High byte to SPI TXBUF
            mov.b   Sin_tab(R5),&TXBUF0     ; Low byte to SPI TXBUF
            incd.w  R5                      ; Inc pointer
            and.w   #03Eh,R5                ; R5 = 0 - 62 only (32 words)
            reti                            ; Return from interupt
                                            ;
;------------------------------------------------------------------------------
; 12-bit Sine Lookup table with 32 steps
;------------------------------------------------------------------------------
Sin_tab     .short   2048
            .short   2447
            .short   2831
            .short   3185
            .short   3495
            .short   3750
            .short   3939
            .short   4056
            .short   4095
            .short   4056
            .short   3939
            .short   3750
            .short   3495
            .short   3185
            .short   2831
            .short   2447
            .short   2048
            .short   1648
            .short   1264
            .short   910
            .short   600
            .short   345
            .short   156
            .short   39
            .short   0
            .short   39
            .short   156
            .short   345
            .short   600
            .short   910
            .short   1264
            .short   1648
;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".int06"                ; Timer_A3 CCIFG0
            .short  TA0_ISR                 ;
            .sect   ".reset"                ; POR, ext. Reset, Watchdog, Flash
            .short  RESET                   ;
            .end

