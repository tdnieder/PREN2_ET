/*
 * interface.h
 *
 *  Created on: 02.03.2016
 *      Author: danie
 */



#ifndef SOURCES_INTERFACE_H_
#define SOURCES_INTERFACE_H_

typedef enum {
  TIMER_IDLE,
  TIMER_USED
} Timer;

typedef struct {
Timer Timer0;
Timer Timer1;
Timer Timer2;
} TimerState;

volatile TimerState Status;

void CDC_Run(void);

void cutString(char*);

void switchCase(char*);

void shitDown(void);

char* itoa(int,char*,int);

void reverse(char[], int);

void swap(int*,int*);
#endif /* SOURCES_INTERFACE_H_ */
