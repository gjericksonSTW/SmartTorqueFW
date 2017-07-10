/*
 * _Timer.h
 *
 *  Created on: Jul 3, 2017
 *      Author: gerickson
 */

#ifndef TIMER_H_
#define TIMER_H_


#include "fsl_tpm.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "fsl_gpio.h"

//Timer used for PWM for LED and Buzzer
#define PWM_BASE TPM0
#define PWM_IRQn TPM0_IRQn
#define PWM_Handler TPM0_IRQHandler
#define OSC0_CLK 2U


//Timer used for delays
#define TIMER_BASE TPM1
#define TIMER_IRQn TPM1_IRQn
#define TIMER_Handler TPM1_IRQHandler

#define PWM_CLK (CLOCK_GetFreq(kCLOCK_Osc0ErClk)*2)
#define TPM_CLK (CLOCK_GetFreq(kCLOCK_Osc0ErClk)/32)

void UpdatePWM(uint32_t percent);

void delay_ms(uint32_t milliseconds);
void delay_us(uint32_t microseconds);

void Timer_INIT(void);
void TIMER_Handler(void);
void PWM_Handler(void);

#endif /* TIMER_H_ */
