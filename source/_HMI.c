/*
 * _HMI.c
 *
 *  Created on: Jun 20, 2017
 *      Author: gerickson
 */

#include "_HMI.h"

/*******************************************************************************
 * Globals
 ******************************************************************************/

volatile bool UP_FLAG;
volatile bool DOWN_FLAG;
volatile bool CLEAR_FLAG;
volatile bool MODE_FLAG;
volatile bool POWER_FLAG;

/*******************************************************************************
 * Code
 ******************************************************************************/

void SW_PORTA_Handler(){

	if( PORTA->ISFR & ( 1U << SW_MODE_PIN )){
		PRINTF("MODE Button Pressed");
		GPIO_ClearPinsInterruptFlags(SW_MODE_GPIO, 1U << SW_MODE_PIN);
		MODE_FLAG = true;
	}
	if( PORTA->ISFR & ( 1U << SW_UP_PIN ) ){
		PRINTF("UP Button Pressed");
		GPIO_ClearPinsInterruptFlags(SW_UP_GPIO, 1U << SW_UP_PIN);
		UP_FLAG = true;
		}
	if( PORTA->ISFR & (1U << SW_DOWN_PIN) ){
		PRINTF("DOWN Button Pressed");
		GPIO_ClearPinsInterruptFlags(SW_DOWN_GPIO, 1U << SW_DOWN_PIN);
		DOWN_FLAG = true;
	}
}

void SW_PORTCD_Handler(){
	if( PORTC->ISFR & (1U << SW_CLEAR_PIN) ){
		PRINTF("CLEAR Button Pressed");
		GPIO_ClearPinsInterruptFlags(SW_CLEAR_GPIO, 1U << SW_CLEAR_PIN);
		CLEAR_FLAG = true;
		}
	if( PORTD->ISFR & (1U << SW_POWER_PIN) ){
		PRINTF("POWER Button Pressed");
		GPIO_ClearPinsInterruptFlags(SW_POWER_GPIO, 1U << SW_POWER_PIN);
		POWER_FLAG = true;
		}
}

void HMI_INIT(void){

	BOARD_InitBUTTONS();

	Display_Init();

	PORT_SetPinInterruptConfig(SW_UP_PORT, SW_UP_PIN, kPORT_InterruptRisingEdge);
	PORT_SetPinInterruptConfig(SW_DOWN_PORT, SW_DOWN_PIN, kPORT_InterruptRisingEdge);
	PORT_SetPinInterruptConfig(SW_MODE_PORT, SW_MODE_PIN, kPORT_InterruptFallingEdge);
	EnableIRQ(SW_PORTA_IRQn);

	PORT_SetPinInterruptConfig(SW_POWER_PORT, SW_POWER_PIN, kPORT_InterruptRisingEdge);
	PORT_SetPinInterruptConfig(SW_CLEAR_PORT, SW_CLEAR_PIN, kPORT_InterruptFallingEdge);
	EnableIRQ(SW_PORTCD_IRQn);

}
