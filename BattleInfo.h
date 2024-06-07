#ifndef BATTLEINFO
#define BATTLEINFO
#include <iostream>
using namespace std;
#include <fstream>
#include <string>
class BattleInfo
{
public:
	int N, ES, ET, EG, HU, AS, AM, AD, prob;
	int EP1, EH1, EAC1, AP1, AH1, AAC1, EH2, EP2, EAC2, AP2, AH2, AAC2;

	BattleInfo() {
		N = 0; ES = 0; ET = 0; EG = 0; HU = 0; AS = 0; AM = 0; AD = 0; prob = 0;
		EP1 = 0; EH1 = 0; EAC1 = 0; AP1 = 0; AH1 = 0; AAC1 = 0; EH2 = 0; EP2 = 0; EAC2 = 0; AP2 = 0; AH2 = 0; AAC2 = 0;
	};

	void setArmyUnits(int n) { N = n; };

	void setProb(int p)
	{
		prob = p;
	};


	void setES(int es) //Earth Soldiers Setter
	{
		ES = es;

	};
	void setET(int et) //Earth Tanks Setter
	{
		ET = et;

	};
	void setEG(int eg) //Earth Gunnery Setter
	{
		EG = eg;

	};
	void setHU(int hu) {
		HU = hu;
	}
	void setEP(int ep1, int ep2) //Earth Power Range Setter
	{
		EP1 = ep1;
		EP2 = ep2;
	};
	void setEH(int eh1, int eh2) //Earth Health Range Setter
	{
		EH1 = eh1;
		EH2 = eh2;
	};
	void setEAC(int eac1, int eac2) //Earth Attack Capacity Range Setter
	{
		EAC1 = eac1;
		EAC2 = eac2;
	};
	void setAS(int as) //Alien Soldier Setter
	{
		AS = as;
	};
	void setAD(int ad) //Alien Drones Setter
	{
		AD = ad;
	};
	void setAM(int am) //Alien Monster Setter
	{
		AM = am;
	};
	void setAP(int ap1, int ap2) //Alien Power Range Setter
	{
		AP1 = ap1;
		AP2 = ap2;
	};
	void setAH(int ah1, int ah2) //Alien Health Range Setter
	{
		AH1 = ah1;
		AH2 = ah2;
	};
	void setAAC(int aac1, int aac2) //Alien Attack Capacity Setter
	{
		AAC1 = aac1;
		AAC2 = aac2;
	};

	int GetProb()
	{
		return prob;
	}

	int GetArmyUnits()
	{
		return N;
	}

	int GetEsoliders()
	{
		return ES;
	};

	int GetAsoliders() {
		return AS;
	};
	int GetEG()
	{
		return EG;
	};

	int GetET()
	{
		return ET;
	};

	int GetAM() {
		return AM;
	};

	int GetAD() {
		return AD;
	};

	int GetEP1() {
		return EP1;
	};

	int GetEH1() {
		return EH1;
	};

	int GetEAC1() {
		return EAC1;
	};

	int GetAP1() {
		return AP1;
	};

	int GetAH1() {
		return AH1;
	};

	int GetAAC1() {
		return AAC1;
	};

	int GetEP2() {
		return EP2;
	};

	int GetEH2() {
		return EH2;
	};

	int GetEAC2() {
		return EAC2;
	};

	int GetAP2() {
		return AP2;
	};

	int GetAH2() {
		return AH2;
	};

	int GetAAC2() {
		return AAC2;
	};

	int GetHU() {
		return HU;
	};

	~BattleInfo() {};
};
#endif
