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
void initEngines(void){
	MotorBit_SetDir(true);//PTE2
	MotorBit_SetVal();

	motor_links_SetDutyUS(10);//PTE22
	motor_rechts_SetDutyUS(10);//PTB3

	motor_links_SetRatio16(50);
	motor_rechts_SetRatio16(50);
}
