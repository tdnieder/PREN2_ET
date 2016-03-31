/*
 * mulde.c
 *
 *  Created on: 01.03.2016
 *      Author: danie
 */
#include "mulde.h"



void initMulde(){
	Mulde_leeren_Enable();
	Mulde_leeren_SetRatio16(0);
	Mulde_leeren_Disable();
	unloadThrough();
}

void turnempty(){
	Mulde_leeren_Enable();
	Mulde_leeren_SetRatio16(100);
	Mulde_leeren_Disable();
}

void turnback(){
	Mulde_leeren_Enable();
	Mulde_leeren_SetRatio16(0);
	Mulde_leeren_Disable();
}

void unloadThrough(){
	turnempty();
	turnback();
}
