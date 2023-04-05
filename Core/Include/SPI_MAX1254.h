/*
 * Max1254.h
 *
 *  Created on: Oct 3, 2022
 *      Author: Sezgin Berber
 */

#ifndef INCLUDE_SPI_MAX1254_H_
#define INCLUDE_SPI_MAX1254_H_

#include "MicroPeripheral.h"
#include "AnalogInput.h"

void MAX1254Reset(strcAdcINSTANCE *AdcInstance);
void MAX1254ChannelStart(strcAdcINSTANCE AdcInstance);
void MAX1254ChannelRead(strcAdcINSTANCE *AdcInstance);
void MAX1254ReadConfig(strcAdcINSTANCE *AdcInstance);
void  MAX1254Config(strcAdcINSTANCE AdcInstance);
void MAX1254WriteChannelConfig(strcAdcINSTANCE AdcInstance, unsigned  char Config);
void MAX1254ReadChannelConfig(strcAdcINSTANCE AdcInstance,unsigned char *Config);
void AdcModuleMAX125X(unsigned char ModuleNo);
#endif /* INCLUDE_SPI_MAX1254_H_ */
