File Name                           Description
----------------------------------------------------------------------------------------
MSP430x261x_1.s43                   Software Toggle P1.0
MSP430x261x_1_vlo.s43               Software Toggle P1.0, MCLK = VLO/8
MSP430x261x_adc12_01.s43            ADC12, Sample A0, Set P1.0 if A0 > 0.5*AVcc
MSP430x261x_adc12_02.s43            ADC12, Using the Internal Reference
MSP430x261x_adc12_03.s43            ADC12, Sample A10 Temp, Set P1.0 if Temp ++ ~2C
MSP430x261x_adc12_04.s43            ADC12, Extend Sampling Period with SHT Bits
MSP430x261x_adc12_05.s43            ADC12, Using an External Reference
MSP430x261x_adc12_06.s43            ADC12, Repeated Sequence of Conversions
MSP430x261x_adc12_07.s43            ADC12, Repeated Single Channel Conversions
MSP430x261x_adc12_08.s43            ADC12, Using 10 External Channels for Conversion
MSP430x261x_adc12_09.s43            ADC12, Sequence of Conversions (non-repeated)
MSP430x261x_adc12_10.s43            ADC12, Sample A10 Temp and Convert to oC and oF
MSP430x261x_clks.s43                Basic Clock, Output Buffered SMCLK, ACLK, and MCLK
MSP430x261x_compA_01.s43            Comparator A, Poll input CA0, result in P1.0
MSP430x261x_compA_02.s43            Comparator A, Poll input CA0, CA exchange, result in P1.0
MSP430x261x_compA_04.s43            Comparator A, Poll input CA0, result in P1.0
MSP430x261x_compA_05.s43            Comparator A, Input to CA0, Interrupt triggered
MSP430x261x_dac12_01.s43            DAC12_0, Output 1.0V on DAC0
MSP430x261x_dac12_02.s43            DAC12_0, Output 2.0V on DAC1
MSP430x261x_dac12_03.s43            DAC12_0, Output Voltage Ramp on DAC0
MSP430x261x_dco_flashcal.s43        DCO Calibration Constants Programmer
MSP430x261x_dma_01.s43              DMA0, Repeated Burst to-from RAM, Software Trigger
MSP430x261x_dma_02.s43              DMA0, Repeated single transfer to P1OUT, TACCR2 Trigger
MSP430x261x_dma_03.s43              DMA0, Repeated single transferUCA1UART 9600, TACCR2, ACLK
MSP430x261x_dma_04.s43               DMA0, single transfer Mode UART1 9600, ACLK
MSP430x261x_dma_05.s43              DMA0, Repeated single transfer to DAC0, Sine Output, TACCR1, DCO
MSP430x261x_dma_06.s43              DMA2, Rpt'd single transfer to DAC1, 8-Bit Sine, TBCCR2, DCO
MSP430x261x_dma_07.s43               DMA0/1, Rpt'd single transfer to DAC12_0/1, Sin/Cos, TACCR1, XT2
MSP430x261x_dma_09.s43               DMA0, ADC12 A10 single blocktransfer Xfer to RAM, TBCCR1, DCO
MSP430x261x_dma_10.s43               DMA0, ADC12 A10 rpt single transfer Xfer to Flash, TBCCR1, DCO
MSP430x261x_dma_11.s43               DMA0/1, ADC12 A10 rpt single transfer Xfer to MPY/RAM, TBCCR1, DCO
MSP430x261x_dma_12.s43               DMA0/1, Block Mode UART1 9600 Auto RX/TX String, ACLK
MSP430x261x_flashwrite_01.s43       Flash In-System Programming, Copy SegC to SegD
MSP430x261x_flashwrite_03.s43       Flash In-System Programming w/ EEI, Copy SegC to SegD
MSP430x261x_flashwrite_04.s43       Flash In-System Programming w/ EEI, Copy SegD to B&C
MSP430x261x_fll_01.s43              Basic Clock, Implement Auto RSEL SW FLL
MSP430x261x_fll_02.s43              Basic Clock, Implement Cont. SW FLL with Auto RSEL
MSP430x261x_hfxt2.s43               Basic Clock, MCLK Configured to Operate from XT2 HF XTAL
MSP430x261x_hfxt2_nmi.s43           Basic Clock, MCLK Sourced from HF XTAL XT2, NMI
MSP430x261x_lpm3.s43                Basic Clock, LPM3 Using WDT ISR, 32kHz ACLK
MSP430x261x_lpm3_vlo.s43            Basic Clock, LPM3 Using WDT ISR, VLO ACLK
MSP430x261x_MPY_01.s43              16x16 Unsigned Multiply
MSP430x261x_MPY_02.s43              8x8 Unsigned Multiply
MSP430x261x_MPY_03.s43              16x16 Signed Multiply
MSP430x261x_MPY_04.s43              8x8 Signed Multiply
MSP430x261x_MPY_05.s43              16x16 Unsigned Multiply Accumulate
MSP430x261x_MPY_06.s43              8x8 Unsigned Multiply Accumulate
MSP430x261x_MPY_07.s43              16x16 Signed Multiply Accumulate
MSP430x261x_MPY_08.s43              8x8 Signed Multiply Accumulate
MSP430x261x_nmi.s43                 Configure RST/NMI as NMI
MSP430x261x_OF_XT2.s43              XT2 Oscillator Fault Detection
MSP430x261x_P1_01.s43               Software Poll P1.3, Set P1.0 if P1.3 = 1
MSP430x261x_P1_02.s43               Software Port Interrupt Service on P1.3 from LPM4
MSP430x261x_P1_05.s43               Write a byte to Port 1
MSP430x261x_P7_05.s43               Write a byte to Port 7
MSP430x261x_P8_05.s43               Write a byte to Port 8
MSP430x261x_PA_05.s43               Write a word to Port A
MSP430x261x_rosc.s43                DCOCLK Biased with External Resistor Rosc
MSP430x261x_svs_01.s43              SVS, POR @ 2.5V Vcc
MSP430x261x_ta_01.s43               Timer_A, Toggle P1.0, CCR0 Cont. Mode ISR, DCO SMCLK
MSP430x261x_ta_02.s43               Timer_A, Toggle P1.0, CCR0 Up Mode ISR, DCO SMCLK
MSP430x261x_ta_03.s43               Timer_A, Toggle P1.0, Overflow ISR, DCO SMCLK
MSP430x261x_ta_04.s43               Timer_A, Toggle P1.0, Overflow ISR, 32kHz ACLK
MSP430x261x_ta_05.s43               Timer_A, Toggle P1.0, CCR0 Up Mode ISR, 32kHz ACLK
MSP430x261x_ta_08.s43               Timer_A, Toggle P1.0,P1.2 & P2.0 Cont. Mode ISR, 32kHz ACLK
MSP430x261x_ta_11.s43               Timer_A, Toggle P1.1/TA0, Up Mode, 32kHz ACLK
MSP430x261x_ta_13.s43               Timer_A, Toggle P1.1/TA0, Up/Down Mode, DCO SMCLK
MSP430x261x_ta_14.s43               Timer_A, Toggle P1.1/TA0, Up/Down Mode, 32kHz ACLK
MSP430x261x_ta_16.s43               Timer_A, PWM TA1-2 Up Mode, DCO SMCLK
MSP430x261x_ta_17.s43               Timer_A, PWM TA1-2, Up Mode, 32kHz ACLK
MSP430x261x_ta_19.s43               Timer_A, PWM TA1-2, Up/Down Mode, DCO SMCLK
MSP430x261x_ta_20.s43               Timer_A, PWM TA1-2, Up/Down Mode, DCO SMCLK
MSP430x261x_tb_01.s43               Timer_B, Toggle P1.0, CCR0 Cont. Mode ISR, DCO SMCLK
MSP430x261x_tb_02.s43               Timer_B, Toggle P1.0, CCR0 Up Mode ISR, DCO SMCLK
MSP430x261x_tb_03.s43               Timer_B, Toggle P1.0, Overflow ISR, DCO SMCLK
MSP430x261x_tb_04.s43               Timer_B, Toggle P1.0, Overflow ISR, 32kHz ACLK
MSP430x261x_tb_05.s43               Timer_B, Toggle P1.0, CCR0 Up Mode ISR, 32kHz ACLK
MSP430x261x_tb_07.s43               Timer_B, PWM TB1-6, Up Mode, 32kHz ACLK
MSP430x261x_uscia0_irda_01.s43      USCI_A0 IrDA External Loopback Test, 8MHz SMCLK
MSP430x261x_uscia0_spi_09.s43       USCI_A0, SPI 3-Wire Master Incremented Data
MSP430x261x_uscia0_spi_10.s43       USCI_A0, SPI 3-Wire Slave Data Echo
MSP430x261x_uscia0_uart_01.s43      USCI_A0, 115200 UART Echo ISR, DCO SMCLK
MSP430x261x_uscia0_uart_03.s43      USCI_A0, Ultra-Low Pwr UART 9600 Echo ISR, 32kHz ACLK
MSP430x261x_uscia0_uart_04.s43      USCI_A0, 9600 UART, SMCLK, LPM0, Echo with over-sampling
MSP430x261x_uscia1_uart_02.s43      USCI_A1, Ultra-Low Pwr UART 2400 Echo ISR, 32kHz ACLK
MSP430x261x_uscib0_i2c_04.s43       USCI_B0 I2C Master RX single bytes from MSP430 Slave
MSP430x261x_uscib0_i2c_05.s43       USCI_B0 I2C Slave TX single bytes to MSP430 Master
MSP430x261x_uscib0_i2c_06.s43       USCI_B0 I2C Master TX single bytes to MSP430 Slave
MSP430x261x_uscib0_i2c_07.s43       USCI_B0 I2C Slave RX single bytes from MSP430 Master
MSP430x261x_uscib0_i2c_08.s43       USCI_B0 I2C Master TX multiple bytes to MSP430 Slave
MSP430x261x_uscib0_i2c_09.s43       USCI_B0 I2C Slave RX multiple bytes from MSP430 Master
MSP430x261x_uscib0_i2c_10.s43       USCI_B0 I2C Master RX multiple bytes from MSP430 Slave
MSP430x261x_uscib0_i2c_11.s43       USCI_B0 I2C Slave TX multiple bytes to MSP430 Master
MSP430x261x_uscib0_spi_09.s43       USCI_B0, SPI 3-Wire Master Incremented Data
MSP430x261x_uscib0_spi_10.s43       USCI_B0, SPI 3-Wire Slave Data Echo
MSP430x261x_vlo_capture.s43         Basic Clock, VLO-Driven Timer with VLO Compensation
MSP430x261x_wdt_01.s43              WDT, Toggle P1.0, Interval Overflow ISR, DCO SMCLK
MSP430x261x_wdt_02.s43              WDT, Toggle P1.0, Interval Overflow ISR, 32kHz ACLK
MSP430x261x_wdt_04.s43              WDT+ Failsafe Clock, WDT mode, DCO SMCLK
MSP430x261x_wdt_05.s43              Reset on Invalid Address fetch, Toggle P1.0
MSP430x261x_wdt_06.s43              WDT+ Failsafe Clock, 32kHz ACLK

