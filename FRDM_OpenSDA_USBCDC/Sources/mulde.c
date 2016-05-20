/*
 * mulde.c
 *
 *  Created on: 01.03.2016
 *      Author: danie
 */
#include "mulde.h"

extern int Duty1ms;
extern int Duty2ms;

int MuldenDutyStop = 65999;
int ForwardDuty = 61000;
int BackwardDuty = 60000;

void initMulde(){
	unloadThrough();
}

void turnempty(){

	Mulde_leeren_SetRatio16(ForwardDuty);


}

void turnbackThrough(){

	Mulde_leeren_SetRatio16(BackwardDuty);

}

void unloadThrough(){
	Status.Timer0 == TIMER_USED;
	turnempty();
	WAIT1_Waitms(1200);

	Mulde_leeren_SetRatio16(MuldenDutyStop);

	WAIT1_Waitms(2000);
	turnbackThrough();
	WAIT1_Waitms(1200);

	Mulde_leeren_SetRatio16(MuldenDutyStop);

	Status.Timer0 == TIMER_IDLE;
}
