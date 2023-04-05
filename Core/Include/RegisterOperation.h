
void IntToArray(unsigned char *Data_Register,unsigned short DataStartPosition,unsigned int Value);
void IntAddArray(unsigned char *Data_Register,unsigned short DataStartPosition,unsigned int Value);
void signedIntToArray(unsigned char *Data_Register,unsigned short DataStartPosition,signed int Value);
short getRegisterShort(unsigned char RegisterType,unsigned short Address);
int getRegisterInt(unsigned char RegisterType,unsigned short Address );
unsigned char getRegisterChar(unsigned char RegisterType,unsigned short Address);
void writeRegisterChar(unsigned int RegisterType,unsigned int Address, unsigned char Value);
void writeRegisterShort(unsigned char RegisterType,unsigned short Address, unsigned short ShortValue);
void writeRegisterInt(unsigned char RegisterType,unsigned short Address, unsigned int intValue);
void AndRegister(unsigned char RegisterType,unsigned short Address, unsigned short AndValue);
void OrRegister(unsigned char RegisterType,unsigned short Address, unsigned short OrValue);
unsigned char DataTypeSize(unsigned char DataType);
void wordflip(enumREGISTERTYPE Register, unsigned int Address , unsigned char DataSize);
void byteflip(enumREGISTERTYPE Register, unsigned int Address , unsigned char DataSize);
//unsigned int *IntOrArray(unsigned char *Data_Register,unsigned short DataStartPosition,unsigned int Value);
void IntOrArray(unsigned char *Data_Register,unsigned short DataStartPosition,unsigned int Value);
void ShortOrArray(unsigned char *Data_Register,unsigned short DataStartPosition,unsigned short Value);
void ShortToArray(unsigned char *Data_Register,unsigned short DataStartPosition,unsigned short Value);
unsigned short ShortFromArray(unsigned char *Data_Register,unsigned short DataStartPosition);
unsigned short ShortFromConstArray(const unsigned char *DataRegister,unsigned int DataStartPosition);
signed short signedShortFromArray(unsigned char *DataRegister,unsigned int DataStartPosition);
signed short signedShortFromArrayReverse(unsigned char *DataRegister,unsigned int DataStartPosition);
unsigned int IntFromArray(unsigned char *Data_Register,unsigned short DataStartPosition);
unsigned int IntFromConstArray(const unsigned char *DataRegister,unsigned int DataStartPosition);
signed int signedIntFromArray(unsigned char *Data_Register,unsigned short DataStartPosition);
unsigned int IntFromArrayReverse(unsigned char *DataRegister,unsigned short DataStartPosition);
unsigned int ShortFromArrayReverse(unsigned char *DataRegister,unsigned short DataStartPosition);
signed int signedIntFromArrayReverse(unsigned char *DataRegister,unsigned short DataStartPosition);
signed int signedIntFromConstArray(unsigned char const *DataRegister,unsigned int DataStartPosition);
void ShortAndArray(unsigned char *Data_Register,unsigned short DataStartPosition,unsigned short Value);
void IntAndArray(unsigned char *Data_Register,unsigned short DataStartPosition,unsigned int Value);
void RegisterDataGet(unsigned char *Data_Register,unsigned short DataStartPosition,unsigned char *Data,signed short DataSize);
unsigned short RegisterDataGetEndChar(unsigned char *DataRegister, unsigned short DataStartPosition, unsigned char *Data, signed short DataSize, signed short EndChar);
void RegisterDataUpdate(unsigned char *Data_Register,unsigned short DataStartPosition,unsigned char *Data,unsigned char DataSize);
void RegisterDataUpdateWithEndChar(unsigned char *Data_Register,unsigned short DataStartPosition,unsigned char *Data,unsigned char DataSize);
void RegisterConstDataUpdate(unsigned char *Data_Register,unsigned short DataStartPosition,const char *Data,unsigned char DataSize);
void RegisterConstDataUpdateWithEndChar(unsigned char *DataRegister,unsigned short DataStartPosition,const char *Data,unsigned char DataSize);

void RegisterConstShortDataUpdate(unsigned char *DataRegister,unsigned short DataStartPosition,const char *Data,unsigned char DataSize);
void RegisterConstShortDataUpdateWithEndChar(unsigned char *DataRegister,unsigned short DataStartPosition,const char *Data,unsigned char DataSize);

void fillRegisterToArray(unsigned char RegisterType,unsigned short Address,unsigned char *FillData, unsigned char DataLength);
void fillRegisterToArrayReverse(unsigned char RegisterType,unsigned short Address,unsigned char *FillData, unsigned char DataLength);
void fillArrayToRegister(unsigned char RegisterType,unsigned short Address,unsigned char *FillData, unsigned char DataLength);

unsigned char *GetRegister1(enumREGISTERTYPE Register);
unsigned char *GetRegisterWithAddress( enumREGISTERTYPE Register, unsigned long Address);

unsigned char  BitsCount(unsigned int Value);
signed char FirstSetBitPos(unsigned int Value);





