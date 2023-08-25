#pragma once
#include <SDL.h>
#include "Map.h"
#include "Player.h"
#include "Tilemap.h"

class UI
{
private:
	SDL_Renderer* renderer;
	SDL_Rect userInterfaceRect[1600 / 16][MAX_Y]{};
public:
	UI(SDL_Renderer* renderer, int userInterfaceRectWidth, int userInterfaceRectHeight);
	~UI();
	void RefreshUserInterface();
	void DrawPlayer(SDL_Renderer* renderer, SDL_Texture* tileMapTexture, Player* player);
	void DrawPlayerInfo(SDL_Renderer* renderer, SDL_Texture* tileMapTexture, Player* player);
	void DrawMap(SDL_Renderer* renderer, Map* map, Tilemap* tileMap);
	void DrawText(SDL_Renderer* renderer, SDL_Texture*, int textPositionX, int textPositionY, std::string text);
	void DrawStatusBar(SDL_Renderer* renderer, SDL_Texture* tileMapTexture, std::string message);
	void DrawInventoryPopup(SDL_Renderer* renderer, SDL_Texture* tileMapTexture, Player* player);
	void DrawInventoryItems(SDL_Renderer* renderer, SDL_Texture* tileMapTexture, std::vector<Item> inventory);
	void DrawVendorPopup(SDL_Renderer* renderer, SDL_Texture* tileMapTexture, Vendor* vendor);
};

