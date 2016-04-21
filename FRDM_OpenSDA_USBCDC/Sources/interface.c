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
#include "mulde.h"
#include "greifer.h"
#include "engine.h"

#define RaumTemperatur 20

static uint8_t cdc_buffer[USB1_DATA_BUFF_SIZE];
static uint8_t in_buffer[USB1_DATA_BUFF_SIZE];

extern int Duty1ms;
extern int Duty2ms;

char* functionName;
char* param1;
char* param2;
int returnValue;
int pk = 0;

/*
 * Sollte den String in_buffer in Stücke zerteilen und einzelne Stücke zurückgeben
 */
void cutString(char* answer) {
	//Danach wird getrennt crc
	char delimiter[] = ";";
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

	/*
	 * FAHREN
	 */
	if (strcmp(function, "initEngines") == 0) {
		if ((Status.Timer0 == TIMER_IDLE) && (Status.Timer1 == TIMER_IDLE)) {
			initEngines();
		} else {
			shitDown();
			initEngines();
		}
		CDC1_SendString((char*) "go\n");
	} else if (strcmp(function, "setSpeedLeft") == 0) {
		if ((Status.Timer0 == TIMER_USED) && (Status.Timer1 == TIMER_USED)) {
			setTimerFrequencyLeft(atoi(param1));
			CDC1_SendString((char*) "go\n");
		}
	} else if (strcmp(function, "setSpeedRight") == 0) {
		if ((Status.Timer0 == TIMER_USED) && (Status.Timer1 == TIMER_USED)) {
			setTimerFrequencyRight(atoi(param1));
			CDC1_SendString((char*) "go\n");
		}
	} else if (strcmp(function, "setSpeed") == 0) {
		if ((Status.Timer0 == TIMER_USED) && (Status.Timer1 == TIMER_USED)) {
			setSpeed(atoi(param1));
			CDC1_SendString((char*) "go\n");
		}
	} else if (strcmp(function, "getDistance") == 0) {
		CDC1_SendString((char*) calcDistance()); //in cm
	}
	/*
	 * FAHREN ENDE
	 */

	/*
	 * GREIFER / MULDE
	 */
	else if (strcmp(function, "setGrabberPosition") == 0) {
		if ((Status.Timer0 == TIMER_IDLE)&&(Status.Timer1 == TIMER_IDLE)) {
			setGrabber(atoi(param1), atoi(param2));
		} else {
			shitDown();
			setGrabber(atoi(param1), atoi(param2));
		}
		CDC1_SendString((char*) "go\n");
	} else if (strcmp(function, "emptyContainer") == 0) {
		if (Status.Timer0 == TIMER_USED) {
			turnBackGrabber();
			WAIT1_Waitms(2000);
			turnGrabber();
		} else {
			shitDown();
			turnBackGrabber();
			WAIT1_Waitms(2000);
			turnGrabber();
		}
		CDC1_SendString((char*) "go\n");
	}

	else if (strcmp(function, "openCloseGrabber") == 0) {
		if (Status.Timer0 == TIMER_USED) {
			if (atoi(param1) == 1) {
				grab();
			}
			if (atoi(param1) == 2) {
				openGreifer();
			}
		} else {
			shitDown();
			if (atoi(param1) == 1) {
				grab();
			} else if (atoi(param1) == 2) {
				openGreifer();
			}
		}
		CDC1_SendString((char*) "go\n");
	}

	/*
	 * ENDE GREIFER
	 */

	/*
	 * MULDE
	 */
	else if (strcmp(function, "unloadThrough") == 0) {
		if (Status.Timer0 == TIMER_IDLE) {
			initMulde();
		} else {
			shitDown();
			initMulde();
		}
		CDC1_SendString((char*) "go\n");
	}
	/*
	 * ENDE MULDE
	 */

	/*
	 * SONTIGES
	 */
	else if (strcmp(function, "getDistanceEnemy") == 0) {
		Status.Timer2 = TIMER_USED;
		CDC1_SendString((char*) Measure());
		Status.Timer2 = TIMER_IDLE;
	} else if (strcmp(function, "battery") == 0) {
		CDC1_SendString((char*) measureBattery()); //1 = leer
		CDC1_SendString((char*) "go\n");
	} else if (strcmp(function, "shutdown") == 0) {
		shitDown();
		CDC1_SendString((char*) "go\n");
	}
	/*
	 * ENDE SONTIGES
	 */
	functionName = 0;
	param1 = 0;
	param2 = 0;
}

void CDC_Run() {
	int i;
	for (;;) {	//endless loop
		while (CDC1_App_Task(cdc_buffer, sizeof(cdc_buffer)) == ERR_BUSOFF) {
			LEDRed_On();
			WAIT1_Waitms(10);
		}
		if (CDC1_GetCharsInRxBuf() != 0) {
			i = 0;
			while ((i < (sizeof(in_buffer) - 1))
					&& (CDC1_GetChar(&in_buffer[i]) == ERR_OK)) {
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

void shitDown() {
	motor_rechts_Disable();
	motor_links_Disable();
	Mulde_leeren_Disable();
	DC_Greifer_Schiene_Horizontal_Disable();
	DC_Greifer_Schiene_Vertikal_Disable();
	Greifen_Disable();
	Drehen_Disable();

	Status.Timer0 = TIMER_IDLE;
	Status.Timer1 = TIMER_IDLE;
}

