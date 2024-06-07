
#include "EGPriQueue.h"
#include "PrintControl.h"
#pragma once
EGPriQueue::EGPriQueue() {}
void EGPriQueue::AddUnit(int id, int health, int power, int attackcap) {
	Earth_Gunner* EG;
	EG= new Earth_Gunner(id, health, power, attackcap);
	int pri = EG->getPri();
	EGCount++;
	this->enqueue(EG, pri);
}
void EGPriQueue::AddUnit(Earth_Gunner* EG) {
	EGCount++;
	this->enqueue(EG, EG->getPri());
}
int EGPriQueue::GetCount()const {
	return EGCount;
}
Earth_Gunner* EGPriQueue::PickUnit() {
	if (!isEmpty()) {
		Earth_Gunner* EG;
		priNode<Earth_Gunner>* P;
		P = this->Gethead();
		EG = P->getItem();
		this->dequeue(EG, EG->getPri());
		EGCount--;
		//// MY_COUT( EG->GetID() << std::endl);
		return EG;
	}
	/*else {
		 MY_COUT( "Earth Gunners queue is Empty!\n");
	}*/
}
void EGPriQueue::PrintAll() {
	
	priNode<Earth_Gunner>* P;
	P = this->Gethead();
	
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
bool EGPriQueue::CheckID(int id) {
	priNode<Earth_Gunner>* P = this->Gethead();
	while (P != nullptr) {
		if (P->getItem()->GetID() == id) {
			return false;
		}
		P = P->getNext();
	}
	return true;
}