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

extern int Duty1ms;
extern int Duty2ms;

/*
 * Initialisiert die Servos
 */
void initAllServos();

/*
 * Greift nach dem Objekt, Servos sollte sich schliessen
 */
void grab(void);

/*
 * Nachdem der Greifer hochgefahren ist, sollte er den
 * Greifer sammt Tonne drehen und ausleeren
 */
void turnGrabber(int);

/*
 * Dreht den greiferArm wieder zur�ck
 */
void turnBackGrabber(int);

/*
 * Servo hat den Greifer zugepackt,
 * h�t ihn gerade und f�hrt nun nach oben.
 */
void up(void);

/*
 * Fahrzeug ist an der Richtigen Stelle und f�hrt
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
 * �ffnet den Greifer Arm
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
 *Setzt den Greifer zur�ck
 */
void setGrabberBack(void);



#endif /* SOURCES_GREIFER_H_ */
