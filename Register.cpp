#include "Register.h"
#include <iostream>
#include <map>
int Register::readFromRegister(int regNo)
{
	int readValue;
	std::map<unsigned int, unsigned int> reg;

#pragma region zero
	reg.insert(std::pair<unsigned int, unsigned int>(0, zero));
#pragma endregion
#pragma region t
	reg.insert(std::pair<unsigned int, unsigned int>(8, Temporaries[0]));
	reg.insert(std::pair<unsigned int, unsigned int>(9, Temporaries[1]));
	reg.insert(std::pair<unsigned int, unsigned int>(10, Temporaries[2]));
	reg.insert(std::pair<unsigned int, unsigned int>(11, Temporaries[3]));
	reg.insert(std::pair<unsigned int, unsigned int>(12, Temporaries[4]));
	reg.insert(std::pair<unsigned int, unsigned int>(13, Temporaries[5]));
	reg.insert(std::pair<unsigned int, unsigned int>(14, Temporaries[6]));
	reg.insert(std::pair<unsigned int, unsigned int>(15, Temporaries[7]));
#pragma endregion

#pragma region s
	reg.insert(std::pair<unsigned int, unsigned int>(16, SavedTemporaries[0]));
	reg.insert(std::pair<unsigned int, unsigned int>(17, SavedTemporaries[1]));
	reg.insert(std::pair<unsigned int, unsigned int>(18, SavedTemporaries[2]));
	reg.insert(std::pair<unsigned int, unsigned int>(19, SavedTemporaries[3]));
	reg.insert(std::pair<unsigned int, unsigned int>(20, SavedTemporaries[4]));
	reg.insert(std::pair<unsigned int, unsigned int>(21, SavedTemporaries[5]));
	reg.insert(std::pair<unsigned int, unsigned int>(22, SavedTemporaries[6]));
	reg.insert(std::pair<unsigned int, unsigned int>(23, SavedTemporaries[7]));
#pragma endregion

#pragma region t2
	reg.insert(std::pair<unsigned int, unsigned int>(24, Temporaries2[0]));
	reg.insert(std::pair<unsigned int, unsigned int>(25, Temporaries2[1]));
#pragma endregion
	
	readValue = reg.at(regNo);
	return readValue;
}
void Register::writeToRegister(int regNo,int writeData)
{
	if (!regNo)
	{
		std::cout << "cannot write in reserved $zero register "<<"\n";
	}
	if (regNo>=8 && regNo<=15)
	{
		Temporaries[regNo - 8] = writeData;
	}
	else if(regNo>=16 && regNo<=23)
	{
		SavedTemporaries[regNo - 16] = writeData;
	}
	else if (regNo==24||regNo==25)
	{
		Temporaries2[regNo - 24] = writeData;
	}
}