;******************************************************************************
;   MSP430F23x0 Demo - USCI_B0, SPI Interface to TLC549 8-Bit ADC
;
;   Description: This program demonstrate USCI_B0 in SPI mode interfaced to a
;   TLC549 8-bit ADC. If AIN > 0.5(REF+ - REF-), P1.0 set, else reset.
;   R15 = 8-bit ADC code.
;   ACLK = n/a, MCLK = SMCLK = DCO ~1.2MHz, BRCLK = SMCLK/2
;   //* VCC must be at least 3v for TLC549 *//
;
;                         MSP430F23x0
;                       -----------------
;                   /|\|              XIN|-
;        TLC549      | |                 |
;    -------------   --|RST          XOUT|-
;   |           CS|<---|P3.0             |
;   |      DATAOUT|--->|P3.2/UCB0SOMI    |
; ~>| IN+  I/O CLK|<---|P3.3/UCB0CLK     |
;   |             |    |             P1.0|--> LED
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x23x0.h"
;-------------------------------------------------------------------------------
			.text							; Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #450h,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop watchdog timer
SetupP1     bis.b   #01h,&P1DIR             ; P1.0 output
SetupP3     bis.b   #0Ch,&P3SEL             ; P3.3,2 USCI_B0 option select
            bis.b   #01h,&P3DIR             ; P3.0 output direction
SetupSPI    bis.b   #UCMSB+UCMST+UCSYNC,&UCB0CTL0;3-pin, 8-bit SPI mstr, MSB 1st
            bis.b   #UCSSEL_2,&UCB0CTL1     ; SMCLK
            mov.b   #02h,&UCB0BR0           ; /2
            clr.b   &UCB0BR1                ;
            bic.b   #UCSWRST,&UCB0CTL1      ; **Initialize USCI state machine**
                                            ;
Mainloop    bic.b   #01h,&P3OUT             ; Enable TLC549, /CS reset
            mov.b   #00h,&UCB0TXBUF         ; Dummy write to start SPI
L1          bit.b   #UCB0RXIFG,&IFG2        ; RXBUF ready?
            jnc     L1                      ; 1 = ready
            mov.b   &UCB0RXBUF,R15          ; R15 = 00|DATA
            bis.b   #01h,&P3OUT             ; Disable TLC549, /CS set
            bic.b   #01h,&P1OUT             ; P1.0 = 0
            cmp.b   #07Fh,R15               ; R15 = AIN > 0.5(REF+ - REF-)?
            jlo     Mainloop                ; Again
            bis.b   #01h,&P1OUT             ; P1.0 = 1
            jmp     Mainloop                ; Again
                                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"            ; RESET Vector
            .short  RESET                   ;
            .end
