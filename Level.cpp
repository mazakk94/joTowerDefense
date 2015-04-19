#include "Level.h"

using namespace std;

Level::Level()
{

}



bool Level::releaseMobs(Troll *troll, Ogre *ogre, Wolf *wolf, Player &Gracz){
	bool end = false;
	if (frameTime % 6 == 0){// (FPS / frameTime == 12){
		for (int i = 0; i < 10; i++){
			if (wolf[i].hp>0 && wolf[i].release && !wolf[i].runAway(Gracz.life)){

				wolf[i].monsterPosition.x += wolf[i].speed.x;
				wolf[i].monsterPosition.y += wolf[i].speed.y;
				wolf[i].hpBarPosition.x += wolf[i].speed.x;
				wolf[i].hpBarPosition.y += wolf[i].speed.y;
			}

		}
		for (int i = 0; i < 10; i++){
			if (troll[i].hp>0 && troll[i].release && !troll[i].runAway(Gracz.life)){

				troll[i].monsterPosition.x += troll[i].speed.x;
				troll[i].monsterPosition.y += troll[i].speed.y;
				troll[i].hpBarPosition.x += troll[i].speed.x;
				troll[i].hpBarPosition.y += troll[i].speed.y;
			}
		}

		for (int i = 0; i < 10; i++){
			if (ogre[i].hp > 0 && ogre[i].release && !ogre[i].runAway(Gracz.life)){

				ogre[i].monsterPosition.x += ogre[i].speed.x;
				ogre[i].monsterPosition.y += ogre[i].speed.y;
				ogre[i].hpBarPosition.x += ogre[i].speed.x;
				ogre[i].hpBarPosition.y += ogre[i].speed.y;
			}
		}

		if (released){ // flaga released sprawdza czy zostaly wszystkie wypuszczone
			for (int i = 0; i < 10; i++){
				if ((ogre[i].hp <= 0 || ogre[i].escaped || !ogre[i].release) && (troll[i].hp <= 0 || troll[i].escaped || !troll[i].release) && (wolf[i].hp <= 0 || wolf[i].escaped || !wolf[i].release)){
					end = true;
					//cout << "tru\t";	// jak wszystkie sa true to zabilismy potwory LUB uciekly LUB nie zostaly wypuszczone
				}
				else {
					end = false;		// jak którys z potworów ma hp>0 || jeszcze biegnie i nie uciek³ to false i przerywamy sprawdzanie
					return end;
				}
			}
		}

	}
	
	return end;
}

void Level::resetMobs(Troll *troll, Ogre *ogre, Wolf *wolf){
	u = w = 0;
	for (int i = 0; i < 10; i++){
		licznik = 1; // licznik od nowa
		released = false; // flaga, ¿e jeszcze nie wszystkich wypuœciliœmy
		troll[i].Troll::Troll(100, 8, 6, 20, 5, 20, 5, 32, 32, 0, 0, 0, 0);// 100, 8, 6, 10, 5, 20, 5, 32, 32, 0, 0, 0, 0);
		wolf[i].Wolf::Wolf(30, 12, 9, 10, 10, 20, 5, 45, 25, 0, 0, 0, 0);// 30, 12, 9, 10, 10, 20, 5, 45, 25, 0, 0, 0, 0);
		ogre[i].Ogre::Ogre(500, 4, 3, 30, 20, 20, 5, 64, 64, 0, 0, 0, 0);// 500, 4, 3, 30, 20, 20, 5, 64, 64, 0, 0, 0, 0);
	}
}

Level::~Level()
{
		//SDL_DestroyWindow(window);
		////SDL_FreeSurface(windowSurface);
		//SDL_DestroyRenderer(renderTarget);
	//	SDL_DestroyTexture(trollImage);
	//	SDL_DestroyTexture(wolfImage);
//		SDL_DestroyTexture(hoverImage);
//		SDL_DestroyTexture(backgroundImage);
//		backgroundImage = nullptr;
////		trollImage = nullptr;
	//	wolfImage = nullptr;
	//	ogreImage = nullptr;
	/*	renderTarget = nullptr;
		window = nullptr;*/
}

