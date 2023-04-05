/*
 * PeripheralTest.c
 *
 *  Created on: Aug 3, 2022
 *      Author: Sezgin Berber
 */
#include "MicroPeripheral.h"
#include "UartPortProcess.h"
#include "Uarts.h"

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;

void PeripheralTestUsart(void)
{
//	//
//	// Usart 1
//	//
//	HAL_UART_Transmit(&huart1, (unsigned char *)"Uart 1 Transmit ****\r\n", 13, 100);
//	uarttxdata(1, (unsigned char *)"Uart 1 Tx\r\n", 11);
	//
	// Usart 2
	//
	HAL_UART_Transmit(&huart3, (unsigned char *)"Uart 3 Transmit ****\r\n", 13, 100);

	uarttxdata(2, (unsigned char *)"Uart 2 Tx Data\r\n", 11);
	//
	// Usart 3
	//
	UART3_RS485_TRANSMIT_ENABLE; UART3_RS485_RECEIVE_DISABLE;

	HAL_UART_Transmit(&huart3, (unsigned char *)"Uart 3 Transmit ****\r\n", 13, 100);

	uarttxdata(3, (unsigned char *)"Uart 3 Tx\r\n", 11);

	UART3_RS485_TRANSMIT_DISABLE; UART3_RS485_RECEIVE_ENABLE;
}


void PeripheralTest(void)
{
	PeripheralTestUsart();
}
