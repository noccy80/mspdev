;*******************************************************************************
;   MSP430F21x2 Demo - USCI_A0, SPI Interface to HC164 Shift Register
;
;   Description: This program demonstrates USCI_A0 in SPI mode, interfaced to
;   a 'HC164 shift register, transferring the value contained in Data.
;   The value is incremented in the mainloop, effectively incrementing
;   HC164 QA - QH.
;   ACLK = n/a, MCLK = SMCLK = default DCO ~1.2MHz, BRCLK = SMCLK/2
;
;                MSP430F21x2
;             -----------------
;         /|\|              XIN|-
;          | |                 |        ^      HC164
;          --|RST          XOUT|-       |  -------------
;            |                 |        |-|/CLR,B       |  8
;            |    UCA0SIMO/P3.4|--------->|A          Qx|--\->
;            |     UCA0CLK/P3.0|--------->|CLK          |
;            |                 |          |             |
;
;
;  JL Bile
;  Texas Instruments Inc.
;  May 2008
;  Built with Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x21x2.h"
;-------------------------------------------------------------------------------
Data        .equ     0200h
;-------------------------------------------------------------------------------
 			.text							; Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #025Fh,SP         		; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop watchdog timer
SetupP3     bis.b   #11h,&P3SEL             ; P3.0,4 USCI_A0 option select
SetupSPI    bis.b   #UCCKPH+UCMSB+UCMST+UCSYNC,&UCA0CTL0 ; 3-pin, 8-bit SPI mast
            bis.b   #UCSSEL_2,&UCA0CTL1     ; SMCLK
            bis.b   #02h,&UCA0BR0
            clr.b   &UCA0BR1                ;
            clr.b   &UCA0MCTL
            bic.b   #UCSWRST,&UCA0CTL1      ; **Initialize USCI state machine**
            mov.b   #0FFh,&Data             ; Load inital data
                                            ;
Mainloop    inc.b   &Data                   ; Increment Data value
            call    #TX_HC164               ; Data --> HC164
            call    #Delay                  ; Wait
            jmp     Mainloop                ; Repeat
                                            ;
;-------------------------------------------------------------------------------
TX_HC164;   SPI Data  --> HC164
;-------------------------------------------------------------------------------
TX0         bit.b   #UCA0TXIFG,&IFG2        ; USCI_A0 TX buffer ready?
            jz      TX0                     ; Jump --> TX buffer not ready
            mov.b   &Data,&UCA0TXBUF        ; Byte to SPI TXBUF
            ret                             ; Return from subroutine
                                            ;
;-------------------------------------------------------------------------------
Delay;      Software delay
;-------------------------------------------------------------------------------
            push.w  #0FFFFh                 ; Delay to TOS
L1          dec.w   0(SP)                   ; Decrement TOS
            jnz     L1                      ; Delay over?
            incd.w  SP                      ; Clean TOS
            ret                             ;
                                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"				; MSP430 RESET Vector
            .short	RESET 
            .end
