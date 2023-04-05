/*
 * ConvertDate.h
 *
 *  Created on: Jul 19, 2022
 *      Author: Sezgin Berber
 */

#ifndef APPLICATION_USER_HEADER_CONVERTDATE_H_
#define APPLICATION_USER_HEADER_CONVERTDATE_H_

typedef struct
	{
		unsigned short Year;
		unsigned char Month;
		unsigned char Day;
		unsigned char Hour;
		unsigned char Minute;
		unsigned char Second;
	}typeDateAndTime;


unsigned long getMinuteSeconds(void);
unsigned long getHourSeconds(void);
unsigned long getDaySeconds(void);
unsigned long getYearSeconds(unsigned short Year);
unsigned long getMonthSeconds(unsigned short Year, unsigned char Month);
unsigned char LeapYear(unsigned short Years);
unsigned long  DateToSeconds(typeDateAndTime DateforSeconds);
unsigned long  BcdDateToSeconds(unsigned char  *BCD, unsigned char Length);
typeDateAndTime DateFromSeconds(unsigned long Seconds);

#endif /* APPLICATION_USER_HEADER_CONVERTDATE_H_ */
