File Name                      Description
----------------------------------------------------------------------------------------
fet140_1.c                     Software Toggle P1.0
fet140_adc12_01.c              ADC12, Sample A0, Set P1.0 if A0 > 0.5*AVcc
fet140_adc12_02.c              ADC12, Using the Internal Reference
fet140_adc12_03.c              ADC12, Sample A10 Temp, Set P1.0 if Temp ++ ~2C
fet140_adc12_04.c              ADC12, Extend Sampling Period with SHT Bits
fet140_adc12_05.c              ADC12, Using an External Reference
fet140_adc12_06.c              ADC12, Repeated Sequence of Conversions
fet140_adc12_07.c              ADC12, Repeated Single Channel Conversions
fet140_adc12_08.c              ADC12, Using 10 External Channels for Conversion
fet140_adc12_09.c              ADC12, Sequence of Conversions (non-repeated)
fet140_adc12_10.c              ADC12, Sample A10 Temp and Convert to oC and oF
fet140_adc12_11.c              ADC12, Single Channel Rpt Mode, TA1 as Sample Trigger
fet140_clks.c                  Basic Clock, Output Buffered SMCLK, ACLK and MCLK
fet140_dac12_01.c              DAC12_0, Output 1.0V on DAC0
fet140_dac12_02.c              DAC12_1, Output 2.0V on DAC1
fet140_dac12_03.c              DAC12_0, Output Voltage Ramp on DAC0
fet140_dma_01.c                DMA0, Repeated Burst to-from RAM, Software Trigger
fet140_dma_02.c                DMA0, Repeated Block To P1OUT, TACCR2, DCO
fet140_dma_03.c                DMA0, Repeated Block UART1 9600, TACCR2, ACLK
fet140_dma_04.c                DMA0, Block Mode UART1 9600, 32kHz ACLK
fet140_dma_05.c                DMA0, Rpt'd Blk to DAC0, Sine Output, TACCR1, DCO
fet140_dma_06.c                DMA2, Rpt'd Blk to DAC1, 8-Bit Sine, TBCCR2, DCO
fet140_dma_07.c                DMA0/1, Rpt'd Blk to DAC0/1, Sin/Cos, TACCR1, XT2
fet140_dma_08.c                DMA0, Rpt'd Blk, I2C Master Interface to DAC8571
fet140_dma_09.c                DMA0, ADC12 A10 Block Xfer to RAM, TBCCR1, DCO
fet140_dma_10.c                DMA0, ADC12 A10 Block Xfer to Flash, TBCCR1, DCO
fet140_dma_11.c                DMA0/1, ADC12 A10 Block Xfer to MPY/RAM, TBCCR1, DCO
fet140_dma_12.c                DMA1/0, Blk Mode UART1 9600 Auto RX/TX String, ACLK
fet140_dma_13.c                DMA0/1/2, USART0 UART 9600 Full-Duplex Transcvr, ACLK
fet140_dma_14.c                DMA0/1/2, USART0 SPI 3-Wire SPI Master P1.x Exchange
fet140_dma_15.c                DMA0/1/2, USART0 SPI 3-Wire SPI Slave P1.x Exchange
fet140_dma_16.c                DMA0/1/2, USART1 SPI 3-Wire Master P1.x Exchange
fet140_flashwrite_01.c         Flash In-System Programming, Copy SegA to SegB
fet140_flashwrite_02.c         Flash In-System Programming, BlockWrite
fet140_fll_01.c                Basic Clock, Implement Auto RSEL SW FLL
fet140_fll_02.c                Basic Clock, Implement Cont. SW FLL with Auto RSEL
fet140_hfxt2.c                 Basic Clock, MCLK Sourced from HF XTAL XT2
fet140_hfxtal.c                Basic Clock, MCLK Sourced from HF XTAL
fet140_i2c_01.c                I2C, Master Intf. to TMP100, Set P1.0 if Temp > 28C
fet140_i2c_02.c                I2C, Master Interface to PCF8574, Read/Write
fet140_i2c_03.c                I2C, Master Interface to DAC8571 in Repeat Mode
fet140_i2c_04.c                I2C, Master Reads from MSP430 Slave
fet140_i2c_05.c                I2C, Slave Transmits to MSP430 Master
fet140_i2c_06.c                I2C, Master Transmits to MSP430 Slave RX
fet140_i2c_07.c                I2C, Slave Reads from MSP430 Master
fet140_i2c_08.c                I2C, Master Writes Multiple Bytes to MSP430 Slave
fet140_i2c_09.c                I2C, Master Reads from MSP430 Slave in Repeat Mode
fet140_i2c_10.c                I2C, Slave Writes to MSP430 Master RX in Repeat Mode
fet140_i2c_12.c                I2C, Master Interface to DAC8571, Write
fet140_i2c_13.c                I2C, Master Interface to DAC8571, Read/Write
fet140_i2c_14.c                Switch Between UART0 & Master I2C Transmitter
fet140_i2c_15.c                I2C, Slave TMP100 Emulation II
fet140_i2c_16.c                I2C, Master Writes/Reads with Slave, Rptd Start
fet140_i2c_17.c                I2C, Slave Reads/Writes with Master, Rptd Start
fet140_lpm3.c                  Basic Clock, LPM3 Using WDT ISR, 32kHz ACLK
fet140_nmi.c                   Basic Clock, Configure RST/NMI as NMI
fet140_rosc.c                  DCOCLK Biased with External Resistor Rosc
fet140_spi0_03.c               USART0, SPI Interface to HC165/164 Shift Registers
fet140_spi0_04.c               USART0, SPI Interface to TLV5616 DAC
fet140_spi0_05.c               USART0, SPI 3-Wire Master
fet140_spi0_06.c               USART0, SPI 3-Wire Slave
fet140_spi0_07.c               USART0, SPI Full-Duplex 3-Wire Master P1.x Exchange
fet140_spi0_08.c               USART0, SPI Full-Duplex 3-Wire Slave P1.x Exchange
fet140_spi1_03.c               USART1, SPI Interface to TLV5616 DAC
fet140_spi1_04.c               USART1, SPI Full-Duplex 3-Wire Master P1.x Exchange
fet140_svs_01.c                SVS, POR @ 2.5V Vcc
fet140_ta0_ta1_uart2400.c      Timer_A software UART 2400 Echo using CCR0 and CCR1, 32kHz ACLK
fet140_ta_01.c                 Timer_A, Toggle P1.0, CCR0 Cont. Mode ISR, DCO SMCLK
fet140_ta_02.c                 Timer_A, Toggle P1.0, CCR0 Up Mode ISR, DCO SMCLK
fet140_ta_03.c                 Timer_A, Toggle P1.0, Overflow ISR, DCO SMCLK
fet140_ta_04.c                 Timer_A, Toggle P1.0, Overflow ISR, 32kHz ACLK
fet140_ta_05.c                 Timer_A, Toggle P1.0, CCR0 Up Mode ISR, 32kHz ACLK
fet140_ta_06.c                 Timer_A, Toggle P1.0, CCR1 Cont. Mode ISR, DCO SMCLK
fet140_ta_07.c                 Timer_A, Toggle P1.0-3, Cont. Mode ISR, DCO SMCLK
fet140_ta_08.c                 Timer_A, Toggle P1.0-3, Cont. Mode ISR, 32kHz ACLK
fet140_ta_09.c                 Timer_A, Toggle P1.0-3, Cont. Mode ISR, HF XTAL ACLK
fet140_ta_10.c                 Timer_A, Toggle P1.1/TA0, Up Mode, DCO SMCLK
fet140_ta_11.c                 Timer_A, Toggle P1.1/TA0, Up Mode, 32kHz ACLK
fet140_ta_12.c                 Timer_A, Toggle P1.1/TA0, Up Mode, HF XTAL ACLK
fet140_ta_13.c                 Timer_A, Toggle P1.1/TA0, Up/Down Mode, DCO SMCLK
fet140_ta_14.c                 Timer_A, Toggle P1.1/TA0, Up/Down Mode, 32kHz ACLK
fet140_ta_15.c                 Timer_A, Toggle P1.1/TA0, Up/Down Mode, HF XTAL ACLK
fet140_ta_16.c                 Timer_A, PWM TA1-2, Up Mode, DCO SMCLK
fet140_ta_17.c                 Timer_A, PWM TA1-2, Up Mode, 32kHz ACLK
fet140_ta_18.c                 Timer_A, PWM TA1-2, Up Mode, HF XTAL ACLK
fet140_ta_19.c                 Timer_A, PWM TA1-2, Up/Down Mode, DCO SMCLK
fet140_ta_20.c                 Timer_A, PWM TA1-2, Up/Down Mode, 32kHz ACLK
fet140_ta_21.c                 Timer_A, PWM TA1-2, Up/Down mode, HF XTAL ACLK
fet140_ta_22.c                 Timer_A0, Capture of ACLK/8 using SMCLK
fet140_ta_23.c                 Timer_A, Toggle P1.0, Overflow ISR, HF XTAL ACLK
fet140_ta_24.c                 Timer_A, Toggle P1.0, CCR0 Up Mode ISR, 32kHz INCLK
fet140_tb_01.c                 Timer_B, Toggle P1.0, CCR0 Cont. Mode ISR, DCO SMCLK
fet140_tb_02.c                 Timer_B, Toggle P1.0, CCR0 Up Mode ISR, DCO SMCLK
fet140_tb_03.c                 Timer_B, Toggle P1.0, Overflow ISR, DCO SMCLK
fet140_tb_04.c                 Timer_B, Toggle P1.0, Overflow ISR, 32kHz ACLK
fet140_tb_05.c                 Timer_B, Toggle P1.0, CCR0 Up Mode ISR, 32kHz ACLK
fet140_tb_06.c                 Timer_B, PWM TB1-6, Up Mode, DCO SMCLK
fet140_tb_07.c                 Timer_B, PWM TB1-6, Up Mode, 32kHz ACLK
fet140_tb_08.c                 Timer_B, PWM TB1-2, Up Mode, HF XTAL ACLK
fet140_tb_09.c                 Timer_B, PWM TB1-2, Up/Down Mode, DCO SMCLK
fet140_tb_10.c                 Timer_B, PWM TB1-2, Up/Down Mode, 32kHz ACLK
fet140_tb_11.c                 Timer_B, PWM TB1-2, Up/Down Mode, HF XTAL ACLK
fet140_uart01_0115k.c          USART0, UART 115200 Echo ISR, HF XTAL ACLK
fet140_uart01_0115k_2.c        USART0, UART 115200 Echo ISR, XT2 HF XTAL ACLK
fet140_uart01_02400.c          USART0, Ultra-Low Pwr UART 2400 Echo ISR, 32kHz ACLK
fet140_uart01_09600.c          USART0, UART 9600 Echo ISR, HF XTAL ACLK
fet140_uart01_09600_2.c        USART0, Ultra-Low Pwr UART 9600 Echo ISR, 32kHz ACLK
fet140_uart01_19200.c          USART0, UART 19200 Echo ISR, HF XTAL ACLK
fet140_uart01_19200_2.c        USART0, UART 19200 Echo ISR, XT2 HF XTAL ACLK
fet140_uart02_09600.c          USART0, Ultra-Low Pwr UART 9600 Echo ISR, 32kHz ACLK
fet140_uart02_19200.c          USART0, Ultra-Low Pwr UART 19200 Echo ISR, 32kHz ACLK
fet140_uart03_09600.c          USART0, UART 9600 Echo ISR, 32kHz ACLK + DCO
fet140_uart03_19200.c          USART0, UART 19200 Echo ISR, 32kHz ACLK + DCO
fet140_uart04_09600.c          USART0, UART 9600 Echo ISR, No XTAL, Rosc DCO Only
fet140_uart04_19200.c          USART0, UART 19200 Echo ISR, No XTAL, Rosc DCO Only
fet140_uart05_09600.c          USART0, Ultra-Low Pwr UART 9600 Echo ISR, 32kHz ACLK
fet140_uart06_09600.c          USART0, Ultra-Low Pwr UART 9600 String, 32kHz ACLK
fet140_uart07_09600.c          USART0, Ultra-Low Pwr UART 9600 RX/TX, 32kHz ACLK
fet140_uart08_09600.c          USART0, UART 9600 Full-Duplex Transceiver, 32K ACLK
fet140_uart09_2400.c           USART0, SPI/UART 2400 alternating transmission, 32kHz ACLK
fet140_uart11_0115k_2.c        USART1, UART 115200 Echo ISR, XT2 HF XTAL SMCLK
fet140_uart11_02400.c          USART1, Ultra-Low Pwr UART 2400 Echo ISR, 32kHz ACLK
fet140_uart11_19200_2.c        USART1, UART 19200 Echo ISR, XT2 HF XTAL SMCLK
fet140_uart15_09600.c          USART1, Ultra-Low Pwr UART 9600 Echo ISR, 32kHz ACLK
fet140_wdt_01.c                WDT, Toggle P1.0, Interval Overflow ISR, DCO SMCLK
fet140_wdt_02.c                WDT, Toggle P1.0, Interval Overflow ISR, 32kHz ACLK
fet140_wdt_03.c                WDT, Toggle P1.0, Interval Overflow ISR, HF XTAL ACLK

