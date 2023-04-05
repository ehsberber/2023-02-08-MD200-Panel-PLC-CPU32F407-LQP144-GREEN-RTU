//* ****                           ***** */
//* ****     Project               ***** */
//* ****                           ***** */
//* Name   : Decos REF STM32 F4-F1 PANEL BP *// 
//* Date            :31.03.2021 10:51:48  *// 
//* ****                                                  ***** */
//* ****              Status Register Address             ***** */
//* ****                                                  ***** */
//* ****                                                  ***** */
//* ****              SYSTEM_CONFIG_REGISTER              ***** */
//* ****                                                  ***** */
//* ****                                                  ***** */
//* ****                Micro Port Number                 ***** */
//* ****                                                  ***** */
    #define   PORTA                                                            0                                                                               // 
    #define   PORTB                                                            1                                                                               // 
    #define   PORTC                                                            2                                                                               // 
    #define   PORTD                                                            3                                                                               // 
    #define   PORTE                                                            4                                                                               // 
    #define   PORTF                                                            5                                                                               // 
    #define   PORTG                                                            6                                                                               // 
    #define   PORTH                                                            7                                                                               // 
//* ****                                                  ***** */
//* ****              Micro Control Register              ***** */
//* ****                                                  ***** */
    #define   RCC_APB2ENR                                                      0x0000007D                                                                      // 
    #define   GPIOA_CRL_AND                                                    0xFFFFFFF0                                                                      // 
    #define   GPIOA_CRL_OR                                                     0x00000003                                                                      // 
    #define   GPIOA_CRH_AND                                                    0x00000000                                                                      // 
    #define   GPIOA_CRH_OR                                                     0x00000000                                                                      // 
    #define   GPIOB_CRL_AND                                                    0xFFFFF000                                                                      // 
    #define   GPIOB_CRL_OR                                                     0xFF000333                                                                      // 
    #define   GPIOB_CRH_AND                                                    0x0000FFFF                                                                      // 
    #define   GPIOB_CRH_OR                                                     0x3344FF00                                                                      // 
    #define   GPIOC_CRL_AND                                                    0x00000000                                                                      // 
    #define   GPIOC_CRL_OR                                                     0x00000000                                                                      // 
    #define   GPIOC_CRH_AND                                                    0xFFF0FFF0                                                                      // 
    #define   GPIOC_CRH_OR                                                     0x00030003                                                                      // 
    #define   GPIOD_CRL_AND                                                    0x00000000                                                                      // 
    #define   GPIOD_CRL_OR                                                     0x33333333                                                                      // 
    #define   GPIOD_CRH_AND                                                    0x00000000                                                                      // 
    #define   GPIOD_CRH_OR                                                     0x33333333                                                                      // 
    #define   GPIOE_CRL_AND                                                    0x00000000                                                                      // 
    #define   GPIOE_CRL_OR                                                     0x33333333                                                                      // 
    #define   GPIOE_CRH_AND                                                    0x00000000                                                                      // 
    #define   GPIOE_CRH_OR                                                     0x44444444                                                                      // 
    #define   GPIOF_CRL_AND                                                    0x00000000                                                                      // 
    #define   GPIOF_CRL_OR                                                     0x33333333                                                                      // 
    #define   GPIOF_CRH_AND                                                    0x00000000                                                                      // 
    #define   GPIOF_CRH_OR                                                     0x33333333                                                                      // 
