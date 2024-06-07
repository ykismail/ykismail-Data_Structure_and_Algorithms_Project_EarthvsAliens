 //class Units;
#ifndef _GAME
#define _GAME
extern bool SilentMode;
class AMArray;
class ASQueue;
class Game
{
protected:
	LinkedQueue<Units*>* KilledList;
	LinkedQueue<Units*>* UnitsFightingList;
	priQueue<Units>* UnitsTempList;
	priQueue<Units>* UnitsMaintenanceList;
	priQueue<Earth_Soldier>* ESMaintenanceList;
	LinkedQueue<Earth_Tank*>* ETMaintenanceList;
	int destructedESCount = 0;
	int destructedETCount = 0;
	int destructedEGCount = 0;
	int destructedHUCount = 0;
	int destructedASCount = 0;
	int destructedAMCount = 0;
	int destructedADCount = 0;
public:
	int KilledCount = 0;
	int UnitsFightingCount = 0;
	int UMLCount = 0;
	int ESMLCount = 0;
	int ETMLCount = 0;
	int EHCum; //Earth Health Cummulative
	int AHCum; //Alien Health Cummulative
	int EIDCounter = 0; //Earth ID Counter --> Alive units
	int AIDCounter = 0; //Alien ID Counter --> Alive Units
	Game();
	LinkedQueue<Units*>* GetKilledList();
	LinkedQueue<Units*>* GetUnitsFightingList();
	priQueue<Units>* GetUnitsMaintenanceList();
	bool AddtoKilledList(Units* unit,int Td);
	bool AddtoUnitsFightingList(Units* attackingunit);
	void AddtoUnitsMaintenanceList(Units* unit,int t);
	void AddtoTempList(Units* unit,int pri);
	void AddtoTempList(Earth_Soldier* unit);
	void AddtoTempList(Earth_Tank* unit);
	void AddtoUnitsMaintenanceList(Earth_Soldier* ES,int t);
	void AddtoUnitsMaintenanceList(Earth_Tank* ET,int t);
	void AddtoESMaintenanceList(Earth_Soldier* ES,int t);
	void AddtoETMaintenanceList(Earth_Tank* ET,int t);
	void MovefromTemptoUML(int t);
	Units* removefromUFL();
	bool removefromUML();
	Units* removefromTempList();
	Earth_Soldier* removefromESUML();
	Earth_Tank* removefromETUML();
	Units* removefromkilledlist();
	void ClearUnitsFightingList();
	void PrintUnitsMaintenanceList();
	void PrintUnitsFightingList();
	void PrintKilledList();
	int getEHCum();
	int getAHCum();
	int getEIDCounter();
	int getAIDCounter();
	void RunRound();
	priQueue<Earth_Soldier>* GetESMaintenanceList();
	LinkedQueue<Earth_Tank*>* GetETMaintenanceList();
	int getASDCount();
	int getAMDCount();
	int getADDCount();
	int getESDCount();
	int getETDCount();
	int getEGDCount();
	int getHUDCount();
	void setASDCount(int d);
	void setAMDCount(int d);
	void setADDCount(int d);
	void setESDCount(int d);
	void setETDCount(int d);
	void setEGDCount(int d);
	void setHUDCount(int d);
};

#endif
