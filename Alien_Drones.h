#pragma once
#ifndef ALIENDRONES
#define ALIENDRONES

#include "Units.h"
#include <iostream>


class Alien_Drones : public Units
    
{public:
    Alien_Drones();
    Alien_Drones(int id, int health, int power, int attackcap);
    int GetHealth();
    int GetID();
  
    void setID(int id);
    void setHealth(int health);
    void setPower(int power);
    void setAttackCap(int AC);
};
#endif

