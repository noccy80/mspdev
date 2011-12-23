;******************************************************************************
;   MSP-FET430P140 Demo - USART1, SPI Interface to TLV1549 10-Bit ADC
;
;   Description: This program demonstrate a USART1 in SPI mode interface to a
;   TLV1549 10-bit ADC. If AIN > 0.5(REF+ - REF-), P1.0 set, else reset.
;   R15 = MSB|LSB, left justified.  R14 also used and not saved.
;   ACLK = n/a, MCLK = SMCLK = default DCO ~800k, UCLK1 = SMCLK/2
;   //* VCC must be at least 3v for TLV1549 *//
;
;                            MSP430F149
;                         -----------------
;                     /|\|              XIN|-
;         TLV1549      | |                 |
;      -------------   --|RST          XOUT|-
;     |           CS|<---|P5.0             |
;     |      DATAOUT|--->|P5.2/SOMI        |
;   ~>|AIN+  I/O CLK|<---|P5.3/UCLK0       |
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
SetupP1     bis.b   #001h,&P1DIR            ; P1.0 output
SetupP5     bis.b   #0Ch,&P5SEL             ; P5.2,3 SPI option select
            bis.b   #09h,&P5DIR             ; P5.3,0 output direction
SetupSPI    bis.b   #USPIE1,&ME2            ; Enable USART1 SPI
            bis.b   #CKPH+SSEL1+SSEL0+STC,&UTCTL1 ; SMCLK, 3-pin
            bis.b   #CHAR+SYNC+MM,&UCTL1    ; 8-bit SPI Master
            mov.b   #02h,&UBR01             ; SMCLK/2 for baud rate
            clr.b   &UBR11                  ; SMCLK/2 for baud rate
            clr.b   &UMCTL1                 ; Clear modulation
            bic.b   #SWRST,&UCTL1           ; **Initialize USART state machine**
                                            ;
Mainloop    bic.b   #01h,&P5OUT             ; Enable TLV1549, /CS reset
            mov.b   #00h,&TXBUF1            ; Dummy write to start SPI
            mov.b   #00h,&TXBUF1            ;
L1          bit.b   #URXIFG1,&IFG2          ; RXBUF ready?
            jnc     L1                      ; 1 = ready
            mov.b   &RXBUF1,R15             ; R15 = 00|MSB
            swpb    R15                     ; R15 = MSB|00
L2          bit.b   #URXIFG1,&IFG2          ; RXBUF ready?
            jnc     L2                      ; 1 = ready
            mov.b   &RXBUF1,R14             ; R14 = 00|LSB
            add.w   R14,R15                 ; R15 = MSB|LSB
            bis.b   #01h,&P5OUT             ; Disable TLV1549, /CS .set
            bic.b   #01h,&P1OUT             ; P1.0 = 0
            cmp.w   #07FE0h,R15             ; R15 = AIN > 0.5(REF+ - REF-)?
            jlo     Mainloop                ; Again
            bis.b   #01h,&P1OUT             ; P1.0 = 1
            jmp     Mainloop                ; Again
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .end

