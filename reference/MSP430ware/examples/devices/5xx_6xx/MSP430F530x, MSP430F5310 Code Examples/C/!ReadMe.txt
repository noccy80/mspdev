File Name                         Description
----------------------------------------------------------------------------------------
MSP430F530x.c                     Toggle P1.0/LED
MSP430F530x_adc10_01.c            ADC10, Sample A0, AVcc Ref, Set P1.0 if A0 > 0.5*AVcc
MSP430F530x_adc10_02.c            ADC10, Sample A0, 1.5V Shared Ref, Set P1.0 if A0 > 0.5V
MSP430F530x_adc10_03.c            ADC10, Sample A10 Temp, TA0.1 Trigger, Set P1.0 if Temp++ ~2C
MSP430F530x_adc10_04.c            ADC10, Sample A1, Signed, Set P1.0 if A1 > 0.5*AVcc
MSP430F530x_adc10_05.c            ADC10, Sample A11, Lo_Batt, Clear P1.0 if AVcc < 2.3V
MSP430F530x_adc10_06.c            ADC10, Internal Reference toggle
MSP430F530x_adc10_07.c            ADC10, DMA Sample A1 64x, AVcc, Repeat Single, DCO
MSP430F530x_adc10_10.c            ADC10, DMA Sample A2-0, 8-bit Res, Single Sequence, DCO
MSP430F530x_adc10_11.c            ADC10, Sample A0, 1.5V Ref, TA0.1 Trig, Set P1.0 if A0>0.5V
MSP430F530x_adc10_12.c            ADC10, Sample A5, 1.5V Ref, TA0.0 Trig, Ultra-Low Pwr
MSP430F530x_adc10_13.c            ADC10, DMA Sample A1 32x, 2.5V Ref, TB0 Trig, DCO
MSP430F530x_adc10_14.c            ADC10, DMA Sample A1-0 32x, AVcc, Repeat Seq, DCO
MSP430F530x_adc10_15.c            ADC10, DMA Sample A11 32x to Flash, Int Ref, DCO
MSP430F530x_adc10_21.c            ADC10, Window Comparator, 2.5V ref, Timer trigger, DCO
MSP430F530x_compB_01.c            COMPB output Toggle in LPM4; 
MSP430F530x_compB_02.c            COMPB output Toggle from LPM4; input channel CB1; 
MSP430F530x_compB_03.c            COMPB interrupt capability; 
MSP430F530x_compB_04.c            COMPB Toggle from LPM4; Ultra low power mode; 
MSP430F530x_compB_05.c            COMPB Hysteresis, CBOUT Toggle in LPM4; High speed mode
MSP430F530x_compB_06.c            COMPB and TIMERAx interaction (TA0.1, TA1.1)
MSP430F530x_dma_01.c              DMA0, Repeated Block to-from RAM, Software Trigger
MSP430F530x_dma_02.c              DMA0, Repeated Block UCA1UART 9600, TACCR2, ACLK
MSP430F530x_dma_03.c              SPI TX & RX using DMA0 & DMA1 Single Transfer in Fixed Address Mode
MSP430F530x_flashwrite_01.c       Single-Byte Flash In-System Programming, Copy SegC to SegD
MSP430F530x_flashwrite_02.c       Flash In-System Programming w/ Long-Word write at 0x1800
MSP430F530x_LDO_01.c              Internal LDO powering device VCC and PortU
MSP430F530x_LDO_02.c              Internal LDO enabled after device power-up
MSP430F530x_LPM3_01.c             Enters LPM3 with ACLK = LFXT1, REF0 disabled, VUSB LDO and SLDO disabled, SVS disabled
MSP430F530x_LPM3_02.c             Enters LPM3 (ACLK = VLO)
MSP430F530x_MPY_01.c              16x16 Unsigned Multiply
MSP430F530x_MPY_02.c              8x8 Unsigned Multiply
MSP430F530x_MPY_03.c              16x16 Signed Multiply
MSP430F530x_MPY_04.c              8x8 Signed Multiply
MSP430F530x_MPY_05.c              16x16 Unsigned Multiply Accumulate
MSP430F530x_MPY_06.c              8x8 Unsigned Multiply Accumulate
MSP430F530x_MPY_07.c              16x16 Signed Multiply Accumulate
MSP430F530x_MPY_08.c              8x8 Signed Multiply Accumulate
MSP430F530x_MPY_09.c              32x32 Unsigned Multiply
MSP430F530x_MPY_10.c              32x32 Signed Multiply
MSP430F530x_MPY_11.c              32x32 Signed Multiply Accumalate
MSP430F530x_MPY_12.c              32x32 Unsigned Multiply Accumalate
MSP430F530x_MPY_13.c              Saturation mode overflow test
MSP430F530x_MPY_14.c              Saturation mode underflow test
MSP430F530x_MPY_15.c              Fractional mode, Q15 multiplication
MSP430F530x_OF_LFXT1_nmi.c        LFXT1 Oscillator Fault Detection
MSP430F530x_P1_01.c               Software Poll P1.4, Set P1.0 if P1.4 = 1
MSP430F530x_P1_02.c               Software Port Interrupt Service on P1.4 from LPM4 with Internal Pull-up Resistance Enabled
MSP430F530x_P1_03.c               Software Port Interrupt Service on P1.4 from LPM4
MSP430F530x_PA_05.c               Write a Word to Port A (Port1+Port2)
MSP430F530x_PB_05.c               Write a Word to Port B (Port3+Port4)
MSP430F530x_PortMap_01.c          Port Mapping Port4; Single runtime configuration
MSP430F530x_PortMap_02.c          Port Mapping single function to multiple pins; Single runtime configuration.
MSP430F530x_PortMap_03.c          Port Map single function to multiple pins; Multiple runtime configurations
MSP430F530x_PU_01.c               Software Toggle PU.0/1
MSP430F530x_PU_02.c               Software Poll PU.0, Set P1.0 if PU.0 = 1
MSP430F530x_ta0_02.c              Timer0_A5, Toggle P1.0, CCR0 Up Mode ISR, DCO SMCLK
MSP430F530x_ta0_04.c              Timer0_A5, Toggle P1.0, Overflow ISR, 32kHz ACLK
MSP430F530x_ta0_16.c              Timer0_A5, PWM TA1.1-2, Up Mode, DCO SMCLK
MSP430F530x_ta0_17.c              Timer0_A5, PWM TA1.1-2, Up Mode, 32kHz ACLK
MSP430F530x_ta1_01.c              Timer1_A3, Toggle P1.0, CCR0 Cont. Mode ISR, DCO SMCLK
MSP430F530x_ta1_02.c              Timer1_A3, Toggle P1.0, CCR0 Up Mode ISR, DCO SMCLK
MSP430F530x_ta1_03.c              Timer1_A3, Toggle P1.0, Overflow ISR, DCO SMCLK
MSP430F530x_ta1_04.c              Timer1_A3, Toggle P1.0, Overflow ISR, 32kHz ACLK
MSP430F530x_ta1_05.c              Timer1_A3, Toggle P1.0, CCR0 Up Mode ISR, 32kHz ACLK
MSP430F530x_ta1_11.c              Timer1_A3, Toggle P1.7/TA1.0, Up Mode, 32kHz ACLK
MSP430F530x_ta1_13.c              Timer1_A3, Toggle P1.7/TA1.0, Up/Down Mode, DCO SMCLK
MSP430F530x_ta1_14.c              Timer1_A3, Toggle P1.7/TA1.0, Up/Down Mode, 32kHz ACLK
MSP430F530x_ta1_16.c              Timer1_A3, PWM TA1.1-2, Up Mode, DCO SMCLK
MSP430F530x_ta1_17.c              Timer1_A3, PWM TA1.1-2, Up Mode, 32kHz ACLK
MSP430F530x_ta1_19.c              Timer1_A3, PWM TA1.1-2, Up/Down Mode, DCO SMCLK
MSP430F530x_ta1_20.c              Timer1_A3, PWM TA1.1-2, Up/Down Mode, 32kHz ACLK
MSP430F530x_ta2_01.c              Timer2_A3, Toggle P1.0, CCR0 Cont. Mode ISR, DCO SMCLK
MSP430F530x_ta2_03.c              Timer2_A3, Toggle P1.0, Overflow ISR, DCO SMCLK
MSP430F530x_ta2_08.c              Timer2_A3, Toggle P1.0;P2.3-5, Cont. Mode ISR, 32kHz ACLK
MSP430F530x_ta2_14.c              Timer2_A3, Toggle P2.3/TA2.0, Up/Down Mode, 32kHz ACLK
MSP430F530x_ta2_19.c              Timer2_A3, PWM TA1.1-2, Up/Down Mode, DCO SMCLK
MSP430F530x_tb_01.c               Timer_B, Toggle P1.0, CCR0 Cont. Mode ISR, DCO SMCLK
MSP430F530x_tb_02.c               Timer_B, Toggle P1.0, CCR0 Up Mode ISR, DCO SMCLK
MSP430F530x_tb_03.c               Timer_B, Toggle P1.0, Overflow ISR, DCO SMCLK
MSP430F530x_tb_04.c               Timer_B, Toggle P1.0, Overflow ISR, 32kHz ACLK
MSP430F530x_tb_05.c               Timer_B, Toggle P1.0, CCR0 Up Mode ISR, 32kHz ACLK
MSP430F530x_UCS_01.c              Software Toggle P1.1 at Default DCO 
MSP430F530x_UCS_02.c              Software Toggle P1.1 with 8MHz DCO
MSP430F530x_UCS_03.c              Software Toggle P1.1 with 12MHz DCO
MSP430F530x_UCS_04.c              FLL+, Runs Internal DCO at 2.45MHz
MSP430F530x_UCS_05.c              VLO sources ACLK
MSP430F530x_UCS_06.c              XT1 sources ACLK
MSP430F530x_UCS_07.c              FLL+, Output 32kHz Xtal + HF Xtal + Internal DCO
MSP430F530x_UCS_08.c              XT2 sources MCLK & SMCLK
MSP430F530x_UCS_10.c              Software Toggle P1.1 with 25MHz DCO
MSP430F530x_uscia0_spi_09.c       USCI_A0, SPI 3-Wire Master Incremented Data
MSP430F530x_uscia0_spi_10.c       USCI_A0, SPI 3-Wire Slave Data Echo
MSP430F530x_uscia0_uart_01.c      USCI_A0, 115200 UART Echo ISR, DCO SMCLK
MSP430F530x_uscia0_uart_02.c      USCI_A0, Ultra-Low Pwr UART 2400 Echo ISR, 32kHz ACLK
MSP430F530x_uscia0_uart_03.c      USCI_A0, Ultra-Low Pwr UART 9600 Echo ISR, 32kHz ACLK
MSP430F530x_uscia0_uart_04.c      USCI_A0, 9600 UART, SMCLK, LPM0, Echo with over-sampling
MSP430F530x_uscib0_i2c_04.c       USCI_B0 I2C Master RX single bytes from MSP430 Master
MSP430F530x_uscib0_i2c_05.c       USCI_B0 I2C Slave TX single bytes to MSP430 Slave
MSP430F530x_uscib0_i2c_06.c       USCI_B0 I2C Master TX single bytes to MSP430 Slave
MSP430F530x_uscib0_i2c_07.c       USCI_B0 I2C Slave RX single bytes from MSP430 Master
MSP430F530x_uscib0_i2c_08.c       USCI_B0 I2C Master TX multiple bytes to MSP430 Slave
MSP430F530x_uscib0_i2c_09.c       USCI_B0 I2C Slave RX multiple bytes from MSP430 Master
MSP430F530x_uscib0_i2c_10.c       USCI_B0 I2C Master RX multiple bytes from MSP430 Slave
MSP430F530x_uscib0_i2c_11.c       USCI_B0 I2C Slave TX multiple bytes to MSP430 Master
MSP430F530x_WDT_01.c              WDT, Toggle P1.0, Interval Overflow ISR, DCO SMCLK
MSP430F530x_WDT_02.c              WDT, Toggle P1.0, Interval Overflow ISR, 32kHz ACLK
MSP430F530x_WDT_04.c              WDT+ Failsafe Clock, WDT mode, DCO SMCLK
MSP430F530x_WDT_05.c              Reset on Invalid Address fetch, Toggle P1.0
MSP430F530x_WDT_06.c              WDT+ Failsafe Clock, 32kHz ACLK

