File Name                                          Description
----------------------------------------------------------------------------------------
MSP430FR57xx_active_01.asm                         Stay in active mode with MCLK = 8MHz (uses while loop)
MSP430FR57xx_active_02.asm                         Stay in active mode with MCLK = 8MHz (uses active mode test)
MSP430FR57xx_adc10_01.asm                          ADC10, Sample A1, AVcc Ref, Set P1.0 if A1 > 0.5*Avcc
MSP430FR57xx_adc10_02.asm                          ADC10, Sample A1, 1.5V Shared Ref, Set P1.0 if A1 > 0.5V
MSP430FR57xx_adc10_21.asm                          ADC10, Window Comparator, 2.5V ref, Timer trigger, DCO
MSP430FR57xx_dma_01.asm                            DMA0, Repeated Block to-from RAM, Software Trigger
MSP430FR57xx_FRAMWrite.asm                         FRAM In-System Programming w/ Long-Word write 
MSP430FR57xx_LPM3_01.asm                           Enters LPM3 with ACLK = LFXT1
MSP430FR57xx_LPM3_02.asm                           Enters LPM3 with ACLK = VLO 
MSP430FR57xx_LPM4.asm                              Enters LPM4
MSP430FR57xx_MPU_02.asm                            MPU write protection violation - PUC
MSP430FR57xx_MPY_01.asm                            16x16 Unsigned Multiply
MSP430FR57xx_P1_03.asm                             Software Port Interrupt Service on P1.4 from LPM4
MSP430FR57xx_ta0_17.asm                            Timer0_A3, PWM TA0.1-2, Up Mode, 32KHz ACLK
MSP430FR57xx_ta1_05.asm                            Timer1_A3, Toggle P1.0, CCR0 Cont Mode ISR, 32KHz ACLK 
MSP430FR57xx_ta1_06.asm                            Timer1_A3, Toggle P1.0, CCR0 UP Mode ISR, 32KHz ACLK 
MSP430FR57xx_ta1_17.asm                            Timer1_A3, PWM TA1.1-2, Up Mode, 32KHz ACLK
MSP430FR57xx_tb0_04.asm                            TimerB, Toggle P1.0, Overflow ISR, 32kHz ACLK
MSP430FR57xx_tb0_06.asm                            TimerB, Toggle P1.0, CCR0 UP Mode ISR, 32KHz ACLK 
MSP430FR57xx_tb0_17.asm                            TimerB, PWM TB0.1-2, Up Mode, 32KHz ACLK
MSP430FR57xx_UCS_01.asm                            Configure MCLK for 8MHz operation
MSP430FR57xx_UCS_02.asm                            Configure MCLK for 24MHz operation
MSP430FR57xx_UCS_03.asm                            Output 32768Hz crystal on XT1 and observe failsafe
MSP430FR57xx_uscia0_spi_09.asm                     USCI_A0, SPI 3-Wire Master Incremented Data
MSP430FR57xx_uscia0_spi_10.asm                     USCI_A0, SPI 3-Wire Slave Data Echo
MSP430FR57xx_uscia0_uart04.asm                     USCI_A0, 9600 UART external loopback
MSP430FR57xx_uscib0_i2c_04.asm                     USCI_B0 I2C Master RX single bytes to MSP430 Slave
MSP430FR57xx_uscib0_i2c_05.asm                     USCI_B0 I2C Slave TX single bytes from MSP430 Master
MSP430FR57xx_uscib0_i2c_06.asm                     USCI_B0 I2C Master TX single bytes to MSP430 Slave
MSP430FR57xx_uscib0_i2c_07.asm                     USCI_B0 I2C Slave RX single bytes from MSP430 Master
MSP430FR57xx_uscib0_i2c_11.asm                     USCI_B0 I2C Slave TX multiple bytes to MSP430 Master
MSP430FR57xx_uscib0_i2c_Master_MultiSlave.asm      USCI_B0 Master TX to 4 unique slave addresses
MSP430FR57xx_uscib0_i2c_MultiSlave.asm             USCI_B0 configured as 4 unique slave receviers.

