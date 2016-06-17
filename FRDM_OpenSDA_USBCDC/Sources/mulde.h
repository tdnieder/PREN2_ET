/*
 * mulde.h
 *
 *  Created on: 01.03.2016
 *      Author: danie
 */

#ifndef SOURCES_MULDE_H_
#define SOURCES_MULDE_H_

#include "Mulde_leeren.h"
#include "interface.h"

extern int Duty1ms;
extern int Duty2ms;

void initMulde(void);

void turnempty(void);

void turnbackThrough(void);

void unloadThrough(void);

void smooth(void);

void smoothBack(void);

void stopMulde(void);
#endif /* SOURCES_MULDE_H_ */
