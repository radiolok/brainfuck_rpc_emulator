/*
 * Features.h
 *
 *  Created on: 30 сент. 2016 г.
 *      Author: radiolok
 */

#ifndef FEATURES_H_
#define FEATURES_H_

#include <unistd.h>
#include <signal.h>
#include <stdio.h>

#include <sys/select.h>
#include <sys/time.h>

#include "Constant.h"

void WaitRelay(int relay);

int PrepareClock(unsigned int freq);

void WaitClock(void);

#endif /* FEATURES_H_ */
