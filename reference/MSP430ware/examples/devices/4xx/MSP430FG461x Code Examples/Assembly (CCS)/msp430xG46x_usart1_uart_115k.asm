;******************************************************************************
;   MSP430xG46x Demo - USART1, 115200 UART Echo ISR, DCO SMCLK
;
;   Description: Echo a received character, RX ISR used. Normal mode is LPM0.
;   USART1 RX interrupt triggers TX Echo.
;   Baud rate divider with 1048576hz = 1048576/115200 = ~9.1 (009h|08h)
;   ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
;   //* An external watch crystal between XIN & XOUT is required for ACLK *//	
;
;                MSP430FG461x
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |       P4.0/UTXD1|------------>
;            |                 | 115200 - 8N1
;            |       P4.1/URXD1|<------------
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430xG46x.h"
;-------------------------------------------------------------------------------
			.text	;Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #900,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupFLL    bis.b   #XCAP14PF,&FLL_CTL0     ; Configure load caps

OFIFGcheck  bic.b   #OFIFG,&IFG1            ; Clear OFIFG
            mov.w   #047FFh,R15             ; Wait for OFIFG to set again if
OFIFGwait   dec.w   R15                     ; not stable yet
            jnz     OFIFGwait
            bit.b   #OFIFG,&IFG1            ; Has it set again?
            jnz     OFIFGcheck              ; If so, wait some more

SetupP4     bis.b   #003h,&P4SEL            ; P4.0,1 = USART1 TXD/RXD
SetupUART0  bis.b   #UTXE1+URXE1,&ME2       ; Enable USART1 TXD/RXD
            bis.b   #CHAR,&U1CTL            ; 8-bit characters
            mov.b   #SSEL1,&U1TCTL          ; UCLK = SMCLK
            mov.b   #009h,&U1BR0            ; 1MHz 115200
            mov.b   #000h,&U1BR1            ; 1MHz 115200
            mov.b   #008h,&U1MCTL           ; Modulation
            bic.b   #SWRST,&U1CTL           ; **Initialize USART state machine**
            bis.b   #URXIE1,&IE2            ; Enable USART1 RX interrupt
                                            ;
Mainloop    bis.b   #CPUOFF+GIE,SR          ; Enter LPM0, interrupts enabled
            nop                             ; Needed only for debugger
                                            ;
;------------------------------------------------------------------------------
USART1RX_ISR;  Echo back RXed character, confirm TX buffer is ready first
;------------------------------------------------------------------------------
TX0         bit.b   #UTXIFG1,&IFG2          ; USART1 TX buffer ready?
            jz      TX0                     ; Jump if TX buffer not ready
            mov.b   &U1RXBUF,&U1TXBUF       ; TX -> RXed character
            reti                            ;

;------------------------------------------------------------------------------
;			Interrupt Vectors
;------------------------------------------------------------------------------
            .sect    ".int19"
            .short   USART1RX_ISR
            .sect	".reset"            	
            .short   RESET
            .end
            