#include <bitset>
#include "ProgramCounter.h"
#include "Tokeniser.h"
#include "Assembler.h"
#include "Register.h"
#include "ControlUnit.h"
#include "ALU.h"
#include "Memory.h"

Tokeniser token;
Assembler assemble;
Register mipsRegister;
ProgramCounter PC;
ControlUnitOutput control;
Memory mem;
unsigned int currentInstruct;
int opcode, funct;
std::vector<std::vector<std::string>> tokens;
std::vector<unsigned int> instructionMemory;
uint32_t A, B, IR, ALUout;
void fetch(std::vector<unsigned int> inputInstruct);
void decoder();
void execute();
void memory();
void writeBack();

int main()
{
	tokens = token.stringtokenReader();
	instructionMemory = assemble.AssemblerOutput(tokens);
	tokens = token.stringtokenReader();
	mem.initMem(instructionMemory);
	size_t counter;
	for (counter = 0; PC.nextInstructionMemoryAddress < instructionMemory.size() ; counter++)
	//for (size_t i = 0; i < instructionMemory.size(); i++)
	{	
		//if (counter == 1000) // gets out of an infinite loop
		//	break;
		fetch(instructionMemory);
		decoder();
		execute();
		memory();
		writeBack();
		std::cout << "current line no: " << PC.nextInstructionMemoryAddress << "\n";
		std::cout << "\t" << "$t0: " << mipsRegister.Temporaries[0] << "\n";
		std::cout << "\t" << "$t1: " << mipsRegister.Temporaries[1] << "\n";
		std::cout << "\t" << "$t2: " << mipsRegister.Temporaries[2] << "\n";
	}
	std::cout << "insruction execution count = " << counter<<"\n";
	for (int i = 0; i < 130; i++)
	{
		std::cout << i << " " << std::bitset<32>(mem.MemoryBank[i]) << "\n";
	}
}

 void fetch(std::vector<unsigned int> inputInstruct)
{
	 //int counter = PC.getPC();
	 
	currentInstruct = instructionMemory[PC.nextInstructionMemoryAddress];
	//std::cout<<std::bitset<32>(currentInstruct) << "\n";
	PC.nextInstructionMemoryAddress++;
}

 void decoder()
{
	opcode = (currentInstruct & 0xFC000000) >> 26;
	//std::cout << "opcode: " << std::bitset<6>(opcode) << "\n";
	funct = currentInstruct & 0x3F;
	mipsRegister.readReg1 = (currentInstruct & 0x3E00000) >> 21;
//	std::cout << "reg 1: "<<mipsRegister.readReg1 << "\n";
	mipsRegister.readReg2 = (currentInstruct & 0x1F0000) >> 16;
//	std::cout << "reg 2: " <<mipsRegister.readReg2 << "\n";
	if (opcode==0)
	{
		control.RegDst = true;
		control.ALUOp1 = true;
	}
	if (opcode == LW)
	{
		control.MemtoReg = true;
		control.MemRead = true;
	}
	if (opcode == BEQ|| opcode == BNE)
	{
		control.Branch = true;
		control.ALUOp0 = true;
	}
	if (opcode == SW)
	{
		control.MemWrite = true;
	}
	if ((!opcode) || opcode == LW || opcode==ADDI)
	{
		//std::cout << "addi regwrite\n";
		control.RegWrite = true;
	}
	if (opcode == LW || opcode == SW || opcode==ADDI)
	{
		//std::cout << "addi alu src\n";
		control.ALUSrc = true;
	}
	if (opcode == J)
	{
		control.Jump = true;
	}
	
	mipsRegister.readData1 = mipsRegister.readFromRegister(mipsRegister.readReg1);
	mipsRegister.readData2 = mipsRegister.readFromRegister(mipsRegister.readReg2);
	A = mipsRegister.readData1;
	B = mipsRegister.readData2;
	//std::cout << A << "\n";
	//std::cout << B << "\n";
	/*std::cout << "RegDst "<<control.RegDst << "\n";
	std::cout << "ALU src " << control.ALUSrc << "\n";
	std::cout << "MemtoReg " << control.MemtoReg << "\n";
	std::cout << "RegWrite " << control.RegWrite << "\n";
	std::cout << "MemRead " << control.MemRead << "\n";
	std::cout << "MemWrite " << control.MemWrite << "\n";*/
	//std::cout << "Branch " << control.Branch << "\n";
	/*std::cout << "ALU op1 " << control.ALUOp1 << "\n";
	std::cout << "ALU op0 " << control.ALUOp0 << "\n";
	std::cout << "jump " << control.Jump << "\n";*/

}

 void execute()
{
	if (control.ALUSrc)
	{
		ALU alu = ALU(funct, A, currentInstruct & 0xFFFF, control.ALUOp0, control.ALUOp1);	
		ALUout = alu.output;
		alu.ALUreset();
	}
	else
	{
		ALU alu = ALU(funct, A, B, control.ALUOp0, control.ALUOp1);
		ALUout = alu.output;
		//std::cout << "zero " << alu.zero <<"\n";
		if (alu.zero&&control.Branch && ((currentInstruct & 0xFC000000) >> 26)==BEQ) //beq
		{
		//	std::cout << "beq\n";
			std::cout <<"increment "<< (static_cast<int16_t>(currentInstruct & 0xFFFF)) << "\n";
			PC.nextInstructionMemoryAddress += (static_cast<int16_t>(currentInstruct & 0xFFFF))-1;
		}
		else if ((!alu.zero) && control.Branch && ((currentInstruct & 0xFC000000) >> 26) == BNE) //bne
		{
		//	std::cout << "bne\n";
			std::cout << "increment " << static_cast<int16_t>(currentInstruct & 0xFFFF) << "\n";
			PC.nextInstructionMemoryAddress += (static_cast<int16_t>(currentInstruct & 0xFFFF)) -1;
		}
		alu.ALUreset();
	}	
	if (control.Jump)
	{
		//std::cout << "new " << (currentInstruct & 0x3FFFFFF) << "\n";
		PC.nextInstructionMemoryAddress = currentInstruct & 0x3FFFFFF;
	}
	//std::cout << "ALU out " << ALUout<<"\n";
	
}

 void memory()
{ 
 if(control.MemWrite)
	{
	 mem.storeWord(B, ALUout);
	}
}


 void writeBack()
{
	int writeData, writeReg;
	if (control.MemtoReg)
	{
		writeData=mem.loadWord(ALUout);
	}
	else
	{
		writeData = ALUout;
	//	std::cout << "write data= " << writeData << " \n";
	}
	if (control.RegDst)
	{
		writeReg = (currentInstruct & 0xF800)>>11;
		//std::cout << "register written: " << std::bitset<5>(writeReg) << "\n";
	}
	else
	{
		writeReg = (currentInstruct & 0x1F0000)>>16;
		//std::cout <<"register written: " <<std::bitset<5>(writeReg)<<"\n";
	}

	if (control.RegWrite)
	{
		mipsRegister.writeToRegister(writeReg, writeData);
	}

	control.controlReset();
	
}

 

