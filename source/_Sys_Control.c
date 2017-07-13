/*
 * _Sys_Config.c
 *
 *  Created on: Jun 12, 2017
 *      Author: gerickson
 */

#include <_Sys_Control.h>

/*******************************************************************************
 * Globals
 ******************************************************************************/

// Configuration structures for holding current and intermediate setting values
system_config_t mainConfig, builderConfig;
volatile bool save, underConstruction, resume;
bool DOWN, UP, targetSet;
TaskHandle_t xBuildHandle;
char strTorque[15];
char Terminator[6] = "E00\r\n\0";

/*******************************************************************************
 * Code
 ******************************************************************************/

// Initializing the System configuration for it to be in a known state. Using previously saved state or factory settings
void Sys_Control_INIT(void){

	// Initialize HMI flags and on-board red torch showing Bluetooth connection
	DOWN = false;
	UP = false;
	LED_RED_INIT(0);
	LED_RED_OFF();

	TorqueVoltage = 55;
	Stop_Torch();

	targetSet = false;

	// Format for sending off data to the host application
	strcpy(strTorque, "RE,000,000.0\r\n\0");

	// flag set if the memory already has been loaded with configuration data
	bool memEmpty = true;

	// Set memory locations for configuration data all to zero before pulling from FRAM or setting to factory settings
	memset(&mainConfig, 0, sizeof(mainConfig));
	memset(&builderConfig, 0 , sizeof(builderConfig));

	// Make sure system is not in manual configuration mode
	underConstruction = false;

	/***
	 * Determine if the main configuration settings are already logged in memory
	 * one bit is set at address 0x0000 when the main configuration data is written
	***/

	_FRAM.read(0x0000,(uint8_t *) &memEmpty, 1, kI2C_TransferDefaultFlag);

	if (memEmpty){
		// When there is nothing in memory set everything to default
		Set_Configuration_default();

		// Write the default configuration to memory and sign that there is information in memory
		_FRAM.write(0, (uint8_t *) 1, 1, kI2C_TransferDefaultFlag);
		_FRAM.write(0x0001,(uint8_t *) &mainConfig, sizeof(mainConfig), kI2C_TransferDefaultFlag);
	}
	else{
		// When memory is not empty read out the configuration data
		_FRAM.read(0x0001, (uint8_t *) &mainConfig, sizeof(mainConfig), kI2C_TransferDefaultFlag);
	}

	// Start the Configuration Building task to remain in suspended state until activated through MODE button
	xTaskCreate(ConfigurationBuilder, "Builder", 300, NULL, 1, &xBuildHandle);

}

// Process all Button inputs based on what flags are set via NVIC
void HandleButtons(void){
	if(UP_FLAG){
		UP_FLAG = false;
		UP = true;
		// Handle up button
	}
	if(DOWN_FLAG){
		DOWN_FLAG = false;
		DOWN = true;
		// Handle down button
	}
	if(CLEAR_FLAG){
		CLEAR_FLAG = false;
		save = true;
		// Handle clear button
	}
	if(MODE_FLAG){
		MODE_FLAG = false;
		underConstruction = true;
		resume = true;
		// Handle mode flag
	}
	if(POWER_FLAG){
		POWER_FLAG = false;
	}
}

// Determine what Mode the system is in and implement the corresponding display
void UpdateDisplay(void){
	Set_Display(TorqueVoltage, 3);
}

// RTOS task for managing all of the inputs and outputs of the system
void vSystemControllerTask(void* pvParameters){

	while(1){

		// Manage the inputs to the system
		HandleButtons();

		// Update PWM for LED to indicate proximity to target torque
		HandleTorch(TorqueVoltage);

		// Function that will manage communication to host application
		ManageTransmission();

		// Function to process commands coming in from the host application
		HandleCommands();

		/***
		 *  Resume configuration mode if the user sets the under construction flag
		 *  otherwise continue updating display with current torque values
		 ***/
		if (!underConstruction) {
			UpdateDisplay();
		}
		if(resume){
			vTaskResume(xBuildHandle);
			resume = false;
		}

		// Turn off and on LED based on Bluetooth connectivity
		(BTConnected) ?	LED_RED_ON() : LED_RED_OFF();
		vTaskDelay(100);
	}
}

