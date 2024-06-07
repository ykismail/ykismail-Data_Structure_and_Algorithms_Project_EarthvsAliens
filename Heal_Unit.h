#ifndef HEALUNIT
#define HEALUNIT
#include "Units.h"
#pragma once
class Heal_Unit:public Units
{ public:
	Heal_Unit();
	Heal_Unit(int id,int health, int power,int attackcap);
	int GetID();
	void HealUnit(Units* unit);
	void setID(int id);
	void setHealth(int health);
	void setPower(int power);
	void setAttackCap(int AC);
};

#endif