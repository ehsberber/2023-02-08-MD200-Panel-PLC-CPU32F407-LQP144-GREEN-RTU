/*
 * ConvertString.h
 *
 *  Created on: Jul 19, 2022
 *      Author: Sezgin Berber
 */

#ifndef APPLICATION_USER_HEADER_CONVERTSTRING_H_
#define APPLICATION_USER_HEADER_CONVERTSTRING_H_
unsigned long int ConvertStringToLong(unsigned char *ConvertString,unsigned int LenghtOfString);
unsigned char ctobcd(unsigned char ConvertChar);
unsigned char bcdtod(unsigned char bcd);
signed long int ConvertStringToSignedLong(unsigned char *ConvertString,unsigned int LenghtOfString);
unsigned long int ConvertAlphaStringToLong(unsigned char *ConvertString,unsigned int LenghtOfString);
signed long int ConvertAlphaStringToSignedLong(unsigned char *ConvertString,unsigned char LenghtOfString);
double ConvertAlphaStringToDouble(unsigned char *ConvertString,unsigned char LenghtOfString);
unsigned char ConvertHexStringToCharArray(unsigned char *HexString,signed char LengthOfString,unsigned char *CharArray);
unsigned char ConvertHexStringToCharArrayReverse(unsigned char *HexString,signed char LengthOfString,unsigned char *CharArray);
unsigned char HexByte(unsigned char HexChar);
unsigned char ConvertConstHexStringToCharArray(const char *HexString,unsigned char *CharArray);
unsigned char ConvertConstHexStringToReverseCharArray(const char *HexString,unsigned char *CharArray);
unsigned char ConvertCharArrayToHexString(unsigned char *CharArray,	signed char LengthOfString,unsigned char *HexString);
unsigned char ConvertCharArrayToString(unsigned char *CharArray,	unsigned char LengthOfString,unsigned char CharSize, unsigned char *String);
unsigned long ConvertHexStringToLong(unsigned char *HexString,unsigned char DataLength);
unsigned long int ConvertHexORAlphaStringToLong(unsigned char *ConvertString,unsigned int LenghtOfString);
double ConvertHexORAlphaStringToDouble(unsigned char *ConvertString,unsigned int LenghtOfString);
signed long int ConvertHexORAlphaStringToSignedLong(unsigned char *ConvertString,unsigned int LenghtOfString);
unsigned long ConvertHexStringToLongMid(unsigned char *HexString,unsigned char StartPosition,unsigned char DataLength);



#endif /* APPLICATION_USER_HEADER_CONVERTSTRING_H_ */
