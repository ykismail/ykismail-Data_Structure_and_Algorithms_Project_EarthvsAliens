#include "EarthArmy.h"
#include <iostream>
#include "AlienArmy.h"
#include "Units.h"
#include "Game.h"
#include "PrintControl.h"
#pragma once

EarthArmy::EarthArmy() {};
void EarthArmy::GenerateEUnits(int NoArmyUnits, int ESPerc, int ETPerc, int EGPerc, int HUPerc, int EH1, int EH2, int EP1, int EP2, int EAC1, int EAC2, int timestep) {
	RandomGen rg;
	for (int i = 0; i < NoArmyUnits; i++) {
		int B = rg.generateRandProb();
		//// MY_COUT("B= " << B << endl);
		if (B <= ESPerc) {
			Earth_Soldier* ES = new Earth_Soldier;
			int id = rg.generateEID();
			while (!(this->CheckEarthIDs(id))) { id = rg.generateEID(); }
			ES->setID(id);
			ES->setHealth(rg.generateWithinRange(EH1, EH2));
			ES->setOriginalHealth(ES->GetHealth());
			ES->setPower(rg.generateWithinRange(EP1, EP2));
			ES->setAttackCap(rg.generateWithinRange(EAC1, EAC2));
			ESList.AddUnit(ES);
			ES->setTj(timestep);
		////	MY_COUT(" ES created with ID:" << ES->GetID() << endl);
			AliveEUnits++;
			totalunits++;
			totalESCount++;
		}
		else if ((B > ESPerc) && B <= (100 - EGPerc - HUPerc)) {
			Earth_Tank* ET = new Earth_Tank;
			int id = rg.generateEID();
			while (!(this->CheckEarthIDs(id))) { id = rg.generateEID(); }
			ET->setID(id);
			ET->setHealth(rg.generateWithinRange(EH1, EH2));
			ET->setOriginalHealth(ET->GetHealth());
			ET->setPower(rg.generateWithinRange(EP1, EP2));
			ET->setAttackCap(rg.generateWithinRange(EAC1, EAC2));
			ETList.AddUnit(ET);
			ET->setTj(timestep);
		////	MY_COUT(" ET created with ID:" << ET->GetID() << endl);
			AliveEUnits++;
			totalunits++;
			totalETCount++;
		}
		else if ((B > ETPerc) && B <= (100 - HUPerc)) {
			Earth_Gunner* EG = new Earth_Gunner;
			int id = rg.generateEID();
			while (!(this->CheckEarthIDs(id))) { id = rg.generateEID(); }
			EG->setID(id);
			EG->setHealth(rg.generateWithinRange(EH1, EH2));
			EG->setPower(rg.generateWithinRange(EP1, EP2));
			EG->setAttackCap(rg.generateWithinRange(EAC1, EAC2));
			EGList.AddUnit(EG);
			EG->setTj(timestep);
			MY_COUT(" EG created with ID:" << EG->GetID() << endl);
			AliveEUnits++;
			totalunits++;
			totalEGCount++;
		}
		else {
			Heal_Unit* HU = new Heal_Unit;
			int id = rg.generateEID();
			while (!(this->CheckEarthIDs(id))) { id = rg.generateEID(); }
			HU->setID(id);
			HU->setHealth(rg.generateWithinRange(EH1, EH2));
			HU->setPower(rg.generateWithinRange(EP1, EP2));
			HU->setAttackCap(rg.generateWithinRange(EAC1, EAC2));
			HUList.AddUnit(HU);
			HU->setTj(timestep);
			MY_COUT(" Earth Healer created with ID:" << HU->GetID() << endl);
			totalunits++;
			totalHUCount++;
		}
	}
}

bool EarthArmy::CheckEarthIDs(int id)
{
	if (ESList.CheckID(id) && ETList.CheckID(id) && EGList.CheckID(id))
		return true;
	else
		return false;
}

int EarthArmy::getAliveEUnits() {
	return AliveEUnits;
}

