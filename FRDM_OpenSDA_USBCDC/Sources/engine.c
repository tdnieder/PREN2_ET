/*
 * engine.c
 *
 *  Created on: 01.03.2016
 *      Author: danie
 */
# include "engine.h"


/**
 * Initialisiert den Motor mit 0.1Mhz und den Duty Cycle mit 50 %
 * ausserdem wurde das BIT noch gesetzt PTE2 auf 1
 */
 uint16 counterLeft;
 uint16 counterRight;

void initEngines(void){
	MotorBit_SetDir(true);//PTE2
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

/*
 * Pro Durchgang plus eins
 */
interrupt motor_links_OnEnd(){
	counterLeft = 1+counterLeft;
}

/*
 * Pro Durchgang plus eins
 */
interrupt motor_rechts_OnEnd(){
	counterRight = 1+counterRight;
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
