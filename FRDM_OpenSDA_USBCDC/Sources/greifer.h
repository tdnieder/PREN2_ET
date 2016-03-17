/*
 * greifer.h
 *
 *  Created on: 01.03.2016
 *      Author: danie
 */

#ifndef SOURCES_GREIFER_H_
#define SOURCES_GREIFER_H_

/*
 * Initialisiert die Servos
 */
void initAllServos(void);

/*
 * Greift nach dem Objekt, Servos sollte sich schliessen
 */
void grab(void);

/*
 * Nachdem der Greifer hochgefahren ist, sollte er den
 * Greifer sammt Tonne drehen und ausleeren
 */
void turn(void);

/*
 * Dreht den greiferArm wieder zur�ck
 */
void turnBack(void);

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
#endif /* SOURCES_GREIFER_H_ */
