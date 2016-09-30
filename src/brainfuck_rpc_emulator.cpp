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

using namespace std;

int main(int argc, char *argv[]) {

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
			NextReg();
			break;
		case '<':
			PrevReg();
			break;
		case '+':
			SetVal(Inc(GetVal()));
			break;
		case '-':
			SetVal(Dec(GetVal()));
			break;
		case '[':
			CycleStackPush();
			break;
		case ']':
			if (GetVal()){
				CycleStackPop();
			}
			break;
		case '.':
			Out(GetVal());
			break;
		case ',':
			SetVal(In());
			break;
		case 0://End of the programm
			return 0;
			break;
		}
		/*if (IsASymbol(cmd)){
			fprintf(stderr, "IP:%04x  %c: @%04x = %d -%c\n", GetInstrPtrVal(), cmd, GetPtrVal(), GetVal(), GetVal());
		}*/
	}
	return 0;
}
