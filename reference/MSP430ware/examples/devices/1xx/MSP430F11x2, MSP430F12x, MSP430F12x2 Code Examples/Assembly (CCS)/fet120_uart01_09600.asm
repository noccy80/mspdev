;******************************************************************************
;   MSP-FET430P120 Demo - USART0, UART 9600 Echo ISR, HF XTAL ACLK
;
;   Description: Echo a received character, RX ISR used. Normal mode is LPM0,
;   USART0 RX interrupt triggers TX Echo. Though not required, MCLK = LFXT1
;   Baud rate divider with 3.58Mhz XTAL @9600 = 3.58MHz/9600 = 372 (0174h)
;   ACLK = MCLK = UCLK0 = LFXT1 = 3.58MHz, SMCLK = DCOCLK
;   //* An external 3.58MHz XTAL on XIN XOUT is required for ACLK *//	
;
;
;               MSP430F123(2)
;             -----------------
;         /|\|              XIN|-
;          | |                 | 3.58MHz
;          --|RST          XOUT|-
;            |                 |
;            |             P3.4|------------>
;            |                 | 9600 - 8N1
;            |             P3.5|<------------
;
;   M. Buccini / M. Raju
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430x12x2.h"
;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #300h,SP                ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP3     bis.b   #030h,&P3SEL            ; P3.4,5 = USART0 TXD/RXD
SetupBC     bis.b   #XTS,&BCSCTL1           ; LFXT1 = HF XTAL
SetupOsc    bic.b   #OFIFG,&IFG1            ; Clear OSC fault flag
            mov.w   #0FFh,R15               ; R15 = Delay
SetupOsc1   dec.w   R15                     ; Additional delay to ensure start
            jnz     SetupOsc1               ;
            bit.b   #OFIFG,&IFG1            ; OSC fault flag set?
            jnz     SetupOsc                ; OSC Fault, clear flag again
            bis.b   #SELM_3,&BCSCTL2        ; MCLK = LFXT1
SetupUART0  bis.b   #UTXE0+URXE0,&ME2       ; Enable USART0 TXD/RXD
            bis.b   #CHAR,&UCTL0            ; 8-bit characters
            bis.b   #SSEL0,&UTCTL0          ; UCLK = ACLK
            mov.b   #074h,&UBR00            ; 3.58Mhz 9600 - 372
            mov.b   #001h,&UBR10            ; 3.58Mhz 9600
            mov.b   #000h,&UMCTL0           ; no modulation 19200
            bic.b   #SWRST,&UCTL0           ; **Initalize USART state machine**
            bis.b   #URXIE0,&IE2            ; Enable USART0 RX interrupt
                                            ;
Mainloop    bis.b   #CPUOFF+GIE,SR          ; Enter LPM0, interrupts enabled
            nop                             ; Needed only for debugger
                                            ;
;------------------------------------------------------------------------------
USART0RX_ISR;  Confirm TX buffer is ready, then Echo back RXed character
;------------------------------------------------------------------------------
TX1         bit.b   #UTXIFG0,&IFG2          ; USART0 TX buffer ready?
            jz      TX1                     ; Jump is TX buffer not ready
            mov.b   &RXBUF0,&TXBUF0         ; TX -> RXed character
            reti                            ;
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ;
            .short  RESET                   ; POR, ext. Reset, Watchdog
            .sect   ".int07"                ;
            .short  USART0RX_ISR            ; USART0 receive
            .end