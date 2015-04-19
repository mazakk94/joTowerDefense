#include "Cannon.h"


Cannon::Cannon(int xx, int yy, int Level, int Range, int Price, int Damage, int AttackRate, int bought) : Tower(xx, yy, Level)
{
	range = Range;// 150;
	range0 = Range;
	price = Price; // 150;
	price0 = Price;
	damage = Damage; //20
	attackRate = AttackRate;// 2;
	boughtTower = bought;//0
	level = Level;
	splash = splash0;
	//cout << "\t" << range << "\t" << range0 << "\t" << price << "\t" << price0 << "\t" << damage << "\t" << attackRate << "\t" << boughtTower << "\t" << level << "\t" << endl;

}

bool Cannon::onSplash(Mob* &target, Troll &troll, int i){
	//cout << "Splesz = " << splash << endl;
	//cout << "splesz trolla" << endl;
	int x = troll.monsterPosition.x;
	int y = troll.monsterPosition.y;
	int p = target->monsterPosition.x + target->monsterPosition.w / 2;
	int q = target->monsterPosition.y + target->monsterPosition.h / 2;
	int w = troll.monsterPosition.w;
	int h = troll.monsterPosition.h;

	//cout << "p = " << p << endl;
	//cout << "q = " << q << endl;

	if (pow((x - p), 2) + pow((y - q), 2) <= pow(splash, 2) ||
		pow((x + w - p), 2) + pow((y - q), 2) <= pow(splash, 2) ||
		pow((x - p), 2) + pow((y + h - q), 2) <= pow(splash, 2) ||
		pow((x + w - p), 2) + pow((y + h - p), 2) <= pow(splash, 2)){
		cout << "target: " << target->name << "\tsplesz : troll[" << i << "]" << endl;
		return true;
	}
	else
		return false;
}

bool Cannon::onSplash(Mob* &target, Wolf &wolf, int i){
	//cout << "splesz wolfa" << endl;
	int x = wolf.monsterPosition.x;
	int y = wolf.monsterPosition.y;
	int p = target->monsterPosition.x + target->monsterPosition.w / 2;
	int q = target->monsterPosition.y + target->monsterPosition.h / 2;
	int w = wolf.monsterPosition.w;
	int h = wolf.monsterPosition.h;

	if (pow((x - p), 2) + pow((y - q), 2) <= pow(splash, 2) ||
		pow((x + w - p), 2) + pow((y - q), 2) <= pow(splash, 2) ||
		pow((x - p), 2) + pow((y + h - q), 2) <= pow(splash, 2) ||
		pow((x + w - p), 2) + pow((y + h - p), 2) <= pow(splash, 2)){
		cout << "target: " << target->name << "\tsplesz : wolf[" << i << "]" << endl;
		return true;
	}
	else
		return false;
}

bool Cannon::onSplash(Mob* &target, Ogre &ogre, int i){
	//cout << "splesz ogra" << endl;
	int x = ogre.monsterPosition.x;
	int y = ogre.monsterPosition.y;
	int p = target->monsterPosition.x + target->monsterPosition.w / 2;
	int q = target->monsterPosition.y + target->monsterPosition.h / 2;
	int w = ogre.monsterPosition.w;
	int h = ogre.monsterPosition.h;

	//	cout << "p = " << p << endl;
	//	cout << "q = " << q << endl;

	if (pow((x - p), 2) + pow((y - q), 2) <= pow(splash, 2) ||
		pow((x + w - p), 2) + pow((y - q), 2) <= pow(splash, 2) ||
		pow((x - p), 2) + pow((y + h - q), 2) <= pow(splash, 2) ||
		pow((x + w - p), 2) + pow((y + h - p), 2) <= pow(splash, 2)){
		cout << "target: " << target->name << "\tsplesz : ogre[" << i << "]" << endl;
		return true;
	}
	else
		return false;
}

bool Cannon::attack(int frameTime, int FPS, Troll *troll, Ogre *ogre, Wolf *wolf, Mob* &target, Player &Gracz){
	//Game.frameTime -= 10;
	//cout << "inside: " << Game.frameTime << endl;
	bool flag = false;
	if (boughtTower == 3){
		if (frameTime % (FPS / attackRate) == 0){
			//cout << "inside: " << Game.frameTime << endl;
			bool pierwszy = true;				// ustalam target
			for (int i = 0; i < 10; i++) {

				if (onRange(troll[i]) && troll[i].hp > 0 && troll[i].release) {
					if (pierwszy){
						pierwszy = false;
						target = &troll[i];
						cout << "troll " << i << endl;
					}
					if (target->monsterPosition.x < troll[i].monsterPosition.x) {
						target = &troll[i];
						cout << "troll " << i << endl;
					}
				}

				if (onRange(wolf[i]) && wolf[i].hp > 0 && wolf[i].release) {
					if (pierwszy){
						pierwszy = false;
						target = &wolf[i];
						cout << "wolf " << i << endl;
					}
					if (target->monsterPosition.x < wolf[i].monsterPosition.x) {
						target = &wolf[i];
						cout << "wolf " << i << endl;
					}
				}

				if (onRange(ogre[i]) && ogre[i].hp > 0 && ogre[i].release) {
					if (pierwszy){
						pierwszy = false;
						target = &ogre[i];
						cout << "ogre " << i << endl;
					}
					if (target->monsterPosition.x < ogre[i].monsterPosition.x) {
						target = &ogre[i];
						cout << "ogre " << i << endl;
					}
				}
			}


			if (target != nullptr){
				if (onRangeTarget(target)) {
					if (target->hp > 0){
						//cout <<  endl;
						target->hp -= damage;
						for (int i = 0; i < 10; i++){									// SPLASH
							if (troll[i].returnHp()>0 && troll[i].release && onSplash(target, troll[i], i)){
								troll[i].hp -= damage;
								cout << "Troll " << i << "zgarnal hita" << endl;
							}
							if (wolf[i].returnHp()>0 && wolf[i].release && onSplash(target, wolf[i], i)){
								wolf[i].hp -= damage;
								cout << "Wolf " << i << "zgarnal hita" << endl;
							}
							if (ogre[i].returnHp()>0 && ogre[i].release && onSplash(target, ogre[i], i)){
								ogre[i].hp -= damage;
								cout << "Ogre " << i << "zgarnal hita" << endl;
							}

						
						}

						if (target->hp <= 0){
							cout << "Zabiles " << target->name << endl;
							Gracz.money += target->returnLoot();
							Gracz.points += target->returnScore();
							cout << "Money : " << Gracz.money << endl << "Points: " << Gracz.points << endl;
						}
						//cout << "HP = " << target->returnHp() << endl;
						flag = true;
					}
					else flag = false;
				}
				else {
					target = nullptr;	// zerujemy cel jak nie jest ju¿ w zasiêgu
					flag = false;
				}
			}
		}
	}

	return flag;
}

void Cannon::draw(){

}

void Cannon::upgrade(){

}

Cannon::~Cannon()
{
}

int Cannon::returnBought(){
	return boughtTower;
}

void Cannon::isBought(){
	boughtTower = 3;
}