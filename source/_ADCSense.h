/*
 * _ADCSense.h
 *
 *  Created on: Jun 12, 2017
 *      Author: gerickson
 */

#ifndef ADCSENSE_H_
#define ADCSENSE_H_

/*******************************************************************************
 * Libraries
 ******************************************************************************/

#include "FreeRTOS.h"
#include "task.h"
#include "fsl_adc16.h"
#include "fsl_debug_console.h"
#include "fsl_dma.h"
#include "fsl_lptmr.h"
#include "fsl_dmamux.h"

#include "_Timer.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define ADC16_BASE ADC0
#define ADC16_CHANNEL_GROUP 0U
#define ADC16_TORQUE_CHANNEL 7U
#define ADC16_BATTERY_CHANNEL 11U
#define ADC16_IRQn ADC0_IRQn
#define ADC16_IRQ ADC0_IRQHandler

#define ADC16_RESULT_REG_ADDR (uint32_t)(&ADC0->R[0])
#define ADC_VDD (65535U)
#define V_BG (1000U)

#define DMA_BASEADDR DMA0
#define DMA_IRQ DMA0_IRQn
#define DMA_IRQHandler DMA0_IRQHandler
#define DMA_CHANNEL 0U
#define DMA_ADC_SRC kDmaRequestMux0ADC0

#define DMAMUX_BASE DMAMUX0

#define LPTMR_BASE LPTMR0
#define CONV_RATE 10U

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

void vADC16Task(void *pvParameters);
void ADC_INIT(ADC_Type *base);
void getMeasurements(void);
void BOARD_ConfigTrigger(void);
void DMA_CONFIG(void);
void LPTMR_TRIG(void);
void DMA_IRQHandler(void);

#endif /* ADCSENSE_H_ */
