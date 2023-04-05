/*
 * DataTypeGsm.h
 *
 *  Created on: Feb 3, 2023
 *      Author: Sezgin Berber
 */

#ifndef INCLUDE_DATATYPEGSM_H_
#define INCLUDE_DATATYPEGSM_H_

	typedef enum
		{	stateNone = 0,
			stateInitialize = 1,
			stateSmsSend = 2,
			stateSmsRead = 3,
			stateSmsDelete = 4,
			stateGprsConnection = 5,
		}enumModemStates;

	typedef enum
		{
			cmdAT = 0,
			cmdATE = 1,
			cmdCMGF = 2,
			smdCMGS = 3,
			smdCMGR = 4,
			smdCMGD = 5,
		}enumModemCommandNo;

	union unionModemResponse
		{
			struct
				{
					unsigned short Ok:1;
					unsigned short Error:1;
					unsigned short Initialize:1;
					unsigned short Connected:1;
					unsigned short DataReady:1;
					unsigned short IdleResponseExecuted:1;
					unsigned short Response:1;
					unsigned short SmsCommand:1;
					unsigned short PowerOff:1;
				}ResponseState;

			unsigned short ResponseStates;
		};

	typedef struct
			{
				enumModemStates *Status;
				enumModemCommandNo *CommandNo;
				union unionModemResponse *Response;
				unsigned char *Command;
				unsigned short *CommandCounter;
				unsigned short *InitializeState;

			}strcMODEM;

	typedef struct
		{
			unsigned short *NewSmsNo;
			unsigned short *ActiveSmsNo;
			unsigned short *SendStatusEnable;
			unsigned short *SendStatus;
			unsigned short *ActiveReplyGsm;
			unsigned short *ReplyGsm[16];
		}strcSMS;

	typedef struct
		{
			strcSMS    Sms;
			strcMODEM  Modem;
		}strcGSM;

#endif /* INCLUDE_DATATYPEGSM_H_ */
