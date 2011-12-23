;*******************************************************************************
;  MSP430x261x Demo - DMA0/1, rpt single transfer Mode UART1 9600 Auto RX/TX String, ACLK
;
;  Description: DMA1 is used to capture a 32 byte string from USART1. The
;  DMA1 interrupt is used to trigger DMA0 to echo back the received string.
;  USART1 is configured at 96008N1.
;  Level senstive trigger used for UTXIFG1 to prevent loss of initial edge
;  sensitive triggers - UTXIFG1 which is set at POR.
;  ACLK = 32768Hz = UCLK1, MCLK = SMCLK = default DCO 1 Mhz
;  Baud rate divider with 32768hz XTAL @9600 = 32768Hz/9600 = 3.41 (0003h)
;
;               MSP430x2619
;            -----------------
;        /|\|              XIN|-
;         | |                 | 32768Hz
;         --|RST          XOUT|-
;           |                 |
;           |             P3.6|------------>
;           |                 | 9600 - 8N1
;           |             P3.7|<------------
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x26x.h"
;-------------------------------------------------------------------------------
			.text	;Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #0850h,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop watchdog timer
SetupP3     bis.b   #BIT6+BIT7,&P3SEL       ; P3.6,7 = USART1 TXD/RXD
SetupUSCI1  bis.b   #UCSSEL_1,&UCA1CTL1     ; ACLK
            mov.b   #3,&UCA1BR0             ; 32768Hz 9600 32k/9600=3.41
            mov.b   #0,&UCA1BR1             ; 32768Hz 9600
            mov.b   #UCBRS_3,&UCA1MCTL      ; Modulation UCBRSx = 3
            bic.b   #UCSWRST,&UCA1CTL1      ; **Initialize USCI state machine**
Playback    movx.a  #01500h,&DMA0SA         ; Src = RAM memory
            movx.a  #UCA1TXBUF,&DMA0DA      ; Dst = UART1 TX Buffer
            mov.w   #010h,&DMA0SZ           ; Size in words
            mov.w   #DMASRCINCR_3+DMASBDB+DMALEVEL,&DMA0CTL ; Inc src, enable
Record      movx.a  #UCA1RXBUF,&DMA1SA      ; Src address = UART1 RX Buffer
            movx.a  #01500h,&DMA1DA         ; Dst address = RAM memory
            mov.w   #010h,&DMA1SZ           ; Size in byte
            mov.w   #DMADSTINCR_3+DMASBDB+DMAIE+DMAEN,&DMA1CTL ; Sng, config
            mov.w   #DMA1TSEL_9+DMA0TSEL_10,&DMACTL0 ; DMA1=URXIFG1,DMA0=UTXIFG1
            bis.w   #CPUOFF+GIE,SR          ; Enter LPM0, enable interrupts
;-------------------------------------------------------------------------------
DMA_ISR;    Common ISR for DMA/DAC12
;-------------------------------------------------------------------------------
            bic.w   #DMAIFG,&DMA1CTL        ; Clear DMA1 interrupt flag
            bis.w   #DMAEN,&DMA0CTL         ; Enable
            bis.w   #DMAEN,&DMA1CTL         ; (re)Enable
            reti                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect     ".int15"              ; DMA Vector
            .short   DMA_ISR                 ;
            .sect    ".reset"            ; POR, ext. Reset
            .short   RESET
            .end
