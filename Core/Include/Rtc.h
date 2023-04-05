/*
 * Rtc.h
 *
 *  Created on: Jul 20, 2022
 *      Author: Sezgin Berber
 */

#ifndef APPLICATION_USER_HEADER_RTC_H_
#define APPLICATION_USER_HEADER_RTC_H_


	#define   RTC_CONTROL_UPDATE_BIT_NO                                                            0                                                                               // Mask
    #define   RTC_DAY_POS                                                                          0                                                                               // Mask
    #define   RTC_MONTH_POS                                                                        1                                                                               // Mask
    #define   RTC_YEAR_POS                                                                         2                                                                               // Mask
    #define   RTC_HOUR_POS                                                                         3                                                                               // Mask
    #define   RTC_MINUTE_POS                                                                       4                                                                               // Mask
    #define   RTC_SECOND_POS                                                                       5                                                                               // Mask
    #define   RTC_MILISECOND_POS                                                                   6                                                                               // Mask
    #define   RTC_DAYOFWEEK_POS                                                                    7                                                                               // Mask


	void RtcSecondUpdate(void);
	void RtcAdjust(void);

#endif /* APPLICATION_USER_HEADER_RTC_H_ */
