/*
 * engine.c
 *
 *  Created on: 01.03.2016
 *      Author: danie
 */
#include "engine.h"
#include "TU1.h"

//#define VelocityEngines 1800

extern int counterLeft;
extern int counterRight;

volatile int CValueNowLeft;
volatile int CValueNowRight;

typedef enum {
	EngineDriving, EnigneIdle, EngineCorrecting, EngineBreaking, EngineSlowDown
} EngineState;

//volatile = Kann verändert werden!
volatile EngineState EngineLeft;
volatile EngineState EngineRight;

/**
 *
 */

void initEngines(void) {
	LEDBlue_On();
	LEDGreen_Off();

	CValueNowLeft = TPM2_C0V;
	CValueNowRight = TPM2_C1V;

	motor_rechts_Enable();
	motor_links_Enable();

//setVelocityleft(VelocityEngines);//PTE22
//setVelocityright(VelocityEngines);//PTB3

	MotorBit_SetVal(); //PTE2

	//setzt Duty Cycle
	motor_links_SetRatio16(50); //PTE22
	motor_rechts_SetRatio16(50);

	EngineLeft, EngineRight = EngineDriving;
}

/*
 * Breite von 1
 *
 */
void setVelocityleft(int v) {
	TPM2_C0V = v;
	EngineLeft = EngineCorrecting;
}

void setVelocityright(int v) {
	TPM2_C1V = v;
	EngineRight = EngineCorrecting;
}

void setSpeed(int VeloCityFromPi) {
	setVelocityright(VeloCityFromPi);
	setVelocityleft(VeloCityFromPi);
}

/*
 * Korrigiert die geschwindigkeit damit der Winkel wieder Null wird!
 */
void calcVelocityToNumber(int angleFromPi) {
	if (angleFromPi == 0) {
		return;
	}
	if (angleFromPi >= 0) {
		//Aufwendige Rechnung
		setVelocityleft(CValueNowLeft + 10);
	} else {
		//Aufwendige Rechnung
		setVelocityright(CValueNowRight + 10);
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

void EnginesBreak(void) {
	EngineLeft, EngineRight = EngineBreaking;
}


/*
 * int CValueNowLeft;
int CValueNowRight;
 */
void EnginesSlowDown(void) {

	int i = CValueNowLeft;

	EngineLeft, EngineRight = EngineSlowDown;
	while (i != 0) {
		setVelocityright(i);
		setVelocityleft(i);
		i--;
	}

}
//Setzt frequenzen im Rechten Timer
/*
 * Timer 1.5MHZ
 * 1 Clock = 0.0000006666666667 s
 * Value ist bei 1800 Scheinbar !!!!
 *
 *
 *
 *Nebengedanke,
 *Höherer Value = Tiefe Frequenz!
 *Tieferer Value = Höhere Frequenz!
 */
void setTimerFrequencyRight(int value) {
	TPM2_C1V = value;
}

void setTimerFrequencyLeft(int value) {
	TPM2_C0V = value;
}
