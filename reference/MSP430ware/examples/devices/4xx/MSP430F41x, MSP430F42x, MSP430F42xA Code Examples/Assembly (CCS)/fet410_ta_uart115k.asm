;******************************************************************************
;   MSP-FET430P410 Demo - Timer_A, UART 115200 Echo, DCO SMCLK
;
;   Description: Use Timer_A CCR0 hardware output modes and SCCI data latch to
;   implement UART function @ 115k baud. Software does not directly read and
;   write to RX and TX pins, instead proper use of output modes and SCCI data
;   latch are demonstrated. Using these hardware features eliminates ISR
;   latency effects as hardware ensures that input and output bit latching and
;   timing are perfectly synchronised with Timer_A regardless of other
;   software activity. In the Mainloop the UART function readies the UART to
;   receive one character and waits in LPM0 with all activity interrupt driven.
;   After a character has been received, the UART receive function forces exit
;   from LPM0 in the Mainloop which echo's back the received character.
;   ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
;   ;* An external watch crystal between XIN & XOUT is required for ACLK *//
;
;                MSP430F413
;            -----------------
;        /|\|              XIN|-
;         | |                 | 32kHz
;         --|RST          XOUT|-
;           |                 |
;           |         P1.0/TA0|----------->
;           |                 | 115200 8N1
;           |    P1.1/TA0/MCLK|<-----------
;
;   M. Buccini / S. Karthikeyan
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430x41x.h"

;   CPU Registers Used
RXTXData .equ     R4
BitCnt   .equ     R5
;
RXD         .equ   002h                     ; RXD on P1.1
TXD         .equ   001h                     ; TXD on P1.0
                                            ;
;   Conditions for 115200 Baud SW UART, SMCLK = 8MHz
Bitime_5    .equ   36                       ; ~ 0.5 bit length
Bitime      .equ   69                       ; 8.6 us bit length ~ 115942 baud
                                            ;
;------------------------------------------------------------------------------
            .text                  ;
;------------------------------------------------------------------------------
RESET       mov.w   #300h,SP                ; Initialize stackpointer
SetupWDT    mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop Watchdog Timer
                                            ;
SetupFLL2   bis.b   #FN_4,&SCFI0            ; x2 DCO, 8MHz nominal DCO
            bis.b   #DCOPLUS+XCAP14PF,&FLL_CTL0 ; DCO+, configure load caps
            mov.b   #121,&SCFQCTL           ;(121+1) x 2 x 32768 = 7.99 Mhz
                                            ;
SetupTA     mov.w   #TASSEL1+MC1,&TACTL     ; SMCLK, continous mode
SetupC0     mov.w   #OUT,&CCTL0             ; TXD Idle as Mark
SetupP1_2   bis.b   #TXD+RXD,&P1SEL         ; P1.0/1 TA0 for TXD/RXD function
            bis.b   #TXD,&P1DIR             ; TXD output on P1
            eint                            ; General Enable Interrupts
                                            ;
Mainloop    call    #RX_Ready               ; UART ready to RX one Byte
            bis.w   #LPM0,SR                ; Enter LPM0 Until Byte RXed
            call    #TX_Byte                ; TX Back RXed Byte Received
            jmp     Mainloop                ;
                                            ;
;------------------------------------------------------------------------------
TX_Byte   ; Subroutine Transmits Character from RXTXData Buffer
;------------------------------------------------------------------------------
            mov.w   &TAR,&CCR0              ; Current state of TA counter
            add.w   #Bitime,&CCR0           ; Some time till first bit
            bis.w   #0100h, RXTXData        ; Add mark stop bit to RXTXData
            rla.w   RXTXData                ; Add space start bit
            mov.w   #10,BitCnt              ; Load Bit counter, 8data + ST/SP
            mov.w   #OUTMOD0+CCIE,&CCTL0    ; TXD = mark = idle
TX_Wait     bit.w   #CCIE,&CCTL0            ; Wait for TX completion
            jnz     TX_Wait                 ;
            ret                             ;
                                            ;
;------------------------------------------------------------------------------
RX_Ready  ; Subroutine Readies UART to Receive Character into RXTXData Buffer
;------------------------------------------------------------------------------
            mov.w   #8,BitCnt              ; Load Bit Counter, 8 data bits
SetupRX     mov.w   #SCS+CCIS0+OUTMOD0+CM1+CAP+CCIE,&CCTL0  ; Sync,Neg Edge,cap
            ret                             ;
                                            ;
;------------------------------------------------------------------------------
TA0_ISR  ;  RXTXData Buffer holds UART Data
;------------------------------------------------------------------------------
            add.w   #Bitime,&CCR0           ; Time to next bit
            bit.w   #CCIS0,&CCTL0           ; RX on CCI0B?
            jnz     UART_RX                 ; Jump --> RX
UART_TX     cmp.w   #00h,BitCnt             ;
            jne     TX_Next                 ; Next bit?
            bic.w   #CCIE,&CCTL0            ; All Bits TX or RX, Disable Int.
            reti                            ;
TX_Next     bic.w   #OUTMOD2,&CCTL0         ; TX Mark
            rra.w   RXTXData                ; LSB is shifted to carry
            jc      TX_Test                 ; Jump --> bit = 1
TX_Space    bis.w   #OUTMOD2,&CCTL0         ; TX Space
TX_Test     dec.w   BitCnt                  ; All bits sent (or received)?
            reti                            ;
                                            ;
UART_RX     bit.w   #CAP,&CCTL0             ; Capture mode = start bit edge
            jz      RX_Bit                  ; Start bit edge?
RX_Edge     bic.w   #CAP,&CCTL0             ; Switch to compare mode
            add.w   #Bitime_5,&CCR0         ; First databit 1.5 bits from edge
            reti                            ;
RX_Bit      bit.w   #SCCI,&CCTL0            ; Get bit waiting in receive latch
            rrc.b   RXTXData                ; Store received bit
RX_Test     dec.w   BitCnt                  ; All bits RXed?
            jnz     RX_Next                 ; Next bit?
;>>>>>>>>>> Decode of Received Byte Here <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
RX_Comp     bic.w   #CCIE,&CCTL0            ; All bits RXed, disable interrupt
            mov.w   #GIE,0(SP)              ; Decode byte = active in Mainloop
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
RX_Next     reti                            ;
;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect     ".reset"                  ; RESET Vector
            .short  RESET                   ;
            .sect   ".int06"                  ; Timer_A0 Vector
            .short  TA0_ISR                 ;
            .end