#ifndef EGPRIQUEUE
#define EGPRIQUEUE
#include "priQueue.h"
#include "Earth_Gunners.h"
#pragma once
extern bool SilentMode;

class EGPriQueue:public priQueue<Earth_Gunner>
{	protected:
	int EGCount=0;
 public:
	 EGPriQueue();
	void AddUnit(int id, int health, int power, int attackcap);
	void AddUnit(Earth_Gunner* EG);
	int GetCount()const;
	void PrintAll();
	Earth_Gunner* PickUnit();
	bool CheckID(int id);
};

#endif