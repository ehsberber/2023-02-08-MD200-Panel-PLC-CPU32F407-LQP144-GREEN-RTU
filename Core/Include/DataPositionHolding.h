//* ****                           ***** */
//* ****     Project               ***** */
//* ****                           ***** */
//* Name   : Decos REF STM32 F4-F1 PANEL BP *// 
//* Date            :31.03.2021 10:51:48  *// 
//* ****                                                  ***** */
//* ****                 Holding Register                 ***** */
//* ****                                                  ***** */

//* ****                                                  ***** */
//* ****          SYSTEM_HOLDING_REGISTER_USART           ***** */
//* ****                                                  ***** */
//* ****                                                  ***** */
//* ****                   PLC Variable                   ***** */
//* ****                                                  ***** */

#define   HA_PLC_MASTER_CONTROL                                     0x000A
    #define   BN_PLC_MASTER_CONTROL_ID_CONTROL
    #define   BN_PLC_MASTER_CONTROL_ILLEGAL_FUELING

#define   HA_USART_PORT_DATA_END                                  	0x0010

#define   HA_SYSTEM_STATE											0x0020
#define   HA_SYSTEM_SUBSTATE										0x0022


#define   HA_SYSTEM_CONTROL											0x0024

#define   HA_BUTTON_00												0x0030
#define   HA_BUTTON_01												0x0032
#define   HA_BUTTON_02												0x0034


#define   HA_DEFAULT                                                0x0040
#define   HA_PLC_CONTROL                                         	0x0044
    #define   UPDATE_HOLDING_REG                                    	0x8000
    #define   DEFAULT_HOLDING_REG                                   	0x2000
    #define   BN_HOLDING_UPDATE_INPROGRESS                          0


#define   HA_PLC_RUN_TIMEOUT                                      	0x0050
//* ****                                                  ***** */
//* ****            SYSTEM_HOLDING_REGISTER_PLC           ***** */
//* ****                                                  ***** */
#define   HA_PLC_NAME                                          		0x0060
#define   HA_PLC_SERIAL_NO                                          0x00D0
#define   HA_SLAVE_ADDRESS                                          0x00D8
//* ****                                                  ***** */
//* ****      SYSTEM_HOLDING_REGISTER_EXTERNAL_BOARDS     ***** */
//* ****                                                  ***** */
    #define   EXTERNAL_BOARD_TYPE_COUNT                                4
    #define   MODULE_AI                                                0
    #define   MODULE_AO                                                1
    #define   MODULE_DI                                                2
    #define   MODULE_DO                                                3

#define   HA_MODULE_ENABLE                                         	0x00E0
    #define   HA_AI_MODULE_ENABLE                                   HA_MODULE_ENABLE + ( 4 * MODULE_AI )
    #define   HA_AO_MODULE_ENABLE                                   HA_MODULE_ENABLE + ( 4 * MODULE_AO )
    #define   HA_DI_MODULE_ENABLE                                   HA_MODULE_ENABLE + ( 4 * MODULE_DI )
    #define   HA_DO_MODULE_ENABLE                                	HA_MODULE_ENABLE + ( 4 * MODULE_DO )
#define   HA_DO_MASTER                                              0x00F0

//* ****                                                  ***** */
//* ****                   Analog Input                   ***** */
//* ****                                                  ***** */
#define   HA_AI_CALB                                                0x0100
#define   HA_AI_OFFSET                                              0x0140
#define   HA_AI_BOTTOM	                                            0x0180
#define   HA_AI_TOP	                                                0x01C0
#define   HA_AI_CALC	                                            0x0200

#define   HA_AI_CHANNEL_TYPES                                     	0x0240

#define   HA_AI_KALMAN_FILTER                                		0x0248
#define   HA_AI_AVARAGE_CALCULATION                                 0x0250

#define   HA_AI_MODULE_CHANNEL_POS                                  0x0260                                                           //
#define   HA_AI_MODULE_CHANNEL_POS_00                               0x0262
#define   HA_AI_MODULE_CHANNEL_POS_01                               0x0264
#define   HA_AI_MODULE_CHANNEL_POS_02                               0x0266
#define   HA_AI_MODULE_CHANNEL_POS_03                               0x0268

#define   HA_AI_MODULE_CHANNEL_MODULE_TYPE_SPI						0x0270
#define   HA_AI_MODULE_CHANNEL_MODULE_TYPE_SPI1						0x0270
#define   HA_AI_MODULE_CHANNEL_MODULE_TYPE_SPI2						0x0272

//* ****                                                  ***** */
//* ****                  AI Channel No                   ***** */
//* ****                                                  ***** */
#define   HA_AI_ALLOCATION                             				0x0280

#define   HA_AI_MODULE_RESOLUTION_MULTIPLIER						0x02C0

#define   HA_AI_CHANNEL_BOTTOM_VALUE_mV								0x0300
#define   HA_AI_CHANNEL_TOP_VALUE_mV								0x0340
//* ****                                                  ***** */
//* ****                    Digital IO                    ***** */



