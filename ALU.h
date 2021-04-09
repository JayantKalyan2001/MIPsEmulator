#pragma once
class ALU
{
public:
	bool zero=false ;
	int output;
	ALU(int funct,int A, int secondInput, bool Op0, bool Op1);
	void ALUreset();
};

