/*
 * ADS_1220.C
 *
 *  Created on: Nov 15, 2022
 *      Author: Sezgin Berber
 */
#include "MicroPeripheral.h"
#include "Registers.h"
#include "AnalogInput.h"
#include "ADS_1220.h"

extern strcADC ADC_Modules[MAX_AI_BOARD_COUNT];
extern strcPLC Plc;


/* ADS1220 Initial Configuration */
void ADS1220Config(strcAdcINSTANCE *AdcInstance)
{
	unsigned Temp;
	static unsigned short ADS1220_0 = ADS1220_MUX_0_G, ADS1220_1 = ADS1220_DR_20 + ADS1220_CC; //, ADS1220_2 = ADS1220_VREF_INT;

	ADS1220ReadRegister(AdcInstance, ADS1220_0_REGISTER, 0x01, &Temp);
	/* clear prev value; */
   	//Temp &= 0x00;
   	switch(AdcInstance->ChannelSeqNo)
		{
			case 0: ADS1220_0 = ADS1220_MUX_0_G; break;
			case 1: ADS1220_0 = ADS1220_MUX_1_G; break;
			case 2: ADS1220_0 = ADS1220_MUX_2_G; break;
			case 3: ADS1220_0 = ADS1220_MUX_3_G; break;

			default :ADS1220_0 = ADS1220_MUX_0_G; break;

		}

   	Temp = ADS1220_0;
   	/* write the register value containing the new value back to the ADS */


   	ADS1220WriteRegister(AdcInstance, ADS1220_0_REGISTER, 0x01, &Temp);

	ADS1220ReadRegister(AdcInstance, ADS1220_1_REGISTER, 0x01, &Temp);
	/* clear prev DataRate code; */
	Temp &= 0x1f;
	Temp = ADS1220_1;	/* Set default start mode to 600sps and continuous conversions */
	/* write the register value containing the new value back to the ADS */
	ADS1220WriteRegister(AdcInstance, ADS1220_1_REGISTER, 0x01, &Temp);

	ADS1220ReadRegister(AdcInstance, ADS1220_2_REGISTER, 0x01, &Temp);
	Temp &= 0x3F;
	Temp |= (ADS1220_VREF_INT);
	ADS1220SetVoltageReference(AdcInstance, Temp);

	ADS1220ReadRegister(AdcInstance, ADS1220_3_REGISTER, 0x01, &Temp);

	Temp |= (ADS1220_DRDY_MODE);
	ADS1220WriteRegister(AdcInstance, ADS1220_3_REGISTER, 0x01, &Temp);

}
void ADS1220Channel(strcAdcINSTANCE *AdcInstance)
{
	unsigned Temp;
	static unsigned short ADS1220_0 = ADS1220_MUX_0_G;

	/* clear prev value; */
   	//Temp &= 0x00;
   	switch(AdcInstance->ChannelSeqNo)
		{
			case 0: ADS1220_0 = ADS1220_MUX_0_G; break;
			case 1: ADS1220_0 = ADS1220_MUX_1_G; break;
			case 2: ADS1220_0 = ADS1220_MUX_2_G; break;
			case 3: ADS1220_0 = ADS1220_MUX_3_G; break;

			default :ADS1220_0 = ADS1220_MUX_0_G; break;

		}

   	Temp = ADS1220_0;
   	/* write the register value containing the new value back to the ADS */
   	ADS1220WriteRegister(AdcInstance, ADS1220_0_REGISTER, 0x01, &Temp);
}
//
///* ADS1220 Initial Configuration */
//void ADS1220Config(strcAdcINSTANCE *AdcInstance)
//{
//	unsigned Temp;
//
//	ADS1220ReadRegister(AdcInstance, ADS1220_0_REGISTER, 0x01, &Temp);
//	/* clear prev value; */
//   	Temp &= 0x00;
//   	Temp |= ADS1220_MUX_0_G;
//   	/* write the register value containing the new value back to the ADS */
//   	ADS1220WriteRegister(AdcInstance, ADS1220_0_REGISTER, 0x01, &Temp);
//
//	ADS1220ReadRegister(AdcInstance, ADS1220_1_REGISTER, 0x01, &Temp);
//	/* clear prev DataRate code; */
//	Temp &= 0x1f;
//	Temp |= (ADS1220_DR_600 + ADS1220_CC);		/* Set default start mode to 600sps and continuous conversions */
//	/* write the register value containing the new value back to the ADS */
//	ADS1220WriteRegister(AdcInstance, ADS1220_1_REGISTER, 0x01, &Temp);
//}

/*  Polling Function */
//int ADS1220WaitForDataReady(int Timeout)
//{
//   if (Timeout > 0)
//   {
//      /* wait for /DRDY = 1 */
//      while (!(P2IN & ADS1220_DRDY) && (Timeout-- >= 0));
//      /* wait for /DRDY = 0 */
//      while ( (P2IN & ADS1220_DRDY) && (Timeout-- >= 0))         ;
//      if (Timeout < 0)
//         return 0; /* ADS1220_TIMEOUT_WARNING; */
//   }
//   else
//   {
//      /* wait for /DRDY = 1 */
//      while (!(P2IN & ADS1220_DRDY));
//      /* wait for /DRDY = 0 */
//      while ( (P2IN & ADS1220_DRDY));
//   }
//   return ADS1220_NO_ERROR;
//}
//void ADS1220AssertCS( int fAssert)
//{
//   if (fAssert)
//		P1OUT &=  ~(ADS1220_CS);
//   else
//		P1OUT |=  (ADS1220_CS);
//}
//
//void ADS1220SendByte(unsigned char Byte)
//{	char dummy;
//	while(!(UCA0IFG&UCTXIFG));
//	UCA0TXBUF = Byte;
//	while(!(UCA0IFG&UCRXIFG));
//	dummy = UCA0RXBUF;
//
//}
//
//unsigned char ADS1220ReceiveByte(void)
//{
//   unsigned char Result = 0;
//	while(!(UCA0IFG & UCTXIFG));	/* Make sure nothing is currently transmitting */
//	UCA0TXBUF = 0xff;		 	/* Send out NOP to initiate SCLK */
//	while(!(UCA0IFG&UCRXIFG));	/* Wait until all data is transmitted (received) */
//	Result = UCA0RXBUF;			/* Capture the receive buffer */
//	return Result;
//}
/*
******************************************************************************
 Higher level functions
*/
unsigned char ADS1220EOC(strcAdcINSTANCE *AdcInstance)
{
	unsigned char State=0;

	SPIModuleChipSelect(*AdcInstance, SPI_MODULE_ENABLE);

	if(AdcInstance->SPIx == &hspi1)
		{
			State = !HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6);
		}

	SPIModuleChipSelect(*AdcInstance, SPI_MODULE_DISABLE);

	return State;
}

