/*
 * Uarts.h
 *
 *  Created on: Aug 3, 2022
 *      Author: Sezgin Berber
 */
#include "MicroPeripheral.h"

#ifndef INCLUDE_UARTS_H_
#define INCLUDE_UARTS_H_


	//
	// Uart Count
	//
	#define   UART_COUNT                                                       7
	//
	// UART TX/RX ENABLE
	//

	//
	// UART 1
	//
	#define UART1_RS485_RECEIVE_ENABLE		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET)
//	#define UART1_RS485_RECEIVE_DISABLE		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET)

	#define UART1_RS485_TRANSMIT_ENABLE		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET)
//	#define UART1_RS485_TRANSMIT_DISABLE	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET)

//	#define UART1_RS485_RECEIVE_ENABLE		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET)
//	#define UART1_RS485_RECEIVE_DISABLE		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET)
//
//	#define UART1_RS485_TRANSMIT_ENABLE		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_12, GPIO_PIN_SET)
//	#define UART1_RS485_TRANSMIT_DISABLE	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_12, GPIO_PIN_RESET)
	//
	// UART 2
	//
	#define UART2_RS485_RECEIVE_ENABLE		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET)
	#define UART2_RS485_RECEIVE_DISABLE		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET)

	#define UART2_RS485_TRANSMIT_ENABLE		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_15, GPIO_PIN_SET)
	#define UART2_RS485_TRANSMIT_DISABLE	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_15, GPIO_PIN_RESET)
	//
	// UART 3
	//
	#define UART3_RS485_RECEIVE_ENABLE		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_RESET)
	#define UART3_RS485_RECEIVE_DISABLE		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_SET)

	#define UART3_RS485_TRANSMIT_ENABLE		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_SET)
	#define UART3_RS485_TRANSMIT_DISABLE	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_RESET)
	//
	// UART 4
	//
	#define UART4_RS485_RECEIVE_ENABLE		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_RESET)
	#define UART4_RS485_RECEIVE_DISABLE		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_SET)

	#define UART4_RS485_TRANSMIT_ENABLE		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_SET)
	#define UART4_RS485_TRANSMIT_DISABLE	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_RESET)
	//
	// UART 6
	//
	#define UART6_RS485_RECEIVE_ENABLE		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_RESET)
	#define UART6_RS485_RECEIVE_DISABLE		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_SET)

	#define UART6_RS485_TRANSMIT_ENABLE		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_SET)
	#define UART6_RS485_TRANSMIT_DISABLE	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_RESET)

	#define UART3_ETHERNET_ENABLE			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET)
	#define UART3_ETHERNET_DISABLE			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET)
	//
	//	SA_UART_STATUS Mask
	//
    #define   PORT_DATA_START                                                                      0x01                                                                            // Mask
    #define   PORT_DATA_STOP                                                                       0x02                                                                            // Mask
    #define   PORT_WAIT_TO_TIME                                                                    0x04                                                                            // Mask
    #define   PORT_BUSY                                                                            0x08                                                                            // Mask
    #define   PORT_RESPONSE                                                                        0x10                                                                            // Mask
    #define   PORT_COMMAND_TYPE_SMS                                                                0x40                                                                            // Mask
    #define   PORT_COMMAND_TYPE_HEX                                                                0x80                                                                            // Mask
    #define   PORT_COMMAND_TYPE_MODBUS                                                             0xC0

	typedef struct
	{
		unsigned char  *Data;
		unsigned short *Offset;
		unsigned short *BufferSize;
		unsigned short *Status;
		unsigned short *Timeout;
		unsigned short *DataEnd;
		unsigned short PortDataEndCounter;
	}strcUART;

#endif /* INCLUDE_UARTS_H_ */
