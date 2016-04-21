/*
 * greifer.c
 *
 *  Created on: 01.03.2016
 *      Author: danie
 */

#include "greifer.h"

typedef enum {
	DCRunning, DCBraking, DCWaiting,
} DCState;

typedef enum {
	ServoOpening, ServoClosing, ServoWaiting,
} ServoState;

//Zeit um Reset Wert
int timeVertical;
int timeHorizontal;
int timeToTurn = 0;

//Servo Status
volatile ServoState ServoGrab;
volatile ServoState ServoTurn;

//DC Motor Status
volatile DCState DcHorizontal;
volatile DCState DcVertikal;

/*
 * Initialisiert die Servos
 */
void initAllServos() {
	ServoGrab, ServoTurn = ServoWaiting;
	Greifen_Disable();
	Drehen_Disable();
	ModeDC_PutVal(TRUE);
	DC_Greifer_Schiene_Horizontal_Disable();
	DC_Greifer_Schiene_Vertikal_Disable();
}

/*
 * Greift nach dem Objekt, Servos sollte sich schliessen
 */
void grab() {
	ServoGrab = ServoClosing;
	Greifen_Enable();
	Greifen_SetRatio16(Duty2ms);
}

/*
 * Öffnet den Greifer Arm
 */
void openGreifer() {
	ServoGrab = ServoOpening;
	Greifen_Enable();
	Greifen_SetRatio16(Duty1ms);
}

/*
 * Nachdem der Greifer hochgefahren ist, sollte er den
 * Greifer sammt Tonne drehen und ausleeren
 */
void turnGrabber(int DutyC) {
	ServoTurn = ServoOpening;
	Drehen_Enable();
	Drehen_SetRatio16(DutyC);
	//Vll ein Wait
}

/*
 * Dreht den Greiferarm wieder zurück
 */
void turnBackGrabber(int DutyC) {
	ServoTurn = ServoClosing;
	Drehen_Enable();
	Drehen_SetRatio16(DutyC);
	//Vll ein Waitq
}


/*
 * Servo hat den Greifer zugepackt,
 * hät ihn gerade und fährt nun nach oben.
 */
void up() {
	up_bit();
	DC_Greifer_Schiene_Horizontal_SetRatio16(20000);
	DC_Greifer_Schiene_Vertikal_Enable();
	WAIT1_Waitms(100);
	DC_Greifer_Schiene_Vertikal_Disable();
	timeVertical += 10;
}

/*
 * Fahrzeug ist an der Richtigen Stelle und fährt
 * den Greifer nun herunter
 */
void down() {
	down_bit();
	DC_Greifer_Schiene_Vertikal_Enable();
	WAIT1_Waitms(100);
	DC_Greifer_Schiene_Vertikal_Disable();
	timeVertical -= 10;
}

/*
 * Bringt den ganzen Greifer nach vorne
 */
void forward() {
	forward_bit();
	DC_Greifer_Schiene_Horizontal_Enable();
	WAIT1_Waitms(100);
	DC_Greifer_Schiene_Horizontal_Disable();
	timeHorizontal += 10;
}
/*
 * Bring den Greifer nach hinten.
 */
void backward() {
	backward_bit();
	DC_Greifer_Schiene_Horizontal_Enable();
	WAIT1_Waitms(100);
	DC_Greifer_Schiene_Horizontal_Disable();
	timeHorizontal -=10;
}


/*
 * Setzt das Bit um Hochzufahren
 */
void up_bit(){
	DCVertikalBit_SetVal();
}
/*
 * Setzt das Bit so um wieder runterzufahren
 */
void down_bit(){
	DCVertikalBit_ClrVal();
}
/*
 * Setzt das Bit um nach vorne zu fahren
 */
void forward_bit(){
	DCHorizontalBit_SetVal();
}
/*
 * Setzt das Bit um nach hinten zu fahren
 */
void backward_bit(){
	DCHorizontalBit_ClrVal();
}

void setGrabber(int Hor, int Vert){

	if(Hor == 1){
		forward();//Richtung container
	}
	else if(Hor == 2){
		backward();
	}
	if(Vert == 1){
		up();
	}
	else if(Vert == 2){
		down();
	}
}

void setGrabberBack(){
	int vert = timeVertical/10;
	int hor = timeHorizontal/10;
	int counter = 0;

	if(vert >= 0){
		for(counter;counter > vert; counter ++){
			down();
		}
	}
	else{
		for(counter;counter > vert; counter ++){
			up();
		}
	}

	counter = 0;

	if(hor >= 0){
		for(counter;counter > vert; counter ++){
			backward();
		}
	}
	else{
		for(counter;counter > vert; counter ++){
			forward();
		}
	}
}





