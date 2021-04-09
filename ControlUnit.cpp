#include "ControlUnit.h"
#include <iostream>
void ControlUnitOutput::controlReset()
{
	RegDst = false;
	ALUSrc = false;
	MemtoReg = false;
	RegWrite = false;
	MemRead = false;
	MemWrite = false;
	Branch = false; 
	ALUOp1 = false; 
	ALUOp0 = false; 
	Jump = false;
	//std::cout << "Control reset\n";
}