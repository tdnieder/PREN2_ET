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
char distanceEnemyArray[8];
char colorArray[8];

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
		initEngines();
		CDC1_SendString((char*) "go\n");

	} else if (strcmp(function, "setSpeedLeft") == 0) {
		setTimerFrequencyLeft(atoi(param1));
		CDC1_SendString((char*) "go\n");

	} else if (strcmp(function, "setEngineSteps") == 0) {
		setEngineSteps(atoi(param1));
		CDC1_SendString((char*) "go\n");

	} else if (strcmp(function, "setSpeedRight") == 0) {
		setTimerFrequencyRight(atoi(param1));
		CDC1_SendString((char*) "go\n");

	} else if (strcmp(function, "setSpeed") == 0) {
		setSpeed(atoi(param1));
		CDC1_SendString((char*) "go\n");

	} else if (strcmp(function, "getDistance") == 0) {
		int j = 0;
		sprintf(distanceArray, "%i\n", calcDistance());
		CDC1_SendString(distanceArray);
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
		setGrabber(atoi(param1), atoi(param2));
		CDC1_SendString((char*) "go\n");
	}

	else if (strcmp(function, "emptyContainer") == 0) {
		turnBackGrabber();
		WAIT1_Waitms(3000);
		turnGrabber();
		CDC1_SendString((char*) "go\n");
	}

	else if (strcmp(function, "openCloseGrabber") == 0) {
		if (atoi(param1) == 1) {
			grab();
			CDC1_SendString((char*) "go\n");
		} else if (atoi(param1) == 2) {
			openGreifer();
			CDC1_SendString((char*) "go\n");
		}
	} else if (strcmp(function, "setGrabberBack()") == 0) {
		setGrabberBack();
		CDC1_SendString((char*) "go\n");
	}

	else if (strcmp(function, "backToEnd") == 0) {
		backToEnd();
		DC_Greifer_Schiene_Horizontal_SetRatio16(0);
		CDC1_SendString((char*) "go\n");
	} else if (strcmp(function, "upToEnd") == 0) {
		upToEnd();
		DC_Greifer_Schiene_Vertikal_SetRatio16(0);
		CDC1_SendString((char*) "go\n");
	} else if (strcmp(function, "frontToEnd") == 0) {
		frontToEnd();
		DC_Greifer_Schiene_Horizontal_SetRatio16(0);
		CDC1_SendString((char*) "go\n");
	}

	/*
	 * ENDE GREIFER
	 */

	/*
	 * MULDE
	 */
	else if (strcmp(function, "unloadThrough") == 0) {
		initMulde();
		CDC1_SendString((char*) "go\n");
	}
	/*
	 * ENDE MULDE
	 */

	/*
	 * SONTIGES
	 */
	else if (strcmp(function, "getDistanceEnemy") == 0) {
		int j = 0;
		US_Init();
		sprintf(distanceEnemyArray, "%d\n", Measure());
		CDC1_SendString(distanceEnemyArray);
		while (j != 7) {
			distanceEnemyArray[j] = 0;
			j++;
		}
	} else if (strcmp(function, "battery") == 0) {
		CDC1_SendString((char*) measureBattery()); //1 = leer
		CDC1_SendString((char*) "go\n");
	} else if (strcmp(function, "shutdown") == 0) {
		shitDown();
		CDC1_SendString((char*) "go\n");
	} else if (strcmp(function, "getColor") == 0) {
		sprintf(colorArray, "%i\n", buttonPressed());
		CDC1_SendString(colorArray);
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

	else if (strcmp(function, "testServo") == 0) {
		Mulde_leeren_Enable();
		Mulde_leeren_SetRatio16(atoi(param1));
		CDC1_SendString((char*) "go\n");
	}

	else if (strcmp(function, "testEndchalter") == 0) {
		int loop = 1;
		while (loop) {
			if (!AnschlagVertikalOben_GetRawVal()) {
				CDC1_SendString((char*) "Oben gedrückt");
				loop = 0;
			} else if (!AnschlagHorizontalVorne_GetRawVal()) {
				CDC1_SendString((char*) "Vorne gedrückt");
				loop = 0;

			} else if (!AnschlagHorizontalHinten_GetRawVal()) {
				CDC1_SendString((char*) "Hinten gedrückt");
				loop = 0;
			}
		}
	}

	else if (strcmp(function, "testSwitch") == 0) {
		int loop = 1;
		while (loop) {
			if (!SwitchBlue_GetRawVal()) {
				CDC1_SendString((char*) "Blau");
				loop = 0;
			} else if (!SwitchGreen_GetRawVal()) {
				CDC1_SendString((char*) "Green");
				loop = 0;
			}
		}
	}

	else if (strcmp(function, "endeGelaende") == 0) {
		CDC1_SendString((char*) "go\n");
		exit(0);
		CDC1_SendString((char*) "go\n");
	}
	else if (strcmp(function, "begin") == 0) {
		main();
		CDC1_SendString((char*) "go\n");
	}

	/*
	 * ENDE TEST
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
//Damit der Counter der Strecke stoppt!
	motor_links_DisableEvent();
	motor_rechts_DisableEvent();
//Funktioniert irgendwie!!
//Modulo wieder zurücksetzen
	TPM0_MOD = 59999;
	TPM1_MOD = 59999;

//Stellt Motoren ab
	Enable_SetVal();

//Signale auf 0 setzen
	Mulde_leeren_SetRatio16(0xFFFF);
	Drehen_SetRatio16(0xFFFF);
	DC_Greifer_Schiene_Vertikal_SetRatio16(0xFFFF);
	Greifen_SetRatio16(0xFFFF);
	DC_Greifer_Schiene_Horizontal_SetRatio16(0xFFFF);
	motor_links_SetRatio16(0xFFFF);
	motor_rechts_SetRatio16(0xFFFF);
}

