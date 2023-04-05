/*
 * Registers.h
 *
 *  Created on: Aug 3, 2022
 *      Author: Sezgin Berber
 */

#ifndef INCLUDE_REGISTERS_H_
#define INCLUDE_REGISTERS_H_
		#include "DefinitionCommon.h"
		#include "DataTypeGsm.h"
		#include "PlcDefinition.h"
		#include "TimerProcess.h"

		#include "Leds.h"

		union unionLeds
			{
				 struct
					{
						unsigned short Red:1;
						unsigned short Green:1;
						unsigned short Blue:1;
					}LED;

				unsigned short LedsAll;
			};

		//#define	PI	3.1416
		union unionDO
					{
						 struct
							{
								unsigned short No00:1;
								unsigned short No01:1;

							}DO;
						unsigned int DOs;
					};

				union unionDI
					{
						 struct
							{
								unsigned short ESB1:1;
								unsigned short ESB2:1;
								unsigned short ESB3:1;
								unsigned short ESB4:1;
								unsigned short Pump1Ignition:1;
								unsigned short DeadManButton:1;
								unsigned short Thermic:1;
								unsigned short Pump2Ignition:1;
								unsigned short Contactor:1;
								unsigned short VeederRootHighLevel:1;
								unsigned short StartState:1;
							}DI;
						unsigned int DIs;
					};

		typedef enum
			{
				RegisterTypeNone					=	0,
				RegisterTypeHolding					=	1,
				RegisterTypeStatus					=	2,
				RegisterTypeInput					=	3,
				RegisterTypeOutput					=	4,
				RegisterTypeTimerControl			=	5,
				RegisterTypeFlash					=	6,
				RegisterTypeMicroPortSet			=	7,
				RegisterTypeMicroPortReset			=	8,
				RegisterTypeMicroPortInput 			=	9,
				RegisterTypeMicroPortOutput 		=	10
			}enumREGISTERTYPE;

		typedef struct
			{
				unsigned char   FirstRead;
				unsigned char 	Channel;
				unsigned char   NextChannel;
				double 			ChannelValue;
				unsigned char 	InProgress;
				unsigned char   Process;
				unsigned short  SlaveAddress;
				unsigned char  Status;
			}strcADC;

		typedef enum
			{
				LTVeryHigh 			= 0x01,
				LTHigh 				= 0x02,
				LTEndOfFilling 		= 0x04,
				LTWarningLow 		= 0x20,
				LTLow 				= 0x40,
				LTVeryLow			= 0x80
			}enumALERTLT;

		typedef enum
			{
				GDVeryHigh 			= 0x01,
				GDHigh 				= 0x02
			}enumALERTGD;

		typedef struct
			{
				unsigned short Timeout:1;
				unsigned short Started:1;
				unsigned short Restart:1;
				unsigned short Hang:1;
				unsigned short Enable:1;
			}strcTIMERCONTROL;

		typedef struct
			{
				unsigned short IllegalFueling:1;
				unsigned short AlertRunOnUpDown:1;
				unsigned short FuelingWithID:1;
				unsigned short ShutOffRelayState:1;
			}strcSYSTEMCONTROL;


		typedef struct
			{
				strcTIMERCONTROL 	*Control[TIMER_COUNT];
				unsigned int 		*Counter[TIMER_COUNT];
				unsigned int 		*TimeOut[TIMER_COUNT];
			}strcTIMERS;

		typedef struct
			{
				unsigned char 	*Holding;
				unsigned char 	*Status;
				unsigned int 	*Input;
				unsigned int 	*Coil;
				unsigned char 	*CoilBackup;
				strcTIMERS      Timers;
			}strcREGISTERS;

		typedef struct
			{
				unsigned short *SavePosition;
				unsigned int *Code[MASTER_CODE_COUNT];
			}strcMASTERCODE;


		typedef struct
			{
				enumREGISTERTYPE RegisterType;
				unsigned long Address;
				signed short Length;
				unsigned long Value;
			}strcREGISTERDATAINFO;

		typedef struct
				{
					unsigned short *EnabledModule;
					unsigned short *Control;
					signed int *ChannelValue[2];
				}strcAnalogOutput;

		typedef struct
				{
					float *Bottom;
					float *Top;
				}strcSCALE;

		typedef struct
				{
					float *Constant;
					float *Offset;
				}strcCALIBRATION;

		typedef struct
			{
				float *Low;
				float *HighOfLiquid;

			}strcRANGE;



		typedef struct
			{
				unsigned short Active:1;
				unsigned short OnOffState:1;
				unsigned short Continuously:1;
				unsigned short Acknowledge:1;
			}strcALERTRUNCONTROL;

		typedef struct
			{
				unsigned short *Len;
				float *fP;
				float *fQ;
				float *fR;
				float *fKGain;
			}strcKALMANPARAMETER;

		typedef struct
			{
				unsigned short *EnabledModule;
				unsigned int *ChannelType;
				unsigned int *KalmanFilterEnable;
				unsigned int *AvarageEnable;
				signed int *AnalogValue[AI_CHANNEL_COUNT];
				float *AnalogValueFiltered[AI_CHANNEL_COUNT];

				unsigned short *Allocation[AI_CHANNEL_COUNT];

				double *ModuleResolutionMultiplier[AI_MODULE_COUNT];
				float *ChannelBottomValuemV[AI_CHANNEL_COUNT];
				float *ChannelTopValuemV[AI_CHANNEL_COUNT];

				strcSCALE Scale[AI_CHANNEL_COUNT];
				strcCALIBRATION Calibration[AI_CHANNEL_COUNT];
				float *Calculated[AI_CHANNEL_COUNT];

				unsigned short *ChannelState[AI_CHANNEL_COUNT];
				unsigned short *ModuleChannelPos[AI_MODULE_COUNT];
				unsigned short *SeqNo[AI_MODULE_COUNT];
				unsigned short *ModuleType[MODULE_SLOT_COUNT];
				strcKALMANPARAMETER KalmanPar;
				strcRANGE Follow[AI_CHANNEL_COUNT];
			}strcAnalogInput;


		typedef struct
			{
				unsigned short *EnabledModule;

				union unionDI *DebugMode;
				union unionDI *Debug;
				union unionDI *StandBy;
				union unionDI *State;
			}strcDigitalInput;

		typedef struct
			{
				unsigned short *EnabledModule;
				unsigned int *Master[4];
			}strcDigitalOutput;


		typedef struct
			{
				strcAnalogInput AnalogInput;
				strcAnalogOutput AnalogOutput;
				strcDigitalInput DigitalInput;
				strcDigitalOutput DigitalOutput;

			}strcPERIPHERAL;

		typedef struct
			{
				unsigned short *Dispenser;
				unsigned short *Pump[4];
				unsigned short *Tank[4];
			}strcRELAYSTATE;

		typedef struct
			{
				unsigned int  Adc:1;
				unsigned int  OneWire:1;
				unsigned int  LTMasterWarning:1;
				unsigned int  LTWarning:2;
				unsigned int  WarningTimeout:2;
				unsigned int  ProbeTimeout:2;
			}strcWARNING;

		typedef struct
			{
				unsigned short  ProcessStart:1;
				unsigned short  IDRead:1;
				unsigned short  IDOK:1;
				unsigned short FuelingStated:1;

			}strcPLCSTATUS;

		typedef struct
			{
				float  PI_Const;
				unsigned short  IDRead:1;
				unsigned short  IDOK:1;
			}strcCONSTANT;

		typedef struct
			{
				unsigned short  HRUpdate:1;
				unsigned short  HRUpdateInprogress:1;
				unsigned short  IllegalFueling:1;
			}strcPLCCONTROL;

		typedef struct
			{
				unsigned short  *Status;
				unsigned short  *OnTime;
				unsigned short  *OffTime;
			}strcLED;


		typedef struct
				{
					unsigned short *BaudRate;
					unsigned short *DataBits;
					unsigned short *Parity;
					unsigned short *StopBits;
				}strcRTU;

		typedef struct
			{
				strcCONSTANT  Constant;
				strcPLCSTATUS *Status;
				strcRTU RTU;
				unsigned int *RunTime;
				unsigned int *SerialNo;
				unsigned short *SlaveAddress;
				strcPLCCONTROL *Control;
				strcPERIPHERAL Peripheral;
				strcWARNING *Warning;
				strcLED 	Led[LED_COUNT];
				//unsigned short *ModBusSequenceNo;
				//unsigned short *ModBusAddress[10];
				union unionDO *DOout;
				union unionDI *DInput;
			}strcPLC;




		typedef struct
			{
				unsigned short Timeout:1;
				unsigned short DataSent:1;
				unsigned short DataReceive:1;
				unsigned short DataSendInprogress:1;
				unsigned short ModBusCommActive:1;
				unsigned short ModBusCommActiveTimerRestart:1;
			}strcDATASENDCONTROL;

		typedef struct
			{
				strcDATASENDCONTROL *DataSendControl;
				unsigned int *DefaultPacket;
				unsigned int *ActivePacket;
				unsigned int *ToBeSendPacket;
				unsigned int *ActiveToBeSendPacket;
				unsigned int *ToBeSendSubPacket;
				unsigned int *DataSendPeriod;
				signed int *DataChannelValueMultiplier;
				signed int *DataAnalogInputValueMultiplier;
				unsigned short *SendPacketNo;
				unsigned short *SendSubPacketNo;
				unsigned char *SendArray;
			}strcDATASENDCENTER;

		typedef struct
			{
				unsigned short *Enable;
				unsigned short *State;
			}strcALERTESDETAIL;

		typedef struct
			{
				unsigned short *AlertEnable;
				unsigned short *ESEnable;
				unsigned short *State;
			}strcALERTESPERIPHERAL;

		typedef struct
			{
				unsigned short *AlertEnable;
				unsigned short *ESEnable;
				unsigned short *AlertState;
				unsigned short *ESState;
			}strcALERTESPERIPHERALMASTER;

		typedef struct
			{
				unsigned short *Alert;
				unsigned short *ES;
			}strcALERTESCLEAR;

		typedef struct
			{
				unsigned short *AlertEnable;
				unsigned short *ESEnable;
				unsigned short *AlertState;
				unsigned short *ESState;
				unsigned short *AlertAutoClear;
				unsigned short *ESAutoClear;
				strcALERTESPERIPHERALMASTER LT;
				strcALERTESPERIPHERALMASTER GD;
				strcALERTESPERIPHERALMASTER ESB;
				strcALERTESPERIPHERALMASTER THERMIC;
				strcALERTESPERIPHERALMASTER CONTACTOR;
				strcALERTESPERIPHERALMASTER SYSTEM;
			}strcALERTESMASTER;

	typedef struct
		{
			unsigned int CalValLTSeqNo;
			unsigned int CalValLTSeqNo2;
			unsigned short LTSeqNo;
			unsigned short DOValveByteNo;
			unsigned short DOValveNo;
		}strcSTATIONTANK;

	typedef struct
			{
				unsigned short Enable:1;
				unsigned short Continuously:1;
			}strcALERTCONTROL;

		typedef struct
			{
				strcALERTCONTROL  *Control;
				unsigned short    *AlertOnTime;
				unsigned short    *AlertOffTime;
				signed short      *AlertCount;
			}strcALERTRUN;

		typedef struct
			{
				strcALERTRUNCONTROL  	*Control;
				unsigned short    		*AlertNo;
				signed short      		*AlertCounter;
				unsigned int 			*WaitToRun;
				unsigned int 			*AlertTimeToBeDisplay;
			}strcALERTRUNSTATE;

		typedef struct
			{
				unsigned short    *VeryHigh;
				unsigned short    *High;
				unsigned short    *EndOfFilling;
				unsigned short    *WarningLow;
				unsigned short    *Low;
				unsigned short    *VeryLow;
			}strcLTALERTTYPE;

		typedef struct
			{
				unsigned short    *VeryHigh;
				unsigned short    *High;
			}strcGDALERTTYPE;

		typedef struct
			{
				unsigned short    *IllegalFueling;
				unsigned short    *AlertTest;
				unsigned short    *OverFilling;
			}strcSYSTEMALERTTYPE;

		typedef struct
			{
				float  *LT;
				float  *GD;
				unsigned int *WarningTimeout;
			}strcALERTCLEAR;



		typedef struct
			{
				strcLTALERTTYPE LT;
				strcGDALERTTYPE GD;
				strcSYSTEMALERTTYPE SYSTEM;
				unsigned short *ESB;
				unsigned short *Contactor;
				unsigned short *Thermic;
				unsigned short *Deviation;
			}strcALERTTYPE;

		typedef struct
			{
				strcALERTESMASTER 		Master;
				strcALERTESPERIPHERAL	LT[LT_COUNT];
				strcALERTESPERIPHERAL	GD[GD_COUNT];
				strcALERTESPERIPHERAL	ESB;
				strcALERTESPERIPHERAL	THERMIC;
				strcALERTESPERIPHERAL	CONTACTOR;
			}strcALERTES;

		typedef struct
			{
				strcALERTTYPE     	TypeNo;
				strcALERTCLEAR		Clear;
				strcALERTRUN 	  	RunTypes[ALERT_TYPE_COUNT];
				strcALERTRUNSTATE  	RunState;

			}strcALERT;

		typedef struct
			{
				unsigned short AlertSource;
				unsigned short SeqNo;
				unsigned short AlertState;
				unsigned short AlertRunNo;
			}strcALERTACTIVATE;

		typedef struct
			{
				float *VeryHigh ;
				float *High;
				float *EndOfFilling;

				float *WarningLow;
				float *Low;
				float *VeryLow;
			}strcLTCRITICAL;

		typedef struct
			{
				unsigned short *SeqNo;
				float  *SeqValue;
			}strcACTIVESENSOR;

		typedef struct
			{
				float *VeryHigh ;
				float *High;
			}strcGDCRITICAL;

		typedef struct
			{
				unsigned short *Count;
				strcLTCRITICAL CriticalLevel;
			}strcLTCRITICALS;

		typedef struct
			{
				unsigned short *Count;
				strcGDCRITICAL CriticalLevel;
			}strcGDCRITICALS;

		typedef struct
			{
				strcLTCRITICALS LT[LT_COUNT];
				strcGDCRITICALS GD[GD_COUNT];
				strcACTIVESENSOR GDActiveSensor;
				strcACTIVESENSOR ESBActive;
			}strcCRITICALS;


		union unionButton0
			{
				 struct
					{
						unsigned short  StartStop:1;
						unsigned short  EmergencyStop:1;
						unsigned short  PeriodicallyPumpRun:1;
						unsigned short  TankCapacityCalc:1;
						unsigned short  Acknowledge:1;
						unsigned short  TestAlertRunClose:1;
						unsigned short  OverFillingConfirmation:1;
						unsigned short  OverFillingClear:1;
						unsigned short  IDOK:1;
						unsigned short  DataSend:1;
						unsigned short  CopyChannelMv:1;
						unsigned short  Empty11:1;
						unsigned short  Empty12:1;
						unsigned short  Empty13:1;
						unsigned short  HRDefault:1;
						unsigned short  HRUpdate:1;
					}Button;
				unsigned short Buttons;
			};

			union unionButton1
				{
				  struct
					{
						unsigned short  DOAlert:1;
						unsigned short  DOFuelingValve02:1;
						unsigned short  DOFuelingValve01:1;
						unsigned short  DOPump02:1;
						unsigned short  DOPump01:1;
						unsigned short  DOModemPower:1;
						unsigned short  DOShutOff:1;
						unsigned short  DOPumpPeriodicallyrun:1;
						unsigned short  DO8:1;
						unsigned short  DO9:1;
						unsigned short  DO10:1;
						unsigned short  DO11:1;
						unsigned short  DO12:1;
						unsigned short  DO13:1;
						unsigned short  DO14:1;
						unsigned short  DO15:1;
					}Button;
					unsigned short Buttons;
				};

			union unionButton2
			{
				struct
					{
						unsigned short  AnalogScaleMv1:1;
						unsigned short  AnalogScaleMv2:1;
						unsigned short  AnalogScale1:1;
						unsigned short  AnalogScale2:1;
						unsigned short  KalmanDefault:1;
						unsigned short  KalmanReInit:1;
						unsigned short  GDCritical03:1;
						unsigned short  GDCritical47:1;
						unsigned short  GDCritical811:1;
						unsigned short  GDCritical1215:1;

						unsigned short  AnalogModuleOnBoardDefault:1;
						unsigned short  AnalogModuleExtDefault:1;
					}Button;

				unsigned short Buttons;
			};

		typedef struct
			{
				unsigned short Alert:1;
				unsigned short FillingValve:2;
				unsigned short Pump:2;
				unsigned short ModemPower:1;
				unsigned short Shutoff:1;
				unsigned short PumpPeriodicallyRun:1;
				unsigned short ShutoffState:1;
				unsigned short ShowSecondLevel:2;
				unsigned short DispenserPumpIgnition:2;
			}strcSYSTEMINDICATOR;

		typedef struct
			{
				unsigned short TestAlert:1;
				unsigned short EndOfFillingWarning:1;
				unsigned short EndOfFilling:1;
				unsigned short OverFillingLevel:2;
				unsigned short ToBeClearOverFilling:1;
			}strcSYSTEMWARNING;

		typedef struct
			{
				unsigned short *Count;
				float *Capacity[2];
				float *Density[2];
				float *AmoungKg[2];
			}strcTANK;

		typedef struct
			{
				union unionButton0 	*Button0;
				union unionButton1 	*Button1;
				union unionButton2	*Button2;
				unsigned short 		*State;
				unsigned short 		*Substate;
				strcSYSTEMCONTROL 	*Control;
				strcSYSTEMINDICATOR *Indicator;
				strcSYSTEMWARNING	*Warning;
				strcTANK 			Tanks;
			}strcSYSTEM;

		typedef struct
			{
				unsigned short *DispenserCount;
				unsigned short *FillingValveCount;

			}strcSTATION;

		typedef struct
			{
				unsigned char *Date;
				unsigned int *Control;
				unsigned char *Day;
				unsigned char *Month;
				unsigned char *Year;
				unsigned char *Hour;
				unsigned char *Minute;
				unsigned char *Second;
				unsigned char *MiliSecond;
				unsigned char *DayOfWeek;
			}strcRTC;

		typedef struct
			{
				unsigned int *Master;
				unsigned int *Count;
			}strcRTCCounter;

		typedef struct
			{
				float *LT[2];
				float *PT[2];
				float *TankCapacity[2];
				float *TankAmountKg[2];

				unsigned short *DigitalInput;
				unsigned short *DigitalOutput;
			}strcHMI;


#endif /* INCLUDE_REGISTERS_H_ */
