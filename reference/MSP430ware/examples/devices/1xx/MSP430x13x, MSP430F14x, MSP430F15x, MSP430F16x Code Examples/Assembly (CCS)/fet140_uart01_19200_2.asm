;******************************************************************************
;   MSP-FET430P140 Demo - USART0, UART 19200 Echo ISR, XT2 HF XTAL SMCLK
;
;   Description: This program will echo a received character, RX interrupt
;   service used. XT2 oscillator used in this example.
;   ACLK = MCLK = SMCLK = UCLK0 = XT2 = 8MHz
;   Baud rate divider with 8Mhz XTAL @19200 = 8MHz/19200 = 416.66 ~ 417
;   //* An external 8MHz XTAL on X2IN X2OUT is required for XT2CLK *//
;   //* Min Vcc required varies with MCLK frequency - refer to datasheet *//		
;
;                MSP430F149
;             -----------------
;         /|\|            XT2IN|-
;          | |                 | 8Mhz
;          --|RST        XT2OUT|-
;            |                 |
;            |             P3.4|------------>
;            |                 | 19200 - 8N1
;            |             P3.5|<------------
;
;   M. Buccini / G. Morton
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430x14x.h"
;------------------------------------------------------------------------------
            .text                           ; Progam Start
;------------------------------------------------------------------------------
RESET       mov.w   #0A00h,SP               ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP3     bis.b   #030h,&P3SEL            ; P3.4,5 = USART0 TXD/RXD
SetupBC     bic.b   #XT2OFF,&BCSCTL1        ; XT2on
SetupOsc    bic.b   #OFIFG,&IFG1            ; Clear OSC fault flag
            mov.w   #0FFh,R15               ; R15 = Delay
SetupOsc1   dec.w   R15                     ; Additional delay to ensure start
            jnz     SetupOsc1               ;
            bit.b   #OFIFG,&IFG1            ; OSC fault flag set?
            jnz     SetupOsc                ; OSC Fault, clear flag again
            bis.b   #SELM_2+SELS,BCSCTL2    ; MCLK = SMCLK = XT2
                                            ;
SetupUART0  bis.b   #UTXE0+URXE0,&ME1       ; Enable USART0 TXD/RXD
            bis.b   #CHAR,&UCTL0            ; 8-bit characters
            mov.b   #SSEL1,&UTCTL0          ; UCLK = SMCLK
            mov.b   #0A0h,&UBR00            ; 8Mhz/19200 ~ 417
            mov.b   #001h,&UBR10            ;
            mov.b   #000h,&UMCTL0           ; no modulation
            bic.b   #SWRST,&UCTL0           ; **Initialize USART state machine**
            bis.b   #URXIE0,&IE1            ; Enable USART0 RX interrupt
                                            ;
Mainloop    bis.b   #CPUOFF+GIE,SR          ; Enter LPM0, interrupts enabled
            nop                             ; Needed only for debugger
                                            ;
;------------------------------------------------------------------------------
USART0RX_ISR;  Echo back RXed character, confirm TX buffer is ready first
;------------------------------------------------------------------------------
TX1         bit.b   #UTXIFG0,&IFG1          ; USART1 TX buffer ready?
            jz      TX1                     ; Jump is TX buffer not ready
            mov.b   &RXBUF0,&TXBUF0         ; TX -> RXed character
            reti                            ;
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ;
            .short  RESET                   ; POR, ext. Reset, Watchdog
            .sect   ".int09"                ;
            .short  USART0RX_ISR            ; USART0 receive
            .end