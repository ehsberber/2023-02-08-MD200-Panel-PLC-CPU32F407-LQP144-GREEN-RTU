#include "Registers.h"
#include "Eeprom.h"
#include "MC25LCxxx.h"
#include "Constant.h"

#define I2C_EEPROM_DELAY_CONSTANT  0x00002000
#define SPI_EEPROM_DELAY_CONSTANT  0x000FFFFF


//#define SPI_EEPROM_00_CS_PORT		GPIOG
//#define SPI_EEPROM_00_CS_PORT_PIN	GPIO_PIN_10
//
//#define SPI_EEPROM_01_CS_PORT		GPIOG
//#define SPI_EEPROM_01_CS_PORT_PIN	GPIO_PIN_11

extern void WatchDogFeed(void);

//extern unsigned char *HoldingRegister;
//extern unsigned char *CoilRegister;

extern strcREGISTERS  Registers; 

void MC25LCxxx_CS(unsigned char EEPROM_NO, unsigned char CS_HIGH_LOW )
{
	static char DelayTime=5;
	if (SPI_CS_SOFT)
		{
			if (CS_HIGH_LOW == 0)
				{
					switch(EEPROM_NO)
					{
						case EEPROM_NO_00:

							HAL_GPIO_WritePin( SPI_EEPROM_00_CS_PORT, SPI_EEPROM_00_CS_PORT_PIN ,  GPIO_PIN_RESET );
							break;
						case EEPROM_NO_01:
							HAL_GPIO_WritePin( SPI_EEPROM_01_CS_PORT, SPI_EEPROM_01_CS_PORT_PIN ,  GPIO_PIN_RESET );

							break;
					}
					//
					// Delay After Enable
					//
					HAL_Delay(DelayTime);
				}
			else
				{
					//
					//Delay Before Disable
					//
					HAL_Delay(DelayTime);
					
					switch(EEPROM_NO)
						{
							case EEPROM_NO_00:

								HAL_GPIO_WritePin( SPI_EEPROM_00_CS_PORT, SPI_EEPROM_00_CS_PORT_PIN ,  GPIO_PIN_SET );
								break;

							case EEPROM_NO_01:
								HAL_GPIO_WritePin( SPI_EEPROM_01_CS_PORT, SPI_EEPROM_01_CS_PORT_PIN ,  GPIO_PIN_SET );
								break;
						}
					HAL_Delay(DelayTime);
				}
		}
}

void MC25LCxxx_Init(SPI_HandleTypeDef* SPIx)
{
	MC25LCxxx_CS(EEPROM_NO_00, 1 );
	
	//MC25LCxxx_CS(EEPROM_NO_01, 1 );

	MC25LCxxx_ReleaseDeepPowerDownMode(SPIx, EEPROM_NO_00);
	
	MC25LCxxx_ReadStatus(SPIx, EEPROM_NO_00);
	
	MC25LCxxx_WriteEnable(SPIx, EEPROM_NO_00,ENABLE);

}

unsigned char MC25LCxxx_ReleaseDeepPowerDownMode(SPI_HandleTypeDef* SPIx,unsigned char EEPROM_NO)
	{
 
		unsigned char SendByte = MC25LCxxx_SPI_RDID, ReceivedByte=0xA5;

		//
		// ENABLE CHIP SELECT
		//
		MC25LCxxx_CS(EEPROM_NO, 0 );
			
		HAL_SPI_Transmit(SPIx , &SendByte, 1,100) ;
		//HAL_Delay(2);
 
		HAL_SPI_Receive(SPIx , &ReceivedByte, 1,100) ;
		HAL_SPI_Receive(SPIx , &ReceivedByte, 1,100) ;	
		HAL_SPI_Receive(SPIx , &ReceivedByte, 1,100) ;	// This Byte is manifacturer Id
		//HAL_Delay(100);
		//
		// DISABLE CHIP SELECT
		//
		MC25LCxxx_CS(EEPROM_NO, 1 );

		//HAL_Delay(1000);
		
		return ReceivedByte;
	}
	

unsigned char MC25LCxxx_ReadStatus(SPI_HandleTypeDef* SPIx, unsigned char EEPROM_NO)
{
	unsigned char SendByte=MC25LCxxx_SPI_RDSR, ReceivedData;

	//
	// ENABLE CHIP SELECT
	//
	MC25LCxxx_CS(EEPROM_NO, 0 );
 
	HAL_SPI_Transmit(SPIx , &SendByte, 1, 100) ;
		
	HAL_SPI_Receive(SPIx , &ReceivedData, 1 , 100) ;

	//
	// DISABLE CHIP SELECT
	//
	MC25LCxxx_CS(EEPROM_NO, 1 );
	
	return ReceivedData;
		 
}


