/*
 * _Sys_Config.h
 *
 *  Created on: Jun 12, 2017
 *      Author: gerickson
 */

#ifndef SYS_CONTROL_H_
#define SYS_CONTROL_H_

/*******************************************************************************
 * Libraries
 ******************************************************************************/

//#include "fsl_rtc.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Public.h"
#include "_FRAM.h"
#include "_HMI.h"
#include "_Timer.h"
#include "_Bluetooth.h"
#include "board.h"

#include "FreeRTOS.h"
#include "task.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

//Enumeration for switch statement to take user through configuring each parameter for the device
typedef enum CONFIG_STATE{
	Mode = 0U,
	Units = 1U,
	Upper_Limit = 2U,
	Target = 3U,
	Rotation = 4U,
	Memory = 5U,
	Display = 6U,
	Delay = 7U,
	Judgment = 8U,
	Buzzer = 9U,
	Default = 10U
} Config_State;

//Declaration of the typedef for system configuration to be used as global data structure
typedef struct System_Configuration system_config_t;

//Enumeration for choosing Torque mode for wrench
typedef enum System_Mode{
	kSystemConfig_Mode_Manual = 0U,
	kSystemConfig_Mode_Inspection = 1U
} system_mode_t;

//Enumeration used for unit conversion from the Torque Sensor
typedef enum System_Units{
	kSystemConfig_Units_NM = 0U,
	kSystemConfig_Units_lbfm = 1U,
	kSystemConfig_Units_kgfm = 2U,
	kSystemConfig_Units_kgfcm = 3U,
	kSystemConfig_Units_lbfft = 4U
} system_units_t;

//Enumeration to describe rotational mode of the wrench
typedef enum System_Rotation{
	kSystemConfig_Rotation_CW = 0U,
	kSystemConfig_Rotation_CCW = 1U,
	kSystemConfig_Rotation_BI = 2U
} system_rotation_t;

//Struct for holding delay before saving new information to memory
typedef struct System_Memory{
	uint16_t saveTime;
}system_memory_t;

//Enumeration for describing the display mode the system is in
typedef enum System_Display{
	kSystemConfig_Display_LCD = 0U,
	kSystemConfig_Display_DUAL = 1U
} system_display_t;

//Struct for describing delay before sending data over Communication
//uint16_t system_delay;

//Enumeration for describing if system is in judgment mode or not
typedef enum System_Judgment{
	kSystemConfig_Judgment_OFF = 0U,
	kSystemConfig_Judgment_ON = 1U
} system_judgment_t;

//Enumeration for buzzer enable bit to activate/deactivate buzzer
typedef enum System_Buzzer{
	kSystemConfig_Buzzer_OFF = 0U,
	kSystemConfig_Buzzer_ON = 1U
} system_buzzer_t;

//Struct for describing the delay until the machine goes into sleep mode
typedef struct System_Sleep{
	uint16_t delay;
} system_sleep_t;

//Enumeration for restoring the wrench to factory settings or not
typedef enum System_DFT{
	kSystemConfig_Not_Default = 0U,
	kSystemConfig_Set_Default = 1U
} system_dft_t;

//Main struct to hold all device configuration settings
typedef struct System_Configuration{
	system_mode_t mode;
	system_units_t units;
	uint32_t upperLimit;
	uint32_t target;
	system_rotation_t rotation;
	system_memory_t memory;
	system_display_t display;
	uint16_t comm_delay;
	system_judgment_t judge;
	system_buzzer_t buzzer;
	system_sleep_t sleep;
	system_dft_t _default;
	bool inConfiguration;
} system_config_t;

//	rtc_datetime_t time; // Not used now time stamp happens on remote tablet client

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

//System initialization and tasks
void Sys_Control_INIT(void);
void vSystemControllerTask(void* pvParameters);
void ConfigurationBuilder(void* pvParameters);

//Handle the HMI input and output
void HandleButtons(void);
void UpdateDisplay(void);

//Reset the device to known settings
void Set_Configuration_default(void);

//Function called when controller requests a torquing procedure
void Start_Torquing(void);
bool TorqueWithinRange(uint32_t torque);
void HandleTorch(uint32_t torque);
void ManageTransmission(void);
void HandleCommands(void);

#endif /* SYS_CONTROL_H_ */