long ADS1220ReadData(strcAdcINSTANCE *AdcInstance)
{
   long Data;
   unsigned char SendChar,ReceiveChar;

   /* assert CS to start transfer */
   //ADS1220AssertCS(1);
   SPIModuleChipSelect(*AdcInstance, 1);  // Enable

   /* send the command byte */
   //ADS1220SendByte(ADS1220_CMD_RDATA);
   SendChar = ADS1220_CMD_RDATA;
   HAL_SPI_Transmit(AdcInstance->SPIx, &SendChar , 1,  ADS1220_SPI_TIMEOUTS);

   /* get the conversion result */
   //Data = ADS1220ReceiveByte();

   HAL_SPI_Receive(AdcInstance->SPIx, &ReceiveChar, 1, ADS1220_SPI_TIMEOUTS);
   Data = ReceiveChar ; // | ADS1220ReceiveByte();
   Data <<= 8;

   HAL_SPI_Receive(AdcInstance->SPIx, &ReceiveChar, 1, ADS1220_SPI_TIMEOUTS);
   Data |= ReceiveChar  ; // | ADS1220ReceiveByte();
   Data <<= 8;

   HAL_SPI_Receive(AdcInstance->SPIx, &ReceiveChar, 1, ADS1220_SPI_TIMEOUTS);
   Data |= ReceiveChar  ; // | ADS1220ReceiveByte();

   /* sign extend data */
   if (Data & 0x800000)
	   {
		   Data &= ~0x800000;
	   }
   //Data |= 0xff000000;

   /* de-assert CS */
   SPIModuleChipSelect(*AdcInstance, 0);  // Disable
   AdcInstance->lAdcValue = Data;
   return Data;
}

