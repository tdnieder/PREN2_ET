/*
 * ultrasonic.h
 *
 *  Created on: 03.03.2016
 *      Author: danie
 */
#include "Events.h"
#include "TU2.h"
#ifndef SOURCES_ULTRASONIC_H_
#define SOURCES_ULTRASONIC_H_

typedef enum {
  ECHO_IDLE, /* device not used */
  ECHO_TRIGGERED, /* started trigger pulse */
  ECHO_MEASURE, /* measuring echo pulse */
  ECHO_OVERFLOW, /* measurement took too long */
  ECHO_FINISHED /* measurement finished */
} US_EchoState;

typedef struct {
  LDD_TDeviceData *trigDevice; /* device handle for the Trigger pin */
  LDD_TDeviceData *echoDevice; /* input capture device handle (echo pin) */
  volatile US_EchoState state; /* state */
  TU2_TValueType capture; /* input capture value */
} US_DeviceType;

 /* device handle for the ultrasonic device */

int generatePulse(void);

void US_EventEchoOverflow(LDD_TUserData*);

static int calcAirspeed_dms(int);

int US_usToCentimeters(int, int);

void initUS(void);
#endif /* SOURCES_ULTRASONIC_H_ */