ESQueue& EarthArmy::getESList() {
	return ESList;
}

ETStack& EarthArmy::getETList() {
	return ETList;
}

EGPriQueue& EarthArmy::getEGList() {
	return EGList;
}

HUStack& EarthArmy::getHUList() {
	return HUList;
}



void EarthArmy::print() {
	MY_COUT(ESList.GetCount() << " ES [");
	ESList.PrintAll();
	MY_COUT("]" << endl);
	MY_COUT(ETList.GetCount() << " ET [");
	ETList.PrintAll();
	MY_COUT( "]" << endl);
	MY_COUT(EGList.GetCount() << " EG [");
	EGList.PrintAll();
	MY_COUT("]" << endl);
	HUList.PrintAll();
}

void EarthArmy::Heal(Game* G1,int timestep)
{

	if (G1->GetUnitsMaintenanceList()->isEmpty()) {
		MY_COUT("There are no units in the UML!\n");
	} 
	else if (HUList.GetCount() == 0) {
		MY_COUT("There are no Heal Units!\n");
	} else {
		Heal_Unit* HU = getHUList().PickUnit(); 
			int Counter = HU->getAttckCap();
			int i = 0;
			while ((!G1->GetESMaintenanceList()->isEmpty() || !G1->GetETMaintenanceList()->isEmpty()) && i < Counter) {
				if (!G1->GetESMaintenanceList()->isEmpty()) {
					Earth_Soldier* ES = G1->removefromESUML();
					if ((timestep - ES->getTUML()) >= 10) {
						G1->AddtoKilledList(ES, timestep);
						ES = G1->removefromESUML();
					}
					else {
						HU->HealUnit(ES);
						if (ES->GetHealth() <= 0.2 * ES->GetOriginalHealth()) {
							////	MY_COUT( "ES " << ES->GetID() << " health has not exceeded 20 % of its original health! So it will be added back to UML after healing ends!\n ET's Original Health= " << ES->GetOriginalHealth() << " ET's Health after healing=  " << ES->GetHealth() << "\n");
							if (HU->getTa() == 0) { HU->setTa(timestep); }
							G1->AddtoTempList(ES);
						}

						else {
							//// MY_COUT( "ES with ID " << ES->GetID() << " Has been Healed!\n New Health= " << ES->GetHealth() << "\n New Maintenance List : \n");
							ESList.AddUnit(ES);
							if (HU->getTa() == 0) { HU->setTa(timestep); }
							totalhealedunits++;
							G1->PrintUnitsMaintenanceList();
						}
					}
				}
				else if (!G1->GetETMaintenanceList()->isEmpty() && G1->GetESMaintenanceList()->isEmpty()) {
					Earth_Tank* ET = G1->removefromETUML();
					if (timestep - ET->getTUML() > 10) {
						G1->AddtoKilledList(ET, timestep);
						ET = G1->removefromETUML();
					}
					else {
						HU->HealUnit(ET);
						if (ET->GetHealth() <= 0.2 * ET->GetOriginalHealth()) {
							////	MY_COUT( "ET " << ET->GetID() << " health has not exceeded 20 % of its original health! So it will be added back to UML after healing ends!\n ET's Original Health= " << ET->GetOriginalHealth() << " ET's Health after healing=  " << ET->GetHealth() << "\n");
							if (HU->getTa() == 0) { HU->setTa(timestep); }
							G1->AddtoTempList(ET);
						}
						else {
							////	MY_COUT( "ET with ID " << ET->GetID() << " Has been Healed!\n New Health= " << ET->GetHealth() << "\n New Maintenance List : \n");
							ETList.AddUnit(ET);
							if (HU->getTa() == 0) { HU->setTa(timestep); }
							totalhealedunits++;
							G1->PrintUnitsMaintenanceList();
						}
					}
					i++;
				}
			}
			if (G1->GetESMaintenanceList()->isEmpty() && G1->GetETMaintenanceList()->isEmpty()) {
				MY_COUT( "No more Units in UML!\n");
			}
		MY_COUT( "Healing has finished and healer will be moved to killed list!\n");
		G1->AddtoKilledList(HU,timestep);
		G1->setHUDCount(G1->getHUDCount() + 1);
		G1->PrintKilledList();
		MY_COUT( "UML: \n");
		G1->MovefromTemptoUML(timestep); 
		G1->PrintUnitsMaintenanceList(); 
		}
}


