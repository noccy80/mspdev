;******************************************************************************
;   MSP430F41x2 Demo - USCI_A0, Ultra-Low Pwr UART 9600 String, 32kHz ACLK
;
;   Description: This program demonstrates a full-duplex 9600-baud UART using
;   USCI_A0 and a 32kHz crystal.  The program will wait in LPM3, and will
;   respond to a received 'u' character using 8N1 protocol. The response will
;   be the string 'Hello World'.
;   ACLK = BRCLK = LFXT1 = 32768Hz, MCLK = SMCLK = DCO ~1.045Mhz
;   Baud rate divider with 32768Hz XTAL @9600 = 32768Hz/9600 = 3.41
;   //* An external watch crystal is required on XIN XOUT for ACLK *//
;
;                MSP430F41x2
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |     P6.5/UCA0RXD|------------>
;            |                 | 9600 - 8N1
;            |     P6.6/UCA0TXD|<------------
;
;  P. Thanigai
;  Texas Instruments Inc.
;  January 2009
;  Built with CCE Version: 3.1
;******************************************************************************
 .cdecls C,LIST, "msp430x41x2.h" 
 
            .global _main
;-------------------------------------------------------------------------------
;   CPU registers used
Pointer 	.equ	R4
;-------------------------------------------------------------------------------
LF          .equ    0ah                     ; ASCII Line Feed
CR          .equ    0dh                     ; ASCII Carriage Return            
;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
_main
RESET       mov.w   #0400h,SP               ; Initialize stack pointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupFLL    bis.b   #XCAP14PF,&FLL_CTL0     ; Configure load caps

OFIFGcheck  bic.b   #OFIFG,&IFG1            ; Clear OFIFG
            mov.w   #047FFh,R15             ; Wait for OFIFG to set again if
OFIFGwait   dec.w   R15                     ; not stable yet
            jnz     OFIFGwait
            bit.b   #OFIFG,&IFG1            ; Has it set again?
            jnz     OFIFGcheck              ; If so, wait some more

SetupP6     bis.b   #BIT5+BIT6,&P6SEL       ; P6.5,6 USCI option select
SetupUART   bis.b   #UCSSEL_1,&UCA0CTL1     ; CLK = ACLK
            mov.b   #03h,&UCA0BR0           ; 32k/9600 - 3.41
            mov.b   #00h,&UCA0BR1           ;
            mov.b   #06h,&UCA0MCTL          ; Modulation
            bic.b   #UCSWRST,&UCA0CTL1      ; **Initialize USCI state machine**
            bis.b   #UCA0RXIE,&IE2          ; Enable USCI_A0 RX interrupt
                                            ;
Mainloop    bis.b   #LPM3+GIE,SR            ; Enter LPM3, interrupts enabled
            nop                             ; Required for debugger
                                            ;
;-------------------------------------------------------------------------------
USCIA0TX_ISR;
;-------------------------------------------------------------------------------
            cmp.w   #String1+13,Pointer     ;
            jeq     Done                    ;
            mov.b   @Pointer+,&UCA0TXBUF    ;
            reti                            ;
Done        bic.b   #UCA0TXIE,&IE2          ; Disable USCI_A0 TX interrupt
            reti                            ;
;-------------------------------------------------------------------------------
USCIA0RX_ISR;
;-------------------------------------------------------------------------------
            cmp.b   #'u',&UCA0RXBUF         ;
            jne     UART_Done               ;
            bis.b   #UCA0TXIE,&IE2          ; Enable USCI_A0 TX interrupt
            mov.w   #String1,Pointer        ;
            mov.b   @Pointer+,&UCA0TXBUF    ;
UART_Done   reti                            ;
                                            ;
String1     .byte      "Hello World",CR,LF
;------------------------------------------------------------------------------
;			Interrupt Vectors
;------------------------------------------------------------------------------
            .sect    ".int09"       		;
            .short   USCIA0RX_ISR           ; USCI receive
            .sect    ".int08"       		;
            .short   USCIA0TX_ISR           ; USCI receive
            .sect    ".reset"            	; POR, ext. Reset, Watchdog
            .short   RESET                  ;
            .end
