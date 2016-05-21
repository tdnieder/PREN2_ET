/*
 * greifer.h
 *
 *  Created on: 01.03.2016
 *      Author: danie
 */

#ifndef SOURCES_GREIFER_H_
#define SOURCES_GREIFER_H_

#include "DC_Greifer_Schiene_Horizontal.h"//PTE23
#include "DC_Greifer_Schiene_Vertikal.h"
#include "ModeDC.h"
#include "Greifen.h"
#include "Drehen.h"
#include "DCVertikalBit.h"
#include "DCHorizontalBit.h"//PTE0
#include "interface.h"
#include "AnschlagHorizontalVorne.h"
#include "AnschlagVertikalOben.h"
#include "AnschlagHorizontalHinten.h"

extern int Duty1ms;
extern int Duty2ms;
extern int Duty360Deg1;
extern int Duty360Deg2;





/*
 * Greift nach dem Objekt, Servos sollte sich schliessen
 */
void grab(void);

/*
 * Nachdem der Greifer hochgefahren ist, sollte er den
 * Greifer sammt Tonne drehen und ausleeren
 */
void turnGrabber(void);

/*
 * Dreht den greiferArm wieder zurück
 */
void turnBackGrabber(void);

/*
 * Servo hat den Greifer zugepackt,
 * hät ihn gerade und fährt nun nach oben.
 */
void up(void);

/*
 * Fahrzeug ist an der Richtigen Stelle und fährt
 * den Greifer nun herunter
 */
void down(void);

/*
 * Bringt den ganzen Greifer nach vorne
 */
void forward(void);
/*
 * Bring den Greifer nach hinten.
 */
void backward(void);
/*
 * Öffnet den Greifer Arm
 */
void openGreifer(void);
/*
 * Setzt das Bit um Hochzufahren
 */
void up_bit(void);
/*
 * Setzt das Bit so um wieder runterzufahren
 */
void down_bit(void);
/*
 * Setzt das Bit um nach vorne zu fahren
 */
void forward_bit(void);
/*
 * Setzt das Bit um nach hinten zu fahren
 */
void backward_bit(void);
/*
 * Greifer steuerung
 */
void setGrabber(int, int);
/*
 *Setzt den Greifer zurück
 */
void setGrabberBack(void);
/*
 * Setzt DC Mode Bit
 */
void setModeBitDc();

/*
 * Greifer geht bis zum Anschlagschalter hinten.
 */
void backToEnd(void);
/*
 * Greifer geht bis zum Anschlagschalter oben.
 */
void upToEnd(void);
/*
 * Greifer geht bis zum Anschlagschalter vorne.
 */
void frontToEnd(void);
#endif /* SOURCES_GREIFER_H_ */
