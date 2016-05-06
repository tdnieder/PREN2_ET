/*
 * Color.c
 *
 *  Created on: 27.04.2016
 *      Author: Daniel Klauser
 */
#include "SwitchGreen.h"
#include "SwitchBlue.h"


int buttonPressed(){
	int blue = 0;
	int green = 0;

	int loop = 1;
	SwitchGreen_SetInput();
	SwitchBlue_SetInput();

	while(1){
		blue = SwitchBlue_GetRawVal();
		green = SwitchGreen_GetRawVal();

		if((blue ==1)||(green==1)){
			loop = 0;
		}
	}
	if(green == 1){
		return 1;
	}
	if(blue == 1){
		return 2;
	}
}
