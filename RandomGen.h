#ifndef RANDOMGENERATOR
#define RANDOMGENERATOR
#include "BattleInfo.h"
#include <iostream>
#include <ctime>
#include <random>
using namespace std;

class RandomGen
{
public:
	RandomGen()
	{

	}
	int generateRandProb() //Witin 1-100 inclusive -- For A & B
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dist(1, 100);
		return dist(gen);
		/*srand(time(NULL));
		int r = 1 + rand() % 100;
		return r;*/
	}

	int generateWithinRange(int lowerB, int upperB) //Within 2 given values -- For Ranges
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dist(lowerB, upperB);
		return dist(gen);
		/*srand(time(NULL));
		int r = lowerB + rand() % (upperB - lowerB + 1);
		return r;*/
	}

	int generateEID() //Earth ID generator
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dist(1, 999);
		return dist(gen);
		/*srand(time(NULL));
		int r = 1 + rand() % 999;
		return r;*/
	}

	int generateAID() //Alien ID generator
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dist(2000, 2999);
		return dist(gen);
		/*srand(time(NULL));
		int r = 2000 + rand() % 1000;
		return r;*/
	}
};
#endif