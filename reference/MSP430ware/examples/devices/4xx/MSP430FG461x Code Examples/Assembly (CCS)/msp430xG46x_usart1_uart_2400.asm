;******************************************************************************
;  MSP430xG46x Demo - USART1, Ultra-Low Pwr UART 2400 Echo ISR, 32kHz ACLK
;
;  Description: Echo a received character, RX ISR used. In the Mainloop USART1
;  is made ready to receive one character with interrupt active. The Mainloop
;  waits in LPM3. The USART1 ISR forces the Mainloop to exit LPM3 after
;  receiving one character which echo's back the received character.
;  ACLK = UCLK1 = LFXT1 = 32768, MCLK = SMCLK = DCO~ 1048k
;  Baud rate divider with 32768kHz XTAL @2400 = 32768Hz/2400 = 13.65 (000Dh)
;  //* An external watch crystal is required on XIN XOUT for ACLK *//	
;
;                MSP430xG461x
;            -----------------
;        /|\|              XIN|-
;         | |                 | 32kHz
;         --|RST          XOUT|-
;           |                 |
;           |             P4.0|----------->
;           |                 | 2400 - 8N1
;           |             P4.1|<-----------
;
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

SetupP3     bis.b   #003h,&P4SEL            ; P4.0,1 = USART1 TXD/RXD
SetupUART0  bis.b   #UTXE1+URXE1,&ME2       ; Enable USART1 TXD/RXD
            bis.b   #CHAR,&U1CTL            ; 8-bit characters
            mov.b   #SSEL0,&U1TCTL          ; UCLK = ACLK
            mov.b   #00Dh,&U1BR0            ; 32k/2400 - 13.65
            mov.b   #000h,&U1BR1            ; 32k 2400
            mov.b   #06Bh,&U1MCTL           ; 32k 2400 modulation
            bic.b   #SWRST,&U1CTL           ; **Initialize USART state machine**
            bis.b   #URXIE1,&IE2            ; Enable USART1 RX interrupt
                                            ;
Mainloop    bis.b   #LPM3+GIE,SR            ; Enter LPM3, enable interrupts
            jmp     Mainloop                ; Do nothing
                                            ;
;------------------------------------------------------------------------------
USART1RX_ISR;  Echo back RXed character, confirm TX buffer is ready first
;------------------------------------------------------------------------------
TX0         bit.b   #UTXIFG1,&IFG2          ; USART1 TX buffer ready?
            jz      TX0                     ; Jump if TX buffer not ready
            mov.b   &U1RXBUF,&U1TXBUF       ; TX -> RXed character
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
 