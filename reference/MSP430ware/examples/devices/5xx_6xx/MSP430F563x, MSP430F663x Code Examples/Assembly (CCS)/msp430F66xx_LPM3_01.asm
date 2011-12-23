;******************************************************************************
;   MSP430x66xx Demo - Enters LPM3 with ACLK = LFXT1, REF0 disabled, 
;                    VUSB LDO and SLDO disabled, SVS disabled
;
;   Description: Configure ACLK = LFXT1 and enters LPM3. Measure current.
;   ACLK = LFXT1 = 32kHz, MCLK = SMCLK = default DCO
;   NOTE: CONNECT VBAT TO VCC WHEN BACKUP SUPPLY IS NOT AVAILABLE.
; 
;           MSP430F663x
;         ---------------
;     /|\|               |
;      | |               |
;      --|RST            |
;        |          Vbat |---
;        |               |  |
;        |          Vcc  |---
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

Test_LOCKIO bit.w   #LOCKIO,&BAKCTL
            jz      Clock_Init
            bic.w   #LOCKIO,&BAKCTL
            jmp     Test_LOCKIO
Clock_Init            
            bic.w   #XT1OFF,&UCSCTL6        ; XT1 On
            bis.w   #XCAP_3,&UCSCTL6        ; Internal load cap

            ; Loop until XT1,XT2 & DCO stabilizes
do_while    bic.w   #XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG,&UCSCTL7
                                            ; Clear XT2,XT1,DCO fault flags
            bic.w   #OFIFG,&SFRIFG1         ; Clear fault flags
            bit.w   #OFIFG,&SFRIFG1         ; Test oscillator fault flag
            jc      do_while

            bic.w   #XT1DRIVE_3,&UCSCTL6    ; XT1 stable, reduce drive strength
            bic.w   #SELA0+SELA1+SELA2,&UCSCTL4

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
            
Wait        mov.w   #050000,R15             ; Delay to R15
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
