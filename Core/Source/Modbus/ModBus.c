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

 
//extern unsigned short 	RelayProcess[];
//extern unsigned char 	RelayProcessCount[];
//extern unsigned char 	RelayNo[];
//extern unsigned short 	RelayBeginTime[]; 		// sn cinsidnde ON Suresi
//extern unsigned short 	RelayOnTime[]; 			// sn cinsidnde ON Suresi
//extern unsigned short 	RelayOffTime[];			// sn cinsidnde OFF Suresi
  //
	//QUERY:
	//<Slave Address><Function><Starting Address Hi><Starting Address Lo><No. of DataLength Hi><No. of DataLength Lo><Error Check LRC><Trailer CR LF>
	//RESPONSE:
	//<Slave Address><Function><Byte Count><Data Hi><Data Lo><Data Hi><Data Lo><Data Hi><Data Lo><Error Check LRC> <CR> <LF>	
	//
  //
	//
	//
#define MODBUS_MAX_DATA_LEN 	512



unsigned short ModBusFunction01(unsigned char *Query,unsigned char *ModBus)
{
	union unionShortInteger DataAddress;
	union unionShortInteger DataLength;

	unsigned short ModBusDataLength;
	unsigned int CoilBit,StartCoilNo,CoilArrayIndex;
	unsigned int ByteCounter = 0,CoilNoInDataByte=0;;

	signed short j,CharCount ;

	//
	// Data Address
	//
	DataAddress.Bytes.Byte0 = Query[2];			// Data Address High Byte
	DataAddress.Bytes.Byte1 = Query[3];			// Data Address Low  Byte


	//
	// Data Length
	//
	DataLength.Bytes.Byte0 = Query[4];
	DataLength.Bytes.Byte1 = Query[5];

	//
	// Creating Response Data
	//

	//
	// Data Process
	//
	ModBusDataLength = DataLength.ShortInteger;

	ModBus[0] = Registers.Holding[HA_SLAVE_ADDRESS];
	ModBus[1] = Query[1];

	if(DataLength.ShortInteger > 64 )
		{
			DataLength.ShortInteger = 16;
		}


	StartCoilNo 		= DataAddress.ShortInteger % 32;
	CoilArrayIndex  	= DataAddress.ShortInteger  / 32 ;

	CharCount = DataLength.ShortInteger / 8 ;
	if(DataLength.ShortInteger % 8)
		{
			CharCount++;
		}

	ModBus[2] = CharCount;

	ModBusDataLength = 2 + 1 + CharCount ;

	ModBus[3 + ByteCounter] = 0;
	for(j = StartCoilNo; j < StartCoilNo + DataLength.ShortInteger;j++)
		{

			if( (j != 0) && (j % 32) == 0)
				{
					CoilArrayIndex++;
				}

			CoilBit = 0x01 << (j);

			if ( Registers.Coil[CoilArrayIndex] & CoilBit)
				{
					ModBus[3 + ByteCounter] |= (0x01 << CoilNoInDataByte);
				}
			else
				{
					CoilBit = ~(0x01 << CoilNoInDataByte);
					ModBus[3 + ByteCounter]  &= CoilBit;
				}
			CoilNoInDataByte++;
			if(CoilNoInDataByte == 8)
				{
					CoilNoInDataByte = 0;
					ByteCounter++;
					ModBus[3 + ByteCounter] = 0;
				}
		}
	return ModBusDataLength;
}


