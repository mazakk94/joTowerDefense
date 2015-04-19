#ifndef PLAYER_H
#define PLAYER_H


#include "Archer.h"
#include "Mage.h"
#include "Cannon.h"


class Archer;
class Mage;
class Cannon;

class Player
{
public:
	int points;
	int money;
	int life;
	// metody


	void buyTower(Tower* &wsk, Archer &tower, int j, bool (&isFree)[12]);
	void buyTower(Tower* &wsk, Mage &tower, int j, bool (&isFree)[12]);
	void buyTower(Tower* &wsk, Cannon &tower, int j, bool (&isFree)[12]);
	bool Lose();
	int howMuchForSell(Tower* &wsk);
	void sellTower(Tower* &wsk, int rBought, int j, bool isFree[]);
	void upgradeTower(Tower* &wsk);
	Player(int score = 0, int money = 600, int life = 5);
	~Player();
};

#endif