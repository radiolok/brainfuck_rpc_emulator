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
#include <ittnotify.h>
#include "Features.h"
#include "Alu.h"


bool IsASymbol(uint8_t c);
uint8_t OpenListing(const char *path);

uint8_t GetCmd(void);

uint8_t GetBias();

int CycleStackPush(void);

int CycleStackPop(bool);

size_t GetIp(void);

void PrintProgram(void);

void IncIp(void);

#endif /* SOURCE_H_ */
