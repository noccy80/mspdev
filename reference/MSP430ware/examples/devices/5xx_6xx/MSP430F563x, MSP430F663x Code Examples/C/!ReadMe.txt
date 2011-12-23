File Name                         Description
----------------------------------------------------------------------------------------
msp430f66xx_1.c                   LED Toggle code example
msp430f66xx_adc_01.c              ADC12, Sample A0, Set P1.0 if A0 > 0.5*AVcc
msp430f66xx_adc_02.c              ADC12, Using the Internal Reference
msp430f66xx_adc_05.c              ADC12, Using an External Reference
msp430f66xx_adc_06.c              ADC12, Repeated Sequence of Conversions
msp430f66xx_adc_07.c              ADC12, Repeated Single Channel Conversions
msp430f66xx_adc_08.c              ADC12, Using A8 and A9 Ext Channels for Conversion
msp430f66xx_adc_09.c              ADC12, Sequence of Conversions (non-repeated)
msp430f66xx_adc_10.c              ADC12, Sample A10 Temp and Convert to oC and oF
msp430f66xx_compB_01.c            COMPB output Toggle in LPM4; 
msp430f66xx_compB_02.c            COMPB output Toggle from LPM4; input channel CB1; 
msp430f66xx_compB_03.c            COMPB interrupt capability; 
msp430f66xx_compB_04.c            COMPB Toggle from LPM4; Ultra low power mode; 
msp430f66xx_compB_05.c            COMPB Hysteresis, CBOUT Toggle in LPM4; High speed mode
msp430f66xx_dac12_1.c             DAC12_0, Output 1.5V on DAC0
msp430f66xx_dac12_2.c             DAC12_1, Output 0.75V on DAC1
msp430f66xx_dac12_3.c             DAC12_0, Output Voltage Ramp on DAC0
msp430f66xx_dma_01.c              DMA0, Repeated Block to-from RAM, Software Trigger
msp430f66xx_dma_02.c              DMA0, Repeated Block UCA1UART 9600, TACCR2, ACLK
msp430f66xx_dma_04.c              DMA0, Single transfer using ADC12 triggered by TimerB
msp430f66xx_flashwrite_01.c       Single-Byte Flash In-System Programming, Copy SegC to SegD
msp430f66xx_flashwrite_02.c       Flash In-System Programming w/ Long-Word write at 0x1800
msp430f66xx_LPM3_01.c             Enters LPM3 with ACLK = LFXT1, REF0 disabled, VUSB LDO and SLDO disabled, SVS disabled
msp430f66xx_LPM3_02.c             Enters LPM3 with ACLK = LFXT1, REF0 disabled, VUSB LDO and SLDO disabled, SVS default state
msp430f66xx_LPM3_03.c             Enters LPM3 with ACLK =VLO, REF0 disabled, VUSB LDO and SLDO disabled, SVS default state
msp430f66xx_LPM4.c                Enters LPM4
msp430f66xx_MPY_01.c              16x16 Unsigned Multiply
msp430f66xx_MPY_10.c              32x32 Signed Multiply
msp430f66xx_MPY_11.c              32x32 Signed Multiply Accumalate
msp430f66xx_PortMap_01.c          Port Mapping Port4; Single runtime configuration
msp430f66xx_PortMap_02.c          Port Mapping single function to multiple pins; Single runtime configuration.
msp430f66xx_PortMap_03.c          Port Map single function to multiple pins; Multiple runtime configurations
msp430f66xx_ta0_02.c              Timer0_A5, Toggle P1.0, CCR0 Up Mode ISR, DCO SMCLK
msp430f66xx_ta0_04.c              Timer0_A5, Toggle P1.0, Overflow ISR, 32kHz ACLK
msp430f66xx_ta0_16.c              Timer0_A5, PWM TA1.1-2, Up Mode, DCO SMCLK
msp430f66xx_ta0_17.c              Timer0_A5, PWM TA1.1-2, Up Mode, 32kHz ACLK
msp430f66xx_ta1_01.c              Timer1_A3, Toggle P1.0, CCR0 Cont. Mode ISR, DCO SMCLK
msp430f66xx_ta1_02.c              Timer1_A3, Toggle P1.0, CCR0 Up Mode ISR, DCO SMCLK
msp430f66xx_ta1_03.c              Timer1_A3, Toggle P1.0, Overflow ISR, DCO SMCLK
msp430f66xx_ta1_04.c              Timer1_A3, Toggle P1.0, Overflow ISR, 32kHz ACLK
msp430f66xx_ta1_05.c              Timer1_A3, Toggle P1.0, CCR0 Up Mode ISR, 32kHz ACLK
msp430f66xx_ta1_11.c              Timer1_A3, Toggle P1.7/TA1.0, Up Mode, 32kHz ACLK
msp430f66xx_ta1_13.c              Timer1_A3, Toggle P1.7/TA1.0, Up/Down Mode, DCO SMCLK
msp430f66xx_ta1_14.c              Timer1_A3, Toggle P1.7/TA1.0, Up/Down Mode, 32kHz ACLK
msp430f66xx_ta1_16.c              Timer1_A3, PWM TA1.1-2, Up Mode, DCO SMCLK
msp430f66xx_ta1_17.c              Timer1_A3, PWM TA1.1-2, Up Mode, 32kHz ACLK
msp430f66xx_ta1_19.c              Timer1_A3, PWM TA1.1-2, Up/Down Mode, DCO SMCLK
msp430f66xx_ta1_20.c              Timer1_A3, PWM TA1.1-2, Up/Down Mode, 32kHz ACLK
msp430f66xx_ta2_01.c              Timer2_A3, Toggle P1.0, CCR0 Cont. Mode ISR, DCO SMCLK
msp430f66xx_ta2_03.c              Timer2_A3, Toggle P1.0, Overflow ISR, DCO SMCLK
msp430f66xx_ta2_08.c              Timer2_A3, Toggle P1.0;P2.3-5, Cont. Mode ISR, 32kHz ACLK
msp430f66xx_ta2_14.c              Timer2_A3, Toggle P2.3/TA2.0, Up/Down Mode, 32kHz ACLK
msp430f66xx_ta2_19.c              Timer2_A3, PWM TA1.1-2, Up/Down Mode, DCO SMCLK
msp430f66xx_tb_01.c               Timer_B, Toggle P1.0, CCR0 Cont. Mode ISR, DCO SMCLK
msp430f66xx_tb_02.c               Timer_B, Toggle P1.0, CCR0 Up Mode ISR, DCO SMCLK
msp430f66xx_tb_03.c               Timer_B, Toggle P1.0, Overflow ISR, DCO SMCLK
msp430f66xx_tb_04.c               Timer_B, Toggle P1.0, Overflow ISR, 32kHz ACLK
msp430f66xx_tb_05.c               Timer_B, Toggle P1.0, CCR0 Up Mode ISR, 32kHz ACLK
msp430f66xx_tb_10.c               Timer_B, PWM TB1-6, Up Mode, DCO SMCLK
msp430f66xx_UCS_03.c              Software Toggle P1.1 with 12MHz DCO
msp430f66xx_UCS_04.c              FLL+, Runs Internal DCO at 2.45MHz
msp430f66xx_UCS_05.c              VLO sources ACLK
msp430f66xx_UCS_06.c              XT1 sources ACLK
msp430f66xx_UCS_07.c              FLL+, Output 32kHz Xtal + HF Xtal + Internal DCO
msp430f66xx_UCS_08.c              XT2 sources MCLK & SMCLK
msp430f66xx_uscia0_spi_09.c       USCI_A0, SPI 3-Wire Master Incremented Data
msp430f66xx_uscia0_spi_10.c       USCI_A0, SPI 3-Wire Slave Data Echo
msp430f66xx_uscia0_uart_03.c      USCI_A0, Ultra-Low Pwr UART 9600 Echo ISR, 32kHz ACLK
msp430f66xx_uscia0_uart_04.c      USCI_A0, 9600 UART, SMCLK, LPM0, Echo with over-sampling
msp430f66xx_uscib0_i2c_06.c       USCI_B0 I2C Master TX single bytes to MSP430 Slave
msp430f66xx_uscib0_i2c_07.c       USCI_B0 I2C Slave RX single bytes from MSP430 Master
msp430f66xx_uscib0_i2c_08.c       USCI_B0 I2C Master TX multiple bytes to MSP430 Slave
msp430f66xx_uscib0_i2c_09.c       USCI_B0 I2C Slave RX multiple bytes from MSP430 Master
msp430f66xx_uscib0_i2c_10.c       USCI_B0 I2C Master RX multiple bytes from MSP430 Slave
msp430f66xx_uscib0_i2c_11.c       USCI_B0 I2C Slave TX multiple bytes to MSP430 Master
msp430f66xx_WDT_01.c              WDT, Toggle P1.0, Interval Overflow ISR, DCO SMCLK
msp430f66xx_WDT_02.c              WDT, Toggle P1.0, Interval Overflow ISR, 32kHz ACLK
msp430f66xx_WDT_04.c              WDT+ Failsafe Clock, WDT mode, DCO SMCLK
msp430f66xx_WDT_05.c              Reset on Invalid Address fetch, Toggle P1.0
msp430f66xx_WDT_06.c              WDT+ Failsafe Clock, 32kHz ACLK

