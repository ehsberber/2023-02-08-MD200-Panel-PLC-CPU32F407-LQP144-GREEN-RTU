/*
 * ds2431.h
 *
 *  Created on: Aug 17, 2022
 *      Author: Sezgin Berber
 */

#ifndef INCLUDE_DS2431_H_
#define INCLUDE_DS2431_H_

unsigned char ds2431write(strcONEWIRELINE strcOneWireLine); //I2C_HandleTypeDef *I2Cx, unsigned char SlaveAddress, unsigned OneWireLineNo, unsigned char RomNo);
unsigned char ds2431read(strcONEWIRELINE strcOneWireLine);
void ds2431(strcONEWIRELINE strcOneWireLine);
#endif /* INCLUDE_DS2431_H_ */
