;*******************************************************************************
;   MSP430F22x4 Demo - USCI_A0 IrDA External Loopback Test, 8MHz SMCLK
;
;   Description: This example transmits bytes through the USCI module
;   configured for IrDA mode, and receives them using an external loopback
;   connection. The transfered sequence is 00h, 01h, 02h, ..., ffh. The
;   received bytes are also stored in memory starting at address RxData.
;   In the case of an RX error the LED is lighted and program execution stops.
;   An external loopback connection has been used as it allows for the
;   connection of a scope to monitor the communication, which is not possible
;   when using the internal loopback.
;   ACLK = n/a, MCLK = SMCLK = BRCLK = CALxxx_8MHZ = 8MHz
;
;               MSP430F22x4
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |     P3.5/UCA0RXD|--+   external
;            |     P3.4/UCA0TXD|--+   loopback connection
;            |                 |
;            |                 |
;            |             P1.0|--->  LED
;            |                 |
;
;  P.Thanigai
;  Texas Instruments Inc.
;  August 2007
;  Built with Code Composer Essentials Version: 2.0
;*******************************************************************************
 .cdecls C,LIST,  "msp430x22x4.h"
;------------------------------------------------------------------------------             
RxData      .usect ".bss",256              ; Received data buffer-256 bytes
;------------------------------------------------------------------------------                              
;------------------------------------------------------------------------------
            .text                  			; Program reset
;------------------------------------------------------------------------------
RESET       mov.w   #300h,SP                ; Initialize stack pointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupBCS    mov.b   &CALDCO_8MHZ,&DCOCTL    ; Load 8MHz constants
            mov.b   &CALBC1_8MHZ,&BCSCTL1   ;
SetupP1     bic.b   #001h,&P1OUT            ; Clear P1.0
            bis.b   #001h,&P1DIR            ; P1.0 output
SetupP3     bis.b   #030h,&P3SEL            ; Use P3.4/P3.5 for USCI_A0
SetupUSCI0  bis.b   #UCSWRST,&UCA0CTL1      ; Set SW Reset
            mov.b   #UCSSEL_2+UCSWRST,&UCA0CTL1
                                            ; Use SMCLK, keep SW reset
            mov.b   #52,&UCA0BR0            ; 8MHz/52=153.8KHz
            mov.b   #0,&UCA0BR1             ;
            mov.b   #UCBRF_1+UCOS16,&UCA0MCTL
                                            ; Set 1st stage modulator to 1
                                            ; 16-times oversampling mode
            mov.b   #UCIRTXPL2+UCIRTXPL0+UCIRTXCLK+UCIREN,&UCA0IRTCTL
                                            ; Pulse length = 6 half clock cyc
                                            ; Enable BITCLK16, IrDA enc/dec
            bic.b   #UCSWRST,&UCA0CTL1      ; Resume operation
                                            ;
            clr.w   R4                      ; Init delay counter
            clr.b   R5                      ; TX data and pointer, 8-bit
                                            ;
Mainloop    inc.w   R4                      ; Small delay
            cmp.w   #1000,R4                ;
            jne     Mainloop                ;
            clr.w   R4                      ; Re-init delay counter
                                            ;
TX          bit.b   #UCA0TXIFG,&IFG2        ; USCI_A0 TX buffer ready?
            jnc     TX                      ; Loop if not
            mov.b   R5,&UCA0TXBUF           ; TX character
            dint                            ;
            bis.b   #UCA0RXIE,&IE2          ; Enable RX int
            bis.w   #CPUOFF+GIE,SR          ; Enter LPM0, interrupts enabled
            mov.b   &UCA0RXBUF,RxData(R5)   ; Store RXed character in RAM
            cmp.b   R5,&UCA0RXBUF           ; RX OK?
            jeq     RX_OK                   ;
                                            ;
RX_ERROR    bis.b   #001h,&P1OUT            ; LED P1.0 on
            jmp     $                       ; Trap PC here
                                            ;
RX_OK       inc.b   R5                      ; Next character to TX
            jmp     Mainloop                ; Again
                                            ;
;-------------------------------------------------------------------------------
USCIAB0RX_ISR; Clear UCA0RXIFG interrupt flag and return active
;-------------------------------------------------------------------------------
            bic.b   #UCA0RXIFG,&IFG2        ; Clear RX int flag
            bic.b   #UCA0RXIE,&IE2          ; Disable RX int
            bic.w   #CPUOFF,0(SP)           ; Return active after receiption
            reti                            ; Return from ISR
            
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int07"                ; USCI Vector
            .short  USCIAB0RX_ISR           ;        
            .end

