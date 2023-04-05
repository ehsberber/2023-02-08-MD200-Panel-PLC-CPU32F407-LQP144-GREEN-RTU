/*
 * ConvertInteger.h
 *
 *  Created on: Jul 19, 2022
 *      Author: Sezgin Berber
 */

#ifndef APPLICATION_USER_HEADER_CONVERTINTEGER_H_
#define APPLICATION_USER_HEADER_CONVERTINTEGER_H_

unsigned char sltostr(signed long int  Number,unsigned char Length,unsigned char FillLeft, unsigned char *ReturnString );
unsigned char ltostr(unsigned long int  Number,unsigned char Length,unsigned char FillLeft,unsigned char *R_STRING );
void chartohex(unsigned char value,unsigned char *HexString);
void chartohex2(unsigned char value,unsigned char *HexString);
unsigned char charvalue(unsigned char value);
void ltohex(unsigned int  *Number,unsigned char Length,unsigned char *ReturnString );
void ltochararray(unsigned int *Number,unsigned char Length,unsigned char *ReturnString );
void sltochararray(signed int *Number,unsigned char Length,unsigned char *ReturnString );
void ltohex0x(unsigned int *Number,unsigned char Length,unsigned char *ReturnString );
void CharHexByte(unsigned char Character, unsigned char *HexByte1,unsigned char *HexByte2);
unsigned char hexnumbertochar(unsigned char HiByteHex, unsigned char LowByteHex);
unsigned int shortflip(unsigned int intValue);



#endif /* APPLICATION_USER_HEADER_CONVERTINTEGER_H_ */
