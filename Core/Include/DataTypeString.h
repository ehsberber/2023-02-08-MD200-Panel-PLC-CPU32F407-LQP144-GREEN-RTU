/*
 * DataTypeString.h
 *
 *  Created on: Aug 4, 2022
 *      Author: Sezgin Berber
 */

#ifndef INCLUDE_DATATYPESTRING_H_
#define INCLUDE_DATATYPESTRING_H_






		typedef enum
		{
			StringRemoveOptionNone 			= 0x00,
			StringRemoveOptionEnd 			= 0x10,
			StringRemoveOptionStart 		= 0x20,
			StringRemoveOptionStartEnd 	= 0x30
		}enumSTRINGREMOVEOPTION;

	typedef enum
		{
			StringMidOptionNone 		= 0x00,
			StringMidOptionEnd 			= 0x10,
			StringMidOptionStart 		= 0x20,
			StringMidOptionStartEnd = 0x30
		}enumSTRINGMIDOPTION;

	typedef enum
		{
			StringMakeOptionNone = 0x00,
			StringMakeOptionEnd = 0x10
		}enumSTRINGMAKEOPTION;

	typedef struct
		{
			unsigned char *String;
			unsigned long DataAddress;
			signed short StartPos;
			signed short EndPos;
			signed short LengthOfString;

			signed short Result;

			unsigned char Option;
		} strcSTRINGMID;


	typedef struct
		{
			unsigned char *DataRegister;
			unsigned long DataAddress;
			unsigned short Length;
		} strcSTRINGMAKE;

	typedef struct
		{
			unsigned char *String;
			signed short LengthOfString;

			unsigned char *FindString;
			signed short LengthOfFindString;

			unsigned char *ReplaceString;
			signed short LengthOfReplaceString;

			signed short StartPos;
			signed short EndPos;

			signed short Result;
		} strcSTRING_PARAMETERS;

#endif /* INCLUDE_DATATYPESTRING_H_ */
