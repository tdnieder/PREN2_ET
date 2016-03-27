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

#ifndef SOURCES_ENGINE_H_
#define SOURCES_ENGINE_H_

void initEngines(void);

void setVelocityleft(int);

void setVelocityright(int);

void calcVelocityToNumber(int);

int calcStepsLeft(void);

int calcStepsRight(void);

int getValueRight(void);

int getValueLeft(void);

void EnginesBreak(void);

void EnginesSlowDown(void);

void setTimerFrequencyRight(int);

void setTimerFrequencyLeft(int);

void setSpeed(int);
#endif /* SOURCES_ENGINE_H_ */