unsigned short ModBusFunction02(unsigned char *Query,unsigned char *ModBus)
{
	union unionShortInteger DataAddress;
	union unionShortInteger DataLength;

	unsigned short ModBusDataLength;
	unsigned int InputBit,StartInputNo,InputArrayIndex;
	unsigned int ByteCounter = 0,InputNoInDataByte=0;;

	signed short  j,CharCount ;

	//
	// Data Address
	//
	DataAddress.Bytes.Byte0 = Query[2];			// Data Address High Byte
	DataAddress.Bytes.Byte1 = Query[3];			// Data Address Low  Byte


	//
	// Data Length
	//
	DataLength.Bytes.Byte0 = Query[4];
	DataLength.Bytes.Byte1 = Query[5];

	//
	// Creating Response Data
	//

	//
	// Data Process
	//
	ModBusDataLength = DataLength.ShortInteger;

	ModBus[0] = Registers.Holding[HA_SLAVE_ADDRESS];
	ModBus[1] = Query[1];

	if(DataLength.ShortInteger > 64 )
		{
			DataLength.ShortInteger = 16;
		}


	StartInputNo 		= DataAddress.ShortInteger % 32;
	InputArrayIndex  	= DataAddress.ShortInteger  / 32 ;

	CharCount = DataLength.ShortInteger / 8 ;
	if(DataLength.ShortInteger % 8)
		{
			CharCount++;
		}

	ModBus[2] = CharCount;

	ModBusDataLength = 2 + 1 + CharCount ;

	ModBus[3 + ByteCounter] = 0;
	for(j = StartInputNo; j < StartInputNo + DataLength.ShortInteger;j++)
		{

			if( (j != 0) && (j % 32) == 0)
				{
					InputArrayIndex++;
				}

			InputBit = 0x01 << (j);

			if ( Registers.Input[InputArrayIndex] & InputBit)
				{
					ModBus[3 + ByteCounter] |= (0x01 << InputNoInDataByte);
				}
			else
				{
					InputBit = ~(0x01 << InputNoInDataByte);
					ModBus[3 + ByteCounter]  &= InputBit;
				}
			InputNoInDataByte++;
			if(InputNoInDataByte == 8)
				{
					InputNoInDataByte = 0;
					ByteCounter++;
					ModBus[3 + ByteCounter] = 0;
				}
		}
	return ModBusDataLength;
}

unsigned short ModBusFunction03(unsigned char *Query,unsigned char *ModBus)
{
	union unionShortInteger DataAddress;
	union unionShortInteger DataLength;
	unsigned short ModBusDataLength;
	signed short i,j;

	for(i=0;i<7;i++)
		{
			ModBus[i] = Query[i];
		}
	//
	// Data Address
	//
	DataAddress.Bytes.Byte0 = Query[2];			// Data Address High Byte
	DataAddress.Bytes.Byte1 = Query[3];			// Data Address Low  Byte

	//
	// Data Length
	//
	DataLength.Bytes.Byte0 = Query[4];
	DataLength.Bytes.Byte1 = Query[5];

	//
	// Holding Register Byte Olarak Adreslendiginde Short Tipinde Adres icin
	//
	DataAddress.ShortInteger *= 2;

	if (Query[1] == MDB_FNC_HR)
		{
			for(j=0;j<DataLength.ShortInteger;j++)
				{
					ModBus[3 + (j*2)    ] = Registers.Holding[DataAddress.ShortInteger + 1 + (j*2)];
					ModBus[3 + (j*2) + 1] = Registers.Holding[DataAddress.ShortInteger + 0 + (j*2)];
				}
			ModBus[2]	= DataLength.ShortInteger * 2 ;
		}
	else if(Query[1] == MDB_FNC_HRA)
			{
				i = 0;
				while(i<DataLength.ShortInteger) { ModBus[3+i] = Registers.Holding[DataAddress.ShortInteger + i]; i++;}
				ModBus[2]	= DataLength.ShortInteger;
			}
		else
			{
				j = DataLength.ShortInteger;
				i = 0;
				while(j--) {ModBus[3+i] = Registers.Holding[DataAddress.ShortInteger + j]; i++; }
				ModBus[2]	= DataLength.ShortInteger;
			}

	ModBusDataLength = ModBus[2] + 3;

	return ModBusDataLength;
}

unsigned short ModBusFunction04(unsigned char *Query,unsigned char *ModBus)
{
	union unionShortInteger DataAddress;
	union unionShortInteger DataLength;
	unsigned short ModBusDataLength;
	signed short  i,j ;


	for(i=0;i<7;i++)
		{
			ModBus[i] = Query[i];
		}
	//
	// Data Address
	//
	DataAddress.Bytes.Byte0 = Query[2];			// Data Address High Byte
	DataAddress.Bytes.Byte1 = Query[3];			// Data Address Low  Byte
	DataAddress.ShortInteger *= 2;
	//
	// Data Length
	//
	DataLength.Bytes.Byte0 = Query[4];
	DataLength.Bytes.Byte1 = Query[5];

	//
	// Status Register Byte Olarak Adreslendiginde Short Tipinde Adres icin
	//

	for(j=0;j<DataLength.ShortInteger;j++)
		{
			ModBus[3 + (j*2)    ] = Registers.Status[DataAddress.ShortInteger + 1 + (j*2)];
			ModBus[3 + (j*2) + 1] = Registers.Status[DataAddress.ShortInteger + 0 + (j*2)];
		}
	ModBus[2]	= DataLength.ShortInteger * 2 ;

	ModBusDataLength = ModBus[2] + 3;

	return ModBusDataLength;
}

