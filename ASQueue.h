#ifndef ASQUEUE
#define ASQUEUE
#include "LinkedQueue.h"
#include "Alien_Soldier.h"
	extern bool SilentMode;

class ASQueue: public LinkedQueue<Alien_Soldier*>
{ protected:
	int ASCount = 0,KilledASCount=0;
public:
	ASQueue();
	//ASQueue(int id, int health, int power, int attackcap);
	bool AddUnit(int id,int health,int power,int attackcap);
	bool AddUnit(Alien_Soldier* AS);
	Alien_Soldier* PickUnit();
	int GetCount()const;
	void PrintAll();
	bool CheckID(int id);
	int  picktoattack(Alien_Soldier*); 
};
#endif