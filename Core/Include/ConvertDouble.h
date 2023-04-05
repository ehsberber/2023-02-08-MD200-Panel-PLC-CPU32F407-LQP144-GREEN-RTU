#include "DataType.h"

//unsigned char dbltostr1(double dblNumber,unsigned char Length,unsigned char DecimalLength,unsigned char Format,unsigned char *dblString );
unsigned char dbltostr(double dblNumber,strcDATAFORMAT *DataFormat,unsigned char *dblString );
unsigned char dbltoBCD(double dblValue,unsigned char Length, unsigned char *StringArray );
