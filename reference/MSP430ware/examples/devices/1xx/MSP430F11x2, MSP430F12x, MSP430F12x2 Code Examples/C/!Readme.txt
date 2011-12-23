File Name                  Description
----------------------------------------------------------------------------------------
fet120_1.c                 Software Toggle P1.0
fet120_adc10_01.c          ADC10, Sample A0, AVcc Ref, Set P1.0 if > 0.5*AVcc
fet120_adc10_02.c          ADC10, Sample A0, 1.5V Ref, Set P1.0 if > 0.2V
fet120_adc10_03.c          ADC10, Sample A10 Temp, Set P1.0 if Temp ++ ~2C
fet120_adc10_04.c          ADC10, Sample A0, Signed, Set P1.0 if > 0.5*AVcc
fet120_adc10_05.c          ADC10, Sample A11, Lo_Batt, Set P1.0 if < 2.3V
fet120_adc10_06.c          ADC10, Output Internal Vref on P2.4 & ADCCLK on P1.0
fet120_adc10_07.c          ADC10, DTC Sample A0 64x, AVcc, Repeat Single, DCO
fet120_adc10_08.c          ADC10, DTC Sample A0 64x, 1.5V, Repeat Single, DCO
fet120_adc10_09.c          ADC10, DTC Sample A10 64x, 1.5V, Repeat Single, DCO
fet120_adc10_10.c          ADC10, DTC Sample A2-0, AVcc, Single Sequence, DCO
fet120_adc10_11.c          ADC10, Sample A0, 1.5V, TA1 Trig, Set P1.0 if > 0.5V
fet120_adc10_12.c          ADC10, Sample A7, 1.5V, TA1 Trig, Ultra-Low Pwr
fet120_adc10_13.c          ADC10, DTC Sample A1 32x, AVcc, TA0 Trig, DCO
fet120_adc10_14.c          ADC10, DTC Sample A1-0 32x, AVcc, Repeat Seq, DCO
fet120_adc10_15.c          ADC10, DTC Sample A10 32x to Flash, Int Ref, DCO
fet120_adc10_temp.c        ADC10, Sample A10 Temp and Convert to oC and oF
fet120_clks.c              Basic Clock, Output Buffered SMCLK, ACLK and MCLK/10
fet120_flash_write.c       Flash In-System Programming, Copy SegA to SegB
fet120_fll_01.c            Basic Clock, Implement Auto RSEL SW FLL
fet120_fll_02.c            Basic Clock, Implement Cont. SW FLL with Auto RSEL
fet120_hfxtal.c            Basic Clock, MCLK Sourced from HF XTAL
fet120_lpm3.c              Basic Clock, LPM3 Using WDT ISR, 32kHz ACLK
fet120_nmi.c               Basic Clock, Configure RST/NMI as NMI
fet120_rosc.c              DCOCLK Biased with External Resistor Rosc
fet120_spi0_016x.c         USART0, SPI Interface with HC165/164 Shift Registers
fet120_spi0_mstr.c         USART0, SPI 3-Wire Master
fet120_spi0_slav.c         USART0, SPI 3-Wire Slave
fet120_ta_01.c             Timer_A, Toggle P1.0, CCR0 Cont. Mode ISR, DCO SMCLK
fet120_ta_02.c             Timer_A, Toggle P1.0, CCR0 Up Mode ISR, DCO SMCLK
fet120_ta_03.c             Timer_A, Toggle P1.0, Overflow ISR, DCO SMCLK
fet120_ta_04.c             Timer_A, Toggle P1.0, Overflow ISR, 32kHz ACLK
fet120_ta_05.c             Timer_A, Toggle P1.0, CCR0 Up Mode ISR, 32kHz ACLK
fet120_ta_06.c             Timer_A, Toggle P1.0, CCR1 Cont. Mode ISR, DCO SMCLK
fet120_ta_07.c             Timer_A, Toggle P1.0-3, Cont. Mode ISR, DCO SMCLK
fet120_ta_08.c             Timer_A, Toggle P1.0-3, Cont. Mode ISR, 32kHz ACLK
fet120_ta_09.c             Timer_A, Toggle P1.0-3, Cont. Mode ISR, HF XTAL ACLK
fet120_ta_10.c             Timer_A, Toggle P1.1/TA0, Up Mode, DCO SMCLK
fet120_ta_11.c             Timer_A, Toggle P1.1/TA0, Up Mode, 32kHz ACLK
fet120_ta_12.c             Timer_A, Toggle P1.1/TA0, Up Mode, HF XTAL ACLK
fet120_ta_13.c             Timer_A, Toggle P1.1/TA0, Up/Down Mode, DCO SMCLK
fet120_ta_14.c             Timer_A, Toggle P1.1/TA0, Up/Down Mode, 32kHz ACLK
fet120_ta_15.c             Timer_A, Toggle P1.1/TA0, Up/Down Mode, HF XTAL ACLK
fet120_ta_16.c             Timer_A, PWM TA1-2, Up Mode, DCO SMCLK
fet120_ta_17.c             Timer_A, PWM TA1-2, Up Mode, 32kHz ACLK
fet120_ta_18.c             Timer_A, PWM TA1-2, Up Mode, HF XTAL ACLK
fet120_ta_19.c             Timer_A, PWM TA1-2, Up/Down Mode, DCO SMCLK
fet120_ta_20.c             Timer_A, PWM TA1-2, Up/Down Mode, 32kHz ACLK
fet120_ta_21.c             Timer_A, PWM TA1-2, Up/Down Mode, HF XTAL ACLK
fet120_uart01_0115k.c      USART0, UART 115200 Echo ISR, HF XTAL ACLK
fet120_uart01_02400.c      USART0, Ultra-Low Pwr UART 2400 Echo ISR, 32kHz ACLK
fet120_uart01_09600.c      USART0, UART 9600 Echo ISR, HF XTAL ACLK
fet120_uart01_19200.c      USART0, UART 19200 Echo ISR, HF XTAL ACLK
fet120_uart02_09600.c      USART0, Ultra-Low Pwr UART 9600 Echo ISR, 32kHz ACLK
fet120_uart02_19200.c      USART0, Ultra-Low Pwr UART 19200 Echo ISR, 32kHz ACLK
fet120_uart03_09600.c      USART0, UART 9600 Echo ISR, 32kHz ACLK + DCO
fet120_uart03_19200.c      USART0, UART 19200 Echo ISR, 32kHz ACLK + DCO
fet120_uart04_09600.c      USART0, UART 9600 Echo ISR, No XTAL, Rosc DCO Only
fet120_uart04_19200.c      USART0, UART 19200 Echo ISR, No XTAL, Rosc DCO Only
fet120_uart05_09600.c      USART0, Ultra-Low Pwr 9600 Echo ISR, 32kHz ACLK
fet120_uart06_09600.c      USART0, Ultra-Low Pwr UART 9600 String, 32kHz ACLK
fet120_wdt_01.c            WDT, Toggle P1.0, Interval Overflow ISR, DCO SMCLK
fet120_wdt_02.c            WDT, Toggle P1.0, Interval Overflow ISR, 32kHz ACLK
fet120_wdt_03.c            WDT, Toggle P1.0, Interval Overflow ISR, HF XTAL ACLK

