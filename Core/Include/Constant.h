/*
 * Constant.h
 *
 *  Created on: 30 Ara 2021
 *      Author: SBerber
 */

#ifndef HEADER_CONSTANT_H_
#define HEADER_CONSTANT_H_

#define SPI_CS_SOFT				1
#define PLC_DO_CHANNEL_COUNT	16

//
// DEFAULT BUTTON
//

#define PLC_DEFAULT_BUTTON_PORT			GPIOD
#define PLC_DEFAULT_BUTTON_PORT_PIN		GPIO_PIN_0


//
// EEPROM CS
//

#define SPI_EEPROM_00_CS_PORT			GPIOB
#define SPI_EEPROM_00_CS_PORT_PIN		GPIO_PIN_2

#define SPI_EEPROM_01_CS_PORT			GPIOE
#define SPI_EEPROM_01_CS_PORT_PIN		GPIO_PIN_8


//
// DAC CS
//

#define SPI_DAC_00_CS_PORT				GPIOC
#define SPI_DAC_00_CS_PORT_PIN			GPIO_PIN_4

#define SPI_DAC_01_CS_PORT				GPIOC
#define SPI_DAC_01_CS_PORT_PIN			GPIO_PIN_5
//
// DAC DEVICE NO
//
#define DEVICE_NO_DAC_00				0
#define DEVICE_NO_DAC_01				1


#endif /* HEADER_CONSTANT_H_ */