//* ****                                                  ***** */
//* ****             System Usart Port Config             ***** */
//* ****                                                  ***** */
    #define   _USART_SETUP                                                     0x01                                                                            // 
    #define   _USART_USED                                                      0x07                                                                            // 
    #define   _USART_INTERRUPTS                                                0x07                                                                            // 
    #define   _USART1_REMAP                                                    0x00000000                                                                      // 
    #define   _USART1_CR1                                                      0x00000020                                                                      // 
    #define   _USART1_CR2                                                      0x00000000                                                                      // 
    #define   _USART1_CR3                                                      0x00000000                                                                      // 
    #define   _USART1_BAUDRATE                                                 19200                                                                           // 
    #define   _USART1_DATABITS                                                 0x00000000                                                                      // 
    #define   _USART1_STOPBITS                                                 0x00000000                                                                      // 
    #define   _USART1_PARITY                                                   0x00000000                                                                      // 
    #define   _USART1_FLOWCTRL                                                 0x00000000                                                                      // 
    #define   _USART2_REMAP                                                    0x00000000                                                                      // 
    #define   _USART2_CR1                                                      0x00000020                                                                      // 
    #define   _USART2_CR2                                                      0x00000000                                                                      // 
    #define   _USART2_CR3                                                      0x00000000                                                                      // 
    #define   _USART2_BAUDRATE                                                 115200                                                                          // 
    #define   _USART2_DATABITS                                                 0x00000000                                                                      // 
    #define   _USART2_STOPBITS                                                 0x00000000                                                                      // 
    #define   _USART2_PARITY                                                   0x00000000                                                                      // 
    #define   _USART2_FLOWCTRL                                                 0x00000000                                                                      // 
    #define   _USART3_REMAP                                                    0x00000010                                                                      // 
    #define   _USART3_CR1                                                      0x00000020                                                                      // 
    #define   _USART3_CR2                                                      0x00000000                                                                      // 
    #define   _USART3_CR3                                                      0x00000000                                                                      // 
    #define   _USART3_BAUDRATE                                                 9600                                                                            // 
    #define   _USART3_DATABITS                                                 0x00000000                                                                      // 
    #define   _USART3_STOPBITS                                                 0x00000000                                                                      // 
    #define   _USART3_PARITY                                                   0x00000000                                                                      // 
    #define   _USART3_FLOWCTRL                                                 0x00000000                                                                      // 
    #define   _USART4_REMAP                                                    0x00000000                                                                      // 
    #define   _USART4_CR1                                                      0x00000020                                                                      // 
    #define   _USART4_CR2                                                      0x00000000                                                                      // 
    #define   _USART4_CR3                                                      0x00000000                                                                      // 
    #define   _USART4_BAUDRATE                                                 115200                                                                          // 
    #define   _USART4_DATABITS                                                 0x00000000                                                                      // 
    #define   _USART4_STOPBITS                                                 0x00000000                                                                      // 
    #define   _USART4_PARITY                                                   0x00000000                                                                      // 
    #define   _USART4_FLOWCTRL                                                 0x00000000                                                                      // 
//* ****                                                  ***** */
//* ****              SYSTEM_STATUS_REGISTER              ***** */
//* ****                                                  ***** */

//* ****                                                  ***** */
//* ****                   Plc Revision                   ***** */
//* ****                                                  ***** */
#define   SA_REVISION                                                      	0x0010


//* ****                                                  ***** */
//* ****       Control , Input Parameters, Accuracy       ***** */
//* ****                                                  ***** */
#define   SA_MASTER_CONTROL                                                	0x0020
#define   SA_SYSTEM_INDICATOR                                              	0x0040
#define   SA_SYSTEM_WARNING													0x0044

#define SA_PLC_STATUS                                                    	0x0050
//    #define   BN_PLC_STATUS_START                                        		0
//    #define   BN_PLC_STATUS_DATA_RECEIVED                                   	1
//    #define   BN_PLC_STATUS_AUTOMODE                                            2
//    #define   BN_PLC_STATUS_ILLEGAL_FUELING                                     6
//    #define   BN_PLC_STATUS_PERSONEL_ID                                         7
//    #define   BN_PLC_STATUS_ALERT_INPROGRESS                                    8
//    #define   BN_PLC_STATUS_VEDEER_ROOT_COMM                                    9

#define   SA_DO_STATUS                                                     	0x0060
#define   SA_DO_STATUS_LAST                                                	0x006C

#define   SA_DI_STATE                                                     	0x0080
#define   SA_DI_STATE_LAST                                                	0x008C


#define	  SA_PLC_WARNING													0x00A0
#define   SA_INPUT_PARAMETER_SAVE_00                                       	0x0100
#define   SA_INPUT_PARAMETER_SAVE_01                                       	0x0200                                                           //

//* ****                                                  ***** */
//* ****                    RTC, Timers                   ***** */
//* ****                                                  ***** */



#define	SA_ILLEGAL_FUELING													0x0300

#define	SA_TANK_FILLING_STATUS												0x0308
#define SA_TANK_DEVIATION_STATUS											0x030A

