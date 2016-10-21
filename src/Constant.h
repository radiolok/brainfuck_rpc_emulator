/*
 * Constant.h
 *
 *  Created on: 30 сент. 2016 г.
 *      Author: radiolok
 */

#ifndef CONSTANT_H_
#define CONSTANT_H_

#include "stdint.h"

#define MEMORY_LENGTH_MAX 30000

#define CYCLE_STACK_SIZE 128


#define ERROR 0
#define SUCCESS 1


//All delays in useconds
#define ONE_RELAY_DELAY (300)

#if ONE_RELAY_DELAY == 0

	#define DEFAULT_FREQUENCY 1000

#else

	#define DEFAULT_FREQUENCY 100

#endif

#define ALU_DELAY (8)
#define REG_SHIFT_DELAY (8)
#define REG_LOAD_DELAY (1)
#define REG_STORE_DELAY (4)


#define CONSOLE_LOAD_DELAY (2)
#define CONSOLE_STORE_DELAY (4)


typedef struct _cmd_t{
	uint8_t cmd;
	uint8_t bias;
}cmd_t;

#endif /* CONSTANT_H_ */
