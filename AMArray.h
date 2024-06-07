#ifndef AMARRAY
#define AMARRAY
#include "ArrayofPointers.h"
#include "Alien_Monsters.h"
	extern bool SilentMode;

class AMArray:public ArrayofPointers<Alien_Monster*>
{ protected:
	int AMCount = 0;

public:
	void AddUnit(int id, int health, int power, int attackcap);
	void AddUnit(Alien_Monster* AM);
	Alien_Monster* PickUnit(int index);
	void PrintAll();
	int GetCount()const;
	bool CheckID(int id);
};

#endif