#define SA_TOTAL_LEVEL_CURRENT												0x0310
#define SA_TANK_DEVIATION_DIFFERANCE										0x0320
#define SA_TANK_DEVIATION_PERCENT											0x0330

#define   SA_RTC_DATA                                                      	0x0400                                                           //
#define   SA_RTC_CONTROL                                                   	0x0420                                                           // Password For Display Parameter
#define   SA_RTC_MASTER_COUNTER                                            	0x0422                                                           //
#define   SA_RTC_REAL_TIME_COUNTER                                         	0x0426                                                           //

#define   SA_DATE                                                       	0x0430                                                           // Password For Display Parameter
    #define   RTC_DAY_POS                                                  		0                                                                               // Mask
    #define   RTC_MONTH_POS                                                     1                                                                               // Mask
    #define   RTC_YEAR_POS                                                      2                                                                               // Mask
    #define   RTC_HOUR_POS                                                      3                                                                               // Mask
    #define   RTC_MINUTE_POS                                                    4                                                                               // Mask
    #define   RTC_SECOND_POS                                                    5                                                                               // Mask
    #define   RTC_MILISECOND_POS                                                6                                                                               // Mask
    #define   RTC_DAYOFWEEK_POS                                                 7                                                                               // Mask

#define   SA_TIMER_CONTROL                                                 	0x0440                                                           //
    #define   MASK_TIMER_CONTROL_TIMEOUT                                    	0x01                                                                            // Mask
    #define   BIT_NO_TIMER_CONTROL_TIMEOUT                                      0                                                                               // Mask
    #define   MASK_TIMER_CONTROL_STARTED                                        0x10                                                                            // Mask
    #define   BIT_NO_TIMER_CONTROL_STARTED                                      4                                                                               // Mask
    #define   MASK_TIMER_CONTROL_RESTART                                        0x20                                                                            // Mask
    #define   BIT_NO_TIMER_CONTROL_RESTART                                      5                                                                               // Mask
    #define   MASK_TIMER_CONTROL_HANG                                           0x40                                                                            // Mask
    #define   BIT_NO_TIMER_CONTROL_HANG                                         6                                                                               // Mask
    #define   MASK_TIMER_CONTROL_ENABLE                                         0x80                                                                            // Mask
    #define   BIT_NO_TIMER_CONTROL_ENABLE                                       7                                                                               // Mask

#define   SA_TIMER_TIMEOUT                                                 	0x0480                                                           //
#define   SA_TIMER_COUNTER                                                 	0x0500



//* ****                                                  ***** */
//* ****              Serial Port Data Size               ***** */
//* ****                                                  ***** */
    #define   UART_0_BUFFER_SIZE                                               0                                                                               // 
    #define   UART_1_BUFFER_SIZE                                               100                                                                             //
    #define   UART_2_BUFFER_SIZE                                               100                                                                              //
    #define   UART_3_BUFFER_SIZE                                               100                                                                              //
    #define   UART_4_BUFFER_SIZE                                               0                                                                               // 
    #define   UART_5_BUFFER_SIZE                                               0                                                                               // 
    #define   UART_6_BUFFER_SIZE                                               30                                                                              // 
#define   SA_UART_PROCEDURE                                                0x0600                                                           //
#define   SA_UART_STATUS                                                   0x0620                                                           //
//* ****                                                  ***** */
//* ****                 Serial Port Data                 ***** */
//* ****                                                  ***** */
#define   SA_UART_0_DATA                                                   0x0640                                                           //
#define   SA_UART_1_DATA                                                   0x0660                                                           //
#define   SA_UART_2_DATA                                                   0x0800                                                           //
#define   SA_UART_3_DATA                                                   0x0900                                                           //
#define   SA_UART_4_DATA                                                   0x0A00                                                           //
#define   SA_UART_5_DATA                                                   0x0A40                                                           //
#define   SA_UART_6_DATA                                                   0x0A80                                                           //

#define   SA_UART_DATA_OFFSET                                              0x0B00                                                           //
#define   SA_UART_BUFFER_SIZE                                              0x0B40                                                           //
#define   SA_UART_TIMEOUT                                                  0x0B80                                                           //
                                                        //

