# STM32F4 CAN Bus Telemetry System
This is a small two-board system built around a CAN bus. One STM32F4 board reads environmental data from a BME280 over I²C and motion data from its onboard LIS3DSH accelerometer over SPI, then sends the readings out on the bus. The second STM32F4 board receives those messages and shows the values on its built-in LCD. 

The firmware runs without the vendor HAL. The peripheral drivers are written at the register level, the startup code and linker scripts are custom, and FreeRTOS handles task scheduling.
