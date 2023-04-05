#include "MicroPeripheral.h"
#include "DigitalOutputMicroLayer.h" 


void DigitalOutputWriteToMicroPort(unsigned short OutputData)
{
	//unsigned char OutputPosition=0;
	unsigned char i;
 
	//
	// MicroControler �zerindeki Portlar Kullaniliyor
	//					
	//Registers.Coil[OutputPosition] = ( ~Registers.Holding[HA_DO_MASTER +  (OutputPosition * 2) ] & Registers.Coil[OutputPosition ] ) | Registers.Holding[HA_DO_MASTER + (OutputPosition  * 2) + 1];
	//
	// ON BOARD OUTPUT PIN 
	//
	for(i=0;i<16;i++)
		{
		 		switch(i)
					{
						case 0:
									if (OutputData & (1 << i))
										HAL_GPIO_WritePin(PLC_ONBOARD_DO_0_PORT, PLC_ONBOARD_DO_0_PIN, GPIO_PIN_SET);
									else
										HAL_GPIO_WritePin(PLC_ONBOARD_DO_0_PORT, PLC_ONBOARD_DO_0_PIN, GPIO_PIN_RESET);
								break;
						case 1:
									if (OutputData & (1 << i))  HAL_GPIO_WritePin(PLC_ONBOARD_DO_1_PORT, PLC_ONBOARD_DO_1_PIN, GPIO_PIN_SET);	else HAL_GPIO_WritePin(PLC_ONBOARD_DO_1_PORT, PLC_ONBOARD_DO_1_PIN, GPIO_PIN_RESET);
								break;

						case 2:
									if (OutputData & (1 << i))  HAL_GPIO_WritePin(PLC_ONBOARD_DO_2_PORT, PLC_ONBOARD_DO_2_PIN, GPIO_PIN_SET);	else HAL_GPIO_WritePin(PLC_ONBOARD_DO_2_PORT, PLC_ONBOARD_DO_2_PIN, GPIO_PIN_RESET);
								break;

						case 3:
									if (OutputData & (1 << i))  HAL_GPIO_WritePin(PLC_ONBOARD_DO_3_PORT, PLC_ONBOARD_DO_3_PIN, GPIO_PIN_SET);	else HAL_GPIO_WritePin(PLC_ONBOARD_DO_3_PORT, PLC_ONBOARD_DO_3_PIN, GPIO_PIN_RESET);
								break;

						
						case 4:
									if (OutputData & (1 << i))  HAL_GPIO_WritePin(PLC_ONBOARD_DO_4_PORT, PLC_ONBOARD_DO_4_PIN, GPIO_PIN_SET);	else HAL_GPIO_WritePin(PLC_ONBOARD_DO_4_PORT, PLC_ONBOARD_DO_4_PIN, GPIO_PIN_RESET);
								break;

						case 5:
									if (OutputData & (1 << i))  HAL_GPIO_WritePin(PLC_ONBOARD_DO_5_PORT, PLC_ONBOARD_DO_5_PIN, GPIO_PIN_SET);	else HAL_GPIO_WritePin(PLC_ONBOARD_DO_5_PORT, PLC_ONBOARD_DO_5_PIN, GPIO_PIN_RESET);
								break;
								
						case 6:
									if (OutputData & (1 << i))  HAL_GPIO_WritePin(PLC_ONBOARD_DO_6_PORT, PLC_ONBOARD_DO_6_PIN, GPIO_PIN_SET);	else HAL_GPIO_WritePin(PLC_ONBOARD_DO_6_PORT, PLC_ONBOARD_DO_6_PIN, GPIO_PIN_RESET);
								break;
								
						case 7:
									if (OutputData & (1 << i))  HAL_GPIO_WritePin(PLC_ONBOARD_DO_7_PORT, PLC_ONBOARD_DO_7_PIN, GPIO_PIN_SET);	else HAL_GPIO_WritePin(PLC_ONBOARD_DO_7_PORT, PLC_ONBOARD_DO_7_PIN, GPIO_PIN_RESET);
								break;							


						case 8:
									if (OutputData & (1 << i))  HAL_GPIO_WritePin(PLC_ONBOARD_DO_8_PORT, PLC_ONBOARD_DO_8_PIN, GPIO_PIN_SET);	else HAL_GPIO_WritePin(PLC_ONBOARD_DO_8_PORT, PLC_ONBOARD_DO_8_PIN, GPIO_PIN_RESET);
								break;	

						case 9:
									if (OutputData & (1 << i))  HAL_GPIO_WritePin(PLC_ONBOARD_DO_9_PORT, PLC_ONBOARD_DO_9_PIN, GPIO_PIN_SET);	else HAL_GPIO_WritePin(PLC_ONBOARD_DO_9_PORT, PLC_ONBOARD_DO_9_PIN, GPIO_PIN_RESET);
								break;	

						case 10:
									if (OutputData & (1 << i))  HAL_GPIO_WritePin(PLC_ONBOARD_DO_10_PORT, PLC_ONBOARD_DO_10_PIN, GPIO_PIN_SET);	else HAL_GPIO_WritePin(PLC_ONBOARD_DO_10_PORT, PLC_ONBOARD_DO_10_PIN, GPIO_PIN_RESET);
								break;	

						case 11:
									if (OutputData & (1 << i))  HAL_GPIO_WritePin(PLC_ONBOARD_DO_11_PORT, PLC_ONBOARD_DO_11_PIN, GPIO_PIN_SET );	else HAL_GPIO_WritePin(PLC_ONBOARD_DO_11_PORT, PLC_ONBOARD_DO_11_PIN, GPIO_PIN_RESET);
								break;	

						case 12:
									if (OutputData & (1 << i))  HAL_GPIO_WritePin(PLC_ONBOARD_DO_12_PORT, PLC_ONBOARD_DO_12_PIN, GPIO_PIN_SET);	else HAL_GPIO_WritePin(PLC_ONBOARD_DO_12_PORT, PLC_ONBOARD_DO_12_PIN, GPIO_PIN_RESET);
								break;	
								
						case 13:
									if (OutputData & (1 << i))  HAL_GPIO_WritePin(PLC_ONBOARD_DO_13_PORT, PLC_ONBOARD_DO_13_PIN, GPIO_PIN_SET);	else HAL_GPIO_WritePin(PLC_ONBOARD_DO_13_PORT, PLC_ONBOARD_DO_13_PIN, GPIO_PIN_RESET);
								break;	

						case 14:
									if (OutputData & (1 << i))  HAL_GPIO_WritePin(PLC_ONBOARD_DO_14_PORT, PLC_ONBOARD_DO_14_PIN, GPIO_PIN_SET);	else HAL_GPIO_WritePin(PLC_ONBOARD_DO_14_PORT, PLC_ONBOARD_DO_14_PIN, GPIO_PIN_RESET);
								break;	

						case 15:
									if (OutputData & (1 << i))  HAL_GPIO_WritePin(PLC_ONBOARD_DO_15_PORT, PLC_ONBOARD_DO_15_PIN, GPIO_PIN_SET);	else HAL_GPIO_WritePin(PLC_ONBOARD_DO_15_PORT, PLC_ONBOARD_DO_15_PIN, GPIO_PIN_RESET);
								break;
					}

		}
}

