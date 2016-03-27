/*
 * greifer.c
 *
 *  Created on: 01.03.2016
 *      Author: danie
 */
typedef enum {
	DCRunning, DCBraking, DCWaiting,
} DCState;

typedef enum {
	ServoOpening, ServoClosing, ServoWaiting,
} ServoState;

volatile ServoState ServoGrab;
volatile ServoState ServoTurn;

volatile DCState DcHorizontal;
volatile DCState DcVertikal;


//DC
/*
 * Initialisiert die Servos
 */
void initAllServos(void) {
	ServoGrab, ServoTurn = ServoWaiting;
	Greifen_Disable();
	Drehen_Disable();
	DC_Greifer_Schiene_Horizontal_Disable();
	DC_Greifer_Schiene_Vertikal_Disable();
}

/*
 * Greift nach dem Objekt, Servos sollte sich schliessen
 */
void grab(void) {
	ServoGrab = ServoClosing;
	Greifen_Enable();
	Greifen_SetRatio16(100);
}

/*
 * Öffnet den Greifer Arm
 */
void openGreifer(void) {
	ServoGrab = ServoOpening;
	Greifen_Enable();
	Greifen_SetRatio16(0);
}

/*
 * Nachdem der Greifer hochgefahren ist, sollte er den
 * Greifer sammt Tonne drehen und ausleeren
 */
void turn(void) {
	ServoTurn = ServoOpening;
	Drehen_Enable();
	Drehen_SetRatio16(100);
}

/*
 * Dreht den Greiferarm wieder zurück
 */
void turnBack(void) {
	ServoTurn = ServoClosing;
	Drehen_Enable();
	Drehen_SetRatio16(0);
}

/*
 * Servo hat den Greifer zugepackt,
 * hät ihn gerade und fährt nun nach oben.
 */
void up(void) {
	DCVertikalBit_ClrVal();
	DC_Greifer_Schiene_Vertikal_Enable();
	WAIT1_Waitms(10);
	DC_Greifer_Schiene_Vertikal_Disable();
}

/*
 * Fahrzeug ist an der Richtigen Stelle und fährt
 * den Greifer nun herunter
 */
void down(void) {
	DCVertikalBit_SetVal(); //Setzt DC Motor Treiber auf 1 damit er wieder runterfährt
	DC_Greifer_Schiene_Vertikal_Enable();
	WAIT1_Waitms(10);
	DC_Greifer_Schiene_Vertikal_Disable();
}

/*
 * Bringt den ganzen Greifer nach vorne
 */
void forward(void) {
	DCHorizontalBit_ClrVal();
	DC_Greifer_Schiene_Horizontal_Enable();
	WAIT1_Waitms(10);
	DC_Greifer_Schiene_Horizontal_Disable();
}
/*
 * Bring den Greifer nach hinten.
 */
void backward(void) {
	DCHorizontalBit_SetVal();
	DC_Greifer_Schiene_Horizontal_Enable();
	WAIT1_Waitms(10);
	DC_Greifer_Schiene_Horizontal_Disable();
}
