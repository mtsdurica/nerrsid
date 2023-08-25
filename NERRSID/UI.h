#pragma once
#include <SDL.h>
#include "Map.h"
#include "Player.h"
#include "Tilemap.h"

class UI
{
private:
	SDL_Renderer* renderer;
	SDL_Rect userInterfaceRect[MAX_X * 2][MAX_Y]{};
public:
	explicit UI(SDL_Renderer* renderer);
	~UI();
	void refreshUserInterface();
	void drawMap();
	void drawPlayer(SDL_Renderer*, SDL_Texture*, Player*);
	void drawPlayerInfo(SDL_Renderer*, SDL_Texture*, Player*);
	void dumpMap(SDL_Renderer*, Map*, Tilemap*);
	void drawText(SDL_Renderer*, SDL_Texture*, int, int, std::string);
};