#define   HA_DI_STANDBY												0x0380
#define   HA_DI_DEBUG_MODE											0x03A0
#define   HA_DI_DEBUG												0x03C0

//* ****                                                  ***** */
//* ****                   Master Codes                   ***** */
//* ****                                                  ***** */
#define   HA_MASTER_CODE_SAVE_POSITION								0x0400
#define   HA_MASTER_CODE                                    		0x0404


#define	  HA_RTU_BAUDRATE												0x0500
#define	  HA_RTU_DATA_BITS												0x0502
#define	  HA_RTU_DATA_PARITY											0x0504
#define	  HA_RTU_STOP_BITS												0x0506





//* ****                                                  ***** */
//* ****            Alert/Emergency Stop                  ***** */
//* ****                                                  ***** */



#define   HA_AI_KALMAN_fP											0x0B00
#define   HA_AI_KALMAN_fQ											0x0B04
#define   HA_AI_KALMAN_fR											0x0B08
#define   HA_AI_KALMAN_fKGain										0x0B0C
#define   HA_AI_KALMAN_LEN											0x0B10                                                           //

//* ****                                                  ***** */
//* ****            Tank Capacity And Deviation           ***** */
//* ****                                                  ***** */

#define   HA_TANK_COUNT                                             0x1A30


//* ****                                                  ***** */
//* ****      Tank Level Up Down And Illegal fueling      ***** */
//* ****                                                  ***** */
#define   HA_LEVEL_ALLOWED                                          0x1AA0
#define   HA_TOTAL_LEVEL_LAST                                       0x1AA4
#define   HA_TOTAL_ILLEGAL_FUELING                                  0x1AA8
#define   HA_MIN_UP_LEVEL_AT_PEROID_OF_FILLING               		0x1AAC
#define   HA_MIN_UP_LEVEL_TIMEOUT_AT_PEROID_OF_FILLING              0x1AB0

#define   HA_TANK_OVER_FILLING_LEVEL1              					0x1AC0
#define   HA_TANK_OVER_FILLING_LEVEL2              					0x1AC4

#define   HA_ALERT_TYPE_NO_TANK_OVER_FILLING          					0x1AD0

//* ****                                                  ***** */
//* ****          Tank Serial No, Veeder Root No          ***** */
//* ****                                                  ***** */

#define   HA_PROBE_TIMEOUT                                   		0x1C00

#define   HA_PROBE_PROTOCOL_NO                                   	0x1D00

#define   HA_PROBE_ACTIVE                                       	0x1D02


#define   HA_PROBE_SERIAL_NO                                        0x1D04
    #define   HA_PROBE1_SERIAL_NO                                    	HA_PROBE_SERIAL_NO + ( 4 * 0 )
    #define   HA_PROBE2_SERIAL_NO                                       HA_PROBE_SERIAL_NO + ( 4 * 1 )

#define   HA_PROBE_TANK_ALLOCATION                                   0x1D20
    #define   HA_PROBE_TANK1_ALLOCATION                                	HA_PROBE_TANK_ALLOCATION + ( 2 * 0 )
    #define   HA_PROBE_TANK2_ALLOCATION                                 HA_PROBE_TANK_ALLOCATION + ( 2 * 1 )


#define   HA_PROBE_TANK_OFFSET                                   	0x1D40
    #define   HA_PROBE_TANK1_OFFSET                                	HA_PROBE_TANK_OFFSET + ( 4 * 0 )
    #define   HA_PROBE_TANK2_OFFSET                                 HA_PROBE_TANK_OFFSET + ( 4 * 1 )

#define   HA_TANK_CAPACITY                                      	0x1E00
#define   HA_TANK_DIAMETER                                      	0x1E20
#define   HA_TANK_LEN                                      			0x1E40
#define   HA_TANK_ELLIPTICAL_LEN									0x1E60
#define   HA_TANK_DENSITY                                          	0x1E80

#define   HA_TANK_DEVIATION                               			0x1EA0
#define   HA_TANK_DIFFERANCE                                       	0x1EC0


//* ****                                                  ***** */
//* ****                    Admin Gsm                     ***** */
//* ****                                                  ***** */
    #define   ADMIN_GSM_COUNT                                       	16
    #define   LENGTH_OF_ADMIN_GSM                                       16
#define   HA_ADMIN_GSM                                              0x2000
//* ****                                                  ***** */
//* ****                        Sms                       ***** */
//* ****                                                  ***** */
#define   HA_SMS_COUNT                                                     0x2100
#define   HA_SMS_PERIOD                                                    0x2102
#define   HA_SMS_DATA_TYPE                                                 0x2106

#define   HA_SMS_TIME                                                      0x2108                                                           // SMS Send Time List 
    #define   SMS_REPLY_COUNT                                                  32                                                                              // Reply Count
