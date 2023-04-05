/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "WatchDog.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "MicroPeripheral.h"
#include "PlcDefinition.h"
#include "Registers.h"
#include "DataTypeGsm.h"
#include "HoldingRegister.h"
#include "DataRegisterAssigment.h"
#include "DataSendProcess.h"
#include "Uarts.h"
#include "UartPortTimerProcess.h"
#include "Rtc.h"
#include "AnalogInput.h"
#include "DigitalInput.h"
#include "DigitalOutput.h"
#include "Modbus.h"
#include "TimerProcess.h"
#include "MC25LCxxx.h"
#include "Kalman.h"
#include "DefaultProcess.h"
#include "Initialize.h"
#include "Coils.h"
#include "Peripheral.h"
#include "PeripheralTest.h"
#include "SystemStates.h"
#include "ButtonProcess.h"
#include "HMI.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc3;

I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c2;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim7;
TIM_HandleTypeDef htim8;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */

strcUART Uart[UART_COUNT];


#define BUFF_SIZE 800
uint8_t convEnd = 0;			//conv end flag

uint16_t adcBuff[BUFF_SIZE] = {0};		//to store converted values
uint16_t adcData[BUFF_SIZE] = {0};		//to use as a second buffer

strcREGISTERS Registers;

strcMASTERCODE MasterCode;

strcPLC Plc;

strcGSM GSM;

strcHMI HMI;

strcDATASENDCENTER DataSendCenter;

strcALERTES AlertES;

strcALERT Alerts;

strcCRITICALS Criticals;

strcAnalogInput AnalogInput;

strcSYSTEM System;

strcRTC RtcData;

strcRTCCounter RtcCounter;

strcADC ADC_Modules[MAX_AI_BOARD_COUNT];

strcKalman mKalmanFilter[AI_CHANNEL_COUNT];

unsigned char  HoldingRegister_Data[32768] ;

unsigned char  StatusRegister_Data[32768] ;

unsigned int InputRegister_Data[4];

unsigned int  CoilRegister_Data[COIL_INT_COUNT];

//
// Hex Data Array H
//
const unsigned char HexArray[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
//
// InputParamaterList
//
unsigned char *InputParameterList[2];

static void MX_USART1_UART_Init_Custom(void);
void TankKg(void);

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_ADC3_Init(void);
static void MX_I2C1_Init(void);
static void MX_I2C2_Init(void);
static void MX_SPI1_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM7_Init(void);
static void MX_TIM8_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
//
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//	unsigned short PortNo = 0;
//	unsigned char Data;
//	if(huart->Instance == USART1)
//		{
//			PortNo = 1;
//			Data = USART1->DR;
//		}
//	else
//		{
//			if(huart->Instance == USART2)
//				{
//					PortNo = 2;
//					Data = USART2->DR;
//				}
//			else
//				{
//					if(huart->Instance == USART3)
//									{
//										PortNo = 3;
//										Data = USART3->DR;
//									}
//				}
//
//		}
//
//	if(PortNo > 0 )
//		{
//			Uart[PortNo].PortDataEndCounter  = 0;
//
//			if(*Uart[PortNo].Offset >= *Uart[PortNo].BufferSize ) *Uart[PortNo].Offset  = 0;
//
//			Uart[PortNo].Data[*Uart[PortNo].Offset] =  Data;
//
//			*Uart[PortNo].Status = PORT_DATA_START;
//			*Uart[PortNo].Offset = *Uart[PortNo].Offset  + 1;
//		}
//}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
 {
	 unsigned short Counter;
	 //
	 // Timers And Port Data End
	 //
	 if(htim->Instance==TIM2)
		 {
			  for(Counter= 0; Counter < TIMER_COUNT; Counter++)
				  {
					  if(Registers.Timers.Control[Counter]->Enable)
						  *Registers.Timers.Counter[Counter] = *Registers.Timers.Counter[Counter] + 1;
				  }

			  for(Counter= 0; Counter < UART_COUNT; Counter++)
				  {
					  if(*Uart[Counter].Status &  PORT_DATA_START)  *Uart[Counter].Status = *Uart[Counter].Status | PORT_DATA_STOP;
				  }
		 }

	 //
	 // Serial Port Data Process
	 //
	 if(htim->Instance==TIM7)
	 	 {
			  for (Counter=0; Counter < UART_COUNT; Counter++)
				  {
					if(*Uart[Counter].Status &  PORT_DATA_START)
						{
							Uart[Counter].PortDataEndCounter = Uart[Counter].PortDataEndCounter + 1;
							//*Uart[Counter].Status = *Uart[Counter].Status | PORT_DATA_STOP;
						}
				  }
	 	 }

//
	 if(htim->Instance==TIM8)
		 {
		 	 *RtcCounter.Master = *RtcCounter.Master + 1;
//		 	 if (Seconds[8]++ >= 10)
//		 	 {
//		 		 Seconds[8] = 0;
//		 		 if(Registers.Coil[0] & 0x80)
//		 		 	 {
//		 			 	 Registers.Coil[0] = Registers.Coil[0] & ~0x80;
//		 		 	 }
//		 		 else
//		 		 	 {
//						 Registers.Coil[0] = Registers.Coil[0] | 0x80;
//					 }
//		 	 }
		 }
}

// USART Error Handler
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
	//
	// Usart 1 Error
	//
	if(huart->Instance==USART1)
	  {

		  HAL_UART_DeInit(&huart1);
		  MX_USART1_UART_Init(); //my initialization code

		  SET_BIT(huart1.Instance->CR1, USART_CR1_PEIE | USART_CR1_RXNEIE);
	  }
	//
	// Usart 2 Error
	//
	if(huart->Instance==USART2)
	  {
		  HAL_UART_DeInit(&huart2);
		  MX_USART2_UART_Init(); //my initialization code

		  SET_BIT(huart2.Instance->CR1, USART_CR1_PEIE | USART_CR1_RXNEIE);
	  }
	//
	// Usart 3 Error
	//
	if(huart->Instance==USART3)
	  {

		  HAL_UART_DeInit(&huart3);
		  MX_USART3_UART_Init(); //my initialization code

		  SET_BIT(huart3.Instance->CR1, USART_CR1_PEIE | USART_CR1_RXNEIE);
	  }
}

