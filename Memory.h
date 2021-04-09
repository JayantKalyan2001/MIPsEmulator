#pragma once
#include <vector>
class Memory
{
public:
	int memRead;
	int MemoryBank[130];
	
	void initMem(std::vector<unsigned int> instructionMemory);
	int loadWord(int address);
	void storeWord(int value, int address);
};

