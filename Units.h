#ifndef UNITS
#define UNITS
#include <string>
#include <iostream>
class Units
{
protected:
	int ID, Health, Power, Attack_Capacity,OriginalHealth;
	int Tj=0, Ta=0, Td=0, Df=0, Db=0, Dd=0,TUML=0;
	// Tj is time joined, Ta is first time getting attacked,Td is time for destruction,TUML is time spent in UML
	// Df is delay of first attack (Ta-Tj), Db time unit was alive (Td-Tj), Dd is time unit got destroyed after first being attacked (Td-Ta)
	std::string Type;
public:
	Units(int id=0, int health=0, int power=0, int attackcap=0, std::string type="a") {
		ID = id; Health = health; Power = power; Attack_Capacity = attackcap; Type = type; OriginalHealth = health;
	}
	//virtual void setdamage();
	//virtual bool AddUnit(T unit)
	//virtual void PrintAll();
	//virtual bool RemoveUnit(T unit) = 0;
	void hit( Units* dfndUnit) {
		int mult = this->getPower() * this->GetHealth();
		int root = sqrt(dfndUnit->GetHealth());
		int damage = (mult / 100) * root;
		int health = dfndUnit->GetHealth() - damage;
		dfndUnit->setHealth(health);
	}
	virtual void Attack(Units* dfndUnit) {};

	int GetID() {
		return this->ID;
	}
	Units* DecrementHealth(Units* unit,int removedHealth) {
		unit = new Units(unit->ID, unit->Health - removedHealth, unit->Power, unit->Attack_Capacity, unit->Type);
		return unit;
	}
	int GetHealth() {
		return this->Health;
	}
	void setHealth(int health) {
		Health = health;
	}
	int getAttckCap() {
		return this->Attack_Capacity;
	}
	int getPower() {
		return this->Power;
	}
	int getTj() {
		return this->Tj;
	}
	void setTj(int TJ) {
		Tj = TJ;
	}
	int getTa() {
		return this->Ta;
	}
	void setTa(int TA) {
		Ta = TA;
	}
	int getTd() {
		return this->Td;
	}
	void setTd(int TD) {
		Td = TD;
	}
	int getTUML() {
		return this->TUML;
	}
	void setTUML(int T) {
		TUML = T;
	}
	int getDf() {
		return this->Df;
	}
	void setDf(int DF) {
		Df = DF;
	}
	int getDb() {
		return this->Db;
	}
	void setDb(int DB) {
		Db = DB;
	}
	int getDd() {
		return this->Dd;
	}
	void setDd(int DD) {
		Dd = DD;
	}
};
#endif
