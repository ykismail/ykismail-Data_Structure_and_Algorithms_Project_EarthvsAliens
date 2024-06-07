#include "Earth_Gunners.h"
Earth_Gunner::Earth_Gunner(int id, int health, int power, int attackcap) {
	ID = id; Health = health; Power = power; Attack_Capacity = attackcap;
}
Earth_Gunner::Earth_Gunner() {}
float Earth_Gunner::getPri() const{
	return (Health * Power)%100;
}
int Earth_Gunner::GetHealth() {
	return Health;
}
int Earth_Gunner::GetID() {
	return ID;
}
void Earth_Gunner::setID(int id) {
	ID = id;
}
void Earth_Gunner::setHealth(int health)
{
	Health = health;
}
void Earth_Gunner::setPower(int power)
{
	Power = power;
}
void Earth_Gunner::setAttackCap(int AC)
{
	Attack_Capacity = AC;
}

std::ostream& operator<<(std::ostream& os, Earth_Gunner& eg) {
	os << eg.GetID();
	return os;

};




