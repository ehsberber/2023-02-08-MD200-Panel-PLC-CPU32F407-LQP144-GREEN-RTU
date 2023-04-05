/*
 * Peripheral.h
 *
 *  Created on: Jan 28, 2022
 *      Author: SBerber
 */

#ifndef APPLICATION_USER_HEADER_PERIPHERAL_H_
#define APPLICATION_USER_HEADER_PERIPHERAL_H_

#include "MicroPeripheral.h"

#define __LSB										0x0001

#define UART_NO_MODEM									1

#define   SEQ_LT1                             			0
#define   SEQ_LT2                                 		1
#define   SEQ_GD0                             			4
#define   SEQ_GD1                             			5
#define   SEQ_GD2                             			6
#define   SEQ_GD3                             			7
#define   SEQ_GD4                             			8
#define   SEQ_GD5                             			9
#define   SEQ_GD6                             			10
#define   SEQ_GD7                             			11

extern I2C_HandleTypeDef hi2c1;
extern I2C_HandleTypeDef hi2c2;

#define I2C_INT hi2c1
#define I2C_EXT hi2c2

void RelayEnable(void);
#endif /* APPLICATION_USER_HEADER_PERIPHERAL_H_ */
