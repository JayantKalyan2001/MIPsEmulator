#pragma once
class Register
{
public:
	const int zero = 0;
	int readReg1=8, readReg2=8, writeReg=0,readData1=0,readData2=0;
	int Temporaries[8] = {0};
	int SavedTemporaries[8] = {0};
	int Temporaries2[2] = { 0 };
	int readFromRegister(int regNo);
	void writeToRegister(int regNo,int writeData);
};

