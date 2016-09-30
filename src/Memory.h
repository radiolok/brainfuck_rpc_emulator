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

void NextReg(void);

void PrevReg(void);


void SetVal(char val);


char GetVal(void);

size_t GetPtrVal();

#endif /* MEMORY_H_ */
