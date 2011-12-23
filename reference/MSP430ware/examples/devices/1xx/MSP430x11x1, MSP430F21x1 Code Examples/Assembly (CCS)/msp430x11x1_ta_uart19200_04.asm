;*******************************************************************************
;   MSP430x11x1 Demo - Timer_A, Ultra-Low Pwr UART 19200 Echo, No XTAL ROSC
;
;   Description: This program demonstrates a half-duplex 19200-baud UART using
;   Timer_A3 using no XTAL and an external resistor for DCO ROSC. DCO used for
;   TACLK UART baud generation. The program will wait in LPM4, echoing back
;   a received character using 8N1 protocol. On valid RX character, character
;   echoed back.
;   Using a 100k resistor on ROSC, with default DCO setting, set DCOCLK ~2MHz.
;   ACLK = n/a, MCLK = SMCLK ~2MHz DCOCLK
;   ;* Use of external resistor reduces temperature sensitivity of DCOCLK *//
;
;                MSP430F1121
;             -----------------
;   /|\   /|\|              XIN|-
;    |     | |                 |
;   100k   --|RST          XOUT|-
;    |       |                 |
;    +-------|P2.5/ROSC        |
;            |   CCI0A/TXD/P1.1|-------->
;            |                 | 19200 8N1
;            |   CCI0B/RXD/P2.2|<--------
;
;   CPU registers used
RXTXData .equ     R4
BitCnt   .equ     R5
;
;   Conditions for 19200 Baud HW/SW UART, SMCLK = DCOCLK ~ 2Mhz
Bitime_5    .equ    42                      ; 0.5 bit length
Bitime      .equ    104                     ; 52 us
Delta       .equ    488                     ; DCOCLK = (Delta)/(32768/8)

RXD         .set    004h                    ; RXD on P2.2
TXD         .set    002h                    ; TXD on P1.1
;
;   M. Buccini / Z. Albus
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;*******************************************************************************
 .cdecls C,LIST,  "msp430x11x1.h"
;-------------------------------------------------------------------------------
            .text                           ; Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #300h,SP                ; Initialize Stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupBC     bis.b   #DCOR,&BCSCTL2          ; Rosc
            bis.w   #OSCOFF,SR              ; XTAL not used
Setup_TA    mov.w   #TASSEL_2+MC_2,&TACTL   ; SMCLK, ContMode
SetupC0     mov.w   #OUT,&CCTL0             ; TXD Idle as Mark
SetupP1_2   bis.b   #TXD,&P1SEL             ; P1.1/TA0 for TXD function
            bis.b   #TXD,&P1DIR             ; TXD output on P1
            bis.b   #RXD,&P2SEL             ; P2.2/TA0 as RXD input
                                            ;
Mainloop    call    #RX_Ready               ; UART ready to RX one Byte
            bis.w   #LPM4+GIE,SR            ; Enter LPM4 w/ int until Byte RXed
            call    #TX_Byte                ; TX Back RXed Byte Received
            jmp     Mainloop                ;
                                            ;
;-------------------------------------------------------------------------------
TX_Byte   ; Subroutine that Transmit One Byte from RXTXData Buffer.
;-------------------------------------------------------------------------------
            mov.w   &TAR,&CCR0              ; Current state of TA Counter
            add.w   #Bitime,&CCR0           ; Some time till first bit
            bis.w   #0100h, RXTXData        ; Add mark stop bit to RXTXData
            rla.w   RXTXData                ; Add space start bit
            mov.w   #10,BitCnt              ; Load Bit Counter, 8data + ST/SP
            mov.w   #OUTMOD0+CCIE,&CCTL0    ; TXD = mark = idle
TX_Wait     bit.w   #CCIE,&CCTL0            ; Wait for TX completion
            jnz     TX_Wait                 ;
            ret                             ;
                                            ;
;-------------------------------------------------------------------------------
RX_Ready  ; Subroutine that will Receive One Byte into RXTXData Buffer.
          ; !! Sync capture not possible as DCO=TACLK=SMCLK can be off !!
;-------------------------------------------------------------------------------
            mov.w   #8,BitCnt               ; Load Bit Counter, 8 data bits
SetupRX     mov.w   #CM1+CCIS0+OUTMOD0+CAP+CCIE,&CCTL0; Neg Edge,Cap
            ret                             ;
                                            ;
;-------------------------------------------------------------------------------
TA0_ISR  ;  RXTXData Buffer holds UART Data.
;-------------------------------------------------------------------------------
            add.w   #Bitime,&CCR0           ; Time to Next Bit
            bit.w   #CCIS0,&CCTL0           ; RX on ISCCIB?
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
UART_RX     bit.w   #CAP,&CCTL0             ; Compare mode for start bit edge
            jz      RX_Bit                  ; Start bit edge?
RX_Edge     bic.w   #CAP,&CCTL0             ; Switch to Compare mode
            add.w   #Bitime_5,&CCR0         ; First databit 1.5 bits from edge
            bic.w   #SCG1+SCG0,0(SP)        ; !!! DCO needs to remain on !!!
            reti                            ;
RX_Bit      bit.w   #SCCI,&CCTL0            ; Get bit waiting in receive latch
            rrc.b   RXTXData                ; Store received bit
RX_Test     dec.w   BitCnt                  ; All bits sent (or received)?
            jnz     RX_Next                 ; Next bit?
;>>>>>>>>>> Decode of Received Byte Here <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
RX_Comp     bic.w   #CCIE,&CCTL0            ; All Bits RXed, Disable Interrupt
            bic.w   #CPUOFF,0(SP)           ; Decode Byte= Active in Mainloop
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
RX_Next     reti                            ;
                                            ;
;-------------------------------------------------------------------------------
;           Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int09"                ; Timer_A0 Vector
            .short  TA0_ISR                 ;
            .end

