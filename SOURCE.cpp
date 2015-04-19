#pragma message("DEBUG UNICORNIO: added libs: sdl2.lib sdl2main.lib sdl2_image.lib sdl2_ttf.lib sdl2_mixer.lib")
#pragma comment( lib, "SDL/SDL2.lib" )
#pragma comment( lib, "SDL/SDL2main.lib" )
#pragma comment( lib, "SDL/SDL2_image.lib" )
#pragma comment( lib, "SDL/SDL2_ttf.lib" )
//#pragma comment( lib, "SDL/SDL2_mixer.lib" )

#include <sstream>
#include <math.h>

//inkludujemy klasy
#include "Level.h" // zawiera functions.h

#include "Mage.h"
#include "Archer.h"
#include "Cannon.h"

#include "Player.h"

#include "Troll.h"
#include "Wolf.h"
#include "Ogre.h"

using namespace std;


//int SDL_main(int argc, char* argv[])
int main(int argc, char* argv[])
{
	
	int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;		// mo¿liwoœæ fot png i jpg
	IMG_InitFlags(imgFlags) & imgFlags;

	SDL_Window *window = nullptr;				//tworzymy okno i rendera
	SDL_Renderer *renderTarget = nullptr;
	const Uint8 *keyState;				// deklaracja klawiatury

	Level *Game = new Level();//		(0, nullptr, nullptr, nullptr);

	Player Maciej(0, 800, 5);		// tworzymy gracza (score, money, lives)

	// polimorficzny wskaznik init
	Tower *wsk[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	//archer init
	Archer archer[12]{
		{ 20, 120 }, { 100, 180 }, { 180, 240 },
		{ 260, 300 }, { 340, 360 }, { 420, 420 },
		{ 180, 10 }, { 260, 70 }, { 340, 130 },
		{ 420, 190 }, { 500, 250 }, { 580, 310 }
	};
	//mage init
	Mage mage[12]{
		{ 20, 120 }, { 100, 180 }, { 180, 240 },
		{ 260, 300 }, { 340, 360 }, { 420, 420 },
		{ 180, 10 }, { 260, 70 }, { 340, 130 },
		{ 420, 190 }, { 500, 250 }, { 580, 310 }
	};
	//cannon init
	Cannon cannon[12]{
		{ 20, 120 }, { 100, 180 }, { 180, 240 },
		{ 260, 300 }, { 340, 360 }, { 420, 420 },
		{ 180, 10 }, { 260, 70 }, { 340, 130 },
		{ 420, 190 }, { 500, 250 }, { 580, 310 }
	};

	

	
	//init mobów
	Troll troll[10]{};
	Wolf wolf[10]{};
	Ogre ogre[10]{};

	
	SDL_Rect backgroundPosition;
	backgroundPosition.w = 640;
	backgroundPosition.h = 480;
	backgroundPosition.x = 0;
	backgroundPosition.y = 0;
	
	

	//init tekstur
	SDL_Texture *trollImage = nullptr;
	SDL_Texture *ogreImage = nullptr;
	SDL_Texture *wolfImage = nullptr;
	SDL_Texture *archerImage = nullptr;
	SDL_Texture *mageImage = nullptr;
	SDL_Texture *cannonImage = nullptr;
	SDL_Texture *hoverImage = nullptr;
	SDL_Texture *click1Image = nullptr;
	SDL_Texture *backgroundImage = nullptr;
	SDL_Texture *mageBang = nullptr;
	SDL_Texture *hp[10] = { nullptr };
	SDL_Texture *click2Image = nullptr;
	SDL_Texture *cannonBang = nullptr;
	SDL_Texture *archerBang = nullptr;
	SDL_Texture *levelImage[7] = { nullptr };

	SDL_Texture *displayImage = nullptr;
	SDL_Texture *displayImage2 = nullptr;
	SDL_Texture *youAreDeadImage = nullptr;
	SDL_Texture *youWinImage = nullptr;

	SDL_Texture *click1TableImage = nullptr;
	SDL_Texture *click2TableImage = nullptr;
	SDL_Texture *click2TableImage2 = nullptr;

	SDL_Rect click1TablePosition;
	click1TablePosition.x = 420;
	click1TablePosition.y = 20;
	click1TablePosition.w = 220;
	click1TablePosition.h = 106;

	


	SDL_Texture *startButton = nullptr;
	SDL_Texture *startButtonHover = nullptr;
	SDL_Rect startButtonPosition;
	startButtonPosition.x = 20;
	startButtonPosition.y = 10;
	startButtonPosition.w = startButtonPosition.h = 32;

	SDL_Rect bangRect;
	SDL_Rect bangPosition;
	bangRect.h = bangRect.w = bangPosition.h = bangPosition.w = 64;
	bangRect.x = bangRect.y = 0;
	bangPosition.x = bangPosition.y = 0;

	
		//init towerplace'ów
	SDL_Rect hover[12];
	SDL_Rect hoverPosition[12];
	for (int i = 0; i < 6; i++) {			// wspolrzedne i szerokosc tower place'ów part I
		hoverPosition[i].h = hoverPosition[i].w = 50;
		hoverPosition[i].x = 20 + (i * 80);
		hoverPosition[i].y = 120 + (i * 60);
		hover[i].x = 20 + (i * 80);
		hover[i].y = 120 + (i * 60);
		hover[i].w = 50;
		hover[i].h = 50;
	}

	for (int i = 6; i < 12; i++) {							// part II
		hoverPosition[i].h = hoverPosition[i].w = 50;
		hoverPosition[i].x = 180 + ((i-6) * 80);
		hoverPosition[i].y = 10 + ((i-6) * 60);
		hover[i].x = 180 + ((i-6) * 80);
		hover[i].y = 10 + ((i-6) * 60);
		hover[i].w = 50;
		hover[i].h = 50;
	}
	
	
	SDL_Init(SDL_INIT_EVERYTHING);	// tworzymy okno i rendera
	window = SDL_CreateWindow("joTowerDefenseGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Game->windowWidth, Game->windowHeight, SDL_WINDOW_SHOWN);		//gejm
	renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	
	if (TTF_Init() < 0)		// init czcionki
		cout << "Error: " << TTF_GetError() << endl;

	int wave = 0;

	TTF_Font* tibiaFont = TTF_OpenFont("TibiaFont.ttf", 18);		// robimy czcionki
	TTF_Font* waveFont = TTF_OpenFont("TibiaFont.ttf", 20);
	TTF_Font* deadFont = TTF_OpenFont("TibiaFont.ttf", 24);
	SDL_Color fontColor = { 255, 255, 0 };

						// init wszystkich napisów
	SDL_Texture* staticLives = nullptr;
	SDL_Rect staticLivesRect; staticLivesRect.x = 20; staticLivesRect.y = 380;
	staticLives = LoadText(tibiaFont, fontColor, renderTarget, "Lives :");
	TTF_SizeText(tibiaFont, "Lives :", &staticLivesRect.w, &staticLivesRect.h);// ustalamy wysokoœæ i szerokoœc proporcjonalnie do czcionki

	SDL_Texture* staticWave = nullptr;
	SDL_Rect staticWaveRect; staticWaveRect.x = 270; staticWaveRect.y = 10;
	staticWave = LoadText(waveFont, fontColor, renderTarget, "Wave");
	TTF_SizeText(waveFont, "Wave", &staticWaveRect.w, &staticWaveRect.h);

	SDL_Texture* staticMoney = nullptr;	
	SDL_Rect staticMoneyRect; staticMoneyRect.x = 20; staticMoneyRect.y = 440;
	staticMoney = LoadText(tibiaFont, fontColor, renderTarget, "Money :");
	TTF_SizeText(tibiaFont, "Money :", &staticMoneyRect.w, &staticMoneyRect.h); 

	SDL_Texture* staticScore = nullptr;
	SDL_Rect staticScoreRect; staticScoreRect.x = 20; staticScoreRect.y = 410;
	staticScore = LoadText(tibiaFont, fontColor, renderTarget, "Score : ");
	TTF_SizeText(tibiaFont, "Score :", &staticScoreRect.w, &staticScoreRect.h);

	SDL_Texture* textMoney = nullptr;
	string kasatemp;	//rzutujemy inta na const chara*
	const char* kasa;
	kasatemp = intToStr(Maciej.money); kasa = kasatemp.c_str();
	textMoney = LoadText(tibiaFont, fontColor, renderTarget, kasa);
	SDL_Rect textMoneyRect;	textMoneyRect.x = 110; textMoneyRect.y = 440;
	TTF_SizeText(tibiaFont, kasa, &textMoneyRect.w, &textMoneyRect.h);

	SDL_Texture* textWave = nullptr;
	string vvavetemp; const char* vvave; vvavetemp = intToStr(wave); vvave = vvavetemp.c_str();
	textWave = LoadText(waveFont, fontColor, renderTarget, vvave);
	SDL_Rect textWaveRect; textWaveRect.x = 340; textWaveRect.y = 10;
	TTF_SizeText(waveFont, vvave, &textWaveRect.w, &textWaveRect.h);
	
	SDL_Texture* textScore = nullptr;
	string skortemp; const char* skor; skortemp = intToStr(Maciej.points); skor = skortemp.c_str();
	textScore = LoadText(tibiaFont, fontColor, renderTarget, skor);
	SDL_Rect textScoreRect; textScoreRect.x = 95; textScoreRect.y = 410;
	SDL_Rect deadScoreRect; deadScoreRect.x = 40; deadScoreRect.y = 210;
	TTF_SizeText(tibiaFont, skor, &textScoreRect.w, &textScoreRect.h);

	SDL_Texture* textLives = nullptr;
	string lajftemp; const char* lajf; lajftemp = intToStr(Maciej.points); lajf = lajftemp.c_str();
	textLives = LoadText(tibiaFont, fontColor, renderTarget, lajf);
	SDL_Rect textLivesRect;	textLivesRect.x = 95; textLivesRect.y = 380;
	TTF_SizeText(tibiaFont, lajf, &textLivesRect.w, &textLivesRect.h);

	SDL_Texture* textToLevel = nullptr;
	string toleveltemp;	const char* tolevel; toleveltemp = intToStr(0); tolevel = toleveltemp.c_str();
	textToLevel = LoadText(tibiaFont, fontColor, renderTarget, tolevel);
	SDL_Rect textToLevelRect; textToLevelRect.x = 610; textToLevelRect.y = 15;
	TTF_SizeText(tibiaFont, tolevel, &textToLevelRect.w, &textToLevelRect.h);

	SDL_Texture* textToPrice = nullptr;
	string topricetemp;	const char* toprice; topricetemp = intToStr(0); toprice = topricetemp.c_str();
	textToPrice = LoadText(tibiaFont, fontColor, renderTarget, toprice);
	SDL_Rect textToPriceRect; textToPriceRect.x = 485; textToPriceRect.y = 55;
	TTF_SizeText(tibiaFont, tolevel, &textToPriceRect.w, &textToPriceRect.h);

	SDL_Texture* textToSell = nullptr;
	string toselltemp; const char* tosell; toselltemp = intToStr(0); tosell = toselltemp.c_str();
	textToSell = LoadText(tibiaFont, fontColor, renderTarget, tosell);
	SDL_Rect textToSellRect; textToSellRect.x = 530; textToSellRect.y = 95;
	TTF_SizeText(tibiaFont, tolevel, &textToSellRect.w, &textToSellRect.h);

	
				// wczytujemy foty oraz tworzymy tekstury
	youWinImage = LoadTexture("images/youWin.png", renderTarget);
	displayImage = LoadTexture("images/main.png", renderTarget);
	displayImage2 = LoadTexture("images/mainHover.png", renderTarget);
	youAreDeadImage = LoadTexture("images/youAreDead.png", renderTarget);
	click1Image = LoadTexture("images/buyTower2.png", renderTarget);
	click2Image = LoadTexture("images/sellTower.png", renderTarget);
	trollImage = LoadTexture("images/troll.png", renderTarget);
	wolfImage = LoadTexture("images/wolf.png", renderTarget);
	ogreImage = LoadTexture("images/ogre.png", renderTarget);
	backgroundImage = LoadTexture("images/backgroundGrass.png", renderTarget);
	hoverImage = LoadTexture("images/buyTower.png", renderTarget);
	archerImage = LoadTexture("images/archerTower.png", renderTarget);
	mageImage = LoadTexture("images/mageTower.png", renderTarget);
	cannonImage = LoadTexture("images/cannonTower.png", renderTarget);
	startButton = LoadTexture("images/start.png", renderTarget);
	startButtonHover = LoadTexture("images/startHover.png", renderTarget);
	click1TableImage = LoadTexture("images/click1table.png", renderTarget);	
	click2TableImage = LoadTexture("images/click2table.png", renderTarget); 
	click2TableImage2 = LoadTexture("images/click2table2.png", renderTarget);

	cannonBang = LoadTexture("images/cannonBang.png", renderTarget);
	archerBang = LoadTexture("images/archerBang.png", renderTarget);
	mageBang = LoadTexture("images/mageBang.png", renderTarget);

	hp[0] = LoadTexture("images/hp/10.jpg", renderTarget);
	hp[1] = LoadTexture("images/hp/20.jpg", renderTarget);
	hp[2] = LoadTexture("images/hp/30.jpg", renderTarget);
	hp[3] = LoadTexture("images/hp/40.jpg", renderTarget);
	hp[4] = LoadTexture("images/hp/50.jpg", renderTarget);
	hp[5] = LoadTexture("images/hp/60.jpg", renderTarget);
	hp[6] = LoadTexture("images/hp/70.jpg", renderTarget);
	hp[7] = LoadTexture("images/hp/80.jpg", renderTarget);
	hp[8] = LoadTexture("images/hp/90.jpg", renderTarget);
	hp[9] = LoadTexture("images/hp/100.jpg", renderTarget);

	levelImage[1] = LoadTexture("images/level/level1.png", renderTarget);
	levelImage[2] = LoadTexture("images/level/level2.png", renderTarget);
	levelImage[3] = LoadTexture("images/level/level3.png", renderTarget);
	levelImage[4] = LoadTexture("images/level/level4.png", renderTarget);
	levelImage[5] = LoadTexture("images/level/level5.png", renderTarget);
	levelImage[6] = LoadTexture("images/level/level6.png", renderTarget);
	
		//init flag 
	bool flag = false;
	bool isRunning = true;
	bool clicked1[12] = { 0 };		
	bool clicked2[12] = { 0 };
	bool visibleButton = true;
	bool counter = false;
	bool isFree[12] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };				// zmienna, która zezwala lub nie na zakup wie¿y
	SDL_Event ev;							//tworzymy zmienn¹ event

	Mob* target[12]{0}; // polimorficzny target wie¿y

	
	int display = 1;	// zmienna wybieraj¹ca który ekran wyœwietlaæ

	while (isRunning){

	
		switch (display){
		case 1:{		// ekran g³owny
				   while (SDL_PollEvent(&ev) != 0)
				   if (ev.type == SDL_QUIT)
					   isRunning = false;

				   SDL_RenderClear(renderTarget);
				   SDL_RenderCopy(renderTarget, displayImage, NULL, &backgroundPosition);

				   if (ev.type == SDL_MOUSEMOTION)
					   if (ev.button.x >= 260 && ev.button.x <= 390 && ev.button.y >= 80 && ev.button.y <= 115) //jak naje¿d¿amy na przycisk start
						   SDL_RenderCopy(renderTarget, displayImage2, NULL, &backgroundPosition);
					   if (ev.type == SDL_MOUSEBUTTONUP && ev.button.x >= 260 && ev.button.x <= 390 && ev.button.y >= 80 && ev.button.y <= 115){
						   display = 2;
					   }
				   
				   
				   SDL_RenderPresent(renderTarget);
				   SDL_UpdateWindowSurface(window);
				   break;
		}
		case 3:{	// ekran pora¿ki
				   while (SDL_PollEvent(&ev) != 0)
				   if (ev.type == SDL_QUIT)
					   isRunning = false;

				   SDL_RenderClear(renderTarget);
				   SDL_RenderCopy(renderTarget, youAreDeadImage, NULL, &backgroundPosition);
				   
				   TTF_SizeText(deadFont, skor, &deadScoreRect.w, &deadScoreRect.h);
				   SDL_RenderCopy(renderTarget, textScore, NULL, &deadScoreRect);

				   SDL_RenderPresent(renderTarget);
				   SDL_UpdateWindowSurface(window);
				   break;
		}

		case 4:{		// ekran wygranej
				   while (SDL_PollEvent(&ev) != 0)
				   if (ev.type == SDL_QUIT)
					   isRunning = false;

				   SDL_RenderClear(renderTarget);
				   SDL_RenderCopy(renderTarget, youWinImage, NULL, &backgroundPosition);

				   SDL_RenderPresent(renderTarget);
				   SDL_UpdateWindowSurface(window);
				   break;
		}
		case 2:		//ekran gry
		{
				  while (SDL_PollEvent(&ev) != 0)
				  if (ev.type == SDL_QUIT)
					  isRunning = false;
				  flag = false;
				

				  if (Maciej.Lose())	//przegrana !
					  display = 3;

				  Game->frameTime++;				



				  if (Game->frameTime % 30 == 0) {			// GIFY 

					  for (int i = 0; i < 10; i++){							// przesuwamy ramke
						  troll[i].monster.x += 32;		//frameWidth
						  if (troll[i].monster.x >= 64)		//textureWidth)					
							  troll[i].monster.x = 0;		// zerujemy obrazek

						  wolf[i].monster.x += 45;
						  if (wolf[i].monster.x >= 90)		//textureWidth
							  wolf[i].monster.x = 0;

						  ogre[i].monster.x += 64;
						  if (ogre[i].monster.x >= 128)
							  ogre[i].monster.x = 0;
					  }
					 
				  }


				  if (Game->frameTime == 120)	// zapêtlanie czasu
				  {
					  //flag = false;
					  Game->frameTime = 0;
				  }

				  SDL_RenderClear(renderTarget);			// czyœmimy poprzedni render

				  SDL_RenderCopy(renderTarget, backgroundImage, NULL, &backgroundPosition); // t³o

				  for (int i = 0; i < 10; i++){		// rysujemy potwory i ich hpbar jak ¿yj¹
					  if (troll[i].hp > 0 && troll[i].release){ // release to flaga czy ma wypuszczaæ czy nie. w runAway zmieniamy na falsh jak ucieknie
						  SDL_RenderCopy(renderTarget, trollImage, &troll[i].monster, &troll[i].monsterPosition);
						  SDL_RenderCopy(renderTarget, hp[hpImage(troll[i].hp, troll[i].maxHp)], &troll[i].hpBar, &troll[i].hpBarPosition);
					  }
					  if (wolf[i].hp > 0 && wolf[i].release){
						  SDL_RenderCopy(renderTarget, wolfImage, &wolf[i].monster, &wolf[i].monsterPosition);
						  SDL_RenderCopy(renderTarget, hp[hpImage(wolf[i].hp, wolf[i].maxHp)], &wolf[i].hpBar, &wolf[i].hpBarPosition);
					  }
					  if (ogre[i].hp > 0 && ogre[i].release){
						  SDL_RenderCopy(renderTarget, ogreImage, &ogre[i].monster, &ogre[i].monsterPosition);
						  SDL_RenderCopy(renderTarget, hp[hpImage(ogre[i].hp, ogre[i].maxHp)], &ogre[i].hpBar, &ogre[i].hpBarPosition);
					  }
				  }

				  for (int i = 0; i < 12; i++){
					  if (counter){							// jak dzia³a licznik wypuszczania to wykonujemy metody attack()
						  if (archer[i].attack(Game->frameTime, Game->FPS, troll, ogre, wolf, target[i], Maciej)) // (Game, troll, ogre, ...
							  SDL_RenderCopy(renderTarget, archerBang, NULL, &target[i]->monsterPosition); // rysujemy bang w czasie uderzenia
						  if (cannon[i].attack(Game->frameTime, Game->FPS, troll, ogre, wolf, target[i], Maciej))
							  SDL_RenderCopy(renderTarget, cannonBang, NULL, &target[i]->monsterPosition);
						  if (mage[i].attack(Game->frameTime, Game->FPS, troll, ogre, wolf, target[i], Maciej))
							  SDL_RenderCopy(renderTarget, mageBang, NULL, &target[i]->monsterPosition); 
					  }
					  //if (wsk[i] != nullptr, target[i] != nullptr && target[i]->hp > 0){
					  //	bangPosition.x = target[i]->monsterPosition.x;
					  //	bangPosition.y = target[i]->monsterPosition.y;
					  //	SDL_RenderCopy(renderTarget, archerBang, NULL, &bangPosition);					// trzeci parametr ¿eby gifa ogarn¹æ 

				  }


				  for (int i = 0; i < 12; i++) {

					  if (ev.type == SDL_MOUSEBUTTONDOWN) {
						  if (ev.button.button == SDL_BUTTON_LEFT) {
							  if (isHover(hoverPosition[i], ev)){			// jak najechalismy w jeden z TowerPlace'ów i kliknêliœmy
								  if (!clicked1[i] && !clicked2[i] && isFree[i]) {	// jak nie jest klikniety i wolny

									  clicked1[i] = true;
									  for (int j = 0; j < 12; j++){
										  clicked2[j] = false;
										  if (j != i)
											  clicked1[j] = false;	//pozostale gasimy		
									  }									  
								  }
								  else if (!isFree[i] && !clicked2[i]){
									  clicked2[i] = true;
									  for (int j = 0; j < 12; j++){		// gasimy pozostale
										  clicked1[j] = false;
										  if (j != i)
											  clicked2[j] = false;
									  }									
								  }
							  }
						  }
					  }
					  else if (ev.type == SDL_MOUSEMOTION){				// wyswietlamy KLIK
						  if (isHover(hoverPosition[i], ev))
						  {
							  if (!clicked1[i] && !clicked2[i] && wsk[i] == nullptr){
								  SDL_RenderCopy(renderTarget, hoverImage, NULL, &hoverPosition[i]);
							  }
						  }
					  }
				  }
				 
				  int j = 0;									//zmienna do kopiowania bie¿¹cego numeru towerPlace'a
				  for (int i = 0; i < 12; i++) {				// zmieniamy wybrany Tower place
					  if (clicked1[i] == true && wsk[i] == nullptr){
						  SDL_RenderCopy(renderTarget, click1Image, NULL, &hoverPosition[i]);
						  SDL_RenderCopy(renderTarget, click1TableImage, NULL, &click1TablePosition);  // rysujemy wybrany click1 i info o wie¿ach
						  j = i;
					  }
					  else if (clicked2[i] == true){			// rysujemy to, co ma byæ po kliknieciu clicked2[i]
						  SDL_RenderCopy(renderTarget, click2Image, NULL, &hoverPosition[i]);

						  {
							  if (wsk[i]->returnLevel() < 6){	// info o ulepszeniu jak level 0..5
								  SDL_RenderCopy(renderTarget, click2TableImage, NULL, &click1TablePosition);

								  toleveltemp = intToStr(wsk[i]->returnLevel() + 1);
								  tolevel = toleveltemp.c_str();
								  textToLevel = LoadText(tibiaFont, fontColor, renderTarget, tolevel);
								  TTF_SizeText(tibiaFont, tolevel, &textToLevelRect.w, &textToLevelRect.h);
								  SDL_RenderCopy(renderTarget, textToLevel, NULL, &textToLevelRect);

								  topricetemp = intToStr(wsk[i]->returnPrice(wsk[i]->returnLevel() + 1));
								  toprice = topricetemp.c_str();
								  textToPrice = LoadText(tibiaFont, fontColor, renderTarget, toprice);
								  TTF_SizeText(tibiaFont, toprice, &textToPriceRect.w, &textToPriceRect.h);
								  SDL_RenderCopy(renderTarget, textToPrice, NULL, &textToPriceRect);
							  }
							  else { //info ¿e ju¿ nie mo¿na ulepszyæ
								  SDL_RenderCopy(renderTarget, click2TableImage2, NULL, &click1TablePosition);
							  }

							  toselltemp = intToStr(Maciej.howMuchForSell(wsk[i]));	// info o sprzedaniu wiezy
							  tosell = toselltemp.c_str();
							  textToSell = LoadText(tibiaFont, fontColor, renderTarget, tosell);
							  TTF_SizeText(tibiaFont, tosell, &textToSellRect.w, &textToSellRect.h);
							  SDL_RenderCopy(renderTarget, textToSell, NULL, &textToSellRect);
						  }
						  j = i;
					  }
				  }

				  keyState = SDL_GetKeyboardState(NULL);		// obs³uga klawiatury
				  if (clicked1[j] == true){					// kupowanie wie¿y
					  if (isFree[j] == true){
						  if (keyState[SDL_SCANCODE_1]) 
							  Maciej.buyTower(wsk[j], archer[j], j, isFree);
						  else if (keyState[SDL_SCANCODE_2])
							  Maciej.buyTower(wsk[j], mage[j], j, isFree);					  
						  else if (keyState[SDL_SCANCODE_3])
							  Maciej.buyTower(wsk[j], cannon[j], j, isFree);					  
					  }
				  }
				  else if (clicked2[j] == true){	//ulepszanie i sprzeda¿
					  if (keyState[SDL_SCANCODE_4] && clicked2[j] == true){
						  clicked2[j] = false;
						  Maciej.upgradeTower(wsk[j]);
					  }
					  else if (keyState[SDL_SCANCODE_5]){
						  clicked2[j] = false;
						  Maciej.sellTower(wsk[j], wsk[j]->returnBought(), j, isFree);
					  }
				  }


				  for (int i = 0; i < 12; i++){		// rysujemy zakupione wie¿e
					  if (wsk[i] != nullptr){
						  
						  switch (wsk[i]->returnBought()){
						  case 1:
							  SDL_RenderCopy(renderTarget, archerImage, NULL, &hoverPosition[i]);
							  break;
						  case 2:
							  SDL_RenderCopy(renderTarget, mageImage, NULL, &hoverPosition[i]);
							  break;
						  case 3:
							  SDL_RenderCopy(renderTarget, cannonImage, NULL, &hoverPosition[i]);
							  break;
						  default:
							  break;
						  }
						  if (wsk[i]->returnLevel()>0)
							  SDL_RenderCopy(renderTarget, levelImage[wsk[i]->returnLevel()], NULL, &hoverPosition[i]);	//rysujemy poziom wie¿y
					  }
				  }

						// wyswietlamy startButton
				  if (visibleButton) {
					  SDL_RenderCopy(renderTarget, startButton, NULL, &startButtonPosition);
					  if (ev.type == SDL_MOUSEMOTION)	{
						  if (ev.button.x <= startButtonPosition.x + 32 && ev.button.x >= startButtonPosition.x && ev.button.y >= startButtonPosition.y && ev.button.y <= startButtonPosition.y + 32)
							  SDL_RenderCopy(renderTarget, startButtonHover, NULL, &startButtonPosition); // kolor jak najedzie siê
					  }

					  if (ev.type == SDL_MOUSEBUTTONDOWN) {	// po kliknieciu wypuszczamy potwory
						  if (ev.button.x <= startButtonPosition.x + 32 && ev.button.x >= startButtonPosition.x && ev.button.y >= startButtonPosition.y && ev.button.y <= startButtonPosition.y + 32){
							  if (ev.button.button == SDL_BUTTON_LEFT) {
								  counter = true; // odpalamy licznik
								  visibleButton = false;	//gasimy przycisk
								  wave++;	// id fali
							  }
						  }
					  }
				  }

				  {		// dynamicznie zmieniamy ilosc Maciej.money i wyrzucamy na ekran
					  kasatemp = intToStr(Maciej.money);
					  kasa = kasatemp.c_str();
					  textMoney = LoadText(tibiaFont, fontColor, renderTarget, kasa);
					  TTF_SizeText(tibiaFont, kasa, &textMoneyRect.w, &textMoneyRect.h);
					  SDL_RenderCopy(renderTarget, textMoney, NULL, &textMoneyRect);
				  }

				  {
					  skortemp = intToStr(Maciej.points);
					  skor = skortemp.c_str();
					  textScore = LoadText(tibiaFont, fontColor, renderTarget, skor);
					  TTF_SizeText(tibiaFont, skor, &textScoreRect.w, &textScoreRect.h);
					  SDL_RenderCopy(renderTarget, textScore, NULL, &textScoreRect);
				  }

				  {
					  lajftemp = intToStr(Maciej.life);
					  lajf = lajftemp.c_str();
					  textLives = LoadText(tibiaFont, fontColor, renderTarget, lajf);
					  TTF_SizeText(tibiaFont, lajf, &textLivesRect.w, &textLivesRect.h);
					  SDL_RenderCopy(renderTarget, textLives, NULL, &textLivesRect);
				  }

				  {
					  vvavetemp = intToStr(wave);
					  vvave = vvavetemp.c_str();
					  textWave = LoadText(waveFont, fontColor, renderTarget, vvave);
					  TTF_SizeText(waveFont, vvave, &textWaveRect.w, &textWaveRect.h);
					  SDL_RenderCopy(renderTarget, textWave, NULL, &textWaveRect);
				  }
				  SDL_RenderCopy(renderTarget, staticLives, NULL, &staticLivesRect);
				  SDL_RenderCopy(renderTarget, staticMoney, NULL, &staticMoneyRect);
				  SDL_RenderCopy(renderTarget, staticScore, NULL, &staticScoreRect);
				  SDL_RenderCopy(renderTarget, staticWave, NULL, &staticWaveRect);

				  if (counter){
					  Game->counter(troll, ogre, wolf, wave); // gejm
					  if (Game->releaseMobs(troll, ogre, wolf, Maciej)) { // jak true to wszystkie potwory zosta³y zniszczone
						  if (wave == 5)
						  {
							  display = 4;
							  break;
						  }
						  visibleButton = true;
						  counter = false;
						  Game->resetMobs(troll, ogre, wolf);
						  //cout << Game->releaseMobs(troll, ogre, wolf) << endl;
					  }
				  }





				  SDL_RenderPresent(renderTarget);
				  SDL_UpdateWindowSurface(window);
				  break;
		}

		}
		


	//	SDL_Delay(20);
	}
		



//		imageSurface = nullptr;											// zerujemy wszystkie wskazniki
//	SDL_DestroyWindow(window);
////	SDL_FreeSurface(currentImage);
//	SDL_DestroyRenderer(renderTarget);
//	SDL_DestroyTexture(trollImage);
//	SDL_DestroyTexture(wolfImage);
//	SDL_DestroyTexture(hoverImage);
//	SDL_DestroyTexture(backgroundImage);
//
////	currentImage = nullptr;
//	renderTarget = nullptr;
//	window = nullptr;
////	windowSurface = nullptr;
	//delete Game();
	Game->~Level();		//gejm

	//textSurface = nullptr;
	//SDL_FreeSurface(textSurface);
	//text = nullptr;
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
	//system("pause");
	return 0;
}







//SDL_Surface *OptimizedSurface(string filePath, SDL_Surface *windowSurface){
//	SDL_Surface *optimizedSurface = nullptr;
//	SDL_Surface *surface = SDL_LoadBMP(filePath.c_str());
//	if (surface == NULL)
//		cout << "Error" << endl;
//	else {
//		optimizedSurface = SDL_ConvertSurface(surface, windowSurface->format, 0);
//		if (optimizedSurface == NULL)
//			cout << "Error" << endl;
//	}
//
//	SDL_FreeSurface(surface);
//
//	return optimizedSurface;
//}


//else if (ev.type == SDL_KEYDOWN)
//{
//	switch (ev.key.keysym.sym)
//	{
//	case SDLK_RIGHT:
//		trollPosition.x += trollXMoveSpeed * deltaTime;
//		break;
//	case SDLK_LEFT:
//		trollPosition.x -= trollYMoveSpeed * deltaTime;
//		break;
//	case SDLK_a:
//		wolfPosition.x -= wolfXMoveSpeed * deltaTime * 2;
//		break;
//	case SDLK_d:
//		wolfPosition.x += wolfXMoveSpeed * deltaTime * 2;
//		break;
//	}
//}