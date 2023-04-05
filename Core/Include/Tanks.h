/*
 * Tanks.h
 *
 *  Created on: Sep 7, 2022
 *      Author: Sezgin Berber
 */

#ifndef INCLUDE_TANKS_H_
#define INCLUDE_TANKS_H_

	#define	MAX_TANK_COUNT  2
	#define	MAX_PROBE_COUNT  2

	#define CALCV_LT1_SEQ	0
	#define CALCV_LT2_SEQ	1

	#define CALCV_PROBE1_SEQ	14
	#define CALCV_PROBE2_SEQ	15


	#define LT1_SEQ			0
	#define LT2_SEQ			1

	#define FUELING_STATE_NONE			0
	#define FUELING_STATE_INPROGRESS	1
	#define FUELING_STATE_STOPPING		2
	#define FUELING_STATE_STOP			3

	#define SECOND_LEVEL_SHOW_NONE				0
	#define SECOND_LEVEL_SHOW_ALWAYS			1
	#define SECOND_LEVEL_SHOW_ON_DEVIATION		2

	#define SECOND_LEVEL_SHOW_TANK1 			0x01
	#define SECOND_LEVEL_SHOW_TANK2				0x02

	#define IDOK_SET					1
	#define IDOK_CLEAR					0

	void TankFuelingTimerRestart(void);
	void TankFuelingControl(unsigned char Restart);
	void TankSecondlevelShow(void);
	void TankVolumeCalculationHorzCylindrical(unsigned short ProbeSeqNo);
	void TankFuelingAlertTest(void);

#endif /* INCLUDE_TANKS_H_ */
