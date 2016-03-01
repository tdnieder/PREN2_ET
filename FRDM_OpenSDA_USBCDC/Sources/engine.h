/*
 * engine.h
 *
 *  Created on: 01.03.2016
 *      Author: danie
 */

#ifndef SOURCES_ENGINE_H_
#define SOURCES_ENGINE_H_

void initEngines(void);

void setVelocityleft(int);

void setVelocityright(int);

void calcVelocityToNumber(int);

void calcVelocityToNumber(int,int);

int calcStepsLeft(void);

int calcStepsRight(void);

int getValueRight(void);

int getValueLeft(void);
#endif /* SOURCES_ENGINE_H_ */