void  MC25LCxxx_WriteEnable(SPI_HandleTypeDef* SPIx, unsigned char EEPROM_NO, unsigned char Enable)
{
	unsigned char SendByte;
	
	//
	// ENABLE CHIP SELECT
	//
	MC25LCxxx_CS(EEPROM_NO, 0 );
	HAL_Delay(5);
	//
	// SEND WRITE ENABLE OR DISABLE COMMAND
	//
	if(Enable)
		{
			SendByte = MC25LCxxx_SPI_WREN;
		}
	else
		{
			SendByte = MC25LCxxx_SPI_WRDI;
		}	

		
	HAL_SPI_Transmit(SPIx , &SendByte, 1, 100) ;
	
	HAL_Delay(5);
	//
	// ENABLE CHIP SELECT
	//
	MC25LCxxx_CS(EEPROM_NO, 1 );
}


unsigned char MC25LCxxx_ReadData(SPI_HandleTypeDef* SPIx, unsigned char EEPROM_NO, unsigned int Address, unsigned short ReadByteCount, unsigned char *ReadByteArray )
{
 
	unsigned char SendByte;
	HAL_StatusTypeDef ReadStatus;
	//
	// ENABLE CHIP SELECT
	//
	MC25LCxxx_CS(EEPROM_NO, 0 );
	//
	HAL_Delay(1);
	//
	// Send Read Command
	// 
	SendByte = MC25LCxxx_SPI_READ; 
	
	HAL_SPI_Transmit(SPIx , &SendByte, 1, 1000) ;
	
	//
	// Send Address Bytes
	//
	SendByte =  Address >> 8;			

	HAL_SPI_Transmit(SPIx , &SendByte, 1, 1000) ; // High Byte Of Address

	SendByte =  Address & 0x00FF;	
	
	HAL_SPI_Transmit(SPIx , &SendByte, 1, 1000) ; // Low Byte Of Address

	ReadStatus = HAL_SPI_Receive(SPIx , ReadByteArray , ReadByteCount , 10000) ;

	//
	// DISABLE CHIP SELECT
	//
	HAL_Delay(1);
	MC25LCxxx_CS(EEPROM_NO, 1 );
	
	HAL_Delay(1);	
	
	return ReadStatus;
}

unsigned char MC25LCxxx_Read(SPI_HandleTypeDef* SPIx, unsigned char EEPROM_NO, unsigned char *ReadByteArray )
{
	unsigned short PacketNumber = 0;
	unsigned short Address=0;
	unsigned char SendByte;

	
	for (PacketNumber = 0; PacketNumber< HR_DATA_PACKET_COUNT; PacketNumber++)			//
		{
 
			//
			// BU KISIM MC25LCxxx_ReadData FONKSIYONU ILE DEGISTIRILEBILIR
			//
			
			//
			// ENABLE CHIP SELECT
			//
			MC25LCxxx_CS(EEPROM_NO, 0 );
			//
			//HAL_Delay(10);
			//
			// Send Read Command
			// 
			SendByte = MC25LCxxx_SPI_READ; 
		
 
			
			HAL_SPI_Transmit(SPIx , &SendByte, 1, 1000) ;
			
			// 
			// Address
			//
			Address = PacketNumber * HR_DATA_PACKET_SIZE;
			 
			//
			// Send Address Bytes
			//
			SendByte =  Address >> 8;			

			HAL_SPI_Transmit(SPIx , &SendByte, 1, 1000) ; // High Byte Of Address
 
			SendByte =  Address & 0x00FF;	
			
			HAL_SPI_Transmit(SPIx , &SendByte, 1, 1000) ; // Low Byte Of Address
 
			HAL_SPI_Receive(SPIx , &ReadByteArray[(PacketNumber * HR_DATA_PACKET_SIZE)], HR_DATA_PACKET_SIZE , 10000) ;

			//
			// DISABLE CHIP SELECT
			//
			//HAL_Delay(10);
			MC25LCxxx_CS(EEPROM_NO, 1 );
			
			//HAL_Delay(10);
			
		}
	return 1;
	
}
 


void MC25LCxxx_WriteBytes(SPI_HandleTypeDef* SPIx, unsigned char *WriteByteArray, unsigned int EEPromAddress, unsigned int WriteByteCount )
{
 
		unsigned char SendByte;
		
		SendByte = MC25LCxxx_SPI_WRITE;
		//
		// Send Data Write Command
		//
		HAL_SPI_Transmit(SPIx , &SendByte, 1, 100);
 
		// 
		// Address
		//
 
		//
		// Send Address Bytes
		//
		SendByte =  EEPromAddress >> 8;			
		HAL_SPI_Transmit(SPIx , &SendByte, 1, 100) ; // High Byte Of Address
		
		SendByte =  EEPromAddress & 0x00FF;	
		HAL_SPI_Transmit(SPIx , &SendByte, 1, 100) ; // Low Byte Of Address
		//
		// Send Chars	
		//
		HAL_SPI_Transmit(SPIx , WriteByteArray  , WriteByteCount , 100) ;
		 
}

