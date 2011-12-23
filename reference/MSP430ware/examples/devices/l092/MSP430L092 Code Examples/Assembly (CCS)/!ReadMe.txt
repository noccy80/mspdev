File Name                         Description
----------------------------------------------------------------------------------------
msp430x09x_apool_adc_01.asm       APOOL_ADC, conversion without Error Compensation, Sample A0
msp430x09x_apool_adc_02.asm       APOOL_ADC, conversion with Overdrive Compensation, Sample A0
msp430x09x_apool_adc_03.asm       APOOL_ADC, conversion with Offset Compensation, Sample A0
msp430x09x_apool_adc_04.asm       APOOL_ADC, Vcc Monitoring
msp430x09x_apool_adc_05.asm       APOOL_ADC, Timer_A0 Triggered
msp430x09x_apool_adc_06.asm       APOOL_ADC, Sampled Temperature and Convert to oC 
msp430x09x_apool_adc_07.asm       APOOL_ADC, Sample Multiple ADC Channels
msp430x09x_apool_comp_01.asm      APOOL_COMPARATOR, Comparator in Compensated Mode, Compare signals on A0 and A2 
msp430x09x_apool_comp_02.asm      APOOL_COMPARATOR, Comparator in Non Compensated Mode, Compare signals on A0 and A2 
msp430x09x_apool_comp_03.asm      APOOL_COMPARATOR, Comparator in Compensated Mode,A0 compared with internal reference
msp430x09x_apool_dac_01.asm       APOOL_DAC, Output Analog Signal with write to APINT; 
msp430x09x_apool_dac_02.asm       APOOL_DAC, Output Triangle Wave using APINT with Timer Interrupt; 
msp430x09x_apool_dac_03.asm       APOOL_DAC, Output Triangle Wave using APFRACT_H with Timer Interrupt;
msp430x09x_ccs_clkin.asm          External Clock source for ACLK, MCLK, and SMCLK 
msp430x09x_ccs_hfosc.asm          HF Clock source for ACLK(1MHz), MCLK(1MHz), and SMCLK(1MHz) 
msp430x09x_ccs_hfosc_01.asm       HF Clock source for ACLK(~62.5kHz), MCLK(~250kHz), and SMCLK(~1MHz) 
msp430x09x_ccs_hfosc_02.asm       HF Clock source for ACLK(~125kHz), MCLK(~62.5kHz), and SMCLK(~32kHz)
msp430x09x_ccs_hfosc_03.asm       HF Clock source for ACLK(~32kHz), MCLK(~125kHz), and SMCLK(~62.5kHz)
msp430x09x_ccs_lfosc.asm          LF Clock source for ACLK(~17.9kHz), MCLK(~17.9kHz), and SMCLK (~17.9kHz) 
msp430x09x_ccs_lfosc_01.asm       LF Clock source for ACLK(~9kHz), MCLK(~2.2kHz), and SMCLK(~1kHz)
msp430x09x_ccs_lfosc_02.asm       LF Clock source for ACLK(~4.5 kHz), MCLK(~17.9kHz), and SMCLK(~9kHz)
msp430x09x_ccs_lfosc_03.asm       LF Clock source for ACLK(~17.9kHz), MCLK(~2.2kHz), and SMCLK (~4.5kHz)
msp430x09x_lpm3.asm               LPM3, WDT ISR, 32kHz ACLK
msp430x09x_p1_01.asm              Software Poll P1.3, Set P1.0 if P1.3 = 1
msp430x09x_p1_02.asm              Software Port Interrupt Service on P1.3 from LPM4 which Toggles P1.0 
msp430x09x_p1_03.asm              Software Port Interrupt Service on P1.3 from LPM4 with internal Pull up
msp430x09x_sys_01.asm             Toggle P1.0 using system NMI ISR: VMA
msp430x09x_ta_01.asm              Timer_A, Toggle P1.0, CCR0 Cont. Mode ISR, LFCLK/VLO SMCLK
msp430x09x_ta_02.asm              Timer_A, Toggle P1.0, CCR0 Up Mode ISR, LFCLK/VLO SMCLK
msp430x09x_ta_03.asm              Timer_A, Toggle P1.0, Overflow ISR, HFCLK/DCO SMCLK
msp430x09x_ta_04.asm              Timer_A, Toggle P1.0, Overflow ISR, CLKIN SMCLK
msp430x09x_ta_06.asm              Timer_A, Toggle P1.0, TACCR1 Cont. Mode ISR, HFCLK/DCO SMCLK
msp430x09x_ta_07.asm              Timer_A, Toggle P1.5-6, Cont. Mode ISR, HFCLK/DCO SMCLK
msp430x09x_ta_08.asm              Timer_A, Toggle P1.5-6, Cont. Mode ISR, CLKIN SMCLK
msp430x09x_ta_16.asm              Timer_A, PWM TA1.1-2, Up Mode, HFCLK/DCO SMCLK
msp430x09x_ta_17.asm              TimerA, PWM TA1.1-2, Up Mode, CLKIN SMCLK
msp430x09x_ta_18.asm              Timer1_A3, PWM TA1.1-2, Up Mode, CLKIN ACLK
msp430x09x_ta_19.asm              Timer1_A3, PWM TA1.1-2, Up/Down Mode, HFCLK/DCO SMCLK
msp430x09x_ta_20.asm              Timer1_A3, PWM TA1.1-2, Up/Down Mode, 32kHz ACLK
msp430x09x_ta_21.asm              Timer1_A3, PWM TA1.1-2, Up Mode, CLKIN ACLK
msp430x09x_wdt_01.asm             WDT, Toggle P1.0, Interval Overflow ISR, LF-OSC ACLK
msp430x09x_wdt_02.asm             WDT, Toggle P1.0, Interval Overflow ISR, HF-OSC SMCLK
msp430x09x_wdt_04.asm             WDT, Reset on Invalid Address fetch, Toggle P1.0

