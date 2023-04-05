/*
 * ds1820.h
 *
 *  Created on: Aug 19, 2022
 *      Author: Sezgin Berber
 */

#ifndef INCLUDE_DS1820_H_
#define INCLUDE_DS1820_H_

#include "OneWire.h"
#include "DataType.h"

signed char ds1820StartConvertion(strcONEWIRELINE strcOneWireLine);
signed short ds1820ReadTemperature(strcONEWIRELINE strcOneWireLine, strcTEMPERATURE *Temperature);


#endif /* INCLUDE_DS1820_H_ */