void RelayTest(void)
{

	if(Registers.Coil[0] & 0x80)
		{
			Registers.Coil[0] = Registers.Coil[0] & ~0x80;
		}
	else
		{
			Registers.Coil[0] = Registers.Coil[0] | 0x80;
		}
}

void TankKg(void)
{
	unsigned short Counter ;
	float AmountKg;
	for(Counter = 0; Counter < 2; Counter++)
		{

			AmountKg = 0;
			if ( ( *System.Tanks.Capacity[Counter] > 0 ) && (*Plc.Peripheral.AnalogInput.Calculated[Counter] >0 ) )
				{
					AmountKg =  *System.Tanks.Capacity[Counter] * *Plc.Peripheral.AnalogInput.Calculated[Counter] / 100;
					AmountKg = AmountKg * *System.Tanks.Density[Counter];
				}

			*System.Tanks.AmoungKg[Counter] = AmountKg;
		}
}

void Peripherals(void)
{
	DigitalInput();

	DigitalOutput();

	AnalogInputs();
}

void PlcProcessStart(void)
{
	static unsigned char State = 0;
	if(Plc.Status->ProcessStart) return;


	switch(State)
		{
			case 0:
				TimerRestart(TIM_NO_PLC_PROCESS_START, *Plc.RunTime);
				State = 1;
				break;
			case 1:
				if (Registers.Timers.Control[TIM_NO_PLC_PROCESS_START]->Timeout)
					{
						Plc.Status->ProcessStart = 1;
						RelayEnable();
						TimerStop(TIM_NO_PLC_PROCESS_START);
					}
				break;
		}
}

