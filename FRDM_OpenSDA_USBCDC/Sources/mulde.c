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
int ForwardDuty = 60000;
int BackwardDuty = 61000;

void initMulde(){
	unloadThrough();
}

void turnempty(){
	Mulde_leeren_SetRatio16(ForwardDuty);
}

void turnbackThrough(){
	Mulde_leeren_SetRatio16(BackwardDuty);
}
void stopMulde(){
	Mulde_leeren_SetRatio16(MuldenDutyStop);
}
/*
 * Entleert mit 3 maligem nachrütteln
 */
void unloadThrough(){
	int i = 1;
	Status.Timer0 == TIMER_USED;
	turnempty();
	WAIT1_Waitms(600);
	Mulde_leeren_SetRatio16(MuldenDutyStop);

	while(i != 3){
	WAIT1_Waitms(200);
	turnbackThrough();
	WAIT1_Waitms(200);
	turnempty();
	WAIT1_Waitms(200);
	Mulde_leeren_SetRatio16(MuldenDutyStop);
	i++;
	}

	Mulde_leeren_SetRatio16(MuldenDutyStop);
	WAIT1_Waitms(200);
	turnbackThrough();
	WAIT1_Waitms(283);
	Mulde_leeren_SetRatio16(MuldenDutyStop);
}


void smooth(){
	Mulde_leeren_SetRatio16(BackwardDuty);
	WAIT1_Waitms(50);
	Mulde_leeren_SetRatio16(MuldenDutyStop);
}

void smoothBack(){
	Mulde_leeren_SetRatio16(ForwardDuty);
	WAIT1_Waitms(40);
	Mulde_leeren_SetRatio16(MuldenDutyStop);
}
