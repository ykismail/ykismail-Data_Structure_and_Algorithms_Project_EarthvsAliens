#include "Alien_Soldier.h"

Alien_Soldier::Alien_Soldier() {}

Alien_Soldier::Alien_Soldier(int id,int health,int power,int attackcap) {
	ID = id; Health = health;  Power = power;  Attack_Capacity = attackcap;
}
int Alien_Soldier::GetHealth() {
	return Health;
}
int Alien_Soldier::GetID() {
	return ID;
}

void Alien_Soldier::setID(int id)
{
	ID = id;
}
void Alien_Soldier::setHealth(int health)
{
	Health = health;
}
void Alien_Soldier::setPower(int power)
{
	Power = power;
}
void Alien_Soldier::setAttackCap(int AC)
{
	Attack_Capacity = AC;
}

std::ostream& operator<<(std::ostream& os, Alien_Soldier& as) {
	os << as.GetID();
	return os;

};