/*
 * Memory.cpp
 *
 *  Created on: 30 сент. 2016 г.
 *      Author: radiolok
 */

#include "Memory.h"



char Memory[MEMORY_LENGTH_MAX] = {0};

size_t MemoryPtr = 0;


void NextReg(void){
	WaitRelay(REG_SHIFT_DELAY);
	if (MemoryPtr < MEMORY_LENGTH_MAX){
		MemoryPtr++;
	}
}

void PrevReg(void){
	WaitRelay(REG_SHIFT_DELAY);
	if (MemoryPtr > 0){
		MemoryPtr--;
	}
}


void SetVal(char val){
	WaitRelay(REG_STORE_DELAY);
	Memory[MemoryPtr] = val;
}


char GetVal(void){
	WaitRelay(REG_STORE_DELAY);
	return Memory[MemoryPtr];
}


size_t GetPtrVal(){
	return MemoryPtr;
}
