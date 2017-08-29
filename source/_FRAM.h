/*
 * _FRAM.h
 *
 *  Created on: Jun 13, 2017
 *      Author: gerickson
 */

#ifndef FRAM_H_
#define FRAM_H_

/*******************************************************************************
 * Libraries
 ******************************************************************************/

#include <_Sys_Control.h>
#include <string.h>

#include "fsl_i2c.h"

#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_clock.h"
#include "board.h"
#include "clock_config.h"
#include "fsl_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define I2C_BASE I2C1

//GPIO to be configured for Data Line
#define SDA_PORT PORTE
#define SDA_GPIO GPIOE
#define SDA_PIN 0U

//GPIO to be configured for Clock Line
#define SCL_PORT PORTE
#define SCL_GPIO GPIOE
#define SCL_PIN 1U

//General Settings for project
#define I2C_RELEASE_BUS_COUNT 100
#define I2C_BAUD_RATE	100000U
#define CLK_SRC I2C1_CLK_SRC
#define CLK_SOURCE_FREQ CLOCK_GetFreq(CLK_SRC)

//Define FRAM addresses
#define FRAM_ADDR 0X50U // Address of FRAM on the board with all select bits grounded
#define SLEEP_MODE 0X86U // Command for setting device into Sleep Mode
#define RSVD_ID 0XF8U // Used to access Slave ID to set Sleep Mode or find Device ID

//Structure to abstract the FRAM interface
typedef struct i2c_FRAM	{
	void (*write)(uint16_t address, uint8_t* data, size_t dataSize, uint32_t flag);
	void (*read)(uint16_t address, uint8_t* readBuff, size_t dataSize, uint32_t flag);
	void (*sleep)(void);
	status_t (*test)(void);
	void (*wakeup)(void);
	struct System_Configuration* (*readConfig)(uint16_t address, size_t dataSize);
	i2c_master_handle_t master_handle;
} i2c_FRAM_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

//Functions for talking to device over I2C
void FRAM_INIT(void);
void BOARD_I2C_ReleaseBus(void);

//Local functions for interfacing to the FRAM
bool I2C_Write(uint16_t reg_addr, uint8_t *txBuff, uint8_t txSize, uint32_t flag);
bool I2C_Read(uint16_t reg_addr, uint8_t *rxBuff, uint32_t rxSize, uint32_t flag);
void i2c_master_callback(I2C_Type *base, i2c_master_handle_t *handle, status_t status, void *userData);

//Functions to interface over to the FRAM from separate subsystem
void write(uint16_t address, uint8_t* data, size_t dataSize, uint32_t flag);
void read(uint16_t address, uint8_t* readBuff, size_t dataSize, uint32_t flag);
void sleep(void);
status_t test(void);
void wakeup(void);

#endif /* FRAM_H_ */
