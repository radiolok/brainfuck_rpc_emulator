//============================================================================
// Name        : brainfuck_rpc_emulator.cpp
// Author      : Artem Kashkanov
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include "Source.h"
#include "Memory.h"
#include "Alu.h"
#include "Console.h"
#include "Constant.h"
#include "Features.h"
#include <ittnotify.h>

using namespace std;

__itt_domain* domain = __itt_domain_create("Brainfuck.machine");
__itt_string_handle* handle_main = __itt_string_handle_create("main");

__itt_string_handle* handle_next = __itt_string_handle_create("next");
__itt_string_handle* handle_prev = __itt_string_handle_create("prev");
__itt_string_handle* handle_inc = __itt_string_handle_create("inc");
__itt_string_handle* handle_dec = __itt_string_handle_create("dec");
__itt_string_handle* handle_cycle = __itt_string_handle_create("cycle");
__itt_string_handle* handle_begin = __itt_string_handle_create("begin");
__itt_string_handle* handle_loop = __itt_string_handle_create("loop");
__itt_string_handle* handle_in = __itt_string_handle_create("in");
__itt_string_handle* handle_out = __itt_string_handle_create("out");

__itt_string_handle* handle_tick = __itt_string_handle_create("tick");
__itt_string_handle* handle_tack = __itt_string_handle_create("tack");


int ExecCmd(char cmd){
	int status = 1;
	switch(cmd){
		case '>':
			__itt_task_begin(domain, __itt_null, __itt_null, handle_next);
			NextReg();
			__itt_task_end(domain);
			break;
		case '<':
			__itt_task_begin(domain, __itt_null, __itt_null, handle_prev);
			PrevReg();
			__itt_task_end(domain);
			break;
		case '+':
			__itt_task_begin(domain, __itt_null, __itt_null, handle_inc);
			SetVal(Inc(GetVal()));
			__itt_task_end(domain);
			break;
		case '-':
			__itt_task_begin(domain, __itt_null, __itt_null, handle_dec);
			SetVal(Dec(GetVal()));
			__itt_task_end(domain);
			break;
		case '[':
			__itt_task_begin(domain, __itt_null, __itt_null, handle_begin);
			CycleStackPush();
			__itt_task_end(domain);
			break;
		case ']':
			__itt_task_begin(domain, __itt_null, __itt_null, handle_loop);
			if (GetVal()){
				CycleStackPop();
			}
			__itt_task_end(domain);

			break;
		case '.':
			__itt_task_begin(domain, __itt_null, __itt_null, handle_out);
			Out(GetVal());
			__itt_task_end(domain);
			break;
		case ',':
			__itt_task_begin(domain, __itt_null, __itt_null, handle_in);
			SetVal(In());
			__itt_task_end(domain);
			break;
		case 0://End of the program
			status = 0;
			break;
		default:
			SetStep(cmd);
		}
	return status;
}

#define UP_FRONT true
#define DOWN_FRONT false

bool front = UP_FRONT;

int Tick(char *cmd){
	__itt_task_begin(domain, __itt_null, __itt_null, handle_tick);
	*cmd = GetCmd();

	return *cmd;
}

int Tack(char *cmd){
	__itt_task_begin(domain, __itt_null, __itt_null, handle_tack);
	int status = ExecCmd(*cmd);
	return status;
}



int Period(char *cmd){
	int status = 1;
	if (front == UP_FRONT){
		status = Tick(cmd);
		front = DOWN_FRONT;
	}
	else{
		status = Tack(cmd);
		front = UP_FRONT;
	}
	WaitClock();
	__itt_task_end(domain);
	return status;
}


int ExecProgram(void){
	//Start Program:
	char cmd = 0;
	while(Period(&cmd)){

	}
	return 0;
}



int main(int argc, char *argv[]) {
	__itt_task_begin(domain, __itt_null, __itt_null, handle_main);
	int status = -1;
	unsigned int clock = 0;
	int c = 0;
	while((c = getopt(argc, argv, "f:c:")) != -1){
		switch(c)
		{
		case 'f':
			status = OpenListing(optarg);
			break;
		case 'c':
			clock = atol(optarg);
			break;
		}
	}
	if (status){
		fprintf(stderr, "Parameters error\n");
		return -1;
	}
	if (clock == 0){
		clock = DEFAULT_FREQUENCY;
	}
	PrepareClock(clock);

	ExecProgram();

	__itt_task_end(domain);
	return 0;
}
