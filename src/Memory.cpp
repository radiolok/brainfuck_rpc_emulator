/*
 * Memory.cpp
 *
 *  Created on: 30 сент. 2016 г.
 *      Author: radiolok
 */

#include "Memory.h"



uint8_t Memory[USHRT_MAX] = {0};

uint16_t MemoryPtr = 0;


void NextReg(void){
	WaitRelay(REG_SHIFT_DELAY);
	if (MemoryPtr < MEMORY_LENGTH_MAX){
		MemoryPtr += GetBias();
	}
}

void PrevReg(void){
	WaitRelay(REG_SHIFT_DELAY);
	if (MemoryPtr > 0){
		MemoryPtr -= GetBias();
	}
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