#define   HA_SMS_REPLY_GSM                                                 0x2128                                                           // Sms Reply Gsm 
#define   HA_SMS_SEND_STATUS                                               0x2168                                                           // Sms Send Status  
    #define   SMS_TIME                                                                             0x00000001                                                                      //  
    #define   SMS_ANSWER_ME                                                                        0x00000002                                                                      //  
    #define   SMS_PROGRAM_SMS                                                                      0x00000004                                                                      //  
    #define   SMS_EMERGENCY_STOP                                                                   0x00000008                                                                      //  
    #define   SMS_CONSTANT_VALUE                                                                   0x00000010                                                                      //  
    #define   SMS_CRITICAL_VALUE                                                                   0x00000020                                                                      //  
    #define   SMS_ADC_CHANNEL_VALUE_CHANGE                                                         0x00000040                                                                      //  
    #define   SMS_ILLEGAL_FUELING                                                                  0x00000080                                                                      //  
    #define   SMS_FUELING_TIMEOUT                                                                  0x00000100                                                                      //  
    #define   SMS_COVER                                                                            0x00000200                                                                      //  
    #define   SMS_MASTER_CARD                                                                      0x00000400                                                                      //  
    #define   SMS_OPEN_CARD                                                                        0x00000800                                                                      //  
    #define   SMS_FLAME_DETECTOR                                                                   0x00001000                                                                      //  
    #define   SMS_THERMIC_RELAY                                                                    0x00004000                                                                      //  
    #define   SMS_GAS_ALERT                                                                        0x00008000                                                                      //  
    #define   SMS_PASSWORD_TIMEOUT                                                                 0x00010000                                                                      //  
    #define   SMS_SYSTEM_OFF_ON                                                                    0x00020000                                                                      //  
    #define   SMS_START_BUTTON                                                                     0x00040000                                                                      //  
    #define   SMS_STOP_BUTTON                                                                      0x00080000                                                                      //  
    #define   SMS_RESET_BUTTON                                                                     0x00100000                                                                      //  
    #define   SMS_EARTH_QUAKE                                                                      0x00200000                                                                      //  
    #define   SMS_GAS_SENSOR_ERROR                                                                 0x00400000                                                                      //  
    #define   SMS_LEVEL_SENSOR_ERROR                                                               0x00800000                                                                      //  
    #define   SMS_LT_UP_MASK                                                                       0x01000000                                                                      //  
//* ****                                                  ***** */
//* ****                       Gprs                       ***** */
//* ****                                                  ***** */
#define   HA_GPRS_CONNECTION_TYPE                                          0x2200                                                           // Gprs Connection Type (TCP/UDP) 
    #define   GPRS_CONNECTION_TYPE_UDP                                         0                                                                               // Udp Connection
    #define   GPRS_CONNECTION_TYPE_TCP                                         2                                                                               // Tcp Connection

#define   HA_GPRS_APN_NAME                                                 0x2202                                                           // Gprs Connection APN Name
#define   HA_GPRS_APN_USER_NAME                                            0x2220                                                           // Gprs Connection User Name
#define   HA_GPRS_APN_USER_PASS                                            0x2240                                                           // Gprs Connection User Pass
#define   HA_GPRS_DNS_ADDRESS                                              0x2260                                                           // Gprs Connection DNS Address
#define   HA_GPRS_IP_ADDRESS                                               0x2280                                                           // Gprs Connection Ip Address
#define   HA_GPRS_IP_ADDRESS_PORT                                          0x22A0                                                           // Gprs Connection Ip Address Port

#define   HA_DATA_SEND_PERIOD                                              0x22A4                                                           // GPRS Data Send Period
#define   HA_CONNECTION_CHECK_TIME                                    	   0x22A8                                                           // Gprs Send Status
#define   HA_DATA_DEFAULT_PACKET                                           0x22AC                                                           //


#define   HA_DATA_CHANNEL_VALUE_MULTIPLIER                                 0x22C0                                                           //
#define   HA_DATA_ANALOG_INPUT_VALUE_MULTIPLIER                            0x22C4
//* ****                                                  ***** */
//* ****          Modbus , Veeder Root Data Read          ***** */
//* ****                                                  ***** */
#define   HA_VR_DATA_READ_TIMEOUT                                          0x24A4                                                           // Veeder Root Data Read Timer 
//* ****                                                  ***** */
//* ****                     HMI Data                     ***** */
//* ****                                                  ***** */
#define   HA_HMI_ALERT                                                     0x3500                                                           //  
#define   HA_HMI_DISP_MESSAGE                                              0x3506                                                           //  
#define   HA_HMI_LOG                                                       0x3508                                                           //  
    #define   BN_HMI_LOG_EMERGENCY_STOP                                                            0                                                                               //  
    #define   BN_HMI_LOG_DATA_SAVE                                                                 8                                                                               //  
    #define   BN_HMI_LOG_ID_FOUND                                                                  12                                                                              //  
    #define   BN_HMI_LOG_ID_NOT_FOUND                                                              13                                                                              //  
#define   HA_HMI_DATA_SAVE_TIMEOUT                                         0x3510                                                           //  
