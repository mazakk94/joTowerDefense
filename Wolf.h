#ifndef WOLF_H
#define WOLF_H

#include "Mob.h"
class Wolf :
	public Mob
{
public:
	const int maxHp = 30;
	Wolf(int Hp = 30, int sx = 12, int sy = 9, int Loot = 10, int Score = 3, int hpW = 20, int hpH = 5,
		int w = 45, int h = 25, int x = 0, int y = 0, int posx = 0, int posy = 0, string Name = "wolf");
	~Wolf();

};

#endif