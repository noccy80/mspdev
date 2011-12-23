;******************************************************************************
;   MSP-FET430P140 Demo - I2C, Master Intf. to TMP100, .set P1.0 if Temp > 28C
;
;   Description: I2C interface to TMP100 temperature sensor in 9-bit mode.
;   Timer_A CCR0 interrupt is used to wake up and read the two bytes of
;   the TMP100 temperature register. If the temperature is greater than 28C,
;   P1.0 is set, else reset. CPU is normally off and used only during TA_ISR.
;   ACLK = n/a, MCLK = SMCLK = TACLK = I2CCLOCK = default DCO ~800kHz
;   //* MSP430F169 Device Required *//
;
;
;          /|\           /|\ /|\
;           |   TMP100   10k 10k     MSP430F169
;           |   -------   |   |  -----------------
;           +--|Vcc SDA|<-|---+>|P3.1         P1.0|---> LED
;           |  |       |  |     |                 |
;           +--|A1,A0  |  |     |                 |
;              |       |  |     |                 |
;           ---|Vss SCL|<-+-----|P3.3             |
;          \|/  -------         |                 |
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
            bis.b   #01h,&P1DIR             ;
SetupP3     bis.b   #0Ah,&P3SEL             ; Assign I2C pins to module
SetupI2C    bis.b   #SYNC+I2C,&U0CTL        ; Switch USART0 to I2C mode
            bic.b   #I2CEN, U0CTL           ; Recommended I2C init procedure
            mov.b   #I2CWORD+I2CSSEL1,&I2CTCTL ; SMCLK, word mode
            mov.b   #003h,&I2CSCLH          ; High period of SCL
            mov.b   #003h,&I2CSCLL          ; Low period of SCL
            mov.b   #002h,&I2CNDAT          ; transfer two bytes
            mov.w   #04Eh,&I2CSA            ; .set slave address
            bis.b   #I2CEN,&U0CTL           ; Enable I2C
            mov.w   #CCIE,&CCTL0            ; CCR0 interrupt enabled
            mov.w   #TASSEL_2+ MC_2,&TACTL  ; SMCLK, contmode
                                            ;
Mainloop    bis.w   #CPUOFF+GIE,SR          ; CPU off, interrupts enabled
            nop                             ; Required for debugger
                                            ;
;------------------------------------------------------------------------------
TA0_ISR;
;------------------------------------------------------------------------------
            mov.w   &I2CDRW,R4              ; R4 = Temp data
            swpb    R4                      ;
            cmp.w   #01E00h,R4              ;  > 28c?
            jlo     Low_Temp                ;
            bis.b   #01h,&P1OUT             ; P1.0 = 1
            jmp     Next_Temp               ;
Low_Temp    bic.b   #01h,&P1OUT             ; P1.0 = 0
Next_Temp   bis.b   #MST,&U0CTL             ; Master
            bis.b   #I2CSTT+I2CSTP,&I2CTCTL ; Read, ST, SP (clears MST)
            reti                            ;		
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int06"                ; Timer_A0 Vector
            .short  TA0_ISR                 ;
            .end