
#include "AMArray.h"
#include "PrintControl.h"
#pragma once

void AMArray::AddUnit(int id, int health, int power, int attackcap) {
	Alien_Monster* AM;
	AM = new Alien_Monster(id, health, power, attackcap);

	if (AMCount < MAXSIZE)
	{
		Array[AMCount] = AM;
		AMCount++;
	} else { 
		std ::cout << "ERROR";
		return;
	
	}
}
void AMArray::AddUnit(Alien_Monster* AM) {
	if (AM == nullptr)
	{
		 MY_COUT( "NULL ELEMENT! Couldn't add.\n");
		return;
	}
	else { 
		Array[AMCount] = AM;
		AMCount++;
	}
}
int AMArray::GetCount() const{
	return AMCount;
}
Alien_Monster* AMArray::PickUnit(int index) {
	if (index < 0 || index >= AMCount)
	{
		//// MY_COUT( "Monster picked is outside the range!\n");
		return nullptr;
	}
	Alien_Monster* AM;
	AM = Array[index];
	Array[index] = Array[AMCount - 1];
	AMCount--;
	//// MY_COUT( AM->GetID() << std::endl);
	return AM;
}
void AMArray::PrintAll() {  
	
	for (int i = 0; i < AMCount; i++) {
		Alien_Monster* P; 
		P = Array[i]; 
		if (i+1==AMCount) {
			 MY_COUT( P->GetID());
		}
		else {
			 MY_COUT( P->GetID() << ", ");
		}
	}

}
bool AMArray::CheckID(int id) {
	for (int i = 0; i < AMCount; i++) {
		Alien_Monster* P=Array[i];
		if (P->GetID() == id) { return false; }
	}
	return true;
}