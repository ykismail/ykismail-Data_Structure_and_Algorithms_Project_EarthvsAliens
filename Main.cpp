// Phase 1.2 final.cpp : This file contains the 'main' function. Program execution begins and ends there.//

#include <iostream>
#include<fstream>
#include<iomanip>
#include "AlienArmy.h"
#include "EarthArmy.h"
#include "Game.h"
#include "BattleInfo.h"
#include "InputReader.h"
#include"RandomGen.h"
#include "PrintControl.h"
#include "GenerateNewFileName.h"
// Phase 1.2 final.cpp : This file contains the 'main' function. Program execution begins and ends there.//
bool SilentMode = false;
int main() 
{
	
	std::cout << "Hello World!\n";

	InputReader R1;
	BattleInfo BI = R1.reader();
	Game* G1 = new Game();
	AlienArmy AlienArmy;
	EarthArmy EarthArmy;
	RandomGen rg;
	char Continue = 'a';
	int timestep = 0;
	bool fightFlag = 0;
	//SilentStream stream(SilentMode);
	std::cout << " Enter S to run in Silent Mode.\n";
	char input;
	std::cin >> input;
	if (input == 'S') {
		SilentMode = true;
	
	std::cout << "Program is running in silent mode...\n";
	}
	//std::cout << SilentMode ? "True\n" : "False\n";
	if (SilentMode) {
		std::cout << "SHHHHH...\n";
	}
	else std::cout << "Let the Battle Begin!!\n";
	while (fightFlag == 0 || ((AlienArmy.getAliveAUnits() >= 1 && EarthArmy.getAliveEUnits() >= 1 && timestep < 100)))
	{
		MY_COUT("Current Timestep is " << timestep << endl);
		int AE = rg.generateRandProb();
	//	MY_COUT("A= " << AE << endl); //integer A for Earth "AE"
		if (AE <= BI.GetProb())
		{
			//MY_COUT("A<=Probability therefore " << BI.GetArmyUnits() << " Earth units will be generated:\n");
			EarthArmy.GenerateEUnits(BI.GetArmyUnits(), BI.GetEsoliders(), BI.GetET(), BI.GetEG(), BI.GetHU(), BI.GetEH1(), BI.GetEH2(), BI.GetEP1(), BI.GetEP2(), BI.GetEAC1(), BI.GetEAC2(), timestep);
			//EarthArmy.getEGList().AddUnit(rg.generateEID(), 20, 20, rg.generateWithinRange(1,10));
		}
		/*else {
			MY_COUT("A>Probability therefore no Earth units will be generated this timestep!\n");
		}*/

		int AA = rg.generateRandProb(); //integer A for Aliens "AA"
	//	MY_COUT("A = " << AA << endl);

		if (AA <= BI.GetProb())
		{
			//MY_COUT("A<=Probability therefore " << BI.GetArmyUnits() << " Alien units will be generated:\n");
			//AlienArmy.getADList().AddUnitfirst(rg.generateAID(), rg.generateRandProb(), rg.generateRandProb(), rg.generateRandProb());
			AlienArmy.GenerateAUnits(BI.GetArmyUnits(), BI.GetAsoliders(), BI.GetAM(), BI.GetAD(), BI.GetAH1(), BI.GetAH2(), BI.GetAP1(), BI.GetAP2(), BI.GetAAC1(), BI.GetAAC2(), timestep);
		}
		/*else {
			MY_COUT("A>Probability therefore no Alien units will be generated this timestep!\n");
		}*/


		MY_COUT("==============Units fighting at current timestep==============\n\n");
		if (EarthArmy.getAliveEUnits() > 0 && AlienArmy.getAliveAUnits() > 0) {
			AlienArmy.ATTACK(EarthArmy, G1, timestep);
			fightFlag = 1;
			if (EarthArmy.getAliveEUnits() > 0)
				EarthArmy.ATTACK(AlienArmy, G1, timestep); 
		}
		G1->PrintUnitsFightingList();
		MY_COUT("OUTPUT SCREEN:\n");
		MY_COUT("==============Earth Army Alive Units==============\n");
		EarthArmy.print();

		MY_COUT("==============Alien Army Alive Units==============\n");
		AlienArmy.print();

		
		MY_COUT("==============Units Maintenance List==============\n\n");
		G1->PrintUnitsMaintenanceList();

		if (timestep < 10 && AlienArmy.getAliveAUnits() == 0 && EarthArmy.getAliveEUnits() == 0) {
			MY_COUT("Since no Earth units && no Alien units exist yet, no fighting will happen!\n");
		}


		MY_COUT("==============Killed/Destructed Units==============\n");
		G1->PrintKilledList();
		MY_COUT(" Press any key to move to next time step:\n");
	//	std::cin >> Continue;
		timestep++;
		G1->ClearUnitsFightingList();
	}
	if ((EarthArmy.getAliveEUnits() <= 1 && AlienArmy.getAliveAUnits() <= 1) || timestep == 500) {
		MY_COUT("##################  DRAW  ###################");
		//cin >> Continue;
	}
	else if (EarthArmy.getAliveEUnits() <= 1) {
		MY_COUT("##################  ALIENS VICTORY  ###################");
		//cin >> Continue;
	}
	else if (AlienArmy.getAliveAUnits() <= 1) {
		MY_COUT("##################  EARTH VICTORY  ###################");
		//cin >> Continue;
	}
//	cin >> Continue;
	std::cout << "Output File has been created...\n";
	std::string filename = "output.txt"; // Existing filename 
	std::string newFilename = generateNewFilename(filename);
	std::ofstream out_file(newFilename);
	while (!G1->GetKilledList()->isEmpty()) { 
		Units* unit=G1->removefromkilledlist(); 
		out_file << "Td     ID    Tj    Df    Dd    Db\n"; 
		out_file <<" " << unit->getTd() << "     " << unit->GetID() << "     " << unit->getTj() << "     " << unit->getDf() << "     " << unit->getDd() << "     " << unit->getDb() << std::endl; 
	}
	if (EarthArmy.getAliveEUnits() <= 1) {
		out_file << "Earth Army has Lost!\n";
	}
	else if (AlienArmy.getAliveAUnits() <= 1) {
		out_file << "Earth Army has Won!\n";
	}
	else {
		out_file << "DRAW!\n";
	}
	out_file << "Total ES units: " << EarthArmy.gettotalESCount() << "\n";  
	out_file << "Total ET units: " << EarthArmy.gettotalETCount()  << "\n"; 
	out_file << "Total EG units: " << EarthArmy.gettotalEGCount() << "\n"; 
	out_file << "Total HU units: " << EarthArmy.gettotalHUCount() << "\n";  
	double tdES = G1->getESDCount();
	double tdET = G1->getETDCount();
	double tdEG = G1->getEGDCount();
	double tdHU = G1->getHUDCount();
	double tES = EarthArmy.gettotalESCount();
	double tET = EarthArmy.gettotalETCount();
	double tEG = EarthArmy.gettotalEGCount();
	double tHU = EarthArmy.gettotalHUCount();
	double tEU = EarthArmy.gettotalEunits(); 
	double relES = (tdES / tES)*100;
	double relET = (tdET / tET)*100;
	double relEG = (tdEG / (tEG+1))*100;
	double relt = ((tdES + tdET + tdEG) / tEU) * 100;
	out_file << "Percentage of destructed ES units relative to total ES units: " << relES<<"%\n";
	out_file << "Percentage of destructed ET units relative to total ET units: " << relET<<"%\n";
	out_file << "Percentage of destructed EG units relative to total EG units: " << relEG<<"%\n";
	out_file << "Percentage of destructed Earth units relative to total units: " << relt <<"%\n";
	double th = EarthArmy.gettotalhealedunits();
	double relh = (th/ tEU)*100;
	out_file << "Total Healed Units relative to total units: " << th << "/"<<tEU<<"\n";
	double avgDfE = AlienArmy.gettotalDf() / (G1->getADDCount() + G1->getAMDCount() + G1->getASDCount());
	double avgDdE = AlienArmy.gettotalDd() / (G1->getADDCount() + G1->getAMDCount() + G1->getASDCount());
	double avgDbE = AlienArmy.gettotalDb() / (G1->getADDCount() + G1->getAMDCount() + G1->getASDCount());
	double dfdbE = (avgDfE / avgDbE) * 100; 
	double dddbE = (avgDdE / avgDbE) * 100;
	out_file << "Average Df for killed Earth Units: "<<avgDfE <<"\n";
	out_file << "Average Dd for killed Earth Units: "<<avgDdE <<"\n";
	out_file << "Average Db for killed Earth Units: "<< avgDbE<<"\n";
	out_file << "%Df/Db for killed Earth Units: "	<<dfdbE <<"%\n";
	out_file << "%Dd/Db for killed Earth Units: "	<< dddbE<<"%\n";
	

	out_file << "Total AS units: " << AlienArmy.gettotalASCount() << "\n";  
	out_file << "Total AM units: " << AlienArmy.gettotalAMCount() << "\n";  
	out_file << "Total AD units: " << AlienArmy.gettotalADCount() << "\n";
	double tdAS = G1->getASDCount(); 
	double tdAM = G1->getAMDCount(); 
	double tdAD = G1->getADDCount(); 
	double tdAU = AlienArmy.gettotalAunits(); 
	double relAS = (tdAS/ tdAU) * 100;  
	double relAM = (tdAM/ tdAU) * 100; 
	double relAD = (tdAD/ tdAU) * 100; 
	double reltA = ((tdAS+tdAM+tdAD) / tdAU) * 100;
	out_file << "Percentage of destructed AS units relative to total AS units: " << relAS<<"%\n";
	out_file << "Percentage of destructed AM units relative to total AM units: " <<relAM <<"%\n";
	out_file << "Percentage of destructed AD units relative to total AD units: " <<relAD <<"%\n";
	out_file << "Percentage of destructed Alien units relative to total units: " <<reltA <<"%\n";
	double avgdfA = EarthArmy.gettotalDf() / (G1->getESDCount() + G1->getETDCount() + G1->getEGDCount());
	double avgdbA = EarthArmy.gettotalDb() / (G1->getESDCount() + G1->getETDCount() + G1->getEGDCount());
	double avgddA = EarthArmy.gettotalDd() / (G1->getESDCount() + G1->getETDCount() + G1->getEGDCount());
	double dfdbA = (avgdfA / avgdbA) * 100; 
	double dddbA = (avgddA / avgdbA) * 100; 
	out_file << "Average Df for killed Alien Units: "<< avgdfA<< "\n";
	out_file << "Average Dd for killed Alien Units: "<< avgdbA<< "\n";
	out_file << "Average Db for killed Alien Units: "<< avgddA<< "\n";
	out_file << "%Df/Db for killed Alien Units: "	<< dfdbA<< "%\n";
	out_file << "%Dd/Db for killed Alien Units: "	<< dddbA<< "%\n";

	/*
	EarthArmy.getHUList().AddUnit(300, 30, 30, 6);
	EarthArmy.getHUList().AddUnit(200, 20, 20, 5);
	Earth_Tank* ET1 = new Earth_Tank(12, 10, 30, 2);
	Earth_Tank* ET2 = new Earth_Tank(13, 10, 30, 2);
	Earth_Tank* ET3 = new Earth_Tank(14, 20, 30, 2);
	Earth_Tank* ET4 = new Earth_Tank(15, 30, 30, 2);
	Earth_Tank* ET5 = new Earth_Tank(16, 100, 30, 2);
	G1->AddtoUnitsMaintenanceList(ET1,timestep);
	G1->AddtoUnitsMaintenanceList(ET2,timestep);
	G1->AddtoUnitsMaintenanceList(ET3,timestep);
	G1->AddtoUnitsMaintenanceList(ET4,timestep);
	ET5->setHealth(10);
	MY_COUT(ET5->GetHealth() << " " << ET5->GetOriginalHealth() << std::endl);
	G1->AddtoUnitsMaintenanceList(ET5,timestep);
	Earth_Soldier* ES1 = new Earth_Soldier(9, 10, 20, 2);
	Earth_Soldier* ES2 = new Earth_Soldier(10, 5, 20, 2);
	Earth_Soldier* ES3 = new Earth_Soldier(11, 30, 20, 2);
	G1->AddtoUnitsMaintenanceList(ES1,timestep);
	G1->AddtoUnitsMaintenanceList(ES2,timestep);
	G1->AddtoUnitsMaintenanceList(ES3,timestep);
	EarthArmy.Heal(G1,timestep);
	EarthArmy.getETList().PrintAll();
	EarthArmy.getESList().PrintAll();*/







	//if 0, no fight has started yet... if 1, a fight has started

	//////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////ES ATTACKS AS//////////////////////////////////////////

	//Earth_Soldier* ES = new Earth_Soldier;
	//int id = rg.generateEID();
	//while (!(ESList.CheckID(id) || ETList.CheckID(id) || EGList.CheckID(id))) { id = rg.generateEID(); }
	//ES->setID(id);
	//ES->setHealth(rg.generateWithinRange(BI.GetEH1(), BI.GetEH2()));
	//ES->setPower(rg.generateWithinRange(BI.GetEP1(), BI.GetEP2()));
	//ES->setAttackCap(rg.generateWithinRange(BI.GetEAC1(), BI.GetEAC2()));
	//ESList.AddUnit(ES);
	//std::cout << " ES created with ID:" << ES->GetID() << endl;

	//Earth_Soldier* attckSold = ESList.PickUnit();
	//for (int i = 0; i < attckSold->getAttckCap(); i++) {
	//	Alien_Soldier* AS = new Alien_Soldier;
	//	id = rg.generateEID();
	//	while (!(ASList.CheckID(id) || AMList.CheckID(id) || ADList.CheckID(id))) { id = rg.generateEID(); }
	//	AS->setID(id);
	//	AS->setHealth(rg.generateWithinRange(BI.GetAH1(), BI.GetAH2()));
	//	AS->setPower(rg.generateWithinRange(BI.GetAP1(), BI.GetAP2()));
	//	AS->setAttackCap(rg.generateWithinRange(BI.GetAAC1(), BI.GetAAC2()));
	//	ASList.AddUnit(AS);
	//	std::cout << " AS created with ID:" << AS->GetID() << endl;
	//	std::cout << " AS created with health:" << AS->GetHealth() << endl;
	//}

	//AS->hit();
	//std::cout << " AS health after hit:" << AS->GetHealth() <<endl;

	//Alien_Soldier* ShotbyES[1000];

	//std::cout << "ES attack capacity: " << attckSold->getAttckCap() << endl;
	//std::cout << " Attack will begin:" << endl;
	//for (int i = 0; i < attckSold->getAttckCap(); i++) {
	//	Alien_Soldier* dfndSold = ASList.PickUnit();
	//	attckSold->Attack(dfndSold);
	//	std::cout << " Attack #" << i + 1 << " ended:" << endl;
	//	std::cout << " New AS Health =" << dfndSold->GetHealth() << endl;
	//	ShotbyES[i] = dfndSold;
	//}
	//std::cout << "ES " << attckSold->GetID() << " shot AS [ ";
	//for (int i = 0; i < attckSold->getAttckCap(); i++)
	//{
	//	std::cout << ShotbyES[i]->GetID() << ", ";
	//}
	//std::cout << "]\n";
	//std::cout << " Reinsertion of attacking ES unit:" << endl;
	//ESList.AddUnit(attckSold);
	//std::cout << " Reinsertion of attacking ES unit complete!" << endl;
	//std::cout << " Reinsertion of attacked AS units:" << endl;
	//for (int i = 0; i < attckSold->getAttckCap(); i++)
	//{
	//	std::cout << "Shot soldier #" << i + 1 << " has health = " << ShotbyES[i]->GetHealth() << endl;
	//	if (ShotbyES[i]->GetHealth() <= 0) {
	//		G1->AddtoKilledList(ShotbyES[i]);
	//		std::cout << "Added to killed List\n";
	//	}
	//	else {
	//		ASList.AddUnit(ShotbyES[i]);
	//		std::cout << "Added to ASList\n";
	//	}
	//}
	//std::cout << "Insertion of AS complete\n";
	//for (int i = 0; i < attckSold->getAttckCap(); i++)
	//{
	//	ShotbyES[i] = NULL;
	//}

	////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////AD ATTACKS ET&EG//////////////////////////////////////////

	//{
	//	Alien_Drones* AD1 = new Alien_Drones;
	//	int id = rg.generateEID();
	//	while (!(ASList.CheckID(id) || AMList.CheckID(id) || ADList.CheckID(id))) { id = rg.generateEID(); }
	//	AD1->setID(id);
	//	AD1->setHealth(rg.generateWithinRange(BI.GetAH1(), BI.GetAH2()));
	//	AD1->setPower(rg.generateWithinRange(BI.GetAP1(), BI.GetAP2()));
	//	AD1->setAttackCap(rg.generateWithinRange(BI.GetAAC1(), BI.GetAAC2()));
	//	ADList.AddUnitfirst(AD1);
	//}
	//{
	//	Alien_Drones* AD2 = new Alien_Drones;
	//	int id = rg.generateEID();
	//	//while (!(ASList.CheckID(id) || AMList.CheckID(id) || ADList.CheckID(id))) { id = rg.generateEID(); }
	//	AD2->setID(id);
	//	AD2->setHealth(rg.generateWithinRange(BI.GetAH1(), BI.GetAH2()));
	//	AD2->setPower(rg.generateWithinRange(BI.GetAP1(), BI.GetAP2()));
	//	AD2->setAttackCap(rg.generateWithinRange(BI.GetAAC1(), BI.GetAAC2()));
	//	ADList.AddUnitlast(AD2);
	//}


	//Alien_Drones* attckD1 = ADList.PickUnitfirst();

	//for (int i = 0; i < attckD1->getAttckCap(); i++) {
	//	Earth_Tank* ET = new Earth_Tank;
	//	int id = rg.generateEID();
	//	//while (!(ESList.CheckID(id) || ETList.CheckID(id) || EGList.CheckID(id))) { id = rg.generateEID(); }
	//	ET->setID(id);
	//	ET->setHealth(rg.generateWithinRange(BI.GetEH1(), BI.GetEH2()));
	//	ET->setPower(rg.generateWithinRange(BI.GetEP1(), BI.GetEP2()));
	//	ET->setAttackCap(rg.generateWithinRange(BI.GetEAC1(), BI.GetEAC2()));
	//	ETList.AddUnit(ET);
	//	std::cout << " ET created with ID:" << ET->GetID() << endl;
	//}

	//Alien_Drones* attckD2 = ADList.PickUnitlast();

	//for (int i = 0; i < attckD2->getAttckCap(); i++) {
	//	Earth_Gunner* EG = new Earth_Gunner;
	//	int id = rg.generateEID();
	//	//while (!(ESList.CheckID(id) || ETList.CheckID(id) || EGList.CheckID(id))) { id = rg.generateEID(); }
	//	EG->setID(id);
	//	EG->setHealth(rg.generateWithinRange(BI.GetEH1(), BI.GetEH2()));
	//	EG->setPower(rg.generateWithinRange(BI.GetEP1(), BI.GetEP2()));
	//	EG->setAttackCap(rg.generateWithinRange(BI.GetEAC1(), BI.GetEAC2()));
	//	EGList.AddUnit(EG);
	//	std::cout << " EG created with ID:" << EG->GetID() << endl;
	//}


	//Earth_Tank* ShotbyAD1[1000];
	//Earth_Gunner* ShotbyAD2[1000];

	//std::cout << "AD1 attack capacity: " << attckD1->getAttckCap() << endl;
	//std::cout << " Attacks of AD1 will begin:" << endl;
	//for (int i = 0; i < attckD1->getAttckCap(); i++) {
	//	Earth_Tank* dfndSold = ETList.PickUnit();
	//	attckD1->Attack(dfndSold);
	//	std::cout << " Attack #" << i + 1 << " ended:" << endl;
	//	std::cout << " New ET Health =" << dfndSold->GetHealth() << endl;
	//	ShotbyAD1[i] = dfndSold;
	//}

	//std::cout << "AD2 attack capacity: " << attckD2->getAttckCap() << endl;
	//std::cout << " Attacks of AD2 will begin:" << endl;
	//for (int i = 0; i < attckD2->getAttckCap(); i++) {
	//	Earth_Gunner* dfndSold = EGList.PickUnit();
	//	attckD2->Attack(dfndSold);
	//	std::cout << " Attack #" << i + 1 << " ended:" << endl;
	//	std::cout << " New EG Health =" << dfndSold->GetHealth() << endl;
	//	ShotbyAD2[i] = dfndSold;
	//}

	//std::cout << "AD1 " << attckD1->GetID() << " shot ET [ ";
	//for (int i = 0; i < attckD1->getAttckCap(); i++)
	//{
	//	std::cout << ShotbyAD1[i]->GetID() << ", ";
	//}
	//std::cout << "]\n";


	//std::cout << "AD2 " << attckD2->GetID() << " shot EG [ ";
	//for (int i = 0; i < attckD2->getAttckCap(); i++)
	//{
	//	std::cout << ShotbyAD2[i]->GetID() << ", ";
	//}
	//std::cout << "]\n";

	//std::cout << " Reinsertion of attacking AD1 unit:" << endl;
	//ADList.AddUnitfirst(attckD1);
	//std::cout << " Reinsertion of attacking AD1 unit complete!" << endl;
	//std::cout << " Reinsertion of attacking AD2 unit:" << endl;
	//ADList.AddUnitfirst(attckD2);
	//std::cout << " Reinsertion of attacking AD2 unit complete!" << endl;

	//std::cout << " Reinsertion of attacked ET units:" << endl;
	//for (int i = 0; i < attckD1->getAttckCap(); i++)
	//{
	//	std::cout << "Shot Tank #" << i + 1 << " has health = " << ShotbyAD1[i]->GetHealth() << endl;
	//	if (ShotbyAD1[i]->GetHealth() <= 0) {
	//		G1->AddtoKilledList(ShotbyAD1[i]);
	//		std::cout << "Added to killed List\n";
	//	}
	//	else {
	//		ETList.AddUnit(ShotbyAD1[i]);
	//		std::cout << "Added to ETList\n";
	//	}
	//}
	//std::cout << "Insertion of ET complete\n";
	//for (int i = 0; i < attckD1->getAttckCap(); i++)
	//{
	//	ShotbyAD1[i] = NULL;
	//}

	//std::cout << " Reinsertion of attacked EG units:" << endl;
	//for (int i = 0; i < attckD2->getAttckCap(); i++)
	//{
	//	std::cout << "Shot Gunnery #" << i + 1 << " has health = " << ShotbyAD2[i]->GetHealth() << endl;
	//	if (ShotbyAD2[i]->GetHealth() <= 0) {
	//		G1->AddtoKilledList(ShotbyAD2[i]);
	//		std::cout << "Added to killed List\n";
	//	}
	//	else {
	//		EGList.AddUnit(ShotbyAD2[i]);
	//		std::cout << "Added to EGList\n";
	//	}
	//}

	//std::cout << "Insertion of EG complete\n";
	//for (int i = 0; i < attckD2->getAttckCap(); i++)
	//{
	//	ShotbyAD2[i] = NULL;
	//}



//////////////////////////////////////////////////////////////////////////////////////////////////
/*
	while (fightFlag == 0 || ((AlienArmy.getAliveAUnits() >= 1 && EarthArmy.getAliveEUnits() >= 1)))
	{0
		std::cout << "Current Timestep is " << timestep << endl;
		//G1->RunRound();
		int AE = rg.generateRandProb();
		std::cout << "A= " << AE << endl; //integer A for Earth "AE"
		if (AE <= BI.GetProb())
		{
			std::cout << "A<=Probability therefore " << BI.GetArmyUnits() << " Earth units will be generated:\n";
			EarthArmy.GenerateEUnits(BI.GetArmyUnits(), BI.GetEsoliders(), BI.GetET(), BI.GetEG(), BI.GetEH1(), BI.GetEH2(), BI.GetEP1(), BI.GetEP2(), BI.GetEAC1(), BI.GetEAC2());
		}
		else {
			std::cout << "A>Probability therefore no Earth units will be generated this timestep!\n";
		}

		int AA = rg.generateRandProb(); //integer A for Aliens "AA"
		std::cout << "A = " << AA << endl;

		if (AA <= BI.GetProb())
		{
			std::cout << "A<=Probability therefore " << BI.GetArmyUnits() << " Alien units will be generated:\n";
			AlienArmy.GenerateAUnits(BI.GetArmyUnits(), BI.GetAsoliders(), BI.GetAM(), BI.GetAD(), BI.GetAH1(), BI.GetAH2(), BI.GetAP1(), BI.GetAP2(), BI.GetAAC1(), BI.GetAAC2());
		}
		else {
			std::cout << "A>Probability therefore no Alien units will be generated this timestep!\n";
		}

		std::cout << "\n\n";

		if (timestep < 10 && AlienArmy.getAliveAUnits() == 0 && EarthArmy.getAliveEUnits() == 0) {
			std::cout << "Since no Earth units && no Alien units exist yet, no fighting will happen!\n";
		}
		AlienArmy.print();
		fightFlag == 1;
		cin >> Continue;
		timestep++;
	}
	*/

		//while (G1->getEHCum() != 0 && G1->getAHCum() != 0)
		//{
		//	int X = rg.generateWithinRange(0, 60);
		//	std::cout << "X is generated between 0-60 inclusive: X = " << X << endl;

		//	if (timestep == 0 && AE > BI.GetProb() && AA > BI.GetProb()) {
		//		std::cout << "Since no Earth units && no Alien units exist, X will do nothing\n";
		//	}
		//	else if (X >= 0 && X < 10) {
		//		std::cout << "An ES will be picked & re-inserted:\n";
		//		if (ESList.GetCount() != 0) {
		//			Earth_Soldier* ES;
		//			ES = ESList.PickUnit();
		//			std::cout << "ES Unit is picked\n";
		//			ESList.PrintAll();
		//			ESList.AddUnit(ES);
		//			std::cout << "ES Unit is re-inserted\n";
		//			ESList.PrintAll();
		//		}
		//		else {
		//			std::cout << "No Earth Soldiers found!\n";
		//		}
		//	}
		//	else if (X >= 10 && X < 20) {
		//		std::cout << "An ET will be picked & moved to Killed List\n";
		//		if (ETList.GetCount() != 0) {
		//			Earth_Tank* ET;
		//			std::cout << "ET Unit picked: ";
		//			ET = ETList.PickUnit();
		//			std::cout << "New ET List: ";
		//			ETList.PrintAll();
		//			G1->AddtoKilledList(ET);
		//			std::cout << "ET Unit is added to Killed List\n";
		//			std::cout << "New Killed List: ";
		//			G1->PrintKilledList();
		//			//pick ET from list & move to killed list
		//		}
		//		else {
		//			std::cout << "No Earth Tanks found!\n";
		//		}
		//	}
		//	else if (X >= 20 && X < 30) {
		//		std::cout << "An EG unit will be picked & its health will be halved:\n";
		//		if (EGList.GetCount() != 0) {
		//			Earth_Gunner* EG;
		//			std::cout << "EG Unit picked: ";
		//			EG = EGList.PickUnit();
		//			std::cout << "New EG List: ";
		//			EGList.PrintAll();
		//			int oldHealth = 0;
		//			oldHealth = EG->GetHealth();
		//			EG->setHealth((EG->GetHealth()) * 0.5);
		//			std::cout << "EG unit's health is halved: \n Old Health = " << oldHealth << " , New Health = " << EG->GetHealth() << endl;
		//			EGList.AddUnit(EG);
		//			std::cout << "EG Unit is re-inserted\n";
		//			EGList.PrintAll();
		//			//pick EG from list, EG.setHealth((EG.getHealth())*0.5)), insert it again
		//		}
		//		else {
		//			std::cout << "No Earth Gunners found!\n";
		//		}
		//	}
		//	else if (X >= 30 && X < 40) {
		//		std::cout << "5 AS will be picked, their health will be halved, put in a temp list & then re-inserted to AS List:\n";
		//		if (ASList.GetCount() != 0) {
		//			int N;
		//			ASQueue tempASList;
		//			if (ASList.GetCount() < 5)
		//			{
		//				N = ASList.GetCount();
		//				std::cout << "There are less than 5 AS generated, so all AS will be removed:\n";
		//			}
		//			else {
		//				N = 5;
		//			}
		//			for (int i = 0; i < N; i++)
		//			{
		//				Alien_Soldier* AS = new Alien_Soldier;
		//				int oldHealth = 0;
		//				oldHealth = AS->GetHealth();
		//				AS->setHealth((AS->GetHealth()) * 0.5);
		//				std::cout << "AS Unit picked: ";
		//				AS = ASList.PickUnit();
		//				std::cout << "AS unit's health is halved: \n Old Health = " << oldHealth << " , New Health = " << AS->GetHealth() << endl;
		//				tempASList.AddUnit(AS);
		//				std::cout << "Unit Added to temp list\n";
		//				std::cout << "Temp List: ";
		//				tempASList.PrintAll();
		//			}

		//			std::cout << "All " << N << "AS units added to temp list. Re-insterting them into ASList.\n";
		//			for (int i = 0; i < N; i++)
		//			{
		//				ASList.AddUnit(tempASList.PickUnit());
		//				std::cout << "Element re-inserted\n";
		//				ASList.PrintAll();
		//			}
		//			std::cout << "Re-insertion complete!\n";
		//		}
		//		else {
		//			std::cout << "No Alien Soldiers found!\n";

		//		}
		//	}
		//	else if (X >= 40 && X < 50) {
		//		std::cout << "5 AM will be picked & re-inserted:\n";
		//		if (AMList.GetCount() != 0) {
		//			int N;
		//			RandomGen rand;
		//			int r;
		//			if (AMList.GetCount() < 5)
		//			{
		//				N = AMList.GetCount();
		//				std::cout << "There are less than 5 AM generated, so all AM will be removed:\n";
		//			}
		//			else {
		//				N = 5;
		//			}
		//			for (int i = 0; i < N; i++)
		//			{
		//				r = rand.generateWithinRange(0, AMList.GetCount()-1);
		//				std::cout << r << std::endl;

		//				Alien_Monster* AM;
		//				std::cout << "AM Unit picked: ";
		//				AM = AMList.PickUnit(r);
		//				AMList.PrintAll();
		//				AMList.AddUnit(AM);
		//				std::cout << "Unit Re-inserted: " << AM->GetID() << endl;
		//				AMList.PrintAll();
		//			}
		//		}
		//		else {
		//			std::cout << "No Alien Monsters found!\n";
		//		}
		//	}
		//	else if (X >= 50 && X <= 60) {
		//		std::cout << "6 AD will be picked alternatingly (one rear, one front), and moved to killed list:\n";
		//		if (ADList.GetCount() != 0)
		//		{
		//			int N;
		//			int flag = 0;
		//			if (ADList.GetCount() < 6)
		//			{
		//				N = ADList.GetCount();
		//				std::cout << N << std::endl;
		//				std::cout << "There are less than 6 AD generated, so all AD will be removed:\n";
		//			}
		//			else {
		//				N = 6;
		//			}
		//			for (int i = 0; i < N; i++)
		//			{
		//				Alien_Drones* AD;
		//				if (flag == 0) {
		//					AD = ADList.PickUnitfirst();
		//					flag++;
		//					G1->AddtoKilledList(AD);
		//				 cout<<"First element in drone array is added to killed list\n";
		//				 std::cout << "New Killed List: ";
		//				 G1->PrintKilledList();
		//				}
		//				else if (flag == 1) {
		//					AD = ADList.PickUnitlast();
		//					flag--;
		//					G1->AddtoKilledList(AD);
		//				cout<<"Last element in drone array is added to killed list\n";
		//				std::cout << "New Killed List: ";
		//				G1->PrintKilledList();
		//				ADList.PrintAll();
		//				}
		//			}
		//			cout<<"Final killedList: ";
		//			G1->PrintKilledList();
		//		}
		//		else {
		//			std::cout << "No Alien Drones found!\n";
		//		}

		//	}

		//	std::cout << "X actions are done!!\n\n\n";



		//	std::cout << "OUTPUT SCREEN:\n";
		//	std::cout << "==============Earth Army Alive Units==============\n";
		//	ESList.PrintAll();
		//	ETList.PrintAll();
		//	EGList.PrintAll();

		//	std::cout << "==============Alien Army Alive Units==============\n";
		//	ASList.PrintAll();
		//	AMList.PrintAll();
		//	ADList.PrintAll();

		//	std::cout << "==============Units fighting at current timestep==============\n\n";

		//	std::cout << "==============Killed/Destructed Units==============\n";
		//	G1->PrintKilledList();
		//	std::cout << " Press any key to move to next time step:\n";
		//	std::cin >> Continue;
		//	timestep++;
		//}


	}




