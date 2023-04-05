/*
 * Crc.h
 *
 *  Created on: Aug 3, 2022
 *      Author: Sezgin Berber
 */

#ifndef INCLUDE_CRC_H_
#define INCLUDE_CRC_H_

	typedef enum
		{
			CrcTypeNone 			= 0x00,
			CrcTypeDecos 			= 0x01,
			CrcTypeModBus 		= 0x02,
			CrcTypeWayne 			= 0x03
		}enumCrcType;

#endif /* INCLUDE_CRC_H_ */
