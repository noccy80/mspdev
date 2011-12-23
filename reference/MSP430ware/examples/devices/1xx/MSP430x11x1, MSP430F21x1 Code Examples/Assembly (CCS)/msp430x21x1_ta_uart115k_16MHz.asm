;******************************************************************************
;   MSP430x21x1 Demo - Timer_A, UART 115200 Echo, 16MHz DCO SMCLK
;
;   Description: Use Timer_A CCR0 hardware output modes and SCCI data latch
;   to implement UART function @ 115k baud. Software does not directly read and
;   write to RX and TX pins, instead proper use of output modes and SCCI data
;   latch are demonstrated. Use of these hardware features eliminates ISR
;   latency effects as hardware insures that output and input bit latching and
;   timing are perfectly synchronised with Timer_A regardless of other
;   software activity. In the Mainloop the UART function readies the UART to
;   receive one character and waits in LPM3 with all activity interrupt driven.
;   After a character has been received, the UART receive function forces exit
;   from LPM0 in the Mainloop which echo's back the received character.
;   ACLK = n/a, MCLK = TACLK = DCO = 16000000Hz
;
;               MSP430F21x1
;            -----------------
;        /|\|              XIN|-
;         | |                 |
;         --|RST          XOUT|-
;           |                 |
;           |             P1.3|--------> Power for MAX3221
;           |   CCI0A/TXD/P1.1|-------->
;           |                 | 115200 8N1
;           |   CCI0B/RXD/P2.2|<--------
;
;   H. Grewal / A. Dannenberg
;   Texas Instruments Inc.
;   July 2005
;   Built with Code Composer Essentials Version: 1.0
;*****************************************************************************
 .cdecls C,LIST,  "msp430x21x1.h"

RXD         .equ    004h                    ; RXD on P2.2
TXD         .equ    002h                    ; TXD on P1.1
;
;   CPU Registers Used
RXTXData .equ     R4
BitCnt   .equ     R5
;
;   Conditions for 115200 Baud SW UART, SMCLK = 16MHz
Bitime_5    .equ    69                      ; ~ 0.5 bit length
Bitime      .equ    138                     ; 115942 baud
;------------------------------------------------------------------------------
            .text                           ;
;------------------------------------------------------------------------------
RESET       mov.w   #300h,SP                ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop Watchdog Timer
            mov.b   &CALBC1_16MHZ,&BCSCTL1  ; Set DCO
            mov.b   &CALDCO_16MHZ,&DCOCTL

SetupTA     mov.w   #TASSEL_2+MC_2,&TACTL   ; SMCLK, continuous mode
SetupC0     mov.w   #OUT,&CCTL0             ; TXD Idle as Mark
SetupP1_2   bis.b   #TXD,&P1SEL             ; P1.1/TA0 for TXD function
            bis.b   #TXD,&P1DIR             ; TXD output on P1
            bis.b   #RXD,&P2SEL             ; P2.2/TA0 as RXD input
            bis.b   #08h,&P1DIR             ; Power MAX3221
            bis.b   #08h,&P1OUT
                                            ;
Mainloop    call    #RX_Ready               ; UART ready to RX one Byte
            bis.w   #LPM0+GIE,SR            ; Enter LPM0 w/ int until Byte RXed
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
            mov.w   #8,BitCnt               ; Load Bit Counter, 8 data bits
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
;-----------------------------------------------------------------------------
;           Interrupt Vectors
;-----------------------------------------------------------------------------
            .sect ".reset"                  ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect ".int09"                  ; Timer_A0 Vector
            .short  TA0_ISR                 ;
            .end
