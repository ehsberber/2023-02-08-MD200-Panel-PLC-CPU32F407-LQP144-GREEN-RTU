#include "MicroPeripheral.h"  
#include "Registers.h"
#include "DataPositionHolding.h"
#include "DataOperations.h"
#include "DataType.h"
#include "ModbusRegister.h"
#include "Coils.h"
 
#include "ModBus.h"
#include "ModbusCrc.h"

#include "Constant.h"


extern strcREGISTERS Registers; 
extern strcPLC Plc;
extern unsigned char *ModBus;
extern unsigned char *ExternalDataValue;
 

extern unsigned char *Uart[];


#define MODBUS_MAX_DATA_LEN 	512


unsigned short ModBusTcpFunction01(unsigned char *Query,unsigned char *ModBus)
{
	union unionShortInteger DataAddress;
	union unionShortInteger DataLength;
	union unionShortInteger ResponseDataBytes;
	unsigned short ModBusDataLength;
	unsigned int CoilBit,StartCoilNo,CoilArrayIndex;
	unsigned int ByteCounter = 0,CoilNoInDataByte=0;;

	unsigned short i,j,CharCount ;

	//
	// Data Address
	//
	DataAddress.Bytes.Byte0 = Query[8];			// Data Address High Byte
	DataAddress.Bytes.Byte1 = Query[9];			// Data Address Low  Byte
	//
	// Data Length
	//
	DataLength.Bytes.Byte0 = Query[10];
	DataLength.Bytes.Byte1 = Query[11];
	if(DataLength.ShortInteger > 64 )
		{
			DataLength.ShortInteger = 16;
		}

	//
	// Data Process
	//
	for(i=0;i<12;i++)
		ModBus[i] = Query[i];

	StartCoilNo 		= DataAddress.ShortInteger % 32;

	CoilArrayIndex  	= DataAddress.ShortInteger  / 32 ;


	CharCount = DataLength.ShortInteger / 8 ;
	if(DataLength.ShortInteger % 8)
		{
			CharCount++;
		}
	ModBus[8] = CharCount;

	ResponseDataBytes.ShortInteger = CharCount + 3;

	ModBus[4] = ResponseDataBytes.Bytes.Byte0;
	ModBus[5] = ResponseDataBytes.Bytes.Byte1;

	ModBusDataLength = 8 + 1 + CharCount ;

	ModBus[9 + ByteCounter] = 0;
	for(j = StartCoilNo; j < StartCoilNo + DataLength.ShortInteger;j++)
		{

			if( (j != 0) && (j % 32) == 0)
				{
					CoilArrayIndex++;
				}

			CoilBit = 0x01 << (j);

			if ( Registers.Coil[CoilArrayIndex] & CoilBit)
				{
					ModBus[9 + ByteCounter] |= (0x01 << CoilNoInDataByte);
				}
			else
				{
					CoilBit = ~(0x01 << CoilNoInDataByte);
					ModBus[9 + ByteCounter]  &= CoilBit;
				}
			CoilNoInDataByte++;
			if(CoilNoInDataByte == 8)
				{
					CoilNoInDataByte = 0;
					ByteCounter++;
					ModBus[9 + ByteCounter] = 0;
				}
		}
	return ModBusDataLength;
}


