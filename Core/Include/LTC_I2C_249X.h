
#define LTC_CONVERSION_CYCLE_CONCLUDED 0x80

#include "MicroPeripheral.h"
#include "DataType.h"

unsigned char LTC_I2C_2499_WriteChannel(I2C_TypeDef *I2Cx, unsigned char SlaveAddress,unsigned short ConfigBytes,  unsigned char Channel);
//unsigned int LTC_I2C_2499_ReadChannelData(I2C_HandleTypeDef *I2Cx, unsigned char SlaveAddress,  unsigned char *IsChannelDataRead);
//signed int LTC_I2C_ADC_2499_Read(I2C_HandleTypeDef *I2Cx, unsigned char SlaveAddress, unsigned char Channel, unsigned char NextChannel, unsigned char *ProcessLine);
void LTC2499Read(I2C_HandleTypeDef *I2Cx, strcADC *ADC_Module);
void LTC_249X_Read(I2C_HandleTypeDef *I2Cx, unsigned char SlaveAddress, strcADC *ADC_DATA) ;
unsigned short LTC_I2C_2499_Config(unsigned char Channel);
void AdcModuleLTC2499(unsigned char  ModuleNo );


