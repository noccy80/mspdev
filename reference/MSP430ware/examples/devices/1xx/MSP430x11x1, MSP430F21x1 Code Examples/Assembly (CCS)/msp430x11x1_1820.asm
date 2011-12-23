;*******************************************************************************
;   MSP430x11x1 Demo - Software 1-Wire Interface DS1820, .set P1.0 if > 30C
;
;   Description: 1-wire communication with DS1820 temperature sensor is
;   demonstrated. If temperature read > 30.0c (01E0h), P1.0 is set, else reset.
;   Default 12-bit temperature mode read as two bytes and packed into DATA1W.
;   Only two byte temperature data is read from DS1820, balance of DS1820
;   scratchpad is ignored. 1-wire timing is important and the software is
;   written assuming MCLK ~800kHz. Normal mode is LPM3 with WDT triggering
;   measurement interval every 1s.
;   ACLK = LFXT1 = 32768, MCLK = SMCLK = default DCO ~800k
;   ;* External watch crystal installed on XIN XOUT is required for ACLK *//	
;
;                                   MSP430F1121
;          /|\               /|\  -----------------
;           |   DS1820       4.7k|              XIN|-
;           |   -------       |  |                 | 32kHz
;           ---|VDD  DQ|<-----+->|P2.0         XOUT|-
;           ---|GND    |         |                 |
;          \|/  -------          |             P1.0|-->LED
;
;
;    CPU registers used
DATA1W  .equ     R4
BIT1W   .equ     R5
;
;   Definitions for 1-wire bus
DQ          .equ    001h                    ; P2.0 controls DQ line (pull-up)
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
RESET       mov.w   #300h,SP                ; Initialize stackpointer
Setup       mov.w   #WDT_ADLY_1000,&WDTCTL  ; WDT 1s, ACLK, interval timer
            bis.b   #WDTIE,&IE1             ; Enable WDT interrupt
SetupP1     bis.b   #001h,&P1DIR            ; P1.0 output
SetupP2	    bic.b   #001h,&P2OUT	        ; Make sure P2.0 output latch = 0
                                            ;					
Mainloop    bis.w   #LPM3+GIE,SR            ; Enter LPM3 w/ interrupts
            call    #Reset_1W               ; DS1820 Reset
            mov.b   #0CCh,DATA1W            ; DS1820 command to skip ROM
            call    #Write_1W               ;
            mov.b   #044h,DATA1W            ; DS1820 comand to convert temp
            call    #Write_1W               ;
                                            ;
            call    #Reset_1W               ; DS1820 Reset
            mov.b   #0CCh,DATA1W            ; DS1820 command to skip ROM
            call    #Write_1W               ;
            mov.b   #0BEh,DATA1W            ; DS1820 command to read scratchpad
            call    #Write_1W               ;
            call    #Read_1W                ; DS1820 LSB read
            push.w  DATA1W                  ; TOS = 00|LSB
            call    #Read_1W                ; DS1820 LSB read
            swpb    DATA1W                  ; DATA1W = MSB|00
            add.w   @SP+,DATA1W             ; DATA1W = MSB|LSB
                                            ;
Temp_test   bic.b   #01h,&P1OUT             ; P1.0 = 0
            cmp.w   #01E0h,DATA1W           ; DATA1W > 30.0c?
            jlo     Mainloop                ; Again
            bis.b   #01h,&P1OUT             ; P1.0 = 1
            jmp     Mainloop                ; Again
                                            ;
;-------------------------------------------------------------------------------
Reset_1W;   Subroutine to Reset 1-wire device and detect presence
;-------------------------------------------------------------------------------
            bis.b   #DQ,&P2DIR              ;
            mov     #240,R15                ; ~ 720us delay
            call    #Delay_R15              ;
            bic.b   #DQ,&P2DIR              ;
            call    #Delay_60us             ; ~ 60us delay subroutine
Rxx         bit.b   #DQ,&P2IN               ; Check for presence
            jc      Rxx                     ;
                                            ;
            mov     #160,R15                ; ~ 480us Delay
            call    #Delay_R15              ;
            ret                             ;
                                            ;
;-------------------------------------------------------------------------------
Write_1W;   enter   DATA1W = 00 - FF 1-wire data to write
;                    BIT1W = xx
;-------------------------------------------------------------------------------
            mov.w   #8h,BIT1W               ;
TX_1W_Bit   rrc.b   DATA1W                  ;
            jc      TX_1W_1                 ;
TX_1W_0     bis.b   #DQ,&P2DIR              ;
            call    #Delay_60us             ; ~ 60us delay subroutine
            bic.b   #DQ,&P2DIR              ;
            jmp     TX_1W_x                 ;
TX_1W_1     bis.b   #DQ,&P2DIR              ;
            bic.b   #DQ,&P2DIR              ;
            call    #Delay_60us             ; ~ 60us delay subroutine
TX_1W_x     dec.w   BIT1W                   ;
            jnz     TX_1W_Bit               ;
            ret                             ;
                                            ;
;-------------------------------------------------------------------------------
Read_1W;    enter   DATA1W = xx
;                    BIT1W = xx
;           exit    DATA1W = 00 - FF 1-wire data read
;                    BIT1W = xx
;-------------------------------------------------------------------------------
            mov.w   #8h,BIT1W               ;
RX_1W_Bit   bis.b   #DQ,&P2DIR              ;
            bic.b   #DQ,&P2DIR              ;
            nop                             ;
            nop                             ;
            bit.b   #DQ,&P2IN               ;
            rrc.b   DATA1W                  ;
            call    #Delay_60us             ; ~ 60us delay subroutine
            dec.w   BIT1W                   ;
            jnz     RX_1W_Bit               ;
            ret                             ;
                                            ;
;-------------------------------------------------------------------------------
Delay_60us  mov.w   #20,R15
;-------------------------------------------------------------------------------
Delay_R15   dec.w   R15                     ;
            jnz     Delay_R15               ;
            ret                             ;
                                            ;
;-------------------------------------------------------------------------------
WDT_ISR  ;  Exit LPM3 on reti
;-------------------------------------------------------------------------------
            bic.w   #LPM3,0(SP)             ; Clear LPM3 from TOS
            reti                            ;
                                            ;
;-------------------------------------------------------------------------------
;           Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int10"                ; WDT Vector
            .short  WDT_ISR                 ;
            .end
