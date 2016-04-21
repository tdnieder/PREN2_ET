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
	if (strcmp(function, "initEngines") == 0) {
		initEngines();
		CDC1_SendString((char*)"go\n");
	}
    if (strcmp(function, "setSpeedLeft") == 0) {
    	setTimerFrequencyLeft(atoi(param1));
    	CDC1_SendString((char*)"go\n");
    }
    if (strcmp(function, "setSpeedLeft") == 0) {
    	setTimerFrequencyRight(atoi(param1));
    	CDC1_SendString((char*)"go\n");
    }
    if (strcmp(function, "getDistanceEnemy") == 0) {
    	CDC1_SendString((char*)Measure());
    }
    if (strcmp(function, "unloadThrough") == 0) {
    	initMulde();
    	CDC1_SendString((char*)"go\n");
    }
    if (strcmp(function, "setGrabberPosition") == 0) {
    	setGrabber(atoi(param1),atoi(param2));
    	CDC1_SendString((char*)"go\n");
    }
    if (strcmp(function, "setSpeed") == 0) {
    	setSpeed(atoi(param1));
    	CDC1_SendString((char*)"go\n");
    }
    if (strcmp(function, "emptyContainer") == 0) {
    		initAllServos();
    		int Duty1msTurn = 59500;
    		int Duty2msTurn = 60500;
    		while(Duty1msTurn == Duty2msTurn){
    		turnGrabber(Duty1msTurn+100);
    		}
    		WAIT1_Waitms(4000);
    		while(Duty2msTurn == Duty1msTurn){
    			turnBackGrabber(Duty2msTurn-100);
    		}
    		CDC1_SendString((char*)"go\n");
    }
    if(strcmp(function, "battery") == 0){
    	CDC1_SendString((char*)measureBattery());//1 = leer
    	CDC1_SendString((char*)"go\n");
    }
    if(strcmp(function, "getDistance")==0){
    	CDC1_SendString((char*)calcDistance());//in cm
    }
    if(strcmp(function, "shutdown")==0){
    	motor_rechts_Disable();
    	motor_links_Disable();
    	Mulde_leeren_Disable();
    	DC_Greifer_Schiene_Horizontal_Disable();
    	DC_Greifer_Schiene_Vertikal_Disable();
    	CDC1_SendString((char*)"go\n");
    }
    if(strcmp(function, "openCloseGrabber")==0){
        	initAllServos();
        	if(atoi(param1) == 1){
        		grab();
        	}
        	if(atoi(param1) == 2){
        		openGreifer();
        	}
        	CDC1_SendString((char*)"go\n");
         }
	//clear Variablen!!
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
			while ((i < (sizeof(in_buffer) - 1)) && (CDC1_GetChar(&in_buffer[i]) == ERR_OK)) {
				i++;
			}
			in_buffer[i] = '\0';
			cutString((char*)in_buffer);
			switchCase(functionName);

		} else {
			WAIT1_Waitms(10);
		}
	}
}

