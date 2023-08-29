#pragma once

#include <SDL.h>
#include <tuple>

#include "Map.h"
#include "Player.h"
#include "Tilemap.h"
#include "Menu.h"

typedef enum cornerType
{
	TopLeft,
	TopRight,
	BottomLeft,
	BottomRight
} cornerType;

class UI
{
private:
	SDL_Renderer* renderer;
	SDL_Rect userInterfaceRect[GAME_RESOLUTION_WIDTH / 16][GAME_RESOLUTION_HEIGHT / 16];
	void DrawHorizontalLine(SDL_Renderer* renderer, SDL_Texture* tilemapTexture, int row, int startingPoint, int endingPoint);
	void DrawVerticalLine(SDL_Renderer* renderer, SDL_Texture* tilemapTexture, int column, int startingPoint, int endingPoint);
	void DrawPopupBorder(SDL_Renderer* renderer, SDL_Texture* tilemapTexture);
	void DrawCorner(SDL_Renderer* renderer, SDL_Texture* tilemapTexture, cornerType cornerType, int column, int row);
	void DrawBox(SDL_Renderer* renderer, SDL_Texture* tilemapTexture, int topLeftCornerPositionX, int topLeftCornerPositionY, int width, int height);
public:
	UI(SDL_Renderer* renderer, int userInterfaceRectWidth, int userInterfaceRectHeight);
	~UI();
	std::tuple<bool, Player> DrawStartingMenu(SDL_Renderer* renderer, SDL_Texture* tilemapTexture);
	void RefreshUserInterface();
	void DrawPlayer(SDL_Renderer* renderer, SDL_Texture* tilemapTexture, Player* player);
	void DrawPlayerInfo(SDL_Renderer* renderer, SDL_Texture* tilemapTexture, Player* player);
	void DrawMap(SDL_Renderer* renderer, Map* map, Tilemap* tilemap);
	void DrawText(SDL_Renderer* renderer, SDL_Texture*, int textPositionX, int textPositionY, std::string text);
	void DrawStatusBar(SDL_Renderer* renderer, SDL_Texture* tilemapTexture, std::string message);
	void DrawInventoryPopup(SDL_Renderer* renderer, SDL_Texture* tilemapTexture, Player* player, int selectedItem, int startingItem, int endingItem);
	void DrawInventoryItems(SDL_Renderer* renderer, SDL_Texture* tilemapTexture, std::array<Item, 50>* inventory, int itemsInInventory, int selectedItem, int startingItem, int endingItem);
	void DrawVendorPopup(SDL_Renderer* renderer, SDL_Texture* tilemapTexture, Vendor* vendor, int selectedItem, int startingItem, int endingItem);
};

