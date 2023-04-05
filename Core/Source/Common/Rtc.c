/*
 * RTCProcess.c
 *
 *  Created on: Jul 19, 2022
 *      Author: Sezgin Berber
 */
#include "Registers.h"
#include "Rtc.h"
#include "Peripheral.h"
#include "DateTime.h"
#include "M41T_RTC_I2C.h"

extern strcRTCCounter RtcCounter;
extern strcRTC RtcData;

void RtcSecondUpdate(void)
{
	unsigned int BackupSeconds;
	static unsigned int LastRtcSecondMaster=0;
	BackupSeconds = *RtcCounter.Master;

	*RtcCounter.Count += (BackupSeconds - LastRtcSecondMaster);
	LastRtcSecondMaster = BackupSeconds;
}

void RtcAdjust(void)
{
	unsigned char RTC_TEMP_DATA[10];
	unsigned char *RTC_TEMP;
	unsigned long Seconds;
//	static unsigned short Counter=0;
//	static unsigned char FirstTime=1;

//	HAL_StatusTypeDef Status= HAL_OK;

//	typeDateAndTime DateforSeconds;

	RTC_TEMP = &RTC_TEMP_DATA[0];

	if(*RtcData.Control & (0x01 << RTC_CONTROL_UPDATE_BIT_NO))
		{
			RTC_TEMP[0] = RTC_DATE_ADDRESS;

			RTC_TEMP[1] = *RtcData.MiliSecond ;
			RTC_TEMP[2] = *RtcData.Second;
			RTC_TEMP[3] = *RtcData.Minute;
			RTC_TEMP[4] = *RtcData.Hour;
			RTC_TEMP[5] = *RtcData.DayOfWeek;
			RTC_TEMP[6] = *RtcData.Day;
			RTC_TEMP[7] = *RtcData.Month;
			RTC_TEMP[8] = *RtcData.Year;

			// FOR TEST if( FirstTime == 0xA5)
			M41T_Write(&I2C_INT, RTC_TEMP,  9);

			Seconds = ConvertDateToSecond();

			*RtcCounter.Count = Seconds * 10 ;

			*RtcData.Control &= ~(0x01 << RTC_CONTROL_UPDATE_BIT_NO);
		}
}
