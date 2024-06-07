#ifndef EARTH_SOLDIER
#define EARTH_SOLDIER
#include "Units.h"

class Earth_Soldier : public Units
{
public:
	Earth_Soldier();
	Earth_Soldier(int id, int health, int power, int attackcap);
	int GetHealth();
	int GetOriginalHealth();
	int GetID();
	void setID(int id);
	void setHealth(int health);
	void setOriginalHealth(int health);
	void setPower(int power);
	void setAttackCap(int AC);
};
#endif

