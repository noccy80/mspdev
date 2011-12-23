;******************************************************************************
;   MSP430x66xx Demo - Enters LPM3 with ACLK =VLO;  LFXT1, REF0 disabled, 
;                      VUSB LDO and SLDO disabled, SVS default state
;
;   Description: Configure ACLK = VLO and enter LPM3. Measure current.
;   ACLK = VLO = 12kHz, MCLK = SMCLK = default DCO
; 
;           MSP430F663x
;         ---------------
;     /|\|               |
;      | |               |
;      --|RST            |
;        |               |
;        |               |  
;        |               |
;
;   Priya Thanigai
;   Texas Instruments Inc.
;   August 2011
;   Built with CCS V5
;******************************************************************************
            .cdecls C,LIST,"msp430f6638.h"

;-------------------------------------------------------------------------------
            .global _main
            .text                           ; Assemble to Flash memory
;-------------------------------------------------------------------------------
_main
RESET       mov.w   #0x63FE,SP              ; Initialize stackpointer
            mov.w   #WDTPW + WDTHOLD,&WDTCTL; Stop WDT

            mov.w   #SELA_1,&UCSCTL4

            mov.b   #0xFF,&P1DIR
            mov.b   #0xFF,&P2DIR
            mov.b   #0xFF,&P3DIR
            mov.b   #0xFF,&P4DIR
            mov.b   #0xFF,&P5DIR
            mov.b   #0xFF,&P6DIR
            mov.b   #0xFF,&P7DIR
            mov.b   #0xFF,&P8DIR
            mov.b   #0xFF,&P9DIR
            mov.w   #0xFF,&PJDIR
            clr.b   &P1OUT
            clr.b   &P2OUT
            clr.b   &P3OUT
            clr.b   &P4OUT
            clr.b   &P5OUT
            clr.b   &P6OUT
            clr.b   &P7OUT
            clr.b   &P8OUT
            clr.b   &P9OUT
            clr.w   &PJOUT
            ; disable USB LDOs           
            mov.w   #0x9628,&USBKEYPID
            bic.w   #SLDOEN+VUSBEN,&USBPWRCTL
            mov.w   #0x9600,&USBKEYPID
            
            ; disable SVS
            mov.b   #PMMPW_H,&PMMCTL0_H
            bic.w   #SVMHE+SVSHE,&SVSMHCTL
            bic.w   #SVMLE+SVSLE,&SVSMLCTL
            
            ; blink LED a few times before entering LPM
            mov.w   #0Fh,R8
Blink       dec.w   R8
            jz      Mainloop            
            xor.b   #BIT0,&P1OUT
            
Wait        mov.w   #05000,R15             ; Delay to R15
L1          dec.w   R15                     ; Decrement R15
            jnz     L1                      ; Delay over?
            
            jmp     Blink
           
            clr.b   &P1OUT
Mainloop    bis.w   #LPM3,SR                ; Enter LPM3
            nop                             ; For debugger

;-------------------------------------------------------------------------------
                  ; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; POR, ext. Reset
            .short  RESET
            .end
