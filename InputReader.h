#ifndef INPUTREADER
#define INPUTREADER
#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include "BattleInfo.h"
#include <sstream>
#include <iomanip>


class InputReader
{


public:
	InputReader() {};

	BattleInfo reader() {
		std::ifstream file("testing.txt");

		BattleInfo obj;
		std::string line;
		int linecount = 0;
		while (std::getline(file, line)) {
			linecount++;
			std::istringstream iss(line);
			if (linecount == 1) {
				int value1;
				iss >> value1;
				obj.setArmyUnits(value1);
			}
			if (linecount == 2) {
				int value2, value3, value4, value10;
				iss >> value2 >> value3 >> value4 >> value10;
				obj.setES(value2);
				obj.setET(value3);
				obj.setEG(value4);
				obj.setHU(value10);
			}
			if (linecount == 3) {
				int value5, value6, value7;
				iss >> value5 >> value6 >> value7;
				obj.setAS(value5);
				obj.setAM(value6);
				obj.setAD(value7);
			}
			if (linecount == 4) {
				int value8;
				iss >> value8;
				obj.setProb(value8);
			}
			if (linecount == 5) {
				EparseRange(line, obj);
			}
			if (linecount == 6) {
				AparseRange(line, obj);
			}
		}
		file.close();
		return obj;
	};

	void EparseRange(string& range, BattleInfo& BI)
	{
		int counter = 0;
		std::istringstream iss(range);
		string token;
		while (iss >> token && counter < 3)
		{
			size_t dashPosition = token.find('-');
			if (dashPosition != std::string::npos)
			{
				int min = stoi(token.substr(0, dashPosition));
				int max = stoi(token.substr(dashPosition + 1));

				switch (counter) {
				case 0: //power
					BI.EP1 = min;
					BI.EP2 = max;
					break;
				case 1: //health
					BI.EH1 = min;
					BI.EH2 = max;
					break;
				case 2: //attack cap
					BI.EAC1 = min;
					BI.EAC2 = max;
					break;
				}
				counter++;
			}
		}
	}

	void AparseRange(string& range, BattleInfo& BI)
	{
		int counter = 0;
		std::istringstream iss(range);
		string token;
		while (iss >> token && counter < 3)
		{
			size_t dashPosition = token.find('-');
			if (dashPosition != std::string::npos)
			{
				int min = stoi(token.substr(0, dashPosition));
				int max = stoi(token.substr(dashPosition + 1));

				switch (counter) {
				case 0: //power
					BI.AP1 = min;
					BI.AP2 = max;
					break;
				case 1: //health
					BI.AH1 = min;
					BI.AH2 = max;
					break;
				case 2: //attack cap
					BI.AAC1 = min;
					BI.AAC2 = max;
					break;
				}
				counter++;
			}
		}
	}

	~InputReader() {};
};

#endif