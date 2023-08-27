#pragma once
#include <SDL.h>
#include "Map.h"
#include "Player.h"
#include "Tilemap.h"

class UI
{
private:
	SDL_Renderer* renderer;
	SDL_Rect userInterfaceRect[GAME_RESOLUTION_WIDTH / 16][GAME_RESOLUTION_HEIGHT / 16];
public:
	UI(SDL_Renderer* renderer, int userInterfaceRectWidth, int userInterfaceRectHeight);
	~UI();
	void DrawUI();
	void RefreshUserInterface();
	void DrawPlayer(SDL_Renderer* renderer, SDL_Texture* tilemapTexture, Player* player);
	void DrawPlayerInfo(SDL_Renderer* renderer, SDL_Texture* tilemapTexture, Player* player);
	void DrawMap(SDL_Renderer* renderer, Map* map, Tilemap* tilemap);
	void DrawText(SDL_Renderer* renderer, SDL_Texture*, int textPositionX, int textPositionY, std::string text);
	void DrawStatusBar(SDL_Renderer* renderer, SDL_Texture* tilemapTexture, std::string message);
	void DrawInventoryPopup(SDL_Renderer* renderer, SDL_Texture* tilemapTexture, Player* player, int selectedItem, int startingItem, int endingItem);
	void DrawInventoryItems(SDL_Renderer* renderer, SDL_Texture* tilemapTexture, std::vector<Item>* inventory, int itemsInInventory, int selectedItem, int startingItem, int endingItem);
	void DrawVendorPopup(SDL_Renderer* renderer, SDL_Texture* tilemapTexture, Vendor* vendor, int selectedItem, int startingItem, int endingItem);
};

