#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>
#include <iostream>

using namespace std;

SDL_Texture *LoadTexture(string filePath, SDL_Renderer *renderTarget);
SDL_Texture *LoadText(TTF_Font* font, SDL_Color color, SDL_Renderer *renderTarget, const char *text);
string intToStr(int n);
int hpImage(int hp, int maxHp);
bool isHover(SDL_Rect hoverPosition, SDL_Event ev);

#endif