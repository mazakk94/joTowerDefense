#ifndef OGRE_H
#define OGRE_H

#include "Mob.h"
class Ogre :
	public Mob
{
public:
	const int maxHp = 500;
	Ogre(int Hp = 500, int sx = 4, int sy = 3, int Loot = 50, int Score = 20, int hpW = 20, int hpH = 5,
		int w = 64, int h = 64, int x = 0, int y = 0, int posx = 0, int posy = 0, string name = "ogre");
	//500, 4, 3, 30, 20, 20, 5, 64, 64, 0, 0, 0, 0
	~Ogre();
	

};


#endif