/*
 * interface.c

 *
 *  Created on: 02.03.2016
 *      Author: danie
 */
#include "interface.h"
#include "Cpu.h"
#include "Events.h"
#include "LEDRed.h"
#include "LEDpin1.h"
#include "BitIoLdd1.h"
#include "LEDGreen.h"
#include "LEDpin2.h"
#include "BitIoLdd2.h"
#include "LEDBlue.h"
#include "LEDpin3.h"
#include "BitIoLdd3.h"
#include "WAIT1.h"
#include "USB1.h"
#include "USB0.h"
#include "CDC1.h"
#include "Tx1.h"
#include "Rx1.h"
#include "motor_links.h"
#include "PwmLdd1.h"
#include "TU1.h"
#include "motor_rechts.h"
#include "PwmLdd2.h"
#include "MS1.h"
#include "BitIoLdd4.h"

#define RaumTemperatur 20

static uint8_t cdc_buffer[USB1_DATA_BUFF_SIZE];
static uint8_t in_buffer[USB1_DATA_BUFF_SIZE];
char* functionName;
char* param1;
char* param2;
int returnValue;

/*
 * Sollte den String in_buffer in Stücke zerteilen und einzelne Stücke zurückgeben
 */
void cutString(char* answer) {
	//Danach wird getrennt
	char delimiter[2] = ";";
	functionName = (char*) strtok(answer, delimiter);
	if (functionName != NULL) {
		param1 = (char*) strtok(NULL, delimiter);
		if (param1 != NULL) {
			param2 = (char*) strtok(NULL, delimiter);
		}
	}

}
/*
 * wählt mit dem String eine Funktion auf.
 * Parameter fehlt noch
 */
void switchCase(char* function) {
	if (strcmp(function, "initEngines") == 0) {
		LEDGreen_Off();
		initEngines();
		CDC1_SendString("go;");
	}
    if (strcmp(function, "setCorrectionAngle") == 0) {
    	calcVelocityToNumber(atoi(param1));
    }
    if (strcmp(function, "setSpeedLeft") == 0) {
    	setTimerFrequencyLeft(atoi(param1));
    }
    if (strcmp(function, "setSpeedRight") == 0) {
    	setTimerFrequencyRight(atoi(param1));
    }
    if (strcmp(function, "getDistanceEnemy") == 0) {
    	CDC1_SendString((char*) US_usToCentimeters(US_Measure_us(), RaumTemperatur));//checkEnemy
    }
    if (strcmp(function, "checkEnemy") == 0) {
    	CDC1_SendString((char*) US_usToCentimeters(US_Measure_us(), RaumTemperatur));//checkEnemy
    }
    if (strcmp(function, "unloadThrough") == 0) {
    	initMulde();
    }
    if (strcmp(function, "setGrabberPosition") == 0) {
    	//setGrabberPosition(param1,param2);
    }
    if (strcmp(function, "setSpeed") == 0) {
    	setSpeed(atoi(param1));
    }
    if (strcmp(function, "takeContainer") == 0) {
    	grab();
    }
    if(strcmp(function, "battery")){
    	CDC1_SendString((char*)measureBattery());
    }
    if(strcmp(function, "getDistance")){
    	CDC1_SendString((char*)calcDistance());//in cm
    }

	//clear Variablen!!
	functionName = "NULL";
	param1 = "NULL";
	param2 = "NULL";
}

void CDC_Run() {
	int i;
	int k;
	char* word;
	for (;;) {	//endless loop
		while (CDC1_App_Task(cdc_buffer, sizeof(cdc_buffer)) == ERR_BUSOFF) {
			LEDRed_On();
			WAIT1_Waitms(10);
		}
		LEDRed_Off();LEDGreen_On();
		if (CDC1_GetCharsInRxBuf() != 0) {
			i = 0;
			while (i < sizeof(in_buffer) - 1
					&& CDC1_GetChar(&in_buffer[i]) == ERR_OK) {
				i++;
			}
			in_buffer[i] = '\0';
			cutString((char*) in_buffer);
			switchCase(functionName);
		} else {
			WAIT1_Waitms(10);
		}
	}
}

