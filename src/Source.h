/*
 * Source.h
 *
 *  Created on: 29 сент. 2016 г.
 *      Author: radiolok
 */

#ifndef SOURCE_H_
#define SOURCE_H_


#include <stdint.h>
#include <stdio.h>
#include <stddef.h>

#include <linux/limits.h>

#include "Constant.h"



bool IsASymbol(char c);
uint8_t OpenListing(const char *path);

char GetCmd(void);

void CycleStackPush(void);

void CycleStackPop(void);

size_t GetInstrPtrVal(void);

#endif /* SOURCE_H_ */
