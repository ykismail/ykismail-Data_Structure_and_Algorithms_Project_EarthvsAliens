#ifndef ALIENMONSTERS
#define ALIENMONSTERS

#include "Units.h"

class Alien_Monster: public Units
{ 
public:
	Alien_Monster();
	Alien_Monster(int id,int health,int power,int attackcap);
	int GetHealth();
	int GetID();
	void setID(int id);
	void setHealth(int health);
	void setPower(int power);
	void setAttackCap(int AC);
};
#endif
