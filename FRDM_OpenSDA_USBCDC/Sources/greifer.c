/*
 * greifer.c
 *
 *  Created on: 01.03.2016
 *      Author: danie
 */

#include "greifer.h"
#include "AnschlagHorizontalVorne.h"
#include "AnschlagVertikalOben.h"
#include "AnschlagHorizontalHinten.h"
#include "stdbool.h"
#include "mulde.h"
//Zeit um Reset Wert
int timeVertical;
int timeHorizontal;

/*
 * Initialisiert die Servos
 */

/*
 * Greift nach dem Objekt, Servos sollte sich schliessen
 */
void grab() {
	Greifen_SetRatio16(Duty2ms);
	Status.Timer0 == TIMER_USED;
}
/*
 * Öffnet den Greifer Arm
 */
void openGreifer() {
	Greifen_SetRatio16(Duty1ms);
	Status.Timer0 == TIMER_USED;
}

/*
 * Nachdem der Greifer hochgefahren ist, sollte er den
 * Greifer sammt Tonne drehen und ausleeren
 */
void turnGrabber(void) {
	smooth();
	WAIT1_Waitms(100);
	Greifen_SetRatio16(Duty2ms);
	Drehen_SetRatio16(Duty360Deg2);
}

/*
 * Dreht den Greiferarm wieder zurück
 */
void turnBackGrabber(void) {
	Greifen_SetRatio16(Duty2ms);
	Drehen_SetRatio16(Duty360Deg1);
	WAIT1_Waitms(1000);
	smoothBack();
	//WAIT1_Waitms(1000);
	//shakeShake();
}

/*
 * Servo hat den Greifer zugepackt,
 * hät ihn gerade und fährt nun nach oben.
 */
void up() {
		up_bit();
		DC_Greifer_Schiene_Vertikal_SetRatio16(100);
		WAIT1_Waitms(100);
		DC_Greifer_Schiene_Vertikal_SetRatio16(0xFFFF);

}

/*
 * Fahrzeug ist an der Richtigen Stelle und fährt
 * den Greifer nun herunter
 */
void down() {
	down_bit();
	DC_Greifer_Schiene_Vertikal_SetRatio16(100);
	WAIT1_Waitms(100);
	DC_Greifer_Schiene_Vertikal_SetRatio16(0xFFFF);
}

/*
 * Bringt den ganzen Greifer nach vorne
 */
void forward() {
		forward_bit();
		DC_Greifer_Schiene_Horizontal_SetRatio16(30000);
		WAIT1_Waitms(100);
		DC_Greifer_Schiene_Horizontal_SetRatio16(0xFFFF);
}
/*
 * Bring den Greifer nach hinten.
 */
void backward() {
		backward_bit();
		DC_Greifer_Schiene_Horizontal_SetRatio16(30000);
		WAIT1_Waitms(100);
		DC_Greifer_Schiene_Horizontal_SetRatio16(0xFFFF);
}
/*
 * Setzt das Bit um Hochzufahren
 */
void up_bit() {
	DCVertikalBit_PutVal(1);
}
/*
 * Setzt das Bit so um wieder runterzufahren
 */
void down_bit() {
	DCVertikalBit_PutVal(0);
}
/*
 * Setzt das Bit um nach vorne zu fahren
 */
void forward_bit() {
	DCHorizontalBit_PutVal(1);
}
/*
 * Setzt das Bit um nach hinten zu fahren
 */
void backward_bit() {
	DCHorizontalBit_PutVal(0);
}
/*
 * Setzt den greifer an der Schiene hoch/runter usw.
 */
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

/*
 * Setzt den Greifer zuerst ganz hoch mit dem leeren Eimer,
 * danach geht er ganz nach vorne
 * dann setzt er ihn mit dem Paramtere ganz ab.
 * Dann wird der Greifer geöffnet und der Eimer wird abgesetzt.
 *
 */
void setGrabberBack() {
	int dummy = 0;
	upToEnd();
	WAIT1_Waitms(2000);
	backToEnd();
	WAIT1_Waitms(2000);
	turnBackGrabber();
	WAIT1_Waitms(2000);
	turnGrabber();
	WAIT1_Waitms(500);
}

void setModeBitDc(void) {
	ModeDC_PutVal(TRUE);
}

void backToEnd(void) {
	int loop = 1;
	backward_bit();
	DC_Greifer_Schiene_Horizontal_SetRatio16(30000);
	while (loop) {
		WAIT1_Wait10Cycles();
		if (!AnschlagHorizontalVorne_GetRawVal()) {
			loop = 0;
			DC_Greifer_Schiene_Horizontal_SetRatio16(0xFFFF);
		}
	}
	DC_Greifer_Schiene_Horizontal_SetRatio16(0);
}

void upToEnd(void) {
	int loop = 1;
	//test
	DCVertikalBit_PutVal(0);
	//up_bit();
	DC_Greifer_Schiene_Vertikal_SetRatio16(1000);
	while (loop) {
		//DCVertikalBit_PutVal(0);
		WAIT1_Wait10Cycles();
		if (!AnschlagHorizontalHinten_GetRawVal()) {
			loop = 0;
		}

	}
	DC_Greifer_Schiene_Vertikal_SetRatio16(0xFFFF);
	//Test
	//DCVertikalBit_PutVal(0);
}

void frontToEnd(void) {
	int loop = 1;
	forward_bit();
	DC_Greifer_Schiene_Horizontal_SetRatio16(30000);
	while (loop) {
		WAIT1_Wait10Cycles();
		if (!AnschlagVertikalOben_GetRawVal()) {
			loop = 0;
		}
	}
	DC_Greifer_Schiene_Horizontal_SetRatio16(0);
}


void shakeShake(){
	Drehen_SetRatio16(Duty360Deg1);
	WAIT1_Waitms(500);
	Drehen_SetRatio16(61000);
	WAIT1_Waitms(500);
	Drehen_SetRatio16(Duty360Deg1);
}
