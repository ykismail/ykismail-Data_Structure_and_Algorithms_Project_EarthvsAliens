#include "AlienArmy.h"
#include "EarthArmy.h"
#include "Units.h"
#include"PrintControl.h"
#include <iostream>
//class ESQueue;


#pragma once


AlienArmy::AlienArmy() {};

void AlienArmy::GenerateAUnits(int NoArmyUnits, int ASPerc, int AMPerc, int ADPerc, int AH1, int AH2, int AP1, int AP2, int AAC1, int AAC2,int timestep) {
	RandomGen rg;
	for (int i = 0; i < NoArmyUnits; i++) {
		int B = rg.generateRandProb();
		//// MY_COUT( "B = " << B << endl);
		if (B <= ASPerc) {
			Alien_Soldier* AS = new Alien_Soldier;
			int id = rg.generateAID();
			while (!(this->CheckAlienIDs(id))) { id = rg.generateAID(); }
			AS->setID(id);
			AS->setHealth(rg.generateWithinRange(AH1, AH2));
			AS->setPower(rg.generateWithinRange(AP1, AP2));
			AS->setAttackCap(rg.generateWithinRange(AAC1, AAC2));
			ASList.AddUnit(AS);
			AS->setTj(timestep);
		////	 MY_COUT( " AS created with ID:" << AS->GetID() << endl);
			AliveAUnits++;
			totalunits++;
			totalASCount++;
		}
		else if ((B > ASPerc) && B <= (100 - ADPerc)) {
			Alien_Monster* AM = new Alien_Monster;
			int id = rg.generateAID();
			while (!(this->CheckAlienIDs(id))) { id = rg.generateAID(); }
			AM->setID(id);
			AM->setHealth(rg.generateWithinRange(AH1, AH2));
			AM->setPower(rg.generateWithinRange(AP1, AP2));
			AM->setAttackCap(rg.generateWithinRange(AAC1, AAC2));
			AMList.AddUnit(AM);
			AM->setTj(timestep);
		////	 MY_COUT( " AM created with ID:" << AM->GetID() << endl);
			AliveAUnits++;
			totalunits++;
			totalAMCount++;
		}
		else {
			Alien_Drones* AD = new Alien_Drones;
			int id = rg.generateAID();
			while (!(this->CheckAlienIDs(id))) { id = rg.generateAID(); }
			AD->setID(id);
			AD->setHealth(rg.generateWithinRange(AH1, AH2));
			AD->setPower(rg.generateWithinRange(AP1, AP2));
			AD->setAttackCap(rg.generateWithinRange(AAC1, AAC2));
			if (droneFlag == 1) {
				ADList.AddUnitfirst(AD);
				AD->setTj(timestep);
				droneFlag++;
			}
			else if (droneFlag == 2) {
				ADList.AddUnitlast(AD);
				AD->setTj(timestep); 
				droneFlag--;
			}
		////	 MY_COUT( " AD created with ID:" << AD->GetID() << endl);
			AliveAUnits++;
			totalunits++;
			totalADCount++;
		}
	}
}

bool AlienArmy::CheckAlienIDs(int id)
{
	if (ASList.CheckID(id) && AMList.CheckID(id) && ADList.CheckID(id))
		return true;
	else
		return false;
}

int AlienArmy::getAliveAUnits() {
	return AliveAUnits;
}

ASQueue& AlienArmy::getASList() {
	return ASList;
}

AMArray& AlienArmy::getAMList() {
	return AMList;
}

ADSPECIALQ& AlienArmy::getADList() {
	return ADList;
}

void AlienArmy::print() {
	MY_COUT( ASList.GetCount() << " AS [");
	ASList.PrintAll();
	MY_COUT( "]"<<endl);
	MY_COUT( AMList.GetCount() << " AM [");
	AMList.PrintAll();
	MY_COUT( "]" << endl);
	MY_COUT(ADList.GetCount() << " AD [");
	ADList.PrintAll();
	MY_COUT( "]" << endl);

}

