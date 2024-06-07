
#include "ADSPECIALQ.h"
#include "PrintControl.h"
#pragma once

	 ADSPECIALQ :: ADSPECIALQ(){}
bool ADSPECIALQ::AddUnitfirst(int id, int health, int power, int attackcap) {
	Alien_Drones* AD;
	AD = new Alien_Drones(id, health, power, attackcap);
	ADCount++;
		Node<Alien_Drones*>* newNodePtr = new Node<Alien_Drones*>(AD);
		// Insert the new node
		if (isEmpty())	//special case if this is the first node to insert
			backPtr = newNodePtr; // The queue is empty
		else
			newNodePtr->setNext(frontPtr); // The queue was not empty

		frontPtr = newNodePtr; // New node is the first node now
		return true;
	
}
bool ADSPECIALQ::AddUnitfirst(Alien_Drones* AD) {
	ADCount++;
	Node<Alien_Drones*>* newNodePtr = new Node<Alien_Drones*>(AD); 
	// Insert the new node
	if (isEmpty())	//special case if this is the first node to insert 
		frontPtr=backPtr = newNodePtr; // The queue is empty 
	else {
		newNodePtr->setNext(frontPtr); // The queue was not empty 

		frontPtr = newNodePtr; // New node is the first node now 
	}
	return true;
}
bool ADSPECIALQ::AddUnitlast(int id, int health, int power, int attackcap) {
	Alien_Drones* AD;
	AD = new Alien_Drones(id, health, power, attackcap);
	ADCount++;
	return this->enqueue(AD);

}
bool ADSPECIALQ::AddUnitlast(Alien_Drones* AD) {
	ADCount++;
	return enqueue(AD);
}
Alien_Drones* ADSPECIALQ::PickUnitfirst() {
	if (!isEmpty())
	{
		Alien_Drones* AD;
		Node<Alien_Drones*>* P;
		P = this->GetfrontPtr();
		AD = P->getItem();
		ADCount--;
		this->dequeue(AD);
	////	 MY_COUT( AD->GetID() << std::endl);
		return AD;
	}
	/*else {
		 MY_COUT( "Alien Drone queue is empty!\n");
	}*/

}
Alien_Drones* ADSPECIALQ::PickUnitlast() {

	if (!isEmpty()) {
		Node<Alien_Drones*>* currentNode = GetfrontPtr();
		Node<Alien_Drones*>* prevNode = NULL;

		while (currentNode->getNext() != NULL) //traverse to reach last element
		{
			prevNode = currentNode;
			currentNode = currentNode->getNext();
		}
		//after while loop, currentNode heya el last element
		Alien_Drones* AD = currentNode->getItem();

		if (frontPtr == backPtr) //only 1 element in array to delete
		{
			frontPtr = backPtr = NULL;
		}
		else {
			backPtr = prevNode; //update backPtr lel node el abl el akhera	
			backPtr->setNext(NULL); //set next of akher element be null 
		}

		delete currentNode;
		ADCount--;
		return AD;
	}
	/*else {
		 MY_COUT( "Alien Drones queue is empty!\n");
	}*/

}

int ADSPECIALQ::GetCount()const { 
	return ADCount;
}

void ADSPECIALQ::PrintAll() {
	
	Node<Alien_Drones*>* P;
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
bool ADSPECIALQ::CheckID(int id) {
	Node<Alien_Drones*>* P = this->GetfrontPtr();
	while (P != nullptr) {
		if (P->getItem()->GetID() == id) {
			return false;
		}
		P = P->getNext();
	}
	return true;
}