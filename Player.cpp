#include "Player.h"

using namespace std; 

Player::Player(int Score, int Money, int Life)
{
	points = Score;
	money = Money;
	life = Life;
}


void Player::buyTower(Tower* &wsk, Archer &tower, int j, bool(&isFree)[12]) {
	if (money >= tower.returnPrice(0)){
		money -= tower.returnPrice(0);

		tower.isBought();
		wsk = &tower;
		//wsk->isBought();
		isFree[j] = false; // blokujemy zakup wie¿y w danym miejscu 
		cout << "Kupiles wieze archer!" << endl;
		cout << "Money: " << money << endl;
		
	}
	else {
		cout << "Nie masz hajsu!" << endl;
		cout << "Money: " << money << endl;
	}
}

void Player::buyTower(Tower* &wsk, Mage &tower, int j, bool(&isFree)[12]){
	if (money >= tower.returnPrice(0)){
		money -= tower.returnPrice(0);

		tower.isBought();
		wsk = &tower;
		isFree[j] = false; // blokujemy zakup wie¿y w danym miejscu 
		cout << "Kupiles wieze mage!" << endl;
		cout << "Money: " << money << endl;
	}
	else {
		cout << "Nie masz hajsu!" << endl;
		cout << "Money: " << money << endl;
	}
}

void Player::buyTower(Tower* &wsk, Cannon &tower, int j, bool(&isFree)[12]){
	if (money >= tower.returnPrice(0)){
		money -= tower.returnPrice(0);

		tower.isBought();
		wsk = &tower;
		//wsk->isBought();
		isFree[j] = false; // blokujemy zakup wie¿y w danym miejscu 
		cout << "Kupiles wieze cannon!" << endl;
		cout << "Money: " << money << endl;
	}
	else {
		cout << "Nie masz hajsu!" << endl;
		cout << "Money: " << money << endl;
	}
}

bool Player::Lose(){
	return (life <= 0);

}

void Player::sellTower(Tower* &wsk, int rBought, int j, bool isFree[]){
	wsk -> isSold(); // boughtTower = 0;

	for (int i = 0; i <= wsk->returnLevel(); i++){
		money += (wsk->returnPrice(i)) / 2;
	}

	isFree[j] = true;
	wsk -> Price0();
	wsk -> Range0();
	wsk -> Level0();
	wsk = nullptr;
	cout << "Sprzedales wieze z j = " << j << endl;
	cout << "Money = " << money << endl;
	

}

int Player::howMuchForSell(Tower* &wsk){
	int howMuch = 0;
	for (int i = 0; i <= wsk->returnLevel(); i++){
		 howMuch += (wsk->returnPrice(i)) / 2;
	}
	return howMuch;
}

void Player::upgradeTower(Tower* &wsk) {
	if (wsk->returnLevel() < 6){
		if (money >= wsk->returnPrice(wsk->returnLevel() + 1)){
			wsk->upgrade();
			money -= wsk->returnPrice(wsk->returnLevel());
			cout << endl;
			cout << "Money: " << money << endl;
		}
		else cout << "Nie stac cie na ulepszenie!" << endl;
	}
}

Player::~Player(){
}
