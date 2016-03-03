/*
 * ultrasonic.c
 *
 *  Created on: 03.03.2016
 *      Author: danie
 */
#include "ultrasonic.h"
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
#include "MotorBit.h"
#include "BitIoLdd4.h"
#include "TrigUS.h"
#include "TU2.h"
//Quelle
//http://mcuoneclipse.com/2013/01/01/tutorial-ultrasonic-ranging-with-the-freedom-board/


static US_DeviceType usDevice;

int generatePulse() {
	  int us;

	  /* send 10us pulse on TRIG line. */
	  TrigUS_SetVal(usDevice.trigDevice);
	  WAIT1_Waitus(10);
	  usDevice.state = ECHO_TRIGGERED;
	  TrigUS_ClrVal(usDevice.trigDevice);
	  while(usDevice.state!=ECHO_FINISHED) {
	    /* measure echo pulse */
	    if (usDevice.state==ECHO_OVERFLOW) { /* measurement took too long? */
	      usDevice.state = ECHO_IDLE;
	      return 0; /* no echo, error case */
	    }
	  }
	  us = (usDevice.capture*1000UL)/(TU2_CNT_INP_FREQ_U_0/1000);
	  return us;
	}


//	int i = 5;
//	while (i < 5) {
//		TrigUS_SetVal();
//		WAIT1_Waitus(10);
//		TrigUS_ClrVal();
//		i++;
//	}



void initUS(void) {
  usDevice.state = ECHO_IDLE;
  usDevice.capture = 0;
  usDevice.trigDevice = TRIG_Init(NULL);
  usDevice.echoDevice = TU2_Init(&usDevice);
}

void US_EventEchoOverflow(LDD_TUserData *UserDataPtr) {
  US_DeviceType *ptr = (US_DeviceType*)UserDataPtr;

  ptr->state = ECHO_OVERFLOW;
}


static int calcAirspeed_dms(int temperatureCelsius) {
  /* Return the airspeed depending on the temperature, in deci-meter per second */
  unsigned int airspeed; /* decimeters per second */

  airspeed = 3313 + (6 * temperatureCelsius); /* dry air, 0% humidity, see http://en.wikipedia.org/wiki/Speed_of_sound */
  airspeed -= (airspeed/100)*15; /* factor in ~15% for a relative humidity of ~40% */
  return airspeed;
}

int US_usToCentimeters(int microseconds, int temperatureCelsius) {
  return (microseconds*100UL)/calcAirspeed_dms(temperatureCelsius)/2; /* 2 because of two way */
}
