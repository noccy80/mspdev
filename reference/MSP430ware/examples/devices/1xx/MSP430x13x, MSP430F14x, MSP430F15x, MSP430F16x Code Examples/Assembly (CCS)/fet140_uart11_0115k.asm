;******************************************************************************
;   MSP-FET430P140 Demo - USART1, UART 115200 Echo ISR, HF XTAL ACLK
;
;   Description: Echo a received character, RX ISR used. Normal mode is LPM0,
;   USART0 RX interrupt triggers TX Echo. Though not required, MCLK = LFXT1
;   ACLK = MCLK = UCLK1 = LFXT1 = 8MHz
;   Baud rate divider with 8MHz XTAL @115k = 8000000/115200 = 0069
;   //* An external 8MHz XTAL on XIN XOUT is required for ACLK *//	
;   //* Min Vcc required varies with MCLK frequency - refer to datasheet *//	
;
;
;                MSP430F149
;             -----------------
;         /|\|              XIN|-
;          | |                 | 8MHz
;          --|RST          XOUT|-
;            |                 |
;            |             P3.6|------------>
;            |                 | 115200 - 8N1
;            |             P3.7|<------------
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
SetupP3     bis.b   #0C0h,&P3SEL            ; P3.6,7 = USART1 option select
SetupBC     bis.b   #XTS,&BCSCTL1           ; LFXT1 = HF XTAL
SetupOsc    bic.b   #OFIFG,&IFG1            ; Clear OSC fault flag
            mov.w   #0FFh,R15               ; R15 = Delay
SetupOsc1   dec.w   R15                     ; Additional delay to ensure start
            jnz     SetupOsc1               ;
            bit.b   #OFIFG,&IFG1            ; OSC fault flag set?
            jnz     SetupOsc                ; OSC Fault, clear flag again
            bis.b   #SELM_3,&BCSCTL2        ; MCLK = LFXT1
SetupUART1  bis.b   #UTXE1+URXE1,&ME2       ; Enable USART1 TXD/RXD
            bis.b   #CHAR,&UCTL1            ; 8-bit characters
            mov.b   #SSEL0,&UTCTL1          ; UCLK = ACLK
            mov.b   #045h,&UBR01            ; 8MHz 115200
            mov.b   #000h,&UBR11            ; 8MHz 115200
            mov.b   #000h,&UMCTL1           ; 8MHz no modulation 115200
            bic.b   #SWRST,&UCTL1           ; **Initialize USART state machine**
            bis.b   #URXIE1,&IE2            ; Enable USART1 RX interrupt
                                            ;
Mainloop    bis.b   #CPUOFF+GIE,SR          ; Enter LPM0, interrupts enabled
            nop                             ; Needed only for debugger
                                            ;
;------------------------------------------------------------------------------
USART1_ISR;  Echo back RXed character, confirm TX buffer is ready first
;------------------------------------------------------------------------------
TX2         bit.b   #UTXIFG1,&IFG2          ; USART1 TX buffer ready?
            jz      TX2                     ; Jump is TX buffer not ready
            mov.b   &RXBUF1,&TXBUF1         ; TX -> RXed character
            reti                            ;
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ;
            .short  RESET                   ; POR, ext. Reset, Watchdog
            .sect   ".int03"                ;
            .short  USART1_ISR              ; USART1 Receive
            .end