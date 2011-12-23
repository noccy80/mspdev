;******************************************************************************
;  MSP430x261x Demo - Basic Clock, VLO-Driven Timer with VLO Compensation
;
;  This example toggles P1.0 approx. every second, using a timer driven by the
;  VLO.  The VLO freq can vary between 4kHz-20kHz, so the timer compare value 
;  must be adjusted to compensate, in order to produce a one-second interval.  
;  So in effect, this code performs a kind of "calibration" of the VLO.  This 
;  is done by counting the number of 1MHz DCO pulses in one ACLK=VLO/8 period, 
;  assigned to dco_delta.  VLO is /8 in order to increase the number of DCO 
;  pulses in one ACLK pulse, increasing the resolution of the measurement, 
;  and therefore the accuracy of the one-second interval.  Since 1,000,000 
;  DCO pulses at 1MHz are required to produce a one-second interval, the 
;  number of VLO/8 pulses in one second is given by 1M/dco_delta.  This value 
;  is loaded into TACCR0 as the timer compare value.  
 
;  MSP430x2xx devices are shipped with calibration values in info memory that,
;  when used by software, allow the DCO to operate within approx. +/-1% of 
;  common values such as 1MHz.  (See the datasheet for add'l information.)  
;  Through the algorithm shown here, this accuracy is extended to the VLO.  An
;  additional source of error in this algorithm is that the VLO/8 freq will 
;  most likely not be evenly divisible by the DCO freq, and therefore up to 
;  one DCO pulse may be lost.  At nominal values, there are 400 1MHz DCO 
;  pulses in one 2.5kHz VLO/8 pulse, so losing one clock pulse produces 
;  ~0.25% error, in addition to the error tolerance of the calibrated DCO.  
;  ACLK = VLO/8, MCLK = SMCLK = 1MHz
;
;             MSP430F261x/241x
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |                 |
;            |       P1.0/TACLK|-->LED 1 second interrupt
;
;  
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x26x.h"
;-------------------------------------------------------------------------------
dco_delta	.usect ".bss",2
;-------------------------------------------------------------------------------
			.text							;Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #0850h,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP1     bis.b   #011h, &P1DIR           ; P1.0,4 outputs
            bis.b   #010h, &P1SEL           ; P1.4 = SMCLK

            calla   #measureVLO
            mov.w   r12, &dco_delta         ; dco delta = number of 1MHz cycles 
                                            ; in 8 VLO cycles
            ; Clock settings: DCO freq = 1MHz; ACLK = VLO/8
            
SetupC0     mov.w   #CCIE,&TACCTL0          ; TACCR0 interrupt enabled            
            ; TACCRO = 1000000/dco_delta 
            clr.w   r10
            clr.w   r11
            mov.w   #0ffffh, r15	    ; r15 = quotient
            mov.w   #04240h, r12	    ; 1000000 = 0F4240h in r12 and r13		
            mov.w   #00Fh, r13		    ;  = dividend
            mov.w   &dco_delta, r14	    ; r14 = divisor
Start       cmp.w   r12, r10
            jnc     Continue                ; unsigned number compare
            cmp.w   r13, r11
            jnc     Continue                ; unsigned number compare
            jmp     Stop       
Continue    mov.w   r10, r9
            add.w   r14,r9		    
            jnc     One
            inc.w   r11
One         add.w   r14,r10
            inc.w   r15
            jmp     Start   
Stop        mov.w   r15,&TACCR0
            ; 
SetupTA     mov.w   #TASSEL_1+MC_1,&TACTL   ; ACLK, upmode
            mov.b   #01h, P1OUT
Mainloop    bis.w   #LPM3+GIE,SR            ; Enter LPM3, interrupts enabled
            nop                             ; Required only for debugger            
            
;-------------------------------------------------------------------------------
measureVLO
;           returns: r12
;           -An int representing the number of 8MHz clock pulses in one VLO cycle
;-------------------------------------------------------------------------------       
            mov.b   &CALBC1_1MHZ, &BCSCTL1  ; Set range
            mov.b   &CALDCO_1MHZ, &DCOCTL   ; Set DCO step + modulation
            mov.w   #CM_1+CCIS_1+CAP,&TACCTL2 ; CAP, ACLK
            mov.w   #TASSEL_2+MC_2+TACLR, &TACTL; SMCLK, cont-mode, clear
            mov.b   #LFXT1S_2,    &BCSCTL3  ; ACLK = VLO
            clr.b   &BCSCTL2
            bis.b   #DIVA_3,      &BCSCTL1  ; ACLK=VLO/8
            
            bic.w   #CCIFG,       &TACCTL2  ; Clear capture flag
edge_one    bit.w   #CCIFG,       &TACCTL2  ; Test capture flag to skip 1st signal
            jz      edge_one
            bic.w   #CCIFG,       &TACCTL2  ; Clear capture flag

edge_two    bit.w   #CCIFG,       &TACCTL2  ; Test capture flag to skip 2nd signal
            jz      edge_two                ;
            mov.w   &TACCR2,      r13       ; save hardware captured value
            bic.w   #CCIFG,       &TACCTL2  ; Clear capture flag

edge_three  bit.w   #CCIFG,       &TACCTL2  ; Test capture flag to capture a good clock
            jz      edge_three              ;
            bic.w   #MC_3,        &TACTL    ; stop timer
            mov.w   &TACCR2,      r12
            sub.w   r13,          r12
            reta            
                                            ;
;------------------------------------------------------------------------------
TA0_ISR;    Toggle P1.0
;------------------------------------------------------------------------------
            xor.b   #BIT0,&P1OUT            ; Toggle P1.0
            reti                            ;	                                                   
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"	            ; MSP430 RESET Vector
            .short  RESET					;
            .sect	".int25"		        ; Timer_A0 Vector
            .short	TA0_ISR                ;
            .end
