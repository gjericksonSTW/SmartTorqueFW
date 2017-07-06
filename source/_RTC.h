/*
 * zRTC.h
 *
 *  Created on: Jun 12, 2017
 *      Author: gerickson
 */

#ifndef RTC_H_
#define RTC_H_

#include "fsl_rtc.h"
#include "Public.h"
#include "fsl_debug_console.h"



//Initialize the RTC within the system
void RTC_INIT(void);

//Function to enable the RTC within the MCU
void BOARD_SetRtcClock(void);

void RTC_Seconds_IRQHandler(void);

#endif /* RTC_H_ */
