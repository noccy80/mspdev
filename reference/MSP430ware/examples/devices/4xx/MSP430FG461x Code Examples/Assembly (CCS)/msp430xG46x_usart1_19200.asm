;******************************************************************************
;   MSP430xG46x Demo - USART1, Ultra-Low Pwr UART 19200 Echo ISR, 32kHz ACLK
;
;   Description: Echo a received character, USART1 RX ISR at high-speed used
;   with ultra-low power techniques.  Normal operation in LPM3.  On valid RX
;   character, character echoed back. Use start-bit edge detect - URXSE - to
;   automatically (re)enable DCO and trigger ISR.  ISR must make sure DCO clock
;   source remains enabled for the UART to receive full character.
;   Software needs to make sure a character has been completely TX'ed, or RX'ed
;   before entering LPM3, which disables DCO required for the USART baud rate
;   generator. In the example, TX'ing is checked using the TXEPT bit directly.
;   RX'ing is checked using the SSEL0 clock select bit as a flag. This is
;   possible because UCLK1 = SMCLK when either both SSEL1 and SSEL0 or just
;   SSEL1 = 1. In the example, when SSEL1 = SSEL0 = 1 there is no RX'ing, and
;   LPM3 is allowed. When SSEL 1 = 1 and  SSEL0 = 0 SMCLK is selected, but
;   RX'ing is active and the DCO is required, thus LPM3 is not allowed.
;   ACLK = LFXT1 = 32768,  MCLK = SMCLK = UCLK1 = DCOCLK = 1048576
;   Baud rate divider with 1048576Hz= 1048576Hz/19200 ~ 55 (0036h)
;   //* An external 32kHz watch crystal on XIN XOUT is required for ACLK *//	
;
;
;                MSP430FG461x
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32768Hz
;          --|RST          XOUT|-
;            |                 |
;            |       P4.0/UTXD1|------------>
;            |                 | 19200 - 8N1
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
            bis.b   #CHAR,&U1CTL            ; 8-bit char
            bis.b   #SSEL1+SSEL0+URXSE,&U1TCTL ; UCLK = SMCLK, start edge
            mov.b   #036h,&U1BR0            ; 1MHz 19200
            mov.b   #000h,&U1BR1            ; 1MHz 19200
            mov.b   #06Bh,&U1MCTL           ; Modulation
            bic.b   #SWRST,&U1CTL           ; **Initialize USART state machine**
            bis.b   #URXIE1,&IE2            ; Enable USART1 RX interrupt
                                            ;
                                            ;
Mainloop    bit.b   #TXEPT,&U1TCTL          ; Confirm no TXing before --> LPM3
            jeq     Mainloop                ;
            dint                            ; Disable interrupts
            nop                             ; One clock for dint to latch
RX_Test     bit.b   #SSEL0,&U1TCTL          ; SSEL0 = 0 as flag for RX'ing
            jnc     RX_Active               ;
            bis.b   #LPM3+GIE,SR            ; Enter LPM3, interrupts enabled
            jmp     Mainloop                ;
RX_Active   bis.b   #LPM0+GIE,SR            ; Enter LPM0, interrupts enabled
            jmp     Mainloop                ;
                                            ;
                                            ;
;------------------------------------------------------------------------------
USART1RX_ISR;  Echo back RXed character, confirm TX buffer is ready first
;------------------------------------------------------------------------------
            bit.b   #URXIFG1,&IFG2          ; Interrupt from start edge?
            jnc     RX_Edge                 ; Jump--> interrupt from edge
TX1         bit.b   #UTXIFG1,&IFG2          ; USART1 TX buffer ready?
            jz      TX1                     ; Jump is TX buffer not ready
            mov.b   &U1RXBUF,&U1TXBUF       ; TX -> RXed character
            bis.b   #SSEL0,&U1TCTL          ; SSEL0 = 1, RX complete
            bic.b   #LPM3,0(SP)             ; Exit LPM3 on reti
            reti                            ;
                                            ;
RX_Edge     bic.b   #URXSE,&U1TCTL          ; Clear start edge signal
            bis.b   #URXSE,&U1TCTL          ; Enable start edge detect
            bic.b   #SSEL0,&U1TCTL          ; SSEL0 = 0 as flag for start
            bic.b   #SCG1+SCG0,0(SP)        ; Enter LPM0 on reti
            reti                            ;
                                            ;
;------------------------------------------------------------------------------
;			Interrupt Vectors
;------------------------------------------------------------------------------
            .sect	".int19"
            .short   USART1RX_ISR
            .sect	".reset"            	;	RESET Vector
            .short   RESET					;
            .end
