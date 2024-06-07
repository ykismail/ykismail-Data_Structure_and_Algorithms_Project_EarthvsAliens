#ifndef ETSTACK
#define ETSTACK
#include "ArrayStack.h"
#include "Earth_Tank.h"
extern bool SilentMode;
class ETStack:ArrayStack<Earth_Tank*>
{ protected:
	int ETCount=0;
		public:
			bool AddUnit(int id, int health, int power, int attackcap);
			bool AddUnit(Earth_Tank* ET);
			int GetCount()const;
			void PrintAll();
			Earth_Tank* PickUnit();
			bool CheckID(int id);
};
#endif