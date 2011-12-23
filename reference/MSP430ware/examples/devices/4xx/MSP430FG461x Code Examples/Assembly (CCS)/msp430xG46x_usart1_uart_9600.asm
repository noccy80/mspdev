;******************************************************************************
;   MSP430xG46x Demo - USART1, Ultra-Low Pwr UART 9600 Echo ISR, 32kHz ACLK
;
;   Description: Echo a received character, RX ISR used. Normal mode is LPM3,
;   USART1 RX interrupt triggers TX Echo.
;   ACLK = UCLK1 = LFXT1 = 32768, MCLK = SMCLK = DCO~ 1048k
;   Baud rate divider with 32768hz XTAL @9600 = 32768Hz/9600 = 3.41 (0003h 4Ah )
;   //* An external watch crystal is required on XIN XOUT for ACLK *//	
;
;
;                 MSP430FG461x
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |       P4.0/UTXD1|------------>
;            |                 | 9600 - 8N1
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
            mov.b   #SSEL0,&U1TCTL          ; UCLK = ACLK
            mov.b   #003h,&U1BR0            ; 32k/9600 - 3.41
            mov.b   #000h,&U1BR1            ;
            mov.b   #04Ah,&U1MCTL           ; Modulation
            bic.b   #SWRST,&U1CTL           ; **Initialize USART state machine**
            bis.b   #URXIE1,&IE2            ; Enable USART1 RX interrupt
                                            ;
Mainloop    bis.b   #LPM3+GIE,SR            ; Enter LPM3, interrupts enabled
            nop                             ; Required for debugger
                                            ;
;------------------------------------------------------------------------------
USART1RX_ISR;  Echo back RXed character, confirm TX buffer is ready first
;------------------------------------------------------------------------------
TX1         bit.b   #UTXIFG1,&IFG2          ; USART1 TX buffer ready?
            jz      TX1                     ; Jump is TX buffer not ready
            mov.b   &U1RXBUF,&U1TXBUF         ; TX -> RXed character
            reti                            ;
                                            ;
;------------------------------------------------------------------------------
;			Interrupt Vectors
;------------------------------------------------------------------------------
            .sect    ".int19"
            .short   USART1RX_ISR
            .sect	".reset"            	
            .short   RESET
            .end
 