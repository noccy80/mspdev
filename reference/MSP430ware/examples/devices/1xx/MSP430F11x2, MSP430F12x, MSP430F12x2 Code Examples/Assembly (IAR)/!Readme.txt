File Name                    Description
----------------------------------------------------------------------------------------
fet120_1.s43                 Software Toggle P1.0
fet120_5timers.s43           5 Interrupt Timers & 2 Clock Outputs, 32kHz ACLK
fet120_adc10_01.s43          ADC10, Sample A0, AVcc Ref, Set P1.0 if A0 > 0.5*AVcc
fet120_adc10_02.s43          ADC10, Sample A0, 1.5V Ref, Set P1.0 if A0 > 0.2V
fet120_adc10_03.s43          ADC10, Sample A10 Temp, Set P1.0 if Temp ++ ~2C
fet120_adc10_04.s43          ADC10, Sample A0, Signed, Set P1.0 if A0 > 0.5*AVcc
fet120_adc10_05.s43          ADC10, Sample A11, Lo_Batt, Set P1.0 if AVcc < 2.3V
fet120_adc10_06.s43          ADC10, Output Internal Vref on P2.4 & ADCCLK on P1.0
fet120_adc10_07.s43          ADC10, DTC Sample A0 64x, AVcc, Repeat Single, DCO
fet120_adc10_08.s43          ADC10, DTC Sample A0 64x, 1.5V, Repeat Single, DCO
fet120_adc10_09.s43          ADC10, DTC Sample A10 64x, 1.5V, Repeat Single, DCO
fet120_adc10_10.s43          ADC10, DTC Sample A2-0, AVcc, Single Sequence, DCO
fet120_adc10_11.s43          ADC10, Sample A0, 1.5V, TA1 Trig, Set P1.0 if > 0.5V
fet120_adc10_12.s43          ADC10, Sample A7, 1.5V, TA1 Trig, Ultra-Low Pwr
fet120_adc10_13.s43          ADC10, DTC Sample A1 32x, AVcc, TA0 Trig, DCO
fet120_adc10_14.s43          ADC10, DTC Sample A1-0 32x, AVcc, Repeat Seq, DCO
fet120_adc10_15.s43          ADC10, DTC Sample A10 32x to Flash, Int Ref, DCO
fet120_adc10_16.s43          ADC10, DTC Sample A0 -> TA1, AVcc, DCO
fet120_adc10_17.s43          ADC10, DTC Sample A0 -> TA1, AVcc, HF XTAL
fet120_adc10_18.s43          ADC10, DTC Sample A1/0 -> TA1/2, 2.5V, HF XTAL
fet120_adc10_19.s43          ADC10, DTC Sample A0 64x, AVcc, HF XTAL
fet120_adc10_20.s43          ADC10, DTC Sample A0 2-Blk Cont. Mode, AVcc, HF XTAL
fet120_adc10_temp.s43        ADC10, Sample A10 Temp and Convert to oC and oF
fet120_clks.s43              Basic Clock, Output Buffered SMCLK, ACLK and MCLK/10
fet120_flash_write.s43       Flash In-System Programming, Copy SegA to SegB
fet120_fll_01.s43            Basic Clock, Implement Auto RSEL SW FLL
fet120_fll_02.s43            Basic Clock, Implement Cont. SW FLL with Auto RSEL
fet120_hfxtal.s43            Basic Clock, LFXTI/MCLK Sourced from HF XTAL
fet120_hfxtal_nmi.s43        Basic Clock, LFXT1/MCLK Sourced from HF XTAL, NMI
fet120_lpm3.s43              Basic Clock, LPM3 Using WDT ISR, 32kHz ACLK
fet120_nmi.s43               Basic Clock, Configure RST/NMI as NMI
fet120_rosc.s43              DCOCLK Biased with External Resistor Rosc
fet120_spi0_0549.s43         USART0, SPI Interface to TLC549 8-Bit ADC
fet120_spi0_1549.s43         USART0, SPI Interface to TLV1549 10-Bit ADC
fet120_spi0_16x.s43          USART0, SPI Interface to HC165/164 Shift Registers
fet120_spi0_7822.s43         USART0, SPI Interface to ADS7822 ADC
fet120_spi0_mstr.s43         USART0, SPI 3-Wire Master
fet120_spi0_slav.s43         USART0, SPI 3-Wire Slave
fet120_ta_01.s43             Timer_A, Toggle P1.0, CCR0 Cont. Mode ISR, DCO SMCLK
fet120_ta_02.s43             Timer_A, Toggle P1.0, CCR0 Up Mode ISR, DCO SMCLK
fet120_ta_03.s43             Timer_A, Toggle P1.0, Overflow ISR, DCO SMCLK
fet120_ta_04.s43             Timer_A, Toggle P1.0, Overflow ISR, 32kHz ACLK
fet120_ta_05.s43             Timer_A, Toggle P1.0, CCR0 Up Mode ISR, 32kHz ACLK
fet120_ta_06.s43             Timer_A, Toggle P1.0, CCR1 Cont. Mode ISR, DCO SMCLK
fet120_ta_07.s43             Timer_A, Toggle P1.0-3, Cont. Mode ISR, DCO SMCLK
fet120_ta_08.s43             Timer_A, Toggle P1.0-3, Cont. Mode ISR, 32kHz ACLK
fet120_ta_09.s43             Timer_A, Toggle P1.0-3, Cont. Mode ISR, HF XTAL ACLK
fet120_ta_10.s43             Timer_A, Toggle P1.1/TA0, Up Mode, DCO SMCLK
fet120_ta_11.s43             Timer_A, Toggle P1.1/TA0, Up Mode, 32kHz ACLK
fet120_ta_12.s43             Timer_A, Toggle P1.1/TA0, Up Mode, HF XTAL ACLK
fet120_ta_13.s43             Timer_A, Toggle P1.1/TA0, Up/Down Mode, DCO SMCLK
fet120_ta_14.s43             Timer_A, Toggle P1.1/TA0, Up/Down Mode, 32kHz ACLK
fet120_ta_15.s43             Timer_A, Toggle P1.1/TA0, Up/Down Mode, HF XTAL ACLK
fet120_ta_16.s43             Timer_A, PWM TA1-2, Up Mode, DCO SMCLK
fet120_ta_17.s43             Timer_A, PWM TA1-2, Up Mode, 32kHz ACLK
fet120_ta_18.s43             Timer_A, PWM TA1-2, Up Mode, HF XTAL ACLK
fet120_ta_19.s43             Timer_A, PWM TA1-2, Up/Down Mode, DCO SMCLK
fet120_ta_20.s43             Timer_A, PWM TA1-2, Up/Down Mode, 32kHz ACLK
fet120_ta_21.s43             Timer_A, PWM TA1-2, Up/Down Mode, HF XTAL ACLK
fet120_ta_22.s43             Timer_A, Ultra-Low Pwr Pulse Accumulator
fet120_uart01_0115k.s43      USART0, UART 115200 Echo ISR, HF XTAL ACLK
fet120_uart01_02400.s43      USART0, Ultra-Low Pwr UART 2400 Echo ISR, 32kHz ACLK
fet120_uart01_09600.s43      USART0, UART 9600 Echo ISR, HF XTAL ACLK
fet120_uart01_19200.s43      USART0, UART 19200 Echo ISR, HF XTAL ACLK
fet120_uart02_09600.s43      USART0, Ultra-Low Pwr UART 9600 Echo ISR, 32kHz ACLK
fet120_uart02_19200.s43      USART0, Ultra-Low Pwr UART 19200 Echo ISR, 32kHz ACLK
fet120_uart03_09600.s43      USART0, UART 9600 Echo ISR, 32kHz ACLK + DCO
fet120_uart03_19200.s43      USART0, UART 19200 Echo ISR, 32kHz ACLK + DCO
fet120_uart04_09600.s43      USART0, UART 9600 Echo ISR, No XTAL, Rosc DCO Only
fet120_uart04_19200.s43      USART0, UART 19200 Echo ISR, No XTAL, Rosc DCO Only
fet120_uart05_09600.s43      USART0, Ultra-Low Pwr UART 9600 Echo ISR, 32kHz ACLK
fet120_uart06_09600.s43      USART0, Ultra-Low Pwr UART 9600 String, 32kHz ACLK
fet120_wdt_01.s43            WDT, Toggle P1.0, Interval Overflow ISR, DCO SMCLK
fet120_wdt_02.s43            WDT, Toggle P1.0, Interval Overflow ISR, 32kHz ACLK
fet120_wdt_03.s43            WDT, Toggle P1.0, Interval Overflow ISR, HF XTAL ACLK

