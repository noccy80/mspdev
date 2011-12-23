;*******************************************************************************
;   MSP430G2xx1 Demo - USI SPI Interface to HC165/164 Shift Registers
;
;   Description: Demonstrate USI in two-way SPI mode. Data are read from
;   an HC165, and same data written back to the HC164.
;   ACLK = n/a  MCLK = SMCLK = Default DCO, USI = SMCLK/2
;
;                         MSP430G2x21/G2x31
;                       -----------------
;                   /|\|              XIN|-
;                    | |                 |     ^      HC164
;          HC165     --|RST          XOUT|-    |  -------------
;        ----------    |                 |     |-|/CLR,B       |  8
;    8  |      /LD|<---|P1.1   SIMO0/P1.6|------>|A          Qx|--\->
;   -\->|A-H   CLK|<---|P1.5/SCLK  - P1.5|------>|CLK          |
;     |-|INH    QH|--->|P1.7/SOMI        |       |             |
;     |-|SER      |    |                 |       |             |
;     - |         |    |                 |       |             |
;
;   D. Dang
;   Texas Instruments Inc.
;   October 2010
;   Built with Code Composer Essentials Version: 4.2.0
;*******************************************************************************
 .cdecls C,LIST,  "msp430g2221.h"
;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #0280h,SP               ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop watchdog timer
SetupP1     bis.b   #02h,&P1OUT             ;
            bis.b   #02h,&P1DIR             ;
SetupUSI    bis.b   #USIPE7+USIPE6+USIPE5+USIMST+USIOE,&USICTL0; Port, SPI master
            bis.b   #USICKPH+USIIE,&USICTL1 ; Counter interrupt, flag remains
            mov.b   #USIDIV_1+USISSEL_2,&USICKCTL    ; /2 SMCLK
            bic.b   #USISWRST,&USICTL0      ; Enable USI
            mov.b   #08h,&USICNT            ; init-load counter, clears flag
                                            ;
Mainloop    call    #RXTX_HC16x             ; Exchange data
Delay       push.w  #0                      ; Software delay
D1          dec.w   0(SP)                   ;
            jnz     D1                      ;
            incd.w  SP                      ;
            jmp     Mainloop                ; Repeat
                                            ;
;-------------------------------------------------------------------------------
RXTX_HC16x;   HC165--> URXBUF0  UTXBUF0 --> HC164
;-------------------------------------------------------------------------------
TX0         bit.b   #USIIFG,&USICTL1        ; USART0 TX buffer ready?
            jz      TX0                     ; Jump --> TX buffer not ready
            bic.b   #02h,&P1OUT             ; Latch data into 'HC165
            bis.b   #02h,&P1OUT             ;
;           ********************            ; Read data are ready to be written
            mov.b   #08h,&USICNT            ; Load counter, clears flag
            ret                             ; Return from subroutine
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;      
            .end

