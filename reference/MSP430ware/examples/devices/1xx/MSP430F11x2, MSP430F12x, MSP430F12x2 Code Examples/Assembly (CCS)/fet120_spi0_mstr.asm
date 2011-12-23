;******************************************************************************
;   MSP-FET430P120 Demo - USART0, SPI 3-Wire Master
;
;   Description: SPI master talks to SPI slave using 3-wire mode. Incrementing
;   data is sent by the master starting at 0x00. Received data is expected to
;   decrement starting at 0xFF. USART0 RX ISR is used to handle communication
;   with the CPU normally in LPM0. The slave is initialized by the master
;   followed by a slave setup delay time in order to assure proper SPI
;   synchronization. P1.0 indicates proper data reception.
;
;   ACLK = n/a, MCLK = SMCLK = DCO ~ 800kHz
;
;                 MSP430F123(2)
;              -----------------
;          /|\|              XIN|-
;           --|RST          XOUT|-
;             |                 |
;       LED <-|P1.0         P3.1|-> Data Out (SIMO0)
;             |                 |
;     Scope <-|P3.4         P3.2|<- Data In (SOMI0)
;             |                 |
; Slave RST <-|P3.5         P3.3|-> Serial Clock Out (UCLK)
;
;   Z. Albus / M. Raju
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430x12x2.h"

MST_Data   .equ      R6
SLV_Data   .equ      R7

;-----------------------------------------------------------------------------
            .text                           ; Program Reset
;-----------------------------------------------------------------------------
RESET       mov.w   #0300h,SP               ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop watchdog timer
SetupP1     mov.b   #000h,&P1OUT            ; P1.0 setup for LED output
            bis.b   #001h,&P1DIR            ;
SetupP3     bis.b   #00Eh,&P3SEL            ; P3.1,2,3 SPI option select
            mov.b   #020h,&P3OUT            ; P3.4 setup for scope trigger &
            bis.b   #030h,&P3DIR            ; P3.5 setup for slave reset
SetupSPI    mov.b   #CHAR+SYNC+MM+SWRST,&U0CTL ; 8-bit, SPI, Master
            bis.b   #CKPL+SSEL1+STC,&U0TCTL ; Polarity, SMCLK, 3-wire
            mov.b   #002h,&U0BR0            ; SPICLK = SMCLK/2
            mov.b   #000h,&U0BR1            ;
            mov.b   #000h,&U0MCTL           ;
            bis.b   #USPIE0,&ME2            ; Module enable
            bic.b   #SWRST,&U0CTL           ; SPI enable
            bis.b   #URXIE0,&IE2            ; Receive interrupt enable
                                            ;
Init_Slave  bic.b   #020h,&P3OUT            ; Toggle P3.5: reset slave
            bis.b   #020h,&P3OUT            ;
Wait        mov.w   #050000,R15             ; Delay to R15
L1          dec.w   R15                     ; Decrement R15
            jnz     L1                      ; Delay over?
                                            ;
            mov.b   #000h,MST_Data          ;
            mov.b   #0FFh,SLV_Data          ;
                                            ;
Mainloop    mov.b   MST_Data,&TXBUF0        ; Transmit first character
            bis.b   #LPM0+GIE,SR            ; CPU off, enable interrupts
            nop                             ; Required for debugger only
                                            ;
;------------------------------------------------------------------------------
USART0RX_ISR;       Test for valid RX and TX character
;------------------------------------------------------------------------------
            xor.b   #010h,&P3OUT            ; XOR P3.4 for scope trigger
TX1         bit.b   #UTXIFG0,&IFG2          ; USART0 TX buffer ready?
            jz      TX1                     ; Jump is TX buffer not ready
            cmp.b   SLV_Data,&RXBUF0        ; Test for correct character RX'd
            jeq     PASS                    ;
FAIL        mov.b   MST_Data,&TXBUF0        ;
            bis.b   #001h,&P1OUT            ; .set P1.0 indicating data error
            reti                            ; Exit ISR
PASS        inc.b   MST_Data                ;
            dec.b   SLV_Data                ;
            mov.b   MST_Data,&TXBUF0        ;
            bis.b   #001h,&P1OUT            ; Pulse P1.0 indicating valid data
            bic.b   #001h,&P1OUT            ;
            reti                            ; Exit ISR
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ;
            .short  RESET                   ; POR, ext. Reset, Watchdog
            .sect   ".int07"                ;
            .short  USART0RX_ISR            ; USART0 receive
            .end                            ;