//* ****                                                  ***** */
//* ****                      OneWire                     ***** */
//* ****                                                  ***** */
#define   SA_ONEWIRE_STATUS                                                	0x0D00                                                           //
    #define   ONEWIRE_ROM_CODE_OK                                           	0x01                                                                            // Mask
    #define   ONEWIRE_EEPROM_CODE_OK                                            0x02                                                                            // Mask
    #define   ONEWIRE_EEPROM_CODE_CRC_OK                                        0x04                                                                            // Mask
    #define   ONEWIRE_ROM_DATA_READ                                             0x08                                                                            // Mask
    #define   ONEWIRE_EEPROM_DATA_READ                                          0x10                                                                            // Mask
    #define   BN_ONEWIRE_ROM_DATA_READ                                          3                                                                               //
    #define   BN_ONEWIRE_EEPROM_DATA_READ                                       4                                                                               //
#define   SA_ONEWIRE_ROM_DATA                                              	0x0D20
#define   SA_ONEWIRE_EEPROM_READ_DATA                                      	0x0DA0
#define   SA_ONEWIRE_EEPROM_WRITE_DATA                                     	0x0DC0

#define   SA_ONEWIRE_TEMPERATURE										   	0x0E00
#define   SA_ONEWIRE_TEMPERATURE_00_00										0x0E00
#define   SA_ONEWIRE_TEMPERATURE_00_01										0x0E04
#define   SA_ONEWIRE_TEMPERATURE_01_00										0x0E08
#define   SA_ONEWIRE_TEMPERATURE_01_01										0x0E0C
#define   SA_ONEWIRE_TEMPERATURE_02_00										0x0E10
#define   SA_ONEWIRE_TEMPERATURE_02_01										0x0E14
#define   SA_ONEWIRE_TEMPERATURE_03_00										0x0E18
#define   SA_ONEWIRE_TEMPERATURE_03_01										0x0E1C

#define   SA_AI_CURRENT                                                    	0x1000

#define   SA_AI_CHANNEL_VALUE                                              	0x1080
#define   SA_AI_CHANNEL_VALUE_FILTERED                                     	0x10C0

//
#define   SA_CHANNEL_VALUE	                                        		0x1100
#define   SA_CHANNEL_VALUE_SEQ_COUNT                                          	16
#define   SA_CHANNEL_VALUE_SEQ_LT1                                          	0
#define   SA_CHANNEL_VALUE_SEQ_LT2                                          	1
#define   SA_CHANNEL_VALUE_SEQ_GD1                                          	2
#define   SA_CHANNEL_VALUE_SEQ_GD2                                          	3
#define   SA_CHANNEL_VALUE_SEQ_GD3                                          	4
#define   SA_CHANNEL_VALUE_SEQ_GD4                                          	5
#define   SA_CHANNEL_VALUE_SEQ_GD5                                          	6
#define   SA_CHANNEL_VALUE_SEQ_GD6                                          	7
#define   SA_CHANNEL_VALUE_SEQ_GD7                                          	8
#define   SA_CHANNEL_VALUE_SEQ_GD8                                          	9
#define   SA_CHANNEL_VALUE_SEQ_PT1                                          	10
#define   SA_CHANNEL_VALUE_SEQ_PT2                                          	11
#define   SA_CHANNEL_VALUE_SEQ_TT1                                          	12
#define   SA_CHANNEL_VALUE_SEQ_TT2                                          	13
#define   SA_CHANNEL_VALUE_SEQ_PROBE_LT1                                   		14
#define   SA_CHANNEL_VALUE_SEQ_PROBE_LT2                                   		15


#define   SA_AI_CHANNEL_STATE	                                          	0x1160
    #define   AI_ERROR_NO_SENSOR_CABLE_BROKEN                                	0x0001
    #define   AI_ERROR_NO_SENSOR_OPTIC_ERROR                                 	0x0002
    #define   AI_ERROR_NO_SENSOR_LOW_CURRENT                                 	0x0004
    #define   AI_ERROR_NO_SENSOR_HIGH_CURRENT                                	0x0008
    #define   AI_ERROR_NO_SENSOR_LOWER_THAN_BOTTOM_VAL                       	0x0010
    #define   AI_ERROR_NO_SENSOR_HIGHER_THAN_TOP_VAL                         	0x0020
	#define   MASK_AI_CHANNEL_NOT_READ_YET									 	0x0040

    #define   AI_CHANNEL_VALUE_UP                                            	0x0100
    #define   AI_CHANNEL_VALUE_DOWN                                          	0x0200
    #define   AI_CHANNEL_DIFFERENCE                                          	0x0400

