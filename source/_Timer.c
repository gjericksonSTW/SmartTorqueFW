/*
 * _Timer.c
 *
 *  Created on: Jul 3, 2017
 *      Author: gerickson
 */

#include "_Timer.h"

uint16_t count;

void Timer_INIT(void){
	tpm_config_t tpm_config;

	CLOCK_SetTpmClock(kCLOCK_Tpm1);
	TPM_GetDefaultConfig(&tpm_config);
	tpm_config.prescale = kTPM_Prescale_Divide_2;

	TPM_Init(TIMER_BASE, &tpm_config);
	TPM_EnableInterrupts(TIMER_BASE, kTPM_TimeOverflowInterruptEnable);
	EnableIRQ(TIMER_IRQn);
}

void delay_ms(uint32_t milliseconds){
	TPM_SetTimerPeriod(TIMER_BASE, MSEC_TO_COUNT(1U, TPM_CLK));
	count = 0;
	TPM_StartTimer(TIMER_BASE, kTPM_SystemClock);
	while(count <= milliseconds){
		__WFI();
	}
	TPM_StopTimer(TIMER_BASE);
}

void delay_us(uint32_t microseconds){
	TPM_SetTimerPeriod(TIMER_BASE, USEC_TO_COUNT(microseconds, TPM_CLK));
	count = 0;
	TPM_StartTimer(TIMER_BASE, kTPM_SystemClock);
	while(!count){
		__WFI();
	}
	TPM_StopTimer(TIMER_BASE);
}

void TIMER_Handler(void){
	TPM_ClearStatusFlags(TIMER_BASE, kTPM_TimeOverflowFlag);
	count++;
}
