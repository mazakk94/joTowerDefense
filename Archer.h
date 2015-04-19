#ifndef ARCHER_H
#define ARCHER_H

#include "Tower.h"
#include "Player.h"
class Player;

class Archer :
	public Tower
{
public:
	Archer(int x, int y, int Level = 0, int range = 125, int price = 100, int damage = 7, int attackRate = 4, int bought = 0);

	~Archer();

	
	bool attack(int frameTime, int FPS, Troll troll[], Ogre ogre[], Wolf wolf[], Mob* &target, Player &Gracz);


	//virtual
	int returnBought();
	void isBought();
};

#endif