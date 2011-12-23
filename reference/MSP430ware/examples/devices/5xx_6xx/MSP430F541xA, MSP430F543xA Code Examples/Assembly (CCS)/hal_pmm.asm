;*******************************************************************************
;   Function Library for setting the PMM
;
;   Texas Instruments, Inc
;   August 2009
;   Built with CCS4
;
;    Version 1.2
;    10/17/09
;
;    V1.0  Initial Version
;    V1.1  Adjustment to UG 
;    V1.2  Added return values
;*******************************************************************************
            .cdecls C,"MSP430x54xA.h"  			; Include device header file
            .cdecls C,"hal_PMM.h"  			; Include device header file

;------------------------------------------------------------------------------
 
;-------------------------------------------------------------------------------
            .text                           		; write in program Section
;-------------------------------------------------------------------------------

 .export SetVCore
;-------------------------------------------------------------------------------
SetVCore		;Subroutine sets VCorelevel to a choosed level (R12)
;       Input:  R12 (choosed VCoreLevel)
;		Output: R12	(error value)
;-------------------------------------------------------------------------------
 
 ; Define Variables as Offsett form SP			      
Error         	.set 	0							; unsigned int Error
ActiveLevel		.set	2							; unsigned int ActiveLevel
ChoosedLevel	.set	4							; unsigned int ChoosedLevel
 
           	SUB.W	#6,SP							;secure 3 words in Stack for Variables
           	CLR.W	Error(SP)						;initiate local V. Error
           	AND.W	#0x0003,R12						;Set mask for Max Level
           	MOV.W	R12,ChoosedLevel(SP)			;mov variable to stack
			MOV.W	&PMMCTL0,ActiveLevel(SP)		;get actual VCorelevel
           	AND.W	#0x0003,ActiveLevel(SP)			
           
STEP_VCO	CMP.B	ChoosedLevel(SP),ActiveLevel(SP);if((Level != ActiveLevel...
			JEQ		OR_LOWER						;
			TST.B	Error(SP)						;... && (Error == 0))...
			JNZ		OR_LOWER						;
			JMP		IF_L_AL
OR_LOWER	CMP.B	ChoosedLevel(SP),ActiveLevel(SP); ...|| (level < actlevel))
			JHS		EXIT_T_VCO						;
			
IF_L_AL		CMP.B	ChoosedLevel(SP),ActiveLevel(SP);if (level > actlevel) 
			JHS		ELSE_L_AL
			JMP		INC_1_STEP
			JMP		EX_STEP_VCO	
ELSE_L_AL	JMP		DEC_1_STEP

EX_STEP_VCO	MOV.B	&PMMCTL0,ActiveLevel(SP)		;get actual VCorelevel
           	AND.B	#0x03,ActiveLevel(SP)			;
			CMP.B	ChoosedLevel(SP),ActiveLevel(SP);if(Level != ActiveLevel...
			JEQ		EXIT_T_VCO						;
			TST.B	Error(SP)						;... && (Error == 0))
			JNZ		EXIT_T_VCO
			JMP		IF_L_AL							;-> modify VCore once more		
			
EXIT_T_VCO	MOV.B	Error(SP),R12
			ADD.W	#6,SP							;delete the Variables
			RETA	

INC_1_STEP	MOV.W	ActiveLevel(SP),R12
			INC.W	R12
			CALLA	#SetVCoreUp						;error = TrySetVCoreUp(level++)
			MOV.B	R12,Error(SP)
			JMP		EX_STEP_VCO	

DEC_1_STEP	MOV.W	ActiveLevel(SP),R12
			DEC.W	R12
			CALLA	#SetVCoreDown					;error = TrySetVCoreUp(level--)
			MOV.B	R12,Error(SP)
			JMP		EX_STEP_VCO	

 .export	SetVCoreUp
;-------------------------------------------------------------------------------
SetVCoreUp		;Subroutine sets VCorelevel to a higher level (R12)
;           Input:  R12 (ActiveVCoreLevel) 				R13 (working Register)
;			Output:	R12 (warning)
;-------------------------------------------------------------------------------

 ; Define Variables as Offsett form SP	