static void MX_USART1_UART_Init_Custom(void)
{

  huart1.Instance = USART1;
  switch (*Plc.RTU.BaudRate)
	  {
		  case 0:
				  huart1.Init.BaudRate = 9600;
			  break;

		  case 1:
				  huart1.Init.BaudRate = 14400;
			  break;

		  case 2:
				  huart1.Init.BaudRate = 19200;
			  break;

		  case 3:
				  huart1.Init.BaudRate = 38400;
			  break;

		  case 4:
				  huart1.Init.BaudRate = 56000;
			  break;

		  case 5:
				  huart1.Init.BaudRate = 57600;
			  break;

		  case 6:
				  huart1.Init.BaudRate = 115200;
			  break;

  	  	  default:
  	  		  	  huart1.Init.BaudRate = 9600;
	  			break;

	  }

  switch (*Plc.RTU.DataBits)
	  {
  	  	  case 8:
  	  		  	  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  	  			break;

  	  	  case 9:
	  		  	  huart1.Init.WordLength = UART_WORDLENGTH_9B;
	  			break;

  	  	  default:
	  		  	  huart1.Init.WordLength = UART_WORDLENGTH_8B;
	  			break;

	  }

  switch (*Plc.RTU.StopBits)
	  {
  	  	  case 1:
  	  		  	  huart1.Init.StopBits = UART_STOPBITS_1;
  	  			break;

  	  	  case 2:
  	  		  	  huart1.Init.StopBits = UART_STOPBITS_2;
	  			break;

  	  	  default:
	  		  	  huart1.Init.StopBits = UART_STOPBITS_1;
	  			break;

	  }

  switch (*Plc.RTU.Parity)
	  {
  	  	  case 0:
  	  		  	  huart1.Init.Parity = UART_PARITY_NONE;
  	  			break;

  	  	  case 1:
  	  		  	  huart1.Init.Parity = UART_PARITY_EVEN;
	  			break;

  	  	  case 2:
  	  		  	  huart1.Init.Parity = UART_PARITY_ODD;
	  			break;

  	  	  default:
  	  		huart1.Init.Parity = UART_PARITY_NONE;
	  			break;

	  }

  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

void HAL_GPIO_WRITE_ODR(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  GPIOx->ODR |= GPIO_Pin;
}

void HAL_I2C_ClearBusyFlagErrata(I2C_HandleTypeDef *hi2c) {

    static uint8_t resetTried = 0;
    if (resetTried == 1) {
        return ;
    }
    uint32_t SDA_PIN = GPIO_PIN_7;
    uint32_t SCL_PIN = GPIO_PIN_6;
    GPIO_InitTypeDef GPIO_InitStruct;

    // 1
    __HAL_I2C_DISABLE(hi2c);

    // 2
    GPIO_InitStruct.Pin = SDA_PIN|SCL_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    HAL_GPIO_WRITE_ODR(GPIOB, SDA_PIN);
    HAL_GPIO_WRITE_ODR(GPIOB, SCL_PIN);

    // 3
    //GPIO_PinState pinState;
    if (HAL_GPIO_ReadPin(GPIOB, SDA_PIN) == GPIO_PIN_RESET) {
        for(;;){}
    }
    if (HAL_GPIO_ReadPin(GPIOB, SCL_PIN) == GPIO_PIN_RESET) {
        for(;;){}
    }

    // 4
    GPIO_InitStruct.Pin = SDA_PIN;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    HAL_GPIO_TogglePin(GPIOB, SDA_PIN);

    // 5
    if (HAL_GPIO_ReadPin(GPIOB, SDA_PIN) == GPIO_PIN_SET) {
        for(;;){}
    }

    // 6
    GPIO_InitStruct.Pin = SCL_PIN;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    HAL_GPIO_TogglePin(GPIOB, SCL_PIN);

    // 7
    if (HAL_GPIO_ReadPin(GPIOB, SCL_PIN) == GPIO_PIN_SET) {
        for(;;){}
    }

    // 8
    GPIO_InitStruct.Pin = SDA_PIN;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    HAL_GPIO_WRITE_ODR(GPIOB, SDA_PIN);

    // 9
    if (HAL_GPIO_ReadPin(GPIOB, SDA_PIN) == GPIO_PIN_RESET) {
        for(;;){}
    }

    // 10
    GPIO_InitStruct.Pin = SCL_PIN;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    HAL_GPIO_WRITE_ODR(GPIOB, SCL_PIN);

    // 11
    if (HAL_GPIO_ReadPin(GPIOB, SCL_PIN) == GPIO_PIN_RESET) {
        for(;;){}
    }

    // 12
//    GPIO_InitStruct.Pin = SDA_PIN|SCL_PIN;
//    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
//    GPIO_InitStruct.Alternate = I2C ; //NUCLEO_I2C_EXPBD_SCL_SDA_AF;
//    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);


   // 13
   hi2c->Instance->CR1 |= I2C_CR1_SWRST;

   // 14
   hi2c->Instance->CR1 ^= I2C_CR1_SWRST;

   // 15
   __HAL_I2C_ENABLE(hi2c);

   resetTried = 1;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_ADC3_Init();
  MX_I2C1_Init();
  MX_I2C2_Init();
  MX_SPI1_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_TIM2_Init();
  MX_TIM7_Init();
  MX_TIM8_Init();
  /* USER CODE BEGIN 2 */
  //
  	// Register Address Asignment
  	//
  	SetRegisterData();
  	//
  	Initialize();
  	//
  	//
  	//

  	//
  	// Test
  	//
  	PeripheralTest();
  	//
  	// EEPRom Initialize And Read
  	//
  	//
  	// EEProm Init
  	//
  	MC25LCxxx_Init(&hspi1);
  	//
  	// Read EEPROM
  	//
  	MC25LCxxx_Read(&hspi1, EEPROM_NO_00, Registers.Holding);
  	//
  	//
  	//

    HAL_UART_DeInit(&huart1);
    MX_USART1_UART_Init_Custom();

  	//
  	// Wathdog Initialize
  	//
  	//WatchDogInit();

  	// Default Process
  	//
  	DefaultProcess();
  	//
   	// Kalman İnitialize
   	//
   	InitKalmanParameter();
  	//
  	// Timer
  	//
   	HAL_TIM_Base_Start_IT(&htim2);

  	//HAL_TIM_Base_Start_IT(&htim5);

  	//HAL_TIM_Base_Start_IT(&htim6);

  	HAL_TIM_Base_Start_IT(&htim7);

  	HAL_TIM_Base_Start_IT(&htim8);


  	*Uart[1].DataEnd = 50;
  	*Uart[2].DataEnd = 50;
  	*Uart[3].DataEnd = 100;
  	*Uart[4].DataEnd = 20;

  	*System.State = SYSTEM_STATE_NONE;

  	Plc.Status->ProcessStart = 0;

  	UART3_ETHERNET_ENABLE;

  	UART1_RS485_TRANSMIT_ENABLE;

  	HAL_UART_Transmit(&huart1, (unsigned char *)"Uart 1 Test\r\n", 13, 100);

  	UART1_RS485_RECEIVE_ENABLE;

  	UART3_RS485_TRANSMIT_ENABLE;

  	HAL_UART_Transmit(&huart3, (unsigned char *)"Uart 3 Test\r\n", 13, 100);

  	UART3_RS485_RECEIVE_ENABLE;

  	UART2_RS485_TRANSMIT_ENABLE; UART2_RS485_RECEIVE_DISABLE;


  	HAL_ADC_MspInit(&hadc1);
  	HAL_ADC_MspInit(&hadc3);

  	//HAL_ADC_Start_IT(&hadc1);
  	//HAL_ADC_Start_IT(&hadc3);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	PlcProcessStart();

	Peripherals();

	HoldingRegisterWrite();

	UpdateHoldingRegister();

	CheckUsartPortDataEndTimeOut();

	ProtocolModbus();

	TimerControlProcess();

	RtcSecondUpdate();

	RtcAdjust();

	//SystemStateProcess();

	//TcpDataSend();

	SetRegisterDataDefault();

	TankKg();

	HMIData();

	ButtonProcess();

	WatchDogFeed();
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 84;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_4;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief ADC3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC3_Init(void)
{

  /* USER CODE BEGIN ADC3_Init 0 */

  /* USER CODE END ADC3_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC3_Init 1 */

  /* USER CODE END ADC3_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc3.Instance = ADC3;
  hadc3.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc3.Init.Resolution = ADC_RESOLUTION_12B;
  hadc3.Init.ScanConvMode = DISABLE;
  hadc3.Init.ContinuousConvMode = DISABLE;
  hadc3.Init.DiscontinuousConvMode = DISABLE;
  hadc3.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc3.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc3.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc3.Init.NbrOfConversion = 1;
  hadc3.Init.DMAContinuousRequests = DISABLE;
  hadc3.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc3) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_9;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC3_Init 2 */

  /* USER CODE END ADC3_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.ClockSpeed = 100000;
  hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 8400000-1;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM7 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM7_Init(void)
{

  /* USER CODE BEGIN TIM7_Init 0 */

  /* USER CODE END TIM7_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM7_Init 1 */

  /* USER CODE END TIM7_Init 1 */
  htim7.Instance = TIM7;
  htim7.Init.Prescaler = 100;
  htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim7.Init.Period = 8400-1;
  htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim7) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim7, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM7_Init 2 */

  /* USER CODE END TIM7_Init 2 */

}

/**
  * @brief TIM8 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM8_Init(void)
{

  /* USER CODE BEGIN TIM8_Init 0 */

  /* USER CODE END TIM8_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM8_Init 1 */

  /* USER CODE END TIM8_Init 1 */
  htim8.Instance = TIM8;
  htim8.Init.Prescaler = 10000;
  htim8.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim8.Init.Period = 8400-1;
  htim8.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim8.Init.RepetitionCounter = 0;
  htim8.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim8) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim8, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim8, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM8_Init 2 */

  /* USER CODE END TIM8_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}


/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, SPI_SHIELD_CS_Pin|RAM_CS_SPI2_Pin|GYRO_CS_SPI1_Pin|LD1_Pin
                          |LD0_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, Relay_16_Pin|Relay_15_Pin|Relay_14_Pin|DAC0_CS_SPI1_Pin
                          |DAC1_CS_SPI1_Pin|Relay_13_Pin|Relay_12_Pin|Relay_11_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, USART2_RE_DE_Pin|Usart1_RE_DE_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, EEPROM_CS_SPI1_Pin|WIZNET_NRST_Pin|ADC_BOARD2_Pin|LD3_Pin
                          |LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, Relay_10_Pin|Relay_9_Pin|ADC_BOARD1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, Relay_1_Pin|Relay_2_Pin|Relay_3_Pin|Relay_4_Pin
                          |Usart3_RE_DE_Pin|LD_5_Pin|LD_4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, Relay_5_Pin|Relay_6_Pin|Relay_7_Pin|Relay_8_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : SW_1_Pin SW_2_Pin SW_3_Pin SW_4_Pin
                           AUX_EN_Pin DI_2_Pin ACC_INTC0_Pin ACC_INT2C1_Pin
                           GYRO_INTC0_Pin GYRI_INTC1_Pin AUX_Pin */
  GPIO_InitStruct.Pin = SW_1_Pin|SW_2_Pin|SW_3_Pin|SW_4_Pin
                          |AUX_EN_Pin|DI_2_Pin|ACC_INTC0_Pin|ACC_INT2C1_Pin
                          |GYRO_INTC0_Pin|GYRI_INTC1_Pin|AUX_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : SPI_SHIELD_CS_Pin RAM_CS_SPI2_Pin GYRO_CS_SPI1_Pin LD1_Pin
                           LD0_Pin */
  GPIO_InitStruct.Pin = SPI_SHIELD_CS_Pin|RAM_CS_SPI2_Pin|GYRO_CS_SPI1_Pin|LD1_Pin
                          |LD0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : ACCEL_INT_Pin RF_TX_Pin RF_RX_Pin */
  GPIO_InitStruct.Pin = ACCEL_INT_Pin|RF_TX_Pin|RF_RX_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : Relay_16_Pin Relay_15_Pin Relay_14_Pin DAC0_CS_SPI1_Pin
                           DAC1_CS_SPI1_Pin Relay_13_Pin Relay_12_Pin Relay_11_Pin */
  GPIO_InitStruct.Pin = Relay_16_Pin|Relay_15_Pin|Relay_14_Pin|DAC0_CS_SPI1_Pin
                          |DAC1_CS_SPI1_Pin|Relay_13_Pin|Relay_12_Pin|Relay_11_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : USART2_RE_DE_Pin Usart1_RE_DE_Pin */
  GPIO_InitStruct.Pin = USART2_RE_DE_Pin|Usart1_RE_DE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : EEPROM_CS_SPI1_Pin WIZNET_NRST_Pin ADC_BOARD2_Pin LD3_Pin
                           LD2_Pin */
  GPIO_InitStruct.Pin = EEPROM_CS_SPI1_Pin|WIZNET_NRST_Pin|ADC_BOARD2_Pin|LD3_Pin
                          |LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : Relay_10_Pin Relay_9_Pin ADC_BOARD1_Pin */
  GPIO_InitStruct.Pin = Relay_10_Pin|Relay_9_Pin|ADC_BOARD1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : DI_1_Pin DI_3_Pin DI_4_Pin */
  GPIO_InitStruct.Pin = DI_1_Pin|DI_3_Pin|DI_4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : DI_7_Pin DI_8_Pin DEFAULT_BUTTON_Pin SPI1_CS_EXT_Pin */
  GPIO_InitStruct.Pin = DI_7_Pin|DI_8_Pin|DEFAULT_BUTTON_Pin|SPI1_CS_EXT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : Relay_1_Pin Relay_2_Pin Relay_3_Pin Relay_4_Pin
                           Usart3_RE_DE_Pin LD_5_Pin LD_4_Pin */
  GPIO_InitStruct.Pin = Relay_1_Pin|Relay_2_Pin|Relay_3_Pin|Relay_4_Pin
                          |Usart3_RE_DE_Pin|LD_5_Pin|LD_4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : DI_5_Pin DI_6_Pin DI_9_Pin DI_10_Pin
                           DI_16_Pin DI_15_Pin DI_14_Pin DI_13_Pin
                           DI_12_Pin DI_11_Pin */
  GPIO_InitStruct.Pin = DI_5_Pin|DI_6_Pin|DI_9_Pin|DI_10_Pin
                          |DI_16_Pin|DI_15_Pin|DI_14_Pin|DI_13_Pin
                          |DI_12_Pin|DI_11_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : Relay_5_Pin Relay_6_Pin Relay_7_Pin Relay_8_Pin */
  GPIO_InitStruct.Pin = Relay_5_Pin|Relay_6_Pin|Relay_7_Pin|Relay_8_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : AUX_SET_Pin */
  GPIO_InitStruct.Pin = AUX_SET_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(AUX_SET_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
