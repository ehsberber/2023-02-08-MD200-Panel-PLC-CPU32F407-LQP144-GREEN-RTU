//
// CONFIG REGISTER

//7:6 Always 1:0
//5: EN 	EN : 1, the following 5 bits are used to update EN:0 previous channel selection is kept and the following bits are ignored
//4: SGL 	SGL:1 SINGLE ENDED , SGL:0 DIFFERANTIAL INPUT
#define LTC_2499_CONFIG_MUST		0x80
#define LTC_2499_CONFIG_EN 			0x20
#define LTC_2499_CONFIG_SGL			0x10
#define LTC_2499_CONFIG_ODD			0x00
#define LTC_2499_CONFIG_SGN			0x08

#define LTC_2499_CONFIG_EN2			0x80
#define LTC_2499_CONFIG_IM			0x40
#define LTC_2499_CONFIG_FA			0x20
#define LTC_2499_CONFIG_FB			0x10
#define LTC_2499_CONFIG_SPD			0x08


#define CONFIG_EN_PREVIOUS 		0x00

#define LTC_2499_SIGN				0x80000000
#define LTC_2499_MSB				0x40000000


