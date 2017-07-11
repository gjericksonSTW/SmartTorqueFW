/*
 * _Display.h
 *
 *  Created on: Jun 26, 2017
 *      Author: gerickson
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

/*******************************************************************************
 * Libraries
 ******************************************************************************/

#include "fsl_slcd.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "fsl_port.h"


/*******************************************************************************
 * Prototypes
 ******************************************************************************/

void Display_Init(void);
void Set_Display(uint16_t num, uint8_t dp);
void Display_Blink(void);
void Display_Stop_Blink(void);
void Display_Number(uint8_t num, uint8_t pin1, uint8_t pin2, uint8_t dp);

#endif /* DISPLAY_H_ */