int AlienArmy::gettotalAunits()
{
	return totalunits;
}
void AlienArmy::ATTACK(EarthArmy& EA, Game* G1, int ts) {

	int c1;
	if (ASList.GetCount()!=0) {
	Alien_Soldier* attcksoldier = ASList.PickUnit();
		c1 = attcksoldier->getAttckCap();

		//ESQueue ESList = EA.getESList();
		LinkedQueue<Earth_Soldier*>* temp = new LinkedQueue<Earth_Soldier*>;
		if (c1 > (EA.getESList()).GetCount())
			c1 = (EA.getESList()).GetCount();

		for (int i = 0; i < c1; i++) {
			if (!(EA.getESList()).isEmpty()) {
				Earth_Soldier* dfndUnit = (EA.getESList()).PickUnit();
				int mult = attcksoldier->getPower() * attcksoldier->GetHealth();
				int root = sqrt(dfndUnit->GetHealth());
				int damage = (mult / 100) * root;
				int health = dfndUnit->GetHealth() - damage;
				dfndUnit->setHealth(health);
				////		MY_COUT(" ES health after hit:" << dfndUnit->GetHealth() << endl);
				temp->enqueue(dfndUnit);
				if (dfndUnit->getTa() == 0) { dfndUnit->setTa(ts); }
				dfndUnit->setDf(dfndUnit->getTa() - dfndUnit->getTj());
			}
		}
		G1->AddtoUnitsFightingList(attcksoldier);
		MY_COUT("AS " << attcksoldier->GetID() << " shot ES [ ");
		Earth_Soldier* ES;
		while (temp->dequeue(ES)) {
			MY_COUT(ES->GetID() << ", ");
			if (ES->GetHealth() <= 0.2 * ES->GetOriginalHealth() && ES->GetHealth()>0) {
				G1->AddtoUnitsMaintenanceList(ES, ts);
			} else if (ES->GetHealth() <= 0) {
				G1->AddtoKilledList(ES, ts);
				totalDbE += ES->getDb();
				totalDfE += ES->getDf();
				totalDdE += ES->getDd();
				EA.DecAliveEUnits();
				G1->setESDCount(G1->getESDCount() + 1);
			}
			else (EA.getESList()).AddUnit(ES);

		}
		MY_COUT("]\n");
		delete temp;
		////	MY_COUT(" Reinsertion of attacking AS unit:" << endl);
		ASList.AddUnit(attcksoldier);
		////	MY_COUT(" Reinsertion of attacking AS unit complete!" << endl);
	}


	RandomGen rg2;
	int AMRand;
	if (AMList.GetCount() > 0) {
		AMRand = rg2.generateWithinRange(0, AMList.GetCount() - 1);

		Alien_Monster* attckMonster = AMList.PickUnit(AMRand);
		int c2 = attckMonster->getAttckCap();

		static int flag = 0;
		if (flag == 0) {
			//ETStack* ETList = EA.getETList();
			LinkedQueue<Earth_Tank*>* temp = new LinkedQueue<Earth_Tank*>;

			if (c2 > (EA.getETList()).GetCount())
				c2 = (EA.getETList()).GetCount();

			for (int i = 0; i < c2; i++) {
				if ((EA.getETList()).GetCount() > 0) {
					Earth_Tank* dfndUnit = (EA.getETList()).PickUnit();
					int mult = attckMonster->getPower() * attckMonster->GetHealth();
					int root = sqrt(dfndUnit->GetHealth());
					int damage = (mult / 100) * root;
					int health = dfndUnit->GetHealth() - damage;
					dfndUnit->setHealth(health);
					////		MY_COUT(" ET health after hit:" << dfndUnit->GetHealth() << endl);
					temp->enqueue(dfndUnit);
					if (dfndUnit->getTa() == 0) { dfndUnit->setTa(ts); }
					dfndUnit->setDf(dfndUnit->getTa() - dfndUnit->getTj());
				}
			}
			G1->AddtoUnitsFightingList(attckMonster);
			MY_COUT("AM " << attckMonster->GetID() << " shot ET [ ");
			Earth_Tank* ET;
			while (temp->dequeue(ET)) {
				MY_COUT(ET->GetID() << ", ");
				if (ET->GetHealth() <= 0.2 * ET->GetOriginalHealth() && ET->GetHealth() > 0) {
					G1->AddtoUnitsMaintenanceList(ET, ts);
					////		MY_COUT("Added to UML!\n"); 
				}	else if (ET->GetHealth() <= 0) {
					G1->AddtoKilledList(ET, ts);
					totalDfE += ET->getDf();
					totalDbE += ET->getDb();
					totalDdE += ET->getDd();
					EA.DecAliveEUnits();
					G1->setETDCount(G1->getETDCount() + 1);
					////			MY_COUT("Added to killed List\n");
				}
				else {
					(EA.getETList()).AddUnit(ET);
					////			MY_COUT("Added to ET List\n");
				}
			}
			MY_COUT("]\n");
			delete temp;
			////	MY_COUT(" Reinsertion of attacking AM unit:" << endl);
			AMList.AddUnit(attckMonster);
			////	MY_COUT(" Reinsertion of attacking AM unit complete!" << endl);
			flag++;
		}
		else if (flag == 1) {
			//EGPriQueue* EGList = EA.getEGList();
			LinkedQueue<Earth_Gunner*>* temp = new LinkedQueue<Earth_Gunner*>;
			if (c2 > (EA.getETList()).GetCount())
				c2 = (EA.getETList()).GetCount();

			for (int i = 0; i < c2; i++) {
				if (!(EA.getEGList()).isEmpty()) {
					Earth_Gunner* dfndUnit = (EA.getEGList()).PickUnit();
					int mult = attckMonster->getPower() * attckMonster->GetHealth();
					int root = sqrt(dfndUnit->GetHealth());
					int damage = (mult / 100) * root;
					int health = dfndUnit->GetHealth() - damage;
					dfndUnit->setHealth(health);
					////		MY_COUT(" EG health after hit:" << dfndUnit->GetHealth() << endl);
					temp->enqueue(dfndUnit);
					if (dfndUnit->getTa() == 0) { dfndUnit->setTa(ts); }
					dfndUnit->setDf(dfndUnit->getTa() - dfndUnit->getTj());
				}
			}
			G1->AddtoUnitsFightingList(attckMonster);
			MY_COUT("AM " << attckMonster->GetID() << " shot EG [ ");
			Earth_Gunner* EG;
			while (temp->dequeue(EG)) {
				MY_COUT(EG->GetID() << ", ");
				if (EG->GetHealth() <= 0) {
					G1->AddtoKilledList(EG, ts);
					totalDbE += EG->getDb();
					totalDfE += EG->getDf();
					totalDdE += EG->getDd();
					EA.DecAliveEUnits();
					G1->setEGDCount(G1->getEGDCount() + 1);
					////		MY_COUT("Added to killed List\n");
				}
				else {
					(EA.getEGList()).AddUnit(EG);
					////		MY_COUT("Added to EG List\n");
				}
			}
			MY_COUT("]\n");
			delete temp;
			////	MY_COUT(" Reinsertion of attacking AM unit:" << endl);
			AMList.AddUnit(attckMonster);
			////	MY_COUT(" Reinsertion of attacking AM unit complete!" << endl);
			flag--;
		}
	}

	if (ADList.GetCount() >=2) {
		int c3;
		int c4;
		Alien_Drones* attckDrone1 = ADList.PickUnitfirst();
		if (ADList.GetCount() != 0)
			c3 = attckDrone1->getAttckCap();
		else
			c3 = 0;
		Alien_Drones* attckDrone2 = ADList.PickUnitlast();
		if (ADList.GetCount() != 0)
			c4 = attckDrone2->getAttckCap();
		else
			c4 = 0;

		static int flag1 = 0;
		if (flag1 == 0) {
			//ETStack* ETList = EA.getETList();
			LinkedQueue<Earth_Tank*>* temp = new LinkedQueue<Earth_Tank*>;
			LinkedQueue<Earth_Tank*>* temp2 = new LinkedQueue<Earth_Tank*>;
			if (c3 > (EA.getETList()).GetCount())
				c3 = (EA.getETList()).GetCount();
			if (attckDrone1 != nullptr) {
				for (int i = 0; i < c3; i++) {
					if ((EA.getETList()).GetCount() > 0) {
						Earth_Tank* dfndUnit = (EA.getETList()).PickUnit();
						int mult = attckDrone1->getPower() * attckDrone1->GetHealth();
						int root = sqrt(dfndUnit->GetHealth());
						int damage = (mult / 100) * root;
						int health = dfndUnit->GetHealth() - damage;
						dfndUnit->setHealth(health);
						////			MY_COUT(" ET health after hit:" << dfndUnit->GetHealth() << endl);
						temp->enqueue(dfndUnit);
						if (dfndUnit->getTa() == 0) { dfndUnit->setTa(ts); }
						dfndUnit->setDf(dfndUnit->getTa() - dfndUnit->getTj());
					}
				}
				G1->AddtoUnitsFightingList(attckDrone1);
				MY_COUT("AD1 " << attckDrone1->GetID() << " shot ET [ ");
				Earth_Tank* ET;
				while (temp->dequeue(ET)) {
					MY_COUT(ET->GetID() << ", ");
					if (ET->GetHealth() <= 0) {
						G1->AddtoKilledList(ET, ts);
						totalDbE += ET->getDb();
						totalDfE += ET->getDf();
						totalDdE += ET->getDd();
						EA.DecAliveEUnits();
						G1->setETDCount(G1->getETDCount() + 1);
						////				MY_COUT("Added to killed List\n");
					}
					else {
						(EA.getETList()).AddUnit(ET);
						////				MY_COUT("Added to ET List\n");
					}
				}
			}
			MY_COUT("]\n");
			delete temp;
			////		MY_COUT(" Reinsertion of attacking AD1 unit:" << endl);
			ADList.AddUnitfirst(attckDrone1);
			////		MY_COUT(" Reinsertion of attacking AD1 unit complete!" << endl);
		}

		if (attckDrone2 != nullptr) {
			LinkedQueue<Earth_Tank*>* temp = new LinkedQueue<Earth_Tank*>;
			if (c4 > (EA.getETList()).GetCount())
				c4 = (EA.getETList()).GetCount();

			for (int i = 0; i < c4; i++) {
				if ((EA.getETList().GetCount()) > 0) {
					Earth_Tank* dfndUnit = (EA.getETList()).PickUnit();
					int mult = attckDrone2->getPower() * attckDrone2->GetHealth();
					int root = sqrt(dfndUnit->GetHealth());
					int damage = (mult / 100) * root;
					int health = dfndUnit->GetHealth() - damage;
					dfndUnit->setHealth(health);
					////			MY_COUT(" ET health after hit:" << dfndUnit->GetHealth() << endl);
					temp->enqueue(dfndUnit);
					if (dfndUnit->getTa() == 0) { dfndUnit->setTa(ts); }
					dfndUnit->setDf(dfndUnit->getTa() - dfndUnit->getTj());
				}
			}
			G1->AddtoUnitsFightingList(attckDrone2);
			MY_COUT("AD2 " << attckDrone2->GetID() << " shot ET [ ");
			Earth_Tank* ET;
			while (temp->dequeue(ET)) {
				MY_COUT(ET->GetID() << ", ");
				if (ET->GetHealth() <= 0) {
					G1->AddtoKilledList(ET, ts);
					totalDbE += ET->getDb();
					totalDfE += ET->getDf();
					totalDdE += ET->getDd();
					EA.DecAliveEUnits();
					G1->setETDCount(G1->getETDCount() + 1);
					////				MY_COUT("Added to killed List\n");
				}
				else {
					(EA.getETList()).AddUnit(ET);
					////				MY_COUT("Added to ET List\n");
				}
			}
			MY_COUT("]\n");
			delete temp;
			////		MY_COUT(" Reinsertion of attacking AD2 unit:" << endl);
			ADList.AddUnitlast(attckDrone2);
			////	MY_COUT(" Reinsertion of attacking AD2 unit complete!" << endl);
			flag1++;
		}
		else if (flag1 == 1) {
			//EGPriQueue* EGList = EA.getEGList();
			if (attckDrone1 != nullptr) {
				LinkedQueue<Earth_Gunner*>* temp = new LinkedQueue<Earth_Gunner*>;
				if (c3 > (EA.getEGList()).GetCount())
					c3 = (EA.getEGList()).GetCount();

				for (int i = 0; i < c3; i++) {
					if (!(EA.getEGList().isEmpty())) {
						Earth_Gunner* dfndUnit = (EA.getEGList()).PickUnit();
						int mult = attckDrone1->getPower() * attckDrone1->GetHealth();
						int root = sqrt(dfndUnit->GetHealth());
						int damage = (mult / 100) * root;
						int health = dfndUnit->GetHealth() - damage;
						dfndUnit->setHealth(health);
						////			MY_COUT(" EG health after hit:" << dfndUnit->GetHealth() << endl);
						temp->enqueue(dfndUnit);
						if (dfndUnit->getTa() == 0) { dfndUnit->setTa(ts); }
						dfndUnit->setDf(dfndUnit->getTa() - dfndUnit->getTj());
					}
				}
				G1->AddtoUnitsFightingList(attckDrone1);
				MY_COUT("AD1 " << attckDrone1->GetID() << " shot EG [ ");
				Earth_Gunner* EG;
				while (temp->dequeue(EG)) {
					MY_COUT(EG->GetID() << ", ");
					if (EG->GetHealth() <= 0) {
						G1->AddtoKilledList(EG, ts);
						totalDbE += EG->getDb();
						totalDfE += EG->getDf();
						totalDdE += EG->getDd();
						EA.DecAliveEUnits();
						G1->setEGDCount(G1->getEGDCount() + 1);
						////		MY_COUT("Added to killed List\n");
					}
					else {
						(EA.getEGList()).AddUnit(EG);
						////		MY_COUT("Added to EG List\n");
					}
				}
				MY_COUT("]\n");
				delete temp;
				////		MY_COUT(" Reinsertion of attacking AD1 unit:" << endl);
				ADList.AddUnitfirst(attckDrone1);
				////		MY_COUT(" Reinsertion of attacking AD1 unit complete!" << endl);
			}

			if (attckDrone2 != nullptr) {
				LinkedQueue<Earth_Gunner*>* temp = new LinkedQueue<Earth_Gunner*>;
				if (c4 > (EA.getEGList()).GetCount())
					c4 = (EA.getEGList()).GetCount();

				for (int i = 0; i < c4; i++) {
					if (!(EA.getEGList().isEmpty())) {
						Earth_Gunner* dfndUnit = (EA.getEGList()).PickUnit();
						int mult = attckDrone2->getPower() * attckDrone2->GetHealth();
						int root = sqrt(dfndUnit->GetHealth());
						int damage = (mult / 100) * root;
						int health = dfndUnit->GetHealth() - damage;
						dfndUnit->setHealth(health);
						////			MY_COUT(" EG health after hit:" << dfndUnit->GetHealth() << endl);
						temp->enqueue(dfndUnit);
						if (dfndUnit->getTa() == 0) { dfndUnit->setTa(ts); }
						dfndUnit->setDf(dfndUnit->getTa() - dfndUnit->getTj());
					}
				}
				G1->AddtoUnitsFightingList(attckDrone2);
				MY_COUT("AD2 " << attckDrone2->GetID() << " shot EG [ ");
				Earth_Gunner* EG;
				while (temp->dequeue(EG)) {
					MY_COUT(EG->GetID() << ", ");
					if (EG->GetHealth() <= 0) {
						G1->AddtoKilledList(EG, ts);
						totalDbE += EG->getDb();
						totalDfE += EG->getDf();
						totalDdE += EG->getDd();
						EA.DecAliveEUnits();
						G1->setEGDCount(G1->getEGDCount() + 1);
						////		MY_COUT("Added to killed List\n");
					}
					else {
						(EA.getEGList()).AddUnit(EG);
						////		MY_COUT("Added to EG List\n");
					}
				}
				MY_COUT("]\n");
				delete temp;
				////		MY_COUT(" Reinsertion of attacking AD2 unit:" << endl);
				ADList.AddUnitlast(attckDrone2);
				////		MY_COUT(" Reinsertion of attacking AD2 unit complete!" << endl);
				flag1--;
			}
		}
	}
}
void AlienArmy::DecAliveAUnits() {
	AliveAUnits--;
}

int AlienArmy::gettotalASCount()
{
	return totalASCount;
}

int AlienArmy::gettotalAMCount()
{
	return totalAMCount;
}

int AlienArmy::gettotalADCount()
{
	return totalADCount;
}

int AlienArmy::gettotalDf()
{
	return totalDfE;
}

int AlienArmy::gettotalDb()
{
	return totalDbE;
}

int AlienArmy::gettotalDd()
{
	return totalDdE;
}
