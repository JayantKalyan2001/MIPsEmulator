#include "Tokeniser.h"

std::vector<std::vector<std::string>> Tokeniser::stringtokenReader()
{
	std::vector<std::vector<std::string>> output;
	std::string MIPs_Instruc;
	std::fstream  ShowcaseFile;
	ShowcaseFile.open("Text.txt", std::ios::in);
	while (std::getline(ShowcaseFile, MIPs_Instruc))
	{
		std::vector<std::string> tempElement = {};
		std::stringstream stream(MIPs_Instruc);
		std::string temp;
		std::getline(stream, temp, ' ');
		tempElement.push_back(temp);
		int pos = MIPs_Instruc.find_first_of(' ') + 1;
		std::string NoCmd = MIPs_Instruc.substr(pos);
		std::stringstream tempStream(NoCmd);
		if (temp=="lw"||temp=="sw")
		{
			std::getline(tempStream, temp, ',');
			tempElement.push_back(temp);
			tempStream.clear();
			pos= NoCmd.find_first_of(',') + 1;
			NoCmd = NoCmd.substr(pos);
			tempStream.str(NoCmd);
			std::getline(tempStream, temp, '(');
			tempElement.push_back(temp);
			pos = NoCmd.find_first_of('(') + 1;
			NoCmd = NoCmd.substr(pos);
			tempStream.str(NoCmd);
			std::getline(tempStream, temp, ')');
			tempElement.push_back(temp);
			output.push_back(tempElement);
			continue;
		}
		while (std::getline(tempStream, temp, ','))
		{
			tempElement.push_back(temp);
		}
		output.push_back(tempElement);
	}
	ShowcaseFile.close();
	return output;
}