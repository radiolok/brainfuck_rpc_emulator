/*
 * Memory.cpp
 *
 *  Created on: 30 сент. 2016 г.
 *      Author: radiolok
 */

#include "Memory.h"



uint8_t Memory[USHRT_MAX] = {0};

uint16_t MemoryPtr = 0;


int NextReg(void){
	WaitRelay(REG_SHIFT_DELAY);

	MemoryPtr += GetBias();

	return SUCCESS;
}

int PrevReg(void){
	WaitRelay(REG_SHIFT_DELAY);

	MemoryPtr -= GetBias();

	return SUCCESS;
}


void SetVal(uint8_t val){
	WaitRelay(REG_STORE_DELAY);
	Memory[MemoryPtr] = val;
}


uint8_t GetVal(void){
	WaitRelay(REG_STORE_DELAY);
	return Memory[MemoryPtr];
}


size_t GetPtrVal(){
	return MemoryPtr;
}
