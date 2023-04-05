/*
 * Protocol.h
 *
 *  Created on: Aug 3, 2022
 *      Author: Sezgin Berber
 */

#ifndef INCLUDE_PROTOCOL_H_
#define INCLUDE_PROTOCOL_H_

typedef struct
		{
			unsigned char 		QueryCrcCheck;
			enumREGISTERTYPE	QueryRegisterType;
			unsigned int 			QueryAddress;
			enumDATATYPE			QueryDataType;


			enumREGISTERTYPE	QueryLengthRegisterType;
			unsigned int 			QueryLengthAddress;
			enumDATATYPE			QueryLengthDataType;

			signed short			QueryLength;
			signed short 			EndChar;

			enumREGISTERTYPE 	ResponseRegisterType;
			unsigned int 			ResponseAddress;

			unsigned short 		ResponseDataLength;
			enumDATATYPE 			ResponseLengthDataType;

		}strcMODBUSDATA;

#endif


#endif /* INCLUDE_PROTOCOL_H_ */
