/*
 * Source.cpp
 *
 *  Created on: 29 сент. 2016 г.
 *      Author: radiolok
 */

#include "Source.h"

char *Listing_ptr = 0;

size_t MaxInstrPtr;

//instruction pointer
size_t InstrPtr = 0;

//cycle pointer
size_t CyclePtr = 0;

//cycle status
bool CycleStatus = false;

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
	case '}':
		result = true;
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

	 size_t result = fread(temp_data, length, sizeof(char), fd);
	 if (result != length){
		 fprintf(stderr, "Read file error\n");
		 return -1;
	 }

	 fprintf(stdout,"Brainfuck program:\n");
	 for (size_t i = 0 ; i < length; ++i){
		 if (IsASymbol(temp_data[i])){
			 Listing_ptr[MaxInstrPtr++] = temp_data[i];
			 fprintf(stdout, "%c", temp_data[i]);
			 if (!(i % 64)){
				 fprintf(stdout, "\n");
			 }
		 }
	 }


	return 0;
}


char GetCmd(void){

	InstrPtr++;

	if (InstrPtr < MaxInstrPtr){

		if (Listing_ptr[InstrPtr] == '['){
			CyclePtr = InstrPtr;
			CycleStatus = true;
		}
		return Listing_ptr[InstrPtr];
	}

	return 0;//EndOfProgramm
}


void ReturnCycle(void){
	InstrPtr = CyclePtr;
	CycleStatus = false;
}
