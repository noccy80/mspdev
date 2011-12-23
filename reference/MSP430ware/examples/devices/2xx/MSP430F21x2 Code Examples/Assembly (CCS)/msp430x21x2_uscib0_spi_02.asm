;*******************************************************************************
;   MSP430F21x2 Demo - USCI_B0, SPI Interface to TLV1549 10-Bit ADC
;
;   Description: This program demonstrate USCI_B0 in SPI mode interfaced to a
;   TLV1549 10-bit ADC. If AIN > 0.5(REF+ - REF-), P1.0 set, else reset.
;   R15 = MSB|LSB, left justified.  R14 also used and not saved.
;   ACLK = n/a, MCLK = SMCLK = DCO ~1.2MHz, BRCLK = SMCLK/2
;   //* VCC must be at least 3v for TLV1549 *//
;
;                         MSP430F21x2
;                       -----------------
;                   /|\|              XIN|-
;       TLV1549      | |                 |
;    -------------   --|RST          XOUT|-
;   |           CS|<---|P3.0             |
;   |      DATAOUT|--->|P3.2/UCB0SOMI    |
; ~>|AIN+  I/O CLK|<---|P3.3/UCB0CLK     |
;   |             |    |             P1.0|--> LED
;
;  JL Bile
;  Texas Instruments Inc.
;  May 2008
;  Built with Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x21x2.h"
;-------------------------------------------------------------------------------
RxData      .usect	".bss",128              ; Allocate 128 byte of RAM
;-------------------------------------------------------------------------------
			.text							; Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #025Fh,SP         		; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop watchdog timer
SetupP1     bis.b   #01h,&P1DIR             ; P1.0 output
SetupP3     bis.b   #0Ch,&P3SEL             ; P3.2,3 USCI_B0 option select
            bis.b   #01h,&P3DIR             ; P3.0 output direction
SetupSPI    bis.b   #UCMSB+UCMST+UCSYNC,&UCB0CTL0;3-pin, 8-bit SPI mstr, MSB 1st
            bis.b   #UCSSEL_2,&UCB0CTL1     ; SMCLK
            mov.b   #02h,&UCB0BR0           ; /2
            clr.b   &UCB0BR1                ;
            bic.b   #UCSWRST,&UCB0CTL1      ; **Initialize USCI state machine**
                                            ;
Mainloop    bic.b   #01h,&P3OUT             ; Enable TLV1549, /CS reset
            mov.b   #00h,&UCB0TXBUF         ; Dummy write to start SPI
            mov.b   #00h,&UCB0TXBUF         ;
L1          bit.b   #UCB0RXIFG,&IFG2        ; RXBUF ready?
            jnc     L1                      ; 1 = ready
            mov.b   &UCB0RXBUF,R15          ; R15 = 00|MSB
            swpb    R15                     ; R15 = MSB|00
L2          bit.b   #UCB0RXIFG,&IFG2        ; RXBUF ready?
            jnc     L2                      ; 1 = ready
            mov.b   &UCB0RXBUF,R14          ; R14 = 00|LSB
            add.w   R14,R15                 ; R15 = MSB|LSB
            bis.b   #01h,&P3OUT             ; Disable TLV1549, /CS set
            bic.b   #01h,&P1OUT             ; P1.0 = 0
            cmp.w   #07FE0h,R15             ; R15 = AIN > 0.5(REF+ - REF-)?
            jlo     Mainloop                ; Again
            bis.b   #01h,&P1OUT             ; P1.0 = 1
            jmp     Mainloop                ; Again
                                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"				; POR, ext. Reset, Watchdog
            .short	RESET 
            .end

