/*
 * engine.c
 *
 *  Created on: 01.03.2016
 *      Author: danie
 */
#include "engine.h"

#define VelocityEngines 1000

extern int counterLeft;
extern int counterRight;

typedef enum {
  EngineDriving,
  EnigneIdle,
  EngineCorrecting,
  EngineBreaking,
  EngineSlowDown
} EngineState;

//volatile = Kann verändert werden!
volatile EngineState EngineLeft;
volatile EngineState EngineRight;


/**
 * Initialisiert den Motor mit 0.1Mhz und den Duty Cycle mit 50 %
 * ausserdem wurde das BIT noch gesetzt PTE2 auf 1
 */

void initEngines(void){
	LEDBlue_On();
	LEDGreen_Off();

	MotorBit_SetVal();//PTE2

	//Setzt Periode 1/(10*10^-6)
	motor_links_SetDutyUS(10);//PTE22
	motor_rechts_SetDutyUS(10);//PTB3

	//setzt Duty Cycle
	motor_links_SetRatio16(50);
	motor_rechts_SetRatio16(50);

	EngineLeft,EngineRight = EngineDriving;
}

/*
 * Breite von 1
 */
void setVelocityleft(int v){
	motor_links_SetDutyUS(v);//PTE22
	EngineLeft = EngineCorrecting;
}

void setVelocityright(int v){
	motor_rechts_SetDutyUS(v);//PTB3
	EngineRight = EngineCorrecting;
}

void setSpeed(int VeloCityFromPi){
	setVelocityright(VeloCityFromPi);
	setVelocityleft(VeloCityFromPi);
}

/*
 * Korrigiert die geschwindigkeit damit der Winkel wieder Null wird!
 */
void calcVelocityToNumber(int angleFromPi){
	if(angleFromPi == 0){
		return;
	}
	if(angleFromPi>=0){
		//Aufwendige Rechnung
		setVelocityleft(VelocityEngines+10);
	}
	else{
		//Aufwendige Rechnung
		setVelocityright(VelocityEngines+10);
	}
}



/*
 * Gibt den Counter Wert des Rechten Rades zurück
 */
int getValueRight(){
	return counterRight;
}
/*
 * Gibt den Counter Wert des Linken Rades zurück
 */
int getValueLeft(){
	return counterLeft;
}


void EnginesBreak(void){
	EngineLeft,EngineRight = EngineBreaking;
}

void EnginesSlowDown(void){
	int i = VelocityEngines;
	EngineLeft,EngineRight = EngineSlowDown;
	while(i != 0){
		i--;
		setVelocityright(i);
		setVelocityleft(i);
	}

}
