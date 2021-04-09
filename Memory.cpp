#include "Memory.h"

void Memory::initMem(std::vector<unsigned int> instructionMemory)
{
	for (int i = 0; i < instructionMemory.size(); i++)
	{
		MemoryBank[i] = instructionMemory[i];
	}
}


int Memory::loadWord(int address)
{
	return MemoryBank[address];
}

void Memory::storeWord(int value, int address)
{
	MemoryBank[address] = value;
}


