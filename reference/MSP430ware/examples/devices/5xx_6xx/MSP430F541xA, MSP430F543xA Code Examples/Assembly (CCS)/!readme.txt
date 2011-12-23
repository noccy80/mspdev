File Name                               Description
----------------------------------------------------------------------------------------
msp430x54xA_adc12_01.asm                ADC12, Sample A0, Set P1.0 if A0 > 0.5*AVcc
msp430x54xA_adc12_02.asm                ADC12, Using the Internal Reference
msp430x54xA_adc12_05.asm                ADC12, Using an External Reference
msp430x54xA_adc12_06.asm                ADC12, Repeated Sequence of Conversions
msp430x54xA_adc12_07.asm                ADC12, Repeated Single Channel Conversions
msp430x54xA_adc12_09.asm                ADC12, Sequence of Conversions (non-repeated)
msp430x54xA_adc12_10.asm                ADC12, Sample A10 Temp and Convert to oC and oF
msp430x54xA_dma_01.asm                  DMA0, Repeated Block to-from RAM, Software Trigger
msp430x54xA_dma_02.asm                  DMA0, Single Transfer in Block Mode UART1 9600, ACLK
msp430x54xA_dma_03.asm                  SPI TX & RX using DMA0 & DMA1 Single Transfer in Fixed Address Mode
msp430x54xA_dma_04.asm                  DMA0, Single transfer using ADC12 triggered by TimerB
msp430x54xA_flashwrite_01.asm           Single-Byte Flash In-System Programming, Copy SegC to SegD
msp430x54xA_flashwrite_02.asm           Flash In-System Programming w/ Long-Word write at 0x1800
msp430x54xA_LPM3_1.asm                  Enters LPM3 (ACLK = LFXT1)
msp430x54xA_LPM3_2.asm                  Enters LPM3 (ACLK = VLO)
msp430x54xA_MPY_1.asm                   16x16 Unsigned Multiply
msp430x54xA_MPY_10.asm                  32x32 Signed Multiply
msp430x54xA_MPY_11.asm                  32x32 Signed Multiply Accumalate
msp430x54xA_MPY_12.asm                  32x32 Unsigned Multiply Accumalate
msp430x54xA_MPY_13.asm                  Saturation mode overflow test
msp430x54xA_MPY_14.asm                  Saturation mode underflow test
msp430x54xA_MPY_15.asm                  Fractional mode, Q15 multiplication
msp430x54xA_MPY_2.asm                   8x8 Unsigned Multiply
msp430x54xA_MPY_3.asm                   16x16 Signed Multiply
msp430x54xA_MPY_4.asm                   8x8 Signed Multiply
msp430x54xA_MPY_5.asm                   16x16 Unsigned Multiply Accumulate
msp430x54xA_MPY_6.asm                   8x8 Unsigned Multiply Accumulate
msp430x54xA_MPY_7.asm                   16x16 Signed Multiply Accumulate
msp430x54xA_MPY_8.asm                   8x8 Signed Multiply Accumulate
msp430x54xA_MPY_9.asm                   32x32 Unsigned Multiply
msp430x54xA_OF_LFXT1_nmi.asm            LFXT1 Oscillator Fault Detection
msp430x54xA_P1_01.asm                   Software Poll P1.4, Set P1.0 if P1.4 = 1
msp430x54xA_P1_02.asm                   Software Port Interrupt Service on P1.4 from LPM4 with Internal Pull-up Resistance Enabled
msp430x54xA_P1_05.asm                   Write a byte to Port 1
msp430x54xA_PA_05.asm                   Write a Word to Port A (Port1+Port2)
msp430x54xA_RTC_01.asm                  RTC in Counter Mode toggles P1.0 every 1s
msp430x54xA_RTC_02.asm                  RTC_A in real time clock mode
msp430x54xA_ta3_01.asm                  Timer_A3, Toggle P1.0, CCR0 Cont. Mode ISR, DCO SMCLK
msp430x54xA_ta3_02.asm                  Timer_A3, Toggle P1.0, CCR0 Up Mode ISR, DCO SMCLK
msp430x54xA_ta3_03.asm                  Timer_A3, Toggle P1.0, Overflow ISR, DCO SMCLK
msp430x54xA_ta3_04.asm                  Timer_A3, Toggle P1.0, Overflow ISR, 32kHz ACLK
msp430x54xA_ta3_05.asm                  Timer_A3, Toggle P1.0, CCR0 Up Mode ISR, 32kHz ACLK
msp430x54xA_ta3_08.asm                  Timer_A3, Toggle P1.0;P2.1-3, Cont. Mode ISR, 32kHz ACLK
msp430x54xA_ta3_11.asm                  Timer_A3, Toggle P2.1/TA1.0, Up Mode, 32kHz ACLK
msp430x54xA_ta3_13.asm                  Timer_A3, Toggle P2.1/TA1.0, Up/Down Mode, DCO SMCLK
msp430x54xA_ta3_14.asm                  Timer_A3, Toggle P2.1/TA1.0, Up/Down Mode, 32kHz ACLK
msp430x54xA_ta3_16.asm                  Timer_A3, PWM TA1.1-2, Up Mode, DCO SMCLK
msp430x54xA_ta3_17.asm                  Timer_A3, PWM TA1.1-2, Up Mode, 32kHz ACLK
msp430x54xA_ta3_19.asm                  Timer_A3, PWM TA1.1-2, Up/Down Mode, DCO SMCLK
msp430x54xA_ta3_20.asm                  Timer_A3, PWM TA1.1-2, Up/Down Mode, 32kHz ACLK
msp430x54xA_tb_01.asm                   Timer_B, Toggle P1.0, CCR0 Cont. Mode ISR, DCO SMCLK
msp430x54xA_tb_02.asm                   Timer_B, Toggle P1.0, CCR0 Up Mode ISR, DCO SMCLK
msp430x54xA_tb_03.asm                   Timer_B, Toggle P1.0, Overflow ISR, DCO SMCLK
msp430x54xA_tb_04.asm                   Timer_B, Toggle P1.0, Overflow ISR, 32kHz ACLK
msp430x54xA_tb_05.asm                   Timer_B, Toggle P1.0, CCR0 Up Mode ISR, 32kHz ACLK
msp430x54xA_tb_10.asm                   Timer_B, PWM TB1-6, Up Mode, DCO SMCLK
msp430x54xA_UCS_1.asm                   Software Toggle P1.0 at Default DCO
msp430x54xA_UCS_2.asm                   Software Toggle P1.0 with 8MHz DCO
msp430x54xA_UCS_3.asm                   Software Toggle P1.0 with 12MHz DCO
msp430x54xA_UCS_4.asm                   FLL+, Runs Internal DCO at 2.45MHz with LFXT1 as Ref
msp430x54xA_UCS_5.asm                   VLO sources ACLK
msp430x54xA_UCS_6.asm                   XT1 sources ACLK 
msp430x54xA_UCS_7.asm                   FLL+, Output 32kHz Xtal + HF Xtal + Internal DCO
msp430x54xA_UCS_8.asm                   XT2 sources MCLK & SMCLK
msp430x54xA_UCS_9.asm                   LFXT1 HF Xtal + Internal DCO
msp430x54xA_uscia0_duplex_9600.asm      USCI_A0, UART 9600 Full-Duplex Transceiver, 32K ACLK
msp430x54xA_uscia0_spi_09.asm           USCI_A0, SPI 3-Wire Master Incremented Data
msp430x54xA_uscia0_spi_10.asm           USCI_A0, SPI 3-Wire Slave Data Echo
msp430x54xA_uscia0_uart_01.asm          USCI_A0, 115200 UART Echo ISR, DCO SMCLK
msp430x54xA_uscia0_uart_02.asm          USCI_A0, Ultra-Low Pwr UART 2400 Echo ISR, 32kHz ACLK
msp430x54xA_uscia0_uart_03.asm          USCI_A0, Ultra-Low Pwr UART 9600 Echo ISR, 32kHz ACLK
msp430x54xA_uscia0_uart_04.asm          USCI_A0, 9600 UART, SMCLK, LPM0, Echo with over-sampling
msp430x54xA_uscib0_i2c_04.asm           USCI_B0 I2C Master RX single bytes from MSP430 Master
msp430x54xA_uscib0_i2c_05.asm           USCI_B0 I2C Slave TX single bytes to MSP430 Slave
msp430x54xA_uscib0_i2c_06.asm           USCI_B0 I2C Master TX single bytes to MSP430 Slave
msp430x54xA_uscib0_i2c_07.asm           USCI_B0 I2C Slave RX single bytes from MSP430 Master
msp430x54xA_uscib0_i2c_08.asm           USCI_B0 I2C Master TX multiple bytes to MSP430 Slave
msp430x54xA_uscib0_i2c_09.asm           USCI_B0 I2C Slave RX multiple bytes from MSP430 Master
msp430x54xA_uscib0_i2c_10.asm           USCI_B0 I2C Master RX multiple bytes from MSP430 Slave
msp430x54xA_uscib0_i2c_11.asm           USCI_B0 I2C Slave TX multiple bytes to MSP430 Master
msp430x54xA_wdt_01.asm                  WDT, Toggle P1.0, Interval Overflow ISR, DCO SMCLK
msp430x54xA_wdt_02.asm                  WDT, Toggle P1.0, Interval Overflow ISR, 32kHz ACLK
msp430x54xA_wdt_04.asm                  WDT+ Failsafe Clock, WDT mode, DCO SMCLK
msp430x54xA_wdt_05.asm                  Reset on Invalid Address fetch, Toggle P1.0

