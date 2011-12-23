;*******************************************************************************
;   MSP430x24x Demo - USCI_A0, 19200 UART Echo ISR, DCO SMCLK
;
;   Description: Echo a received character, RX ISR used. Normal mode is LPM0.
;   USCI_A0 RX interrupt triggers TX Echo.
;   Baud rate divider with 1MHz = 1MHz/19200 = ~52.1
;   ACLK = n/a, MCLK = SMCLK = CALxxx_1MHZ = 1MHz
;
;                MSP430F249
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |     P3.4/UCA0TXD|------------>
;            |                 | 19200 - 8N1
;            |     P3.5/UCA0RXD|<------------
;
;  JL Bile
;  Texas Instruments Inc.
;  May 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x24x.h"
;-------------------------------------------------------------------------------
			.text	;Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #0500h,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
CheckCal    cmp.b   #0FFh,&CALBC1_1MHZ      ; Calibration constants erased?
            jeq     Trap
            cmp.b   #0FFh,&CALDCO_1MHZ
            jne     Load  
Trap        jmp     $                       ; Trap CPU!!
Load        mov.b   &CALBC1_1MHZ,&BCSCTL1   ; Set DCO to 1MHz
            mov.b   &CALDCO_1MHZ,&DCOCTL    ;
SetupP3     bis.b   #030h,&P3SEL            ; P3.4,5 = USCI_A0 TXD/RXD
SetupUSCI0  bis.b   #UCSSEL_2,&UCA0CTL1     ; SMCLK
            mov.b   #36h,&UCA0BR0           ; 1MHz 19200
            mov.b   #00h,&UCA0BR1           ; 1MHz 19200
            mov.b   #UCBRS0,&UCA0MCTL       ; Modulation UCBRSx = 1
            bic.b   #UCSWRST,&UCA0CTL1      ; **Initialize USCI state machine**
            bis.b   #UCA0RXIE,&IE2          ; Enable USCI_A0 RX interrupt
                                            ;
Mainloop    bis.b   #CPUOFF+GIE,SR          ; Enter LPM0, interrupts enabled
            nop                             ; Needed only for debugger
                                            ;
;-------------------------------------------------------------------------------
USCI0RX_ISR;  Echo back RXed character, confirm TX buffer is ready first
;-------------------------------------------------------------------------------
TX0         bit.b   #UCA0TXIFG,&IFG2        ; USCI_A0 TX buffer ready?
            jz      TX0                     ; Jump if TX buffer not ready
            mov.b   &UCA0RXBUF,&UCA0TXBUF   ; TX -> RXed character
            reti                            ;
                                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".int23"        ; USCI_A0 Rx Vector
            .short  USCI0RX_ISR            ;
            .sect	".reset"            ; POR, ext. Reset
            .short  RESET      
            .end
                        