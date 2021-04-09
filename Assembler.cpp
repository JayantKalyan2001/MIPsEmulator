#include "Assembler.h"
#include <map>
#include <iostream>
#include <string>
std::vector<unsigned int> Assembler::AssemblerOutput(std::vector<std::vector<std::string>> instructionVectors)
{
	std::map<std::string, unsigned int> instructionInt;
	int cumulativeInstructionInt = 0;
	std::vector<unsigned int> output;

#pragma region RTypeFunctions
	instructionInt.insert(std::pair<std::string, unsigned int>("add", 0x20 ));
	instructionInt.insert(std::pair<std::string, unsigned int>("and", 0x24));
	instructionInt.insert(std::pair<std::string, unsigned int>("nor", 0x27));
	instructionInt.insert(std::pair<std::string, unsigned int>("or", 0x25));
	instructionInt.insert(std::pair<std::string, unsigned int>("slt", 0x2a));
	instructionInt.insert(std::pair<std::string, unsigned int>("sub", 0x22));
	instructionInt.insert(std::pair<std::string, unsigned int>("sll", 0));
	instructionInt.insert(std::pair<std::string, unsigned int>("srl", 0x02));
#pragma endregion

#pragma region ImmediateAndJumpOpcodes
	instructionInt.insert(std::pair<std::string, unsigned int>("addi", 0x8<<26));
	instructionInt.insert(std::pair<std::string, unsigned int>("andi", 0xc << 26));
	instructionInt.insert(std::pair<std::string, unsigned int>("beq", 0x4 << 26));
	instructionInt.insert(std::pair<std::string, unsigned int>("bne", 0x5 << 26));
	instructionInt.insert(std::pair<std::string, unsigned int>("j", 0x2 << 26));
#pragma endregion

#pragma region LoadWordAndStoreWord
	instructionInt.insert(std::pair<std::string, unsigned int>("lw", 0x23 << 26));
	instructionInt.insert(std::pair<std::string, unsigned int>("sw", 0x2b << 26));
#pragma endregion 

#pragma region tempRegisters
	instructionInt.insert(std::pair<std::string, unsigned int>("$t0", 8));
	instructionInt.insert(std::pair<std::string, unsigned int>("$t1", 9));
	instructionInt.insert(std::pair<std::string, unsigned int>("$t2", 10));
	instructionInt.insert(std::pair<std::string, unsigned int>("$t3", 11));
	instructionInt.insert(std::pair<std::string, unsigned int>("$t4", 12));
	instructionInt.insert(std::pair<std::string, unsigned int>("$t5", 13));
	instructionInt.insert(std::pair<std::string, unsigned int>("$t6", 14));
	instructionInt.insert(std::pair<std::string, unsigned int>("$t7", 15));
	instructionInt.insert(std::pair<std::string, unsigned int>("$t8", 24));
	instructionInt.insert(std::pair<std::string, unsigned int>("$t9", 25));
#pragma endregion

#pragma region storedRegisters
	instructionInt.insert(std::pair<std::string, unsigned int>("$zero",0));
	instructionInt.insert(std::pair<std::string, unsigned int>("$s0", 16));
	instructionInt.insert(std::pair<std::string, unsigned int>("$s1", 17));
	instructionInt.insert(std::pair<std::string, unsigned int>("$s2", 18));
	instructionInt.insert(std::pair<std::string, unsigned int>("$s3", 19));
	instructionInt.insert(std::pair<std::string, unsigned int>("$s4", 20));
	instructionInt.insert(std::pair<std::string, unsigned int>("$s5", 21));
	instructionInt.insert(std::pair<std::string, unsigned int>("$s6", 22));
	instructionInt.insert(std::pair<std::string, unsigned int>("$s7", 23));
#pragma endregion

	for (int i = 0; i < instructionVectors.size(); i++)
	{
		//r type
		if (instructionVectors[i][0]=="add"|| instructionVectors[i][0] == "and"|| instructionVectors[i][0] == "nor"|| instructionVectors[i][0] == "or"|| instructionVectors[i][0] == "slt"|| instructionVectors[i][0] == "sub"||instructionVectors[i][0] == "sll"|| instructionVectors[i][0] == "srl")
		{
			cumulativeInstructionInt += instructionInt.at(instructionVectors[i][0]);
			cumulativeInstructionInt += instructionInt.at(instructionVectors[i][1]) << 11;
			cumulativeInstructionInt += instructionInt.at(instructionVectors[i][2]) << 21;
			if (instructionInt.count(instructionVectors[i][3]))
			{
				cumulativeInstructionInt += instructionInt.at(instructionVectors[i][3]) << 16;
			}
			else
			{
				std::cout << instructionVectors[i][3]<<"\n";
				cumulativeInstructionInt += stoi(instructionVectors[i][3]) << 6;
			}
		}
		//immediate
		else if (instructionVectors[i][0] == "addi" || instructionVectors[i][0] == "andi" || instructionVectors[i][0] == "beq" || instructionVectors[i][0] == "bne" )
		{
			cumulativeInstructionInt += instructionInt.at(instructionVectors[i][0]);
			cumulativeInstructionInt += instructionInt.at(instructionVectors[i][1]) << 16;
			cumulativeInstructionInt += instructionInt.at(instructionVectors[i][2]) << 21;
			cumulativeInstructionInt += stoi(instructionVectors[i][3]) & (0xFFFF);
		}
		//Store or load word
		else if (instructionVectors[i][0] == "sw" || instructionVectors[i][0] == "lw")
		{
			cumulativeInstructionInt += instructionInt.at(instructionVectors[i][0]);
			cumulativeInstructionInt += instructionInt.at(instructionVectors[i][1]) << 16;
			cumulativeInstructionInt += instructionInt.at(instructionVectors[i][3]) << 21;
			cumulativeInstructionInt += stoi(instructionVectors[i][2])&(0xFFFF);
		}
		//jump
		else if (instructionVectors[i][0] == "j")
		{
			cumulativeInstructionInt += instructionInt.at(instructionVectors[i][0]);
			cumulativeInstructionInt += stoi(instructionVectors[i][1]);
		}
		output.push_back(cumulativeInstructionInt);
		cumulativeInstructionInt = { 0 };
	}
	return output;
}