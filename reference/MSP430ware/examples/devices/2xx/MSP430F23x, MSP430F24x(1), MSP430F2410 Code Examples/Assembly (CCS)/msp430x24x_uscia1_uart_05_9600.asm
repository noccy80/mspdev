;*******************************************************************************
;   MSP430x24x Demo - USCI_A1, Ultra-Low Pwr UART 9600 Echo ISR, 32kHz ACLK
;
;   Description: Echo a received character, RX ISR used. Normal mode is LPM3,
;   USCI_A1 RX interrupt triggers TX Echo.
;   ACLK = BRCLK = LFXT1 = 32768, MCLK = SMCLK = DCO ~1.045MHz
;   Baud rate divider with 32768Hz XTAL @9600 = 32768Hz/9600 = 3.41
;   //* An external watch crystal is required on XIN XOUT for ACLK *//
;
;                MSP430F249
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |     P3.6/UCA1TXD|------------>
;            |                 | 9600 - 8N1
;            |     P3.7/UCA1RXD|<------------
;
;  JL Bile
;  Texas Instruments Inc.
;  May 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x24x.h"
;-------------------------------------------------------------------------------
			.text							;Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #0500h,SP         		; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP1     mov.b   #0FFh,&P1DIR            ; All P1.x outputs
            clr.b   &P1OUT                  ; All P1.x reset
SetupP2     mov.b   #0FFh,&P2DIR            ; All P2.x outputs
            clr.b   &P2OUT                  ; All P2.x reset
SetupP3     bis.b   #0C0h,&P3SEL            ; P3.6,7 = USCI_A1 TXD/RXD
            mov.b   #0FFh,&P3DIR            ; All P3.x outputs
            clr.b   &P3OUT                  ; All P3.x reset
SetupP4     mov.b   #0FFh,&P4DIR            ; All P4.x outputs
            clr.b   &P4OUT                  ; All P4.x reset
SetupP5     mov.b   #0FFh,&P5DIR            ; All P5.x outputs
            clr.b   &P5OUT                  ; All P5.x reset
SetupP6     mov.b   #0FFh,&P6DIR            ; All P6.x outputs
            clr.b   &P6OUT                  ; All P6.x reset               
            
SetupUSCI1  bis.b   #UCSSEL_1,&UCA1CTL1     ; CLK = ACLK
            mov.b   #03h,&UCA1BR0           ; 32kHz/9600 = 3.41
            mov.b   #00h,&UCA1BR1           ;
            mov.b   #UCBRS1+UCBRS0,&UCA1MCTL; Modulation UCBRSx = 3
            bic.b   #UCSWRST,&UCA1CTL1      ; **Initialize USCI state machine**
            bis.b   #UCA1RXIE,&UC1IE          ; Enable USCI_A1 RX interrupt
                                            ;
Mainloop    bis.b   #LPM3+GIE,SR            ; Enter LPM3, interrupts enabled
            nop                             ; Required for debugger
                                            ;
;-------------------------------------------------------------------------------
USCI1RX_ISR;  Echo back RXed character, confirm TX buffer is ready first
;-------------------------------------------------------------------------------
TX0         bit.b   #UCA1TXIFG,&UC1IFG      ; USCI_A1 TX buffer ready?
            jz      TX0                     ; Jump if TX buffer not ready
            mov.b   &UCA1RXBUF,&UCA1TXBUF   ; TX -> RXed character
            reti                            ;
                                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".int17"        ; USCI1 Rx Vector
            .short   USCI1RX_ISR             ;
            .sect   ".reset"            ; RESET Vector
            .short   RESET                   ;
            .end
