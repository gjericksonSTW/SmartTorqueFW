/*
 * _Timer.c
 *
 *  Created on: Jul 3, 2017
 *      Author: gerickson
 */

#include "_Timer.h"

uint16_t count;
tpm_chnl_pwm_signal_param_t pwm_param;

void Timer_INIT(void){
	tpm_config_t tpm_config;

	//Select the LED PTD5 as the output for the PWM signal
	pwm_param.chnlNumber = kTPM_Chnl_5;
	//Send out a standard square waveform
	pwm_param.dutyCyclePercent = 50;

	pwm_param.level = kTPM_HighTrue;

	//Use the Internal Oscillator being run from the EXTAL to drive the TPM module
	CLOCK_SetTpmClock(OSC0_CLK);

	TPM_GetDefaultConfig(&tpm_config);
	tpm_config.prescale = kTPM_Prescale_Divide_1;

	TPM_Init(PWM_BASE, &tpm_config);
	TPM_SetupPwm(PWM_BASE, &pwm_param, 1, kTPM_EdgeAlignedPwm, 1, PWM_CLK);
	TPM_StartTimer(PWM_BASE, kTPM_SystemClock);

	TPM_Init(TIMER_BASE, &tpm_config);
	TPM_EnableInterrupts(TIMER_BASE, kTPM_TimeOverflowInterruptEnable);
	EnableIRQ(TIMER_IRQn);
}

void UpdatePWM(uint32_t percent){
	uint32_t count;

	percent += 1;
	count = percent * 250;

	PWM_BASE->MOD = count;
	PWM_BASE->CONTROLS[5].CnV = count/2;

}

void delay_ms(uint32_t milliseconds){
	TPM_SetTimerPeriod(TIMER_BASE, 1);
	count = 0;
	TPM_StartTimer(TIMER_BASE, kTPM_SystemClock);
	while(count <= milliseconds){
		__WFI();
	}
	TPM_StopTimer(TIMER_BASE);
}

void delay_us(uint32_t microseconds){
	TPM_SetTimerPeriod(TIMER_BASE, 1);
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
