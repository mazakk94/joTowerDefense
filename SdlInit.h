#ifndef SDLINIT_H
#define SDLINIT_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

class SdlInit
{
public:
	SDL_Rect monster;
	SDL_Rect monsterPosition;

	SDL_Rect hpBar;
	SDL_Rect hpBarPosition;

	SdlInit();
	~SdlInit();
};

#endif