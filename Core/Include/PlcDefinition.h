//* Date            :31.03.2021 10:51:46  *// 
//* ****                           ***** */
//* **** Plc Definition      ***** */
//* ****                           ***** */

//* ****                           ***** */
//* **** Project                ***** */
//* ****                           ***** */
//* ****                                      ***** */
//* **** Plc Program Revision       ***** */
//* ****                                      ***** */
#define   DTechCompileRevision                              5379
#define   PlcProgramRevision                                "MD200CPU32F407-LQP100-202208" // 2021033110
//* ****                           ***** */
//* ****     Project               ***** */
//* ****                           ***** */
//* Name   : Decos REF STM32 F4-F1 PANEL BP *// 
//* Date            :31.03.2021 10:51:47  *// 
//* ****                                                  ***** */
//* ****                Xml File Definition               ***** */
//* ****                                                  ***** */
//* ****                                                  ***** */
//* ****                   Plc Variable                   ***** */
//* ****                                                  ***** */
    #define   LENGTH_OF_INTEGER                                                4                                                                               // 0
    #define   LENGTH_OF_SHORT                                                  2                                                                               // 0
    #define   UART_PORT_COUNT                                                  7                                                                               // 0
    #define   RETURN                                                           13                                                                              // 
    #define   LINEFEED                                                         10                                                                              // 
    #define   EOS                                                              0                                                                               // 
    #define   YES                                                              1                                                                               // 
    #define   NO                                                               0                                                                               // 
    #define   NOCRCCHECK                                                       0                                                                               // 
    #define   TX_BUFFER                                                        -1                                                                              // 
    #define   GSM_ENABLE                                                       0                                                                               // 
    #define   ONEWRIRE_ENABLE                                                  1                                                                               // 

//* ****                                                  ***** */
//* ****                    Digital IO                    ***** */
//* ****                                                  ***** */
//* ****                                                  ***** */
//* ****                   Analog Input                   ***** */
//* ****                                                  ***** */
    #define   AI_CALIBRATION_CONSTANT                              	 			1000000
    #define   AI_RxGAIN_CONSTANT                                    			1000
    #define   AI_MODULE_COUNT                                        			8
	#define   MODULE_SLOT_COUNT													2
	#define   AI_READ_COUNT														8
	#define   AI_CHANNEL_COUNT                                      			16
    #define   CHANNEL_VALUE_SEQ_COUNT                                      		16
    #define   PLC_LADDER_AI_CHANNEL_TYPE_COUNT                                 	8
    #define   AI_4_20mA                                                        	1

	#define   MAX_KALMAN_LEN 						                            250
//

//* ****                                                  ***** */
//* ****                  Analog Output                   ***** */
//* ****                                                  ***** */
    #define   PLC_LADDER_AO_CALIBRATION_CONSTANT                               1                                                                               // 0
    #define   PLC_LADDER_AO_CHANNEL_CONFIG_SIZE                                8                                                                               // 0
    #define   PLC_LADDER_AO_BOARD_COUNT                                        8                                                                               // 0
    #define   PLC_LADDER_AO_CHANNEL_COUNT                                      4                                                                               // 0
//* ****                                                  ***** */
//* ****                    Serial Port                   ***** */
//* ****                                                  ***** */
    #define   MODBUS_COM_PORT                                                  1                                                                               // 
    #define   MODBUS_COM_PORT_2                                                2                                                                               // 
    #define   MODBUS_COM_PORT_3                                                3                                                                               // 
    #define   TCP_UDP_USART_NO                                                 3                                                                               // 
    #define   MODBUS_EXT_DATA_USART_NO                                         1                                                                               // 
    #define   VR_COM_PORT                                                      1                                                                               // Veeder Root Communication Port
//* ****                                                  ***** */
//* ****                  GSM / TCP_UDP                   ***** */
//* ****                                                  ***** */
    #define   GSM_MODEM_PORT                                                   1                                                                               // Usart 1
    #define   SMS_COUNT                                                        10                                                                              // 0
    #define   MAX_LENGTH_OF_SMS                                                64                                                                              // 
    #define   TCP_UDP_PORT                                                     3                                                                               // Usart 3
//* ****                                                  ***** */
//* ****                   Master Codes                   ***** */
//* ****                                                  ***** */
    #define   LENGTH_OF_MASTERCODE                                             8                                                                               // 0
    #define   MASTER_CODE_COUNT                                                8                                                                              // 0
//* ****                                                  ***** */
//* ****                    Timer Nos                     ***** */
//* ****                                                  ***** */
//    #define   TIMER_PROGRAM_RUN                                                1                                                                               //
//    #define   TIMER_PLC_RESET                                                  2                                                                               //
//    #define   TIMER_HMI_TANK_DATA                                              3                                                                               //
//    #define   TIMER_PUMP_REIODICALLY_RUN                                       4                                                                               //
//    #define   TIMER_TANK_FILLING                                               5                                                                               //
//    #define   TIMER_START_BUTTON                                               6                                                                               //
//    #define   TIMER_DATA_SEND                                                  7                                                                               //
//    #define   TIMER_MODBUS_DATA_READ                                           8                                                                               //
//    #define   TIMER_TANK_NEXT_TO_EO_FILLING                                    9                                                                               //
//    #define   TIMER_HMI_DATA_SAVE                                              10                                                                              //
//    #define   TIMER_LEVEL_MIN_UP_IN_FUELING                                    11                                                                              //
//    #define   TIMER_TANK1_STANDART_DEVIATION                                   12                                                                              //
//    #define   TIMER_TANK2_STANDART_DEVIATION                                   13                                                                              //
//    #define   TIMER_VR_DATA_READ                                               14                                                                              //
//    #define   TIMER_ETHERNET_RESET                                             15                                                                              //

#define	RTC_CONTROL_UPDATE_BIT_NO 	                                           0

#define EEPROM_NO_00											0x00
#define EEPROM_NO_01											0x01


