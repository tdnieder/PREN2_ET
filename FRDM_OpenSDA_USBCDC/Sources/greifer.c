/*
 * greifer.c
 *
 *  Created on: 01.03.2016
 *      Author: danie
 */

#include "greifer.h"

//Zeit um Reset Wert
int timeVertical;
int timeHorizontal;
int timeToTurn = 0;

/*
 * Initialisiert die Servos
 */

/*
 * Greift nach dem Objekt, Servos sollte sich schliessen
 */
void grab() {
	if (Status.Timer0 == TIMER_IDLE) {
		Greifen_Enable();
		Greifen_SetRatio16(Duty2ms);
		//Greifen_SetDutyMS(2);
		Status.Timer0 == TIMER_USED;

	} else {
		shitDown();
		Greifen_Enable();
		Greifen_SetRatio16(Duty2ms);
		//Greifen_SetDutyMS(2);
		Status.Timer0 == TIMER_USED;
	}
}
/*
 * Öffnet den Greifer Arm
 */
void openGreifer() {
	if (Status.Timer0 == TIMER_IDLE) {
		Greifen_Enable();
		Greifen_SetRatio16(Duty1ms);
		//Greifen_SetDutyMS(1);
		Status.Timer0 == TIMER_USED;
	} else {
		shitDown();
		Greifen_SetRatio16(Duty1ms);
		//Greifen_SetDutyMS(1);
		Status.Timer0 == TIMER_USED;

	}
}

/*
 * Nachdem der Greifer hochgefahren ist, sollte er den
 * Greifer sammt Tonne drehen und ausleeren
 */
void turnGrabber(void) {
	if (Status.Timer0 == TIMER_IDLE) {
		Greifen_Enable();
		Greifen_SetRatio16(Duty2ms);
		Drehen_Enable();
		Drehen_SetRatio16(Duty1ms);
		//Drehen_SetDutyMS(1);
		Status.Timer0 == TIMER_USED;
	} else {
		shitDown();
		Greifen_Enable();
		Greifen_SetRatio16(Duty2ms);
		Drehen_Enable();
		Drehen_SetRatio16(Duty1ms);
		//Drehen_SetDutyMS(1);
		Status.Timer0 == TIMER_USED;
	}

}

/*
 * Dreht den Greiferarm wieder zurück
 */
void turnBackGrabber(void) {

	if (Status.Timer0 == TIMER_IDLE) {
		Greifen_Enable();
		Greifen_SetRatio16(Duty2ms);
		Drehen_Enable();
		Drehen_SetRatio16(Duty2ms);
		//Drehen_SetDutyMS(1);
		Status.Timer0 == TIMER_USED;
	} else {
		shitDown();
		Greifen_Enable();
		Greifen_SetRatio16(Duty2ms);
		Drehen_Enable();
		Drehen_SetRatio16(Duty2ms);
		//Drehen_SetDutyMS(1);
		Status.Timer0 == TIMER_USED;
	}
}

/*
 * Servo hat den Greifer zugepackt,
 * hät ihn gerade und fährt nun nach oben.
 */
void up() {
	if (Status.Timer1 == TIMER_IDLE) {
		up_bit();
		DC_Greifer_Schiene_Vertikal_Enable();

		DC_Greifer_Schiene_Vertikal_SetRatio16(30000);
		WAIT1_Waitms(100);
		DC_Greifer_Schiene_Vertikal_Disable();
		timeVertical += 10;
	} else {
		shitDown();
		up_bit();
		DC_Greifer_Schiene_Vertikal_Enable();
		DC_Greifer_Schiene_Vertikal_SetRatio16(30000);
		WAIT1_Waitms(100);
		DC_Greifer_Schiene_Vertikal_Disable();
		timeVertical += 10;
	}
}

/*
 * Fahrzeug ist an der Richtigen Stelle und fährt
 * den Greifer nun herunter
 */
