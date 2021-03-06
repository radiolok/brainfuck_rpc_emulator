/*
 * Source.cpp
 *
 *  Created on: 29 сент. 2016 г.
 *      Author: radiolok
 */

#include "Source.h"



cmd_t *Listing_ptr = 0;

uint32_t MaxInstrPtr = 0;

uint32_t InstrPtr = 0;

uint8_t CycleStack[CYCLE_STACK_SIZE] = {0};
//cycle stack pointer
uint32_t CyclePtr = 0;

bool IsASymbol(uint8_t c){
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
	case '~': //is a debug symbol
		result = true;
		break;
	default:

		break;
	}

	return result;
}

bool IsAIncrementer(uint8_t c){
	bool result = false;
	switch (c){
	case '<':
	case '>':
	case '+':
	case '-':
		result = true;
		break;
	default:

		break;
	}

	return result;
}

bool IsMemInc(uint8_t c){
	bool result = false;
	switch (c){
	case '>':
	case '<':
		result = true;
		break;
	default:

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

	 Listing_ptr = new cmd_t [length];

	 uint8_t *temp_data = new uint8_t [length];

	 size_t result = fread(temp_data, sizeof(uint8_t), length, fd);
	 if (result != length)
	 {
		 fprintf(stderr, "Read file error\n");
		 return -1;
	 }
	 if (InstrumentedOutput())
	 {
		 fprintf(stderr,"Brainfuck program:\n");
		 for (size_t i = 0 ; i < length; ++i)
		 {
			 if (IsASymbol(temp_data[i]))
			 {
				 if (IsAIncrementer(temp_data[i]))
				 {
					 if (MaxInstrPtr != 0)
					 {
						 if (Listing_ptr[MaxInstrPtr-1].cmd == temp_data[i])
						 {//commands are equal, inc bias
							 Listing_ptr[MaxInstrPtr-1].bias++;
						 }
						 else{
							 Listing_ptr[MaxInstrPtr].cmd = temp_data[i];
							 Listing_ptr[MaxInstrPtr].bias = 1;
							 MaxInstrPtr++;
						 }
					 }
					 else
					 {
						 Listing_ptr[MaxInstrPtr].cmd = temp_data[i];
						 Listing_ptr[MaxInstrPtr].bias = 1;
						 MaxInstrPtr++;
					 }
				 }
				 else
				 {
					 Listing_ptr[MaxInstrPtr].cmd = temp_data[i];
					 Listing_ptr[MaxInstrPtr].bias = 0;
					 MaxInstrPtr++;
				 }
				 fprintf(stderr, "%c", temp_data[i]);
				 if ((i >0) && (!(i % 60))){
					 fprintf(stderr, "\n");
				 }
			 }
		 }
		 fprintf(stderr, "\n");
		 PrintProgram();
	 }
	return 0;
}


int CycleAddLayer(void)
{
	CycleStack[CyclePtr]  = InstrPtr;
	if (InstrumentedOutput())
	{
		fprintf(stderr, "Add:SP:%d, IP:@%04X\n", CyclePtr, InstrPtr);
	}
	if (CyclePtr < CYCLE_STACK_SIZE){
		CyclePtr++;
	}
	else
	{
		fprintf(stderr, "CycleStack++ OVF!\n");
		return ERROR;
	}
	/*CycleStack[CyclePtr]  = InstrPtr;*/
	return SUCCESS;
}

int CycleRemoveLayer(void)
{
	if (InstrumentedOutput())
	{
		fprintf(stderr, "Remove:SP:%d, IP:@%04X\n", CyclePtr, InstrPtr);
	}
	if (CyclePtr > 0){
		CyclePtr--;
	}
	else
	{
		fprintf(stderr, "CycleStack-- OVF!\n");
		return ERROR;
	}

	return SUCCESS;
}

int CycleRestartLayer()
{
	InstrPtr = (CyclePtr > 0) ?
			CycleStack[CyclePtr -1] :
			CycleStack[CyclePtr];
	if (InstrumentedOutput())
	{
		fprintf(stderr, "Restart:SP:%d, IP:@%04X\n", CyclePtr, InstrPtr);
	}
	return SUCCESS;
}

int CycleSkipLayer(void)
{
	size_t i = 1;
	while (i)
	{
		IncIp();
		switch (GetCmd())
		{
		case '[':
			i++;
			break;
		case ']':
			i--;
			break;
		}
	}
	if (InstrumentedOutput())
	{
		fprintf(stderr, "Skip:SP:%d, IP:@%04X\n", CyclePtr, InstrPtr);
	}
	return SUCCESS;
}


size_t GetStackPtr()
{
	return CyclePtr;
}



void PrintProgram(void){
	fprintf(stderr, "Loaded Program:\n");
	for (size_t i = 0; i < MaxInstrPtr; ++i)
	{
		if (IsAIncrementer(Listing_ptr[i].cmd))
		{
			fprintf(stderr, "%c(%d)", Listing_ptr[i].cmd, Listing_ptr[i].bias);
		}
		else
		{
			fprintf(stderr, "%c", Listing_ptr[i].cmd);
		}
	}
	fprintf(stderr, "\n");
}

void IncIp(void)
{
	if (InstrPtr < MaxInstrPtr)
	{
		InstrPtr++;
	}
}

uint8_t GetBias(void)
{
	return  Listing_ptr[InstrPtr].bias;
}

uint8_t GetCmd(void){

	return Listing_ptr[InstrPtr].cmd;//EndOfProgramm

}

size_t GetIp(void){
	return InstrPtr;
}

