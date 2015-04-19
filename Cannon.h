#ifndef CANNON_H
#define CANNON_H

#include "Tower.h"
#include "Player.h"

class Player;



class Cannon :
	public Tower
{
protected:
	int splash0 = 50;
	int splash;
public:
	Cannon(int x, int y, int Level = 0, int range = 100, int price = 200, int damage = 30, int attackRate = 1, int bought = 0);
	~Cannon();

	bool attack(int frameTime, int FPS, Troll troll[], Ogre ogre[], Wolf wolf[], Mob* &target, Player &Gracz);

	void draw();
	void upgrade();
	
	bool onSplash(Mob* &target, Troll &troll,int i);
	bool onSplash(Mob* &target, Ogre &ogre, int i);
	bool onSplash(Mob* &target, Wolf &wolf, int i);

	int returnBought();
	void isBought();
};

#endif