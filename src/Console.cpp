/*
 * Console.cpp
 *
 *  Created on: 30 сент. 2016 г.
 *      Author: radiolok
 */

#include "Console.h"

void Out(char val){
	putc(val, stdout);
}


char In(void){
	char val = 0;
	int data = getc(stdin);
	if (data != EOF){
		val = (char)data;

	}

	return val;
}
