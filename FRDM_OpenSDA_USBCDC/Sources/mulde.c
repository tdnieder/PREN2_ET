/*
 * mulde.c
 *
 *  Created on: 01.03.2016
 *      Author: danie
 */
#include "mulde.h"

extern int Duty1ms;
extern int Duty2ms;

void initMulde(){
	Mulde_leeren_Enable();
	unloadThrough();
}

void turnempty(){
	Mulde_leeren_Enable();
	Mulde_leeren_SetRatio16(Duty1ms);

}

void turnbackThrough(){
	Mulde_leeren_Enable();
	Mulde_leeren_SetRatio16(Duty2ms);

}

void unloadThrough(){
	Status.Timer0 == TIMER_USED;
	turnempty();
	WAIT1_Waitms(3000);
	turnbackThrough();
	Status.Timer0 == TIMER_IDLE;
}
