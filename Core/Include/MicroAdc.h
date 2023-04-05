/*
 * MicroAdc.h
 *
 *  Created on: Oct 5, 2022
 *      Author: Sezgin Berber
 */

#ifndef INCLUDE_MICROADC_H_
#define INCLUDE_MICROADC_H_

#include "MicroPeripheral.h"
  void OnChipAdcChannelDataRead(unsigned short  ModuleNo);
 void OnChipAnalogChannelSet(ADC_HandleTypeDef *hadc, unsigned int Channel);

#endif /* INCLUDE_MICROADC_H_ */
