#ifndef TROLL_H
#define TROLL_H

#include "Mob.h"
class Troll :
	public Mob
{
public:
	const int maxHp = 100;
	Troll(int Hp = 100, int sx = 8, int sy = 6, int Loot = 20, int Score = 5, int hpW = 20, int hpH = 5,
		int w = 32, int h = 32, int x = 0, int y = 0, int posx = 0, int posy = 0, string name = "troll");
	
	//Troll(int x, int y);
	~Troll();

	
	
};

#endif