void ADS1220ReadRegister(strcAdcINSTANCE *AdcInstance, int StartAddress, int NumRegs, unsigned * pData)
{
   int i;
   unsigned char SendChar,ReceiveChar;
	/* assert CS to start transfer */
   SPIModuleChipSelect(*AdcInstance, 1);  // Enable
 	/* send the command byte */

	//ADS1220SendByte(ADS1220_CMD_RREG | (((StartAddress<<2) & 0x0c) |( (NumRegs-1) & 0x03)));

	SendChar = ADS1220_CMD_RREG | (((StartAddress<<2) & 0x0c) |( (NumRegs-1) & 0x03));
	HAL_SPI_Transmit(AdcInstance->SPIx, &SendChar , 1,  ADS1220_SPI_TIMEOUTS);
   	/* get the register content */
	for (i=0; i< NumRegs; i++)
		{
			HAL_SPI_Receive(AdcInstance->SPIx, &ReceiveChar, 1, ADS1220_SPI_TIMEOUTS);
			*pData++ = ReceiveChar;
		}
   	/* de-assert CS */
	SPIModuleChipSelect(*AdcInstance, 0);  // Disable
	return;
}
void ADS1220WriteRegister(strcAdcINSTANCE *AdcInstance, int StartAddress, int NumRegs, unsigned * pData)
{
	int i;
	unsigned char SendChar;
   	/* assert CS to start transfer */
	SPIModuleChipSelect(*AdcInstance, 1);  // Enable
   	/* send the command byte */
	//ADS1220SendByte(ADS1220_CMD_WREG | (((StartAddress<<2) & 0x0c) |((NumRegs-1)&0x03)));
	SendChar = ADS1220_CMD_WREG | (((StartAddress<<2) & 0x0c) |((NumRegs-1)&0x03));
	HAL_SPI_Transmit(AdcInstance->SPIx, &SendChar , 1,  ADS1220_SPI_TIMEOUTS);
    /* send the data bytes */
	for (i=0; i< NumRegs; i++)
	{
		//ADS1220SendByte(*pData++);
		SendChar = *pData++;
		HAL_SPI_Transmit(AdcInstance->SPIx, &SendChar , 1,  ADS1220_SPI_TIMEOUTS);
	}
   	/* de-assert CS */
	SPIModuleChipSelect(*AdcInstance, 0);  // Disable
   	return;
}
void ADS1220SendResetCommand(strcAdcINSTANCE *AdcInstance)
{
	unsigned char SendChar;
	/* assert CS to start transfer */
	//ADS1220AssertCS(1);
	SPIModuleChipSelect(*AdcInstance, 1);  // Enable
   	/* send the command byte */
	//ADS1220SendByte(ADS1220_CMD_RESET);
	SendChar = ADS1220_CMD_RESET;
	HAL_SPI_Transmit(AdcInstance->SPIx, &SendChar , 1,  ADS1220_SPI_TIMEOUTS);
   	/* de-assert CS */
	SPIModuleChipSelect(*AdcInstance, 0);  // Disable
   	return;
}
void ADS1220SendStartCommand(strcAdcINSTANCE *AdcInstance)
{
	unsigned char SendChar;
	/* assert CS to start transfer */
	SPIModuleChipSelect(*AdcInstance, 1);  // Enable
    /* send the command byte */
	//ADS1220SendByte(ADS1220_CMD_SYNC);
	SendChar = ADS1220_CMD_SYNC;
	HAL_SPI_Transmit(AdcInstance->SPIx, &SendChar , 1,  ADS1220_SPI_TIMEOUTS);
   	/* de-assert CS */
	SPIModuleChipSelect(*AdcInstance, 0);  // Disable
    return;
}
void ADS1220SendShutdownCommand(strcAdcINSTANCE *AdcInstance)
{
	unsigned char SendChar;
	/* assert CS to start transfer */
	SPIModuleChipSelect(*AdcInstance, 1);  // Enable
   	/* send the command byte */
	//ADS1220SendByte(ADS1220_CMD_SHUTDOWN);
	SendChar = ADS1220_CMD_SHUTDOWN;
	HAL_SPI_Transmit(AdcInstance->SPIx, &SendChar , 1,  ADS1220_SPI_TIMEOUTS);
   	/* de-assert CS */
	SPIModuleChipSelect(*AdcInstance, 0);  // Disable
    return;
}
/*
******************************************************************************
register set value commands
*/
int ADS1220SetChannel(strcAdcINSTANCE *AdcInstance, int Mux)
{
	unsigned int cMux = Mux;
   /* write the register value containing the new value back to the ADS */
   ADS1220WriteRegister(AdcInstance, ADS1220_0_REGISTER, 0x01, &cMux);
   return ADS1220_NO_ERROR;
}
int ADS1220SetGain(strcAdcINSTANCE *AdcInstance, int Gain)
{
	unsigned int cGain = Gain;
	/* write the register value containing the new code back to the ADS */
	ADS1220WriteRegister(AdcInstance, ADS1220_0_REGISTER, 0x01, &cGain);
	return ADS1220_NO_ERROR;
}
int ADS1220SetPGABypass(strcAdcINSTANCE *AdcInstance, int Bypass)
{
	unsigned int cBypass = Bypass;
	/* write the register value containing the new code back to the ADS */
	ADS1220WriteRegister(AdcInstance, ADS1220_0_REGISTER, 0x01, &cBypass);
	return ADS1220_NO_ERROR;
}
int ADS1220SetDataRate(strcAdcINSTANCE *AdcInstance, int DataRate)
{
	unsigned int cDataRate = DataRate;
	/* write the register value containing the new value back to the ADS */
	ADS1220WriteRegister(AdcInstance, ADS1220_1_REGISTER, 0x01, &cDataRate);
	return ADS1220_NO_ERROR;
}
int ADS1220SetClockMode(strcAdcINSTANCE *AdcInstance, int ClockMode)
{
	unsigned int cClockMode = ClockMode;
   	/* write the register value containing the value back to the ADS */
	ADS1220WriteRegister(AdcInstance, ADS1220_1_REGISTER, 0x01, &cClockMode);
	return ADS1220_NO_ERROR;
}
int ADS1220SetPowerDown(strcAdcINSTANCE *AdcInstance, int PowerDown)
{
	unsigned int cPowerDown = PowerDown;
   	/* write the register value containing the new value back to the ADS */
	ADS1220WriteRegister(AdcInstance,ADS1220_1_REGISTER, 0x01, &cPowerDown);
	return ADS1220_NO_ERROR;
}
int ADS1220SetTemperatureMode(strcAdcINSTANCE *AdcInstance, int TempMode)
{
	unsigned int cTempMode = TempMode;
   	/* write the register value containing the new value back to the ADS */
	ADS1220WriteRegister(AdcInstance, ADS1220_1_REGISTER, 0x01, &cTempMode);
	return ADS1220_NO_ERROR;
}
int ADS1220SetBurnOutSource(strcAdcINSTANCE *AdcInstance, int BurnOut)
{
	unsigned int cBurnOut = BurnOut;
   	/* write the register value containing the new value back to the ADS */
	ADS1220WriteRegister(AdcInstance,  ADS1220_1_REGISTER, 0x01, &cBurnOut);
	return ADS1220_NO_ERROR;
}
int ADS1220SetVoltageReference(strcAdcINSTANCE *AdcInstance,int VoltageRef)
{
	unsigned int cVoltageRef = VoltageRef;
   	/* write the register value containing the new value back to the ADS */
	ADS1220WriteRegister(AdcInstance, ADS1220_2_REGISTER, 0x01, &cVoltageRef);
	return ADS1220_NO_ERROR;
}
int ADS1220Set50_60Rejection(strcAdcINSTANCE *AdcInstance, int Rejection)
{
	unsigned int cRejection = Rejection;
   	/* write the register value containing the new value back to the ADS */
	ADS1220WriteRegister(AdcInstance, ADS1220_2_REGISTER, 0x01, &cRejection);
	return ADS1220_NO_ERROR;
}
int ADS1220SetLowSidePowerSwitch(strcAdcINSTANCE *AdcInstance, int PowerSwitch)
{
	unsigned int cPowerSwitch = PowerSwitch;
   	/* write the register value containing the new value back to the ADS */
	ADS1220WriteRegister(AdcInstance, ADS1220_2_REGISTER, 0x01, &cPowerSwitch);
	return ADS1220_NO_ERROR;
}
int ADS1220SetCurrentDACOutput(strcAdcINSTANCE *AdcInstance, int CurrentOutput)
{
	unsigned int cCurrentOutput = CurrentOutput;
   	/* write the register value containing the new value back to the ADS */
	ADS1220WriteRegister(AdcInstance, ADS1220_2_REGISTER, 0x01, &cCurrentOutput);
	return ADS1220_NO_ERROR;
}
int ADS1220SetIDACRouting(strcAdcINSTANCE *AdcInstance, int IDACRoute)
{
	unsigned int cIDACRoute = IDACRoute;
	/* write the register value containing the new value back to the ADS */
	ADS1220WriteRegister(AdcInstance, ADS1220_3_REGISTER, 0x01, &cIDACRoute);
	return ADS1220_NO_ERROR;
}
int ADS1220SetDRDYMode(strcAdcINSTANCE *AdcInstance, int DRDYMode)
{
	unsigned int cDRDYMode = DRDYMode;
   	/* write the register value containing the new gain code back to the ADS */
	ADS1220WriteRegister(AdcInstance, ADS1220_3_REGISTER, 0x01, &cDRDYMode);
	return ADS1220_NO_ERROR;
}
/*
******************************************************************************
register get value commands
*/
int ADS1220GetChannel(strcAdcINSTANCE *AdcInstance)
{
	unsigned Temp;
	/* Parse Mux data from register */
	ADS1220ReadRegister(AdcInstance, ADS1220_0_REGISTER, 0x01, &Temp);
	/* return the parsed data */
	return (Temp >>4);
}
int ADS1220GetGain(strcAdcINSTANCE *AdcInstance)
{
	unsigned Temp;
	/* Parse Gain data from register */
	ADS1220ReadRegister(AdcInstance, ADS1220_0_REGISTER, 0x01, &Temp);
	/* return the parsed data */
	return ( (Temp & 0x0e) >>1);
}
int ADS1220GetPGABypass(strcAdcINSTANCE *AdcInstance)
{
	unsigned Temp;
	/* Parse Bypass data from register */
	ADS1220ReadRegister(AdcInstance, ADS1220_0_REGISTER, 0x01, &Temp);
	/* return the parsed data */
	return (Temp & 0x01);
}
int ADS1220GetDataRate(strcAdcINSTANCE *AdcInstance)
{
	unsigned Temp;
	/* Parse DataRate data from register */
	ADS1220ReadRegister(AdcInstance, ADS1220_1_REGISTER, 0x01, &Temp);
	/* return the parsed data */
	return ( Temp >>5 );
}
int ADS1220GetClockMode(strcAdcINSTANCE *AdcInstance)
{
	unsigned Temp;
	/* Parse ClockMode data from register */
	ADS1220ReadRegister(AdcInstance, ADS1220_1_REGISTER, 0x01, &Temp);
	/* return the parsed data */
	return ( (Temp & 0x18) >>3 );
}
int ADS1220GetPowerDown(strcAdcINSTANCE *AdcInstance)
{
	unsigned Temp;
	/* Parse PowerDown data from register */
	ADS1220ReadRegister(AdcInstance, ADS1220_1_REGISTER, 0x01, &Temp);
	/* return the parsed data */
	return ( (Temp & 0x04) >>2 );
}
int ADS1220GetTemperatureMode(strcAdcINSTANCE *AdcInstance)
{
	unsigned Temp;
	/* Parse TempMode data from register */
	ADS1220ReadRegister(AdcInstance, ADS1220_1_REGISTER, 0x01, &Temp);
	/* return the parsed data */
	return ( (Temp & 0x02) >>1 );
}
int ADS1220GetBurnOutSource(strcAdcINSTANCE *AdcInstance)
{
	unsigned Temp;
	/* Parse BurnOut data from register */
	ADS1220ReadRegister(AdcInstance, ADS1220_1_REGISTER, 0x01, &Temp);
	/* return the parsed data */
	return ( Temp & 0x01 );
}
int ADS1220GetVoltageReference(strcAdcINSTANCE *AdcInstance)
{
	unsigned Temp;
	/* Parse VoltageRef data from register */
	ADS1220ReadRegister(AdcInstance, ADS1220_2_REGISTER, 0x01, &Temp);
	/* return the parsed data */
	return ( Temp >>6 );
}
int ADS1220Get50_60Rejection(strcAdcINSTANCE *AdcInstance)
{
	unsigned Temp;
	/* Parse Rejection data from register */
	ADS1220ReadRegister(AdcInstance, ADS1220_2_REGISTER, 0x01, &Temp);
	/* return the parsed data */
	return ( (Temp & 0x30) >>4 );
}
int ADS1220GetLowSidePowerSwitch(strcAdcINSTANCE *AdcInstance)
{
	unsigned Temp;
	/* Parse PowerSwitch data from register */
	ADS1220ReadRegister(AdcInstance, ADS1220_2_REGISTER, 0x01, &Temp);
	/* return the parsed data */
	return ( (Temp & 0x08) >>3);
}
int ADS1220GetCurrentDACOutput(strcAdcINSTANCE *AdcInstance)
{
	unsigned Temp;
	/* Parse IDACOutput data from register */
	ADS1220ReadRegister(AdcInstance, ADS1220_2_REGISTER, 0x01, &Temp);
	/* return the parsed data */
	return ( Temp & 0x07 );
}
int ADS1220GetIDACRouting(strcAdcINSTANCE *AdcInstance, int WhichOne)
{
	/* Check WhichOne sizing */
	if (WhichOne >1) return ADS1220_ERROR;
	unsigned Temp;
	/* Parse Mux data from register */
	ADS1220ReadRegister(AdcInstance, ADS1220_3_REGISTER, 0x01, &Temp);
	/* return the parsed data */
	if (WhichOne) return ( (Temp & 0x1c) >>2);
	else return ( Temp >>5 );
}
int ADS1220GetDRDYMode(strcAdcINSTANCE *AdcInstance)
{
	unsigned Temp;
	/* Parse DRDYMode data from register */
	ADS1220ReadRegister(AdcInstance, ADS1220_3_REGISTER, 0x01, &Temp);
	/* return the parsed data */
	return ( (Temp & 0x02) >>1 );
}
/* Useful Functions within Main Program for Setting Register Contents
*
*  	These functions show the programming flow based on the header definitions.
*  	The calls are not made within the demo example, but could easily be used by calling the function
*  		defined within the program to complete a fully useful program.
*	Similar function calls were made in the firwmare design for the ADS1220EVM.
*
*  The following function calls use ASCII data sent from a COM port to control settings
*	on the ADS1220.  The data is recontructed from ASCII and then combined with the
*	register contents to save as new configuration settings.
*
* 	Function names correspond to datasheet register definitions
*/
void set_MUX(strcAdcINSTANCE *AdcInstance, char c)
{
	int mux = (int) c - 48;
	int dERROR;
	unsigned Temp;
	if (mux>=49 && mux<=54) mux -= 39;
	/* The MUX value is only part of the register, so we have to read it back
	   and massage the new value into it */
	ADS1220ReadRegister(AdcInstance, ADS1220_0_REGISTER, 0x01, &Temp);
	Temp &= 0x0f;									/* strip out old settings */
	/* Change Data rate */
	switch(mux) {
		case 0:
			dERROR = ADS1220SetChannel(AdcInstance, Temp + ADS1220_MUX_0_1);
			break;
		case 1:
			dERROR = ADS1220SetChannel(AdcInstance, Temp + ADS1220_MUX_0_2);
			break;
		case 2:
			dERROR = ADS1220SetChannel(AdcInstance, Temp + ADS1220_MUX_0_3);
			break;
		case 3:
			dERROR = ADS1220SetChannel(AdcInstance, Temp + ADS1220_MUX_1_2);
			break;
		case 4:
			dERROR = ADS1220SetChannel(AdcInstance, Temp + ADS1220_MUX_1_3);
			break;
		case 5:
			dERROR = ADS1220SetChannel(AdcInstance, Temp + ADS1220_MUX_2_3);
			break;
		case 6:
			dERROR = ADS1220SetChannel(AdcInstance, Temp + ADS1220_MUX_1_0);
			break;
		case 7:
			dERROR = ADS1220SetChannel(AdcInstance, Temp + ADS1220_MUX_3_2);
			break;
		case 8:
			dERROR = ADS1220SetChannel(AdcInstance, Temp + ADS1220_MUX_0_G);
			break;
		case 9:
			dERROR = ADS1220SetChannel(AdcInstance, Temp + ADS1220_MUX_1_G);
			break;
		case 10:
			dERROR = ADS1220SetChannel(AdcInstance, Temp + ADS1220_MUX_2_G);
			break;
		case 11:
			dERROR = ADS1220SetChannel(AdcInstance, Temp + ADS1220_MUX_3_G);
			break;
		case 12:
			dERROR = ADS1220SetChannel(AdcInstance, Temp + ADS1220_MUX_EX_VREF);
			break;
		case 13:
			dERROR = ADS1220SetChannel(AdcInstance, Temp + ADS1220_MUX_AVDD);
			break;
		case 14:
			dERROR = ADS1220SetChannel(AdcInstance, Temp + ADS1220_MUX_DIV2);
			break;
		case 15:
			dERROR = ADS1220SetChannel(AdcInstance, Temp + ADS1220_MUX_DIV2);
			break;
		default:
			dERROR = ADS1220_ERROR;
			break;
	}
	if (dERROR==ADS1220_ERROR)
		set_ERROR();
}
void set_GAIN(strcAdcINSTANCE *AdcInstance, char c)
{
	int pga = (int) c - 48;
	int dERROR;
	unsigned Temp;
	/* The GAIN value is only part of the register, so we have to read it back
	   and massage the new value into it*/
	ADS1220ReadRegister(AdcInstance, ADS1220_0_REGISTER, 0x01, &Temp);
		Temp &= 0xf1;									/* strip out old settings */
	/* Change gain rate */
	switch(pga) {
		case 0:
			dERROR = ADS1220SetGain(AdcInstance, Temp + ADS1220_GAIN_1);
			break;
		case 1:
			dERROR = ADS1220SetGain(AdcInstance, Temp + ADS1220_GAIN_2);
			break;
		case 2:
			dERROR = ADS1220SetGain(AdcInstance, Temp + ADS1220_GAIN_4);
			break;
		case 3:
			dERROR = ADS1220SetGain(AdcInstance, Temp + ADS1220_GAIN_8);
			break;
		case 4:
			dERROR = ADS1220SetGain(AdcInstance, Temp + ADS1220_GAIN_16);
			break;
		case 5:
			dERROR = ADS1220SetGain(AdcInstance, Temp + ADS1220_GAIN_32);
			break;
		case 6:
			dERROR = ADS1220SetGain(AdcInstance, Temp + ADS1220_GAIN_64);
			break;
		case 7:
			dERROR = ADS1220SetGain(AdcInstance, Temp + ADS1220_GAIN_128);
			break;
		default:
			dERROR = ADS1220_ERROR;
			break;
		}
	if (dERROR==ADS1220_ERROR)
		set_ERROR();
}
void set_PGA_BYPASS(strcAdcINSTANCE *AdcInstance, char c)
{
	int buff = (int) c - 48;
	int dERROR;
	unsigned Temp;
	/* the PGA Bypass value is only part of the register, so we have to read it back
	   and massage the new value into it */
	ADS1220ReadRegister(AdcInstance, ADS1220_0_REGISTER, 0x01, &Temp);
	Temp &= 0xfe;									/* strip out old settings */
	/* Change PGA Bypass */
	switch(buff) {
		case 0:
			dERROR = ADS1220SetPGABypass(AdcInstance, Temp);
			break;
		case 1:
			dERROR = ADS1220SetPGABypass(AdcInstance, Temp + ADS1220_PGA_BYPASS);
			break;
		default:
			dERROR = ADS1220_ERROR;
			break;
	}
	if (dERROR==ADS1220_ERROR)
		set_ERROR();
}
void set_DR(strcAdcINSTANCE *AdcInstance, char c)
{
	int spd = (int) c - 48;
	int dERROR;
	unsigned Temp;
	/* the DataRate value is only part of the register, so we have to read it back
	   and massage the new value into it */
	ADS1220ReadRegister(AdcInstance, ADS1220_1_REGISTER, 0x01, &Temp);
	Temp &= 0x1f;									/* strip out old settings */
	/* Change Data rate */
	switch(spd) {
		case 0:
			dERROR = ADS1220SetDataRate(AdcInstance, Temp + ADS1220_DR_20);
			break;
		case 1:
			dERROR = ADS1220SetDataRate(AdcInstance, Temp + ADS1220_DR_45);
			break;
		case 2:
			dERROR = ADS1220SetDataRate(AdcInstance, Temp + ADS1220_DR_90);
			break;
		case 3:
			dERROR = ADS1220SetDataRate(AdcInstance, Temp + ADS1220_DR_175);
			break;
		case 4:
			dERROR = ADS1220SetDataRate(AdcInstance, Temp + ADS1220_DR_330);
			break;
		case 5:
			dERROR = ADS1220SetDataRate(AdcInstance, Temp + ADS1220_DR_600);
			break;
		case 6:
			dERROR = ADS1220SetDataRate(AdcInstance, Temp + ADS1220_DR_1000);
			break;
		case 7:
			dERROR = ADS1220SetDataRate(AdcInstance, Temp + ADS1220_DR_1000);
			break;
		default:
			dERROR = ADS1220_ERROR;
			break;
	}
	if (dERROR==ADS1220_ERROR)
		set_ERROR();
}
void set_MODE(strcAdcINSTANCE *AdcInstance, char c)
{
	int spd = (int) c - 48;
	int dERROR;
	unsigned Temp;
	/* the MODE value is only part of the register, so we have to read it back
	   and massage the new value into it */
	ADS1220ReadRegister(AdcInstance, ADS1220_1_REGISTER, 0x01, &Temp);
	Temp &= 0xe7;									/* strip out old settings */
	/* Change the operating Mode */
	switch(spd) {
		case 0:
			dERROR = ADS1220SetClockMode(AdcInstance, Temp + ADS1220_MODE_NORMAL);
			break;
		case 1:
			dERROR = ADS1220SetClockMode(AdcInstance, Temp + ADS1220_MODE_DUTY);
			break;
		case 2:
			dERROR = ADS1220SetClockMode(AdcInstance, Temp + ADS1220_MODE_TURBO);
			break;
		case 3:
			dERROR = ADS1220SetClockMode(AdcInstance, Temp + ADS1220_MODE_DCT);
			break;
		default:
			dERROR = ADS1220_ERROR;
			break;
	}
	if (dERROR==ADS1220_ERROR)
		set_ERROR();
}
void set_CM(strcAdcINSTANCE *AdcInstance, char c)
{
	int pwrdn = (int) c - 48;
	int dERROR;
	unsigned Temp;
	/* the Conversion Mode value is only part of the register, so we have to read it back
	   and massage the new value into it */
	ADS1220ReadRegister(AdcInstance, ADS1220_1_REGISTER, 0x01, &Temp);
	Temp &= 0xfb;									/* strip out old settings */
	/* Change power down mode */
	switch(pwrdn) {
		case 0:
			dERROR = ADS1220SetPowerDown(AdcInstance, Temp);
			break;
		case 1:
			dERROR = ADS1220SetPowerDown(AdcInstance, Temp + ADS1220_CC);
			break;
		default:
			dERROR = ADS1220_ERROR;
			break;
	}
	if (dERROR==ADS1220_ERROR)
		set_ERROR();
}
void set_TS(strcAdcINSTANCE *AdcInstance, char c)
{
	int tmp = (int) c - 48;
	int dERROR;
	unsigned Temp;
	/* the Temperature Sensor mode value is only part of the register, so we have to read it back
	   and massage the new value into it */
	ADS1220ReadRegister(AdcInstance, ADS1220_1_REGISTER, 0x01, &Temp);
	Temp &= 0xfd;									/* strip out old settings */
	/* Change Temp Diode Setting */
	switch(tmp) {
		case 0:
			dERROR = ADS1220SetTemperatureMode(AdcInstance, Temp);
			break;
		case 1:
			dERROR = ADS1220SetTemperatureMode(AdcInstance, Temp + ADS1220_TEMP_SENSOR);
			break;
		default:
			dERROR = ADS1220_ERROR;
			break;
	}
	if (dERROR==ADS1220_ERROR)
		set_ERROR();
}
void set_BCS(strcAdcINSTANCE *AdcInstance, char c)
{
	int bo = (int) c - 48;
	int dERROR;
	unsigned Temp;
	/* the Burnout Current Source value is only part of the register, so we have to read it back
	   and massage the new value into it */
	ADS1220ReadRegister(AdcInstance, ADS1220_1_REGISTER, 0x01, &Temp);
	Temp &= 0xfe;									/* strip out old settings */
	/* Change Burnout Current */
	switch(bo) {
		case 0:
			dERROR = ADS1220SetBurnOutSource(AdcInstance, Temp);
			break;
		case 1:
			dERROR = ADS1220SetBurnOutSource(AdcInstance, Temp + ADS1220_BCS);
			break;
		default:
			dERROR = ADS1220_ERROR;
			break;
	}
	if (dERROR==ADS1220_ERROR)
		set_ERROR();
}
void set_VREF(strcAdcINSTANCE *AdcInstance, char c)
{
	int ref = (int) c - 48;
	int dERROR;
	unsigned Temp;
	/* the Voltage Reference value is only part of the register, so we have to read it back
	   and massage the new value into it */
	ADS1220ReadRegister(AdcInstance, ADS1220_2_REGISTER, 0x01, &Temp);
	Temp &= 0x3f;									/* strip out old settings */
	/* Change Reference */
	switch(ref) {
		case 0:
			dERROR = ADS1220SetVoltageReference(AdcInstance, Temp + ADS1220_VREF_INT);
			break;
		case 1:
			dERROR = ADS1220SetVoltageReference(AdcInstance, Temp + ADS1220_VREF_EX_DED);
			break;
		case 2:
			dERROR = ADS1220SetVoltageReference(AdcInstance, Temp + ADS1220_VREF_EX_AIN);
			break;
		case 3:
			dERROR = ADS1220SetVoltageReference(AdcInstance, Temp + ADS1220_VREF_SUPPLY);
			break;
		default:
			dERROR = ADS1220_ERROR;
			break;
	}
	if (dERROR==ADS1220_ERROR)
		set_ERROR();
}
void set_50_60(strcAdcINSTANCE *AdcInstance, char c)
{
	int flt = (int) c - 48;
	int dERROR;
	unsigned Temp;
	/* the Digital Filter value is only part of the register, so we have to read it back
	   and massage the new value into it */
	ADS1220ReadRegister(AdcInstance, ADS1220_2_REGISTER, 0x01, &Temp);
	Temp &= 0xcf;									/* strip out old settings */
	/* Change Filter Setting */
	switch(flt) {
		case 0:
			dERROR = ADS1220Set50_60Rejection(AdcInstance, Temp + ADS1220_REJECT_OFF);
			break;
		case 1:
			dERROR = ADS1220Set50_60Rejection(AdcInstance, Temp + ADS1220_REJECT_BOTH);
			break;
		case 2:
			dERROR = ADS1220Set50_60Rejection(AdcInstance, Temp + ADS1220_REJECT_50);
			break;
		case 3:
			dERROR = ADS1220Set50_60Rejection(AdcInstance, Temp + ADS1220_REJECT_60);
			break;
		default:
			dERROR = ADS1220_ERROR;
			break;
	}
	if (dERROR==ADS1220_ERROR)
		set_ERROR();
}
void set_PSW(strcAdcINSTANCE *AdcInstance, char c)
{
	int sw = (int) c - 48;
	int dERROR;
	unsigned Temp;
	/* the Low-side Switch value is only part of the register, so we have to read it back
	   and massage the new value into it */
	ADS1220ReadRegister(AdcInstance, ADS1220_2_REGISTER, 0x01, &Temp);
	Temp &= 0xf7;									/* strip out old settings */
		/* Change low-side switch mode */
	switch(sw) {
		case 0:
			dERROR = ADS1220SetLowSidePowerSwitch(AdcInstance, Temp);
			break;
		case 1:
			dERROR = ADS1220SetLowSidePowerSwitch(AdcInstance, Temp + ADS1220_PSW_SW);
			break;
		default:
			dERROR = ADS1220_ERROR;
			break;
	}
	if (dERROR==ADS1220_ERROR)
		set_ERROR();
}
void set_IDAC(strcAdcINSTANCE *AdcInstance, char c)
{
	int current = (int) c - 48;
	int dERROR;
	unsigned Temp;
	/* the IDAC Current value is only part of the register, so we have to read it back
	   and massage the new value into it */
	ADS1220ReadRegister(AdcInstance, ADS1220_2_REGISTER, 0x01, &Temp);
	Temp &= 0xf8;									/* strip out old settings */
	/* Change IDAC Current Output */
	switch(current) {
		case 0:
			dERROR = ADS1220SetCurrentDACOutput(AdcInstance, Temp + ADS1220_IDAC_OFF);
			break;
		case 1:
#ifdef ADS1120
			dERROR = ADS1220SetCurrentDACOutput(AdcInstance, Temp + ADS1220_IDAC_OFF);
#else
			dERROR = ADS1220SetCurrentDACOutput(AdcInstance, Temp + ADS1220_IDAC_10);
#endif
			break;
		case 2:
			dERROR = ADS1220SetCurrentDACOutput(AdcInstance, Temp + ADS1220_IDAC_50);
			break;
		case 3:
			dERROR = ADS1220SetCurrentDACOutput(AdcInstance, Temp + ADS1220_IDAC_100);
			break;
		case 4:
			dERROR = ADS1220SetCurrentDACOutput(AdcInstance, Temp + ADS1220_IDAC_250);
			break;
		case 5:
			dERROR = ADS1220SetCurrentDACOutput(AdcInstance, Temp + ADS1220_IDAC_500);
			break;
		case 6:
			dERROR = ADS1220SetCurrentDACOutput(AdcInstance, Temp + ADS1220_IDAC_1000);
			break;
		case 7:
			dERROR = ADS1220SetCurrentDACOutput(AdcInstance, Temp + ADS1220_IDAC_2000);
			break;
		default:
			dERROR = ADS1220_ERROR;
			break;
		}
	if (dERROR==ADS1220_ERROR)
		set_ERROR();
}
void set_IMUX(strcAdcINSTANCE *AdcInstance, char c, int i)
{
	int mux = (int) c - 48;
	int dERROR;
	unsigned Temp;
	/* the IDAC Mux value is only part of the register, so we have to read it back
	   and massage the new value into it */
	ADS1220ReadRegister(AdcInstance, ADS1220_3_REGISTER, 0x01, &Temp);
	if (i==1) {
		Temp &= 0xe3;									/* strip out old settings */
		/* Change IDAC2 MUX Output */
		switch(mux) {
			case 0:
				Temp |= ADS1220_IDAC2_OFF;
				break;
			case 1:
				Temp |= ADS1220_IDAC2_AIN0;
				break;
			case 2:
				Temp |= ADS1220_IDAC2_AIN1;
				break;
			case 3:
				Temp |= ADS1220_IDAC2_AIN2;
				break;
			case 4:
				Temp |= ADS1220_IDAC2_AIN3;
				break;
			case 5:
				Temp |= ADS1220_IDAC2_REFP0;
				break;
			case 6:
				Temp |= ADS1220_IDAC2_REFN0;
				break;
			case 7:
				Temp |= ADS1220_IDAC2_REFN0;
				break;
			default:
				dERROR = ADS1220_ERROR;
				break;
		}
	}
	else {
		Temp &= 0x1f;
		/* Change IDAC1 MUX Output */
		switch(mux) {
			case 0:
				Temp |= ADS1220_IDAC1_OFF;
				break;
			case 1:
				Temp |= ADS1220_IDAC1_AIN0;
				break;
			case 2:
				Temp |= ADS1220_IDAC1_AIN1;
				break;
			case 3:
				Temp |= ADS1220_IDAC1_AIN2;
				break;
			case 4:
				Temp |= ADS1220_IDAC1_AIN3;
				break;
			case 5:
				Temp |= ADS1220_IDAC1_REFP0;
				break;
			case 6:
				Temp |= ADS1220_IDAC1_REFN0;
				break;
			case 7:
				Temp |= ADS1220_IDAC1_REFN0;
				break;
			default:
				dERROR = ADS1220_ERROR;
				break;
		}
	}
	if (dERROR==ADS1220_NO_ERROR)
		dERROR = ADS1220SetIDACRouting(AdcInstance, Temp);
	if (dERROR==ADS1220_ERROR)
		set_ERROR();
}
void set_DRDYM(strcAdcINSTANCE *AdcInstance, char c)
{
	int drdy = (int) c - 48;
	int dERROR;
	unsigned Temp;
	/* the DRDY output mode value is only part of the register, so we have to read it back
	   and massage the new value into it */
	ADS1220ReadRegister(AdcInstance, ADS1220_3_REGISTER, 0x01, &Temp);
	Temp &= 0xfd;									/* strip out old settings */
	/* Change DRDY Mode Setting */
	switch(drdy) {
		case 0:
			dERROR = ADS1220SetDRDYMode(AdcInstance, Temp);
			break;
		case 1:
			dERROR = ADS1220SetDRDYMode(AdcInstance, Temp + ADS1220_DRDY_MODE);
			break;
		default:
			dERROR = ADS1220_ERROR;
			break;
	}
	if (dERROR==ADS1220_ERROR)
		set_ERROR();
}
void set_ERROR(void)
{
	/* Add some error routine here is desired */
}


