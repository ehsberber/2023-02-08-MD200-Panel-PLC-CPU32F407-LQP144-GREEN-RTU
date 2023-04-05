#include "ConvertDate.h"
#include "ConvertInteger.h"
#include "ConvertString.h"

#define START_YEAR 2010
extern unsigned char *TEMP;

unsigned char LeapYear(unsigned short Years) 
{
	if( (Years % 4) == 0 && (Years % 100) != 0 )
	    return 1;
	else
		{
	    if ((Years % 400) == 0 )
	        return 1;
	    else
	        return 0;
		}  	  
}

unsigned long getMinuteSeconds(void) 
	{
   	unsigned long SecondsOfMinute = 60;
    return SecondsOfMinute;
	}

unsigned long getHourSeconds(void) 
	{
		unsigned long SecondsOfHour = 60 * 60;
		return SecondsOfHour;
	}

unsigned long getDaySeconds(void) 
	{
		unsigned long SecondsOfDay = 24 * 60 * 60;
    return SecondsOfDay;
	}

unsigned long getYearSeconds(unsigned short Year)
{
 	unsigned short DaysOfYear;

	unsigned long YearSeconds;
	if (LeapYear(Year)) DaysOfYear = 366; else DaysOfYear = 365;
	YearSeconds = DaysOfYear * 24 * 60 * 60	;
  return YearSeconds;
}

unsigned long getMonthSeconds(unsigned short Year, unsigned char Month)
{
	unsigned long MonthSeconds=0;
  switch (Month)
		{
      case 1:
			case 3: 
			case 5:
			case 7:
			case 8:
			case 10: 
			case 12:
          			MonthSeconds = 31 * 24 * 60 * 60;
								break;
					
      case 4: 
			case 6: 
			case 9: 
			case 11:
          			MonthSeconds = 30 * 24 * 60 * 60;
					break;
      case 2:
          if (LeapYear(Year)) 
						MonthSeconds = 29 * 24 * 60 * 60;
          else
          	MonthSeconds = 28 * 24 * 60 * 60;
     }
        
	return MonthSeconds;
}

unsigned long  DateToSeconds(typeDateAndTime DateforSeconds) 
{
     
	unsigned short YearCounter = START_YEAR-2000;
	unsigned short MonthCounter = 1;
	unsigned short DayCounter = 1;
	
	unsigned short HourCounter = 0;
	unsigned short MinuteCounter = 0;

  unsigned long Seconds =0;			

  while (YearCounter < DateforSeconds.Year) 
		{
      Seconds += getYearSeconds(YearCounter);
      YearCounter += 1;
  	}

  
  while (MonthCounter < DateforSeconds.Month)
		{
      Seconds += getMonthSeconds(YearCounter, MonthCounter);
      MonthCounter += 1;
  	}

  
  while (DayCounter < DateforSeconds.Day)
		{
      Seconds += getDaySeconds();
      DayCounter += 1;
  	}

  
  while (HourCounter < DateforSeconds.Hour)
		{
      Seconds += getHourSeconds();
		 	HourCounter += 1;
  	}

  
  while(MinuteCounter <  DateforSeconds.Minute)
		{
      Seconds += getMinuteSeconds();
      MinuteCounter += 1;
  	}

  Seconds +=  DateforSeconds.Second;
  return Seconds;
}

unsigned long  BcdDateToSeconds(unsigned char  *BCD, unsigned char Length) 
{
	unsigned long Seconds =0;		
	typeDateAndTime DateforSeconds;

	if(Length!=6) return 0;

	DateforSeconds.Day 		=  bcdtod(BCD[0]);
	DateforSeconds.Month 	=  bcdtod(BCD[1]);
	DateforSeconds.Year 	=  bcdtod(BCD[2]);
	DateforSeconds.Hour 	=  bcdtod(BCD[3]);
	DateforSeconds.Minute =  bcdtod(BCD[4]);
	DateforSeconds.Second =  bcdtod(BCD[5]);
	Seconds = DateToSeconds(DateforSeconds);
		 
  return Seconds;
}


typeDateAndTime DateFromSeconds(unsigned long Seconds)
{
	unsigned long TotalSeconds = 0;
  unsigned short Year = START_YEAR;
	unsigned short Month = 1;
	unsigned char Day = 1;
	unsigned char Hour = 0;
	unsigned char Minute = 0;
	unsigned char Second;
	typeDateAndTime Date;
	//
	// Year
	//

	//uarttxstring(1,"Calculate Year",2);
  while (TotalSeconds + getYearSeconds(Year) <= Seconds)
		{
			//uarttxstring(1,"Total Second:",0); ltostr(TotalSeconds,10,1,TEMP); uarttxstring(1,TEMP,2);
      TotalSeconds += getYearSeconds(Year);
      Year += 1;
  	}
	//
	// Month
	// 
	//uarttxstring(1,"Calculate Month",2);
  while (TotalSeconds + getMonthSeconds(Year, Month) <= Seconds)
		{
      TotalSeconds += getMonthSeconds(Year, Month);
      Month += 1 ;
  	}

	//
	// Day
	//
	//uarttxstring(1,"Calculate Day",2);
  while (TotalSeconds + getDaySeconds() <= Seconds)
		{
      TotalSeconds += getDaySeconds();
      Day += 1;
  	}

	//
	// Hour
	//
  while (TotalSeconds + getHourSeconds() <= Seconds)
		{
      TotalSeconds += getHourSeconds();
      Hour += 1;
  	}

  //
	// Minute
	//
  while (TotalSeconds + getMinuteSeconds() <= Seconds)
		{
      TotalSeconds += getMinuteSeconds();
      Minute += 1;
  	}

  Second = Seconds - TotalSeconds;

  Date.Year 	= Year;
  Date.Month = Month;
  Date.Day   = Day;

  Date.Hour 		= Hour;
  Date.Minute 	= Minute;
  Date.Second 	= Second;
	return Date;
}
