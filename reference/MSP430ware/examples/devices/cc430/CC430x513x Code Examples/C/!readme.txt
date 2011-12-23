File Name                            Description
----------------------------------------------------------------------------------------
cc430x513x_adc12_01.c                ADC12, Sample A0, Set P1.0 if A0 > 0.5*AVcc
cc430x513x_adc12_02.c                ADC12, Using the Internal Reference
cc430x513x_adc12_05.c                ADC12, Using an External Reference
cc430x513x_adc12_06.c                ADC12, Repeated Sequence of Conversions
cc430x513x_adc12_07.c                ADC12, Repeated Single Channel Conversions
cc430x513x_adc12_09.c                ADC12, Sequence of Conversions (non-repeated)
cc430x513x_adc12_10.c                ADC12, Sample A10 Temp and Convert to oC and oF
cc430x513x_compB_01.c                COMPB output Toggle in LPM4; internal 2.0V reference
cc430x513x_compB_03.c                COMPB interrupts; internal 1.5V reference
cc430x513x_compB_04.c                CBOUT from LPM4; CompB in ultra low power mode; Vref = Vcc*1/2
cc430x513x_compB_05.c                COMPB Hysteresis, CBOUT Toggle in LPM4; High speed mode
cc430x513x_compB_06.c                COMPB and TIMERAx interaction (TA0.1, TA1.1)
cc430x513x_core_01.c                 Reset on Invalid Address fetch, Toggle P1.0
cc430x513x_dma_01.c                  DMA0, Repeated Block to-from RAM, Software Trigger
cc430x513x_dma_02.c                  DMA0, Single Transfer in Block Mode UART1 9600, ACLK
cc430x513x_dma_03.c                  SPI TX & RX using DMA0 & DMA1 Single Transfer in Fixed Address Mode
cc430x513x_dma_04.c                  DMA0, Single transfer using ADC12 triggered by TimerB
cc430x513x_dma_05.c                  USCI_A0, 115200 UART RX & TX, DMA enabled
cc430x513x_flashwrite_01.c           Single-Byte Flash In-System Programming, Copy SegC to SegD
cc430x513x_flashwrite_02.c           Flash In-System Programming w/ Long-Word write at 0x1800
cc430x513x_LPM3_1.c                  Enters LPM3 (ACLK = LFXT1)
cc430x513x_LPM3_2.c                  Enters LPM3 (ACLK = VLO)
cc430x513x_MPY_1.c                   16x16 Unsigned Multiply
cc430x513x_MPY_10.c                  32x32 Signed Multiply
cc430x513x_MPY_11.c                  32x32 Signed Multiply Accumalate
cc430x513x_MPY_12.c                  32x32 Unsigned Multiply Accumalate
cc430x513x_MPY_13.c                  Saturation mode overflow test
cc430x513x_MPY_14.c                  Saturation mode underflow test
cc430x513x_MPY_15.c                  Fractional mode, Q15 multiplication
cc430x513x_MPY_2.c                   8x8 Unsigned Multiply
cc430x513x_MPY_3.c                   16x16 Signed Multiply
cc430x513x_MPY_4.c                   8x8 Signed Multiply
cc430x513x_MPY_5.c                   16x16 Unsigned Multiply Accumulate
cc430x513x_MPY_6.c                   8x8 Unsigned Multiply Accumulate
cc430x513x_MPY_7.c                   16x16 Signed Multiply Accumulate
cc430x513x_MPY_8.c                   8x8 Signed Multiply Accumulate
cc430x513x_MPY_9.c                   32x32 Unsigned Multiply
cc430x513x_OF_LFXT1_nmi.c            LFXT1 Oscillator Fault Detection
cc430x513x_P1_01.c                   Software Poll P1.4, Set P1.0 if P1.4 = 1
cc430x513x_P1_02.c                   Software Port interrupt on P1.4 from LPM4; Internal Pull-up 
cc430x513x_P1_05.c                   Write a byte to Port 1
cc430x513x_PA_05.c                   Write a Word to Port A (Port1+Port2)
cc430x513x_PMM.c                     PMM library for setting PMMCOREV levels
cc430x513x_PortMap_01.c              Port Mapping Port2; Single runtime configuration
cc430x513x_PortMap_02.c              Port Mapping single function to multiple pins;
cc430x513x_PortMap_03.c              Port Map single function to multiple pins; Multiple runtime configurations
cc430x513x_RTC_01.c                  RTC in Counter Mode toggles P1.0 every 1s
cc430x513x_ta3_01.c                  Timer_A3, Toggle P1.0, CCR0 Cont. Mode ISR, DCO SMCLK
cc430x513x_ta3_02.c                  Timer_A3, Toggle P1.0, CCR0 Up Mode ISR, DCO SMCLK
cc430x513x_ta3_03.c                  Timer_A3, Toggle P1.0, Overflow ISR, DCO SMCLK
cc430x513x_ta3_04.c                  Timer_A3, Toggle P1.0, Overflow ISR, 32kHz ACLK
cc430x513x_ta3_05.c                  Timer_A3, Toggle P1.0, CCR0 Up Mode ISR, 32kHz ACLK
cc430x513x_ta3_08.c                  Timer_A3, Toggle P1.0;P2.1-3, Cont. Mode ISR, 32kHz ACLK
cc430x513x_ta3_11.c                  Timer_A3, Toggle P2.1/TA1.0, Up Mode, 32kHz ACLK
cc430x513x_ta3_13.c                  Timer_A3, Toggle P2.1/TA1.0, Up/Down Mode, DCO SMCLK
cc430x513x_ta3_14.c                  Timer_A3, Toggle P2.1/TA1.0, Up/Down Mode, 32kHz ACLK
cc430x513x_ta3_16.c                  Timer_A3, PWM TA1.1-2, Up Mode, DCO SMCLK
cc430x513x_ta3_17.c                  Timer_A3, PWM TA1.1-2, Up Mode, 32kHz ACLK
cc430x513x_ta3_19.c                  Timer_A3, PWM TA1.1-2, Up/Down Mode, DCO SMCLK
cc430x513x_ta3_20.c                  Timer_A3, PWM TA1.1-2, Up/Down Mode, 32kHz ACLK
cc430x513x_UCS_1.c                   Software Toggle P1.0 at Default DCO
cc430x513x_UCS_2.c                   Software Toggle P1.0 with 8MHz DCO
cc430x513x_UCS_3.c                   Software Toggle P1.0 with 12MHz DCO
cc430x513x_UCS_4.c                   FLL+, Runs Internal DCO at 2.45MHz with LFXT1 as Ref
cc430x513x_UCS_5.c                   VLO sources ACLK
cc430x513x_UCS_6.c                   XT1 sources ACLK. Toggles P1.0
cc430x513x_UCS_7.c                   FLL+, Output 32kHz Xtal + HF Xtal + Internal DCO
cc430x513x_UCS_8.c                   XT2 sources MCLK & SMCLK
cc430x513x_UCS_9.c                   LFXT1 HF Xtal + Internal DCO
cc430x513x_uscia0_duplex_9600.c      USCI_A0, UART 9600 Full-Duplex Transceiver, 32K ACLK
cc430x513x_uscia0_spi_09.c           USCI_A0, SPI 3-Wire Master Incremented Data
cc430x513x_uscia0_spi_10.c           USCI_A0, SPI 3-Wire Slave Data Echo
cc430x513x_uscia0_uart_01.c          USCI_A0, 115200 UART Echo ISR, DCO SMCLK
cc430x513x_uscia0_uart_02.c          USCI_A0, Ultra-Low Pwr UART 2400 Echo ISR, 32kHz ACLK
cc430x513x_uscia0_uart_03.c          USCI_A0, Ultra-Low Pwr UART 9600 Echo ISR, 32kHz ACLK
cc430x513x_uscia0_uart_04.c          USCI_A0, 9600 UART, SMCLK, LPM0, Echo with over-sampling
cc430x513x_uscib0_i2c_04.c           USCI_B0 I2C Master RX single bytes from cc430 Master
cc430x513x_uscib0_i2c_05.c           USCI_B0 I2C Slave TX single bytes to cc430 Slave
cc430x513x_uscib0_i2c_06.c           USCI_B0 I2C Master TX single bytes to cc430 Slave
cc430x513x_uscib0_i2c_07.c           USCI_B0 I2C Slave RX single bytes from cc430 Master
cc430x513x_uscib0_i2c_08.c           USCI_B0 I2C Master TX multiple bytes to cc430 Slave
cc430x513x_uscib0_i2c_09.c           USCI_B0 I2C Slave RX multiple bytes from cc430 Master
cc430x513x_uscib0_i2c_10.c           USCI_B0 I2C Master RX multiple bytes from cc430 Slave
cc430x513x_uscib0_i2c_11.c           USCI_B0 I2C Slave TX multiple bytes to cc430 Master
cc430x513x_wdt_01.c                  WDT, Toggle P1.0, Interval Overflow ISR, DCO SMCLK
cc430x513x_wdt_02.c                  WDT, Toggle P1.0, Interval Overflow ISR, 32kHz ACLK
cc430x513x_wdt_04.c                  WDT+ Failsafe Clock, WDT mode, DCO SMCLK