// Call function when entering configurations mode for choosing settings manually
void ConfigurationBuilder(void* pvParameters){

	// TaskHandle_t handle = xTaskGetHandle("Builder");
	// Initialize variables to run through configuration state machine
	Config_State state;
	uint32_t setting;
	while(1){
		state = Mode;

 		if (underConstruction){
			Set_Display(0,0);

			// Set the builderConfiguration equal to the current configuration
			builderConfig = mainConfig;
			Display_Blink();

			/***
			 *  Being Configuration state machine where the user flips through a switch statement for setting
			 *  each parameter of the torque wrench manually through UP & DOWN.
			 *  Once each parameter is set the new configuration is loaded into the main configuration
			 *  the new configuration is saved in the FRAM
			 ***/
			switch (state) {
				case Mode:
					setting = builderConfig.mode;
					while(!save){
						if(UP && setting == kSystemConfig_Mode_Manual){
							setting = kSystemConfig_Mode_Inspection;
							UP = false;
						}
						if(DOWN && setting == kSystemConfig_Mode_Inspection){
							setting = kSystemConfig_Mode_Manual;
							DOWN = false;
						}

						Set_Display(setting, 0);
					}
					builderConfig.mode = setting;
					save = false;
					state = Units;
				case Units:
					setting = builderConfig.units;
					while(!save){
						if(UP && setting < 4){
							setting++;
							UP = false;
						}
						if(DOWN && setting > 0){
							setting--;
							DOWN = false;
						}
						if(DOWN || UP){
							DOWN = false;
							UP = false;
						}
						Set_Display(setting, 0);
					}
					builderConfig.units = setting;
					save = false;
					state = Upper_Limit;
				case Upper_Limit:
					setting = builderConfig.upperLimit;
					while(!save){
						if(DOWN){
							setting--;
							DOWN = false;
						}
						if(UP){
							setting++;
							UP = false;
						}
						Set_Display(setting, 3);
					}
					builderConfig.upperLimit = setting;
					save = false;
					state = Target;
				case Target:
					setting = builderConfig.target;
					while(!save){
						if(DOWN){
							setting--;
							DOWN = false;
						}
						if(UP){
							setting++;
							UP = false;
						}
						Set_Display(setting, 3);
					}
					builderConfig.target = setting;
					save = false;
					state = Rotation;
				case Rotation:
					setting = builderConfig.rotation;
					while(!save){
						if(UP && setting < 2){
							setting++;
							UP = false;
						}
						if(DOWN && setting > 0){
							setting--;
							DOWN = false;
						}
						if(DOWN || UP){
							DOWN = false;
							UP = false;
						}
						Set_Display(setting, 0);
					}
					builderConfig.rotation = setting;
					save = false;
					state = Memory;
				case Memory:
					setting = builderConfig.memory.saveTime;
					while(!save){
						if(DOWN){
							setting--;
							DOWN = false;
						}
						if(UP){
							setting++;
							UP = false;
						}
						Set_Display(setting, 0);

					}
					builderConfig.memory.saveTime = setting;
					save = false;
					state = Display;
				case Display:
					setting = builderConfig.display;
					while(!save){
						if(DOWN && setting > 0){
							setting--;
						}
						if(UP && setting < 1){
							setting++;
						}
						if(DOWN || UP){
							DOWN = false;
							UP = false;
						}
						Set_Display(setting, 0);
					}
					builderConfig.display = setting;
					save = false;
					state = Delay;
				case Delay:
					setting = builderConfig.delay.milliseconds;
					while(!save){
						if(DOWN){
							setting -= 100;
						}
						if(UP){
							setting += 100;
						}
						if(DOWN || UP){
							DOWN = false;
							UP = false;
						}
						Set_Display(setting, 0);
					}
					builderConfig.delay.milliseconds = setting;
					save = false;
					state = Judgment;
				case Judgment:
					setting = builderConfig.judge;
					while(!save){
						if(DOWN && setting > 0){
							setting--;
						}
						if(UP && setting < 1){
							setting++;
						}
						if(DOWN || UP){
							DOWN = false;
							UP = false;
						}
						Set_Display(setting, 0);
					}
					builderConfig.judge = setting;
					save = false;
					state = Buzzer;
				case Buzzer:
					setting = builderConfig.buzzer;
					while(!save){
						if(DOWN && setting > 0){
							setting--;
						}
						if(UP && setting < 1){
							setting++;
						}
						if(DOWN || UP){
							DOWN = false;
							UP = false;
						}
						Set_Display(setting, 0);
					}
					builderConfig.buzzer = setting;
					save = false;
					state = Default;
				case Default:
					setting = builderConfig._default;
					while(!save){
						if(UP && setting == kSystemConfig_Not_Default){
							setting = kSystemConfig_Set_Default;
							UP = false;
						}
						if(DOWN && setting == kSystemConfig_Set_Default){
							setting = kSystemConfig_Not_Default;
							DOWN = false;
						}
						Set_Display(setting, 0);
					}
					builderConfig._default = setting;
					save = false;
				break;
				}

				// Set main configuration with new information
				mainConfig = builderConfig;

				// Write the new settings to the FRAM
				_FRAM.write(0x0001, (uint8_t *) &mainConfig, sizeof(mainConfig), kI2C_TransferDefaultFlag);

				// If default is selected reset the machine to its factory settings
				if (mainConfig._default){
					Set_Configuration_default();
				}

				// Flip the under construction flag back to false
				underConstruction = false;

				// Set the display back to normal
				Display_Stop_Blink();
 			}

 		// Suspend the task until user wants to configure the device again
		vTaskSuspend(NULL);
	}
}

