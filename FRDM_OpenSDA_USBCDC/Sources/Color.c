/*
 * Color.c
 *
 *  Created on: 27.04.2016
 *      Author: Daniel Klauser
 */
#include "SwitchGreen.h"
#include "SwitchBlue.h"
#include "LEDBlue.h"
#include "LEDGreen.h"

int buttonPressed() {
	while (1) {
		if (!SwitchGreen_GetRawVal()) {
			LEDGreen_On();
			LEDBlue_Off();
			return 1;
		}
		else if (!SwitchBlue_GetRawVal()) {
			LEDBlue_On();
			LEDGreen_Off();
			return 2;
		}
	}
}
