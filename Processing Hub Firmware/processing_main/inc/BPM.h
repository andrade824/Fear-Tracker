/*
 * BPM.h
 *
 *  Created on: Jan 29, 2015
 *      Author: B-Chan
 */
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#ifndef BPM_H_
#define BPM_H_

void BPMTimerSetUp();
uint8_t GetBPM();
bool getFlag();
void setFlag(_Bool f);



#endif /* BPM_H_ */
