;******************************************************************************
;   MSP430G2x21/G2x31 Demo - SPI full-Duplex 3-wire Slave
;
;   Description: SPI Master communicates full-duplex with SPI Slave using
;   3-wire mode. The level on P1.4 is TX'ed and RX'ed to P1.0.
;   Master will pulse slave reset for synch start.
;   ACLK = n/a, MCLK = SMCLK = Default DCO
;
;                 Slave                      Master
;              MSP430G2x21/G2x31          MSP430G2x21/G2x31
;              -----------------          -----------------
;             |              XIN|-    /|\|              XIN|-
;             |                 |      | |                 |
;             |             XOUT|-     --|RST          XOUT|-
;             |                 | /|\    |                 |
;             |          RST/NMI|--+<----|P1.2             |
;       LED <-|P1.0             |        |             P1.4|<-
;           ->|P1.4             |        |             P1.0|-> LED
;             |         SDI/P1.7|<-------|P1.6/SDO         |
;             |         SDO/P1.6|------->|P1.7/SDI         |
;             |        SCLK/P1.5|<-------|P1.5/SCLK        |
;
;   D. Dang
;   Texas Instruments Inc.
;   October 2010
;   Built with Code Composer Essentials Version: 4.2.0
;******************************************************************************
 .cdecls C,LIST,  "msp430g2221.h"
;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #0280h,SP               ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop watchdog timer
SetupP1     mov.b   #010h,&P1OUT            ; P1.4 set, else
            bis.b   #010h,&P1REN            ; P1.4 pullup
            bis.b   #001h,&P1DIR            ;
SetupUSI    bis.b   #USIPE7+USIPE6+USIPE5+USIOE,&USICTL0; Port, SPI slave
            bis.b   #USIIE,&USICTL1         ; Counter interrupt, flag remains
            bic.b   #USISWRST,&USICTL0      ; Enable USI
            mov.b   &P1IN,&USISRL           ; init-load TX data
            mov.b   #08h,&USICNT            ; init-load counter, clear flag
                                            ;
Mainloop    bis.b   #LPM4+GIE,SR            ; LPM4 w/ interrupts enabled
            nop                             ; Required for debugger only
                                            ;
;------------------------------------------------------------------------------
USI_ISR;
;------------------------------------------------------------------------------
            mov.b   &USISRL,R4              ; Temp save RX'ed char
            mov.b   &P1IN,&USISRL           ;
            mov.b   #08h,&USICNT            ; re-load counter, clear flag
            bic.b   #01h,&P1OUT             ;
            bit.b   #010h,R4                ;
            jnc     L2                      ;
L1          bis.b   #01h,&P1OUT             ;
L2          reti                            ; Exit ISR
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int04"                ; USI Vector
            .short  USI_ISR                 ;        
            .end