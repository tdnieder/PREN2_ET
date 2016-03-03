/*
 * interface.c
 *
 *  Created on: 02.03.2016
 *      Author: danie
 */

/*
 * Ist mit dem PI verbunden unendliche schlaufe.
 */
char *functionName;
char *param1;
char *param2;

void CDC_Run(void){
	int i;
	int k;
	char* word;
	for(;;){	//endless loop
		while(CDC1_App_Task(cdc_buffer, sizeof(cdc_buffer))==ERR_BUSOFF){
		}

		//Warten bis Funktion ausgeführt wird Lockout!!

		if(CDC1_GetCharsInRxBuf() != 0){
			i = 0;
			while(i < sizeof(in_buffer)-1 && CDC1_GetChar(&in_buffer[i])==ERR_OK){
				i++;
			}
			in_buffer[i] = '\0';
			while(in_buffer == NULL){
			word = stringToken(in_buffer);
			switchCase(word);
			}
		}
		else{
			WAIT1_Waitms(10);
		}
	}
}
/*
 * Sollte den String in_buffer in Stücke zerteilen und einzelne Stücke zurückgeben
 */
char* stringToken(char* answer){
	char delimiter[] = ",;";

	functionName = strtok(answer, delimiter);

	while(functionName != NULL) {
		(void)CDC1_SendString(functionName);
		(void)CDC1_SendString((unsigned char*)"\r\n");
	 	functionName = strtok(NULL, delimiter);
	}
	return functionName;
}
/*
 * wählt mit dem String eine Funktion auf.
 * Parameter fehlt noch
 */
void switchCase(char* funtion){
	switch(function)
	{
	   case "init":
		   initEngines();
	   break;

	   case "takeContainer":
	       //statements
	   break;

	   case "setCorrectionAngle":
	       //statements
	   break;

	   case "getDistance":
	       //statements
	   break;

	   case "checkEnemy":
		   //statements
	   break;

	   case "unloadThrough":
		   //statements
	   break;

	   case "setGrabberPosition":
		   //statements
	   break;

	   case "setSpeed":
		   //statements
	   break;

	}
}

/*
void CDC_Run(void){
	int i;
	int k;
	char* word;
	for(;;){	//endless loop
		while(CDC1_App_Task(cdc_buffer, sizeof(cdc_buffer))==ERR_BUSOFF){
			// device not enumerated
			//LEDRed_Neg(); LEDGreen_Off();
			WAIT1_Waitms(10);
		}
		//LEDRed_Off(); LEDGreen_Neg();
		if(CDC1_GetCharsInRxBuf() != 0){
			i = 0;
			while(i < sizeof(in_buffer)-1 && CDC1_GetChar(&in_buffer[i])==ERR_OK){
				i++;
			}
			in_buffer[i] = '\0';
			while(in_buffer == NULL){
			word = stringToken(in_buffer);
			(void)CDC1_SendString((unsigned char*)"echo: ");
			(void)CDC1_SendString(in_buffer);
			(void)CDC1_SendString((unsigned char*)"\r\n");
			}
		}
		else{
			WAIT1_Waitms(10);
		}
	}
}

*/
