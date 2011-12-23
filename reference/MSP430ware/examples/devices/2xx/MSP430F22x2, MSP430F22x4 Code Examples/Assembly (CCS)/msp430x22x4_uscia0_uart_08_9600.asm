;*******************************************************************************
;   MSP430F22x4 Demo - USCI_A0, UART 9600 Full-Duplex Transceiver, 32kHz ACLK
;
;   Description: USCI_A0 communicates continously as fast as possible full-
;   duplex with another device. Normal mode is LPM3, with activity only during
;   RX and TX ISR's. The TX ISR indicates the USCI_A0 is ready to send another
;   character. The RX ISR indicates the USCI_A0 has received a character. At
;   9600 baud, a full character is tranceived ~1ms.
;   The levels on P1.4/5 are TX'ed. RX'ed value is displayed on P1.0/1.
;   ACLK = BRCLK = LFXT1 = 32768, MCLK = SMCLK = DCO ~1.2MHz
;   Baud rate divider with 32768Hz XTAL @9600 = 32768Hz/9600 = 3.41
;   //* An external watch crystal is required on XIN XOUT for ACLK *//
;
;                 MSP430F22x4                  MSP430F22x4
;              -----------------            -----------------
;             |              XIN|-      /|\|              XIN|-
;             |                 | 32kHz  | |                 | 32kHz
;             |             XOUT|-       --|RST          XOUT|-
;             |                 | /|\      |                 |
;             |              RST|---       |                 |
;             |                 |          |                 |
;           ->|P1.4             |          |             P1.0|-> LED
;           ->|P1.5             |          |             P1.1|-> LED
;       LED <-|P1.0             |          |             P1.4|<-
;       LED <-|P1.1             |          |             P1.5|<-
;             |     UCA0TXD/P3.4|--------->|P3.5             |
;             |                 |   9600   |                 |
;             |     UCA0RXD/P3.5|<---------|P3.4             |
;
;
;  P.Thanigai
;  Texas Instruments Inc.
;  August 2007
;  Built with Code Composer Essentials Version: 2.0
;*******************************************************************************
 .cdecls C,LIST,  "msp430x22x4.h"
                              
;------------------------------------------------------------------------------
            .text                  			; Program reset
;------------------------------------------------------------------------------
RESET       mov.w   #300h,SP                ; Initialize stack pointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop watchdog timer
SetupP1     mov.b   #000h,&P1OUT            ; P1.0/1 setup for LED output
            bis.b   #003h,&P1DIR            ;
SetupP3     bis.b   #030h,&P3SEL            ; Use P3.4/P3.5 for USCI_A0
SetupUSCI0  bis.b   #UCSSEL_1,&UCA0CTL1     ; CLK = ACLK
            mov.b   #03h,&UCA0BR0           ; 32kHz/9600 = 3.41
            mov.b   #00h,&UCA0BR1           ;
            mov.b   #UCBRS1+UCBRS0,&UCA0MCTL; Modulation UCBRSx = 3
            bic.b   #UCSWRST,&UCA0CTL1      ; **Initialize USCI state machine**
            bis.b   #UCA0RXIE+UCA0TXIE,&IE2 ; Enable USCI_A0 TX/RX interrupt
                                            ;
Mainloop    bis.b   #LPM3+GIE,SR            ; Enter LPM3 w/ interrupts enabled
            nop                             ; Required for debugger only
                                            ;
;-------------------------------------------------------------------------------
USCI0TX_ISR;
;-------------------------------------------------------------------------------
            mov.b   &P1IN,R4                ;
            rrc.b   R4                      ; Justify 4x right
            rrc.b   R4                      ;
            rrc.b   R4                      ;
            rrc.b   R4                      ;
            and.b   #03h,R4                 ;
            mov.b   R4,&UCA0TXBUF           ; Transmit character
            reti                            ; Exit ISR
;-------------------------------------------------------------------------------
USCI0RX_ISR;
;-------------------------------------------------------------------------------
            mov.b   &UCA0RXBUF,&P1OUT       ; Display RX'ed charater
            reti                            ; Exit ISR
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int06"                ; USCI Vector
            .short  USCI0TX_ISR             ; 
            .sect   ".int07"                ; USCI Vector
            .short  USCI0RX_ISR             ;        
            .end
