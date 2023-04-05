#include "stm32f407xx.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_uart.h"
#include "stm32f4xx_hal_tim.h"

#define MCU MCU_STM32F7
  
#define TIME_CONSTANT	10				
  
extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;

extern I2C_HandleTypeDef hi2c1;
extern I2C_HandleTypeDef hi2c2;

#define REINITIALIZE_PERIPHERAL_I2C1   0x0001
#define REINITIALIZE_PERIPHERAL_I2C2   0x0002

#define HAL_I2C_NO_RESPONSE_TIMEOUT	100 

#define PI 3.1415926

