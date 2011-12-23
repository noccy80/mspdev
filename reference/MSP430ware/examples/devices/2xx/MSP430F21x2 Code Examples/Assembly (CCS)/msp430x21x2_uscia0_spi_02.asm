;*******************************************************************************
;   MSP430F21x2 Demo - USCI_A0, SPI Interface to HC165 Shift Register
;
;   Description: This program demonstrate a USCI_A0 in SPI mode interface to a
;   an 'HC165 shift register.  Read 8-bit Data from H-A into Data.
;   ACLK = n/a, MCLK = SMCLK = default DCO ~1.2MHz, BRCLK = SMCLK/2
;
;                          MSP430F21x2
;                       -----------------
;                   /|\|              XIN|-
;                    | |                 |
;          HC165     --|RST          XOUT|-
;        ----------    |                 |
;    8  |      /LD|<---|P3.6             |
;   -\->|A-H   CLK|<---|P3.0/UCA0CLK     |
;     |-|INH    QH|--->|P3.5/UCA0SOMI    |
;     |-|SER      |    |                 |
;     v
;
;
;  JL Bile
;  Texas Instruments Inc.
;  May 2008
;  Built with Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x21x2.h"
 
Data        .equ     0200h
;-------------------------------------------------------------------------------
 			.text							; Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #025Fh,SP         		; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop watchdog timer
SetupP3     bis.b   #021h,&P3SEL            ; P3.0,5 USCI_A0 option select
            bis.b   #040h,&P3DIR            ; P3.6 output direction
SetupSPI    bis.b   #UCCKPH+UCMSB+UCMST+UCSYNC,&UCA0CTL0 ; 3-pin, 8-bit SPI mast
            bis.b   #UCSSEL_2,&UCA0CTL1     ; SMCLK
            bis.b   #02h,&UCA0BR0
            clr.b   &UCA0BR1                ;
            clr.b   &UCA0MCTL
            bic.b   #UCSWRST,&UCA0CTL1      ; **Initialize USCI state machine**
                                            ;
Mainloop    call    #RX_HC165               ; Load HC165 value into Rx buffer
            mov.b   &UCA0RXBUF,&Data        ; Move value into Data
            jmp     Mainloop                ; Repeat
                                            ;
;-------------------------------------------------------------------------------
RX_HC165
;-------------------------------------------------------------------------------
            bic.b   #040h,&P3OUT            ; Trigger low edge on HC165 /LD
            bis.b   #040h,&P3OUT            ; Return /LD to high
            bic.b   #UCA0RXIFG,&IFG2        ; Clear U1RXBUF flag
            mov.b   #00h,&UCA0TXBUF         ; Dummy write to start SPI
L1          bit.b   #UCA0RXIFG,&IFG2        ; RXBUF ready?
            jnc     L1                      ; 1 = ready
            ret                             ;
                                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"				; MSP430 RESET Vector
            .short	RESET 
            .end
