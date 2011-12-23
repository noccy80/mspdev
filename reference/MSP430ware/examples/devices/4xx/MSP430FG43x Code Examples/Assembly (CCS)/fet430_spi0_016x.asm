;******************************************************************************
;   MSP-FET430P430 Demo - USART0, SPI Interface to HC165/164 Shift Registers
;
;   Description: Demonstrate USART0 in two-way SPI mode. Data are read from
;   an HC165, and same data written back to the HC164.
;   ACLK = n/a, MCLK = SMCLK = default DCO
;   ;**SWRST** please see MSP430x4xx Users Guide for description //
;   ;*USART0 control bits are in different SFR's from MSP430F14x/13x/12x*//
;
;                          MSP430FG439
;                       -----------------
;                   /|\|              XIN|-
;                    | |                 |     ^      HC164
;          HC165     --|RST          XOUT|-    |  -------------
;        ----------    |                 |     |-|/CLR,B       |  8
;    8  |      /LD|<---|P3.0   P3.1/SIMO0|------>|A          Qx|--\->
;   -\->|A-H   CLK|<---|-- P3.3/UCLK0 ---|------>|CLK          |
;     |-|INH    QH|--->|P3.2/SOMI0       |       |             |
;     |-|SER      |    |                 |       |             |
;     - |         |    |                 |       |             |
;
;   M. Buccini / M. Mitchell
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430xG43x.h"
;------------------------------------------------------------------------------
            .text                  ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #0A00h,SP               ; Initialize stack pointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop watchdog timer
SetupP3     bis.b   #0Eh,&P3SEL             ; P3.1-3 SPI option select
            bis.b   #01h,&P3DIR             ; P3.0 output direction
SetupSPI    bis.b   #USPIE0,&ME1            ; Enable USART0 SPI mode
            bis.b   #CKPH+SSEL1+SSEL0+STC,&UTCTL0 ; SMCLK, 3-pin mode
            bis.b   #CHAR+SYNC+MM,&UCTL0    ; 8-bit SPI Master **SWRST**
            mov.b   #02h,&UBR00             ; SMCLK/2 for baud rate
            clr.b   &UBR10                  ;
            clr.b   &UMCTL0                 ; Clear modulation
            bic.b   #SWRST,&UCTL0           ; **Initialize USART state machine**

                                            ;
Mainloop    call    #RXTX_HC16x             ; Exchange data
Delay       push.w  #0                      ; Software delay
D1          dec.w   0(SP)                   ;
            jnz     D1                      ;
            incd.w  SP                      ;
            jmp     Mainloop                ; Repeat
                                            ;
;------------------------------------------------------------------------------
RXTX_HC16x;   HC165--> URXBUF0  UTXBUF0 --> HC164
;------------------------------------------------------------------------------
TX0         bit.b   #UTXIFG0,&IFG1          ; USART0 TX buffer ready?
            jz      TX0                     ; Jump --> TX buffer not ready
            bic.b   #01h,&P3OUT             ; Latch data into 'HC165
            bis.b   #01h,&P3OUT             ;
            mov.b   &RXBUF0,&TXBUF0         ; Previous data to TX, RX next
            ret                             ; Return from subroutine
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; RESET Vector
            .short  RESET                   ;
            .end

