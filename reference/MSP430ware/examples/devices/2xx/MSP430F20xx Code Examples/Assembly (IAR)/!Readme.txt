File Name                          Description
----------------------------------------------------------------------------------------
msp430x20x1_ca_01.s43              Comp_A, Output Reference Voltages on P1.1
msp430x20x1_ca_02.s43              Comp_A, Detect Threshold, Set P1.0 if P1.1 > 0.25*Vcc
msp430x20x1_ca_03.s43              Comp_A, Simple 2.2V Low Battery Detect
msp430x20x2_adc10_01.s43           ADC10, Sample A0, Set P1.0 if A0 > 0.5*AVcc
msp430x20x2_adc10_02.s43           ADC10, Sample A1, 1.5V Ref, Set P1.0 if A1 > 0.2V
msp430x20x2_adc10_03.s43           ADC10, ADC10, Sample A10 Temp, Set P1.0 if Temp ++ ~2C
msp430x20x2_adc10_04.s43           ADC10, ADC10, Sample A1, Signed, Set P1.0 if A1 > 0.5*AVcc
msp430x20x2_adc10_05.s43           ADC10, ADC10, Sample A11, Lo_Batt, Set P1.0 if AVcc < 2.3V
msp430x20x2_adc10_06.s43           ADC10, ADC10, Output Internal Vref on P1.4 & ADCCLK on P1.3
msp430x20x2_adc10_07.s43           ADC10, DTC Sample A1 32x, AVcc, Repeat Single, DCO
msp430x20x2_adc10_08.s43           ADC10, ADC10, DTC Sample A1 32x, 1.5V, Repeat Single, DCO
msp430x20x2_adc10_09.s43           ADC10, ADC10, DTC Sample A10 32x, 1.5V, Repeat Single, DCO
msp430x20x2_adc10_10.s43           ADC10, ADC10, DTC Sample A3-01, AVcc, Single Sequence, DCO
msp430x20x2_adc10_11.s43           ADC10, ADC10, Sample A1, 1.5V, TA1 Trig, Set P1.0 if > 0.5V
msp430x20x2_adc10_12.s43           ADC10, Sample A7, 1.5V, TA1 Trig, Ultra-Low Pwr
msp430x20x2_adc10_13.s43           ADC10, DTC Sample A1 32x, AVcc, TA0 Trig, DCO
msp430x20x2_adc10_14.s43           ADC10, DTC Sample A1-0 16x, AVcc, Repeat Seq, DCO
msp430x20x2_adc10_16.s43           ADC10, ADC10, DTC Sample A0 -> TA1, AVcc, DCO
msp430x20x2_adc10_temp.s43         ADC10, Sample A10 Temp and Convert to oC and oF
msp430x20x3_1.s43                  Software Toggle P1.0
msp430x20x3_1_vlo.s43              Software Toggle P1.0, MCLK = VLO/8
msp430x20x3_clks.s43               Basic Clock, Output Buffered SMCLK, ACLK and MCLK/10
msp430x20x3_flashwrite_01.s43      Flash In-System Programming, Copy SegC to SegD
msp430x20x3_LFxtal_nmi.s43         LFXT1 Oscillator Fault Detection
msp430x20x3_lpm3.s43               Basic Clock, LPM3 Using WDT ISR, 32kHz ACLK
msp430x20x3_lpm3_vlo.s43           Basic Clock, LPM3 Using WDT ISR, VLO ACLK
msp430x20x3_nmi.s43                Basic Clock, Configure RST/NMI as NMI
msp430x20x3_P1_01.s43              Software Poll P1.4, Set P1.0 if P1.4 = 1
msp430x20x3_P1_02.s43              Software Port Interrupt on P1.4 from LPM4
msp430x20x3_P1_03.s43              Poll P1 With Software with Internal Pull-up
msp430x20x3_P1_04.s43              P1 Interrupt from LPM4 with Internal Pull-up
msp430x20x3_sd16A_01.s43           SD16A, Sample A1+ Continuously, Set P1.0 if > 0.3V
msp430x20x3_sd16A_02.s43           SD16, Using the Integrated Temperature Sensor
msp430x20x3_sd16A_03.s43           SD16A takes a sample of a single sequence of channels
msp430x20x3_ta_01.s43              Timer_A, Toggle P1.0, CCR0 Cont. Mode ISR, DCO SMCLK
msp430x20x3_ta_02.s43              Timer_A, Toggle P1.0, CCR0 Up Mode ISR, DCO SMCLK
msp430x20x3_ta_03.s43              Timer_A, Toggle P1.0, Overflow ISR, DCO SMCLK
msp430x20x3_ta_04.s43              Timer_A, Toggle P1.0, Overflow ISR, 32kHz ACLK
msp430x20x3_ta_05.s43              Timer_A, Toggle P1.0, CCR0 Up Mode ISR, 32kHz ACLK
msp430x20x3_ta_06.s43              Timer_A, Toggle P1.0, CCR1 Cont. Mode ISR, DCO SMCLK
msp430x20x3_ta_07.s43              Timer_A, Toggle P1.0-3, Cont. Mode ISR, DCO SMCLK
msp430x20x3_ta_08.s43              Timer_A, Toggle P1.0-2, Cont. Mode ISR, 32kHz ACLK
msp430x20x3_ta_10.s43              Timer_A, Toggle P1.1/TA0, Up Mode, DCO SMCLK
msp430x20x3_ta_11.s43              Timer_A, Toggle P1.1/TA0, Up Mode, 32kHz ACLK
msp430x20x3_ta_13.s43              Timer_A, Toggle P1.1/TA0, Up/Down Mode, DCO SMCLK
msp430x20x3_ta_14.s43              Timer_A, Toggle P1.1/TA0, Up/Down Mode, 32kHz ACLK
msp430x20x3_ta_16.s43              Timer_A, PWM TA1, Up Mode, DCO SMCLK
msp430x20x3_ta_17.s43              Timer_A, PWM TA1, Up Mode, 32kHz ACLK
msp430x20x3_ta_19.s43              Timer_A, PWM TA1, Up/Down Mode, DCO SMCLK
msp430x20x3_ta_20.s43              Timer_A, PWM TA1-2, Up/Down Mode, 32kHz ACLK
msp430x20x3_ta_uart2400.s43        Timer_A, Ultra-Low Pwr UART 2400 Echo, 32kHz ACLK
msp430x20x3_usi_01.s43             USICNT Used as a One-Shot Timer Function, DCO SMCLK
msp430x20x3_usi_02.s43             SPI full-Duplex 3-wire Master
msp430x20x3_usi_03.s43             SPI full-Duplex 3-wire Slave
msp430x20x3_usi_04.s43             USI SPI Interface to HC165/164 Shift Registers
msp430x20x3_usi_05.s43             USI SPI Interface to TLC549 8-bit ADC
msp430x20x3_usi_06.s43             USI I2C Master Receiver, single byte
msp430x20x3_usi_07.s43             USI I2C Master Transmitter, single byte
msp430x20x3_usi_08.s43             USI I2C Slave Receiver, single byte
msp430x20x3_usi_09.s43             USI I2C Slave Transmitter, single byte
msp430x20x3_wdt_01.s43             WDT, Toggle P1.0, Interval Overflow ISR, DCO SMCLK
msp430x20x3_wdt_02.s43             WDT, Toggle P1.0, Interval Overflow ISR, 32kHz ACLK
msp430x20x3_wdt_04.s43             WDT+ Failsafe Clock, DCO SMCLK
msp430x20x3_wdt_05.s43             Reset on Invalid Address fetch, Toggle P1.0
msp430x20x3_wdt_06.s43             WDT+ Failsafe Clock, 32kHz ACLK
msp430x20xx_dco_flashcal.s43       DCO Calibration Constants Programmer

