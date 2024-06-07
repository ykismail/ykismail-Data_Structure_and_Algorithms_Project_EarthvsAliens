#include "Heal_Unit.h"

Heal_Unit::Heal_Unit() {}
Heal_Unit::Heal_Unit(int id,int health,int power, int attackcap) {
	ID = id; Power = power; Attack_Capacity = attackcap;
}
int Heal_Unit::GetID() {
	return this->ID;
}
void Heal_Unit::HealUnit(Units* unit) { 
	int Heal;
	int num = this->getPower() * this->GetHealth() / 100;
	int den = sqrt(unit->GetHealth());
	Heal = num / den;
	//MY_COUT(Heal << std::endl);
	unit->setHealth(unit->GetHealth() + Heal);
}
void Heal_Unit::setID(int id)
{
	ID = id;
}
void Heal_Unit::setHealth(int health)
{
	Health = health;
}
void Heal_Unit::setPower(int power)
{
	Power = power;
}
void Heal_Unit::setAttackCap(int AC)
{
	Attack_Capacity = AC;
}