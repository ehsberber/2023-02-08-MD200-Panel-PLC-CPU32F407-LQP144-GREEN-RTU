#include "MicroPeripheral.h"  
#include "DataPositionStatus.h"
#include "M41T_RTC_I2C.h"
#include "ConvertString.h"
#include "String.h"
#include "DateTime.h"
#include "ConvertDate.h"

extern unsigned char *StatusRegister;

 
unsigned char M41T_Write(I2C_HandleTypeDef *hi2c, unsigned char *WriteData,  unsigned char DataLength)
{
 HAL_StatusTypeDef Status;
 
 
// //
// // Set Address To Be Write
// //
// Status = HAL_I2C_Master_Transmit(hi2c, RTC_M41T_ON_BOARD_SLAVE_ADDRESS , &WriteAddress, 1, 1000);
// 
// //
// // Write Data 
// //
// if(Status == HAL_OK)
	//
	// First Byte Of Write Data is Address Which is to be written data
	//
	unsigned char SlaveAddress ;
	SlaveAddress = RTC_M41T_ON_BOARD_SLAVE_ADDRESS;
	
	Status = HAL_I2C_Master_Transmit(hi2c, SlaveAddress, WriteData, DataLength, HAL_I2C_NO_RESPONSE_TIMEOUT);
	
	return 	Status;
	
}

 
HAL_StatusTypeDef M41T_Read(I2C_HandleTypeDef *hi2c, unsigned char  ReadAddress,  unsigned char *ReadData, unsigned char DataLength )
{

 HAL_StatusTypeDef Status;

 //
 // Set Address To Be Read
 //
 Status = HAL_I2C_Master_Transmit(hi2c, RTC_M41T_ON_BOARD_SLAVE_ADDRESS , &ReadAddress, 1, HAL_I2C_NO_RESPONSE_TIMEOUT);

 //
 // Read Data 
 //
 if(Status == HAL_OK)
 	 {
	 	 Status = HAL_I2C_Master_Receive(hi2c, RTC_M41T_ON_BOARD_SLAVE_ADDRESS, ReadData, DataLength, HAL_I2C_NO_RESPONSE_TIMEOUT);
 	 }
	return 	Status;
}


#define MAX_TIME_DIFFERANCE					15 
#define ACCEPTED_TIME_ERROR_COUNTER 50

signed int LastDateDifferance(unsigned char *RtcData)
{
	static unsigned int BackupSeconds = 0;	
	static unsigned char ErrorCounter=0;
	signed int Seconds = 0,Differance ;	
	typeDateAndTime DateforSeconds;
	
	DateforSeconds.Day 		=  bcdtod(RtcData[5]); 
	DateforSeconds.Month 	=  bcdtod(RtcData[6]); 	 
	DateforSeconds.Year 	=  bcdtod(RtcData[7]); 	 
	DateforSeconds.Hour 	=  bcdtod(RtcData[3]); 	 
	DateforSeconds.Minute =  bcdtod(RtcData[2]);	 
	DateforSeconds.Second =  bcdtod(RtcData[1]);	
	Seconds = DateToSeconds(DateforSeconds);
	Differance = Seconds -  BackupSeconds;

	if(Differance > MAX_TIME_DIFFERANCE)	
		{
			if(++ErrorCounter < ACCEPTED_TIME_ERROR_COUNTER) return -1;
		}
	BackupSeconds = Seconds;
	ErrorCounter = 0;
	return Differance;
}	

HAL_StatusTypeDef  M41T_ReadClock(I2C_HandleTypeDef *hi2c, unsigned char *DateAddress ,unsigned long *Seconds) 
{
	unsigned char WriteChar[2];  
	unsigned char RTC_Data[20];
	
	typeDateAndTime DateforSeconds;
	HAL_StatusTypeDef Status;
	
	Status = M41T_Read(hi2c, 0, &RTC_Data[0], 16);
					
	if (Status == HAL_OK)
		{
			if((RTC_Data[0x0C] & 0x40) || (RTC_Data[0x0F] & 0x04))
				{
					//
					// Restart Rtc
					//
					WriteChar[0] = 0x0C;
					WriteChar[1] = 0x00;
					M41T_Write(hi2c, WriteChar, 2);  
					
					WriteChar[0] = 0x0F;
					WriteChar[1] = 0x00;
					M41T_Write(hi2c, &WriteChar[0], 2); 
//					return 0;
				}
			
//			Differance = LastDateDifferance(RTC_Data);
//			if( Differance <= 0 )				
//				{
//					return 0;
//				}
			
			DateAddress[RTC_DAY_POS] 					=  RTC_Data[5];
			DateAddress[RTC_MONTH_POS] 				=  RTC_Data[6];
			DateAddress[RTC_YEAR_POS] 				=  RTC_Data[7];
			DateAddress[RTC_HOUR_POS] 				=  RTC_Data[3];
			DateAddress[RTC_MINUTE_POS] 			=  RTC_Data[2];
			DateAddress[RTC_SECOND_POS] 			=  RTC_Data[1];
			DateAddress[RTC_MILISECOND_POS] 	=  RTC_Data[0];
			DateAddress[RTC_DAYOFWEEK_POS] 		=  RTC_Data[4];
			
			DateforSeconds.Day 		=  bcdtod(DateAddress[RTC_DAY_POS]);
			DateforSeconds.Month 	=  bcdtod(DateAddress[RTC_MONTH_POS]);
			DateforSeconds.Year 	=  bcdtod(DateAddress[RTC_YEAR_POS]);
			DateforSeconds.Hour 	=  bcdtod(DateAddress[RTC_HOUR_POS]);
			DateforSeconds.Minute =  bcdtod(DateAddress[RTC_MINUTE_POS]);
			DateforSeconds.Second =  bcdtod(DateAddress[RTC_SECOND_POS]);

			*Seconds = DateToSeconds(DateforSeconds);
		}
		
	return Status;
}