void down() {
	if (Status.Timer1 == TIMER_IDLE) {
		down_bit();
		DC_Greifer_Schiene_Vertikal_Enable();
		DC_Greifer_Schiene_Vertikal_SetRatio16(30000);
		WAIT1_Waitms(100);
		DC_Greifer_Schiene_Vertikal_Disable();
		timeVertical -= 10;
	} else {
		shitDown();
		down_bit();
		DC_Greifer_Schiene_Vertikal_Enable();
		DC_Greifer_Schiene_Vertikal_SetRatio16(30000);
		WAIT1_Waitms(100);
		DC_Greifer_Schiene_Vertikal_Disable();
		timeVertical -= 10;
	}
}

/*
 * Bringt den ganzen Greifer nach vorne
 */
void forward() {
	if (Status.Timer0 == TIMER_IDLE) {
		forward_bit();
		DC_Greifer_Schiene_Horizontal_Enable();
		DC_Greifer_Schiene_Horizontal_SetRatio16(30000);
		WAIT1_Waitms(100);
		DC_Greifer_Schiene_Horizontal_Disable();
		timeHorizontal += 10;
	} else {
		shitDown();
		forward_bit();
		DC_Greifer_Schiene_Horizontal_Enable();
		DC_Greifer_Schiene_Horizontal_SetRatio16(30000);
		WAIT1_Waitms(100);
		DC_Greifer_Schiene_Horizontal_Disable();
		timeHorizontal += 10;
	}
}
/*
 * Bring den Greifer nach hinten.
 */
void backward() {
	if (Status.Timer0 == TIMER_IDLE) {
		backward_bit();
		DC_Greifer_Schiene_Horizontal_Enable();
		DC_Greifer_Schiene_Horizontal_SetRatio16(30000);
		WAIT1_Waitms(100);
		DC_Greifer_Schiene_Horizontal_Disable();
		timeHorizontal -= 10;
	} else {
		shitDown();
		backward_bit();
		DC_Greifer_Schiene_Horizontal_Enable();
		DC_Greifer_Schiene_Horizontal_SetRatio16(30000);
		WAIT1_Waitms(100);
		DC_Greifer_Schiene_Horizontal_Disable();
		timeHorizontal -= 10;
	}
}

/*
 * Setzt das Bit um Hochzufahren
 */
void up_bit() {
	DCVertikalBit_SetVal();
}
/*
 * Setzt das Bit so um wieder runterzufahren
 */
void down_bit() {
	DCVertikalBit_ClrVal();
}
/*
 * Setzt das Bit um nach vorne zu fahren
 */
void forward_bit() {
	DCHorizontalBit_SetVal();
}
/*
 * Setzt das Bit um nach hinten zu fahren
 */
void backward_bit() {
	DCHorizontalBit_ClrVal();
}

void setGrabber(int Hor, int Vert) {
	ModeDC_SetVal();
	if (Hor == 1) {
		forward(); //Richtung container
	} else if (Hor == 2) {
		backward();
	}
	if (Vert == 1) {
		up();
	} else if (Vert == 2) {
		down();
	}
}

void setGrabberBack() {
	int dummy = 0;
/*	int vert = timeVertical / 10;
	int hor = timeHorizontal / 10;
	int counter = 0;

	if (vert >= 0) {
		for (counter; counter < vert; counter++) {
			down();
		}
	} else {
		for (counter; counter < (-1)*vert; counter++) {
			up();
		}
	}

	counter = 0;

	if (hor >= 0) {
		for (counter; counter < vert; counter++) {
			backward();
		}
	} else {
		for (counter; counter < (-1)*vert; counter++) {
			forward();
		}
	}*/
	while(!AnschlagVertikalOben_GetRawVal()){
		up();
	}
	WAIT1_Waitms(100);
	while(!AnschlagHorizontalVorne_GetRawVal()){
		forward();
	}
	WAIT1_Waitms(100);
	for(dummy; dummy < 10;dummy++){
		down();
	}
	WAIT1_Waitms(100);
	openGreifer();
	WAIT1_Waitms(500);
	while(!AnschlagHorizontalHinten_GetRawVal()){
		backward();
	}
}

void setModeBitDc(void) {
	ModeDC_PutVal(TRUE);
}

