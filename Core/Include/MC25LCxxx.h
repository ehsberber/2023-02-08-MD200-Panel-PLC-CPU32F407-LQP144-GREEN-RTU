#include "MicroPeripheral.h"

#define MC25LCxxx_SPI_READ 		0x03 	//0000 0011 Read data from memory array beginning at selected address
#define MC25LCxxx_SPI_WRITE 	0x02  //0000 0010 Write data to memory array beginning at selected address
#define MC25LCxxx_SPI_WREN 		0x06	//0000 0110 Set the write enable latch (enable write operations)
#define MC25LCxxx_SPI_WRDI 		0x04	//0000 0100 Reset the write enable latch (disable write operations)
#define MC25LCxxx_SPI_RDSR 		0x05	//0000 0101 Read STATUS register
#define MC25LCxxx_SPI_WRSR 		0x01	//0000 0001 Write STATUS register
#define MC25LCxxx_SPI_PE 			0x42	//0100 0010 Page Erase – erase one page in memory array
#define MC25LCxxx_SPI_SE 			0xD8	//1101 1000 Sector Erase – erase one sector in memory array
#define MC25LCxxx_SPI_CE 			0xC7	//1100 0111 Chip Erase – erase all sectors in memory array
#define MC25LCxxx_SPI_RDID 		0xAB	//1010 1011 Release from Deep power-down and read electronic signature
#define MC25LCxxx_SPI_DPD 		0xB9	//1011 1001 Deep Power-Down mode

#define MC25LCxxx_STATUS_WPEN	0x80  //Read Write Array Address Write Protect Bit 1
#define MC25LCxxx_STATUS_BP1	0x08	//Read Write Array Address Write Protect Bit 1
#define MC25LCxxx_STATUS_BP0	0x04	//Read Write Array Address Write Protect Bit 0
#define MC25LCxxx_STATUS_WEL	0x02	//Read only Write Enable Latch
#define MC25LCxxx_STATUS_WIP	0x01	//Read only Write In Process



void MC25LCxxx_CS(unsigned char EEPROM_NO, unsigned char CS_HIGH_LOW );
void MC25LCxxx_Init(SPI_HandleTypeDef* SPIx);
unsigned char MC25LCxxx_ReadStatus(SPI_HandleTypeDef* SPIx, unsigned char EEPROM_NO);
void MC25LCxxx_WriteEnable(SPI_HandleTypeDef* SPIx, unsigned char EEPROM_NO, unsigned char Enable);
unsigned char MC25LCxxx_Read(SPI_HandleTypeDef* SPIx, unsigned char EEPROM_NO, unsigned char *ReadByteArray );
unsigned char MC25LCxxx_ReadData(SPI_HandleTypeDef* SPIx, unsigned char EEPROM_NO, unsigned int Address, unsigned short ReadByteCount, unsigned char *ReadByteArray );
void MC25LCxxx_Write(SPI_HandleTypeDef* SPIx, unsigned char EEPROM_NO);
unsigned short MC25LCxxx_WritePacket(SPI_HandleTypeDef* SPIx, unsigned char EEPROM_NO);
void MC25LCxxx_WriteList(SPI_HandleTypeDef* SPIx, unsigned char EEPROM_NO, unsigned char *ParameterList,unsigned char *ParameterDataPosition);
unsigned char MC25LCxxx_ReleaseDeepPowerDownMode(SPI_HandleTypeDef* SPIx,unsigned char EEPROM_NO);
void MC25LCxxx_WriteBytes(SPI_HandleTypeDef* SPIx, unsigned char *WriteByteArray, unsigned int EEPromAddress, unsigned int WriteByteCount );

