;******************************************************************************
;  MSP-FET430P140 Demo - DMA0/1/2, USART0 UART 9600 Full-Duplex Transcvr, ACLK
;
;  Description: UART0 communicates continously as fast as possible full-duplex
;  with another device. With data transfer driven directly by DMA - no CPU
;  resources used.
;  DMA0 trigger from TX ready, which uses MPY to shift read P1 left
;  DMA1 trigger from MPY moves shifted P1 data to the USART0 TX buffer
;  DMA2 trigger from USART0 RX buffer moves received data to P1
;  The levels on P1.4/5 are TX'ed. RX'ed value is displayed on P1.0/1.
;  ACLK = UCLK1 = LFXT1 = 32768, MCLK = SMCLK = DCO~ 800k
;  Baud rate divider with 32768hz XTAL @9600 = 32768Hz/9600 = 3.41 (000Dh 4Ah )
;  //* An external watch crystal is required on XIN XOUT for ACLK *//	
;  //* Final Production MSP430F16x(x) Device Required *//
;
;                MSP430F169                   MSP430F169
;             -----------------            -----------------
;            |              XIN|-      /|\|              XIN|-
;            |                 | 32KHz  | |                 | 32KHz
;            |             XOUT|-       --|RST          XOUT|-
;            |                 | /|\      |                 |
;            |              RST|---       |                 |
;            |                 |          |                 |
;          ->|P1.4             |          |             P1.0|-> LED
;          ->|P1.5             |          |             P1.1|-> LED
;      LED <-|P1.0             |          |             P1.4|<-
;      LED <-|P1.1             |          |             P1.5|<-
;            |        UTXD/P3.4|--------->|P3.5             |
;            |                 | 9600 8N1 |                 |
;            |        URXD/P3.5|<---------|P3.4             |
;
;
;   H. Grewal / A. Dannenberg
;   Texas Instruments Inc.
;   November 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430x16x.h"
;------------------------------------------------------------------------------
            .text                           ; Progam Start
;------------------------------------------------------------------------------
RESET       mov.w   #0A00h,SP               ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop watchdog timer
            mov.b   #0h,&P1OUT              ; P1.0/1 setup for LED output
            mov.b   #03h,&P1DIR             ;
            mov.b   #030h,&P3SEL            ; P3.6,7 = USART1 TXD/RXD
            bis.b   #UTXE0+URXE0,&ME1       ; Enable USART0 TXD/RXD
            bis.b   #CHAR,&UCTL0            ; 8-bit characters
            mov.b   #SSEL0,&UTCTL0          ; UCLK = ACLK
            mov.b   #03h,&UBR00             ; 32k/9600 - 3.41
            mov.b   #00h,&UBR10             ;
            mov.b   #04Ah,&UMCTL0           ; Modulation
            bic.b   #SWRST,&UCTL0           ; **Initialize USART state machine**
            mov.w   #1000h,&MPY             ; MPY first operand
            mov.w   #DMA2TSEL_3+DMA1TSEL_11+DMA0TSEL_4,&DMACTL0 ; URXIFG0, MPY, UTXIFG0
TX_load     mov.w   #RESHI, &DMA1SA         ; Src address = multiplier
            mov.w   #U0TXBUF, &DMA1DA       ; Dst address = UART TX Buffer
            mov.w   #01h,&DMA1SZ            ; Size in words
            mov.w   #DMADT_4+DMASBDB+DMAEN,&DMA1CTL ; Sng, config
TX_Init     mov.w   #P1IN, &DMA0SA          ; Src address
            mov.w   #OP2, &DMA0DA           ; Dst address = multiplier
            mov.w   #01h,&DMA0SZ            ; Size in words
            mov.w   #DMADT_4+DMASBDB+DMALEVEL+DMAEN,&DMA0CTL ; Sng rpt, config
RX_store    mov.w   #U0RXBUF, &DMA2SA       ; Src address = UART RX Buffer
            mov.w   #P1OUT, &DMA2DA         ; Dst address = P1
            mov.w   #01h,&DMA2SZ            ; Size in words
            mov.w   #DMADT_4+DMASBDB+DMAEN,&DMA2CTL ; Sng, config
            bis.b   #LPM3+GIE,SR            ; Enter LPM3
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; POR, ext. Reset, Watchdog, Flash
            .short  RESET                   ;
            .end

