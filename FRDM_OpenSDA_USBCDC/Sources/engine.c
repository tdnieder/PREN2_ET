/*
 * engine.c
 *
 *  Created on: 01.03.2016
 *      Author: danie
 */

#include "engine.h"

const float radiusRad = 3.5;//cm
const float stepperAngle = 0.9;//Grad
const float PII = 3.14;

extern long counterLeft;
extern long counterRight;

volatile int timerValue0;
volatile int timerValue1;

//wird gebraucht um den Timer in den Ursprung zur�ck zu versetzten!
volatile int ModuloValueTimer0;
volatile int ModuloValueTimer1;

typedef enum {
	EngineDriving, EnigneIdle, EngineCorrecting, EngineBreaking, EngineSlowDown
} EngineState;

//volatile = Kann ver�ndert werden!
volatile EngineState EngineLeft;
volatile EngineState EngineRight;

/**
 *Initialisiert Motoren mit den Richtigen Bits
 *Speichert die alten Modulowerte ab, f�r andere Files die 20 ms als Periodendauer brauchen -> Servos
 */
void initEngines(void) {
// Makros erstellen
	//Bit Setzten f�r Treiber
	MS1_PutVal(MSBIT1); //PTE2
	MS2_PutVal(MSBIT2);
	MS3_PutVal(MSBIT3);
	Sleep_PutVal(SLEEP);
	Enable_PutVal(ENABLE);

	DIRLeft_PutVal(DIRLEFT); //Damit vorw�rts f�hrt
	DIRright_PutVal(DIRRIGHT);

	LEDBlue_On();

// Modulo Wert bei beginn 59999 bei T = 20 ms!!
// Speichert Modulo Werte ab f�r Servos sp�ter!
	ModuloValueTimer0 = TPM0_MOD;
	ModuloValueTimer1 = TPM1_MOD;

	//Richtet Modulo f�r Motoren ein.
	//setTimerFrequencyRight(ModuloValueMotor);
	//setTimerFrequencyLeft(ModuloValueMotor);


	setTimerFrequencyRight(ModuloValueMotor);
	setTimerFrequencyLeft(ModuloValueMotor);
	//Motoren beginnen drehen
	motor_rechts_Enable();
	motor_links_Enable();


	//startet mit Rampe
	//ramp();

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
	LEDRed_Off();
	LEDGreen_Off();
	LEDBlue_Off();

	if (angleFromPi == 0) {
		return;
	}
	else if (angleFromPi == 1) {
		TPM1_MOD += 1000;
		TPM0_MOD =  ModuloValueMotor;
		LEDRed_On();LEDGreen_On();
		//CDC1_SendString((char*)"r;");
	}
	else if (angleFromPi == 2) {
		//Motor rechts langsamer
		TPM0_MOD += 1000;
		TPM1_MOD =  ModuloValueMotor;
		LEDGreen_On();
		//CDC1_SendString((char*)"g;");
	}
	else if (angleFromPi == 3) {
		//Motor links schneller
		TPM1_MOD -= 500;
		TPM0_MOD =  ModuloValueMotor;
		LEDBlue_On();
		//CDC1_SendString((char*)"b;");
	}
	else if (angleFromPi == 4) {
		//Motor links langsamer
		TPM0_MOD -= 500;
		TPM1_MOD =  ModuloValueMotor;
		LEDBlue_On();LEDRed_On();
		//CDC1_SendString((char*)"v;");
	}
}

/*
 * Gibt den Counter Wert des Rechten Rades zur�ck
 */
int getValueRight() {
	return counterRight;
}
/*
 * Gibt den Counter Wert des Linken Rades zur�ck
 */
int getValueLeft() {
	return counterLeft;
}
//Braucht es nicht
void EnginesBreak() {
	EngineLeft, EngineRight = EngineBreaking;
	motor_links_Disable();
	motor_rechts_Disable();
}

//Braucht es nicht
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
 *H�herer Modulo = Tiefe Frequenz!
 *Tieferer Modulo = H�here Frequenz!
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
	steps -= 600;
	}
}

//Kann jemals so gross werden das int nicht mehr reicht?
int calcDistance(){
	int mean = (counterLeft + counterRight)/2;
	int distance = 0;
	//Weil wir im HalfStep Modus sind kann mit if's gel�st werden wenn MSB Bits automatisch ge�ndert werden sollen
	mean = (mean/2);
	distance = (int)(mean * (stepperAngle*(PII/180)) * radiusRad);
	return distance;
}