void MC25LCxxx_WriteList(SPI_HandleTypeDef * SPIx, unsigned char EEPROM_NO, unsigned char *ParameterList,unsigned char *ParameterDataPosition)
{
	unsigned short ParameterCount;
	unsigned int EEPromAddress;
	unsigned char WriteStatus;
 
	if (ParameterList[0] & 0x80)
		{
			while (ParameterList[0] & 0x7F)
				{
					ParameterCount = ParameterList[0] & 0x7F;

					//
					// ENABLE WRITE PROCESS
					//
					MC25LCxxx_WriteEnable(SPIx, EEPROM_NO_00,ENABLE);
					
					
					ParameterList[0]--;	
					
					//
					// WRITE EEPROM ADDRES
					//
					EEPromAddress =  *(unsigned short *)&ParameterList[(3*(ParameterCount-1)) + 1] ; // (ParameterList[(3*(ParameterCount-1)) + 1] * 0x100) + ParameterList[ (3*(ParameterCount-1)) + 2]; //AddressHighByte << 8 | AddressLowByte;

					//
					// ENABLE CHIP SELECT
					//
					MC25LCxxx_CS(EEPROM_NO, 0 );
					
					HAL_Delay(5);
					MC25LCxxx_WriteBytes(SPIx, &Registers.Holding[EEPromAddress], EEPromAddress, ParameterList[(3*(ParameterCount-1)) + 3] );
					
					//
					// DISABLE CHIP SELECT
					//
					HAL_Delay(5);
					MC25LCxxx_CS(EEPROM_NO, 1 );
				 
					HAL_Delay(5);
					
					WriteStatus = MC25LCxxx_ReadStatus(SPIx, EEPROM_NO);
					
					while(WriteStatus & MC25LCxxx_STATUS_WIP)	
						{
							WriteStatus = MC25LCxxx_ReadStatus(SPIx, EEPROM_NO);
						}
				}

			ParameterList[0] = 0x00;	
			*ParameterDataPosition = 0;
			
			//for (waitCounter = 0; waitCounter < SPI_EEPROM_DELAY_CONSTANT; waitCounter++)	WatchDogFeed();	
		}
}

void MC25LCxxx_Write(SPI_HandleTypeDef * SPIx, unsigned char EEPROM_NO)
{
	unsigned short PacketNumber=0;
 
	unsigned char WriteStatus;
	
	while(PacketNumber < HR_DATA_PACKET_COUNT)				// HR_DATA_PACKET_COUNT
		{
			//
			//	ENABLE CHIP SELECT
			//
			
			MC25LCxxx_WriteEnable(SPIx, EEPROM_NO_00,ENABLE);	
			//
			// WRITE DATA
			//
	
			//
			// ENABLE CHIP SELECT
			//
			MC25LCxxx_CS(EEPROM_NO, 0 );
			HAL_Delay(5);
 
			MC25LCxxx_WriteBytes(SPIx,  &Registers.Holding[PacketNumber * HR_DATA_PACKET_SIZE], PacketNumber * HR_DATA_PACKET_SIZE, HR_DATA_PACKET_SIZE);

			
			//
			// DISABLE CHIP SELECT
			//
			HAL_Delay(5);
			
			MC25LCxxx_CS(EEPROM_NO, 1 );
			
			HAL_Delay(5);
	
			WriteStatus = MC25LCxxx_ReadStatus(SPIx, EEPROM_NO);
			
			while(WriteStatus & MC25LCxxx_STATUS_WIP)	
				{
					WriteStatus = MC25LCxxx_ReadStatus(SPIx, EEPROM_NO);
				}

			
			PacketNumber++;
		}
}


unsigned short MC25LCxxx_WritePacket(SPI_HandleTypeDef * SPIx, unsigned char EEPROM_NO)
{
	static unsigned short PacketNumber=0;
 
	unsigned char WriteStatus;
	
	if (PacketNumber < HR_DATA_PACKET_COUNT)				// HR_DATA_PACKET_COUNT
		{
			//
			//	ENABLE CHIP SELECT
			//
			
			MC25LCxxx_WriteEnable(SPIx, EEPROM_NO_00,ENABLE);	
			//
			// WRITE DATA
			//
	
			//
			// ENABLE CHIP SELECT
			//
			MC25LCxxx_CS(EEPROM_NO, 0 );
			HAL_Delay(1);
 
			MC25LCxxx_WriteBytes(SPIx,  &Registers.Holding[PacketNumber * HR_DATA_PACKET_SIZE], PacketNumber * HR_DATA_PACKET_SIZE, HR_DATA_PACKET_SIZE);

			//
			// DISABLE CHIP SELECT
			//
			HAL_Delay(2);
			
			MC25LCxxx_CS(EEPROM_NO, 1 );
			
			HAL_Delay(1);
	
			WriteStatus = MC25LCxxx_ReadStatus(SPIx, EEPROM_NO);
			
			while(WriteStatus & MC25LCxxx_STATUS_WIP)	
				{
					WriteStatus = MC25LCxxx_ReadStatus(SPIx, EEPROM_NO);
				}
			PacketNumber++;
			 
		}
	else
		{	
			PacketNumber = 0;
		}
	
	return PacketNumber;
}



