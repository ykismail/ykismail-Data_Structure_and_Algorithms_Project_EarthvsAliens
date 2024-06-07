#include <iostream>
//#include "Node.h"
#include "LinkedQueue.h"
//#include "priNode.h"
#include "priQueue.h"
#include "Units.h"
#include "Earth_Soldiers.h"
#include "Earth_Tank.h"
//#include "Earth_Gunners.h"
#include "AlienArmy.h"
#include "EarthArmy.h"
#include "RandomGen.h"
#include "Game.h"
#include "PrintControl.h"

#pragma once
Game::Game() {
	KilledList = new LinkedQueue<Units*>;
	UnitsFightingList = new LinkedQueue<Units*>;
	UnitsTempList = new priQueue<Units>;
	UnitsMaintenanceList = new priQueue<Units>;
	ESMaintenanceList = new priQueue<Earth_Soldier>;
	ETMaintenanceList = new LinkedQueue<Earth_Tank*>;
	EHCum = 1;
	AHCum = 1;
	int EarthIDs[1000];
	int EIDCounter = 0;
	int AlienIDs[1000];
	int AIDCounter = 0;


	int ESShot[1000]; //IDs of units shot by ES
	int ETShot[1000]; //IDs of units shot by ET
	int EGShot[1000]; //IDs of units shot by EG

	int ASShot[1000]; //IDs of units shot by AS
	int AMShot[1000]; //IDs of units shot by AM
	int ADShot[1000]; //IDs of units shot by AD

	
}
LinkedQueue<Units*>* Game::GetKilledList() {
	return KilledList;
}
LinkedQueue<Units*>* Game::GetUnitsFightingList() {
	return UnitsFightingList;
}
priQueue<Units>* Game::GetUnitsMaintenanceList() {
	return UnitsMaintenanceList;
}
bool Game::AddtoKilledList(Units* unit,int Td) {
	KilledCount++;
	unit->setTd(Td);
	unit->setDb(Td - unit->getTj());
	unit->setDd(Td - unit->getTa());
	return KilledList->enqueue(unit);
}
bool Game::AddtoUnitsFightingList(Units* attackingunit) {
	UnitsFightingCount++;
	return UnitsFightingList->enqueue(attackingunit);
}
void Game::AddtoUnitsMaintenanceList(Units* unit,int timestep) {
	UMLCount++;
	unit->setTUML(timestep);
	UnitsMaintenanceList->enqueue(unit, 0);
}
void Game::AddtoTempList(Units* unit,int pri) {
	UnitsTempList->enqueue(unit,0);
}
void Game::AddtoTempList(Earth_Soldier* ES) {
	AddtoTempList(ES, 100 - ES->GetHealth());
}
void Game::AddtoTempList(Earth_Tank* ET) {
	AddtoTempList(ET, 0);
}
void Game::AddtoUnitsMaintenanceList(Earth_Soldier* ES,int timestep) {
	UMLCount++;
	ES->setTUML(timestep);
	AddtoESMaintenanceList(ES,timestep);
	UnitsMaintenanceList->enqueue(ES, 100 - ES->GetHealth());
}
void Game::AddtoUnitsMaintenanceList(Earth_Tank* ET,int timestep) {
	UMLCount++;
	AddtoETMaintenanceList(ET,timestep);
	ET->setTUML(timestep);
	UnitsMaintenanceList->enqueue(ET, 0);
}
void Game::AddtoESMaintenanceList(Earth_Soldier* ES,int timestep) {
	ESMLCount++;
	ES->setTUML(timestep);
	ESMaintenanceList->enqueue(ES, 100 - ES->GetHealth());
}
void Game::AddtoETMaintenanceList(Earth_Tank* ET,int timestep) {
	ETMLCount++;
	ET->setTUML(timestep);
	ETMaintenanceList->enqueue(ET);
}
void Game::MovefromTemptoUML(int timestep) {
	if (!UnitsTempList->isEmpty()) {
		Units* unit;
		unit = removefromTempList();
		AddtoUnitsMaintenanceList(unit,timestep);
		if (UnitsTempList->Gethead() != nullptr) {
			MovefromTemptoUML(timestep);
		}
	}
}
Units* Game::removefromUFL() {
	Units* unit;
	UnitsFightingCount--;
	UnitsFightingList->dequeue(unit);
	return unit;
}
bool Game::removefromUML() {
	if (UnitsMaintenanceList->isEmpty()) {
		return false;
	}
	else {
		Units* unit = UnitsMaintenanceList->Gethead()->getItem();
		UMLCount--;
		UnitsMaintenanceList->dequeue(unit, unit->GetHealth());
		return true;
	}
}
Units* Game::removefromTempList() {
	if (!UnitsTempList->isEmpty()) {
		Units* unit = UnitsTempList->Gethead()->getItem();
		UnitsTempList->dequeue(unit,0);
		return unit;
	}
	/*else {
		 MY_COUT( "No Units in Temp List!\n");
	}*/
}
Earth_Soldier* Game::removefromESUML() {
	Earth_Soldier* ES = ESMaintenanceList->Gethead()->getItem();
	ESMLCount--;
	removefromUML();
	ESMaintenanceList->dequeue(ES, ES->GetHealth());
	return ES;
}
Earth_Tank* Game::removefromETUML() {
	if (!ETMaintenanceList->isEmpty()) {
		Earth_Tank* ET = ETMaintenanceList->GetfrontPtr()->getItem();
		ETMLCount--;
		removefromUML();
		ETMaintenanceList->dequeue(ET);
		return ET;
	}
	//// else MY_COUT( "No Units in UML!\n");
}
Units* Game::removefromkilledlist()
{
	if (!KilledList->isEmpty()) {
		Units* unit = KilledList->GetfrontPtr()->getItem();
		KilledCount--;
		KilledList->dequeue(unit);
		return unit;
	}
	//// else MY_COUT("No units in killed list!\n");
}
void Game::ClearUnitsFightingList()
{
	UnitsFightingCount = 0;
	Units* unit;
	while (UnitsFightingList->dequeue(unit));
}
void Game::PrintKilledList() {
	if (!(KilledList->isEmpty()))
	{
		Node<Units*>* P;
		P = KilledList->GetfrontPtr();
		MY_COUT(KilledCount << " Killed/Destructed Units [");
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
		MY_COUT("]" << std::endl);
	}
	else {
		 MY_COUT( "0 Killed/Destructed Units []" << std::endl);
	}
}
void Game::PrintUnitsFightingList() {
	if (!(UnitsFightingList->isEmpty())) {
		Node<Units*>* P;
		P = UnitsFightingList->GetfrontPtr();
		 MY_COUT( UnitsFightingCount << " Fighting Units [");
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
		MY_COUT("]\n");
	}
	else MY_COUT( "0 Units Fighting []\n");
}
void Game::PrintUnitsMaintenanceList() {
	priNode<Units>* P;
	P = UnitsMaintenanceList->Gethead();
	 MY_COUT( UMLCount << " Units Needing maintenance [");
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
	 MY_COUT( "]" << std::endl);
}
int Game::getEHCum()
{
	return EHCum;
}

