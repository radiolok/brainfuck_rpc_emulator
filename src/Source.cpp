/*
 * Source.cpp
 *
 *  Created on: 29 сент. 2016 г.
 *      Author: radiolok
 */

#include "Source.h"




char *Listing_ptr = 0;

size_t MaxInstrPtr = 0;

//instruction pointer
volatile size_t InstrPtr = 0;


char CycleStack[CYCLE_STACK_SIZE] = {0};
//cycle stack pointer
size_t CyclePtr = 0;

bool IsASymbol(char c){
	bool result = false;
	switch (c){
	case '>':
	case '<':
	case '+':
	case '-':
	case '.':
	case ',':
	case '[':
	case ']':
		result = true;
		break;
	default:
		if (((c >=0x30) &&( c <=0x39)) ||
				((c>=0x40) && (c <=0x45))||
				((c>=0x61) && (c <=0x66))){
			result = true;
		}
		break;
	}

	return result;
}


uint8_t OpenListing(const char *path){

	FILE *fd;

	if ((fd = fopen(path, "r"))==NULL) {
	  fprintf(stderr, "Couldn't open file %s\n", path);
	  return -1;
	}
	 fseek(fd, 0, SEEK_END);    // Go to end
	 size_t  length = ftell(fd); // read the position which is the size
	 fseek(fd, 0, SEEK_SET);  // restore original position

	 Listing_ptr = new char [length];

	 char *temp_data = new char [length];

	 size_t result = fread(temp_data, sizeof(char), length, fd);
	 if (result != length){
		 fprintf(stderr, "Read file error\n");
		 return -1;
	 }

	 fprintf(stdout,"Brainfuck program:\n");
	 for (size_t i = 0 ; i < length; ++i){
		 if (IsASymbol(temp_data[i])){
			 Listing_ptr[MaxInstrPtr++] = temp_data[i];
			 fprintf(stdout, "%c", temp_data[i]);
			 if ((i >0) && (!(i % 60))){
				 fprintf(stdout, "\n");
			 }
		 }
	 }
	 fprintf(stdout, "\n");

	return 0;
}


void CycleStackPush(void){

	CycleStack[CyclePtr] = InstrPtr;
	if (CyclePtr < CYCLE_STACK_SIZE){
		CyclePtr++;
	}
}

void CycleStackPop(void){
	if (CyclePtr > 0){
		CyclePtr--;
	}
	InstrPtr = CycleStack[CyclePtr];
}


char GetCmd(void){

	char cmd = Listing_ptr[InstrPtr];

	if (InstrPtr < MaxInstrPtr){
		InstrPtr++;

	}

	return cmd;//EndOfProgramm
}

size_t GetInstrPtrVal(void){
	return InstrPtr;
}

