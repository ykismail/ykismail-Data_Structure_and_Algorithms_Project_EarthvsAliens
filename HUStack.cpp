#include "Units.h"
#include "HUStack.h"
#include "PrintControl.h"
#pragma once

bool HUStack::AddUnit(int id, int health, int power, int attackcap) {
	Heal_Unit* HU = new Heal_Unit(id, health, power, attackcap);
	HUCount++;
	return this->push(HU);
}
bool HUStack::AddUnit(Heal_Unit* HU) {
	HUCount++;
	return this->push(HU);
}
int  HUStack::GetCount() {
	return HUCount;
}
bool HUStack::CheckID(int id) {
	int P = 0;
	while (P < HUCount) {
		if (items[P]->GetID() == id) { return false; }
		P++;
	}
	return true;
}
void HUStack::PrintAll() {
	int P = 0;
	 MY_COUT( HUCount << " HU [");
	while (P < HUCount) {
		if (P + 1 == HUCount) {
			 MY_COUT( items[P]->GetID());
			P++;
		}
		else {
			 MY_COUT( items[P]->GetID() << ", ");
			P++;
		}
	}
	 MY_COUT( "]" << std::endl);
}
Heal_Unit* HUStack::PickUnit() {
	if (!isEmpty()) {
		Heal_Unit* HU;
		this->pop(HU);
		HUCount--;
	////	 MY_COUT( HU->GetID() << std::endl);
		return HU;
	}
	/*else {
		 MY_COUT( "Heal Units stack is empty!\n");
	}*/
}