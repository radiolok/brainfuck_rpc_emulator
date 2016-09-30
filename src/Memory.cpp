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
	if (MemoryPtr < MEMORY_LENGTH_MAX){
		MemoryPtr++;
	}
}

void PrevReg(void){
	if (MemoryPtr > 0){
		MemoryPtr--;
	}
}


void SetVal(char val){
	Memory[MemoryPtr] = val;
}


char GetVal(void){
	return Memory[MemoryPtr];
}


size_t GetPtrVal(){
	return MemoryPtr;
}
