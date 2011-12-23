;******************************************************************************
;   MSP-FET430P120 Demo - USART0, SPI Interface to TLC549 8-Bit ADC
;
;   Description: This program demonstrate a USART0 in SPI mode interface to a
;   TLC549 8-bit ADC. The TLC is read 16x, with the conversion code saved in
;   in RAM 21Fh - 200h. R15 used as pointer.
;   ACLK = n/a, MCLK = SMCLK = default DCO ~ 800k, UCLK = DCO/2
;   //* VCC must be at least 3v for TLC549 *//
;
;                          MSP430F123(2)
;                       -----------------
;                   /|\|              XIN|-
;        TLC549      | |                 |
;    -------------   --|RST          XOUT|-
;   |           CS|<---|P3.0             |
;   |      DATAOUT|--->|P3.2/SOMI        |
; ~>| IN+  I/O CLK|<---|P3.3/UCLK0       |
;
;   M. Buccini / M. Raju
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430x12x2.h"
;------------------------------------------------------------------------------
            .text                           ; Program Reset
;------------------------------------------------------------------------------
RESET       mov.w   #0300h,SP               ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop watchdog timer
SetupP3     bis.b   #0Ch,&P3SEL             ; P3.2,3 SPI option select
            bis.b   #09h,&P3DIR             ; P3.3,0 output direction
SetupSPI    bis.b   #USPIE0,&ME2            ; Enable USART0 SPI
            bis.b   #CKPH+SSEL1+SSEL0+STC,&UTCTL0 ; SMCLK, 3-pin
            bis.b   #CHAR+SYNC+MM,&UCTL0    ; 8-bit SPI Master
            mov.b   #02h,&UBR00             ; SMCLK/2 for baud rate
            clr.b   &UBR10                  ; SMCLK/2 for baud rate
            clr.b   &UMCTL0                 ; no modulation
            bic.b   #SWRST,&UCTL0           ; **Initalize USART state machine**
                                            ;
Mainloop    mov.w   #0020h,R15              ;
Read_549    bic.b   #01h,&P3OUT             ; Enable TLC549
            mov.b   #00h,&TXBUF0            ; Dummy write to start SPI
L1          bit.b   #URXIFG0,&IFG2          ; RXBUF ready?
            jnc      L1                     ; 1 = ready
            bis.b   #01,&P3OUT              ; Disable TLC549
                                            ;
            mov.b   &RXBUF0,200h(R15)       ;
            dec.b   R15                     ;
            jc      Read_549                ;
            jmp     Mainloop                ; Repeat
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
             .sect   ".reset"               ; POR, ext. Reset, Watchdog, Flash
             .short  RESET                  ;
             .end

