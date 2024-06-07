
#include "ESQueue.h"
#include "PrintControl.h"
#pragma once
ESQueue::ESQueue() {}
bool ESQueue::AddUnit(int id, int health, int power, int attackcap) {
		Earth_Soldier* ES;
		ES = new Earth_Soldier(id, health, power, attackcap);
		ESCount++;
		return this->enqueue(ES);
}
bool ESQueue::AddUnit(Earth_Soldier* ES) {
	ESCount++;
	return this->enqueue(ES);
}
int ESQueue::GetCount() const{

	return ESCount;
}
Earth_Soldier* ESQueue::PickUnit() {
	if (!isEmpty())
	{
		Earth_Soldier* ES;
		this->dequeue(ES);
		ESCount--;
	////	 MY_COUT( ES->GetID() << std::endl);
		return ES;
	}
	/*else {
		 MY_COUT( "Earth Soldiers queue is empty!\n");
	}*/
}
void ESQueue::PrintAll() {
	
	Node<Earth_Soldier*>* P;
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
bool ESQueue::CheckID(int id) {
	Node<Earth_Soldier*>* P = this->GetfrontPtr();
	while (P != nullptr) {
		if (P->getItem()->GetID() == id) {
			return false;
		}
		P = P->getNext();
	}
	return true;
}

