#include "Alien_Monsters.h"
Alien_Monster::Alien_Monster() {}
Alien_Monster::Alien_Monster(int id,int health,int power,int attackcap) {
	ID = id; Health = health; Power = power; Attack_Capacity = attackcap;
}
int Alien_Monster::GetHealth() {
	return Health;
}
int Alien_Monster::GetID() {
	return ID;
}
void Alien_Monster::setID(int id)
{
	ID = id;
}
void Alien_Monster::setHealth(int health)
{
	Health = health;
}
void Alien_Monster::setPower(int power)
{
	Power = power;
}
void Alien_Monster::setAttackCap(int AC)
{
	Attack_Capacity = AC;
}

std::ostream& operator<<(std::ostream& os, Alien_Monster& am) {
	os << am.GetID();
	return os;

};