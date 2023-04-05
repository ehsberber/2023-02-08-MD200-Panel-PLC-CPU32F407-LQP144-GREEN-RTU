#include "stdlib.h"
#include "DataType.h"
#include "Math.h"

float floatIEEE754(unsigned int intValue)
{
	float fltValue;
	double total=0;
	signed char sign=1;
	signed int exponent;
	unsigned int mantissa, c;
	signed int power=-1;
	unsigned char i;
	
	if (intValue & 0x80000000) sign = -1;
	exponent = (intValue & 0x7F800000) >> 23;
	exponent -= 127;
	//
	// Mantissa
	//
	mantissa = (intValue &  0x007FFFFF);
	for (i = 0; i < 23; i++ )
	 {
			c = (mantissa >> (22-i)) & 0x01;
			total +=  c *  pow( 2.0, power );
			power--;
	 }
	 total += 1.0;

	fltValue = sign *   pow( 2.0, exponent ) * total;
 
	return fltValue;
}

float floatIEEE754R(unsigned int intValueR)
{
	float fltValue;
	double total=0;
	signed char sign=1;
	signed int exponent;
	unsigned int mantissa, c;
	signed int power=-1;
	unsigned char i;
	unsigned int intValue;

	union unionInteger uintValueR;
	union unionInteger uintValue;

	uintValueR.Integer = intValueR;
	uintValue.Bytes.Byte0 = uintValueR.Bytes.Byte3;
	uintValue.Bytes.Byte1 = uintValueR.Bytes.Byte2;
	uintValue.Bytes.Byte2 = uintValueR.Bytes.Byte1;
	uintValue.Bytes.Byte3 = uintValueR.Bytes.Byte0;

	intValue = uintValue.Integer;

	if (intValue & 0x80000000) sign = -1;
	exponent = (intValue & 0x7F800000) >> 23;
	exponent -= 127;
	//
	// Mantissa
	//
	mantissa = (intValue &  0x007FFFFF);
	for (i = 0; i < 23; i++ )
	 {
			c = (mantissa >> (22-i)) & 0x01;
			total +=  c *  pow( 2.0, power );
			power--;
	 }
	 total += 1.0;

	fltValue = sign *   pow( 2.0, exponent ) * total;

	return fltValue;
}

union f {
  float           f;            /* Floating-point value */
  unsigned long   ul;           /* Unsigned long value */
};

float floatIEEE754_2(unsigned int intValue)
{
	float fltValue;
	fltValue = *(float *)&intValue;
	return fltValue;
}
