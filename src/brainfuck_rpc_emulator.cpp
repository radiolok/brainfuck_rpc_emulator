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

#include <stdint.h>
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


long long unsigned int OverallInstructionNumber = 0;



void PrintDebug()
{
	if (InstrumentedOutput())
	{
		fprintf(stderr, "IP:@%04lX\t", GetIp());

		switch (GetCmd()){
		case '>':
		case '<':
		case '+':
		case '-':
			fprintf(stderr, "CMD:'%c(%d)'\t",GetCmd(), GetBias());
			break;
		case '[':
		case ']':
			fprintf(stderr, "CMD:'%c'(%lu)\t",GetCmd(), GetStackPtr());
			break;
		default:
			fprintf(stderr, "CMD:'%c'\t\t",GetCmd());
			break;
		}
		char MemoryStr[256];
		PrintMemory(MemoryStr, 7);
		fprintf(stderr, "%s\n", MemoryStr);
	}

}


int ExecCmd(uint8_t cmd){
	int status = SUCCESS;
	switch(cmd){
		case '>':
			__itt_task_begin(domain, __itt_null, __itt_null, handle_next);
			status = NextReg();
			__itt_task_end(domain);
			break;
		case '<':
			__itt_task_begin(domain, __itt_null, __itt_null, handle_prev);
			status = PrevReg();
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
			if (GetVal())
			{
				status = CycleAddLayer();
			}
			else
			{
				status = CycleSkipLayer();
			}
			__itt_task_end(domain);
			break;
		case ']':
			__itt_task_begin(domain, __itt_null, __itt_null, handle_loop);
			if (GetVal())
			{
				status = CycleRestartLayer();
			}
			else
			{
				status = CycleRemoveLayer();
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
		case '~':
			PrintDebug();
			break;
		case 0://End of the program
			status = ERROR;
			break;
		default:
			break;
		}
	return status;
}

#define UP_FRONT true
#define DOWN_FRONT false

bool front = UP_FRONT;

int Tick(void){

	__itt_task_begin(domain, __itt_null, __itt_null, handle_tack);


	PrintDebug();
	OverallInstructionNumber++;
	if ((OverallInstructionNumber) && !(OverallInstructionNumber % 1000000))
	{
		fprintf(stderr, "OverallInstructionNumber = %lluM\r", OverallInstructionNumber / 1000000);
	}

	int status = ExecCmd(GetCmd());

	return status;
}

int Tack(){

	__itt_task_begin(domain, __itt_null, __itt_null, handle_tick);
	IncIp();

	return 1;
}



int Period(){

	int status = 1;
	if (front == UP_FRONT){
		status = Tick();
		front = DOWN_FRONT;
	}
	else{
		status = Tack();
		front = UP_FRONT;
	}
	WaitClock();
	__itt_task_end(domain);
	return status;
}


int ExecProgram(void){
	//Start Program:
	while(Period() == SUCCESS){

	}
	return 0;
}



int main(int argc, char *argv[]) {
	__itt_task_begin(domain, __itt_null, __itt_null, handle_main);
	int status = -1;
	unsigned int clock = 0;
	int c = 0;
	while((c = getopt(argc, argv, "f:c:di")) != -1){
		switch(c)
		{
		case 'f':
			status = OpenListing(optarg);
			break;
		case 'c':
			clock = atol(optarg);
			break;
		case 'd':
			DelayOff();
			break;
		case 'i':
			SetInstrumented();
			break;
		}
	}
	if (status){
		fprintf(stderr, "Parameters error\n");
		return -1;
	}
	if (IsDelay())
	{
		if (clock == 0){
			clock = DEFAULT_FREQUENCY;
		}
		PrepareClock(clock);

	}

	ExecProgram();

	__itt_task_end(domain);
	return 0;
}