unsigned short ModBusTcpFunction02(unsigned char *Query,unsigned char *ModBus)
{
	union unionShortInteger DataAddress;
	union unionShortInteger DataLength;
	union unionShortInteger ResponseDataBytes;
	unsigned short ModBusDataLength;
	unsigned int InputBit,StartInputNo,InputArrayIndex;
	unsigned int ByteCounter = 0,InputNoInputDataByte=0;;

	unsigned short  i,j,CharCount ;

	//
	// Data Address
	//
	DataAddress.Bytes.Byte0 = Query[8];			// Data Address High Byte
	DataAddress.Bytes.Byte1 = Query[9];			// Data Address Low  Byte
	//
	// Data Length
	//
	DataLength.Bytes.Byte0 = Query[10];
	DataLength.Bytes.Byte1 = Query[11];

	if(DataLength.ShortInteger > 64 )
		{
			DataLength.ShortInteger = 16;
		}
	//
	// Data Process
	//
	for(i=0;i<12;i++)
		ModBus[i] = Query[i];

	StartInputNo 		= DataAddress.ShortInteger % 32;

	InputArrayIndex  	= DataAddress.ShortInteger  / 32 ;


	CharCount = DataLength.ShortInteger / 8 ;
	if(DataLength.ShortInteger % 8)
		{
			CharCount++;
		}
	ModBus[8] = CharCount;

	ResponseDataBytes.ShortInteger = CharCount + 3;

	ModBus[4] = ResponseDataBytes.Bytes.Byte0;
	ModBus[5] = ResponseDataBytes.Bytes.Byte1;
	ModBusDataLength = 8 + 1 + CharCount ;

	ModBus[9 + ByteCounter] = 0;
	for(j = StartInputNo; j < StartInputNo + DataLength.ShortInteger;j++)
		{

			if( (j != 0) && (j % 32) == 0)
				{
					InputArrayIndex++;
				}

			InputBit = 0x01 << (j);

			if ( Registers.Input[InputArrayIndex] & InputBit)
				{
					ModBus[9 + ByteCounter] |= (0x01 << InputNoInputDataByte);
				}
			else
				{
					InputBit = ~(0x01 << InputNoInputDataByte);
					ModBus[9 + ByteCounter]  &= InputBit;
				}
			InputNoInputDataByte++;
			if(InputNoInputDataByte == 8)
				{
					InputNoInputDataByte = 0;
					ByteCounter++;
					ModBus[9 + ByteCounter] = 0;
				}
		}
	return ModBusDataLength;
}

unsigned short ModBusTcpFunction03(unsigned char *Query,unsigned char *ModBus)
{
	union unionShortInteger DataAddress;
	union unionShortInteger DataLength;
	union unionShortInteger Length;
	unsigned short ModBusDataLength;
	signed short i,j;

	//
	// Data Address
	//
	DataAddress.Bytes.Byte0 = Query[8];			// Data Address High Byte
	DataAddress.Bytes.Byte1 = Query[9];			// Data Address Low  Byte
	//
	// Data Length
	//
	DataLength.Bytes.Byte0 = Query[10];
	DataLength.Bytes.Byte1 = Query[11];


	//
	// Data Address
	//
	DataAddress.ShortInteger *= 2;
	//
	// Data Process
	//
	for(i=0;i<4;i++)
		ModBus[i] = Query[i];

	DataLength.ShortInteger *= 2;

	Length.ShortInteger  = DataLength.ShortInteger + 3;

	ModBusDataLength = Length.ShortInteger + 6;

	ModBus[4] = Length.Bytes.Byte0 ;
	ModBus[5] = Length.Bytes.Byte1 ;

	ModBus[6] = Registers.Holding[HA_SLAVE_ADDRESS];
	ModBus[7] = Query[7];
	//
	// Data Byte Count
	//
	ModBus[8] = DataLength.Bytes.Byte1;
	//
	// Holding Register Byte Olarak Adreslendiginde Short Tipinde Adres icin
	//

	for(j=0; j<DataLength.ShortInteger; j++)
		{
			ModBus[9 + (j*2)    ] = Registers.Holding[DataAddress.ShortInteger + 1 + (j*2)];
			ModBus[9 + (j*2) + 1] = Registers.Holding[DataAddress.ShortInteger + 0 + (j*2)];
		}

	return ModBusDataLength;
}

unsigned short ModBusTcpFunction04(unsigned char *Query,unsigned char *ModBus)
{
	union unionShortInteger DataAddress;
	union unionShortInteger DataLength;
	union unionShortInteger Length;
	unsigned short ModBusDataLength;
	signed short i,j;

	//
	// Data Address
	//
	DataAddress.Bytes.Byte0 = Query[8];			// Data Address High Byte
	DataAddress.Bytes.Byte1 = Query[9];			// Data Address Low  Byte
	//
	// Data Length
	//
	DataLength.Bytes.Byte0 = Query[10];
	DataLength.Bytes.Byte1 = Query[11];

	//
	// Data Address
	//
	DataAddress.ShortInteger *= 2;
	//
	// Data Process
	//
	for(i=0;i<4;i++)
		ModBus[i] = Query[i];

	DataLength.ShortInteger *= 2;

	Length.ShortInteger  = DataLength.ShortInteger + 3;

	ModBusDataLength = Length.ShortInteger + 6;

	ModBus[4] = Length.Bytes.Byte0 ;
	ModBus[5] = Length.Bytes.Byte1 ;

	ModBus[6] = Registers.Holding[HA_SLAVE_ADDRESS];
	ModBus[7] = Query[7];
	//
	// Data Byte Count
	//
	ModBus[8] = DataLength.Bytes.Byte1;
	//
	// Holding Register Byte Olarak Adreslendiginde Short Tipinde Adres icin
	//

	for(j=0; j<DataLength.ShortInteger; j++)
		{
			ModBus[9 + (j*2)    ] = Registers.Status[DataAddress.ShortInteger + 1 + (j*2)];
			ModBus[9 + (j*2) + 1] = Registers.Status[DataAddress.ShortInteger + 0 + (j*2)];
		}

	return ModBusDataLength;
}

