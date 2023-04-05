/*
 * Initialize.c
 *
 *  Created on: Jan 22, 2022
 *      Author: SBerber
 */
#include "MicroPeripheral.h"
#include "Registers.h"
#include "Coils.h"
#include "Constant.h"
#include "TimerProcess.h"
#include "SystemStates.h"
#include "Uarts.h"
#include "AnalogInput.h"

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;



extern strcSYSTEM System;;
extern strcREGISTERS  Registers;

extern strcPLC Plc;
extern strcDATASENDCENTER DataSendCenter;

 void UsartEnable(void)
 {
	/* Enable the UART Parity Error interrupt and Data Register Not Empty interrupt */
	SET_BIT(huart1.Instance->CR1, USART_CR1_PEIE | UART_IT_RXNE);
	SET_BIT(huart2.Instance->CR1, USART_CR1_PEIE | UART_IT_RXNE);
	SET_BIT(huart3.Instance->CR1, USART_CR1_PEIE | UART_IT_RXNE);

 }

 void SystemVariableReset(void)
 {

	 SPI_MODULE_CS1_DISABLE;
	 SPI_MODULE_CS2_DISABLE;

	 System.Button0->Buttons = 0;
	 System.Button1->Buttons = 0;
	 System.Button2->Buttons = 0;

	 //*Plc.ModBusSequenceNo					= 0;

	 Registers.Coil[0] = 0x0000;
	*DataSendCenter.ToBeSendPacket = 0;

	 *System.State = SYSTEM_STATE_STOP;


	 UART3_ETHERNET_ENABLE;

 }

 void RelayEnable(void)
  {
	 unsigned char CoilIntNo;

	//
	// All Output Low
	//
	 for(CoilIntNo=0; CoilIntNo<COIL_INT_COUNT ; CoilIntNo++)
		 Registers.Coil[CoilIntNo] = 0;
 	//
 	// Relay Output Enable
 	//
 	// Set Relay 14 , Reset Relay 15
 	//
 	//
 	//Registers.Coil[0] &= 0x3F00;
 	Registers.Coil[0] = 0x4000;
 }

 void Initialize_DAC8760(void)
 {
	 //
	 // DAC 0  SPI CS SET
	 //
	 HAL_GPIO_WritePin( SPI_DAC_00_CS_PORT, SPI_DAC_00_CS_PORT_PIN ,  GPIO_PIN_SET );

	 //
	 // DAC 1  SPI CS SET
	 //
	 HAL_GPIO_WritePin( SPI_DAC_01_CS_PORT, SPI_DAC_01_CS_PORT_PIN ,  GPIO_PIN_SET );

	 *Plc.Peripheral.AnalogOutput.ChannelValue[0] = 0;
	 *Plc.Peripheral.AnalogOutput.ChannelValue[1] = 0;
 }

 void Initialize_DAC_Micro(void)
 {
	 //
	 // DAC 0  SPI CS SET
	 //
	 HAL_GPIO_WritePin( SPI_DAC_00_CS_PORT, SPI_DAC_00_CS_PORT_PIN ,  GPIO_PIN_SET );

	 //
	 // DAC 1  SPI CS SET
	 //
	 HAL_GPIO_WritePin( SPI_DAC_01_CS_PORT, SPI_DAC_01_CS_PORT_PIN ,  GPIO_PIN_SET );
 }

 void Initialize_DAC(void)
 {
	 Initialize_DAC_Micro();

	 Initialize_DAC8760();
 }

 long unsigned int AI_Data[8] = {0,0,0,0,0,0,0,0};

 void Initialize_ADC(void)
 {

	  /* DMA controller clock enable */
//	  __HAL_RCC_DMA2_CLK_ENABLE();

//	 *Plc.AnalogInput.ActiveChannel = 0;

//	 AnalogChannelSet(*Plc.AnalogInput.ActiveChannel);

//	 HAL_ADC_Start_DMA(&hadc3,  &AI_Data[0], 8) ;
//	 HAL_ADC_Start(&hadc3) ;
     //HAL_ADC_Start_IT (&hadc3) ;
//	  HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0, 0);
//	  HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);

 }

void Initialize(void)
 {
	//
	// Initialize DAC
	//
	Initialize_ADC();
	//
	// Usart
	//
	UsartEnable();

	//
	// Plc Variable
	//
	SystemVariableReset();
	//
	// Timer Initialize
	//
	TimerInitialize();
	//
	// Relay Master Adjust
	//
	//RelayEnable();

}
