;******************************************************************************
;   MSP-FET430P140 Demo - DMA0, Block Mode UART1 9600, ACLK
;
;   Description: DMA0 is used to transfer a string as a block to U1TXBUF.
;   UTXIFG1 WILL trigger DMA0. "Hello World" is TX'd via 9600 baud on UART1.
;   Watchdog in interval mode triggers block transfer every 1000ms.
;   Level senstive trigger used for UTXIFG1 to prevent loss of inital edge
;   sensitive triggers - UTXIFG1 which is set at POR.
;   ACLK = UCLK 32768Hz, MCLK = SMCLK = default DCO ~ 800k
;   Baud rate divider with 32768hz XTAL @9600 = 32768Hz/9600 = 3.41 (000Dh 4Ah )
;   //* An external watch crystal on XIN XOUT is required for ACLK *//	
;   //* Final Production MSP430F169 Device Required *//
;
;                MSP430F169
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32768Hz
;          --|RST          XOUT|-
;            |                 |
;            |             P3.6|------------> "Hello World"
;            |                 | 9600 - 8N1
;
LF           .equ   0ah                     ; ASCII Line Feed
CR           .equ   0dh                     ; ASCII Carriage Return
;
;   M. Buccini / L. Westlund
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430x16x.h"
;------------------------------------------------------------------------------
            .text                  ; Progam Start
;------------------------------------------------------------------------------
RESET       mov.w   #0A00h,SP               ; Initialize stackpointer
StopWDT     mov.w   #WDT_ADLY_1000,&WDTCTL  ; WDT 1000ms, ACLK, interval timer
            bis.b   #WDTIE,&IE1             ; Enable WDT interrupt
SetupP3     bis.b   #0C0h,&P3SEL            ; P3.6,7 = USART0 TXD/RXD
SetupUART1  bis.b   #UTXE1+URXE1,&ME2       ; Enable USART1 TXD/RXD
            bis.b   #CHAR,&UCTL1            ; 8-bit characters
            mov.b   #SSEL0,&UTCTL1          ; UCLK = SMCLK
            mov.b   #003h,&UBR01            ; 32k/9600=3.41
            mov.b   #000h,&UBR11            ;
            mov.b   #04Ah,&UMCTL1           ; no modulation
            bic.b   #SWRST,&UCTL1           ; **Initialize USART state machine**
SetupDMA0   mov.w   #DMA0TSEL_10,&DMACTL0   ; UTXIFG1 trigger
            mov.w   #String1,&DMA0SA        ; Source block address
            mov.w   #TXBUF1,&DMA0DA         ; Destination single address
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
String1      .string  CR,LF, "Hello World"
                                            ;
;-----------------------------------------------------------------------------
;           Interrupt Vectors
;-----------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int10"                ; WDT Vector
            .short  WDT_ISR                 ;
            .end
