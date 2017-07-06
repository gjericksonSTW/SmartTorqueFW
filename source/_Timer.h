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

#define TIMER_BASE TPM1
#define TIMER_IRQn TPM1_IRQn
#define TIMER_Handler TPM1_IRQHandler

#define TPM_CLK (CLOCK_GetFreq(kCLOCK_McgIrc48MClk)/2)

void delay_ms(uint32_t milliseconds);
void delay_us(uint32_t microseconds);

void Timer_INIT(void);
void TIMER_Handler(void);

#endif /* TIMER_H_ */
