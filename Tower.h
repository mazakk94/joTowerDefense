#ifndef TOWER_H
#define TOWER_H

#include <iostream>
using namespace std;

#include "Troll.h"
#include "Ogre.h"
#include "Wolf.h"


class Player;
class Troll;
class Ogre;
class Wolf;

class Tower
{

protected:

	int range;
	int range0;
	int price;
	int price0; //poczatkowa cena
	float damage;
	int attackRate;
	int x;				// wspolrzedne srodka od którego bêdzie liczony zasiêg
	int y;
	int boughtTower; // flaga zakupionej wie¿y
	int level;
public:

	Tower(int x, int y, int Level); // liczenie zasiegu w kontruktorze 
	Tower(int boughtTower);
	~Tower();
	
	
	int &returnBought();
	bool onRangeTarget(Mob* mob);
	bool onRange(Troll mob);
	bool onRange(Wolf mob);
	bool onRange(Ogre mob);

	void isSold();
	void Price0();
	void Range0();
	void Level0();
	void upgrade();
	int returnPrice(int Level);
	int returnLevel();


	virtual bool attack(int frameTime, int FPS, Troll troll[], Ogre ogre[], Wolf wolf[], Mob* &target, Player &Gracz) = 0;
	virtual void isBought() = 0;
	
};

#endif