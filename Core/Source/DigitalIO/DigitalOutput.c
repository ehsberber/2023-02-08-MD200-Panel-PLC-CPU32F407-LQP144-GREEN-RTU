#include "MicroPeripheral.h"  
#include "Registers.h"
#include "PlcDefinition.h"
#include "RegisterOperation.h"
#include "Peripheral.h"
#include "DigitalOutputMicroLayer.h"

extern strcREGISTERS  Registers;
extern strcPLC Plc;
// 
//
// Digital Output Write
//
 
//HAL_StatusTypeDef DigitalOutputWriteToExternalBoardType0(unsigned short SlaveAddress, unsigned char OutputPosition, unsigned char ByteCount)
//{
//	unsigned int TryAgainCounter=0;
//
//	HAL_StatusTypeDef HalStatus= HAL_ERROR;
//
//
//	while (( HalStatus != HAL_OK) && ( TryAgainCounter++ < 0xFFF) )
//		{
//			HalStatus = HAL_I2C_Master_Transmit(&I2C_EXT, SlaveAddress, &Registers.Coil[OutputPosition], ByteCount, HAL_I2C_NO_RESPONSE_TIMEOUT);
//		}
//
//	return HalStatus;
//}

//HAL_StatusTypeDef DigitalOutputWriteToOnBoard(unsigned short SlaveAddress, unsigned char OutputPosition, unsigned char ByteCount)
//{
//
//	unsigned int TryAgainCounter=0;
//
//	HAL_StatusTypeDef HalStatus= HAL_ERROR;
//
//
//	while (( HalStatus != HAL_OK) && ( TryAgainCounter++ < 0xFFF) )
//		{
//			HalStatus = HAL_I2C_Master_Transmit(&I2C_INT, SlaveAddress, &Registers.Coil[OutputPosition], ByteCount, HAL_I2C_NO_RESPONSE_TIMEOUT);
//		}
//
//	return HalStatus;
//}

unsigned char DigitalOutput(void)
{

	Registers.Coil[0] = ( ~(*Plc.Peripheral.DigitalOutput.Master[1])  & Registers.Coil[0 ] ) | *Plc.Peripheral.DigitalOutput.Master[0];
	Registers.Coil[1] = ( ~(*Plc.Peripheral.DigitalOutput.Master[3])  & Registers.Coil[1 ] ) | *Plc.Peripheral.DigitalOutput.Master[2];
	//
	// MicroControler �zerindeki Portlar Kullaniliyor
	//
	DigitalOutputWriteToMicroPort(*(unsigned short*)&Registers.Coil[0]);


	return 1;
}

