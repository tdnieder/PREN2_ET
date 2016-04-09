/*
 * mulde.c
 *
 *  Created on: 01.03.2016
 *      Author: danie
 */
#include "mulde.h"



void initMulde(){
	Mulde_leeren_Enable();
	//Mulde_leeren_SetRatio16(65000);
	unloadThrough();
}

void turnempty(){
	Mulde_leeren_Enable();
	Mulde_leeren_SetRatio16(59000);

}

void turnbackThrough(){
	Mulde_leeren_Enable();
	Mulde_leeren_SetRatio16(62500);

}

void unloadThrough(){
	turnempty();
	WAIT1_Waitms(3000);
	turnempty();
}
