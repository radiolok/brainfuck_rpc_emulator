//============================================================================
// Name        : brainfuck_rpc_emulator.cpp
// Author      : Artem Kashkanov
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <unistd.h>
#include "Source.h"
#include "Memory.h"
#include "Alu.h"
#include "Console.h"
#include "Constant.h"
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



int main(int argc, char *argv[]) {
	__itt_task_begin(domain, __itt_null, __itt_null, handle_main);
	int status = -1;
	int c = 0;
	while((c = getopt(argc, argv, "f:")) != -1){
		switch(c)
		{
		case 'f':
			status = OpenListing(optarg);
			break;
		}
	}
	if (status){
		fprintf(stderr, "Parameters error\n");
		return -1;

	}


	//Start Program:
	char cmd = 0;
	while((cmd = GetCmd())){
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
			__itt_task_begin(domain, __itt_null, __itt_null, handle_cycle);
			__itt_task_begin(domain, __itt_null, __itt_null, handle_begin);
			CycleStackPush();
			__itt_task_end(domain);
			break;
		case ']':
			__itt_task_begin(domain, __itt_null, __itt_null, handle_loop);
			if (GetVal()){
				CycleStackPop();
			}
			else{
				__itt_task_end(domain);
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
		case 0://End of the programm
			return 0;
			break;
		default:
			SetStep(cmd);
		}
		/*if (IsASymbol(cmd)){
			fprintf(stderr, "IP:%04x  %c: @%04x = %d -%c\n", GetInstrPtrVal(), cmd, GetPtrVal(), GetVal(), GetVal());
		}*/
	}
	__itt_task_end(domain);
	return 0;
}
