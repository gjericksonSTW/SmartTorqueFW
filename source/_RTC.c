/*
 * zRTC.c
 *
 *  Created on: Jun 12, 2017
 *      Author: gerickson
 */

#include <_RTC.h>

volatile rtc_datetime_t realTime; // Used for keeping a global variable holding the real time signature

void BOARD_SetRtcClock(void){
	RTC->CR |= RTC_CR_OSCE_MASK;
}

void RTC_Seconds_IRQHandler(void){

	realTime.second++;
	realTime.second %= 60;
	if (realTime.second == 0){
		realTime.minute++;
		realTime.minute %= 60;
		if(realTime.minute == 0){
			realTime.hour++;
			realTime.hour %= 24;
		}
	}
}

void RTC_INIT(void){

	rtc_config_t rtcConfig;

	realTime.second = 45;
	realTime.minute = 59;
	realTime.hour = 8;

	RTC_GetDefaultConfig(&rtcConfig);
	RTC_Init(RTC, &rtcConfig);
	BOARD_SetRtcClock();

	RTC_EnableInterrupts(RTC, kRTC_SecondsInterruptEnable);
	EnableIRQ(RTC_Seconds_IRQn);

	RTC_StartTimer(RTC);

}

