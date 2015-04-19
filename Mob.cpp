#include "Mob.h"


Mob::Mob(int x)
{
	monsterPosition.x = x;
	monsterPosition.y = x;
}

Mob::Mob(){

}

int Mob::returnLoot(){
	cout << "Loot = " <<  loot << endl;
	return loot;
}

int Mob::returnScore(){
	return score;
}

Mob::~Mob()
{
}

int Mob::returnHp(){
	return hp;
}

bool Mob::runAway(int &Gracz_life){
	if (monsterPosition.x >= 640) {
		Gracz_life--;
		cout << "Lives: " << Gracz_life << endl;
		release = false; 
		//cout << "ucieczka " << name << "!\n";
		escaped = true;
		return true;
	}
	else
		return false;
}
