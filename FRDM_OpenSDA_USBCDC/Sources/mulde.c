/*
 * mulde.c
 *
 *  Created on: 01.03.2016
 *      Author: danie
 */

void init(void){
	Mulde_Leeren_Enable();
	Mulde_Leeren_SetRatio16(0);
	Mulde_Leeren_Disable();
}

void turnempty(void){
	Mulde_Leeren_Enable();
	Mulde_Leeren_SetRatio16(100);
	Mulde_Leeren_Disable();
}

void turnback(void){
	Mulde_Leeren_Enable();
	Mulde_Leeren_SetRatio16(0);
	Mulde_Leeren_Disable();
}
