#include "MicroPeripheral.h"

/*----------------------------------------------------------------------------
 Define  IWDG PR and RLR settings
 *----------------------------------------------------------------------------*/
 
#define __IWDG_PERIOD             0x0FFFF480			//0x001E8480

#if   (__IWDG_PERIOD >  16384000UL)
  #define __IWDG_PR             (6)
  #define __IWDGCLOCK (32000UL/256)
#elif (__IWDG_PERIOD >   8192000UL)
  #define __IWDG_PR             (5)
  #define __IWDGCLOCK (32000UL/128)
#elif (__IWDG_PERIOD >   4096000UL)
  #define __IWDG_PR             (4)
  #define __IWDGCLOCK  (32000UL/64)
#elif (__IWDG_PERIOD >   2048000UL)
  #define __IWDG_PR             (3)
  #define __IWDGCLOCK  (32000UL/32)
#elif (__IWDG_PERIOD >   1024000UL)
  #define __IWDG_PR             (2)
  #define __IWDGCLOCK  (32000UL/16)
#elif (__IWDG_PERIOD >    512000UL)
  #define __IWDG_PR             (1)
  #define __IWDGCLOCK   (32000UL/8)
#else
  #define __IWDG_PR             (0)
  #define __IWDGCLOCK   (32000UL/4)
#endif
#define __IWGDCLK  (32000UL/(0x04<<__IWDG_PR))
#define __IWDG_RLR (__IWDG_PERIOD*__IWGDCLK/1000000UL-1)


void WatchDogInit(void)
{
  IWDG->KR  = 0x5555;                                           // enable write to PR, RLR
  IWDG->PR  = __IWDG_PR;                                        // Init prescaler
  IWDG->RLR = __IWDG_RLR;                                       // Init RLR
  IWDG->KR  = 0xAAAA;                                           // Reload the watchdog
  IWDG->KR  = 0xCCCC;     
}

void WatchDogFeed(void)
{
	IWDG->KR  = 0xAAAA;				//Clear Watch Dog
}
