#include "MicroPeripheral.h"
#include "OneWire.h"


#define DS2482_STATUS_REGISTER_ADDRESS								0xF0
#define DS2482_READDATA_REGISTER_ADDRESS							0xE1
#define DS2482_CONFIG_REGISTER_ADDRESS								0xC3
#define DS2482_CHANNEL_SELECTION_REGISTER_ADDRESS					0xD2

#define DS2482_DEVICE_RESET											0xF0
#define DS2482_SET_READ_POINTER										0xE1
#define DS2482_WRITE_CONFIGURATION									0xD2
#define DS2482_ONEWIRE_RESET										0xB4
#define DS2482_ONEWIRE_BIT											0x87
#define DS2482_ONEWIRE_WRITE										0xA5
#define DS2482_ONEWIRE_READ											0x96
#define DS2482_ONEWIRE_TRIPLET										0x78
#define DS2482_CHANNEL_SELECT										0xC3

//
// STATUS REGISTER
//
#define DS2482_STATUS_DIR											0x80
#define DS2482_STATUS_TSB											0x40
#define	DS2482_STATUS_SBR											0x20
#define	DS2482_STATUS_RST											0x10
#define	DS2482_STATUS_LL											0x08
#define	DS2482_STATUS_SD											0x04
#define	DS2482_STATUS_PPD											0x02
#define	DS2482_STATUS_1WB											0x01

#define DS2482_CONFIG_APU											0x01
#define DS2482_CONFIG_SPU											0x04
#define DS2482_CONFIG_WS											0x08

unsigned char ds2482_setPointer(strcONEWIRELINE strcOneWireLine,unsigned char PointerValue);
unsigned char ds2482_owStatus(strcONEWIRELINE strcOneWireLine);
unsigned char ds2482_ConfigWrite(strcONEWIRELINE strcOneWireLine,unsigned char Config);
unsigned char ds2482_ConfigRead(strcONEWIRELINE strcOneWireLine);
unsigned char ds2482_owReset(strcONEWIRELINE strcOneWireLine);
unsigned char ds2482_owWrite(strcONEWIRELINE strcOneWireLine,unsigned char WriteByte);
unsigned char ds2482_owRead(strcONEWIRELINE strcOneWireLine);
unsigned char *ds2482_owReadBytes(strcONEWIRELINE strcOneWireLine, unsigned char *Data, unsigned char Length);
void ds2482_owTriplet(strcONEWIRELINE strcOneWireLine,unsigned char DirectionByte);
unsigned char ds2482_DeviceReset(strcONEWIRELINE strcOneWireLine);
unsigned char ds2482_WaitForBusy(strcONEWIRELINE strcOneWireLine);

