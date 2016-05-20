/*
 * Ultrasonic.c
 *
 *  Created on: Dec 30, 2012
 *      Author: Erich Styger
 *      Driver for the HC-SR04 and FRDM-KL25Z board
 */
#include "Ultrasonic.h"

typedef enum {
	ECHO_IDLE, /* device not used */
	ECHO_TRIGGERED, /* started trigger pulse */
	ECHO_MEASURE, /* measuring echo pulse */
	ECHO_OVERFLOW, /* measurement too too long */
	ECHO_FINISHED /* measurement finished */
} US_EchoState;

typedef struct {
	LDD_TDeviceData *trigDevice; /* device handle for the Trigger pin */
	LDD_TDeviceData *echoDevice; /* input capture device handle (echo pin) */
	volatile US_EchoState state; /* state */
	TU3_TValueType capture; /* input capture value */
} US_DeviceType;

static US_DeviceType usDevice; /* device handle for the ultrasonic device */

void US_EventEchoOverflow(LDD_TUserData *UserDataPtr) {
	US_DeviceType *ptr = (US_DeviceType*) UserDataPtr;

	ptr->state = ECHO_OVERFLOW;
}

void US_EventEchoCapture(LDD_TUserData *UserDataPtr) {
	US_DeviceType *ptr = (US_DeviceType*) UserDataPtr;

	if (ptr->state == ECHO_TRIGGERED) { /* 1st edge, this is the raising edge, start measurement */
		TU3_ResetCounter(ptr->echoDevice);
		ptr->state = ECHO_MEASURE;
	} else if (ptr->state == ECHO_MEASURE) { /* 2nd edge, this is the falling edge: use measurement */
		(void) TU3_GetCaptureValue(ptr->echoDevice, 0, &ptr->capture);
		ptr->state = ECHO_FINISHED;
	}
}

static uint16_t calcAirspeed_dms(uint8_t temperatureCelsius) {
	/* Return the airspeed depending on the temperature, in deci-meter per second */
	unsigned int airspeed; /* decimeters per second */

	airspeed = 3313 + (6 * temperatureCelsius); /* dry air, 0% humidity, see http://en.wikipedia.org/wiki/Speed_of_sound */
	airspeed -= (airspeed / 100) * 15; /* factor in ~15% for a relative humidity of ~40% */
	return airspeed;
}

uint16_t US_usToCentimeters(uint16_t microseconds, uint8_t temperatureCelsius) {
	return (microseconds * 100UL) / calcAirspeed_dms(temperatureCelsius) / 2; /* 2 because because of two way */
}

/* measure and return the microseconds */
uint16_t US_Measure_us(void) {
	uint16_t us;

	/* send 10us pulse on TRIG line. */
	TRIG_SetVal(usDevice.trigDevice);
	WAIT1_Waitus(10);
	usDevice.state = ECHO_TRIGGERED;
	TRIG_ClrVal(usDevice.trigDevice);
	while (usDevice.state != ECHO_FINISHED) {
		/* measure echo pulse */
		//Wenn nicht funktioniert dashier ausklammern
		if (usDevice.state == ECHO_OVERFLOW) {
			usDevice.state = ECHO_IDLE;
			return 0;
		}
	}
	us = (usDevice.capture * 1000UL) / (TU3_CNT_INP_FREQ_U_0 / 1000);
	return us;
}

int Measure() {
	uint16_t us, cm;
	//uint8_t buf[8];

	us = US_Measure_us(); //mikro Meter
	cm = US_usToCentimeters(us, 22); //Zenti Meter

//Test
//  LEDRed_Put(cm<10); /* red LED if object closer than 10 cm */
//  LEDBlue_Put(cm>=10&&cm<=100); /* blue LED if object is in 10..100 cm range */
//  LEDGreen_Put(cm>100); /* blue LED if object is in 10..100 cm range */

	return cm;
}

void US_Init(void) {
	usDevice.state = ECHO_IDLE;
	usDevice.capture = 0;
	usDevice.trigDevice = TRIG_Init(NULL);
	usDevice.echoDevice = TU3_Init(&usDevice);
}

int measureALot() {
	int temp;
	int l = 0;
	for (l; l < 9; l++) {
		temp += Measure();
	}
	return temp / 10;
}