void Level::counter(Troll *troll, Ogre *ogre, Wolf *wolf, int wave){

	if (frameTime % 60 == 0 && w < 3) {
		switch (wave){
		case 1:	// pierwsza fala
		{
					if (licznik < 6){
						switch (licznik){
						case 1:
							u = 0;
							w = 0;
							break;
						case 2:
							u = 1;
							w = 0;
							break;
						case 3:
							u = 0;
							w = 1;
							break;
						case 4:
							u = 2;
							w = 0;
							break;
						case 5:
							u = 3;
							w = 0;
						}
						licznik++;

					}
					else
						released = true;	// potrzebne aby zaczal sprawdzac czy mozna pokazac przycisk do wypuszczania kolejnej fali
					break;
		}
		case 2:		// druga fala
		{
						if (licznik < 6){
							switch (licznik){
							case 1:
								u = 0;
								w = 1;
								break;
							case 2:
								u = 1;
								w = 1;
								break;
							case 3:
								u = 0;
								w = 0;
								break;
							case 4:
								u = 1;
								w = 0;
								break;
							case 5:
								u = 2;
								w = 1;
								break;
							}
							licznik++;
							break;
						}
						else
							released = true;	///
						break;
		}
		case 3:
		{
				  if (licznik <= 11){
					  switch (licznik){
					  case 1:
						  u = 0;
						  w = 0;
						  break;
					  case 2:
						  u = 1;
						  w = 0;
						  break;
					  case 3:
						  u = 2;
						  w = 0;
						  break;
					  case 4:
						  u = 3;
						  w = 0;
						  break;
					  case 5:
						  u = 4;
						  w = 0;
						  break;
					  case 6:
						  u = 0;
						  w = 1;
						  break;
					  case 7:
						  u = 1;
						  w = 1;
						  break;
					  case 8:
						  u = 2;
						  w = 1;
						  break;
					  case 9:
						  u = 3;
						  w = 1;
						  break;
					  case 10:
						  u = 4;
						  w = 1;
						  break;
					  case 11:
						  u = 0;
						  w = 2;
						  break;
					  }
					  licznik++;
					  break;
				  }
				  else
					  released = true;	///
				  break;
		}
		case 4:
		{
				  if (licznik <= 15){
					  switch (licznik){
					  case 1:
						  u = 0;
						  w = 0;
						  break;
					  case 2:
						  u = 1;
						  w = 0;
						  break;
					  case 3:
						  u = 2;
						  w = 0;
						  break;
					  case 4:
						  u = 3;
						  w = 0;
						  break;
					  case 5:
						  u = 4;
						  w = 0;
						  break;
					  case 6:
						  u = 0;
						  w = 1;
						  break;
					  case 7:
						  u = 1;
						  w = 1;
						  break;
					  case 8:
						  u = 2;
						  w = 1;
						  break;
					  case 9:
						  u = 3;
						  w = 1;
						  break;
					  case 10:
						  u = 4;
						  w = 1;
						  break;
					  case 11:
						  u = 5;
						  w = 1;
						  break;
					  case 12:
						  u = 6;
						  w = 1;
						  break;
					  case 13:
						  u = 0;
						  w = 2;
						  break;
					  case 14:
						  u = 1;
						  w = 2;
						  break;
					  case 15:
						  u = 2;
						  w = 2;
						  break;
					  }
					  licznik++;
					  break;
				  }
				  else
					  released = true;	///
				  break;
		}
		case 5:
		{
				  if (licznik <= 20){
					  switch (licznik){
					  case 1:
						  u = 0;
						  w = 1;
						  break;
					  case 2:
						  u = 1;
						  w = 1;
						  break;
					  case 3:
						  u = 2;
						  w = 1;
						  break;
					  case 4:
						  u = 3;
						  w = 1;
						  break;
					  case 5:
						  u = 4;
						  w = 1;
						  break;
					  case 6:
						  u = 5;
						  w = 1;
						  break;
					  case 7:
						  u = 6;
						  w = 1;
						  break;
					  case 8:
						  u = 7;
						  w = 1;
						  break;
					  case 9:
						  u = 8;
						  w = 1;
						  break;
					  case 10:
						  u = 9;
						  w = 1;
						  break;
					  case 11:
						  u = 0;
						  w = 2;
						  break;
					  case 12:
						  u = 1;
						  w = 2;
						  break;
					  case 13:
						  u = 2;
						  w = 2;
						  break;
					  case 14:
						  u = 3;
						  w = 2;
						  break;
					  case 15:
						  u = 4;
						  w = 2;
						  break;
					  case 16:
						  u = 0;
						  w = 0;
						  break;
					  case 17:
						  u = 1;
						  w = 0;
						  break;
					  case 18:
						  u = 2;
						  w = 0;
						  break;
					  case 19:
						  u = 3;
						  w = 0;
						  break;
					  case 20:
						  u = 4;
						  w = 0;
						  break;
					  }
					  licznik++;
					  break;
				  }
				  else
					  released = true;	///
				  break;
		}
		}
		switch (w){
		case 0:
			wolf[u].release = 1;
			cout << "wolf " << u << " wypuszczony!" << endl;
			break;
		case 1:
			troll[u].release = 1;
			cout << "troll " << u << " wypuszczony!" << endl;
			break;
		case 2:
			ogre[u].release = 1;
			cout << "ogre " << u << " wypuszczony!" << endl;
		}

		/*for (int i = 0; i < 10; i++){
		cout << "Troll[" << i << "] " << troll[i].release << "\t";
		cout << "Wolf[" << i << "] " << wolf[i].release << "\t";
		cout << "Ogre[" << i << "] " << ogre[i].release << "\t";
		cout << endl;
		}*/
		cout << endl;
	}


	//u++;
	//if (u == 10){
	//	u = 0;
	//	w++;
	//}
}