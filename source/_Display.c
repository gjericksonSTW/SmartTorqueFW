/*
 * _Display.c

 *
 *  Created on: Jun 26, 2017
 *      Author: gerickson
 */

#include "_Display.h"

/*******************************************************************************
 * Code
 ******************************************************************************/

// Configure general settings for the display driver
void Display_Init(void){

	slcd_config_t config;
	slcd_clock_config_t clkConfig = {
			kSLCD_AlternateClk1,
			kSLCD_AltClkDivFactor256,
	        kSLCD_ClkPrescaler01,
			false};

	SLCD_GetDefaultConfig(&config);

	/* Verify and Complete the configuration structure. */
	config.clkConfig = &clkConfig;
	config.loadAdjust = kSLCD_HighLoadOrSlowestClkSrc;
	config.dutyCycle = kSLCD_1Div4DutyCycle;
	config.slcdLowPinEnabled = 0x0d10c000U;  /* LCD_P27/26/24/20 -> b27/26/24/20 = 1. */
	config.slcdHighPinEnabled = 0x18001d00U; /* LCD_P44/43/42/40 -> b12/11/10/8 = 1. */
	config.backPlaneLowPin = 0x0000c000U;    /* LCD_P15/P14 -> b15/b14 = 1. */
	config.backPlaneHighPin = 0x18000000U;   /* LCD_P60/P59 -> b28/27 = 1. */
	config.faultConfig = NULL;

	/* SLCD Initialize. */
	SLCD_Init(LCD, &config);
	SLCD_SetBackPlanePhase(LCD, 59, kSLCD_PhaseAActivate); /* SLCD COM1 --- LCD_P59. */
	SLCD_SetBackPlanePhase(LCD, 60, kSLCD_PhaseBActivate); /* SLCD COM2 --- LCD_P60. */
	SLCD_SetBackPlanePhase(LCD, 14, kSLCD_PhaseCActivate); /* SLCD COM3 --- LCD_P14. */
	SLCD_SetBackPlanePhase(LCD, 15, kSLCD_PhaseDActivate); /* SLCD COM4 --- LCD_P15. */

	SLCD_StartDisplay(LCD);
}

//Wrapper for entering LCD blinker mode
void Display_Blink(void){
	SLCD_StartBlinkMode(LCD, kSLCD_AltDisplayBlink, kSLCD_BlinkRate03);
}

//Wrapper for exiting LCD blinker mode
void Display_Stop_Blink(void){
	SLCD_StopBlinkMode(LCD);
}

//Breakdown digits of numeric to be sent to LCD
void Set_Display(uint16_t num, uint8_t dp){

	uint8_t o, ten, h, th;

	o = num % 10;
	ten = ((num / 10) % 10);
	h = ((num / 100) % 10);
	th = ((num / 1000) % 10);

	Display_Number(th, 20, 24, dp);
	Display_Number(h, 26, 27, dp);
	Display_Number(ten, 40, 42, dp);
	Display_Number(o, 43, 44, 0);
	if(dp == 3){
		SLCD_SetFrontPlaneOnePhase(LCD, 42, kSLCD_PhaseAIndex, 1);
	}
}

//Activating the segments of the LCD for each number
void Display_Number(uint8_t num, uint8_t pin1, uint8_t pin2, uint8_t dp){
	switch (num){
	case 1:
		SLCD_SetFrontPlaneSegments(LCD, pin1, 0);
		SLCD_SetFrontPlaneSegments(LCD, pin2, 2 | 4);
		break;

	case 2:
		SLCD_SetFrontPlaneSegments(LCD, pin1, 1 | 2 | 4);
		SLCD_SetFrontPlaneSegments(LCD, pin2,  4 | 8);
		break;

	case 3:
		SLCD_SetFrontPlaneSegments(LCD, pin1, 1 | 4);
		SLCD_SetFrontPlaneSegments(LCD, pin2, 2 | 4 | 8);
		break;

	case 4:
		SLCD_SetFrontPlaneSegments(LCD, pin1, 4 | 8);
		SLCD_SetFrontPlaneSegments(LCD, pin2, 2| 4);
		break;

	case 5:
		SLCD_SetFrontPlaneSegments(LCD, pin1, 1 | 4 | 8);
		SLCD_SetFrontPlaneSegments(LCD, pin2, 2 | 8);
		break;

	case 6:
		SLCD_SetFrontPlaneSegments(LCD, pin1, 1 | 2 | 4 | 8);
		SLCD_SetFrontPlaneSegments(LCD, pin2, 2 | 8);
		break;

	case 7:
		SLCD_SetFrontPlaneSegments(LCD, pin1, 0);
		SLCD_SetFrontPlaneSegments(LCD, pin2, 2 | 4 | 8);
		break;

	case 8:
		SLCD_SetFrontPlaneSegments(LCD, pin1, 1 | 2 | 4 | 8);
		SLCD_SetFrontPlaneSegments(LCD, pin2, 2| 4| 8);
		break;

	case 9:
		SLCD_SetFrontPlaneSegments(LCD, pin1, 4 | 8);
		SLCD_SetFrontPlaneSegments(LCD, pin2, 2 | 4 | 8);
		break;

	case 0:
		SLCD_SetFrontPlaneSegments(LCD, pin1, 1 | 2 | 8);
		SLCD_SetFrontPlaneSegments(LCD, pin2, 2 | 4 | 8);
		break;
	}
}

