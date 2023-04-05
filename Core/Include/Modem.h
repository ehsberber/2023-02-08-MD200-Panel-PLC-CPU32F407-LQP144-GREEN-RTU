/*
 * Modem.h
 *
 *  Created on: Feb 3, 2023
 *      Author: Sezgin Berber
 */

#ifndef INCLUDE_MODEM_H_
#define INCLUDE_MODEM_H_

	#define MODEM_INITIALIZE_STATE_NONE  				0
	#define MODEM_INITIALIZE_STATE_AT    				1
	#define MODEM_INITIALIZE_STATE_ATE   				2
	#define MODEM_INITIALIZE_STATE_CMGF   				3
	#define MODEM_INITIALIZE_STATE_CHECK_RESPONSE   	10

	#define INITIALIZE_STATE_NONE						0
	#define INITIALIZE_STATE_OK							1

	#include "ModemCommand.h"

#endif /* INCLUDE_MODEM_H_ */
