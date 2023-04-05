#include "MicroPeripheral.h"

unsigned char  M41T_Write(I2C_HandleTypeDef *hi2c, unsigned char *WriteData,  unsigned char DataLength);
HAL_StatusTypeDef M41T_Read(I2C_HandleTypeDef *hi2c, unsigned char  Address,  unsigned char *RtcData, unsigned char DataLength );
HAL_StatusTypeDef M41T_ReadClock(I2C_HandleTypeDef *hi2c, unsigned char *DateAddress,unsigned long *Seconds);

void RtcWriteClock(unsigned char *RtcData);
void SetRtc(unsigned char *RtcData, char Format,unsigned char *DateAddress);
