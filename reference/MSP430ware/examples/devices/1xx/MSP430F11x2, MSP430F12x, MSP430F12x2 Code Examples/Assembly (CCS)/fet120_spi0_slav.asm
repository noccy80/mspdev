;******************************************************************************
;   MSP-FET430P120 Demo - USART0, SPI 3-Wire Slave
;
;   Description: SPI slave talks to SPI master using 3-wire mode. Data is sent
;   to the master starting at 0xFF and decrements. Received data from the
;   master is expected to start at 0x00 and increments with each transmission.
;   USART0 RX ISR is used to handle communication, CPU normally in LPM4.
;   Prior to inital data exchange, master pulses slaves RST for complete reset.
;   ACLK = n/a, MCLK = SMCLK = DCO ~ 800kHz
;
;                MSP430F123(2)
;             -----------------
;         /|\|              XIN|-
;          | |             XOUT|-
;          --|RST              |
;            |             P3.1|<- Data In (SIMO0)
;            |                 |
;            |             P3.2|-> Data Out (SOMI0)
;            |                 |
;            |             P3.3|<- Serial Clock In (UCLK)
;
;   Z. Albus / M. Raju
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;*******************************************************************************
 .cdecls C,LIST,  "msp430x12x2.h"

MST_Data   .equ      R6
SLV_Data   .equ      R7

;-----------------------------------------------------------------------------
            .text                           ; Program Reset
;-----------------------------------------------------------------------------
RESET       mov.w   #0300h,SP               ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop watchdog timer
SetupP3     bis.b   #00Eh,&P3SEL            ; P3.1,2,3 SPI option select
SetupSPI    mov.b   #CHAR+SYNC+SWRST,&U0CTL ; 8-bit, SPI, Slave
            bis.b   #CKPL+STC,&U0TCTL       ; Polarity, UCLK, 3-wire
            bis.b   #USPIE0,&ME2            ; Module enable
            bic.b   #SWRST,&U0CTL           ; SPI enable
            bis.b   #URXIE0,&IE2            ; Receive interrupt enable
                                            ;
            mov.b   #000h,MST_Data          ;
            mov.b   #0FFh,SLV_Data          ;
                                            ;
Mainloop    mov.b   SLV_Data,&TXBUF0        ; Transmit first character
            bis.b   #LPM4+GIE,SR            ; Enter LPM4, enable interrupts
            nop                             ; Required for debugger only
                                            ;
;------------------------------------------------------------------------------
USART0RX_ISR;       Test for valid RX and TX character
;------------------------------------------------------------------------------
TX1         bit.b   #UTXIFG0,&IFG2          ; USART0 TX buffer ready?
            jz      TX1                     ; Jump is TX buffer not ready
            cmp.b   MST_Data,&RXBUF0        ; Test for correct character RX'd
            jeq     PASS                    ;
FAIL        mov.b   SLV_Data,&TXBUF0        ;
            reti                            ; Exit ISR
PASS        inc.b   MST_Data                ;
            dec.b   SLV_Data                ;
            mov.b   SLV_Data,&TXBUF0        ;
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