unsigned short ModBusTcpFunction05(unsigned char *Query,unsigned char *ModBus)
{
	union unionShortInteger DataAddress;
	union unionShortInteger DataLength;
	unsigned short ModBusDataLength;
	unsigned int Index,CoilBit;
	signed short i;
	//
	// Data Address
	//
	DataAddress.Bytes.Byte0 = Query[8];			// Data Address High Byte
	DataAddress.Bytes.Byte1 = Query[9];			// Data Address Low  Byte

	//
	// Data Address
	//
	DataLength.Bytes.Byte0 = Query[10];			// Data Address High Byte
	DataLength.Bytes.Byte1 = Query[11];			// Data Address Low  Byte

	//
	// Data Process
	//
	for(i=0;i<12;i++)
		ModBus[i] = Query[i];


	ModBusDataLength = 12;

	//
	// Find Coil Char
	//
	Index = DataAddress.ShortInteger / 32;

	//
	// Find Coil Position On The Coil Char
	//
	i = DataAddress.ShortInteger % 32;

	//
	// Coil Bits
	//

	CoilBit = 0x01 <<i;
	if (DataLength.ShortInteger == 0xFF00)
		{
			Registers.Coil[Index] |= CoilBit;
		}
	else
		{
			CoilBit = ~CoilBit;
			Registers.Coil[Index] &= CoilBit;
		}

	return ModBusDataLength;
}


unsigned short  ModBusTcpFunction06(unsigned char *Query,unsigned char *ModBus)
{
	union unionShortInteger DataAddress;
	unsigned short ModBusDataLength;
	signed char CharCount;
	signed short i;

	//
	// Data Address
	//
	DataAddress.Bytes.Byte0 = Query[8];			// Data Address High Byte
	DataAddress.Bytes.Byte1 = Query[9];			// Data Address Low  Byte

	//
	// Data Address
	//
	DataAddress.ShortInteger *= 2;
	//
	// Data Process
	//
	for(i=0;i<12;i++)
		ModBus[i] = Query[i];


	ModBusDataLength = 12;

	CharCount = Query[12];

	if(	Query[7] == MDB_FNC_PSR)
		{
			Registers.Holding[DataAddress.ShortInteger + 1 ] = Query[10] ;
			Registers.Holding[DataAddress.ShortInteger + 0 ] = Query[11] ;

			AddDataList(1, DataAddress.ShortInteger, 2, 0x80);
		}
	else
		{
			Registers.Holding[DataAddress.ShortInteger + 1 ] = Query[11] ;
			Registers.Holding[DataAddress.ShortInteger + 0 ] = Query[10] ;

			AddDataList(1, DataAddress.ShortInteger, CharCount, 0x80);
		}

	return ModBusDataLength;
}

unsigned short  ModBusTcpFunction0F(unsigned char *Query,unsigned char *ModBus)
{
	union unionShortInteger DataAddress;
	union unionShortInteger DataLength;
	union unionShortInteger Length;
	unsigned short ModBusDataLength;
	unsigned short CoilArrayIndex,StartCoilNo;
	unsigned int CoilByte,CoilBit;
	unsigned int CoilNoInDataByte=0;
	signed char ByteCounter=0;
	signed short i,j;

	//
	// Data Address
	//
	DataAddress.Bytes.Byte0 = Query[8];			// Data Address High Byte
	DataAddress.Bytes.Byte1 = Query[9];			// Data Address Low  Byte
	//
	// Data Length
	//
	DataLength.Bytes.Byte0 = Query[10];
	DataLength.Bytes.Byte1 = Query[11];
	//
	// Data Process
	//
	for(i=0;i<12;i++)
		ModBus[i] = Query[i];

	Length.ShortInteger  = 6;

	ModBusDataLength = 12;

	ModBus[4] = Length.Bytes.Byte0 ;
	ModBus[5] = Length.Bytes.Byte1 ;

	StartCoilNo = DataAddress.ShortInteger % 32;
	CoilArrayIndex  = DataAddress.ShortInteger  / 32 ;
	CoilByte = Query[13 + ByteCounter];

	for(j = StartCoilNo; j< StartCoilNo + DataLength.ShortInteger;j++)
		{

			if( (j != 0) &&(j % 32) == 0)
				{
					CoilArrayIndex++;
				}

			CoilBit = 0x01 << (j%32);

			if (CoilByte & (0x01 << CoilNoInDataByte))
				{
					Registers.Coil[CoilArrayIndex] |= CoilBit;
				}
			else
				{
					CoilBit = ~CoilBit;
					Registers.Coil[CoilArrayIndex] &= CoilBit;
				}
			CoilNoInDataByte++;
			if(CoilNoInDataByte == 8)
				{
					CoilNoInDataByte = 0;
					ByteCounter++;
					CoilByte = Query[13 + ByteCounter];
				}
		}
	return ModBusDataLength;
}

