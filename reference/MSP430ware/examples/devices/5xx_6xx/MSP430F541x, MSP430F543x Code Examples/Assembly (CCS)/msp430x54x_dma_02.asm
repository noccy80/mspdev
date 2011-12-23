;*******************************************************************************
;   MSP430x54x Demo - DMA0, Single Transfer in Block Mode UART1 9600, ACLK
;
;   Description: DMA0 is used to transfer a string as a block to USCI_A0.
;   USCIA0TXIFG WILL trigger DMA0. "Hello World" is TX'd via 9600 baud on
;   USCI_A0. Watchdog in interval mode triggers block transfer every 1000ms.
;   Level senstive trigger used for USCIA0TXIFG to prevent loss of inital edge
;   sensitive triggers - USCIA0TXIFG which is set at POR.
;   ACLK = UCLK 32768Hz, MCLK = SMCLK = default DCO 1048576Hz
;   Baud rate divider with 32768hz XTAL @9600 = 32768Hz/9600 = 3.41 (0003h 4Ah)
;
;                 MSP430x54x
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32768Hz
;          --|RST          XOUT|-
;            |                 |
;            |             P3.4|------------> "Hello World"
;            |                 | 9600 - 8N1
;
;   M. Morales
;   Texas Instruments Inc.
;   July 2009
;   Built with Code Composer Essentials v3.x
;*******************************************************************************

    .cdecls C,LIST,"msp430x54x.h"

;-------------------------------------------------------------------------------
LF          .equ    0x0a                     ; ASCII Line Feed
CR          .equ    0x0d                     ; ASCII Carriage Return
;-------------------------------------------------------------------------------
 
;-------------------------------------------------------------------------------
            .global _main 
            .text                           ; Assemble to Flash memory
;-------------------------------------------------------------------------------
String1     .byte   CR,LF,"Hello World"
_main
;-------------------------------------------------------------------------------
RESET       mov.w   #0x5C00,SP              ; Initialize stackpointer
StopWDT     mov.w   #WDT_ADLY_1000,&WDTCTL  ; WDT 1000ms, ACLK, interval timer
            bis.w   #WDTIE,&SFRIE1          ; Enable WDT interrupt
SetupP3     bis.b   #0x30,&P3SEL            ; P3.4,5 = USCI_A0 TXD/RXD
SetupUSCIA0 bis.b   #UCSWRST,&UCA0CTL1      ; 8-bit characters
            mov.b   #UCSSEL_1,&UCA0CTL1     ; CLK = ACLK
            mov.b   #0x03,&UCA0BR0          ; 32k/9600=3.41
            mov.b   #0x00,&UCA0BR1          ;
            mov.b   #UCBRS_3+UCBRF_0,&UCA0MCTL ; Modulation
            bic.b   #UCSWRST,&UCA0CTL1      ; Release USCI state machine
SetupDMA0   mov.w   #DMA0TSEL_17,&DMACTL0   ; USCI_A0 TXIFG trigger
            movx.a  #String1,&DMA0SA        ; Source block address
            movx.a  #UCA0TXBUF,&DMA0DA      ; Destination single address
            mov.w   #13,&DMA0SZ             ; Block size
            mov.w   #DMASRCINCR_3+DMASBDB,&DMA0CTL ; Repeat, inc src
                                            ;
Mainloop    bis.w   #LPM3+GIE,SR            ; Enter LPM3 w/ interrupts
            nop                             ; Required only for debugger
                                            ;
;-------------------------------------------------------------------------------
WDT_ISR ;    Trigger DMA block transfer
;-------------------------------------------------------------------------------
            bis.w   #DMAEN,&DMA0CTL         ; Enable
            bic.b   #UCTXIFG,&UCA0IFG       ; Toggle TX IFG to trigger first
            bis.b   #UCTXIFG,&UCA0IFG       ; DMA transfer...
            reti                            ;
            
;-------------------------------------------------------------------------------
                  ; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".int58"                  ; WatchDog Timer Vector
            .short  WDT_ISR
            .sect   ".reset"                ; POR, ext. Reset
            .short  RESET
            .end
            