#ifndef EARTH_GUNNERS
#define EARTH_GUNNERS

#include "Units.h"

class Earth_Gunner:public Units
{
public:
	Earth_Gunner();
	Earth_Gunner(int id, int health, int power, int attackcap);
	float getPri()const;
	int GetHealth();
	int GetID();
	void setID(int id);
	void setHealth(int health);
	void setPower(int power);
	void setAttackCap(int AC);
};

#endif