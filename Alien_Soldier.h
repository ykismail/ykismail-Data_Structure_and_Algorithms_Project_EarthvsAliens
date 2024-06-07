#ifndef ALIENSOLDIER
#define ALIENSOLDIER

#include "Units.h"

class Alien_Soldier: public Units
{ protected:
	int ASCount = 0;
public:
	Alien_Soldier();
	Alien_Soldier(int id,int health,int power, int attackcap);
	int GetHealth();
	int GetID(); 
	void setID(int id);
	void setHealth(int health);
	void setPower(int power);
	void setAttackCap(int AC);
	
};

#endif