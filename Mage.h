#ifndef MAGE_H
#define MAGE_H

#include "Tower.h"
#include "Player.h"
class Player;


class Mage :
	public Tower
{
public:
	Mage(int x, int y, int Level = 0, int range = 175, int price = 150, int damage = 20, int attackRate = 2, int bought = 0);
	~Mage();

	bool attack(int frameTime, int FPS, Troll troll[], Ogre ogre[], Wolf wolf[], Mob* &target, Player &Gracz);

	

	int returnBought();
	void isBought();
};

#endif