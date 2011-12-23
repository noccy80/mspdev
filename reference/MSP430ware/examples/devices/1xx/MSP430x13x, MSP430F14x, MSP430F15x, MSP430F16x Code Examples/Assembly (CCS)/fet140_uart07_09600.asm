;******************************************************************************
;   MSP-FET430P140 Demo - USART0, Ultra-Low Pwr UART 9600 RX/TX, 32kHz ACLK
;
;   Description: This program demonstrates a full-duplex 9600-baud UART using
;   USART0 and a 32kHz crystal. The program waits in LPM3, receives
;   8 characters into RAM starting at location 0x200, and then echos back the 
;   characters.
;   ACLK = LFXT1 = UCLK0, MCLK = SMCLK = default DCO ~ 800KHz
;   Baud rate divider with 32768hz XTAL @9600 = 32768Hz/9600 = 3.41 (0003h 4Ah )
;   //* An external watch crystal is required on XIN XOUT for ACLK *//	
;
;                MSP430F149
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |             P3.4|----------->
;            |                 | 9600 - 8N1
;            |             P3.5|<-----------
;
;   CPU registers used
PointerTX  .equ     R4
PointerRX  .equ     R5
;
String1     .equ    0200h
;
;   M. Buccini / G. Morton
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430x14x.h"
;-----------------------------------------------------------------------------
            .text                           ; Program Reset
;-----------------------------------------------------------------------------
RESET       mov.w   #0A00h,SP               ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP3     bis.b   #030h,&P3SEL            ; P3.4,5 = USART0 TXD/RXD
SetupUART0  bis.b   #UTXE0+URXE0,&ME1       ; Enable USART0 TXD/RXD
            bis.b   #CHAR,&UCTL0            ; 8-bit characters
            mov.b   #SSEL0,&UTCTL0          ; UCLK = ACLK
            mov.b   #003h,&UBR00            ; 32k/9600 - 3.41
            mov.b   #000h,&UBR10            ;
            mov.b   #04Ah,&UMCTL0           ; Modulation
            bic.b   #SWRST,&UCTL0           ; **Initialize USART state machine**
            bis.b   #URXIE0+UTXIE0,&IE1     ; Enable USART0 RX/TX interrupt
            bic.b   #UTXIFG0,&IFG1          ; Clear inital flag on POR
            clr.w   PointerRX               ;
                                            ;
Mainloop    bis.w   #LPM3+GIE,SR            ; Enter LPM3 w/ int until Byte RXed
            nop                             ; Required only for debugger
                                            ;
;------------------------------------------------------------------------------
USART0TX_ISR;
;------------------------------------------------------------------------------
            cmp.w   #String1+8,PointerTX    ; Complete string TX'ed?
            jeq     Done                    ;
            mov.b   @PointerTX+,&TXBUF0     ;
Done        reti                            ;
                                            ;
;-----------------------------------------------------------------------------
USART0RX_ISR;
;-----------------------------------------------------------------------------
            mov.b   &RXBUF0,String1(PointerRX) ; Store RX data
            inc.w   PointerRX               ;
            cmp.b   #8,PointerRX            ;
            jne     USART_Done              ;
            clr.w   PointerRX               ;
            mov.w   #String1,PointerTX      ;
            mov.b   @PointerTX+,&TXBUF0     ;
USART_Done  reti                            ;		
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ;
            .short  RESET                   ; POR, ext. Reset, Watchdog
            .sect   ".int09"                ;
            .short  USART0RX_ISR            ; USART0 receive
            .sect   ".int08"                ;
            .short  USART0TX_ISR            ; USART0 transmit
            .end