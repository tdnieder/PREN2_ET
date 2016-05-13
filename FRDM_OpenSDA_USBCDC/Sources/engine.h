/*
 * engine.h
 *
 *  Created on: 01.03.2016
 *      Author: danie
 */
#include "Cpu.h"
#include "Events.h"
#include "LEDRed.h"
#include "LEDpin1.h"
#include "BitIoLdd1.h"
#include "LEDGreen.h"
#include "LEDpin2.h"
#include "BitIoLdd2.h"
#include "LEDBlue.h"
#include "LEDpin3.h"
#include "BitIoLdd3.h"
#include "WAIT1.h"
#include "USB1.h"
#include "USB0.h"
#include "CDC1.h"
#include "Tx1.h"
#include "Rx1.h"
#include "motor_links.h"
#include "PwmLdd1.h"
#include "TU1.h"
#include "motor_rechts.h"
#include "PwmLdd2.h"
#include "MS1.h"
#include "BitIoLdd4.h"
#include "TU1.h"
#include "TU2.h"
#include "interface.h"


#ifndef SOURCES_ENGINE_H_
#define SOURCES_ENGINE_H_

//Grundwert der Motoren
#define ModuloValueMotor 5000
#define MSBIT1 0
#define MSBIT2 1
#define MSBIT3 0
#define SLEEP 1
#define ENABLE 0
#define DIRLEFT 0
#define DIRRIGHT 1



/*
 * Initialisiert Bits für die Motoren
 * führt eine Rampe aus
 */
void initEngines(void);
/*
 * Steuert die Linken und Rechten Motoren je nach bedarf
 * des Pis über die Schnittstelle
 * "Regelung"
 */
void calcVelocityToNumber(int,int);
/*
 * Zählt die Distanz die zurückgelegt wird Links
 */
int calcStepsLeft(void);
/*
 * Zählt die Distanz die zurückgelegt wird Links
 */
int calcStepsRight(void);
/*
 * Wird gebraucht um die Ticks irgendwohin zu bringen
 */
int getValueRight(void);
/*
 * Wird gebraucht um die Ticks irgendwohin zu bringen
 */
int getValueLeft(void);
/*
 * Sofort anhalten
 */
void EnginesBreak(void);
/*
 * Langsam abbremsen
 */
void EnginesSlowDown(void);
/*
 * Frequenz Rechts ändern
 */
void setTimerFrequencyRight(int);
/*
 * Frequenz Links ändern
 */
void setTimerFrequencyLeft(int);
/*
 * Setzt die Geschwindigkeit bei beiden Motoren
 */
void setSpeed(int);
/*
 * Fährt eine Rampe hoch
 */
void ramp();
/*
 * Sollte die Strecke Ausmessen, welche bereits zurückgelegt wurde.
 */
int calcDistance();

void countLeftStep();

void countRightStep();
#endif /* SOURCES_ENGINE_H_ */