PMMRIE_backup		.set	0						;unsigned int PMMRIE_backup
SVSMHCTL_backup		.set	2						;unsigned int PMMRIE_backup

			PUSHX.A	R13
			SUB.W	#4,SP							;Reserve Space for local 2 Variables
			; Open PMM registers for write access
			MOV.B	#0xA5,&PMMCTL0_H
			
			; Disable dedicated Interrupts to prevent that needed flags will be cleared
			MOV.W	&PMMRIE,PMMRIE_backup(SP)
			BIC.W	#SVSMHDLYIE|SVSMLDLYIE|SVMLVLRIE|SVMHVLRIE|SVMHVLRPE,&PMMRIE
			; Set SVM highside to new level and check if a VCore increase is possible
			MOV.W	&SVSMHCTL,SVSMHCTL_backup(SP)
			BIC.W	#SVMHIFG|SVSMHDLYIFG,&PMMIFG
			MOV.W	R12,R13							;SVSMHCTL = SVMHE | SVMHFP | SVSMHRRL0 * level;
			ADD.W	#SVMHE|SVMHFP,R13			;
			MOV.W	R13,&SVSMHCTL				;
			; Wait until SVM highside is settled
WU_HDLYIFG	BIT.W	#SVSMHDLYIFG,&PMMIFG
			JZ		WU_HDLYIFG
			; Disable full-performance mode to save energy
			BIC.W	#SVMHFP,&SVSMHCTL
			
			; Check if a VCore increase is possible
			BIT.W	#SVMHIFG,&PMMIFG
			JNZ		NOT_POSSIB
			
POSSIBLE	; Set also SVS highside to new level	-> Vcc is high enough for a Vcore increase
			MOV.W	R12,R13							;SVSMHCTL |= SVSHE | SVSHRVL0 * level
			SWPB	R13								;level << 8
			ADD.W	#SVSHE,R13
			BIS.W	R13,&SVSMHCTL
			; Set SVM low side to new level
			MOV.W	R12,R13
			ADD.W	#SVMLE|SVMLFP,R13
			MOV.W	R13,&SVSMLCTL
			; Wait until SVM low side is settled
WU_LDLYIFG	BIT.W	#SVSMLDLYIFG,&PMMIFG
			JZ		WU_LDLYIFG
			; Clear already set flags
			BIC.W	#SVMLVLRIFG | SVMLIFG,&PMMIFG
			; Set VCore to new level
			MOV.B	R12,&PMMCTL0_L
			; Wait until new level reached
			BIT.W	#SVMLIFG,&PMMIFG
			JZ		VC_DONE
WU_LVLRIFG	BIT.W	#SVMLVLRIFG,&PMMIFG
			JZ		WU_LVLRIFG
			; Set also SVS/SVM low side to new level
VC_DONE		BIC.W	#SVSMLDLYIFG,&PMMIFG
			MOV.W	R12,R13							;SVSMLCTL |= SVSLE | (SVSLRVL0 * level);
			SWPB	R13								;level << 8
			ADD.W	#SVSLE,R13
			BIS.W	R13,&SVSMLCTL
			; wait for lowside delay flags
WU_LDLYIFG1	BIT.W	#SVSMLDLYIFG,&PMMIFG
			JZ		WU_LDLYIFG1
			; Disable full-performance mode to save energy
			BIC.W 	#SVMLFP,&SVSMLCTL
			; Clear all Flags
			BIC.W	#SVMHVLRIFG|SVMHIFG|SVSMHDLYIFG|SVMLVLRIFG|SVMLIFG|SVSMLDLYIFG,&PMMIFG
			; backup PMM-Interrupt-Register
			MOV.W	PMMRIE_backup(SP),&PMMRIE
			; Lock PMM registers for write access
			CLR.B	PMMCTL0_H
			MOV.W 	#PMM_STATUS_OK,R12					;return: OK 
			ADD.W	#4,SP							;delete the local Variables
			POPX.A	R13
			RETA
			
			
NOT_POSSIB	; recover the previous settings			-> Vcc is to low for a Vcore increase
			BIC.W	#SVSMHDLYIFG,&PMMIFG
			MOV.W	SVSMHCTL_backup(SP),&SVSMHCTL
			; Wait until SVM highside is settled
WU_HDLYIFG1	BIT.W	#SVSMHDLYIFG,&PMMIFG
			JZ		WU_HDLYIFG1
			; Clear all Flags
			BIC.W	#SVMHVLRIFG|SVMHIFG|SVSMHDLYIFG|SVMLVLRIFG|SVMLIFG|SVSMLDLYIFG,&PMMIFG
			; backup PMM-Interrupt-Register
			MOV.W	PMMRIE_backup(SP),&PMMRIE
			; Lock PMM registers for write access
			CLR.B	PMMCTL0_H
			MOV.W	#PMM_STATUS_ERROR,R12				;return: Error		
			
			ADD.W	#4,SP							;delete the local Variables
			POPX.A	R13
			RETA



 .export	SetVCoreDown
