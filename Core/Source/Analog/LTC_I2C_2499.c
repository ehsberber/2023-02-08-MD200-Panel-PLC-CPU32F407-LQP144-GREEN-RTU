#include "MicroPeripheral.h"
#include "LTC_2499.h" 
#include "ConvertInteger.h"
#include "ConvertDouble.h"
#include "Registers.h"
#include "Peripheral.h"
#include "AnalogInput.h"
#include "LTC_I2C_249X.h"

extern strcPLC Plc;
extern strcADC ADC_Modules[MAX_AI_BOARD_COUNT];

unsigned short LTC2499Config(unsigned char Channel)
{
	unsigned short ConfigByte=0;

	switch(Channel)
		{
			case 0: ConfigByte = LTC_2499_CONFIG_MUST | LTC_2499_CONFIG_EN | LTC_2499_CONFIG_SGL | LTC_2499_CONFIG_ODD | 0x00;
							break;

			case 1: ConfigByte = LTC_2499_CONFIG_MUST | LTC_2499_CONFIG_EN | LTC_2499_CONFIG_SGL | LTC_2499_CONFIG_SGN | 0x00;
							break;

			case 2: ConfigByte = LTC_2499_CONFIG_MUST | LTC_2499_CONFIG_EN | LTC_2499_CONFIG_SGL | LTC_2499_CONFIG_ODD | 0x01;
							break;

			case 3: ConfigByte = LTC_2499_CONFIG_MUST | LTC_2499_CONFIG_EN | LTC_2499_CONFIG_SGL | LTC_2499_CONFIG_SGN | 0x01;
							break;

			case 4: ConfigByte = LTC_2499_CONFIG_MUST | LTC_2499_CONFIG_EN | LTC_2499_CONFIG_SGL | LTC_2499_CONFIG_ODD | 0x02;
							break;

			case 5: ConfigByte = LTC_2499_CONFIG_MUST | LTC_2499_CONFIG_EN | LTC_2499_CONFIG_SGL | LTC_2499_CONFIG_SGN | 0x02;
							break;

			case 6: ConfigByte = LTC_2499_CONFIG_MUST | LTC_2499_CONFIG_EN | LTC_2499_CONFIG_SGL | LTC_2499_CONFIG_ODD | 0x03;
							break;

			case 7: ConfigByte = LTC_2499_CONFIG_MUST | LTC_2499_CONFIG_EN | LTC_2499_CONFIG_SGL | LTC_2499_CONFIG_SGN | 0x03;
							break;

			case 8: ConfigByte = LTC_2499_CONFIG_MUST | LTC_2499_CONFIG_EN | LTC_2499_CONFIG_SGL | LTC_2499_CONFIG_ODD | 0x04;
							break;

			case 9: ConfigByte = LTC_2499_CONFIG_MUST | LTC_2499_CONFIG_EN | LTC_2499_CONFIG_SGL | LTC_2499_CONFIG_SGN | 0x04;
							break;

			case 10: ConfigByte = LTC_2499_CONFIG_MUST | LTC_2499_CONFIG_EN | LTC_2499_CONFIG_SGL | LTC_2499_CONFIG_ODD | 0x05;
							break;

			case 11: ConfigByte = LTC_2499_CONFIG_MUST | LTC_2499_CONFIG_EN | LTC_2499_CONFIG_SGL | LTC_2499_CONFIG_SGN | 0x05;
							break;

			case 12: ConfigByte = LTC_2499_CONFIG_MUST | LTC_2499_CONFIG_EN | LTC_2499_CONFIG_SGL | LTC_2499_CONFIG_ODD | 0x06;
							break;

			case 13: ConfigByte = LTC_2499_CONFIG_MUST | LTC_2499_CONFIG_EN | LTC_2499_CONFIG_SGL | LTC_2499_CONFIG_SGN | 0x06;
							break;

			case 14: ConfigByte = LTC_2499_CONFIG_MUST | LTC_2499_CONFIG_EN | LTC_2499_CONFIG_SGL | LTC_2499_CONFIG_ODD | 0x07;
							break;

			case 15: ConfigByte = LTC_2499_CONFIG_MUST | LTC_2499_CONFIG_EN | LTC_2499_CONFIG_SGL | LTC_2499_CONFIG_SGN | 0x07;
							break;

		}
	ConfigByte <<= 8;
	//ConfigByte |=  LTC_2499_CONFIG_EN2 ;

	return ConfigByte ;
}
 

signed int ConvertToChannelValue(unsigned int intChannelValue,unsigned char *Status )
{
	double dblChannelValue;
	signed int  ChannelValue=0;
	unsigned char IsChannelValuePositive;
	

	if ((intChannelValue & (LTC_2499_SIGN | LTC_2499_MSB)) == (LTC_2499_SIGN | LTC_2499_MSB) )	
		{
			//
			// OUT OF RANGE  	Vin >=  FS	  FS (Full Scale) = Vref * 0.5
			//
			*Status |=  ADC_DATA_STATUS_OUT_OF_RANGE_HIGH;
		}
	else
		{
			if ((intChannelValue & (LTC_2499_SIGN | LTC_2499_MSB) )  == 0x00000000 )
				{
					//
					// OUT OF RANGE  	Vin < -FS	FS (Full Scale) = Vref * 0.5
					//
					*Status |=  ADC_DATA_STATUS_OUT_OF_RANGE_LOW;
				}
			else
				{	
 
					if (intChannelValue & LTC_2499_SIGN) 
						{
							IsChannelValuePositive = 1; 
							intChannelValue >>= 6;
							intChannelValue &= 0x01FFFFFF;
						}
					else  
						{
								IsChannelValuePositive = 0;
								intChannelValue >>= 6;
								
								intChannelValue -= 1;
								intChannelValue = ~intChannelValue;
								intChannelValue &= 0x01FFFFFF;
						}
						 
					//
					// Pozitif Number
					// 			 
					dblChannelValue = intChannelValue;
					//dblChannelValue = dblChannelValue * 0.09834766;   // 0.5*Vref/ 2^24 = 0.5 * 3.3V / 2^24 = 0.09834766 microVolt
					ChannelValue = dblChannelValue;
							 
					//
						
						if (!IsChannelValuePositive )  ChannelValue *= -1; 
				 
				}
		}
	
	return ChannelValue;
}

