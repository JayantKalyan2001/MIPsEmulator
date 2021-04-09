#include "ALU.h"
#include <iostream>
ALU::ALU(int funct, int A, int secondInput,bool Op0,bool Op1)
{ 
	int ALUInput=0;
#pragma region FindTheALUOperation
	{
		int ALUOperation[3];
		bool f[6];
		f[3] = (bool)(funct & 0x8) >> 3;
		f[2] = (bool)(funct & 0x4) >> 2;
		f[1] = (bool)(funct & 0x2) >> 1;
		f[0] = (bool)(funct & 0x1) >> 0;
		ALUOperation[2] = (Op1 & f[1]) | Op0;
		ALUOperation[1] = (!Op1) | (!f[2]);
		ALUOperation[0] = (f[3] | f[0]) & Op1;
		ALUInput = ((int)ALUOperation[2] << 2) + ((int)ALUOperation[1] << 1 )+ (int)ALUOperation[0];
	}
#pragma endregion

#pragma region DetermineALUOutput
	enum ALUfunc {ADD=2,SUB=6,AND=0,OR=1,SLT=7};
	switch (ALUInput)
	{
	case ADD:
		output = A + secondInput;
		break;
	case SUB:
		output = A - secondInput;
		//std::cout << "A: " << A << "\n";
		//std::cout << "secondInput: " << secondInput << "\n";
		if (!output)
		{
			
			zero = true;
		}
		break;
	//bitwise ANDs the output
	case AND:
		output = A & secondInput;
		break;
	//bitwise ORs the output
	case OR:
		output = A | secondInput;
		break;
	//sets output to 1 if A<secondInput
	case SLT:
		if (A<secondInput)
		{
			output = 1;
		}
		else
		{
			output = 0;
		}
		break;
	default:
		break;
	}
#pragma endregion
}

void ALU::ALUreset()
{
	zero = false;
	output = 0;
}