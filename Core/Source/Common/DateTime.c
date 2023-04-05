
#include "Registers.h"
#include "ConvertString.h"
#include "ConvertDate.h"
#include "Rtc.h"

#include "String.h"
#include "DateTime.h"
#include "ConvertDate.h"
#include "M41T_RTC_I2C.h"

extern strcREGISTERS  Registers;
extern strcRTC RtcData;

//void init_RTC(void)
//{
//	ILR = 0x03; 
//	CCR = 0x11; 
//	CIIR = 0x00; 
//	
//	SEC = 0; 
//	MIN = 0;
//	HOUR = 0;
//
//	SEC = 10;
//	MIN = 12;
//	HOUR = 9;
//}
unsigned int ConvertDateToSecond(void)
{
	unsigned int Seconds;
	typeDateAndTime DateforSeconds;
	
	DateforSeconds.Day 		=  bcdtod(*RtcData.Day);
	DateforSeconds.Month 	=  bcdtod(*RtcData.Month);
	DateforSeconds.Year 	=  bcdtod(*RtcData.Year);
	DateforSeconds.Hour 	=  bcdtod(*RtcData.Hour);
	DateforSeconds.Minute 	=  bcdtod(*RtcData.Minute);
	DateforSeconds.Second 	=  bcdtod(*RtcData.Second);

	Seconds = DateToSeconds(DateforSeconds);
	return Seconds;
	
}

void ParseDateString(unsigned char *DateString,unsigned char Format,unsigned char *DateAddress)
{
	signed char i;
	unsigned char Day=1,Month=4,Year=10;
	unsigned char Hour=8,Minute=35,Second=0,MiliSecond = 0;
	unsigned char DayOfWeek=0;
 		
	switch(Format)
		{
			case 0:
					Day	= 	DateString[0];
					Month	= DateString[1];
					Year	= DateString[2];
		
					Hour	= DateString[3];
					Minute= DateString[4];
					Second= DateString[5];
				break;

			case 1:	// yy/mm/dd,hh:mm:ss		+CCLK: "10/03/30,17:03:09"
					i=0;
					while( (DateString[i] < 0x30 || 	DateString[i] > 0x39) && i< 50) i++; 
					if(i<50)
						{
							Year	= ConvertAlphaStringToLong(&DateString[i + 0] ,2);
							Month	= ConvertAlphaStringToLong(&DateString[i + 3] ,2);
							Day		= ConvertAlphaStringToLong(&DateString[i + 6] ,2);
				
							Hour	= ConvertAlphaStringToLong(&DateString[i + 9] ,2);
							Minute	= ConvertAlphaStringToLong(&DateString[i + 12] ,2);
							Second	= ConvertAlphaStringToLong(&DateString[i + 15] ,2);
						}
				break;
			case 2:		//ddmmyyhhmmss
					//uarttxstring(MONITOR_PORT,"\nMenu Date String:",0); uarttxstring(MONITOR_PORT,DateString,0);
					Day			= ConvertAlphaStringToLong(&DateString[0] ,2);
					Month		= ConvertAlphaStringToLong(&DateString[2] ,2);
					Year    	= ConvertAlphaStringToLong(&DateString[4] ,2);
				
					Hour		= ConvertAlphaStringToLong(&DateString[6] 	,2);
					Minute		= ConvertAlphaStringToLong(&DateString[8] 	,2);
					Second		= ConvertAlphaStringToLong(&DateString[10] 	,2);
				break;
			case 3:	//msssmmhhdwddMMyy

				 	i= strsearch(DateString,(unsigned char *)"Date:",0);
					#ifdef	 COMMENT_PORT								
						uarttxstring(COMMENT_PORT,"\n*Date Position:",0); uarttxcharhex(MONITOR_PORT,i);
					#endif

					 if(i>=0) 		
					 	{
							i += 5;
							Day				= ConvertAlphaStringToLong(&DateString[i+10] ,2);
							Month			= ConvertAlphaStringToLong(&DateString[i+12] ,2);
							Year    		= ConvertAlphaStringToLong(&DateString[i+14] ,2);

							DayOfWeek		= ConvertAlphaStringToLong(&DateString[i+8] ,2);
							Hour			= ConvertAlphaStringToLong(&DateString[i+6] ,2);
							Minute			= ConvertAlphaStringToLong(&DateString[i+4] ,2);
							Second			= ConvertAlphaStringToLong(&DateString[i+2] ,2);
							MiliSecond		= ConvertAlphaStringToLong(&DateString[i+0] ,2);
							
						}
				break;

		}
 
	DateAddress[RTC_DAY_POS] 					= ctobcd(Day);
	DateAddress[RTC_MONTH_POS] 					= ctobcd(Month);
	DateAddress[RTC_YEAR_POS] 					= ctobcd(Year);
	DateAddress[RTC_HOUR_POS] 					= ctobcd(Hour);
	DateAddress[RTC_MINUTE_POS] 				= ctobcd(Minute);
	DateAddress[RTC_SECOND_POS] 				= ctobcd(Second);
	DateAddress[RTC_MILISECOND_POS] 			= ctobcd(MiliSecond);
	DateAddress[RTC_DAYOFWEEK_POS] 				= ctobcd(DayOfWeek);

	*RtcData.Control |= (0x01 << RTC_CONTROL_UPDATE_BIT_NO);			// Update Date
}

 
void SetRtc(unsigned char *RtcData, char Format,unsigned char *DateAddress)
{
	ParseDateString(RtcData,Format,DateAddress);
 }

void SetDate(char Format)
{
	ParseDateString(RtcData.Date, Format, RtcData.Date);
}
