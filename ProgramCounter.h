#pragma once
class ProgramCounter
{
public:
	int nextInstructionMemoryAddress=0;
	int getPC() { return nextInstructionMemoryAddress; }
};

