#include "Wolf.h"

Wolf::Wolf(int Hp, int sx, int sy, int Loot, int Score, int hpW, int hpH, int w, int h, int x, int y, int posx, int posy, string Name)
{
	hp = Hp;
	speed.x = sx; // speed init
	speed.y = sy;
	loot = Loot;
	//cout << "Wolf.loot = " << loot << endl;
	score = Score;
	monsterPosition.w = w;
	monsterPosition.h = h;
	monsterPosition.x = posx; //160
	monsterPosition.y = posy; //120
	monster.x = x;
	monster.y = y;
	monster.w = w;
	monster.h = h;
	hpBar.x = x;
	hpBar.y = y;
	hpBar.w = hpW;
	hpBar.h = hpH;
	hpBarPosition.x = posx + 15;
	hpBarPosition.y = posy;
	hpBarPosition.w = hpW;
	hpBarPosition.h = hpH;
	release = posx;//0
	name = Name;
	escaped = posx;//0
}

Wolf::~Wolf()
{
}

