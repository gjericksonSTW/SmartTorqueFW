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

//Initialize the pins required for controlling LCD display
void InitPins(void) {
  CLOCK_EnableClock(kCLOCK_PortB);                           /* Port B Clock Gate Control: Clock enabled */
  CLOCK_EnableClock(kCLOCK_PortC);                           /* Port C Clock Gate Control: Clock enabled */
  CLOCK_EnableClock(kCLOCK_PortD);                           /* Port D Clock Gate Control: Clock enabled */
  CLOCK_EnableClock(kCLOCK_PortE);                           /* Port E Clock Gate Control: Clock enabled */

  PORT_SetPinMux(PORTB, 18U, kPORT_PinDisabledOrAnalog); /* PORTB18 (pin 41) is configured as LCD_P14 */
  PORT_SetPinMux(PORTB, 19U, kPORT_PinDisabledOrAnalog); /* PORTB19 (pin 42) is configured as LCD_P15 */
  PORT_SetPinMux(PORTC, 0U, kPORT_PinDisabledOrAnalog); /* PORTC0 (pin 43) is configured as LCD_P20 */
  PORT_SetPinMux(PORTC, 4U, kPORT_PinDisabledOrAnalog); /* PORTC4 (pin 53) is configured as LCD_P24 */
  PORT_SetPinMux(PORTC, 6U, kPORT_PinDisabledOrAnalog); /* PORTC6 (pin 55) is configured as LCD_P26 */
  PORT_SetPinMux(PORTC, 7U, kPORT_PinDisabledOrAnalog); /* PORTC7 (pin 56) is configured as LCD_P27 */
  PORT_SetPinMux(PORTD, 0U, kPORT_PinDisabledOrAnalog); /* PORTD0 (pin 57) is configured as LCD_P40 */
  PORT_SetPinMux(PORTD, 2U, kPORT_PinDisabledOrAnalog); /* PORTD2 (pin 59) is configured as LCD_P42 */
  PORT_SetPinMux(PORTD, 3U, kPORT_PinDisabledOrAnalog); /* PORTD3 (pin 60) is configured as LCD_P43 */
  PORT_SetPinMux(PORTD, 4U, kPORT_PinDisabledOrAnalog); /* PORTD4 (pin 61) is configured as LCD_P44 */
  PORT_SetPinMux(PORTE, 20U, kPORT_PinDisabledOrAnalog); /* PORTE20 (pin 9) is configured as LCD_P59 */
  PORT_SetPinMux(PORTE, 21U, kPORT_PinDisabledOrAnalog); /* PORTE21 (pin 10) is configured as LCD_P60 */
}

//Configure general settings for the display driver
void Display_Init(void){

	InitPins();
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
	Set_Display(0);
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
void Set_Display(uint16_t num){

	uint8_t o, ten, h, th;

	o = num % 10;
	ten = ((num / 10) % 10);
	h = ((num / 100) % 10);
	th = ((num / 1000) % 10);

	Display_Number(th, 20, 24);
	Display_Number(h, 26, 27);
	Display_Number(ten, 40, 42);
	Display_Number(o, 43, 44);
}

//Activating the segments of the LCD for each number
void Display_Number(uint8_t num, uint8_t pin1, uint8_t pin2){
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