#define SA_AI_CHANNEL_SEQUENCE												0x11A0
#define SA_CHANNEL_HIGHEST													0x1200
#define SA_CHANNEL_LOWEST													0x1260

#define   SA_MODBUS_RESPONSE                                               	0x1400
#define   SA_MODBUS_COMMAND_NO                                             	0x1440
#define   SA_MODBUS_RESPONSE_EXT_DATA_READ                                 	0x1460

#define   SA_VR_RESPONSE                                                  	0x14A0
#define   SA_VR_COMMAND_NO                                                 	0x14EC
#define   SA_VR_RESPONSE_TANK_SEQ_NO                                       	0x14F0

#define   SA_PROBE_STATE                                                   	0x1500
#define   SA_PROBE_ACTIVE_SEQ												0x1510
#define   SA_PROBE_HIGH_OF_LIQUID                                        	0x1520
//#define   SA_PROBE_TANK_VOLUME		                                        0x1580
#define   SA_PROBE_TEMPERATURE                                             	0x15A0
//#define   SA_PROBE_LEVEL_PERCENTAGE                                        	0x15C0
#define   SA_PROBE_LIQUID_VOLUME											0x15E0

#define   SA_ALERT_MASTER_BACKUP                                           	0x1800
#define   SA_ALERT_CONTROL                                              	0x1804
#define   SA_ALERT_NO                                                     	0x1806

#define   SA_ALERT_TIME_TO_BE_DISPLAY                                       0x1808
#define   SA_ALERT_COUNTER                                                 	0x180C

#define   SA_ALERT_MASTER                                                  	0x1810
#define   SA_ES_MASTER                                                 	 	0x1812


#define   SA_ALERT_MASTER_LT                                                0x1818
#define   SA_ES_MASTER_LT                                                	0x181A
    #define   ALERT_ES_LT1                                   					0x01
    #define   ALERT_ES_LT2                                   					0x02

#define   SA_TANK_AMOUNT_KG                                          		0x2030
#define   SA_TANK1_AMOUNT_KG                                          		0x2030
#define   SA_TANK2_AMOUNT_KG                                          		0x2034


//#define	  SA_GSM_MODEM_STATUS												0x2500
//#define	  SA_GSM_GPRS_STATUS												0x2502
//#define	  SA_SMS_STATUS														0x2510


//* ****                                                  ***** */
//* ****     Data Packet For Tcp Udp And Gprs To Send     ***** */
//* ****                                                  ***** */
#define   SA_DATA_PACKET_NO                                                	0x3000
#define   SA_DATA_TO_BE_SEND_PACKET                                         0x3004
#define   SA_DATA_TO_BE_SEND_SUB_PACKET                                     0x3008
#define   SA_DATA_ACTIVE_TO_BE_SEND_PACKET									0x300C
//* ****                                                  ***** */
//* ****                      TCP_UDP                     ***** */
//* ****                                                  ***** */
#define   SA_DATA_SEND_CONTROL                                              0x3040
#define   SA_DATA_SEND_PACKET_NO                                        	0x3044
#define   SA_DATA_SEND_SUB_PACKET_NO										0x3046

#define   SA_DATA_BACKUP_AI		                                        	0x3100

#define   SA_DATA_SEND_ARRAY	                                        	0x3200


//* ****                                                  ***** */
//* ****                        GSM                       ***** */
//* ****                                                  ***** */
#define SA_MODEM_COMMAND													0x3500

#define   SA_GSM_CONTROL                                                  	0x3600
    #define   SMS_TEXT_CREATED                                             		0x02
    #define   SMS_REPLY_READ                                                    0x10
    #define   IS_SMS_SEND_STATUS_BACKUP                                         0x40
    #define   SMS_SEND_TO_SMS_SENDER                                            0x80

#define SA_MODEM_STATUS                                                  	0x3602
#define SA_MODEM_COMMAND_NO													0x3604

#define SA_MODEM_COMMAND_COUNTER											0x3606
#define SA_MODEM_INITIALIZE_STATUS											0x3608

#define SA_MODEM_RESPONSE													0x3620

