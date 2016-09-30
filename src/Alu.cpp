/*
 * Alu.cpp
 *
 *  Created on: 30 сент. 2016 г.
 *      Author: radiolok
 */

#include "Alu.h"

char alu_step = 1;

void SetStep(char step){
	if ((step >=0x30) &&( step <=0x39)){
		step -= 0x30;
	}
	else{
		if ((step>=0x40) && (step <=0x45)){
			step = step - 0x40 + 0xa;
		}
		else{
			if ((step>=0x61) && (step <=0x66)){
				step = step - 0x61 + 0xa;
			}
			else{

			}
		}
	}
	if (step == 0){
		step = 16;
	}
	alu_step = step;
}

char Inc(char val){
	Latency(ALU_DELAY);
	char result = val + alu_step;
	alu_step = 1;
	return result;

}

char Dec(char val){
	Latency(ALU_DELAY);
	char result = val - alu_step;
	alu_step = 1;
	return result;
}
