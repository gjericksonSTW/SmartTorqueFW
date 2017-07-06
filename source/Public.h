/*
 * Public.h
 *
 *  Created on: Jun 12, 2017
 *      Author: gerickson
 */

#ifndef PUBLIC_H_
#define PUBLIC_H_

#include "apitypes.h"
/*******************************************************************************
 * Linker file used for delivering variables between source files and peripherals
 *
 ******************************************************************************/

//#include "fsl_rtc.h"

//extern volatile rtc_datetime_t realTime; // Bridges the RTC configuration member with the RTC trigger source
extern volatile bool BTConnected; // Drives the Bluetooth ON LED
extern uint8_t Bluetooth_rx[64];
extern volatile uint8_t Bluetooth_len;
extern volatile bool message_recieved;
extern volatile struct i2c_FRAM _FRAM;
extern volatile bool UP_FLAG, DOWN_FLAG, CLEAR_FLAG, MODE_FLAG, POWER_FLAG; //Flags set through interrupt driven buttons
extern volatile int TorqueVoltage, BatteryVoltage; //ADC values are converted to voltages and stored here

#endif /* PUBLIC_H_ */
