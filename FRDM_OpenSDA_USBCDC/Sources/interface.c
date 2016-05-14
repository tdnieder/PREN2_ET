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
#include "Color.h"
#include <stdio.h>
#include <stdlib.h>

#define RaumTemperatur 20

static uint8_t cdc_buffer[USB1_DATA_BUFF_SIZE];
static uint8_t in_buffer[USB1_DATA_BUFF_SIZE];

extern int Duty1ms;
extern int Duty2ms;

char distanceArray[8];

char* functionName;
char* param1;
char* param2;
int returnValue;
int pk = 0;

/*
 * Sollte den String in_buffer in St�cke zerteilen und einzelne St�cke zur�ckgeben
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
 * w�hlt mit dem String eine Funktion auf.
 * Parameter fehlt noch
 */
void switchCase(char* function) {

	/*
	 * FAHREN
	 */
	if (strcmp(function, "initEngines") == 0) {
		Enable_ClrVal();
		motor_rechts_EnableEvent();
		motor_links_EnableEvent();
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
		int j = 0;
		sprintf(distanceArray, "%i", calcDistance());
		CDC1_SendString(distanceArray);
		CDC1_SendString((char*) "\n go\n");
		while (j != 7) {
			distanceArray[j] = 0;
			j++;
		}
	}
	/*
	 * FAHREN ENDE
	 */

	/*
	 * GREIFER / MULDE
	 */
	else if (strcmp(function, "setGrabberPosition") == 0) {
		if ((Status.Timer0 == TIMER_IDLE) && (Status.Timer1 == TIMER_IDLE)) {
			setGrabber(atoi(param1), atoi(param2));
		} else {
			shitDown();
			setGrabber(atoi(param1), atoi(param2));
		}
		CDC1_SendString((char*) "go\n");
	} else if (strcmp(function, "emptyContainer") == 0) {
		if (Status.Timer0 == TIMER_IDLE) {
			Greifen_Enable(); //test

			turnBackGrabber();
			WAIT1_Waitms(2000);
			turnGrabber();
		} else {
			shitDown();
			Greifen_Enable(); //test

			turnBackGrabber();
			WAIT1_Waitms(2000);
			turnGrabber();
		}
		CDC1_SendString((char*) "go\n");
	}

	else if (strcmp(function, "openCloseGrabber") == 0) {
		if (Status.Timer0 == TIMER_IDLE) {
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
	} else if (strcmp(function, "setGrabberBack()") == 0) {
		if (Status.Timer0 == TIMER_IDLE) {
			setGrabberBack();
		} else {
			setGrabberBack();
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
		CDC1_SendString((char*) "go\n");
	} else if (strcmp(function, "battery") == 0) {
		CDC1_SendString((char*) measureBattery()); //1 = leer
		CDC1_SendString((char*) "go\n");
	} else if (strcmp(function, "shutdown") == 0) {
		shitDown();
		CDC1_SendString((char*) "go\n");
	} else if (strcmp(function, "color") == 0) {
		CDC1_SendString((char*) buttonPressed());
		CDC1_SendString((char*) "go\n");
	}
	/*
	 * ENDE SONTIGES
	 */

	/*
	 * TEST
	 */
 else if (strcmp(function, "LED") == 0) {
		if (atoi(param1) == 1) {
			LEDRed_On();
		} else if (atoi(param1) == 2) {
			LEDGreen_On();
		} else if (atoi(param1) == 3) {
			LEDBlue_On();
		} else if (atoi(param1) == 4) {
			LEDRed_Off();
		} else if (atoi(param1) == 5) {
			LEDGreen_Off();
		} else if (atoi(param1) == 6) {
			LEDBlue_Off();
		}
		CDC1_SendString((char*) "go\n");
	}


	/*
	 * TEST
	 */
	functionName = 0;
	param1 = 0;
	param2 = 0;
}

void CDC_Run() {
	int i;
	for (;;) {	//endless loop
		while (CDC1_App_Task(cdc_buffer, sizeof(cdc_buffer)) == ERR_BUSOFF) {
			//LEDRed_On();
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
/*
 * Gilt als Reset aller Signale
 */
void shitDown() {
	motor_links_DisableEvent();
	motor_rechts_DisableEvent();
	//Funktioniert irgendwie!!
	TPM0_MOD = 59999;
	TPM1_MOD = 59999;
	//Modulo wieder zur�cksetzen
	Enable_SetVal();	//Stellt Motoren ab
	//@Todo schauen ob Signal weiter l�uft! Sollte mit Enable aufh�ren -> f�r Counter der Strecke.
	Greifen_Enable();
	Drehen_Enable();
	DC_Greifer_Schiene_Vertikal_Enable();
	DC_Greifer_Schiene_Horizontal_Enable();
	//Signale auf 0 setzen
	Mulde_leeren_SetRatio16(0xFFFF);
	Drehen_SetRatio16(0xFFFF);
	DC_Greifer_Schiene_Vertikal_SetRatio16(0xFFFF);
	Greifen_SetRatio16(0xFFFF);
	DC_Greifer_Schiene_Horizontal_SetRatio16(0xFFFF);
	Status.Timer0 = TIMER_IDLE;
	Status.Timer1 = TIMER_IDLE;
}
