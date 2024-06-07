#include "Alien_Drones.h"
#include <ostream>
Alien_Drones::Alien_Drones() {}
Alien_Drones::Alien_Drones(int id, int health, int power, int attackcap) {
	ID = id; Health = health; Power = power; Attack_Capacity = attackcap;
}
int Alien_Drones::GetHealth() {
	return Health;
}
int Alien_Drones::GetID() {
	return ID;
}

void Alien_Drones::setID(int id)
{
	ID = id;
}
void Alien_Drones::setHealth(int health)
{
	Health = health;
}
void Alien_Drones::setPower(int power)
{
	Power = power;
}
void Alien_Drones::setAttackCap(int AC)
{
	Attack_Capacity = AC;
}


std::ostream& operator<<(std::ostream& os, Alien_Drones& ad) {
	os << ad.GetID();
	return os;

};