//#define   SA_MODEM_PROGRESS                                                	0x3606
//    #define   MODEM_PROGRESS_SMS_SEND                                       	1
//    #define   MODEM_PROGRESS_SMS_READ                                           2
//    #define   MODEM_PROGRESS_SMS_DELETE                                         3
//    #define   MODEM_PROGRESS_GPRS_CONNECTION                                    4
//    #define   MODEM_PROGRESS_GPRS_DATA_SEND                                     5
//    #define   MODEM_PROGRESS_GSM_SIGNAL_QUALITY                                 6

#define   SA_GSM_MODEM_PORT_BUSY_TIME                                      	0x3648
#define   SA_GSM_MODEM_PROCESS_LINE                                        	0x364C
#define   SA_GSM_MODEM_ERROR_COUNT                                         	0x364E
#define   SA_GSM_GPRS_ERROR_COUNT                                          	0x3650
#define   SA_GSM_UART_DATA_LENGTH_BACKUP                                   	0x3652
#define   SA_GSM_SIGNAL_QUALITY                                            	0x3654
#define   SA_GSM_MODBUS_RESPONSE                                           	0x3656

//* ****                                                  ***** */
//* ****                    Gsm - SMS                     ***** */
//* ****                                                  ***** */
#define   SA_SMS_SEND_REASON_MASK                                          	0x3700
#define   SA_SMS_REPLY_MASK                                                	0x3704
#define   SA_SMS_REPLY_ADDRESS_REF                                         	0x3706
#define   SA_GSM_NO_ADDRESS_REF                                            	0x3708
#define   SA_SMS_SPECIAL_COMMANDS                                          	0x370A
    #define   CMD_TANK_SELENOID_ON                                          	0x00000001
    #define   CMD_TANK_SELENOID_OFF                                             0x00000002
    #define   CMD_SENDME                                                        0x00000004
    #define   CMD_EMERGENCY_BYPASS_ON                                           0x00000008
    #define   CMD_EMERGENCY_BYPASS_OFF                                          0x00000010
#define   SA_SMS_ON_PROCESS                                                	0x370E
#define   SA_SMS_STATUS                                                    	0x3710
#define   SA_SMS_DATA_TYPE_TEMP                                            	0x3774
#define   SA_SMS_PROCESS                                                   	0x3776
    #define   SMS_ERROR                                                     	0x00000001
    #define   SMS_PROCESS_MODBUS_COMMAND                                        0x00000002
    #define   SMS_PROCESS_CREATED                                               0x00000004
    #define   SMS_SEND_TIME                                                     0x00000010
    #define   SMS_ANSWERME                                                      0x00000020
    #define   SMS_COMMAND                                                       0x00000040
    #define   SMS_DELETE_ALL                                                    0x00000080
    #define   SMS_DATA_SENDING                                                  0x00001000
    #define   SMS_DATA_SENT                                                     0x00002000
    #define   SMS_PRIVATE_COMMAND                                               0x10000000
    #define   SMS_MODBUS_COMMAND                                                0x20000000
    #define   SMS_LAST_REPLY_PHONE                                              0x40000000
    #define   SMS_IN_PROGRESS                                                   0x80000000
#define   SA_SMS_ACTIVE_NO                                                 	0x3840
#define   SA_SMS_SEND_STATUS												0x3844
#define   SA_SMS_NEW_NO                                                		0x390A
#define   SA_SMS_ACTIVE_RELPY_GSM                                         	0x3910
#define   SA_ACTIVE_GSM_NO                                                 	0x3920
#define   SA_SENDER_GSM_NO                                                 	0x3930
#define   SA_SMS_LENGTH                                                    	0x3940
#define   SA_TO_BE_SMS_REPLY                                               	0x3942
#define   SA_SMS_REPLY_TO_BE_SEND                                          	0x3944
#define   SA_SMS_SEND_STATUS_BACKUP                                    		0x3946
#define   SA_SMS_NO_TO_BE_DELETED                                          	0x394A
#define   SA_SMS_NO_TO_BE_READ                                             	0x394C
#define   SA_SMS_DATA_TYPE                                                 	0x394E
#define   SA_SMS_CRITICAL_NO                                               	0x3950
#define   SA_SMS_PROBE_STATE                                               	0x3952
//* ****                                                  ***** */
//* ****                    Gsm - GPRS                    ***** */
//* ****                                                  ***** */
#define   SA_GSM_GPRS_CONTROL                                              	0x3A00
    #define   GSM_GPRS_CONTROL_DATE_TIME_PACKET_BIT                         	4
    #define   GSM_GPRS_CONTROL_SEND_STATUS_BACKUP_BIT                           6
    #define   GSM_GPRS_CONTROL_GRPS_PACKET_TO_BE_SEND_READ_BIT                  7
    #define   GSM_GPRS_CONTROL_RESTORE_BIT                                      5
