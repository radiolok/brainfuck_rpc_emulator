/*
 * Memory.h
 *
 *  Created on: 30 сент. 2016 г.
 *      Author: radiolok
 */

#ifndef MEMORY_H_
#define MEMORY_H_

#include "Constant.h"
#include "stddef.h"
#include <ittnotify.h>
#include <limits.h>
#include <stdint.h>
#include "Features.h"
#include "Source.h"

#include <stdint.h>

void PrintMemory(char *str, size_t mem);

int NextReg(void);

int PrevReg(void);


void SetVal(uint8_t val);


uint8_t GetVal(void);

size_t GetPtrVal();

#endif /* MEMORY_H_ */
