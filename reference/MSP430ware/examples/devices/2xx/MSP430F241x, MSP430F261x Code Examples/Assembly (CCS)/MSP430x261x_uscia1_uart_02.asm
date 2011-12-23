;******************************************************************************
;   MSP430x261x Demo - USCI_A1, Ultra-Low Pwr UART 2400 Echo ISR, 32kHz ACLK
;
;   Description: Echo a received character, RX ISR used. Normal mode is LPM3,
;   USCI_A1 RX interrupt triggers TX Echo.
;   ACLK = BRCLK = LFXT1 = 32768Hz, MCLK = SMCLK = DCO ~1.045MHz
;   Baud rate divider with 32768Hz XTAL @2400 -- from User's Guide
;   //* An external watch crystal is required on XIN XOUT for ACLK *//
;
;             MSP430F261x/241x
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32KHz
;          --|RST          XOUT|-
;            |                 |
;            |     P3.6/UCA1TXD|------------>
;            |                 | 2400 - 8N1
;            |     P3.7/UCA1RXD|<------------
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x26x.h"
;-------------------------------------------------------------------------------
			.text	;Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #0850h,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP3     bis.b   #0C0h,&P3SEL            ; Use P3.6/P3.7 for USCI_A1
SetupUSCI0  bis.b   #UCSSEL_1,&UCA1CTL1     ; CLK = ACLK
            mov.b   #0Dh,&UCA1BR0           ; 2400 (see User's Guide)
            mov.b   #00h,&UCA1BR1             
            mov.b   #UCBRS_6, &UCA1MCTL     ; Modulation UCBRSx = 3
            bic.b   #UCSWRST,&UCA1CTL1      ; **Initialize USCI state machine**
            bis.b   #UCA1RXIE,&UC1IE        ; Enable USCI_A1 RX interrupt
                                            ;
Mainloop    bis.w   #LPM3+GIE,SR            ; Enter LPM3, enable interrupts
            nop                             ; Needed only for debugger
                                            ;
;-------------------------------------------------------------------------------
USCI1RX_ISR;  Echo back RXed character, confirm TX buffer is ready first
;-------------------------------------------------------------------------------
TX1         bit.b   #UCA1TXIFG,&UC1IFG      ; USCI_A1 TX buffer ready?
            jz      TX1                     ; Jump if TX buffer not ready
            mov.b   &UCA1RXBUF,&UCA1TXBUF   ; TX -> RXed character
            reti                            ;
                                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect     ".int17"        		; USCI0 Rx Vector
            .short   USCI1RX_ISR             ;
            .sect	".reset"	           	; MSP430 RESET Vector
            .short  RESET  
            .end