void LTC2499Read(I2C_HandleTypeDef *I2Cx, strcADC *ADC_Module) // unsigned char SlaveAddress, unsigned char Channel, unsigned char NextChannel, unsigned char *ProcessLine)
{
	unsigned char Status;

	unsigned char  ByteCounter;
	unsigned char Bytes[4];
 
	unsigned int ChannelData=0;

 	unsigned short ConfigBytes=0; //,i;

	HAL_StatusTypeDef I2C_State;

	switch(ADC_Module->Process)
		{
			case 0:
				//
				// BASLANGIC DURUMU VE BU GROUP BASLANGICTA CALISTIRILIR
				//
				ConfigBytes = LTC2499Config(ADC_Module->Channel);
				//
				//
				//
				Bytes[0] = ConfigBytes>>8;
				Bytes[1] = 0xA8;
				if( HAL_I2C_Master_Transmit(I2Cx, ADC_Module->SlaveAddress, &Bytes[0], 2, HAL_I2C_NO_RESPONSE_TIMEOUT) == HAL_OK)
					{
						ADC_Module->Process = 2;
					}
				else
					{
						ADC_Module->Process = 1;
					}
				break;

			case 1:
				ConfigBytes = LTC2499Config(ADC_Module->Channel);
				Bytes[0] = ConfigBytes>>8;
				Bytes[1] = 0xA8;

				if( HAL_I2C_Master_Transmit(I2Cx, ADC_Module->SlaveAddress, &Bytes[0], 2, HAL_I2C_NO_RESPONSE_TIMEOUT) == HAL_OK)
					{
						ADC_Module->Process = 2;
					}
				break;

			case 2:

				//
				// Read Channel Data
				//
				I2C_State = HAL_I2C_Master_Receive(I2Cx, ADC_Module->SlaveAddress, &Bytes[0], 4, HAL_I2C_NO_RESPONSE_TIMEOUT);

				if (I2C_State == HAL_OK)
					{
						for(ByteCounter=0; ByteCounter<4; ByteCounter++)
							{
								ChannelData <<= 8;
								ChannelData |= Bytes[ByteCounter];
							}

						ADC_Module->ChannelValue = ConvertToChannelValue(ChannelData, &Status);

						ADC_Module->Process = 0;
					}
				else
					{
						Plc.Warning->Adc = 1;
					};

			break;
		}
	//return ChannelValue;
}

void AdcModuleLTC2499(unsigned char  ModuleNo )
{
	I2C_HandleTypeDef *I2Cx;
	double dblValue;
	unsigned char SequenceNo;
	switch (ModuleNo)
		{
			case ADC_ONBAORD_IC_NO_00:
					I2Cx = &I2C_INT;
					ADC_Modules[ModuleNo].SlaveAddress = 0x4C;
				break;

			case ADC_ONBAORD_IC_NO_01:
					I2Cx = &I2C_INT;
					ADC_Modules[ModuleNo].SlaveAddress = 0x28;
				break;
		}

	if(ADC_Modules[ModuleNo].FirstRead )
		{
			ADC_Modules[ModuleNo].Channel     = 0;
			ADC_Modules[ModuleNo].NextChannel = 1;

			ADC_Modules[ModuleNo].FirstRead = 0;
		}

	SequenceNo = ADC_Modules[ModuleNo].Channel  + *Plc.Peripheral.AnalogInput.ModuleChannelPos[ModuleNo];

	LTC2499Read(I2Cx, &ADC_Modules[ModuleNo]);

	if(ADC_Modules[ModuleNo].Process == 0)
		{
			dblValue = ADC_Modules[ModuleNo].ChannelValue ;
			dblValue = dblValue * *Plc.Peripheral.AnalogInput.ModuleResolutionMultiplier[ModuleNo] / 1000;

			*Plc.Peripheral.AnalogInput.AnalogValue[SequenceNo] = dblValue;

			ChannelValueCalculate( SequenceNo, *Plc.Peripheral.AnalogInput.AnalogValue[SequenceNo]);

			ADC_Modules[ModuleNo].Channel++;
			ADC_Modules[ModuleNo].NextChannel++;

			if(ADC_Modules[ModuleNo].Channel > 3)
				{
					ADC_Modules[ModuleNo].Channel     = 0;
					ADC_Modules[ModuleNo].NextChannel = 1;
				}
			else
				{
					if(ADC_Modules[ModuleNo].Channel == 3 )
						{
							ADC_Modules[ModuleNo].NextChannel = 0;
						}
				}
		}

}
