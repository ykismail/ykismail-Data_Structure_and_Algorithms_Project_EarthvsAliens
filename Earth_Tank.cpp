#include "Earth_Tank.h"
Earth_Tank::Earth_Tank(int id, int health, int power, int attackcap) {
	ID = id; Health = health; Power = power; Attack_Capacity = attackcap; OriginalHealth = health;
}
Earth_Tank::Earth_Tank() {}

int Earth_Tank::GetHealth() {
	return Health;
}
int Earth_Tank::GetOriginalHealth() {
	return OriginalHealth;
}
int Earth_Tank::GetID() {
	return ID;
}
void Earth_Tank::setID(int id)
{
	ID = id;
}
void Earth_Tank::setHealth(int health)
{
	Health = health;
}
void Earth_Tank::setOriginalHealth(int health)
{
	OriginalHealth = health;
}
void Earth_Tank::setPower(int power)
{
	Power = power;
}
void Earth_Tank::setAttackCap(int AC)
{
	Attack_Capacity = AC;
}

std::ostream& operator<<(std::ostream& os, Earth_Tank& et) {
	os << et.GetID();
	return os;

};



