#include "Functions.h"

using namespace std;

SDL_Texture *LoadTexture(string filePath, SDL_Renderer *renderTarget){
	SDL_Texture *texture = nullptr;
	SDL_Surface *surface = IMG_Load(filePath.c_str());
	if (surface == NULL)
		cout << "Error 1" << endl;
	else {
		texture = SDL_CreateTextureFromSurface(renderTarget, surface);
		if (texture == NULL)
			cout << "Error 2" << endl;
	}

	SDL_FreeSurface(surface);

	return texture;
}

SDL_Texture *LoadText(TTF_Font* font, SDL_Color color, SDL_Renderer *renderTarget, const char *text){
	SDL_Texture *texture = nullptr;
	SDL_Surface* surface = nullptr;
	surface = TTF_RenderText_Solid(font, text, color);
	if (surface == NULL)
		cout << "Error 1" << endl;
	else {
		texture = SDL_CreateTextureFromSurface(renderTarget, surface);
		if (texture == NULL)
			cout << "Error: " << SDL_GetError() << endl;
	}

	SDL_FreeSurface(surface);

	return texture;
}

string intToStr(int n)
{
	string tmp, ret;
	if (n < 0) {
		ret = "-";
		n = -n;
	}
	do {
		tmp += n % 10 + 48;
		n -= n % 10;
	} while (n /= 10);
	for (int i = tmp.size() - 1; i >= 0; i--)
		ret += tmp[i];
	return ret;
}

int hpImage(int hp, int maxHp){
	if (hp == maxHp)
		return 9;
	else
		return (int)floor(((float)hp / (float)maxHp) * 10);
}

bool isHover(SDL_Rect hoverPosition, SDL_Event ev){
	if (ev.button.x <= hoverPosition.x + 50 && ev.button.x >= hoverPosition.x
		&& ev.button.y >= hoverPosition.y && ev.button.y <= hoverPosition.y + 50)
		return true;
	else
		return false;
}