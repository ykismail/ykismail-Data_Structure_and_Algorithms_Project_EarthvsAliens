#pragma once


#ifndef EARTHARMY
#define EARTHARMY

#include "ESQueue.h"
#include "ETStack.h"
#include "EGPriQueue.h"
#include "HUStack.h"
#include "Game.h"
#include "RandomGen.h"
	extern bool SilentMode;
	class AlienArmy;
class EarthArmy
{
protected:
	ESQueue ESList;
	ETStack ETList;
	EGPriQueue EGList;
	HUStack HUList;
	int AliveEUnits = 0;
	int totalunits = 0;
	int totalESCount = 0;
	int totalETCount = 0;
	int totalEGCount = 0;
	int totalHUCount = 0;
	int totalhealedunits = 0;
	int totalDfA=0;
	int totalDbA=0;
	int totalDdA=0;
public:
	EarthArmy();
	//void AddSoldier(Earth_Soldier* ES);
	void GenerateEUnits(int NoArmyUnits, int ESPerc, int ETPerc, int EGPerc, int HUPerc, int EH1, int EH2, int EP1, int EP2, int EAC1, int EAC2, int Tj);
	bool CheckEarthIDs(int id);
	int getAliveEUnits();
	ESQueue& getESList();
	ETStack& getETList();
	EGPriQueue& getEGList();
	HUStack& getHUList();
	void print();
	void Heal(Game* G1,int t);
	int gettotalEunits();
	void DecAliveEUnits();
	void ATTACK(AlienArmy& AA, Game* G1, int ts);
	int gettotalESCount();
	int gettotalETCount();
	int gettotalEGCount();
	int gettotalHUCount();
	int gettotalhealedunits();
	int gettotalDf();
	int gettotalDb();
	int gettotalDd();
};

#endif
