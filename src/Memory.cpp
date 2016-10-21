/*
 * Memory.cpp
 *
 *  Created on: 30 сент. 2016 г.
 *      Author: radiolok
 */

#include "Memory.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"


uint8_t Memory[USHRT_MAX] = {0};

uint16_t MemoryPtr = 0;

void PrintMemory(char *str, size_t mem)
{
	char *s_ptr = str;

	uint16_t start_ptr = MemoryPtr - mem / 2;
	uint16_t stop_ptr = start_ptr + mem;

	size_t s_num = 0;

	for (uint16_t m_ptr = start_ptr; m_ptr != stop_ptr; ++m_ptr)
	{
		if (m_ptr == MemoryPtr)
		{
			s_num = sprintf(s_ptr, "%s@%04X(%02X)%s ", ANSI_COLOR_CYAN, m_ptr, Memory[m_ptr], ANSI_COLOR_RESET);
		}
		else
		{
			s_num = sprintf(s_ptr, "@%04X(%02X) ", m_ptr, Memory[m_ptr]);
		}

		s_ptr += s_num;
	}
}

int NextReg(void){
	WaitRelay(REG_SHIFT_DELAY);

	MemoryPtr += GetBias();
	if (InstrumentedOutput())
	{
		fprintf(stderr, "MemoryPtr+%d = %04X \n", GetBias(), MemoryPtr);
	}
	return SUCCESS;
}

int PrevReg(void){
	WaitRelay(REG_SHIFT_DELAY);

	MemoryPtr -= GetBias();
	if (InstrumentedOutput())
	{
		fprintf(stderr, "MemoryPtr-%d = %04X \n", GetBias(), MemoryPtr);
	}
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
