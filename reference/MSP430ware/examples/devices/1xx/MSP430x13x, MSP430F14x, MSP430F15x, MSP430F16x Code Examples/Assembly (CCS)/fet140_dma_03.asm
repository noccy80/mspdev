;******************************************************************************
;   MSP-FET430P140 Demo - DMA0, Repeated Block UART1 9600, TACCR2, ACLK
;
;   Description: DMA0 is used to transfer a string byte-by-byte as a repeating
;   block to U1TXBUF. Timer_A operates continuously at 32768Hz with CCR2IFG
;   triggering DMA0. "Hello World" is TX'd via 9600 baud UART1.
;   ACLK= TACLK 32768Hz, MCLK= SMCLK= default DCO ~ 800k
;   Baud rate divider with 32768Hz XTAL @9600 = 32768Hz/9600 = 3.41 (000Dh 4Ah )
;   //* An external watch crystal on XIN XOUT is required for ACLK *//	
;   //* MSP430F169 Device Required *//
;
;                MSP430F169
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32768Hz
;          --|RST          XOUT|-
;            |                 |
;            |             P3.6|------------> "Hello World"
;            |                 | 9600 - 8N1
;
LF           .equ   0ah                     ; ASCII Line Feed
CR           .equ   0dh                     ; ASCII Carriage Return
Delta        .equ   256                     ; Delta = (target DCO)/(4096) = 1048576
;
;   M. Buccini / L. Westlund
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430x16x.h"
;------------------------------------------------------------------------------
            .text                  ; Progam Start
;------------------------------------------------------------------------------
RESET       mov.w   #0A00h,SP               ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP3     bis.b   #0C0h,&P3SEL            ; P3.6,7 = USART1 TXD/RXD
SetupUART0  bis.b   #UTXE1+URXE1,&ME2       ; Enable USART1 TXD/RXD
            bis.b   #CHAR,&UCTL1            ; 8-bit characters
            mov.b   #SSEL0,&UTCTL1          ; UCLK = ACLK
            mov.b   #003h,&UBR01            ; 32k/9600=3.41
            mov.b   #000h,&UBR11            ;
            mov.b   #04Ah,&UMCTL1           ; no modulation
            bic.b   #SWRST,&UCTL1           ; **Initialize USART state machine**
SetupDMA0   mov.w   #DMA0TSEL_1,&DMACTL0    ; CCR2 trigger
            mov.w   #String1,&DMA0SA        ; Source block address
            mov.w   #TXBUF1,&DMA0DA         ; Destination single address
            mov.w   #13,&DMA0SZ             ; Block size
            mov.w   #DMADT_4+DMASRCINCR_3+DMASBDB+DMAEN,&DMA0CTL; Repeat, inc src
SetupTA     mov.w   #8192,&TACCR0           ; Char freq = TACLK/CCR0
            mov.w   #01,&TACCR2             ; DMA0 trigger
            mov.w   #TASSEL_1+MC_1,&TACTL   ; ACLK, up-mode
                                            ;
Mainloop    bis.w   #LPM3,SR                ; Enter LPM3
            nop                             ; Required only for debugger
                                            ;
String1     .string  CR,LF, "Hello World"
                                            ;
;-----------------------------------------------------------------------------
;           Interrupt Vectors
;-----------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .end
