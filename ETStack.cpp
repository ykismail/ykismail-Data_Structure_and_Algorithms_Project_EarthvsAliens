
#include "ETStack.h"
#include"PrintControl.h"
#pragma once

bool ETStack::AddUnit(int id, int health, int power, int attackcap) {
	Earth_Tank* ET;
	ET = new Earth_Tank(id, health, power, attackcap);
	ETCount++;
	return this->push(ET);
}
bool ETStack::AddUnit(Earth_Tank* ET) { 
	ETCount++; 
	return this->push(ET);
}
Earth_Tank* ETStack::PickUnit() {
	if (!isEmpty()) {
		Earth_Tank* ET;
		this->pop(ET);
		ETCount--;
		//// MY_COUT( ET->GetID() << std::endl);
		return ET;
	}
	//else {
	//	 MY_COUT( "Earth Tanks stack is empty!\n");
	//}
}

int ETStack::GetCount() const{
	return ETCount;
}
void ETStack::PrintAll() {
	int P=0;
	
	while (P <ETCount){
		if (P + 1 == ETCount) {
			 MY_COUT( items[P]->GetID());
			P++;
		}
		else {
			 MY_COUT( items[P]->GetID() << ", ");
			P++;
		}
	}
	
}
bool ETStack::CheckID(int id) {
	int P = 0;
	while (P < ETCount) {
		if (items[P]->GetID() == id) { return false; }
		P++;
	}
	return true;
}