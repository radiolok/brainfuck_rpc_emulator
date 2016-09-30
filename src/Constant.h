/*
 * Constant.h
 *
 *  Created on: 30 сент. 2016 г.
 *      Author: radiolok
 */

#ifndef CONSTANT_H_
#define CONSTANT_H_

#define MEMORY_LENGTH_MAX 30000

#define CYCLE_STACK_SIZE 128

//All delays in useconds
#define ONE_RELAY_DELAY (1)


#define ALU_DELAY (ONE_RELAY_DELAY*4)
#define REG_SHIFT_DELAY (ONE_RELAY_DELAY*3)
#define REG_LOAD_DELAY (ONE_RELAY_DELAY*1)
#define REG_STORE_DELAY (ONE_RELAY_DELAY*4)


#define CONSOLE_LOAD_DELAY (ONE_RELAY_DELAY*1)
#define CONSOLE_STORE_DELAY (ONE_RELAY_DELAY*4)

#endif /* CONSTANT_H_ */
