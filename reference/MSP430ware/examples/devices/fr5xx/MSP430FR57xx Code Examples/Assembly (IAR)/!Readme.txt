File Name                                          Description
----------------------------------------------------------------------------------------
msp430fr57xx_active_01.s43                         Stay in active mode with MCLK = 8MHz (uses while loop)
msp430fr57xx_active_02.s43                         Stay in active mode with MCLK = 8MHz (uses active mode test)
msp430fr57xx_adc10_01.s43                          ADC10, Sample A1, AVcc Ref, Set P1.0 if A1 > 0.5*Avcc
msp430fr57xx_adc10_02.s43                          ADC10, Sample A1, 1.5V Shared Ref, Set P1.0 if A1 > 0.5V
msp430fr57xx_adc10_21.s43                          ADC10, Window Comparator, 2.5V ref, Timer trigger, DCO
msp430fr57xx_dma_01.s43                            DMA0, Repeated Block to-from RAM, Software Trigger
msp430fr57xx_FRAMWrite.s43                         FRAM In-System Programming w/ Long-Word write 
msp430fr57xx_LPM3_01.s43                           Enters LPM3 with ACLK = LFXT1
msp430fr57xx_LPM3_02.s43                           Enters LPM3 with ACLK = VLO 
msp430fr57xx_LPM4.s43                              Enters LPM4
msp430fr57xx_MPU_02.s43                            MPU write protection violation - PUC
msp430fr57xx_MPY_01.s43                            16x16 Unsigned Multiply
msp430fr57xx_P1_03.s43                             Software Port Interrupt Service on P1.4 from LPM4
msp430fr57xx_ta0_17.s43                            Timer0_A3, PWM TA0.1-2, Up Mode, 32KHz ACLK
msp430fr57xx_ta1_05.s43                            Timer1_A3, Toggle P1.0, CCR0 Cont Mode ISR, 32KHz ACLK 
msp430fr57xx_ta1_06.s43                            Timer1_A3, Toggle P1.0, CCR0 UP Mode ISR, 32KHz ACLK 
msp430fr57xx_ta1_17.s43                            Timer1_A3, PWM TA1.1-2, Up Mode, 32KHz ACLK
msp430fr57xx_tb0_04.s43                            TimerB, Toggle P1.0, Overflow ISR, 32kHz ACLK
msp430fr57xx_tb0_06.s43                            TimerB, Toggle P1.0, CCR0 UP Mode ISR, 32KHz ACLK 
msp430fr57xx_tb0_17.s43                            TimerB, PWM TB0.1-2, Up Mode, 32KHz ACLK
msp430fr57xx_UCS_01.s43                            Configure MCLK for 8MHz operation
msp430fr57xx_UCS_02.s43                            Configure MCLK for 24MHz operation
msp430fr57xx_UCS_03.s43                            Output 32768Hz crystal on XT1 and observe failsafe
msp430fr57xx_uscia0_spi_09.s43                     USCI_A0, SPI 3-Wire Master Incremented Data
msp430fr57xx_uscia0_spi_10.s43                     USCI_A0, SPI 3-Wire Slave Data Echo
msp430fr57xx_uscia0_uart04.s43                     USCI_A0, 9600 UART external loopback
msp430fr57xx_uscib0_i2c_04.s43                     USCI_B0 I2C Master RX single bytes to MSP430 Slave
msp430fr57xx_uscib0_i2c_05.s43                     USCI_B0 I2C Slave TX single bytes from MSP430 Master
msp430fr57xx_uscib0_i2c_06.s43                     USCI_B0 I2C Master TX single bytes to MSP430 Slave
msp430fr57xx_uscib0_i2c_07.s43                     USCI_B0 I2C Slave RX single bytes from MSP430 Master
msp430fr57xx_uscib0_i2c_11.s43                     USCI_B0 I2C Slave TX multiple bytes to MSP430 Master
msp430fr57xx_uscib0_i2c_Master_MultiSlave.s43      USCI_B0 Master TX to 4 unique slave addresses
msp430fr57xx_uscib0_i2c_MultiSlave.s43             USCI_B0 configured as 4 unique slave receviers.

