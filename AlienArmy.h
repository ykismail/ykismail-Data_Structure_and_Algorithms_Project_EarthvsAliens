#pragma once

#ifndef ALIENARMY
#define ALIENARMY


#include "ADSPECIALQ.h"
#include "ASQueue.h"
#include "AMArray.h"
#include "RandomGen.h"
	extern bool SilentMode;
	class EarthArmy;
	class Game;
class AlienArmy
{
private:
	ASQueue ASList;
	AMArray AMList;
	ADSPECIALQ ADList;
	int AliveAUnits = 0;
	int droneFlag = 1;
	int totalunits = 0;
	int totalASCount = 0;
	int totalAMCount = 0;
	int totalADCount = 0;
	int totalDfE = 0;
	int totalDbE = 0;
	int totalDdE = 0;
public:
	AlienArmy();
	//void AddSoldier(Earth_Soldier* ES);
	void GenerateAUnits(int NoArmyUnits, int ASPerc, int AMPerc, int ADPerc, int AH1, int AH2, int AP1, int AP2, int AAC1, int AAC2,int t);
	bool CheckAlienIDs(int id);
	int getAliveAUnits();
	ASQueue& getASList();
	AMArray& getAMList();
	ADSPECIALQ& getADList();
	void print();
	int gettotalAunits();
	void ATTACK(EarthArmy& EA, Game* G1, int ts);
	void DecAliveAUnits();
	int gettotalASCount();
	int gettotalAMCount();
	int gettotalADCount();
	int gettotalDf();
	int gettotalDb();
	int gettotalDd();
};

#endif