// Default configuration data for the wrench
void Set_Configuration_default(void){

	mainConfig.mode = kSystemConfig_Mode_Manual;
	mainConfig.units = kSystemConfig_Units_NM;
	mainConfig.upperLimit = 45U;
	mainConfig.target = 0U;
	mainConfig.rotation = kSystemConfig_Rotation_BI;
	mainConfig.memory.saveTime = 1000U;
	mainConfig.buzzer = kSystemConfig_Buzzer_ON;
	mainConfig.delay.milliseconds = 500U;
	mainConfig.judge = kSystemConfig_Judgment_ON;
	mainConfig.sleep.delay = 20000U;
	mainConfig.display = kSystemConfig_Display_DUAL;
	mainConfig._default = kSystemConfig_Not_Default;
}

// Function for returning status if the current Torque value is within the range
bool TorqueWithinRange(uint32_t torque){
	if(torque < mainConfig.target){
		return false;
	}
	//uint32_t tolerance = mainConfig.target * 1000 * 11 / 10000;

	if(torque >= mainConfig.target){
		return true;
	}
	return false;
}

// Update PWM for LED to indicate proximity to target torque
void HandleTorch(uint32_t torque){

	static uint32_t percent, temp;
	// Determine the rate for the PWM related to the Torquing
	if(torque > mainConfig.target){
		percent = 0;
	}else{
		percent = (uint32_t) (mainConfig.target - TorqueVoltage) * 100 / mainConfig.target;
	}
	if(temp != percent){ // Update PWM only on a change
		UpdatePWM(percent);
	}
	temp = percent;

	(torque > (mainConfig.target * 75 / 100)) ? Enable_Torch() : Stop_Torch();
}

// Function that will manage communication to host application
void ManageTransmission(void){

	static uint32_t maxTorque = 0;
	static uint32_t tempTorque = 0;

	static uint8_t delay_count = 0;
	static bool start_counting;
	char hInt[4];

	start_counting = false;
	memset(hInt, '\0', 3);

	// When torquing procedure has begun reset the max torquing value
	if(targetSet){
		maxTorque = 0;
		targetSet = false;
	}

	maxTorque = (maxTorque < TorqueVoltage) ? TorqueVoltage : maxTorque;

	// Check of the torquing has reached the right value and start delay before sending
	if(TorqueWithinRange(maxTorque)){
		start_counting = true;
	}

	delay_count++;

	// Wait for the delay to reach its value before sending off torque value to host device
	if((delay_count*100) >= mainConfig.delay.milliseconds && maxTorque > mainConfig.target){
		if (tempTorque != maxTorque){
			// Convert Integer torque value to a string
			itoa(maxTorque, hInt, 10);

			if (maxTorque < 100){
				strTorque[7] = '0';
				strTorque[8] = '0';
				memcpy(&strTorque[9], &hInt, 1);
				memcpy(&strTorque[11], &hInt[1], 1);
			}
			else if(maxTorque < 1000 && maxTorque > 100){
				strTorque[7] = '0';
				memcpy(&strTorque[8], &hInt, 2);
				memcpy(&strTorque[11], &hInt[2], 1);
			}
			else{
				memcpy(&strTorque[7], &hInt, 3);
				memcpy(&strTorque[11], &hInt[3], 1);
			}

			//printf("Sending Torque Value: %s\r\n", strTorque);

			Bluetooth_Send((uint8_t *) strTorque, strlen(strTorque));

			start_counting = false;
			delay_count = 0;
		}
		tempTorque = maxTorque;
	}

	delay_count = (start_counting) ? delay_count : 0;
}

// Function to process commands coming in from the host application
void HandleCommands(void){

	// Allocate 4 bytes of space for the Header and Payload of Bluetooth message
	static char Header[4];
	static char Payload[4];
	static int value = 0;

	// Set memory location of Header and Payload of Bluetooth message to zeroes
	memset(&Header, '\0', 4);
	memset(&Payload, 0, 4);

	/***
	 *  Process the received messages over Bluetooth by splitting the header from body
	 *  the header will describe what is being written to the wrench and the body holds
	 *  the payload value to be written into the registers. Currently the torque wrench
	 *  only receives upper and lower torque values given by headers of W13 & W12 respectively
	 *  The number of commands received by the wrench may be expanding from this by defining more
	 *  header commands.
	 ***/
	if (message_recieved){
		for(uint8_t i = 0; i < Bluetooth_len; i++){
			PRINTF("%c", (char) Bluetooth_rx[i]);
		}
		// Pull out first 3 bytes as header of command
		memcpy(&Header, &Bluetooth_rx, 3);

		// W13 command to set Upper Torque Limit value
		if (strcmp(Header, "W13") == 0){
			strcpy(Payload, (char *) Bluetooth_rx + 3);
			value = atoi(Payload);
			mainConfig.upperLimit = (uint16_t) value;
			_FRAM.write(0x0001,(uint8_t *) &mainConfig, sizeof(mainConfig), kI2C_TransferDefaultFlag);
		}

		// W12 command to set Tightening Torque setting
		else if(strcmp(Header, "W12") == 0){
			strcpy(Payload, (char *) Bluetooth_rx + 3);
			value = atoi(Payload);
			mainConfig.target = (uint16_t) value;
			_FRAM.write(0x0001,(uint8_t *) &mainConfig, sizeof(mainConfig), kI2C_TransferDefaultFlag);
			targetSet = true;
		}
		message_recieved = false;
		memset(&Header, '\0', 4);
	}

}



