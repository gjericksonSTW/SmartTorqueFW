/*
 * _HMI.h
 *
 *  Created on: Jun 20, 2017
 *      Author: gerickson
 */

#ifndef HMI_H_
#define HMI_H_

#include "fsl_debug_console.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "pin_mux.h"
#include "_Display.h"


#define SW_MODE_PORT PORTA
#define SW_MODE_GPIO GPIOA
#define SW_MODE_PIN 4U

#define SW_CLEAR_PORT PORTC
#define SW_CLEAR_GPIO GPIOC
#define SW_CLEAR_PIN 3U

#define SW_UP_PORT PORTA
#define SW_UP_GPIO GPIOA
#define SW_UP_PIN 13U

#define SW_DOWN_PORT PORTA
#define SW_DOWN_GPIO GPIOA
#define SW_DOWN_PIN 12U

#define SW_POWER_PORT PORTD
#define SW_POWER_GPIO GPIOD
#define SW_POWER_PIN 7U


#define SW_PORTA_IRQn PORTA_IRQn
#define SW_PORTA_Handler PORTA_IRQHandler
#define SW_PORTCD_IRQn PORTC_PORTD_IRQn
#define SW_PORTCD_Handler PORTC_PORTD_IRQHandler


void HMI_INIT(void);


#endif /* HMI_H_ */
