File Name                         Description
----------------------------------------------------------------------------------------
MSP430F51x2.c                     Toggle P1.0, default DCO
MSP430F51x2_adc10_01.c            ADC10, Sample A1, AVcc Ref, Set P1.0 if A1 > 0.5*AVcc 
MSP430F51x2_adc10_02.c            ADC10, Sample A1, 1.5V Shared Ref, Set P1.0 if A1 > 0.2V 
MSP430F51x2_adc10_03.c            ADC10, Sample A10 Temp, TA0 trigger, Set P1.0 if Temp ++ ~2C 
MSP430F51x2_adc10_04.c            ADC10, Sample A1, Signed, Set P1.0 if A1 > 0.5*AVcc
MSP430F51x2_adc10_05.c            ADC10, Sample A11, Lo_Batt, Clear P1.0 if AVcc < 2.3V
MSP430F51x2_adc10_06.c            ADC10, Internal Reference toggle 
MSP430F51x2_adc10_07.c            ADC10, DMA Sample A0 64x, AVcc, Repeat Single, DCO 
MSP430F51x2_adc10_10.c            ADC10, DMA Sample A2-0, 8-bit Res, Single Sequence, DCO 
MSP430F51x2_adc10_11.c            ADC10, Sample A0, 1.5V Shared Ref, ta0 Trig, Set P1.0 if > 0.5V 
MSP430F51x2_adc10_12.c            ADC10, Sample A7, 1.5V Shared Ref, ta0 Trig, Ultra-Low Pwr 
MSP430F51x2_adc10_13.c            ADC10, DMA Sample A1 32x, AVcc, TA0 Trig, DCO 
MSP430F51x2_adc10_14.c            ADC10, DMA Sample A1-0 32x, AVcc, Repeat Seq, DCO 
MSP430F51x2_adc10_15.c            ADC10, DMA Sample A10 32x to Flash, Int Ref, DCO 
MSP430F51x2_adc10_21.c            ADC10, Window Comparator, 2.5V Timer trigger, DCO
MSP430F51x2_compB_01.c            COMPB output Toggle in LPM4; 
MSP430F51x2_compB_02.c            COMPB output Toggle from LPM4; input channel CB1; 
MSP430F51x2_compB_03.c            COMPB interrupt capability; 
MSP430F51x2_compB_04.c            COMPB Toggle from LPM4; Ultra low power mode; 
MSP430F51x2_dma_01.c              DMA0, Repeated Block to-from RAM, Software Trigger
MSP430F51x2_dma_02.c              DMA0, Repeated Block UCA0UART 9600, TACCR2, ACLK
MSP430F51x2_flashwrite_01.c       Single-Byte Flash In-System Programming, Copy SegC to SegD
MSP430F51x2_flashwrite_02.c       Flash In-System Programming w/ Long-Word write at 0x1800
MSP430F51x2_flashwrite_03.c       Bank Erase from a Block while Executing Code from Another Block
MSP430F51x2_LPM3_01.c             Enters LPM3 with ACLK = LFXT1, REF0 disabled, VUSB LDO and SLDO disabled, SVS disabled
MSP430F51x2_LPM3_02.c             Enters LPM3 (ACLK = VLO)
MSP430F51x2_MPY_01.c              16x16 Unsigned Multiply
MSP430F51x2_MPY_02.c              8x8 Unsigned Multiply
MSP430F51x2_MPY_03.c              16x16 Signed Multiply
MSP430F51x2_MPY_04.c              8x8 Signed Multiply
MSP430F51x2_MPY_05.c              16x16 Unsigned Multiply Accumulate
MSP430F51x2_MPY_06.c              8x8 Unsigned Multiply Accumulate
MSP430F51x2_MPY_07.c              16x16 Signed Multiply Accumulate
MSP430F51x2_MPY_08.c              8x8 Signed Multiply Accumulate
MSP430F51x2_MPY_09.c              32x32 Unsigned Multiply
MSP430F51x2_MPY_10.c              32x32 Signed Multiply
MSP430F51x2_MPY_11.c              32x32 Signed Multiply Accumalate
MSP430F51x2_MPY_12.c              32x32 Unsigned Multiply Accumalate
MSP430F51x2_MPY_13.c              Saturation mode overflow test
MSP430F51x2_MPY_14.c              Saturation mode underflow test
MSP430F51x2_MPY_15.c              Fractional mode, Q15 multiplication
MSP430F51x2_P1_01.c               Software Poll P1.4, Set P1.0 if P1.4 = 1
MSP430F51x2_PA_05.c               Write a Word to Port A (Port1+Port2)
MSP430F51x2_PortMap_01.c          Port Mapping Port4; Single runtime configuration
MSP430F51x2_PortMap_02.c          Port Mapping single function to multiple pins; Single runtime configuration.
MSP430F51x2_PortMap_03.c          Port Map single function to multiple pins; Multiple runtime configurations
MSP430F51x2_ta0_02.c              Timer0_A3, Toggle P1.0, CCR0 Up Mode ISR, DCO SMCLK
MSP430F51x2_ta0_04.c              Timer0_A3, Toggle P1.0, Overflow ISR, 32kHz ACLK
MSP430F51x2_ta0_16.c              Timer0_A3, PWM TA0.1-2, Up Mode, DCO SMCLK
MSP430F51x2_ta0_17.c              Timer0_A3, PWM TA0.1-2, Up Mode, 32kHz ACLK
MSP430F51x2_td0_01.c              Timer0_D3, Toggle P1.0, CCR0 Cont. Mode ISR, DCO SMCLK
MSP430F51x2_td0_03.c              Timer0_D3, Toggle P1.0, Overflow ISR, DCO SMCLK
MSP430F51x2_td0_08.c              Timer0_D3, Toggle P1.0;P2.3-5, Cont. Mode ISR, 32kHz ACLK
MSP430F51x2_td0_14.c              Timer0_D3, Toggle TD0.0, Up/Down Mode, 32kHz ACLK
MSP430F51x2_td0_19.c              Timer0_D3, PWM TD0.0-2, Up/Down Mode, DCO SMCLK
MSP430F51x2_td0_20a.c             Timer0_D3, Hi-Res Calibrated mode, PWM TD0.0-2, DCO SMCLK
MSP430F51x2_td0_20b.c             Timer0_D3, Hi-Res Free Running mode, PWM TD0.0-2, TDCLK = 64Mhz
MSP430F51x2_td0_20c.c             Timer0_D3, Hi-Res Free Running mode, PWM TD0.0-2, TDCLK = 128Mhz
MSP430F51x2_td0_20d.c             Timer0_D3, Hi-Res Free Running mode, PWM TD0.0-2, TDCLK = 200Mhz
MSP430F51x2_td0_21.c              Timer0_D3, Hi-Res Free Running mode, PWM TD0.0-2, TDCLK = 256Mhz
MSP430F51x2_td0_22.c              Timer0_D3, Hi-Res Calibrated mode, max TimerD clock 
MSP430F51x2_td0_23.c              Timer0_D3, Combining two CCRx register to control one PWM channel
MSP430F51x2_td0_24.c              Timer0_D3, Single Input Capture mode, Normal Timer Mode
MSP430F51x2_td0_25.c              Timer0_D3, Dual Input Capture mode, Normal timer mode, Period Measurement
MSP430F51x2_td0_26.c              Timer0_D3, Dual Input Capture mode, Normal timer mode, DutyCycle Measurement
MSP430F51x2_tec_01.c              TimerD0/1-TEC, External Clear, Rising edge trigger
MSP430F51x2_tec_02.c              TimerD0/1-TEC, External Clear, Level trigger
MSP430F51x2_tec_03.c              TimerD0/1-TEC, External Fault, Rising edge and Level trigger 
MSP430F51x2_tec_04.c              TimerD0/1-TEC, External Fault, TECIV
MSP430F51x2_tec_05.c              TimerD0/1-TEC, Synchronizing timers, Normal timer mode
MSP430F51x2_tec_06.c              TimerD0/1-TEC, Synchronizing timers, Hi-res timer mode 
MSP430F51x2_tec_07.c              TimerD0/1-TEC, Synchronizing timers, Master Capture/Slave Compare
MSP430F51x2_UCS_01.c              Software Toggle P1.0 at Default DCO 
MSP430F51x2_UCS_02.c              Software Toggle P1.0 with 8MHz DCO
MSP430F51x2_UCS_03.c              Software Toggle P1.0 with 12MHz DCO
MSP430F51x2_UCS_04.c              FLL+, Runs Internal DCO at 2.45MHz, 32kHz XT1
MSP430F51x2_UCS_05.c              VLO sources ACLK
MSP430F51x2_UCS_06.c              XT1 sources ACLK
MSP430F51x2_UCS_10.c              Software Toggle P1.1 with 25MHz DCO
MSP430F51x2_uscia0_spi_09.c       USCI_A0, SPI 3-Wire Master Incremented Data
MSP430F51x2_uscia0_spi_10.c       USCI_A0, SPI 3-Wire Slave Data Echo
MSP430F51x2_uscia0_uart_01.c      USCI_A0, 115200 UART Echo ISR, DCO SMCLK
MSP430F51x2_uscia0_uart_03.c      USCI_A0, Ultra-Low Pwr UART 9600 Echo ISR, 32kHz ACLK
MSP430F51x2_uscib0_i2c_04.c       USCI_B0 I2C Master RX single bytes from MSP430 Master
MSP430F51x2_uscib0_i2c_05.c       USCI_B0 I2C Slave TX single bytes to MSP430 Slave
MSP430F51x2_uscib0_i2c_06.c       USCI_B0 I2C Master TX single bytes to MSP430 Slave
MSP430F51x2_uscib0_i2c_07.c       USCI_B0 I2C Slave RX single bytes from MSP430 Master
MSP430F51x2_uscib0_i2c_08.c       USCI_B0 I2C Master TX multiple bytes to MSP430 Slave
MSP430F51x2_uscib0_i2c_09.c       USCI_B0 I2C Slave RX multiple bytes from MSP430 Master
MSP430F51x2_uscib0_i2c_10.c       USCI_B0 I2C Master RX multiple bytes from MSP430 Slave
MSP430F51x2_uscib0_i2c_11.c       USCI_B0 I2C Slave TX multiple bytes to MSP430 Master
MSP430F51x2_WDT_01.c              WDT, Toggle P1.0, Interval Overflow ISR, DCO SMCLK
MSP430F51x2_WDT_02.c              WDT, Toggle P1.0, Interval Overflow ISR, 32kHz ACLK
MSP430F51x2_WDT_04.c              WDT+ Failsafe Clock, WDT mode, DCO SMCLK
MSP430F51x2_WDT_05.c              Reset on Invalid Address fetch, Toggle P1.0
MSP430F51x2_WDT_06.c              WDT+ Failsafe Clock, 32kHz ACLK
                                  

