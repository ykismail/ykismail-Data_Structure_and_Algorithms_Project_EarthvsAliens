#ifndef HUSTACK
#define HUSTACK
#include "ArrayStack.h"
#include "Heal_Unit.h"
#pragma once
extern bool SilentMode;
class HUStack:ArrayStack<Heal_Unit*>
{ protected:
	int HUCount;
	
public:
	bool AddUnit(int id, int health,int power, int attackcap);
	bool AddUnit(Heal_Unit* HU);
	Heal_Unit* PickUnit();
	int GetCount();
	bool CheckID(int id);
	void PrintAll();
};

#endif