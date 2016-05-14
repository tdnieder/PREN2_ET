/*
 * Color.c
 *
 *  Created on: 27.04.2016
 *      Author: Daniel Klauser
 */
#include "SwitchGreen.h"
#include "SwitchBlue.h"

char* buttonPressed() {
	bool blue = 1;
	bool green = 1;

	int loop = 1;

	while (loop) {
		blue = SwitchBlue_GetRawVal();
		green = SwitchGreen_GetRawVal();

		if ((blue == 0) || (green == 0)) {
			loop = 0;
		}
	}
	if (green == 1) {
		return "green";
	}
	if (blue == 1) {
		return "blue";
	}
}
