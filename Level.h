#ifndef LEVEL_H
#define LEVEL_H

#include "Functions.h"

#include "Troll.h"
#include "Wolf.h"
#include "Ogre.h"
#include "Player.h"


class Troll;
class Wolf;
class Ogre;
class Player;

class Level
{
private:
	int u = 0;	// liczniki
	int w = 0;
	int licznik = 1;
	bool released = false;
	
public:
	int whichLevel = 1;
	const int FPS = 120;
	const int windowWidth = 640;
	const int windowHeight = 480;
	int frameTime;
	
	Level();

	bool releaseMobs(Troll *troll, Ogre *ogre, Wolf *wolf, Player &Gracz);
	void counter(Troll troll[], Ogre ogre[], Wolf wolf[], int wave);
	void resetMobs(Troll *troll, Ogre *ogre, Wolf *wolf);

	~Level();
};

#endif