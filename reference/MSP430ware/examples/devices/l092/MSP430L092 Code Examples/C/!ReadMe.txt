File Name                       Description
----------------------------------------------------------------------------------------
msp430x09x_apool_adc_01.c       APOOL_ADC, conversion without Error Compensation, Sample A0
msp430x09x_apool_adc_02.c       APOOL_ADC, conversion with Overdrive Compensation, Sample A0
msp430x09x_apool_adc_03.c       APOOL_ADC, conversion with Offset Compensation, Sample A0
msp430x09x_apool_adc_04.c       APOOL_ADC, Vcc Monitoring
msp430x09x_apool_adc_05.c       APOOL_ADC, Timer_A0 Triggered
msp430x09x_apool_adc_06.c       APOOL_ADC, Sampled Temperature and Convert to oC 
msp430x09x_apool_adc_07.c       APOOL_ADC, Sample Multiple ADC Channels
msp430x09x_apool_comp_01.c      APOOL_COMPARATOR, Comparator in Compensated Mode, Compare signals on A0 and A2 
msp430x09x_apool_comp_02.c      APOOL_COMPARATOR, Comparator in Non Compensated Mode, Compare signals on A0 and A2 
msp430x09x_apool_comp_03.c      APOOL_COMPARATOR, Comparator in Compensated Mode,A0 compared with internal reference
msp430x09x_apool_dac_01.c       APOOL_DAC, Output Analog Signal with write to APINT; 
msp430x09x_apool_dac_02.c       APOOL_DAC, Output Triangle Wave using APINT with Timer Interrupt; 
msp430x09x_apool_dac_03.c       APOOL_DAC, Output Triangle Wave using APFRACT_H with Timer Interrupt;
msp430x09x_ccs_clkin.c          External Clock source for ACLK, MCLK, and SMCLK 
msp430x09x_ccs_hfosc.c          HF Clock source for ACLK(1MHz), MCLK(1MHz), and SMCLK(1MHz) 
msp430x09x_ccs_hfosc_01.c       HF Clock source for ACLK(~62.5kHz), MCLK(~250kHz), and SMCLK(~1MHz) 
msp430x09x_ccs_hfosc_02.c       HF Clock source for ACLK(~125kHz), MCLK(~62.5kHz), and SMCLK(~32kHz)
msp430x09x_ccs_hfosc_03.c       HF Clock source for ACLK(~32kHz), MCLK(~125kHz), and SMCLK(~62.5kHz)
msp430x09x_ccs_lfosc.c          LF Clock source for ACLK(~17.9kHz), MCLK(~17.9kHz), and SMCLK (~17.9kHz) 
msp430x09x_ccs_lfosc_01.c       LF Clock source for ACLK(~9kHz), MCLK(~2.2kHz), and SMCLK(~1kHz)
msp430x09x_ccs_lfosc_02.c       LF Clock source for ACLK(~4.5 kHz), MCLK(~17.9kHz), and SMCLK(~9kHz)
msp430x09x_ccs_lfosc_03.c       LF Clock source for ACLK(~17.9kHz), MCLK(~2.2kHz), and SMCLK (~4.5kHz)
msp430x09x_lpm3.c               LPM3, WDT ISR, 32kHz ACLK
msp430x09x_p1_01.c              Software Poll P1.3, Set P1.0 if P1.3 = 1
msp430x09x_p1_02.c              Software Port Interrupt Service on P1.3 from LPM4 which Toggles P1.0 
msp430x09x_p1_03.c              Software Port Interrupt Service on P1.3 from LPM4 with internal Pull up
msp430x09x_sys_01.c             Toggle P1.0 using system NMI ISR: VMA
msp430x09x_ta_01.c              Timer_A, Toggle P1.0, CCR0 Cont. Mode ISR, LFCLK/VLO SMCLK
msp430x09x_ta_02.c              Timer_A, Toggle P1.0, CCR0 Up Mode ISR, LFCLK/VLO SMCLK
msp430x09x_ta_03.c              Timer_A, Toggle P1.0, Overflow ISR, HFCLK/DCO SMCLK
msp430x09x_ta_04.c              Timer_A, Toggle P1.0, Overflow ISR, CLKIN SMCLK
msp430x09x_ta_06.c              Timer_A, Toggle P1.0, TACCR1 Cont. Mode ISR, HFCLK/DCO SMCLK
msp430x09x_ta_07.c              Timer_A, Toggle P1.5-6, Cont. Mode ISR, HFCLK/DCO SMCLK
msp430x09x_ta_08.c              Timer_A, Toggle P1.5-6, Cont. Mode ISR, CLKIN SMCLK
msp430x09x_ta_16.c              Timer_A, PWM TA1.1-2, Up Mode, HFCLK/DCO SMCLK
msp430x09x_ta_17.c              TimerA, PWM TA1.1-2, Up Mode, CLKIN SMCLK
msp430x09x_ta_18.c              Timer1_A3, PWM TA1.1-2, Up Mode, CLKIN ACLK
msp430x09x_ta_19.c              Timer1_A3, PWM TA1.1-2, Up/Down Mode, HFCLK/DCO SMCLK
msp430x09x_ta_20.c              Timer1_A3, PWM TA1.1-2, Up/Down Mode, 32kHz ACLK
msp430x09x_ta_21.c              Timer1_A3, PWM TA1.1-2, Up Mode, CLKIN ACLK
msp430x09x_wdt_01.c             WDT, Toggle P1.0, Interval Overflow ISR, LF-OSC ACLK
msp430x09x_wdt_02.c             WDT, Toggle P1.0, Interval Overflow ISR, HF-OSC SMCLK
msp430x09x_wdt_04.c             WDT, Reset on Invalid Address fetch, Toggle P1.0