unsigned short ModBusFunction05(unsigned char *Query,unsigned char *ModBus)
{

	union unionShortInteger DataAddress;
	union unionShortInteger DataLength;
	unsigned int Index,CoilBit;
	signed short i;
	unsigned short ModBusDataLength;

	for(i=0;i<7;i++)
		{
			ModBus[i] = Query[i];
		}
	//
	// Data Address
	//
	DataAddress.Bytes.Byte0 = Query[2];			// Data Address High Byte
	DataAddress.Bytes.Byte1 = Query[3];			// Data Address Low  Byte

	//
	// Data Length
	//
	DataLength.Bytes.Byte0 = Query[4];
	DataLength.Bytes.Byte1 = Query[5];

	Index = DataAddress.ShortInteger / 32;

	//
	// Find Coil Position On The Coil Char
	//
	i = DataAddress.ShortInteger % i;

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

	ModBusDataLength = 6;

	return ModBusDataLength;
}

unsigned short ModBusFunction06(unsigned char *Query,unsigned char *ModBus)
{
	union unionShortInteger DataAddress;
	union unionShortInteger DataLength;

	unsigned short ModBusDataLength;
	unsigned int i;

	for(i=0;i<7;i++)
		{
			ModBus[i] = Query[i];
		}
	//
	// Data Address
	//
	DataAddress.Bytes.Byte0 = Query[2];			// Data Address High Byte
	DataAddress.Bytes.Byte1 = Query[3];			// Data Address Low  Byte

	//
	// Data Length
	//
	DataLength.Bytes.Byte0 = Query[4];
	DataLength.Bytes.Byte1 = Query[5];

	DataAddress.ShortInteger *= 2;

	Registers.Holding[DataAddress.ShortInteger + 1 ] = DataLength.Bytes.Byte0 ;
	Registers.Holding[DataAddress.ShortInteger + 0 ] = DataLength.Bytes.Byte1 ;

	AddDataList(1, DataAddress.ShortInteger, 2, 0x80);

	ModBusDataLength = 6;
	return ModBusDataLength;
}

unsigned short ModBusFunction0F(unsigned char *Query,unsigned char *ModBus)
{
	union unionShortInteger DataAddress;
	union unionShortInteger DataLength;
	unsigned short CoilArrayIndex,StartCoilNo;
	unsigned int CoilNoInDataByte=0;
	unsigned int CoilByte,CoilBit;
	unsigned short  i,j ;


	signed char ByteCounter=0;

	unsigned short ModBusDataLength;

	for(i=0;i<7;i++)
		{
			ModBus[i] = Query[i];
		}
	//
	// Data Address
	//
	DataAddress.Bytes.Byte0 = Query[2];			// Data Address High Byte
	DataAddress.Bytes.Byte1 = Query[3];			// Data Address Low  Byte

	//
	// Data Length
	//
	DataLength.Bytes.Byte0 = Query[4];
	DataLength.Bytes.Byte1 = Query[5];

	//
	// <SLAVE ADDRESS><FUNCTION><COIL ADDRESS HI><COIL ADDRESS LO><QUANTITY OF COIL HI><QUANTITY OF COIL LO><BYTE COUNT><FORCE DATA HI><FORCE DATA LO>
	//	0.   Slave Address
	//  1.   Function (0x0F) Force Multiple Coil
	//  2..3.Coil Address (First Coil Position to be affected)
	//  4..5.Total Coil Count to be affected
	//  6.   Data Count
	//  7..  Force Coil Bits Data

	StartCoilNo = DataAddress.ShortInteger % 32;
	CoilArrayIndex  = DataAddress.ShortInteger  / 32 ;
	CoilByte = Query[7 + ByteCounter];

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

	ModBusDataLength = 6;
	return ModBusDataLength;
}

unsigned short ModBusFunction10(unsigned char *Query,unsigned char *ModBus)
{
	union unionShortInteger DataAddress;
	union unionShortInteger DataLength;
	//unsigned short CharCount;
	signed short  i,j ;
	unsigned short ModBusDataLength;

	//
	// Data Address
	//
	DataAddress.Bytes.Byte0 = Query[2];			// Data Address High Byte
	DataAddress.Bytes.Byte1 = Query[3];			// Data Address Low  Byte
	//
	// Data Length
	//
	DataLength.Bytes.Byte0 = Query[4];
	DataLength.Bytes.Byte1 = Query[5];

	for(i=0;i<7;i++)
		{
			ModBus[i] = Query[i];
		}

	DataAddress.ShortInteger *= 2;

	DataLength.ShortInteger *= 2;

	//CharCount = Query[6];

	for(j=(DataLength.ShortInteger/2)-1;j>=0;j--)
		{
			Registers.Holding[DataAddress.ShortInteger + 1 + (j*2)] = Query[7 + (j*2)     ] ;
			Registers.Holding[DataAddress.ShortInteger + 0 + (j*2)] = Query[7 + (j*2) + 1 ] ;
		}
	AddDataList(1, DataAddress.ShortInteger, DataLength.ShortInteger, 0x80);

	ModBusDataLength = 6;
	return ModBusDataLength;
}

