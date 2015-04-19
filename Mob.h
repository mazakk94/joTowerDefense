#ifndef MOB_H
#define MOB_H

#include "SdlInit.h"
#include <string>
#include <iostream>

using namespace std;

class Mob : public SdlInit
{
protected:
	
	int loot;
	int score;

public:
	string name;
	int hp;
	bool release;
	int escaped;// = false
	
	bool runAway(int &Gracz_life);
	int returnHp();
	int returnLoot();
	int returnScore();

	//bool onSplash(Mob* monster);

	struct Speed {
		int x;
		int y;
	};
	Speed speed;

	Mob(int x);
	Mob();
	~Mob();
};

#endif