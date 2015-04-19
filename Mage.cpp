#include "Mage.h"


Mage::Mage(int xx, int yy, int Level, int Range, int Price, int Damage, int AttackRate, int bought) : Tower(xx, yy, Level)
{
	range = Range;// 150;
	range0 = Range;
	price = Price; // 150;
	price0 = Price;
	damage = Damage; //20
	attackRate = AttackRate;// 2;
	boughtTower = bought;//0
	level = Level;
	}
//cout << "\t" << range << "\t" << range0 << "\t" << price << "\t" << price0 << "\t" << damage << "\t" << attackRate << "\t" << boughtTower << "\t" << level << "\t" << endl;



bool Mage::attack(int frameTime, int FPS, Troll *troll, Ogre *ogre, Wolf *wolf, Mob* &target, Player &Gracz){
	//Game.frameTime -= 10;
	bool flag = false;
	if (boughtTower == 2){
		if (frameTime % (FPS / attackRate) == 0){
			//cout << "inside: " << Game.frameTime << endl;
			bool pierwszy = true;				// ustalam target
			for (int i = 0; i < 10; i++) {

				if (onRange(troll[i]) && troll[i].hp > 0 && troll[i].release) {
					if (pierwszy){
						pierwszy = false;
						target = &troll[i];
					}
					if (target->monsterPosition.x < troll[i].monsterPosition.x) {
						target = &troll[i];
					}
				}

				if (onRange(wolf[i]) && wolf[i].hp > 0 && wolf[i].release) {
					if (pierwszy){
						pierwszy = false;
						target = &wolf[i];
					}
					if (target->monsterPosition.x < wolf[i].monsterPosition.x) {
						target = &wolf[i];
					}
				}

				if (onRange(ogre[i]) && ogre[i].hp > 0 && ogre[i].release) {
					if (pierwszy){
						pierwszy = false;
						target = &ogre[i];
					}
					if (target->monsterPosition.x < ogre[i].monsterPosition.x) {
						target = &ogre[i];
					}
				}
			}


			if (target != nullptr){
				if (onRangeTarget(target)) {
					///cout << "Target = " << onRangeTarget(target) << endl;
					if (target->hp > 0){
						target->hp -= damage;
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

	if (flag) return true;
	else return false;
}


Mage::~Mage()
{
}



int Mage::returnBought(){
	return boughtTower;
}

void Mage::isBought(){
	boughtTower = 2;
}