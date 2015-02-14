/*
 * This file contains functions needed to initialize the timer used in this sytem
 *
 * Created: 12/23/2014 8:05:11 PM
 * Author: Devon
 */ 
#ifndef TIMER_H_
#define TIMER_H_

#include <stdbool.h>

// Initializes Timer 1 to trigger an interrupt every 1ms
void SetupTimer(void);

// Tells the main routine to retrieve and send out data
extern volatile bool ready_to_send;

#endif /* TIMER_H_ */