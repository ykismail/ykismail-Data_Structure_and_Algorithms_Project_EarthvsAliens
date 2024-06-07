#ifndef ESQUEUE
#define ESQUEUE
#include "LinkedQueue.h"
#include "Earth_Soldiers.h"
#pragma once
extern bool SilentMode;

class ESQueue:public LinkedQueue<Earth_Soldier*>
{ protected:
	int ESCount=0;
public:
	ESQueue();
	bool AddUnit(int id, int health, int power, int attackcap);
	bool AddUnit(Earth_Soldier* ES);
	int GetCount()const;
	void PrintAll();
	Earth_Soldier* PickUnit();
	bool CheckID(int id);
};

#endif

