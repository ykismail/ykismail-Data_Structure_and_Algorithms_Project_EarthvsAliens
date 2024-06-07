
#include "ASQueue.h"
#include"PrintControl.h"
#pragma once

ASQueue::ASQueue() {}
bool ASQueue::AddUnit(int id, int health, int power, int attackcap) {
	Alien_Soldier* AS;
	AS = new Alien_Soldier(id, health, power, attackcap);
	ASCount++;
	return this->enqueue(AS);
}
bool ASQueue::AddUnit(Alien_Soldier* AS) {
	ASCount++;
	return this->enqueue(AS);
}
int ASQueue::GetCount() const {
	return ASCount;
}
Alien_Soldier* ASQueue::PickUnit() {
	if (!isEmpty()) {
		Alien_Soldier* AS;
		this->dequeue(AS);
		ASCount--;
		//// MY_COUT( AS->GetID() << std::endl);
		return AS;
	}
	/*else {
		 MY_COUT( "Alien Soldiers queue is empty!\n");
	}*/
}
void ASQueue::PrintAll() {
	
	Node<Alien_Soldier*>* P;
	P = this->GetfrontPtr();
	
	while (P != nullptr) {
		if (P->getNext() == nullptr) {
			 MY_COUT( P->getItem()->GetID());
			P = P->getNext();
		}
		else {
			 MY_COUT( P->getItem()->GetID() << ", ");
			P = P->getNext();
		}
	}
	
}
int ASQueue::picktoattack(Alien_Soldier* as) {
	
	return as->getAttckCap();


}
bool ASQueue::CheckID(int id) {
	Node<Alien_Soldier*>* P = this->GetfrontPtr();
	while (P != nullptr) {
		if (P->getItem()->GetID() == id) {
			return false;
		}
		P = P->getNext();
	}
	return true;
}