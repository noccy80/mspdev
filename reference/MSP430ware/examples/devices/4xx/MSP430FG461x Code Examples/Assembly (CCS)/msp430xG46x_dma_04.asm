;******************************************************************************
;   MSP430xG461x Demo - DMA0, Block Mode UART1 9600, ACLK
;
;   Description: DMA0 is used to transfer a string as a block to U1TXBUF.
;   UTXIFG1 WILL trigger DMA0. "Hello World" is TX'd via 9600 baud on UART1.
;   Watchdog in interval mode triggers block transfer every 1000ms.
;   Level senstive trigger used for UTXIFG1 to prevent loss of inital edge
;   sensitive triggers - UTXIFG1 which is set at POR.
;   ACLK = UCLK 32768Hz, MCLK = SMCLK = default DCO 1048576Hz
;   Baud rate divider with 32768hz XTAL @9600 = 32768Hz/9600 = 3.41 (0003h 4Ah)
;
;                MSP430xG461x
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32768Hz
;          --|RST          XOUT|-
;            |                 |
;            |             P4.0|------------> "Hello World"
;            |                 | 9600 - 8N1
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430xG46x.h"
;-------------------------------------------------------------------------------
LF          .equ     0ah                     ; ASCII Line Feed
CR          .equ     0dh                     ; ASCII Carriage Return
;-------------------------------------------------------------------------------
			.text	;Program Start
;-----------------------------------------------------------------------------
RESET       mov.w   #900,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDT_ADLY_1000,&WDTCTL  ; WDT 1000ms, ACLK, interval timer
            bis.b   #WDTIE,&IE1             ; Enable WDT interrupt
SetupP4     bis.b   #BIT0+BIT1,&P4SEL             ; P4.0,1 = USART1 TXD/RXD
SetupUART1  bis.b   #UTXE1+URXE1,&ME2       ; Enable USART1 TXD/RXD
            bis.b   #CHAR,&UCTL1            ; 8-bit characters
            mov.b   #SSEL0,&UTCTL1          ; BRCLK = ACLK
            mov.b   #003h,&UBR01            ; 32k/9600=3.41
            mov.b   #000h,&UBR11            ;
            mov.b   #04Ah,&UMCTL1           ; Modulation
            bic.b   #SWRST,&UCTL1           ; Release USART state machine
SetupDMA0   mov.w   #DMA0TSEL_10,&DMACTL0   ; UTXIFG1 trigger
            movx.a  #String1,&DMA0SA        ; Source block address
            movx.a  #TXBUF1,&DMA0DA         ; Destination single address
            mov.w   #0013,&DMA0SZ           ; Block size
            mov.w   #DMASRCINCR_3+DMASBDB+DMALEVEL,&DMA0CTL; Repeat, inc src
                                            ;
Mainloop    bis.w   #LPM3+GIE,SR            ; Enter LPM3 w/ interrupts
            nop                             ; Required only for debugger
                                            ;
;-------------------------------------------------------------------------------
WDT_ISR;    Trigger DMA block transfer
;-------------------------------------------------------------------------------
            bis.w   #DMAEN,&DMA0CTL         ; Enable
            reti                            ;
;-------------------------------------------------------------------------------
String1     .byte      CR,LF, 'Hello World'
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect     ".int26"              ; Watchdog Timer
            .short   WDT_ISR
            .sect	".reset"            ; POR, ext. Reset, Watchdog
            .short   RESET
            .end
