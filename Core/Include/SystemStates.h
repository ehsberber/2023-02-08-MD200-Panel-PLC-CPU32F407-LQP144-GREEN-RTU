/*
 * SystemStates.h
 *
 *  Created on: Sep 7, 2022
 *      Author: Sezgin Berber
 */

#ifndef INCLUDE_SYSTEMSTATES_H_
#define INCLUDE_SYSTEMSTATES_H_

    #define   SYSTEM_STATE_NONE                                                 0
	#define   SYSTEM_STATE_STOP                                                 1
	#define   SYSTEM_STATE_STARTED                                              2
    #define   SYSTEM_STATE_INPROGRESS                                          	3
	#define   SYSTEM_STATE_EMERGENCY_STOP                                       4
    #define   SYSTEM_STATE_TEST                                           		5
	#define   SYSTEM_STATE_NOT_READY												6

	void SystemStateProcess(void);
#endif /* INCLUDE_SYSTEMSTATES_H_ */
