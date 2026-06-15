# stm32-can-telemetry
This is a small two-board system built around a CAN bus. One STM32F4 board reads environmental data from a BME280 over I²C and motion data from its onboard LIS3DSH accelerometer over SPI, then sends the readings out on the bus. The second STM32F4 board receives those messages and shows the values on its built-in LCD. 
