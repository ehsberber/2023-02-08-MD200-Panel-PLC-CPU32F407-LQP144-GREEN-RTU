/*
 * ADS_1220.h
 *
 *  Created on: Nov 15, 2022
 *      Author: Sezgin Berber
 */
#include "MicroPeripheral.h"
#include "Registers.h"

#ifndef INCLUDE_ADS_1220_H_
#define INCLUDE_ADS_1220_H_

	/* Definition of GPIO Port Bits Used for Communication */
	/* P1.2 */
	#define ADS1220_CS      	0x04
	/* P3.3  */
	#define ADS1220_DIN     	0x08
	/* P3.4 */
	#define ADS1220_DOUT    	0x10
	/* P2.6 */
	#define ADS1220_DRDY    	0x40
	/* P2.7 */
	#define ADS1220_SCLK    	0x80
	/* Error Return Values */
	#define ADS1220_NO_ERROR        0
	#define ADS1220_ERROR			-1
	/* Command Definitions */
	#define ADS1220_CMD_RDATA    	0x10
	#define ADS1220_CMD_RREG     	0x20
	#define ADS1220_CMD_WREG     	0x40
	#define ADS1220_CMD_SYNC    	0x08
	#define ADS1220_CMD_SHUTDOWN    0x02
	#define ADS1220_CMD_RESET    	0x06

	/* ADS1220 Register Definitions */
	#define ADS1220_0_REGISTER   	0x00
	#define ADS1220_1_REGISTER     	0x01
	#define ADS1220_2_REGISTER     	0x02
	#define ADS1220_3_REGISTER    	0x03

	/* ADS1220 Register 0 Definition */
	/*   Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0
	//--------------------------------------------------------------------------------------------
	//                     MUX [3:0]                 |             GAIN[2:0]             | PGA_BYPASS
	*/
	/* Define MUX */

	#define ADS1220_MUX_0_1   	0x00
	#define ADS1220_MUX_0_2   	0x10
	#define ADS1220_MUX_0_3   	0x20
	#define ADS1220_MUX_1_2   	0x30
	#define ADS1220_MUX_1_3   	0x40
	#define ADS1220_MUX_2_3   	0x50
	#define ADS1220_MUX_1_0   	0x60
	#define ADS1220_MUX_3_2   	0x70
	#define ADS1220_MUX_0_G		0x80
	#define ADS1220_MUX_1_G   	0x90
	#define ADS1220_MUX_2_G   	0xA0
	#define ADS1220_MUX_3_G   	0xB0
	#define ADS1220_MUX_EX_VREF 0xC0
	#define ADS1220_MUX_AVDD   	0xD0
	#define ADS1220_MUX_DIV2   	0xE0
	/* Define GAIN */
	#define ADS1220_GAIN_1      0x00
	#define ADS1220_GAIN_2      0x02
	#define ADS1220_GAIN_4      0x04
	#define ADS1220_GAIN_8      0x06
	#define ADS1220_GAIN_16     0x08
	#define ADS1220_GAIN_32     0x0A
	#define ADS1220_GAIN_64     0x0C
	#define ADS1220_GAIN_128    0x0E
	/* Define PGA_BYPASS */
	#define ADS1220_PGA_BYPASS 	0x01
	/* ADS1220 Register 1 Definition */
	/*   Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0
	//--------------------------------------------------------------------------------------------
	//                DR[2:0]            |      MODE[1:0]        |     CM    |     TS    |    BCS
	*/
	/* Define DR (data rate) */
	#define ADS1220_DR_20		0x00
	#define ADS1220_DR_45		0x20
	#define ADS1220_DR_90		0x40
	#define ADS1220_DR_175		0x60
	#define ADS1220_DR_330		0x80
	#define ADS1220_DR_600		0xA0
	#define ADS1220_DR_1000		0xC0
	/* Define MODE of Operation */
	#define ADS1220_MODE_NORMAL 0x00
	#define ADS1220_MODE_DUTY	0x08
	#define ADS1220_MODE_TURBO 	0x10
	#define ADS1220_MODE_DCT	0x18
	/* Define CM (conversion mode) */
	#define ADS1220_CC			0x04
	/* Define TS (temperature sensor) */
	#define ADS1220_TEMP_SENSOR	0x02
	/* Define BCS (burnout current source) */
	#define ADS1220_BCS			0x01
	/* ADS1220 Register 2 Definition */
	/*   Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0
	//--------------------------------------------------------------------------------------------
	//         VREF[1:0]     |        50/60[1:0]     |    PSW    |             IDAC[2:0]
	*/
	/* Define VREF */
	#define ADS1220_VREF_INT	0x00
	#define ADS1220_VREF_EX_DED	0x40
	#define ADS1220_VREF_EX_AIN	0x80
	#define ADS1220_VREF_SUPPLY	0xc0
	/* Define 50/60 (filter response) */
	#define ADS1220_REJECT_OFF	0x00
	#define ADS1220_REJECT_BOTH	0x10
	#define ADS1220_REJECT_50	0x20
	#define ADS1220_REJECT_60	0x30
	/* Define PSW (low side power switch) */
	#define ADS1220_PSW_SW		0x08
	/* Define IDAC (IDAC current) */
	#define ADS1220_IDAC_OFF	0x00
	#define ADS1220_IDAC_10		0x01
	#define ADS1220_IDAC_50		0x02
	#define ADS1220_IDAC_100	0x03
	#define ADS1220_IDAC_250	0x04
	#define ADS1220_IDAC_500	0x05
	#define ADS1220_IDAC_1000	0x06
	#define ADS1220_IDAC_2000	0x07

	/* ADS1220 Register 3 Definition */
	/*   Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0
	//--------------------------------------------------------------------------------------------
	//               I1MUX[2:0]          |               I2MUX[2:0]          |   DRDYM   | RESERVED
	*/
	/* Define I1MUX (current routing) */

	#define ADS1220_IDAC1_OFF	0x00
	#define ADS1220_IDAC1_AIN0	0x20
	#define ADS1220_IDAC1_AIN1	0x40
	#define ADS1220_IDAC1_AIN2	0x60
	#define ADS1220_IDAC1_AIN3	0x80
	#define ADS1220_IDAC1_REFP0	0xa0
	#define ADS1220_IDAC1_REFN0	0xc0
	/* Define I2MUX (current routing) */
	#define ADS1220_IDAC2_OFF	0x00
	#define ADS1220_IDAC2_AIN0	0x04
	#define ADS1220_IDAC2_AIN1	0x08
	#define ADS1220_IDAC2_AIN2	0x0c
	#define ADS1220_IDAC2_AIN3	0x10
	#define ADS1220_IDAC2_REFP0	0x14
	#define ADS1220_IDAC2_REFN0	0x18
	/* define DRDYM (DOUT/DRDY behaviour) */
	#define ADS1220_DRDY_MODE	0x02
	/* Low Level ADS1220 Device Functions */
	void ADS1220Init(void);							/* Device initialization */
	int ADS1220WaitForDataReady(int Timeout);		/* DRDY polling */
	void ADS1220AssertCS(int fAssert);				/* Assert/deassert CS */
	void ADS1220SendByte(unsigned char cData );		/* Send byte to the ADS1220 */
	unsigned char ADS1220ReceiveByte(void);			/* Receive byte from the ADS1220 */
	/* ADS1220 Higher Level Functions */
	long ADS1220ReadData(strcAdcINSTANCE *AdcInstance);						/* Read the data results */
	void ADS1220ReadRegister(strcAdcINSTANCE *AdcInstance,int StartAddress, int NumRegs, unsigned * pData);	/* Read the register(s) */
	void ADS1220WriteRegister(strcAdcINSTANCE *AdcInstance,int StartAddress, int NumRegs, unsigned * pData); /* Write the register(s) */
	void ADS1220SendResetCommand(strcAdcINSTANCE *AdcInstance);				/* Send a device Reset Command */
	void ADS1220SendStartCommand(strcAdcINSTANCE *AdcInstance);				/* Send a Start/SYNC command */
	void ADS1220SendShutdownCommand(strcAdcINSTANCE *AdcInstance);			/* Place the device in powerdown mode */
	/* Register Set Value Commands */
	void ADS1220Config(strcAdcINSTANCE *AdcInstance);
	int ADS1220SetChannel(strcAdcINSTANCE *AdcInstance, int Mux);
	int ADS1220SetGain(strcAdcINSTANCE *AdcInstance, int Gain);
	int ADS1220SetPGABypass(strcAdcINSTANCE *AdcInstance, int Bypass);
	int ADS1220SetDataRate(strcAdcINSTANCE *AdcInstance, int DataRate);
	int ADS1220SetClockMode(strcAdcINSTANCE *AdcInstance, int ClockMode);
	int ADS1220SetPowerDown(strcAdcINSTANCE *AdcInstance, int PowerDown);
	int ADS1220SetTemperatureMode(strcAdcINSTANCE *AdcInstance, int TempMode);
	int ADS1220SetBurnOutSource(strcAdcINSTANCE *AdcInstance, int BurnOut);
	int ADS1220SetVoltageReference(strcAdcINSTANCE *AdcInstance, int VoltageRef);
	int ADS1220Set50_60Rejection(strcAdcINSTANCE *AdcInstance, int Rejection);
	int ADS1220SetLowSidePowerSwitch(strcAdcINSTANCE *AdcInstance, int PowerSwitch);
	int ADS1220SetCurrentDACOutput(strcAdcINSTANCE *AdcInstance, int CurrentOutput);
	int ADS1220SetIDACRouting(strcAdcINSTANCE *AdcInstance, int IDACRoute);
	int ADS1220SetDRDYMode(strcAdcINSTANCE *AdcInstance, int DRDYMode);
	/* Register Get Value Commands */
	int ADS1220GetChannel(strcAdcINSTANCE *AdcInstance);
	int ADS1220GetGain(strcAdcINSTANCE *AdcInstance);
	int ADS1220GetPGABypass(strcAdcINSTANCE *AdcInstance);
	int ADS1220GetDataRate(strcAdcINSTANCE *AdcInstance);
	int ADS1220GetClockMode(strcAdcINSTANCE *AdcInstance);
	int ADS1220GetPowerDown(strcAdcINSTANCE *AdcInstance);
	int ADS1220GetTemperatureMode(strcAdcINSTANCE *AdcInstance);
	int ADS1220GetBurnOutSource(strcAdcINSTANCE *AdcInstance);
	int ADS1220GetVoltageReference(strcAdcINSTANCE *AdcInstance);
	int ADS1220Get50_60Rejection(strcAdcINSTANCE *AdcInstance);
	int ADS1220GetLowSidePowerSwitch(strcAdcINSTANCE *AdcInstance);
	int ADS1220GetCurrentDACOutput(strcAdcINSTANCE *AdcInstance);
	int ADS1220GetIDACRouting(strcAdcINSTANCE *AdcInstance, int WhichOne);
	int ADS1220GetDRDYMode(strcAdcINSTANCE *AdcInstance);
	/* Useful Functions within Main Program for Setting Register Contents
	*
	*  	These functions show the programming flow based on the header definitions.
	*  	The calls are not made within the demo example, but could easily be used by calling the function
	*  		defined within the program to complete a fully useful program.
	*	Similar function calls were made in the firmware design for the ADS1220EVM.
	*
	*  The following function calls use ASCII data sent from a COM port to control settings
	*	on the ADS1220.  The data is reconstructed from ASCII and then combined with the
	*	register contents to save as new configuration settings.
	*
	* 	Function names correspond to datasheet register definitions
	*/
	void set_MUX(strcAdcINSTANCE *AdcInstance, char c);
	void set_GAIN(strcAdcINSTANCE *AdcInstance, char c);
	void set_PGA_BYPASS(strcAdcINSTANCE *AdcInstance, char c);
	void set_DR(strcAdcINSTANCE *AdcInstance, char c);
	void set_MODE(strcAdcINSTANCE *AdcInstance, char c);
	void set_CM(strcAdcINSTANCE *AdcInstance, char c);
	void set_TS(strcAdcINSTANCE *AdcInstance, char c);
	void set_BCS(strcAdcINSTANCE *AdcInstance, char c);
	void set_VREF(strcAdcINSTANCE *AdcInstance, char c);
	void set_50_60(strcAdcINSTANCE *AdcInstance, char c);
	void set_PSW(strcAdcINSTANCE *AdcInstance, char c);
	void set_IDAC(strcAdcINSTANCE *AdcInstance, char c);
	void set_IMUX(strcAdcINSTANCE *AdcInstance, char c, int i);
	void set_DRDYM(strcAdcINSTANCE *AdcInstance, char c);
	void set_ERROR(void);
	void AdcModuleADS1220(unsigned char ModuleNo);

#endif /* INCLUDE_ADS_1220_H_ */