int EarthArmy::gettotalEunits()
{
	return this->totalunits;
}

void EarthArmy::DecAliveEUnits() {
	AliveEUnits--;
}
void EarthArmy::ATTACK(AlienArmy& AA, Game* G1, int ts) {
	LinkedQueue<Alien_Soldier*>* temp = new LinkedQueue<Alien_Soldier*>;
	if (ESList.GetCount()!=0) {
	Earth_Soldier* attcksoldier = ESList.PickUnit();
		int c1 = attcksoldier->getAttckCap();

		
		if (c1 > (AA.getASList()).GetCount())
			c1 = (AA.getASList()).GetCount();

		for (int i = 0; i < c1; i++) {
			if (!(AA.getASList().isEmpty())) {
				Alien_Soldier* dfndUnit = (AA.getASList()).PickUnit();
				int mult = attcksoldier->getPower() * attcksoldier->GetHealth();
				int root = sqrt(dfndUnit->GetHealth());
				int damage = (mult / 100) * root;
				int health = dfndUnit->GetHealth() - damage;
				dfndUnit->setHealth(health);
			////	MY_COUT(" AS health after hit:" << dfndUnit->GetHealth() << endl);
				temp->enqueue(dfndUnit);
				if (dfndUnit->getTa() == 0) {
					dfndUnit->setTa(ts);
					dfndUnit->setDf(dfndUnit->getTa() - dfndUnit->getTj());
				}
			}
		}
		G1->AddtoUnitsFightingList(attcksoldier);
		MY_COUT("ES " << attcksoldier->GetID() << " shot AS [ ");
		Alien_Soldier* AS;
		while(temp->dequeue(AS)){
				MY_COUT(AS->GetID() << ", "); 
				if (AS->GetHealth() <= 0)
				{
					G1->AddtoKilledList(AS,ts);
					totalDfA += AS->getDf();
					totalDbA += AS->getDb(); 
					totalDdA += AS->getDd(); 
					AA.DecAliveAUnits();  
					G1->setASDCount(G1->getASDCount() + 1);
				}
				else (AA.getASList()).AddUnit(AS);
		}
		MY_COUT("]\n");
		delete temp;
		//// MY_COUT(" Reinsertion of attacking ES unit:" << endl);
		ESList.AddUnit(attcksoldier);
		//// MY_COUT(" Reinsertion of attacking ES unit complete!" << endl);
	}

	//EG Attack
	if (EGList.GetCount() != 0) {
		Earth_Gunner* eg = EGList.PickUnit();
		if (eg != nullptr) {
			int egPri = 0;
			LinkedQueue<Alien_Monster*>* temp = new LinkedQueue<Alien_Monster*>;
			LinkedQueue<Alien_Monster*>* tempall = new LinkedQueue<Alien_Monster*>;
			LinkedQueue<Alien_Drones*>* temp2 = new LinkedQueue<Alien_Drones*>;
			LinkedQueue<Alien_Drones*>* temp2all = new LinkedQueue<Alien_Drones*>;
			RandomGen rg;
			int i = 0;
			if (AA.getAMList().GetCount() != 0) { G1->AddtoUnitsFightingList(eg); } 
			while (i < eg->getAttckCap() && (AA.getAMList().GetCount() != 0)) {
				int amIdx = rg.generateWithinRange(0, AA.getAMList().GetCount() - 1);
				Alien_Monster* am = AA.getAMList().PickUnit(amIdx);

				// decrease health
				eg->hit(am);
				////	MY_COUT("AM health after hit: " << am->GetHealth() << "\n");
				if (am->getTa() == 0) { 
					am->setTa(ts); 
					am->setDf(ts - am->getTj()); 
				}
				if (am->GetHealth() <= 0) {
					// go to killed
					G1->AddtoKilledList(am, ts);
					tempall->enqueue(am);
					AA.DecAliveAUnits();
					totalDfA += am->getDf(); 
					totalDbA += am->getDb(); 
					totalDdA += am->getDd(); 
					G1->setAMDCount(G1->getAMDCount() + 1);
				}
				else { temp->enqueue(am);
				tempall->enqueue(am);
				}
				i++;
			}
			if (i < eg->getAttckCap()) {
				int flag = 0;
				if (AA.getADList().GetCount() != 0 && AA.getAMList().GetCount()==0) { G1->AddtoUnitsFightingList(eg); }
				while (i < eg->getAttckCap() && AA.getADList().GetCount() != 0) {
					Alien_Drones* AD; 
					if (flag == 0) {
						AD = AA.getADList().PickUnitfirst();
						eg->hit(AD);
						if (AD->getTa() == 0) {
							AD->setTa(ts);
							AD->setDf(ts - AD->getTj());
						}
						if (AD->GetHealth() <= 0) {
							G1->AddtoKilledList(AD,ts);
							totalDfA += AD->getDf();
							totalDbA += AD->getDb();
							totalDdA += AD->getDd();
							AA.DecAliveAUnits();
							temp2all->enqueue(AD);
							G1->setADDCount(G1->getADDCount() + 1);
						}
						else { temp2->enqueue(AD); temp2all->enqueue(AD); }
						flag = 1;
					}
					else if (flag == 1) {
						AD = AA.getADList().PickUnitlast();
						eg->hit(AD);
						if (AD->getTa() == 0) { 
							AD->setTa(ts); 
							AD->setDf(ts - AD->getTj()); 
						}
						if (AD->GetHealth() <= 0) { 
	 						G1->AddtoKilledList(AD, ts);
	 						totalDfA += AD->getDf();
	 						totalDbA += AD->getDb();
	 						totalDdA += AD->getDd();
							AA.DecAliveAUnits();
	 						temp2all->enqueue(AD);
							G1->setADDCount(G1->getADDCount() + 1);
						}
	 					else { temp2->enqueue(AD); temp2all->enqueue(AD); }
						flag = 0;
					}
					i++;
				}
					EGList.AddUnit(eg); 
					Alien_Monster* am; 
					while (temp->dequeue(am)) { 
						AA.getAMList().AddUnit(am);  
					}
					MY_COUT("EG " << eg->GetID() << " shot AM [ "); 
					while (tempall->dequeue(am)) { 
						MY_COUT(am->GetID() << ", "); 
					}
					MY_COUT("]\n");
					delete temp; 
					delete tempall; 
					Alien_Drones* AD;
					int addflag = 0;
					while (temp2->dequeue(AD)) {
						if (addflag == 0) {
							AA.getADList().AddUnitfirst(AD);
							addflag = 1;
						}
						else if (addflag == 1) {
							AA.getADList().AddUnitlast(AD);
							addflag = 0;
						}
					}
					MY_COUT("EG " << eg->GetID() << " shot AD [ ");
					while (temp2all->dequeue(AD)) { 
						MY_COUT(AD->GetID() << ", "); 
					}
					MY_COUT("]\n");
					delete temp2;
					delete temp2all; 
				//ET Attack
				if (ETList.GetCount() != 0) {
					Earth_Tank* et = ETList.PickUnit();
						// add back
						
						LinkedQueue<Alien_Monster*>* temp = new LinkedQueue<Alien_Monster*>;
						LinkedQueue<Alien_Monster*>* tempall = new LinkedQueue<Alien_Monster*>;
						// get random am
						RandomGen rg1;
						int i = 0;
						if (AA.getAMList().GetCount() != 0||AA.getASList().GetCount()!=0)
						{
							G1->AddtoUnitsFightingList(et);
						}
						while (i < et->getAttckCap() && AA.getAMList().GetCount() != 0) {
							int amIdx = rg1.generateWithinRange(0, AA.getAMList().GetCount() - 1);
							Alien_Monster* am = AA.getAMList().PickUnit(amIdx);

							// decrease health
							et->hit(am);
							//// MY_COUT("AM health after hit: " << am->GetHealth() << "\n");

							if (am->getTa() == 0) {
								am->setTa(ts);
								am->setDf(ts - am->getTj());
							}
							if (am->GetHealth() <= 0) {
								// go to killed
								G1->AddtoKilledList(am, ts);
								tempall->enqueue(am);
								totalDfA += am->getDf();
								totalDbA += am->getDb();
								totalDdA += am->getDd();
								AA.DecAliveAUnits();
								////	MY_COUT("AM " << am->GetID() << " Has died!\n");
								G1->setAMDCount(G1->getAMDCount() + 1);
							}
							else {
								temp->enqueue(am);
								tempall->enqueue(am);
							}
							i++;
						}
						Alien_Monster* am;
						while (temp->dequeue(am)) {
							AA.getAMList().AddUnit(am);
						}
						MY_COUT("ET " << et->GetID() << " shot AM [ ");
						while (tempall->dequeue(am)) {
							MY_COUT(am->GetID() << ", ");
						}
						MY_COUT("]\n");
						delete temp;
						delete tempall;
					if (i< et->getAttckCap()) { 
						if (ESList.GetCount() < 0.3 * AA.getASList().GetCount()) {
							//Earth_Tank* et = ETList.PickUnit();
							LinkedQueue<Alien_Soldier*>* temp = new LinkedQueue<Alien_Soldier*>;
							LinkedQueue<Alien_Soldier*>* tempall = new LinkedQueue<Alien_Soldier*>;
							// add back
							if (et != nullptr) {

									// decrease health
								while (!AA.getASList().isEmpty() && i < et->getAttckCap()) {
									Alien_Soldier* as = AA.getASList().PickUnit();
									et->hit(as);
									//// MY_COUT("AS health after hit: " << as->GetHealth() << "\n");
									if (as->getTa() == 0) {
										as->setTa(ts);
										as->setDf(ts - as->getTj());
									}
									if (as->GetHealth() <= 0) {
										// go to killed
										G1->AddtoKilledList(as, ts);
										tempall->enqueue(as);
										totalDfA += as->getDf();
										totalDbA += as->getDb();
										totalDdA += as->getDd();
										AA.DecAliveAUnits();
										////	MY_COUT("AS " << as->GetID() << " Has died!\n");
										G1->setASDCount(G1->getASDCount() + 1);
									}
									else {temp->enqueue(as); tempall->enqueue(as);
								}
										i++;
									}
								Alien_Soldier* as;
								while (temp->dequeue(as)) {
									AA.getASList().AddUnit(as);
								}
								MY_COUT("ET" << et->GetID() << " shot AS [ ");
								while (tempall->dequeue(as)) {
									MY_COUT(as->GetID() << ", ");
								}
								MY_COUT("]\n");
								delete temp;
								delete tempall;
							}
						}

					}
						ETList.AddUnit(et); 
				}
			}
		}
	}
	this->Heal(G1, ts);
}

int EarthArmy::gettotalESCount()
{
	return totalESCount;
}

int EarthArmy::gettotalETCount()
{
	return totalETCount;
}

int EarthArmy::gettotalEGCount()
{
	return totalEGCount;
}

int EarthArmy::gettotalHUCount()
{
	return totalHUCount;
}

int EarthArmy::gettotalhealedunits()
{
	return totalhealedunits;
}

int EarthArmy::gettotalDf()
{
	return totalDfA;
}

int EarthArmy::gettotalDb()
{
	return totalDbA;
}

int EarthArmy::gettotalDd()
{
	return totalDdA;
}
