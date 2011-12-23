File Name                                        Description
----------------------------------------------------------------------------------------
MSP430FR57xx_01.c                                LED Toggle code example
MSP430FR57xx_active_01.c                         Stay in active mode with MCLK = 8MHz (uses while loop)
MSP430FR57xx_active_02.c                         Stay in active mode with MCLK = 8MHz (uses active mode test)
MSP430FR57xx_adc10_01.c                          ADC10, Sample A1, AVcc Ref, Set P1.0 if A1 > 0.5*AVcc
MSP430FR57xx_adc10_02.c                          ADC10, Sample A1, 1.5V Shared Ref, Set P1.0 if A1 > 0.5V
MSP430FR57xx_adc10_05.c                          ADC10, Sample A11, Lo_Batt, Clear P1.0 if AVcc < 2.3V
MSP430FR57xx_adc10_06.c                          ADC10, Internal Reference toggle
MSP430FR57xx_adc10_07.c                          ADC10, DMA Sample A1 64x, AVcc, Repeat Single, DCO
MSP430FR57xx_adc10_10.c                          ADC10, DMA Sample A2-0, 8-bit Res, Single Sequence, DCO
MSP430FR57xx_adc10_11.c                          ADC10, Sample A1, 1.5V Ref, TA0.1 Trig, Set P1.0 if A1>0.5V
MSP430FR57xx_adc10_15.c                          ADC10, DMA Sample A11 32x to FRAM, Int Ref, DCO
MSP430FR57xx_adc10_21.c                          ADC10, Window Comparator, 2.5V ref, Timer trigger, DCO
MSP430FR57xx_compD_01.c                          COMPD output Toggle in LPM4; Vcompare is compared against the internal 2.0V reference
MSP430FR57xx_compD_02.c                          COMPD output toggle in LPM4; Vcompare is compared against the internal reference 2.5V
MSP430FR57xx_compD_03.c                          COMPD interrupt capability; 
MSP430FR57xx_compD_04.c                          COMPD Toggle from LPM4; Ultra low power mode; 
MSP430FR57xx_compD_05.c                          COMPD Hysteresis, CBOUT Toggle in LPM4; High speed mode
MSP430FR57xx_dma_01.c                            DMA0, Repeated Block to-from RAM, Software Trigger
MSP430FR57xx_FRAMWrite.c                         FRAM In-System Programming w/ Long-Word write 
MSP430FR57xx_JTAG_01.c                           Secure device using a JTAG password
MSP430FR57xx_LPM3_01.c                           Enters LPM3 with ACLK = LFXT1
MSP430FR57xx_LPM3_02.c                           Enters LPM3 with ACLK = VLO 
MSP430FR57xx_LPM4.c                              Enters LPM4
MSP430FR57xx_MPU_02.c                            MPU write protection violation - PUC
MSP430FR57xx_MPY_01.c                            16x16 Unsigned Multiply
MSP430FR57xx_MPY_10.c                            32x32 Signed Multiply
MSP430FR57xx_MPY_11.c                            32x32 Signed Multiply Accumalate
MSP430FR57xx_P1_01.c                             Software Poll P1.4, Set P1.0 if P1.4 = 1
MSP430FR57xx_P1_03.c                             Software Port Interrupt Service on P1.4 from LPM4
MSP430FR57xx_ta0_01.c                            Timer0_A3, Toggle P1.0, CCR0 Cont Mode ISR, DCO SMCLK
MSP430FR57xx_ta0_02.c                            Timer0_A3, Toggle P1.0, CCR0 Up Mode ISR, DCO SMCLK
MSP430FR57xx_ta0_04.c                            Timer0_A3, Toggle P1.0, Overflow ISR, 32kHz ACLK
MSP430FR57xx_ta0_16.c                            Timer0_A3, PWM TA0.1-2, Up Mode, DCO SMCLK
MSP430FR57xx_ta0_17.c                            Timer0_A3, PWM TA0.1-2, Up Mode, 32KHz ACLK
MSP430FR57xx_ta1_05.c                            Timer1_A3, Toggle P1.0, CCR0 Cont Mode ISR, 32KHz ACLK 
MSP430FR57xx_ta1_06.c                            Timer1_A3, Toggle P1.0, CCR0 UP Mode ISR, 32KHz ACLK 
MSP430FR57xx_ta1_16.c                            Timer1_A3, PWM TA1.1-2, Up Mode, DCO SMCLK
MSP430FR57xx_ta1_17.c                            Timer1_A3, PWM TA1.1-2, Up Mode, 32KHz ACLK
MSP430FR57xx_tb0_01.c                            TimerB, Toggle P1.0, CCR0 Cont Mode ISR, DCO SMCLK
MSP430FR57xx_tb0_02.c                            TimerB, Toggle P1.0, CCR0 UP Mode ISR, DCO SMCLK
MSP430FR57xx_tb0_03.c                            TimerB, Toggle P1.0, Overflow ISR, DCO SMCLK 
MSP430FR57xx_tb0_04.c                            TimerB, Toggle P1.0, Overflow ISR, 32kHz ACLK
MSP430FR57xx_tb0_06.c                            TimerB, Toggle P1.0, CCR0 UP Mode ISR, 32KHz ACLK 
MSP430FR57xx_tb0_16.c                            TimerB, PWM TB0.1-2, Up Mode, DCO SMCLK
MSP430FR57xx_tb0_17.c                            TimerB, PWM TB0.1-2, Up Mode, 32KHz ACLK
MSP430FR57xx_UCS_01.c                            Configure MCLK for 8MHz operation
MSP430FR57xx_UCS_02.c                            Configure MCLK for 24MHz operation
MSP430FR57xx_UCS_03.c                            Output 32768Hz crystal on XT1 and observe failsafe 
MSP430FR57xx_uscia0_spi_09.c                     USCI_A0, SPI 3-Wire Master Incremented Data
MSP430FR57xx_uscia0_spi_10.c                     USCI_A0, SPI 3-Wire Slave Data Echo
MSP430FR57xx_uscia0_uart_03.c                    USCI_A0, Ultra-Low Pwr UART 9600 Echo ISR, 32kHz ACLK
MSP430FR57xx_uscia0_uart_04.c                    USCI_A0, 9600 UART external loopback
MSP430FR57xx_uscib0_i2c_04.c                     USCI_B0 I2C Master RX single bytes to MSP430 Slave
MSP430FR57xx_uscib0_i2c_05.c                     USCI_B0 I2C Slave TX single bytes from MSP430 Master
MSP430FR57xx_uscib0_i2c_06.c                     USCI_B0 I2C Master TX single bytes to MSP430 Slave
MSP430FR57xx_uscib0_i2c_07.c                     USCI_B0 I2C Slave RX single bytes from MSP430 Master
MSP430FR57xx_uscib0_i2c_10.c                     USCI_B0 I2C Master RX multiple bytes from MSP430 Slave
MSP430FR57xx_uscib0_i2c_11.c                     USCI_B0 I2C Slave TX multiple bytes to MSP430 Master
MSP430FR57xx_uscib0_i2c_12.c                     USCI_B0 I2C Slave TX multiple bytes to MSP430 Master using Early Transmit (preload feature)
MSP430FR57xx_uscib0_i2c_Master_MultiSlave.c      USCI_B0 Master TX to 4 unique slave addresses
MSP430FR57xx_uscib0_i2c_MultiSlave.c             USCI_B0 configured as 4 unique slave receviers.
MSP430FR57xx_WDT_01.c                            WDT, Toggle P1.0, Interval Overflow ISR, DCO SMCLK
MSP430FR57xx_WDT_02.c                            WDT, Toggle P1.0, Interval Overflow ISR, 32kHz ACLK
MSP430FR57xx_WDT_04.c                            WDT+ Failsafe Clock, WDT mode, DCO SMCLK
MSP430FR57xx_WDT_05.c                            Reset on Invalid Address fetch, Toggle P1.0