int Game::getAHCum()
{
	return AHCum;
}

int Game::getEIDCounter()
{
	return EIDCounter;
}

int Game::getAIDCounter()
{
	return AIDCounter;
}
void Game::RunRound() {

}

priQueue<Earth_Soldier>* Game::GetESMaintenanceList()
{
	return ESMaintenanceList;
}

LinkedQueue<Earth_Tank*>* Game::GetETMaintenanceList()
{
	return ETMaintenanceList;
}
int Game::getASDCount()
{
	return this->destructedASCount;
}
int Game::getAMDCount()
{
	return this->destructedAMCount;
}
int Game::getADDCount()
{
	return this->destructedADCount;
}
int Game::getESDCount()
{
	return this->destructedESCount;
}

int Game::getETDCount()
{
	return this->destructedETCount;
}

int Game::getEGDCount()
{
	return this->destructedEGCount;
}

int Game::getHUDCount()
{
	return this->destructedHUCount;
}

void Game::setASDCount(int d)
{
	destructedASCount = d;
}

void Game::setAMDCount(int d)
{
	destructedAMCount = d;
}

void Game::setADDCount(int d)
{
	destructedADCount = d;
}

void Game::setESDCount(int d)
{
	destructedESCount = d;
}

void Game::setETDCount(int d)
{
	destructedETCount = d;
}

void Game::setEGDCount(int d)
{
	destructedEGCount = d;
}

void Game::setHUDCount(int d)
{
	destructedHUCount = d;
}