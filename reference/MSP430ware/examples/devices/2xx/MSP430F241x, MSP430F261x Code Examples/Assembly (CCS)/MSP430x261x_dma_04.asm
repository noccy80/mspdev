;******************************************************************************
;   MSP430x261x Demo - DMA0, single transfer Mode UART1 9600, ACLK
;
;   Description: DMA0 is used to transfer a string as a block to U1TXBUF.
;   UTXIFG1 WILL trigger DMA0. "Hello World" is TX'd via 9600 baud on UART1.
;   Watchdog in interval mode triggers block transfer every 1000ms.
;   Level senstive trigger used for UTXIFG1 to prevent loss of inital edge
;   sensitive triggers - UTXIFG1 which is set at POR.
;   ACLK = UCLK 32768Hz, MCLK = SMCLK = default DCO 1048576Hz
;   Baud rate divider with 32768hz XTAL @9600 = 32768Hz/9600 = 3.41 (0003h)
;
;                MSP430x2619
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32768Hz
;          --|RST          XOUT|-
;            |                 |
;            |             P3.6|------------> "Hello World"
;            |                 | 9600 - 8N1
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x26x.h"
;-------------------------------------------------------------------------------
LF          .equ    0ah                     ; ASCII Line Feed
CR          .equ    0dh                     ; ASCII Carriage Return
;-------------------------------------------------------------------------------
			.text	;Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #0850h,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDT_ADLY_1000,&WDTCTL  ; WDT 1000ms, ACLK, interval timer
            bis.b   #WDTIE,&IE1             ; Enable WDT interrupt
SetupP3     bis.b   #BIT6+BIT7,&P3SEL       ; P3.6,7 = USART1 TXD/RXD
SetupUSCI1  bis.b   #UCSSEL_1,&UCA1CTL1     ; ACLK
            mov.b   #3,&UCA1BR0             ; 32768Hz 9600 32k/9600=3.41
            mov.b   #0,&UCA1BR1             ; 32768Hz 9600
            mov.b   #UCBRS_3,&UCA1MCTL      ; Modulation UCBRSx = 3
            bic.b   #UCSWRST,&UCA1CTL1      ; **Initialize USCI state machine**
SetupDMA0   mov.w   #DMA0TSEL_10,&DMACTL0   ; UTXIFG1 trigger
            movx.a  #String1,&DMA0SA        ; Source block address
            movx.a  #UCA1TXBUF,&DMA0DA      ; Destination single address
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
String1     .word      CR,LF, 'Hello World'
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".int26"              ; Watchdog Timer
            .short  WDT_ISR
            .sect	".reset"	           ; POR, ext. Reset, Watchdog
            .short  RESET
            .end