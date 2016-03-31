/*
 * engine.c
 *
 *  Created on: 01.03.2016
 *      Author: danie
 */

#include "engine.h"

const int radiusRad = 10;//cm
const int stepperAngle = 7;//Grad
const int PII = 3;

extern long counterLeft;
extern long counterRight;

volatile int timerValue0;
volatile int timerValue1;

//wird gebraucht um den Timer in den Ursprung zurück zu versetzten!
volatile int ModuloValueTimer0;
volatile int ModuloValueTimer1;

typedef enum {
	EngineDriving, EnigneIdle, EngineCorrecting, EngineBreaking, EngineSlowDown
} EngineState;

//volatile = Kann verändert werden!
volatile EngineState EngineLeft;
volatile EngineState EngineRight;

/**
 *Initialisiert Motoren mit den Richtigen Bits
 *Speichert die alten Modulowerte ab, für andere Files die 20 ms als Periodendauer brauchen -> Servos
 */
void initEngines(void) {
// Makros erstellen
	//Bit Setzten für Treiber
	MS1_PutVal(MSBIT1); //PTE2
	MS2_PutVal(MSBIT2);
	MS3_PutVal(MSBIT3);
	Sleep_PutVal(SLEEP);
	Enable_PutVal(ENABLE);

	DIRLeft_PutVal(DIRLEFT); //Damit vorwärts fährt
	DIRright_PutVal(DIRRIGHT);

	LEDBlue_On();
	LEDGreen_Off();

// Modulo Wert bei beginn 59999 bei T = 20 ms!!
// Speichert Modulo Werte ab für Servos später!
	ModuloValueTimer0 = TPM0_MOD;
	ModuloValueTimer1 = TPM1_MOD;

	//Richtet Modulo für Motoren ein.
	//setTimerFrequencyRight(ModuloValueMotor);
	//setTimerFrequencyLeft(ModuloValueMotor);

	//Motoren beginnen drehen
	motor_rechts_Enable();
	motor_links_Enable();

	//startet mit Rampe
	ramp();

	EngineLeft, EngineRight = EngineDriving;
}

/*
 * Um beide Gleichzeitig einzustellen
 */
void setSpeed(int VeloCityFromPi) {
	setTimerFrequencyLeft(VeloCityFromPi);
	setTimerFrequencyRight(VeloCityFromPi);
}

/*
 * Korrigiert die geschwindigkeit damit der Winkel wieder Null wird!
 */
void calcVelocityToNumber(int angleFromPi) {
	if (angleFromPi == 0) {
		return;
	}
	if (angleFromPi == 1) {
		//Motor links langsamer
		TPM1_MOD += 500;
	}
	if (angleFromPi == 2) {
		//Motor rechts langsamer
		TPM0_MOD += 500;
	}
	if (angleFromPi == 3) {
		//Motor links schneller
		TPM1_MOD -= 500;
	}
	if (angleFromPi == 4) {
		//Motor links schneller
		TPM0_MOD -= 500;
	}
}

/*
 * Gibt den Counter Wert des Rechten Rades zurück
 */
int getValueRight() {
	return counterRight;
}
/*
 * Gibt den Counter Wert des Linken Rades zurück
 */
int getValueLeft() {
	return counterLeft;
}

void EnginesBreak() {
	EngineLeft, EngineRight = EngineBreaking;
	motor_links_Disable();
	motor_rechts_Disable();
}


void EnginesSlowDown() {
	int j = (TPM1_MOD + TPM0_MOD)/2;
	EngineLeft, EngineRight = EngineSlowDown;
	while (j != 0) {
		setTimerFrequencyRight(j);
		setTimerFrequencyLeft(j);
		j -= 400;
	}
	motor_rechts_Disable();
	motor_links_Disable();
}
//Setzt frequenzen im Rechten Timer
/*
 * Timer 1.5MHZ
 * 1 Clock = 0.0000006666666667 s
 * Value ist bei 1800 Scheinbar !!!!
 *
 * 900 ist er!
 *
 *Nebengedanke,
 *Höherer Modulo = Tiefe Frequenz!
 *Tieferer Modulo = Höhere Frequenz!
 */
//5000 ist ein guter Wert
void setTimerFrequencyRight(int value) {
	TPM0_MOD = value;
}

void setTimerFrequencyLeft(int value) {
	TPM1_MOD = value;
}

void ramp(){
	int steps = 10000;
	while(steps != ModuloValueMotor){
	setTimerFrequencyRight(steps);
	setTimerFrequencyLeft(steps);
	steps -= 200;
	}
}



//Kann jemals so gross werden das int nicht mehr reicht?
int calcDistance(){
	int mean = (counterLeft + counterRight)/2;
	int distance = 0;
	//Weil wir im HalfStep Modus sind kann mit if's gelöst werden wenn MSB Bits automatisch geändert werden sollen
	mean = (mean/2);

	distance = mean * (int)(stepperAngle*(PII/180)) * radiusRad;
	return distance;
}