#define   SA_LOCAL_IP_ADDRESS                                              	0x3A02
#define   SA_PLC_GPRS_SEND_STATUS_BACKUP                                   	0x3A22
#define   SA_GPRS_PACKET                                                   	0x3A26
#define   SA_GPRS_CONNECTION_STATUS                                        	0x3A2A
    #define   GPRS_CONNECTED                                                	0x00000001
    #define   GPRS_ACTIVE                                                       0x00000002
    #define   GPRS_ALPHABET                                                     0x00000004
    #define   GPRS_OPEN_CONNECTION                                              0x00000008
    #define   GPRS_CONN_TYPE                                                    0x00000010
    #define   GPRS_CONN_TEXT                                                    0x00000020
    #define   GPRS_USER                                                         0x00000040
    #define   GPRS_USER_PASS                                                    0x00000080
    #define   GPRS_APN                                                          0x00000100
    #define   GPRS_DNS1                                                         0x00000200
    #define   GPRS_SERVER_TYPE                                                  0x00000400
    #define   GPRS_TCP_MR                                                       0x00000800
    #define   GPRS_TCP_OT                                                       0x00001000
    #define   GPRS_IP_START_CONNECTION                                          0x00002000
    #define   GPRS_CONN_ID                                                      0x00004000
    #define   GPRS_DETACH                                                       0x00008000
    #define   GPRS_AUTH_MODE                                                    0x00010000
    #define   GPRS_LOCAL_IP                                                     0x00020000
    #define   GPRS_INACT                                                        0x00080000
    #define   GPRS_IP_CONNECTION                                                0x00100000
    #define   GPRS_DISCONNECTED                                                 0x00200000
    #define   GPRS_SHUT_CONNECTION                                              0x00400000
    #define   GPRS_IP_OR_PORT_CHANGED                                           0x00800000
    #define   GPRS_CLOSE_CONNECTION                                             0x01000000
    #define   GPRS_DATA_SENT                                                    0x02000000
    #define   GPRS_IN_PROGRESS                                                  0x80000000
#define   SA_GPRS_SEND_STATUS_MASK                                         	0x3A2E
#define   SA_GPRS_PACKET_TO_BE_SEND                                        	0x3A32
#define   SA_GPRS_PACKET_DATA_LENGTH                                       	0x3A36
//* ****                                                  ***** */
//* ****             Gsm Gprs To Be Sent Data             ***** */
//* ****                                                  ***** */
#define   SA_GPRS_DATE                                                     	0x3C00
#define   SA_GPRS_OUTPUT                                                   	0x3C04
#define   SA_GPRS_INPUT                                                    	0x3C14
#define   SA_GPRS_CHANNEL_VALUE                                            	0x3C24
#define   SA_GPRS_AI_CURRENT                                               	0x3C64



#define   SA_MODBUS_ADDRESS_SEQ_NO											0x3E00
#define   SA_MODBUS_ADDRESS                                 				0x3E02

//* ****                                                  ***** */
//* ****                        HMI                       ***** */
//* ****                                                  ***** */

#define   SA_HMI_LT1                                               			0x4100
#define   SA_HMI_LT2                                               			0x4104
#define   SA_HMI_PT1                                               			0x4108
#define   SA_HMI_PT2                                               			0x410C
#define   SA_HMI_TANK1_CAPACITY                                            	0x4110
#define   SA_HMI_TANK2_CAPACITY                                             0x4114
#define   SA_HMI_TANK1_AMOUNT_KG                                          	0x4118
#define   SA_HMI_TANK2_AMOUNT_KG                                           	0x411C

#define   SA_HMI_DIGITAL_INPUTS                                             0x4120
#define   SA_HMI_DIGITAL_OUTPUTS                                            0x4124
#define   SA_HMI_BUTTON_STATE                                            	0x4128

