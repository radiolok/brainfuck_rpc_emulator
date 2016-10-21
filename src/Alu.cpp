/*
 * Alu.cpp
 *
 *  Created on: 30 сент. 2016 г.
 *      Author: radiolok
 */

#include "Alu.h"



uint8_t Inc(uint8_t val){
	WaitRelay(ALU_DELAY);
	uint8_t result = val + GetBias();

	return result;

}

uint8_t Dec(uint8_t val){
	WaitRelay(ALU_DELAY);
	uint8_t result = val - GetBias();

	return result;
}