unsigned short  ModBusTcpFunction10(unsigned char *Query,unsigned char *ModBus)
{
	union unionShortInteger DataAddress;
	union unionShortInteger DataLength;
	unsigned short ModBusDataLength;
	//signed char CharCount;
	signed short i,j;

	//
	// Data Address
	//
	DataAddress.Bytes.Byte0 = Query[8];			// Data Address High Byte
	DataAddress.Bytes.Byte1 = Query[9];			// Data Address Low  Byte
	//
	// Data Length
	//
	DataLength.Bytes.Byte0 = Query[10];
	DataLength.Bytes.Byte1 = Query[11];


	//
	// Data Address
	//
	DataAddress.ShortInteger *= 2;
	//
	// Data Process
	//
	for(i=0;i<12;i++)
		ModBus[i] = Query[i];

	DataLength.ShortInteger *= 2;

	//Length.ShortInteger  = DataLength.ShortInteger + 3;

	ModBusDataLength = 12;

	for(j = (DataLength.ShortInteger/2)-1; j >=0 ; j--)
		{
			Registers.Holding[DataAddress.ShortInteger + 1 + (j*2)] = Query[13 + (j*2)     ] ;
			Registers.Holding[DataAddress.ShortInteger + 0 + (j*2)] = Query[13 + (j*2) + 1 ] ;
		}
	AddDataList(1, DataAddress.ShortInteger, DataLength.ShortInteger, 0x80);

	return ModBusDataLength;
}

unsigned short ModBusTcpCommunication(unsigned char *Query,unsigned char *ModBus)
{
 	unsigned short ModBusDataLength = 0;

	static unsigned char OnlineStatus;

	//if ( (Query[6] != *Plc.SlaveAddress) && (Query[6] != 0)  ) return 0;

	OnlineStatus = !OnlineStatus;

	// Sample Query Code
	// 0    1   2   3   4   5   6   7  8   9   10  11
	//{04}{99}{00}{00}{00}{06}{01}{03}{00}{00}{00}{0A}
	//
	//0..1 		{04}{99}  	: Transaction Identifier
	//2..3 		{00}{00}	: Protocol Identifier
	//4..5 		{00}{06}	: Length Field
	//6    		{01}		: Unit Id
	//7    		{03}	 	: Function Code
	//8..9  	{00}{00} 	: Start Address
	//10..11	{00}{0A}	: Data Length


	//
	// ModBus Function
	//
	switch(Query[7])
		{
			case MDB_FNC_CR:
						ModBusDataLength = ModBusTcpFunction01(Query,ModBus);
			 		break;

			case MDB_FNC_IS:
						ModBusDataLength = ModBusTcpFunction02(Query,ModBus);
					break;

			case MDB_FNC_HR_R:
			case MDB_FNC_HR:
			case MDB_FNC_HRA:
						ModBusDataLength = ModBusTcpFunction03(Query,ModBus);
					break;

			case MDB_FNC_SR:
			case MDB_FNC_SR_R:
			case MDB_FNC_SRA:
						ModBusDataLength = ModBusTcpFunction04(Query,ModBus);
					break;

			case  MDB_FNC_FSC:
						ModBusDataLength = ModBusTcpFunction05(Query,ModBus);
					break;

				case MDB_FNC_FPC:
						ModBusDataLength = ModBusTcpFunction0F(Query,ModBus);
					break;

				case MDB_FNC_PSR:
						ModBusDataLength = ModBusTcpFunction06(Query,ModBus);;
					break;

				case MDB_FNC_PMR:
						ModBusDataLength = ModBusTcpFunction10(Query,ModBus);
					break;


		}
	return ModBusDataLength;
};

