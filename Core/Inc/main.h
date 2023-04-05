/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SW_1_Pin GPIO_PIN_2
#define SW_1_GPIO_Port GPIOE
#define SW_2_Pin GPIO_PIN_3
#define SW_2_GPIO_Port GPIOE
#define SW_3_Pin GPIO_PIN_4
#define SW_3_GPIO_Port GPIOE
#define SW_4_Pin GPIO_PIN_5
#define SW_4_GPIO_Port GPIOE
#define SPI_SHIELD_CS_Pin GPIO_PIN_6
#define SPI_SHIELD_CS_GPIO_Port GPIOE
#define ACCEL_INT_Pin GPIO_PIN_13
#define ACCEL_INT_GPIO_Port GPIOC
#define Relay_16_Pin GPIO_PIN_0
#define Relay_16_GPIO_Port GPIOF
#define Relay_15_Pin GPIO_PIN_1
#define Relay_15_GPIO_Port GPIOF
#define Relay_14_Pin GPIO_PIN_2
#define Relay_14_GPIO_Port GPIOF
#define AI_1_Pin GPIO_PIN_3
#define AI_1_GPIO_Port GPIOF
#define AI_2_Pin GPIO_PIN_4
#define AI_2_GPIO_Port GPIOF
#define AI_3_Pin GPIO_PIN_5
#define AI_3_GPIO_Port GPIOF
#define AI_4_Pin GPIO_PIN_6
#define AI_4_GPIO_Port GPIOF
#define AI_5_Pin GPIO_PIN_7
#define AI_5_GPIO_Port GPIOF
#define AI_6_Pin GPIO_PIN_8
#define AI_6_GPIO_Port GPIOF
#define AI_7_Pin GPIO_PIN_9
#define AI_7_GPIO_Port GPIOF
#define AI_8_Pin GPIO_PIN_10
#define AI_8_GPIO_Port GPIOF
#define AI_16_Pin GPIO_PIN_0
#define AI_16_GPIO_Port GPIOC
#define AI_15_Pin GPIO_PIN_1
#define AI_15_GPIO_Port GPIOC
#define AI_14_Pin GPIO_PIN_2
#define AI_14_GPIO_Port GPIOC
#define AI_13_Pin GPIO_PIN_3
#define AI_13_GPIO_Port GPIOC
#define USART2_RE_DE_Pin GPIO_PIN_1
#define USART2_RE_DE_GPIO_Port GPIOA
#define AI_12_Pin GPIO_PIN_4
#define AI_12_GPIO_Port GPIOA
#define AI_11_Pin GPIO_PIN_4
#define AI_11_GPIO_Port GPIOC
#define AI_10_Pin GPIO_PIN_5
#define AI_10_GPIO_Port GPIOC
#define AI_9_Pin GPIO_PIN_0
#define AI_9_GPIO_Port GPIOB
#define EEPROM_CS_SPI1_Pin GPIO_PIN_2
#define EEPROM_CS_SPI1_GPIO_Port GPIOB
#define DAC0_CS_SPI1_Pin GPIO_PIN_11
#define DAC0_CS_SPI1_GPIO_Port GPIOF
#define DAC1_CS_SPI1_Pin GPIO_PIN_12
#define DAC1_CS_SPI1_GPIO_Port GPIOF
#define Relay_13_Pin GPIO_PIN_13
#define Relay_13_GPIO_Port GPIOF
#define Relay_12_Pin GPIO_PIN_14
#define Relay_12_GPIO_Port GPIOF
#define Relay_11_Pin GPIO_PIN_15
#define Relay_11_GPIO_Port GPIOF
#define Relay_10_Pin GPIO_PIN_0
#define Relay_10_GPIO_Port GPIOG
#define Relay_9_Pin GPIO_PIN_1
#define Relay_9_GPIO_Port GPIOG
#define RAM_CS_SPI2_Pin GPIO_PIN_7
#define RAM_CS_SPI2_GPIO_Port GPIOE
#define AUX_EN_Pin GPIO_PIN_8
#define AUX_EN_GPIO_Port GPIOE
#define GYRO_CS_SPI1_Pin GPIO_PIN_9
#define GYRO_CS_SPI1_GPIO_Port GPIOE
#define DI_2_Pin GPIO_PIN_10
#define DI_2_GPIO_Port GPIOE
#define ACC_INTC0_Pin GPIO_PIN_11
#define ACC_INTC0_GPIO_Port GPIOE
#define ACC_INT2C1_Pin GPIO_PIN_12
#define ACC_INT2C1_GPIO_Port GPIOE
#define GYRO_INTC0_Pin GPIO_PIN_13
#define GYRO_INTC0_GPIO_Port GPIOE
#define GYRI_INTC1_Pin GPIO_PIN_14
#define GYRI_INTC1_GPIO_Port GPIOE
#define AUX_Pin GPIO_PIN_15
#define AUX_GPIO_Port GPIOE
#define DI_1_Pin GPIO_PIN_12
#define DI_1_GPIO_Port GPIOB
#define WIZNET_NRST_Pin GPIO_PIN_13
#define WIZNET_NRST_GPIO_Port GPIOB
#define DI_3_Pin GPIO_PIN_14
#define DI_3_GPIO_Port GPIOB
#define DI_4_Pin GPIO_PIN_15
#define DI_4_GPIO_Port GPIOB
#define DI_7_Pin GPIO_PIN_10
#define DI_7_GPIO_Port GPIOD
#define DI_8_Pin GPIO_PIN_11
#define DI_8_GPIO_Port GPIOD
#define Relay_1_Pin GPIO_PIN_12
#define Relay_1_GPIO_Port GPIOD
#define Relay_2_Pin GPIO_PIN_13
#define Relay_2_GPIO_Port GPIOD
#define Relay_3_Pin GPIO_PIN_14
#define Relay_3_GPIO_Port GPIOD
#define Relay_4_Pin GPIO_PIN_15
#define Relay_4_GPIO_Port GPIOD
#define ADC_BOARD1_Pin GPIO_PIN_3
#define ADC_BOARD1_GPIO_Port GPIOG
#define DI_5_Pin GPIO_PIN_5
#define DI_5_GPIO_Port GPIOG
#define DI_6_Pin GPIO_PIN_6
#define DI_6_GPIO_Port GPIOG
#define DI_9_Pin GPIO_PIN_7
#define DI_9_GPIO_Port GPIOG
#define DI_10_Pin GPIO_PIN_8
#define DI_10_GPIO_Port GPIOG
#define Relay_5_Pin GPIO_PIN_6
#define Relay_5_GPIO_Port GPIOC
#define Relay_6_Pin GPIO_PIN_7
#define Relay_6_GPIO_Port GPIOC
#define Relay_7_Pin GPIO_PIN_8
#define Relay_7_GPIO_Port GPIOC
#define Relay_8_Pin GPIO_PIN_9
#define Relay_8_GPIO_Port GPIOC
#define AUX_SET_Pin GPIO_PIN_8
#define AUX_SET_GPIO_Port GPIOA
#define Usart1_RE_DE_Pin GPIO_PIN_11
#define Usart1_RE_DE_GPIO_Port GPIOA
#define RF_TX_Pin GPIO_PIN_10
#define RF_TX_GPIO_Port GPIOC
#define RF_RX_Pin GPIO_PIN_11
#define RF_RX_GPIO_Port GPIOC
#define DEFAULT_BUTTON_Pin GPIO_PIN_0
#define DEFAULT_BUTTON_GPIO_Port GPIOD
#define Usart3_RE_DE_Pin GPIO_PIN_3
#define Usart3_RE_DE_GPIO_Port GPIOD
#define SPI1_CS_EXT_Pin GPIO_PIN_4
#define SPI1_CS_EXT_GPIO_Port GPIOD
#define LD_5_Pin GPIO_PIN_6
#define LD_5_GPIO_Port GPIOD
#define LD_4_Pin GPIO_PIN_7
#define LD_4_GPIO_Port GPIOD
#define DI_16_Pin GPIO_PIN_9
#define DI_16_GPIO_Port GPIOG
#define DI_15_Pin GPIO_PIN_10
#define DI_15_GPIO_Port GPIOG
#define DI_14_Pin GPIO_PIN_11
#define DI_14_GPIO_Port GPIOG
#define DI_13_Pin GPIO_PIN_12
#define DI_13_GPIO_Port GPIOG
#define DI_12_Pin GPIO_PIN_13
#define DI_12_GPIO_Port GPIOG
#define DI_11_Pin GPIO_PIN_14
#define DI_11_GPIO_Port GPIOG
#define ADC_BOARD2_Pin GPIO_PIN_5
#define ADC_BOARD2_GPIO_Port GPIOB
#define LD3_Pin GPIO_PIN_8
#define LD3_GPIO_Port GPIOB
#define LD2_Pin GPIO_PIN_9
#define LD2_GPIO_Port GPIOB
#define LD1_Pin GPIO_PIN_0
#define LD1_GPIO_Port GPIOE
#define LD0_Pin GPIO_PIN_1
#define LD0_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
