#include "Tower.h"


Tower::Tower(int xx, int yy, int Level)
{
	x = xx + 25;
	y = yy + 25;
	level = Level;
}


Tower::~Tower()
{
}

Tower::Tower(int BoughtTower){
	boughtTower = BoughtTower;
}

int &Tower::returnBought(){
	return boughtTower;
}

void Tower::isSold(){
	boughtTower = 0;
}

void Tower::Price0(){
	price = price0;
}

void Tower::Range0(){
	range = range0;
}

void Tower::Level0(){
	level = 0;
}

void Tower::upgrade(){
	level++;
	range += 10;
	damage *= 1.5;
	price = price0 + (level - 1)*(price / 2);
}


bool Tower::onRangeTarget(Mob* mob) {			// z równania okrêgu
	if (pow((mob->monsterPosition.x - x), 2) + pow((mob->monsterPosition.y - y), 2) <= pow(range, 2)  //lewy gorny 
		|| pow((mob->monsterPosition.x - x + mob->monsterPosition.w), 2) + pow((mob->monsterPosition.y - y), 2) <= pow(range, 2) // prawy gorny
		|| pow((mob->monsterPosition.x - x), 2) + pow((mob->monsterPosition.y - y + mob->monsterPosition.h), 2) <= pow(range, 2) // lewy dolny
		|| pow((mob->monsterPosition.x - x + mob->monsterPosition.w), 2) + pow((mob->monsterPosition.y - y + mob->monsterPosition.h), 2) <= pow(range, 2) // prawy dolny
		)
		return true;
	else
		return false;
}


bool Tower::onRange(Wolf mob) {
	if (pow((mob.monsterPosition.x - x), 2) + pow((mob.monsterPosition.y - y), 2) <= pow(range, 2)  //lewy gorny 
		|| pow((mob.monsterPosition.x - x + mob.monsterPosition.w), 2) + pow((mob.monsterPosition.y - y), 2) <= pow(range, 2) // prawy gorny
		|| pow((mob.monsterPosition.x - x), 2) + pow((mob.monsterPosition.y - y + mob.monsterPosition.h), 2) <= pow(range, 2) // lewy dolny
		|| pow((mob.monsterPosition.x - x + mob.monsterPosition.w), 2) + pow((mob.monsterPosition.y - y + mob.monsterPosition.h), 2) <= pow(range, 2) // prawy dolny
		)
		return true;
	else
		return false;
}

bool Tower::onRange(Troll mob) {
	if (pow((mob.monsterPosition.x - x), 2) + pow((mob.monsterPosition.y - y), 2) <= pow(range, 2)  //lewy gorny 
		|| pow((mob.monsterPosition.x - x + mob.monsterPosition.w), 2) + pow((mob.monsterPosition.y - y), 2) <= pow(range, 2) // prawy gorny
		|| pow((mob.monsterPosition.x - x), 2) + pow((mob.monsterPosition.y - y + mob.monsterPosition.h), 2) <= pow(range, 2) // lewy dolny
		|| pow((mob.monsterPosition.x - x + mob.monsterPosition.w), 2) + pow((mob.monsterPosition.y - y + mob.monsterPosition.h), 2) <= pow(range, 2) // prawy dolny
		)
		return true;
	else
		return false;
}

bool Tower::onRange(Ogre mob) {
	if (pow((mob.monsterPosition.x - x), 2) + pow((mob.monsterPosition.y - y), 2) <= pow(range, 2)  //lewy gorny 
		|| pow((mob.monsterPosition.x - x + mob.monsterPosition.w), 2) + pow((mob.monsterPosition.y - y), 2) <= pow(range, 2) // prawy gorny
		|| pow((mob.monsterPosition.x - x), 2) + pow((mob.monsterPosition.y - y + mob.monsterPosition.h), 2) <= pow(range, 2) // lewy dolny
		|| pow((mob.monsterPosition.x - x + mob.monsterPosition.w), 2) + pow((mob.monsterPosition.y - y + mob.monsterPosition.h), 2) <= pow(range, 2) // prawy dolny
		)
		return true;
	else
		return false;
}

int Tower::returnPrice(int Level){
	if (Level > 0)
		return price0 + (Level - 1)*(price0 / 2);
	else return price0;
}

int Tower::returnLevel(){
	return level;
}



//template <class Typ>
//bool Tower::onRangeTarget(Typ mob) {			// z równania okrêgu
//	if (pow((mob->monsterPosition.x - x), 2) + pow((mob->monsterPosition.y - y), 2) <= pow(range, 2)  //lewy gorny 
//		|| pow((mob->monsterPosition.x - x + mob->monsterPosition.w), 2) + pow((mob->monsterPosition.y - y), 2) <= pow(range, 2) // prawy gorny
//		|| pow((mob->monsterPosition.x - x), 2) + pow((mob->monsterPosition.y - y + mob->monsterPosition.h), 2) <= pow(range, 2) // lewy dolny
//		|| pow((mob->monsterPosition.x - x + mob->monsterPosition.w), 2) + pow((mob->monsterPosition.y - y + mob->monsterPosition.h), 2) <= pow(range, 2) // prawy dolny
//		)
//		return true;
//	else
//		return false;
//}
//
//template <class Typ>
//bool Tower::onRange(Typ mob) {
//	if (pow((mob.monsterPosition.x - x), 2) + pow((mob.monsterPosition.y - y), 2) <= pow(range, 2)  //lewy gorny 
//		|| pow((mob.monsterPosition.x - x + mob.monsterPosition.w), 2) + pow((mob.monsterPosition.y - y), 2) <= pow(range, 2) // prawy gorny
//		|| pow((mob.monsterPosition.x - x), 2) + pow((mob.monsterPosition.y - y + mob.monsterPosition.h), 2) <= pow(range, 2) // lewy dolny
//		|| pow((mob.monsterPosition.x - x + mob.monsterPosition.w), 2) + pow((mob.monsterPosition.y - y + mob.monsterPosition.h), 2) <= pow(range, 2) // prawy dolny
//		)
//		return true;
//	else
//		return false;
//}
