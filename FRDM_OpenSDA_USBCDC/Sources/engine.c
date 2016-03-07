/*
 * engine.c
 *
 *  Created on: 01.03.2016
 *      Author: danie
 */
# include "engine.h"

extern int counterLeft;
extern int counterRight;
/**
 * Initialisiert den Motor mit 0.1Mhz und den Duty Cycle mit 50 %
 * ausserdem wurde das BIT noch gesetzt PTE2 auf 1
 */

void initEngines(void){
//	(void)CDC1_SendString((unsigned char*)"\r\n");
//	(void)CDC1_SendString("Ist bei den Scheiss Motoren");
	LEDBlue_On();
	LEDGreen_Off();
	MotorBit_SetDir(1);//PTE2
	MotorBit_SetVal();
	motor_links_SetDutyUS(10);//PTE22
	motor_rechts_SetDutyUS(10);//PTB3

	motor_links_SetRatio16(50);
	motor_rechts_SetRatio16(50);
}


void setVelocityleft(int v){
	motor_links_SetDutyUS(v);//PTE22
}

void setVelocityright(int v){
	motor_rechts_SetDutyUS(v);//PTB3
}

void calcVelocityToNumber(int numberFromPi){

}

void calcVelocityToNumber2(int param1,int param2){

}


/*
 * Gibt den Counter Wert des Rechten Rades zurück
 */
int getValueRight(){
	return counterRight;
}
/*
 * Gibt den Counter Wert des Linken Rades zurück
 */
int getValueLeft(){
	return counterLeft;
}
