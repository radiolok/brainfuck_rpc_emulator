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
	Latency(REG_SHIFT_DELAY);
	if (MemoryPtr < MEMORY_LENGTH_MAX){
		MemoryPtr++;
	}
}

void PrevReg(void){
	Latency(REG_SHIFT_DELAY);
	if (MemoryPtr > 0){
		MemoryPtr--;
	}
}


void SetVal(char val){
	Latency(REG_STORE_DELAY);
	Memory[MemoryPtr] = val;
}


char GetVal(void){
	Latency(REG_STORE_DELAY);
	return Memory[MemoryPtr];
}


size_t GetPtrVal(){
	return MemoryPtr;
}
