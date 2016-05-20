/*
 * battery.c
 *
 *  Created on: 29.03.2016
 *      Author: Daniel Klauser
 */


#include "stdbool.h"
#include "inttypes.h"
#include "LEDRed.h"
#include "LEDGreen.h"
#include "LEDBlue.h"
#include "WAIT1.h"


//Wert den die Batterie nicht unterschreiten darf.
#define BatValue 45700 //2.30V bei unterschreiten Akku unten.

uint16_t value;




int measureBattery(){
	//AD_finished = true;
	(void)Battery_Measure(false);
	WAIT1_Waitus(10);
	(void)Battery_GetValue16(&value);
	if(value <= BatValue){
		return 1;
	}
	return 0;
}

