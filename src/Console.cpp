/*
 * Console.cpp
 *
 *  Created on: 30 сент. 2016 г.
 *      Author: radiolok
 */

#include "Console.h"

void Out(uint8_t val){
	WaitRelay(CONSOLE_LOAD_DELAY);
	if (val < 0x20)
	{
		fprintf(stderr, "(%02x)", val);
	}
	else{
		fprintf(stderr, "%c", val);
	}

}


uint8_t In(void){
	WaitRelay(CONSOLE_STORE_DELAY);
	uint8_t val = 0;
	putc('>', stderr);
	int data = getc(stdin);
	putc('\n', stderr);
	if (data != EOF){
		val = (char)data;

	}

	return val;
}
