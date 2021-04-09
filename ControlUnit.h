#pragma once
class ControlUnitOutput
{public:
	void controlReset();
	bool RegDst=false, ALUSrc = false, MemtoReg = false, RegWrite = false, MemRead = false, MemWrite = false, Branch = false, ALUOp1 = false, ALUOp0 = false, Jump=false;
};
enum OpcodeTypes {LW=0x23,SW=0x2B,BEQ=0x4,J=0x2,ADDI=0x8,BNE=0x5};