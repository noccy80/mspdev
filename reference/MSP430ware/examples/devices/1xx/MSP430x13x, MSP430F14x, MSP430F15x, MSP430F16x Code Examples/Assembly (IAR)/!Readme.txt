File Name                      Description
----------------------------------------------------------------------------------------
fet140_1.s43                   Software Toggle P1.0
fet140_adc12_01.s43            ADC12, Sample A0, Set P1.0 if A0 > 0.5*AVcc
fet140_adc12_02.s43            ADC12, Using the Internal Reference
fet140_adc12_03.s43            ADC12, Sample A10 Temp, Set P1.0 if Temp ++ ~2C
fet140_adc12_04.s43            ADC12, Extend Sampling Period with SHT Bits
fet140_adc12_05.s43            ADC12, Using an External Reference
fet140_adc12_06.s43            ADC12, Repeated Sequence of Conversions
fet140_adc12_07.s43            ADC12, Repeated Single Channel Conversions
fet140_adc12_08.s43            ADC12, Using 10 External Channels for Conversion
fet140_adc12_09.s43            ADC12, Sequence of Conversions (non-repeated)
fet140_adc12_10.s43            ADC12, Sample A10 Temp and Convert to oC and oF
fet140_clks.s43                Basic Clock, Output Buffered SMCLK, ACLK and MCLK
fet140_dac12_01.s43            DAC12_0, Output 1.0V on DAC0
fet140_dac12_02.s43            DAC12_1, Output 2.0V on DAC1
fet140_dac12_03.s43            DAC12_0, Output Voltage Ramp on DAC0
fet140_dma_01.s43              DMA0, Repeated Burst to-from RAM, Software Trigger
fet140_dma_02.s43              DMA0, Repeated Block to P1OUT, TACCR2 Trigger
fet140_dma_03.s43              DMA0, Repeated Block UART1 9600, TACCR2, ACLK
fet140_dma_04.s43              DMA0, Block Mode UART1 9600, ACLK
fet140_dma_05.s43              DMA0, Repeated Blk to DAC0, Sine Output, TACCR1, DCO
fet140_dma_06.s43              DMA2, Rpt'd Blk to DAC1, 8-Bit Sine, TBCCR2, DCO
fet140_dma_07.s43              DMA0/1, Rpt'd Blk to DAC12_0/1, Sin/Cos, TACCR1, XT2
fet140_dma_08.s43              DMA0, Rpt'd Block, I2C Master Intf. to DAC8571, DCO
fet140_dma_09.s43              DMA0, ADC12 A10 Block Xfer to RAM, TBCCR1, DCO
fet140_dma_10.s43              DMA0, ADC12 A10 Block Xfer to Flash, TBCCR1, DCO
fet140_dma_11.s43              DMA0/1, ADC12 A10 Block Xfer to MPY/RAM, TBCCR1, DCO
fet140_dma_12.s43              DMA0/1, Block Mode UART1 9600 Auto RX/TX String, ACLK
fet140_dma_13.s43              DMA0/1/2, USART0 UART 9600 Full-Duplex Transcvr, ACLK
fet140_dma_14.s43              DMA0/1/2, USART0 SPI 3-Wire SPI Master P1.x Exchange
fet140_dma_15.s43              DMA0/1/2, USART0 SPI 3-Wire SPI Slave P1.x Exchange
fet140_dma_16.s43              DMA0/1/2, USART1 SPI 3-Wire Master P1.x Exchange
fet140_flashwrite_01.s43       Flash In-System Programming, Copy SegA to SegB
fet140_flashwrite_02.s43       Flash In-System Programming, BlockWrite
fet140_fll_01.s43              Basic Clock, Implement Auto RSEL SW FLL
fet140_fll_02.s43              Basic Clock, Implement Cont. SW FLL with Auto RSEL
fet140_hfxt2.s43               Basic Clock, MCLK Sourced from HF XTAL XT2
fet140_hfxtal.s43              Basic Clock, LFXT1/MCLK Sourced from HF XTAL
fet140_hfxtal_nmi.s43          Basic Clock, MCLK Sourced from HF XTAL & Osc Fault
fet140_i2c_01.s43              I2C, Master Intf. to TMP100, Set P1.0 if Temp > 28C
fet140_i2c_02.s43              I2C, Master Interface to PCF8574, Read/Write
fet140_i2c_03.s43              I2C, Master Interface to DAC8571, Repeat Mode
fet140_i2c_04.s43              I2C, Master Reads from MSP430 Slave
fet140_i2c_05.s43              I2C, Slave Transmits to MSP430 Master
fet140_i2c_06.s43              I2C, Master Transmits to MSP430 Slave
fet140_i2c_07.s43              I2C, Slave Reads from MSP430 Master
fet140_i2c_08.s43              I2C, Master Writes Multiple Bytes to MSP430 Slave
fet140_i2c_09.s43              I2C, Slave Writes to MSP430 Master, Repeat Mode
fet140_i2c_10.s43              I2C, Master Reads from MSP430 Slave, Repeat Mode
fet140_i2c_11.s43              I2C, Master Writes/Reads with Slave, Rptd Start
fet140_i2c_12.s43              I2C, Slave Reads/Writes to MSP430 Master
fet140_lpm3.s43                Basic Clock, LPM3 Using WDT ISR, 32kHz ACLK
fet140_nmi.s43                 Basic Clock, Configure RST/NMI as NMI
fet140_rosc.s43                DCOCLK Biased with External Resistor Rosc
fet140_spi0_01.s43             USART0, SPI Interface to HC164 Shift Register
fet140_spi0_02.s43             USART0, SPI Interface to HC165 Shift Register
fet140_spi0_03.s43             USART0, SPI Interface to HC165/164 Shift Registers
fet140_spi0_04.s43             USART0, SPI Interface to TLV5616 DAC
fet140_spi0_05.s43             USART0, SPI 3-Wire Master
fet140_spi0_06.s43             USART0, SPI 3-Wire Slave
fet140_spi1_01.s43             USART1, SPI Interface to TLC549 8-Bit ADC
fet140_spi1_02.s43             USART1, SPI Interface to TLV1549 10-Bit ADC
fet140_spi1_03.s43             USART1, SPI Interface to TLV5616 DAC
fet140_svs_01.s43              SVS, POR @ 2.5V Vcc
fet140_ta_01.s43               Timer_A, Toggle P1.0, CCR0 Cont. Mode ISR, DCO SMCLK
fet140_ta_02.s43               Timer_A, Toggle P1.0, CCR0 Up Mode ISR, DCO SMCLK
fet140_ta_03.s43               Timer_A, Toggle P1.0, Overflow ISR, DCO SMCLK
fet140_ta_04.s43               Timer_A, Toggle P1.0, Overflow ISR, 32kHz ACLK
fet140_ta_05.s43               Timer_A, Toggle P1.0, CCR0 Up Mode ISR, 32kHz ACLK
fet140_ta_06.s43               Timer_A, Toggle P1.0, CCR1 Cont. Mode ISR, DCO SMCLK
fet140_ta_07.s43               Timer_A, Toggle P1.0-3, Cont. Mode ISR, DCO SMCLK
fet140_ta_08.s43               Timer_A, Toggle P1.0-3, Cont. Mode ISR, 32kHz ACLK
fet140_ta_09.s43               Timer_A, Toggle P1.0-3, Cont. Mode ISR, HF XTAL ACLK
fet140_ta_10.s43               Timer_A, Toggle P1.1/TA0, Up Mode, DCO SMCLK
fet140_ta_11.s43               Timer_A, Toggle P1.1/TA0, Up Mode, 32kHz ACLK
fet140_ta_12.s43               Timer_A, Toggle P1.1/TA0, Up Mode, HF XTAL ACLK
fet140_ta_13.s43               Timer_A, Toggle P1.1/TA0, Up/Down Mode, DCO SMCLK
fet140_ta_14.s43               Timer_A, Toggle P1.1/TA0, Up/Down Mode, 32kHz ACLK
fet140_ta_15.s43               Timer_A, Toggle P1.1/TA0, Up/Down Mode, HF XTAL ACLK
fet140_ta_16.s43               Timer_A, PWM TA1-2, Up Mode, DCO SMCLK
fet140_ta_17.s43               Timer_A, PWM TA1-2, Up Mode, 32kHz ACLK
fet140_ta_18.s43               Timer_A, PWM TA1-2, Up Mode, HF XTAL ACLK
fet140_ta_19.s43               Timer_A, PWM TA1-2, Up/Down Mode, DCO SMCLK
fet140_ta_20.s43               Timer_A, PWM TA1-2, Up/Down Mode, 32kHz ACLK
fet140_ta_21.s43               Timer_A, PWM TA1-2, Up/Down Mode, HF XTAL ACLK
fet140_ta_22.s43               Timer_A, PWM TA1-2, Up Mode, XT2 HF XTAL SMCLK
fet140_ta_23.s43               Timer_A, PWM TA1-2, Up/Down Mode, XT2 HF XTAL SMCLK
fet140_tb_01.s43               Timer_B, Toggle P1.0, CCR0 Cont. Mode ISR, DCO SMCLK
fet140_tb_02.s43               Timer_B, Toggle P1.0, CCR0 Up Mode ISR, DCO SMCLK
fet140_tb_03.s43               Timer_B, Toggle P1.0, Overflow ISR, DCO SMCLK
fet140_tb_04.s43               Timer_B, Toggle P1.0, Overflow ISR, 32kHz ACLK
fet140_tb_05.s43               Timer_B, Toggle P1.0, CCR0 Up Mode ISR, 32kHz ACLK
fet140_tb_06.s43               Timer_B, Toggle P1.0, CCR1 Cont. Mode ISR, DCO SMCLK
fet140_tb_07.s43               Timer_B, Toggle P4.0-6, Cont. Mode ISR, DCO SMCLK
fet140_tb_08.s43               Timer_B, Toggle P4.0-6, Cont. Mode, 32kHz ACLK
fet140_tb_09.s43               Timer_B, Toggle P4.0-6, Cont. Mode ISR, XT2 SMCLK
fet140_tb_10.s43               Timer_B, PWM TB1-6, Up Mode, DCO SMCLK
fet140_tb_11.s43               Timer_B, PWM TB1-6, Up Mode, 32kHz ACLK
fet140_tb_12.s43               Timer_A, PWM TB1-2, Up Mode, HF XTAL ACLK
fet140_tb_13.s43               Timer_B, PWM TB1-2, Up/Down Mode, DCO SMCLK
fet140_tb_14.s43               Timer_B, PWM TB1-2, Up/Down Mode, 32kHz ACLK
fet140_tb_15.s43               Timer_B, PWM TB1-2, Up/Down Mode, HF XTAL ACLK
fet140_tb_16.s43               Timer_B, PWM TB1-6, Up Mode, XT2 HF XTAL SMCLK
fet140_tb_17.s43               Timer_B, PWM TB1-6, Up/Down Mode, XT2 HF XTAL SMCLK
fet140_uart01_0115k.s43        USART0, UART 115200 Echo ISR, HF XTAL ACLK
fet140_uart01_0115k_2.s43      USART0, UART 115200 Echo ISR, XT2 HF XTAL SMCLK
fet140_uart01_02400.s43        USART0, Ultra-Low Pwr UART 2400 Echo ISR, 32kHz ACLK
fet140_uart01_09600.s43        USART0, UART 9600 Echo ISR, HF XTAL ACLK
fet140_uart01_19200.s43        USART0, UART 19200 Echo ISR, HF XTAL ACLK
fet140_uart01_19200_2.s43      USART0, UART 19200 Echo ISR, XT2 HF XTAL SMCLK
fet140_uart02_09600.s43        USART0, Ultra-Low Pwr UART 9600 Echo ISR, 32kHz ACLK
fet140_uart02_19200.s43        USART0, Ultra-Low Pwr UART 19200 Echo ISR, 32kHz ACLK
fet140_uart03_09600.s43        USART0, UART 9600 Echo ISR, 32kHz ACLK + DCO
fet140_uart03_19200.s43        USART0, UART 19200 Echo ISR, 32kHz ACLK + DCO
fet140_uart04_09600.s43        USART0, UART 9600 Echo ISR, No XTAL, Rosc DCO Only
fet140_uart04_19200.s43        USART0, UART 19200 Echo ISR, No XTAL, Rosc DCO Only
fet140_uart05_09600.s43        USART0, Ultra-Low Pwr UART 9600 Echo ISR, 32kHz ACLK
fet140_uart06_09600.s43        USART0, Ultra-Low Pwr UART 9600 String, 32kHz ACLK
fet140_uart07_09600.s43        USART0, Ultra-Low Pwr UART 9600 RX/TX, 32kHz ACLK
fet140_uart08_09600.s43        USART0, UART 9600 Full-Duplex Transceiver, 32K ACLK
fet140_uart11_0115k.s43        USART1, UART 115200 Echo ISR, HF XTAL ACLK
fet140_uart11_0115k_2.s43      USART1, UART 115200 Echo ISR, XT2 HF XTAL SMCLK
fet140_uart11_02400.s43        USART1, Ultra-Low Pwr UART 2400 Echo ISR, 32kHz ACLK
fet140_uart11_09600.s43        USART1, UART 9600 Echo ISR, HF XTAL ACLK
fet140_uart11_19200.s43        USART1, UART 19200 Echo ISR, HF XTAL ACLK
fet140_uart11_19200_2.s43      USART1, UART 19200 Echo ISR, XT2 HF XTAL SMCLK
fet140_uartxx_00123.s43        USART0/1, UART 19200-115200 Router, XT2 HF XTAL SMCLK
fet140_wdt_01.s43              WDT, Toggle P1.0, Interval overflow ISR, DCO SMCLK
fet140_wdt_02.s43              WDT, Toggle P1.0, Interval Overflow ISR, 32kHz ACLK
fet140_wdt_03.s43              WDT, Toggle P1.0, Interval Overflow ISR, HF XTAL ACLK