unsigned short ModBusCrcCheck( unsigned char *Query)
{
	union unionShortInteger crc16;
	unsigned short ModBusDataLength = 0;
	switch(Query[1])
			{
				case MDB_FNC_CR:
				case MDB_FNC_IS:
				case MDB_FNC_HR:
				case MDB_FNC_HR_R:
				case MDB_FNC_HRA:
				case MDB_FNC_SR:
				case MDB_FNC_SR_R:
				case MDB_FNC_SRA:
										//
										//<Slave Address><Function><Address Hi><Address Lo><Data Length Hi><Data Length Hi >
										//
				case MDB_FNC_FSC:
										//
										//<Slave Address><Function><Coil Address Hi><Coil Address Lo><Force Data Hi><Force Data Lo>
										//
				case MDB_FNC_PSR:
										//
										//<Slave Address><Function><Coil Address Hi><Coil Address Lo><Preset Data Hi><Preset Data Lo>
										//
										ModBusDataLength = 6;
										break;

				case MDB_FNC_FPC:
										//
										//<Slave Address><Function 0x0F><Coil Address Hi><Coil Address Lo><Quantity of Coils Hi><Quantity of Coils Lo>
										//			<Byte Count> <Byte Hi><Byte Lo> <Byte Hi> <Byte Lo> ...

				case MDB_FNC_PMR_R:
				case MDB_FNC_PMR:
				case MDB_FNC_SMR_R:
				case MDB_FNC_SMR:
										//
										//<Slave Address><Function 0x10><Starting Address Hi><Starting Address Lo><No. of Registers Hi><No. of Registers Lo>
										//			<Byte Count> <Byte Hi> <Byte Lo> <Byte Hi> <Byte Lo> ...

										ModBusDataLength = 7 + Query[6];
										break;
				case MDB_FNC_RLC:
										ModBusDataLength = 7;
										break;

			}

		if(!ModBusDataLength) return 0;

		crc16.ShortInteger = ModBusCrc(Query,0,ModBusDataLength);

		if((Query[ModBusDataLength] !=  crc16.Bytes.Byte0) || (Query[ModBusDataLength + 1 ] !=  crc16.Bytes.Byte1)  )
			{
				return 0;
			}

		return 1;
}


unsigned short ModBusCommunication( unsigned char *Query,unsigned char *ModBus,unsigned char CheckCrc)
{
	unsigned short ModBusDataLength = 0;
	union unionShortInteger crc16;
	static unsigned char OnlineStatus;

	if ( (Query[0] != *Plc.SlaveAddress) && (Query[0] != 0)  ) return 0;
 
	OnlineStatus = !OnlineStatus;

	//
	// Crc Check
	// 
	if(CheckCrc)
		{
			if (!ModBusCrcCheck(Query)) return 0;
		}
	//
	// ModBus Function
	//
	switch(Query[1])
		{
			case MDB_FNC_CR:
					ModBusDataLength =  ModBusFunction01(Query,ModBus);
				break;
						
			case MDB_FNC_IS:
					ModBusDataLength =  ModBusFunction02(Query,ModBus);
				break;


			case MDB_FNC_HR:
					ModBusDataLength =  ModBusFunction03(Query,ModBus);
				break;

			case MDB_FNC_SR:
					ModBusDataLength =  ModBusFunction04(Query,ModBus);
				break;


			case  MDB_FNC_FSC:
					ModBusDataLength =  ModBusFunction05(Query,ModBus);
				break;

			case MDB_FNC_FPC:
							ModBusDataLength = ModBusFunction0F(Query,ModBus);
						break;

			case MDB_FNC_PSR:
					ModBusDataLength =  ModBusFunction06(Query,ModBus);
				break;

			case MDB_FNC_PMR:
					ModBusDataLength =  ModBusFunction10(Query,ModBus);
				break;
				
		}

	crc16.ShortInteger = ModBusCrc(ModBus,0, ModBusDataLength);

	ModBus[ModBusDataLength + 0] = crc16.Bytes.Byte0;
	ModBus[ModBusDataLength + 1] = crc16.Bytes.Byte1;
	
	
	return ModBusDataLength + 2;
};


