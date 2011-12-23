;******************************************************************************
;   MSP-FET430P120 Demo - USART0, SPI Interface to TLV1549 10-Bit ADC
;
;   Description: This program demonstrate a USART0 in SPI mode interface to a
;   TLV1549 10-bit ADC. If AIN > 0.5(REF+ - REF-), P1.0 set, else reset.
;   R15 = MSB|LSB, left justified.  R14 also used and not saved.
;   ACLK = n/a, MCLK = SMCLK = default DCO ~ 800k, UCLK = DCO/2
;   //* VCC must be at least 3V for TLV1549 *//
;
;                          MSP430F123(2)
;                       -----------------
;                   /|\|              XIN|-
;       TLV1549      | |                 |
;    -------------   --|RST          XOUT|-
;   |           CS|<---|P3.0             |
;   |      DATAOUT|--->|P3.2/SOMI    P1.0|--> LED
; ~>|AIN+  I/O CLK|<---|P3.3/UCLK0       |
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
SetupP1     bis.b   #001h,&P1DIR            ; P1.0 output
SetupSPI    bis.b   #USPIE0,&ME2            ; Enable USART0 SPI
            bis.b   #CKPH+SSEL1+SSEL0+STC,&UTCTL0 ; SMCLK, 3-pin
            bis.b   #CHAR+SYNC+MM,&UCTL0    ; 8-bit SPI Master
            mov.b   #02h,&UBR00             ; SMCLK/2 for baud rate
            clr.b   &UBR10                  ; SMCLK/2 for baud rate
            clr.b   &UMCTL0                 ; no modulation
            bic.b   #SWRST,&UCTL0           ; **Initalize USART state machine**
                                            ;
Mainloop    bic.b   #01h,&P3OUT             ; Enable TLV1549, /CS reset
            mov.b   #00h,&TXBUF0            ; Dummy write to start SPI
            mov.b   #00h,&TXBUF0            ;
L1          bit.b   #URXIFG0,&IFG2          ; RXBUF ready?
            jnc     L1                      ; 1 = ready
            mov.b   &RXBUF0,R15             ; R15 = 00|MSB
            swpb    R15                     ; R15 = MSB|00
L2          bit.b   #URXIFG0,&IFG2          ; RXBUF ready?
            jnc     L2                      ; 1 = ready
            mov.b   &RXBUF0,R14             ; R14 = 00|LSB
            add.w   R14,R15                 ; R15 = MSB|LSB
            bis.b   #01h,&P3OUT             ; Disable TLV1549, /CS .set
            bic.b   #01h,&P1OUT             ; P1.0 = 0
            cmp.w   #07FE0h,R15             ; R15 = AIN > 0.5(REF+ - REF-)?
            jlo     Mainloop                ; Again
            bis.b   #01h,&P1OUT             ; P1.0 = 1
            jmp     Mainloop                ; Again
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
             .sect   ".reset"               ; POR, ext. Reset, Watchdog, Flash
             .short  RESET                  ;
             .end

