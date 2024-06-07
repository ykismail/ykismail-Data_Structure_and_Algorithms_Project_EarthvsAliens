#ifndef ADSPECIAL
#define ADSPECIAL
#include "LinkedQueue.h"
#include "Alien_Drones.h"
extern bool SilentMode;
class ADSPECIALQ : public LinkedQueue<Alien_Drones*>
{
protected:
	int ADCount = 0;

public:
	ADSPECIALQ();
	bool AddUnitfirst(int id, int health, int power, int attackcap);
	bool AddUnitfirst(Alien_Drones* AD);
	bool AddUnitlast(int id, int health, int power, int attackcap);
	bool AddUnitlast(Alien_Drones* AD);
	Alien_Drones* PickUnitfirst();
	Alien_Drones* PickUnitlast();
	int GetCount()const;
	void PrintAll();
	bool CheckID(int id);
};
#endif

