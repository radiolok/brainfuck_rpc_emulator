/*
 * Console.cpp
 *
 *  Created on: 30 сент. 2016 г.
 *      Author: radiolok
 */

#include "Console.h"

void Out(char val){
	Latency(CONSOLE_LOAD_DELAY);
	putc(val, stderr);
}


char In(void){
	Latency(CONSOLE_STORE_DELAY);
	char val = 0;
	int data = getc(stdin);
	if (data != EOF){
		val = (char)data;

	}

	return val;
}
