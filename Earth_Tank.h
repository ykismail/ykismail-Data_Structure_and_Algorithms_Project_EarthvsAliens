#ifndef EARTH_TANK
#define EARTH_TANK
#include "Units.h"
class Earth_Tank:public Units
{ 
public:
	Earth_Tank();
	Earth_Tank(int id, int health, int power, int attackcap);
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
