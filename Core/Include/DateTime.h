//#define RTC_DAY_POS 			 			0
//#define RTC_MONTH_POS 					1
//#define RTC_YEAR_POS 						2
//#define RTC_HOUR_POS 						3
//#define RTC_MINUTE_POS 					4
//#define RTC_SECOND_POS 					5
//#define RTC_MILISECOND_POS 			6
//#define RTC_DAYOFWEEK_POS 			7

#define RTC_DATE_ADDRESS											0x00
#define RTC_READ_AFTER_LOOP_COUNT									10
#define RTC_ERROR_AFTER_NO_RESPONSE_LOOP_COUNT						5
	

#define RTC_M41T_ON_BOARD_SLAVE_ADDRESS		0xD0
	
void SetDate(char SetNo);
void ParseDateString(unsigned char *DateString,unsigned char Format,unsigned char *RtcAddress);
unsigned int ConvertDateToSecond(void);
void SetRtc(unsigned char *RtcData, char Format,unsigned char *DateAddress);
