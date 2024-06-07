#include "Earth_Soldiers.h"
Earth_Soldier::Earth_Soldier() {}
Earth_Soldier::Earth_Soldier(int id=0, int health=0, int power=0, int attackcap=0) {
	ID = id; Health = health; Power = power; Attack_Capacity = attackcap; OriginalHealth = health;
}
int Earth_Soldier::GetHealth() {
	return Health;
}
int Earth_Soldier::GetOriginalHealth() {
	return OriginalHealth;
}
int Earth_Soldier::GetID() {
	return ID;
}
void Earth_Soldier::setID(int id)
{
	ID = id;
}
void Earth_Soldier::setHealth(int health)
{
	Health = health;
}
void Earth_Soldier::setOriginalHealth(int health)
{
	OriginalHealth = health;
}
void Earth_Soldier::setPower(int power)
{
	Power = power;
}
void Earth_Soldier::setAttackCap(int AC)
{
	Attack_Capacity = AC;
}

std::ostream& operator<<(std::ostream& os, Earth_Soldier& es) {
	os << es.GetID();
	return os;

};




