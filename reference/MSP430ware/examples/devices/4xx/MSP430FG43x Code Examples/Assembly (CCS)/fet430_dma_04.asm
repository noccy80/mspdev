;******************************************************************************
;   MSP-FET430P430 Demo - DMA0, Block Mode UART1 9600, ACLK
;
;   Description; DMA0 is used to transfer a string as a block to U0TXBUF.
;   UTXIFG0 WILL trigger DMA0. "Hello World" is TX'd via 9600 baud on UART0.
;   Watchdog in interval mode triggers block transfer every 1000ms.
;   Level senstive trigger used for UTXIFG0 to prevent loss of inital edge
;   sensitive triggers - UTXIFG0 which is set at POR.
;   Baud rate divider with 32768hz XTAL @9600 = 32768Hz/9600 = 3.41 (003h|4Ah)
;   ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
;   ;* An external watch crystal between XIN & XOUT is required for ACLK *//	
;
;                MSP430FG439
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |       P2.4/UTXD0|------------> "Hello World"
;            |                 | 9600 - 8N1
;
;
;   M. Buccini / M. Mitchell
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430xG43x.h"

LF          .equ    0ah                     ; ASCII Line Feed
CR          .equ    0dh                     ; ASCII Carriage Return
                                            ;
;------------------------------------------------------------------------------
            .text                  ; Progam Start
;------------------------------------------------------------------------------
RESET       mov.w   #0A00h,SP               ; Initialize stack pointer
StopWDT     mov.w   #WDT_ADLY_1000,&WDTCTL  ; WDT 1000ms, ACLK, interval timer
            bis.b   #WDTIE,&IE1             ; Enable WDT interrupt
SetupP3     bis.b   #018h,&P2SEL            ; P2.4,5 = USART0 TXD/RXD
SetupUART1  bis.b   #UTXE0+URXE0,&ME1       ; Enable USART0 TXD/RXD
            bis.b   #CHAR,&UCTL0            ; 8-bit characters
            mov.b   #SSEL0,&UTCTL0          ; UCLK = SMCLK
            mov.b   #003h,&UBR00            ; 32k/9600=3.41
            mov.b   #000h,&UBR10            ;
            mov.b   #04Ah,&UMCTL0           ; Modulation
            bic.b   #SWRST,&UCTL0           ; *Initialize USART state machine*
SetupDMA0   mov.w   #DMA0TSEL_4,&DMACTL0    ; UTXIFG0 trigger
            mov.w   #String1,&DMA0SA        ; Source block address
            mov.w   #TXBUF0,&DMA0DA         ; Destination single address
            mov.w   #13,&DMA0SZ             ; Block size
            mov.w   #DMASRCINCR_3+DMASBDB+DMALEVEL,&DMA0CTL; Repeat, inc src
                                            ;
Mainloop    bis.w   #LPM3 + GIE,SR          ; Enter LPM3 w/ interrupts
            nop                             ; Required only for debugger
                                            ;
;-----------------------------------------------------------------------------
WDT_ISR;    Trigger DMA block
;-----------------------------------------------------------------------------
            bis.w   #DMAEN,&DMA0CTL         ; Enable
            reti                            ;		
                                            ;
String1      .byte  CR,LF, "Hello World"
                                            ;
;-----------------------------------------------------------------------------
;           Interrupt Vectors
;-----------------------------------------------------------------------------
            .sect   ".reset"                ; RESET Vector
            .short  RESET                   ;
            .sect   ".int10"                ; WDT Vector
            .short  WDT_ISR                 ;
            .end