;-------------------------------------------------------------------------------
SetVCoreDown		;Subroutine sets VCorelevel to a lower level (R12)
;           Input:  R12 (ActiveVCoreLevel)				R13 (working Register)
;			Output:	R12 (Status)
;-------------------------------------------------------------------------------
			
 ; Define Variables as Offsett form SP	
PMMRIE_backup		.set	0						;unsigned int PMMRIE_backup			
			PUSHX.A R13
			SUB.W	#2,SP							;Reserve Space for local 1 Variable
			
			; Open PMM registers for write access
			MOV.B	#0xA5,&PMMCTL0_H
			
			; Disable dedicated Interrupts to prevent that needed flags will be cleared
			MOV.W	&PMMRIE,PMMRIE_backup(SP)
			BIC.W	#SVSMHDLYIE|SVSMLDLYIE|SVMLVLRIE|SVMHVLRIE|SVMHVLRPE,&PMMRIE
			; Set SVM highside to new level and check if a VCore increase is possible
			BIC.W	#SVMHIFG|SVSMHDLYIFG|SVMLIFG|SVSMLDLYIFG,&PMMIFG
			MOV.W	R12,R13							;SVSMHCTL = SVMHE | SVMHFP | SVSMHRRL0 * level;
			ADD.W	#SVMHE|SVMHFP,R13				;
			MOV.W	R13,&SVSMHCTL					;
			MOV.W	R12,R13							;SVSMLCTL = SVMLE | SVMLFP | SVSMLRRL0 * level;
			ADD.W	#SVMLE|SVMLFP,R13				;
			MOV.W	R13,&SVSMLCTL					;
			; Wait until SVM high side and SVM low side is settled
WD_DL_FG	BIT.W	#SVSMHDLYIFG|SVSMLDLYIFG,&PMMIFG
			JZ		WD_DL_FG
			; Disable full-performance mode to save energy
			BIC.W	#SVMHFP,&SVSMHCTL
			BIC.W	#SVMLFP,&SVSMLCTL
			; Set VCore to new level
			MOV.B	R12,&PMMCTL0_L
			; Set also SVS highside and SVS low side to new level
			BIC.W 	#SVSHIFG|SVSMHDLYIFG|SVSLIFG|SVSMLDLYIFG,&PMMIFG;
			MOV.W	R12,R13							;SVSMHCTL |= SVSHE | SVSHFP | (SVSHRVL0 * level);
			SWPB	R13								;level << 8
			ADD.W	#SVSHE|SVSHFP,R13
			BIS.W	R13,&SVSMHCTL
			MOV.W	R12,R13							;SVSMLCTL |= SVSLE | SVSLFP | (SVSLRVL0 * level);
			SWPB	R13								;level << 8
			ADD.W	#SVSLE|SVSLFP,R13
			BIS.W	R13,&SVSMLCTL
			; Wait until SVS high side and SVS low side is settled
WD_DL_FG1	BIT.W	#SVSMHDLYIFG|SVSMLDLYIFG,&PMMIFG
			JZ		WD_DL_FG1
			; Disable full-performance mode to save energy
			BIC.W	#SVSHFP,&SVSMHCTL
			BIC.W	#SVSLFP,&SVSMLCTL
			; Clear all Flags
			BIC.W	#SVMHVLRIFG|SVMHIFG|SVSMHDLYIFG|SVMLVLRIFG|SVMLIFG|SVSMLDLYIFG,&PMMIFG
			; backup PMM-Interrupt-Register
			MOV.W	PMMRIE_backup(SP),&PMMRIE
			; Lock PMM registers for write access
			CLR.B	PMMCTL0_H
			BIT.W	#SVMHIFG,&PMMIFG	
			JZ		RETURN0
			MOV.W	#PMM_STATUS_ERROR,R12				;Highside is still to low for the adjusted VCore Level
			JMP		EX_SET_D
RETURN0		MOV.W	#PMM_STATUS_OK,R12                 ; Return: OK
EX_SET_D	; Lock PMM registers for write access
			CLR.B	PMMCTL0_H
			ADD.W	#2,SP							;delete the local Variable
            POPX.A  R13
			RETA		
                  
;################################################################################################################           
                         
            .end   
