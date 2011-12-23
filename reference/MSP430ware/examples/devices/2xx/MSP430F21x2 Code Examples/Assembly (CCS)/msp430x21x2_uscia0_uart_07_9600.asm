;*******************************************************************************
;   MSP430F21x2 Demo - USCI_A0, Ultra-Low Pwr UART 9600 RX/TX, 32kHz ACLK
;
;   Description: This program demonstrates a full-duplex 9600-baud UART using
;   USCI_A0 and a 32kHz crystal.  The program will wait in LPM3, and receive
;   a string1 into RAM starting at 200h, and echo back the complete string.
;   ACLK = BRCLK = LFXT1 = 32768, MCLK = SMCLK = DCO ~1.2MHz
;   Baud rate divider with 32768Hz XTAL @9600 = 32768Hz/9600 = 3.41
;   //* An external watch crystal is required on XIN XOUT for ACLK *//
;
;                MSP430F21x2
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |     P3.4/UCA0TXD|------------>
;            |                 | 9600 - 8N1
;            |     P3.5/UCA0RXD|<------------
;
;
;  JL Bile
;  Texas Instruments Inc.
;  May 2008
;  Built with Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x21x2.h"

;   CPU registers used
PointerTX  .set	R4
PointerRX  .set	R5
String1    .equ	0200h

;-------------------------------------------------------------------------------
 			.text							; Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #025Fh,SP         		; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP1     mov.b   #0FFh,&P1DIR            ; All P1.x outputs
            clr.b   &P1OUT                  ; All P1.x reset
SetupP2     mov.b   #0FFh,&P2DIR            ; All P2.x outputs
            clr.b   &P2OUT                  ; All P2.x reset
SetupP3     bis.b   #030h,&P3SEL            ; P3.4,5 = USCI_A0 TXD/RXD
            mov.b   #0FFh,&P3DIR            ; All P3.x outputs
            clr.b   &P3OUT                  ; All P3.x reset
SetupUSCI0  bis.b   #UCSSEL_1,&UCA0CTL1     ; CLK = ACLK
            mov.b   #03h,&UCA0BR0           ; 32kHz/9600 = 3.41
            mov.b   #00h,&UCA0BR1           ;
            mov.b   #UCBRS1+UCBRS0,&UCA0MCTL; Modulation UCBRSx = 3
            bic.b   #UCSWRST,&UCA0CTL1      ; **Initialize USCI state machine**
            bis.b   #UCA0RXIE,&IE2          ; Enable USCI_A0 RX interrupt
            clr.w   PointerRX               ;
                                            ;
Mainloop    bis.w   #LPM3+GIE,SR            ; Enter LPM3 w/ int until Byte RXed
            nop                             ; Required only for debugger
                                            ;
;-------------------------------------------------------------------------------
USCI0TX_ISR;
;-------------------------------------------------------------------------------
            mov.b   @PointerTX+,&UCA0TXBUF  ; TX next character
            cmp.w   #String1+8,PointerTX    ; TX over?
            jeq     Done                    ;
            reti                            ;
Done        bic.b   #UCA0TXIE,&IE2          ; Disable USCI_A0 TX interrupt
            reti                            ;
                                            ;
;-------------------------------------------------------------------------------
USCI0RX_ISR;
;-------------------------------------------------------------------------------
            mov.b   &UCA0RXBUF,String1(PointerRX) ; Store RX data
            inc.w   PointerRX               ;
            cmp.b   #8,PointerRX            ;
            jne     UART_Done               ;
            bis.b   #UCA0RXIE+UCA0TXIE,&IE2 ; Enable USCI_A0 TX interrupt
            clr.w   PointerRX               ;
            mov.w   #String1,PointerTX      ;
            mov.b   @PointerTX+,&UCA0TXBUF  ;
UART_Done   reti                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect     ".int07" 				;USCIAB0RX_VECTOR
            .short    USCI0RX_ISR
            .sect     ".int06"				;USCIAB0TX_VECTOR
            .short    USCI0TX_ISR
            .sect	  ".reset"				; MSP430 RESET Vector
            .short	  RESET 
            .end