void AdcModuleADS1220(unsigned char ModuleNo)
{
	//unsigned char i, ModuleSeq=0;
	unsigned char ModuleSeq=0;
	unsigned char SequenceNo;
	//unsigned char ReadConfig;
	double dblValue;
	//static unsigned char Config = 6;
	static unsigned short State[2]= {0,0};

	#define ADS1220_SETUP_REG			0x05
	#define ADS1220_ENABLE_CHANNEL		0x0FFF
	#define ADS1220_INPUT_CONFIG_REG	0x0000

	//static unsigned short WaitCounter[2]= {0,0};
	static strcAdcINSTANCE AdcInstance[2];
	//static unsigned char RepeatNeed = 0;

	switch (ModuleNo)
		{
			case ADC_MODULE_NO_00:
					ModuleSeq=0;
					AdcInstance[ModuleSeq].ModuleSeq = 0;
					AdcInstance[ModuleSeq].SPIx = &hspi1;
					AdcInstance[ModuleSeq].EnableInput = ADS1220_ENABLE_CHANNEL;
					AdcInstance[ModuleSeq].InputConfigRegister = ADS1220_INPUT_CONFIG_REG;
					AdcInstance[ModuleSeq].SetupRegister = ADS1220_SETUP_REG;
					break;

			case ADC_MODULE_NO_01:
					ModuleSeq = 1;
					AdcInstance[ModuleSeq].ModuleSeq = 1;
					AdcInstance[ModuleSeq].SPIx = &hspi1;
					AdcInstance[ModuleSeq].EnableInput = ADS1220_ENABLE_CHANNEL;
					AdcInstance[ModuleSeq].InputConfigRegister = ADS1220_INPUT_CONFIG_REG;
					AdcInstance[ModuleSeq].SetupRegister = ADS1220_SETUP_REG;
					break;
		}


		if(ADC_Modules[ModuleNo].FirstRead )
			{
				ADC_Modules[ModuleNo].Channel     = 0;
				ADC_Modules[ModuleNo].NextChannel = 1;

				ADC_Modules[ModuleNo].FirstRead = 0;
			}

		SequenceNo = ADC_Modules[ModuleNo].Channel  + *Plc.Peripheral.AnalogInput.ModuleChannelPos[ModuleNo];

		switch(State[ModuleSeq])
			{
				case 0:
						ADS1220Config(&AdcInstance[ModuleSeq]);
						HAL_Delay(100);

						State[ModuleSeq] = 1;
					break;

				case 1:

					AdcInstance->ChannelSeqNo = AdcInstance->ChannelSeqNo + 1;
					if(AdcInstance->ChannelSeqNo >= 4)
						{
							AdcInstance->ChannelSeqNo = 0;
						}
					ADC_Modules[ModuleNo].Channel = AdcInstance->ChannelSeqNo;

						ADS1220Channel(&AdcInstance[ModuleSeq]);
						State[ModuleSeq] = 2;
					break;

				case 2:
					if(ADS1220EOC(&AdcInstance[ModuleSeq]))
						{
							ADC_Modules[ModuleSeq].Status = ADC_DATA_STATUS_WILL_BE_READ;
							State[ModuleSeq] = 3;
						}
					break;

				case 3:

					 	ADS1220ReadData(&AdcInstance[ModuleSeq]);
					 	SequenceNo = ADC_Modules[ModuleNo].Channel  + *Plc.Peripheral.AnalogInput.ModuleChannelPos[ModuleNo];

						dblValue = AdcInstance[ModuleSeq].lAdcValue;
						dblValue = dblValue * *Plc.Peripheral.AnalogInput.ModuleResolutionMultiplier[ModuleNo] / 1000;

						*Plc.Peripheral.AnalogInput.AnalogValue[SequenceNo] = dblValue;

						ChannelValueCalculate(SequenceNo, *Plc.Peripheral.AnalogInput.AnalogValue[SequenceNo]);

						State[ModuleSeq] = 1;
					break;

			}
}

