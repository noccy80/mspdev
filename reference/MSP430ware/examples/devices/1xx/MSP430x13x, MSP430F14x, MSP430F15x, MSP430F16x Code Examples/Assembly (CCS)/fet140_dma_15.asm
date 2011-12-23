;******************************************************************************
;  MSP-FET430P140 Demo - DMA0/1/2, USART0 SPI 3-Wire SPI Slave P1.x Exchange
;
;  Description: SPI Master communicates at fast as possible, full-duplex with
;  SPI Slave using 3-wire mode. The level on P1.4/5 is TX'ed and RX'ed to P1.0
;  and P1.1. Master will pulse slave Reset on init to insure synch start.
;  With data transfer driven directly by DMA - no CPU resources used.
;  DMA0 trigger from TX read, which uses MPY to shift read P1 left
;  DMA1 trigger from MPY moves shifted P1 data to the USART0 TX buffer
;  DMA2 trigger from USART0 RX buffer moves received data to P1
;  Slave normal mode is LPM4.
;  ACLK = n/a, MCLK = SMCLK = DCO ~ 800kHz, ULCK = external
;  //* Final Production MSP430F16x(x) Device Required *//
;
;             fet140_dma_15              fet140_dma_14
;             MSP430F169 Slave           MSP430F169 Master
;             -----------------          -----------------
;            |              XIN|-    /|\|              XIN|-
;            |                 |      | |                 |
;            |             XOUT|-     --|RST          XOUT|-
;            |                 | /|\    |                 |
;            |              RST|--+<----|P3.0             |
;      LED <-|P1.0             |        |             P1.4|<-
;      LED <-|P1.1             |        |             P1.5|<-
;          ->|P1.4             |        |             P1.0|-> LED
;          ->|P1.5             |        |             P1.1|-> LED
;            |       SIMO0/P3.1|<-------|P3.1/SIMO0       |
;            |       SOMI0/P3.2|------->|P3.2/SOMI0       |
;            |        UCLK/P3.3|<-------|P3.3/UCLK        |
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
SetupP3     bis.b   #0Eh,&P3SEL             ; P3.1-3 SPI option select
SetupSPI    mov.b   #CHAR+SYNC+SWRST,&U0CTL ; 8-bit SPI
            mov.b   #CKPL+STC,&U0TCTL       ; 3-pin mode
            mov.b   #02h,&U0BR0             ; SMCLK/2 for baud rate
            clr.b   &U0BR1                  ;
            clr.b   &U0MCTL                 ; Clear modulation
            bis.b   #USPIE0,&ME1            ; Enable USART0 SPI mode
            bic.b   #SWRST,&U0CTL           ; **Initialize USART state machine**
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
            bis.b   #LPM4+GIE,SR            ; Enter LPM4
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; POR, ext. Reset, Watchdog, Flash
            .short  RESET                   ;
            .end

