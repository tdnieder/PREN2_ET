/*
 * engine.c
 *
 *  Created on: 01.03.2016
 *      Author: danie
 */

#include "engine.h"

const float radiusRad = (7.7) / 2; //cm
const float stepperAngle = 1.8; //Grad
const float PII = 3.14;
int distance;

int counterLeft;
int counterRight;

int counterOverflowLeft;
int counterOverflowRight;

volatile int timerValue0;
volatile int timerValue1;

//wird gebraucht um den Timer in den Ursprung zurück zu versetzten!
volatile int ModuloValueTimer0;
volatile int ModuloValueTimer1;

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
	setEngineSteps(8);
	Sleep_PutVal(SLEEP);


	DIRLeft_PutVal(DIRLEFT);
	DIRright_PutVal(DIRRIGHT);

	//Aktiviert Events
	motor_rechts_EnableEvent();
	motor_links_EnableEvent();

// Modulo Wert bei beginn 59999 bei T = 20 ms!!
// Speichert Modulo Werte ab für Servos später!
	ModuloValueTimer0 = TPM0_MOD;
	ModuloValueTimer1 = TPM1_MOD;

	setTimerFrequencyRight(ModuloValueMotor);
	setTimerFrequencyLeft(ModuloValueMotor);

	Enable_PutVal(ENABLE);

	motor_rechts_SetRatio16(30000);
	motor_links_SetRatio16(30000);

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
void calcVelocityToNumber(int angleFromPi, int velocityFromPi) {
	LEDRed_Off();
	LEDGreen_Off();
	LEDBlue_Off();

	if (angleFromPi == 0) {
		return;
	} else if (angleFromPi == 1) {
		//Motor links langsam
		TPM1_MOD += velocityFromPi;
		LEDRed_On();
		LEDGreen_On();
	} else if (angleFromPi == 2) {
		//Motor rechts langsamer
		TPM0_MOD += velocityFromPi;
		LEDGreen_On();
	} else if (angleFromPi == 3) {
		//Motor links schneller
		TPM1_MOD -= velocityFromPi;
		LEDBlue_On();
	} else if (angleFromPi == 4) {
		//Motor rechts schnell
		TPM0_MOD -= velocityFromPi;
		LEDBlue_On();
		LEDRed_On();
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
	TPM1_MOD = value;
}

void setTimerFrequencyLeft(int value) {
	TPM0_MOD = value;
}
/*
 * Distanz in mm
 */
int calcDistance() {
	int mean = (counterLeft + counterRight) / 2;
	//Weil wir im HalfStep Modus sind kann mit if's gelöst werden wenn MSB Bits automatisch geändert werden sollen
	mean = (mean / 8);
	distance = (int)((mean * (stepperAngle * (PII / 180)) * radiusRad)*10);	//distance;
	return distance;
}

void countLeftStep() {
	counterLeft++;
}

void countRightStep() {
	counterRight++;
}

void setEngineSteps(int steps){
	if(steps == 1){
		MS1_PutVal(0);
		MS2_PutVal(0);
		MS3_PutVal(0);
	}
	else if(steps == 2){
		MS1_PutVal(1);
		MS2_PutVal(0);
		MS3_PutVal(0);
	}
	else if(steps == 4){
		MS1_PutVal(0);
		MS2_PutVal(1);
		MS3_PutVal(0);
	}
	else if(steps == 8){
		MS1_PutVal(1);
		MS2_PutVal(1);
		MS3_PutVal(0);
	}
	else if(steps == 16){
		MS1_PutVal(1);
		MS2_PutVal(1);
		MS3_PutVal(1);
	}
}
