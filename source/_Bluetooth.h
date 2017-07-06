/*
 * _Bluetooth.h
 *
 *  Created on: Jun 12, 2017
 *      Author: gerickson
 */

#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

/*******************************************************************************
 * Libraries
 ******************************************************************************/

#include "fsl_uart_freertos.h"
#include "fsl_uart.h"
#include "dumo_bglib.h"
#include "apitypes.h"
#include "bg_errorcodes.h"
#include "fsl_debug_console.h"
#include "board.h"
#include "Public.h"
#include "_Timer.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define UART_IRQn UART2_FLEXIO_IRQn
#define UART_BASE UART2
#define UART_IRQ UART2_FLEXIO_IRQHandler
#define MAX_BT_LEN (uint8_t) 64
#define UART_CLOCK CLOCK_GetFreq(kCLOCK_BusClk)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

void vBluetoothTask(void *pvParameters);
void Bluetooth_INIT(void);
void Bluetooth_Send(uint8_t* data);
void Bluetooth_Reset(void);
void print_address(uint8_t address[6]);
void UART_IRQ(void);

#endif /* BLUETOOTH_H_ */
